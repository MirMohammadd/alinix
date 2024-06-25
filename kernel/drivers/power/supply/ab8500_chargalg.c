/**
 * @author Ali Mirmohammad
 * @file ab8500_chargalg.c
 * *************************************IMPORTANT ALINIX LICENSE TERM********************************************
 ** This file is part of AliNix.

**AliNix is free software: you can redistribute it and/or modify
**it under the terms of the GNU Affero General Public License as published by
**the Free Software Foundation, either version 3 of the License, or
**(at your option) any later version.

**AliNix is distributed in the hope that it will be useful,
**but WITHOUT ANY WARRANTY; without even the implied warranty of
**MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
**GNU Affero General Public License for more details.

**You should have received a copy of the GNU Affero General Public License
**along with AliNix. If not, see <https://www.gnu.org/licenses/>.
*/

/**
 * @abstraction:
 * 	- Kernel charger drivers implemented.
*/

#include <alinix/types.h>
#include <alinix/hrtimer_types.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Kernel Charger Driver")
MODULE_LICENSE("AGPL")
MODULE_VERSION("1.0")



/* Watchdog kick interval */
#define CHG_WD_INTERVAL			(6 * HZ)

/* End-of-charge criteria counter */
#define EOC_COND_CNT			10

/* One hour expressed in seconds */
#define ONE_HOUR_IN_SECONDS            3600

/* Five minutes expressed in seconds */
#define FIVE_MINUTES_IN_SECONDS        300

/*
 * This is the battery capacity limit that will trigger a new
 * full charging cycle in the case where maintenance charging
 * has been disabled
 */
#define AB8500_RECHARGE_CAP		95

enum ab8500_chargers {
	NO_CHG,
	AC_CHG,
	USB_CHG,
};

struct ab8500_chargalg_charger_info {
	enum ab8500_chargers conn_chg;
	enum ab8500_chargers prev_conn_chg;
	enum ab8500_chargers online_chg;
	enum ab8500_chargers prev_online_chg;
	enum ab8500_chargers charger_type;
	bool usb_chg_ok;
	bool ac_chg_ok;
	int usb_volt_uv;
	int usb_curr_ua;
	int ac_volt_uv;
	int ac_curr_ua;
	int usb_vset_uv;
	int usb_iset_ua;
	int ac_vset_uv;
	int ac_iset_ua;
};

struct ab8500_chargalg_battery_data {
	int temp;
	int volt_uv;
	int avg_curr_ua;
	int inst_curr_ua;
	int percent;
};

enum ab8500_chargalg_states {
	STATE_HANDHELD_INIT,
	STATE_HANDHELD,
	STATE_CHG_NOT_OK_INIT,
	STATE_CHG_NOT_OK,
	STATE_HW_TEMP_PROTECT_INIT,
	STATE_HW_TEMP_PROTECT,
	STATE_NORMAL_INIT,
	STATE_NORMAL,
	STATE_WAIT_FOR_RECHARGE_INIT,
	STATE_WAIT_FOR_RECHARGE,
	STATE_MAINTENANCE_A_INIT,
	STATE_MAINTENANCE_A,
	STATE_MAINTENANCE_B_INIT,
	STATE_MAINTENANCE_B,
	STATE_TEMP_UNDEROVER_INIT,
	STATE_TEMP_UNDEROVER,
	STATE_TEMP_LOWHIGH_INIT,
	STATE_TEMP_LOWHIGH,
	STATE_OVV_PROTECT_INIT,
	STATE_OVV_PROTECT,
	STATE_SAFETY_TIMER_EXPIRED_INIT,
	STATE_SAFETY_TIMER_EXPIRED,
	STATE_BATT_REMOVED_INIT,
	STATE_BATT_REMOVED,
	STATE_WD_EXPIRED_INIT,
	STATE_WD_EXPIRED,
};

static const char * const states[] = {
	"HANDHELD_INIT",
	"HANDHELD",
	"CHG_NOT_OK_INIT",
	"CHG_NOT_OK",
	"HW_TEMP_PROTECT_INIT",
	"HW_TEMP_PROTECT",
	"NORMAL_INIT",
	"NORMAL",
	"WAIT_FOR_RECHARGE_INIT",
	"WAIT_FOR_RECHARGE",
	"MAINTENANCE_A_INIT",
	"MAINTENANCE_A",
	"MAINTENANCE_B_INIT",
	"MAINTENANCE_B",
	"TEMP_UNDEROVER_INIT",
	"TEMP_UNDEROVER",
	"TEMP_LOWHIGH_INIT",
	"TEMP_LOWHIGH",
	"OVV_PROTECT_INIT",
	"OVV_PROTECT",
	"SAFETY_TIMER_EXPIRED_INIT",
	"SAFETY_TIMER_EXPIRED",
	"BATT_REMOVED_INIT",
	"BATT_REMOVED",
	"WD_EXPIRED_INIT",
	"WD_EXPIRED",
};

struct ab8500_chargalg_events {
	bool batt_unknown;
	bool mainextchnotok;
	bool batt_ovv;
	bool batt_rem;
	bool btemp_underover;
	bool btemp_low;
	bool btemp_high;
	bool main_thermal_prot;
	bool usb_thermal_prot;
	bool main_ovv;
	bool vbus_ovv;
	bool usbchargernotok;
	bool safety_timer_expired;
	bool maintenance_timer_expired;
	bool ac_wd_expired;
	bool usb_wd_expired;
	bool ac_cv_active;
	bool usb_cv_active;
	bool vbus_collapsed;
};

struct ab8500_charge_curr_maximization {
	int original_iset_ua;
	int current_iset_ua;
	int condition_cnt;
	int max_current_ua;
	int wait_cnt;
	uint8_t level;
};

enum maxim_ret {
	MAXIM_RET_NOACTION,
	MAXIM_RET_CHANGE,
	MAXIM_RET_IBAT_TOO_HIGH,
};


// PRIVATE enum hrtimer_restart
// ab8500_chargalg_safety_timer_expired(struct hrtimer *timer){
//     struct ab8500_chargalg *di = Contains
// }