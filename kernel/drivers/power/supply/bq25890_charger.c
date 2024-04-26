#include <alinix/kernel.h>
#include <alinix/regmap.h>
#include <alinix/physicalmemory.h>

/**
 * @ref https://github.com/torvalds/linux/blob/master/drivers/power/supply/bq25890_charger.c
*/
#define BQ25890_MANUFACTURER		"Texas Instruments"
#define BQ25890_IRQ_PIN			"bq25890_irq"

#define BQ25890_ID			3
#define BQ25895_ID			7
#define BQ25896_ID			0

#define PUMP_EXPRESS_START_DELAY	(5 * HZ)
#define PUMP_EXPRESS_MAX_TRIES		6
#define PUMP_EXPRESS_VBUS_MARGIN_uV	1000000

enum bq25890_chip_version {
	BQ25890,
	BQ25892,
	BQ25895,
	BQ25896,
};

static const char *const bq25890_chip_name[] = {
	"BQ25890",
	"BQ25892",
	"BQ25895",
	"BQ25896",
};

enum bq25890_fields {
	F_EN_HIZ, F_EN_ILIM, F_IINLIM,				     /* Reg00 */
	F_BHOT, F_BCOLD, F_VINDPM_OFS,				     /* Reg01 */
	F_CONV_START, F_CONV_RATE, F_BOOSTF, F_ICO_EN,
	F_HVDCP_EN, F_MAXC_EN, F_FORCE_DPM, F_AUTO_DPDM_EN,	     /* Reg02 */
	F_BAT_LOAD_EN, F_WD_RST, F_OTG_CFG, F_CHG_CFG, F_SYSVMIN,
	F_MIN_VBAT_SEL,						     /* Reg03 */
	F_PUMPX_EN, F_ICHG,					     /* Reg04 */
	F_IPRECHG, F_ITERM,					     /* Reg05 */
	F_VREG, F_BATLOWV, F_VRECHG,				     /* Reg06 */
	F_TERM_EN, F_STAT_DIS, F_WD, F_TMR_EN, F_CHG_TMR,
	F_JEITA_ISET,						     /* Reg07 */
	F_BATCMP, F_VCLAMP, F_TREG,				     /* Reg08 */
	F_FORCE_ICO, F_TMR2X_EN, F_BATFET_DIS, F_JEITA_VSET,
	F_BATFET_DLY, F_BATFET_RST_EN, F_PUMPX_UP, F_PUMPX_DN,	     /* Reg09 */
	F_BOOSTV, F_PFM_OTG_DIS, F_BOOSTI,			     /* Reg0A */
	F_VBUS_STAT, F_CHG_STAT, F_PG_STAT, F_SDP_STAT, F_0B_RSVD,
	F_VSYS_STAT,						     /* Reg0B */
	F_WD_FAULT, F_BOOST_FAULT, F_CHG_FAULT, F_BAT_FAULT,
	F_NTC_FAULT,						     /* Reg0C */
	F_FORCE_VINDPM, F_VINDPM,				     /* Reg0D */
	F_THERM_STAT, F_BATV,					     /* Reg0E */
	F_SYSV,							     /* Reg0F */
	F_TSPCT,						     /* Reg10 */
	F_VBUS_GD, F_VBUSV,					     /* Reg11 */
	F_ICHGR,						     /* Reg12 */
	F_VDPM_STAT, F_IDPM_STAT, F_IDPM_LIM,			     /* Reg13 */
	F_REG_RST, F_ICO_OPTIMIZED, F_PN, F_TS_PROFILE, F_DEV_REV,   /* Reg14 */

	F_MAX_FIELDS
};

/*Converted to the register values */
struct bq25890_init_data{
    uint8_t ichg; /*Charger status*/
    uint8_t vreg; /* regulation voltage		*/
    uint8_t iterm;
    uint8_t iprechg;
    uint8_t sysvmin;
    uint8_t boostv;
    uint8_t boosti;
    uint8_t ilim_en;
    uint8_t rbatcomp;
    uint8_t vclampl; /* IBAT compensation voltage limit */
};

struct bq25890_state{
    uint8_t online;
    uint8_t hiz;
    uint8_t chrg_status;
    uint8_t chrg_fault;
    uint8_t vsys_status;
    uint8_t boost_fault;
    uint8_t bat_fault;
    uint8_t ntc_fault;
};

// struct bq25890_device {
// 	struct i2c_client *client;
// 	struct device *dev;
// 	struct power_supply *charger;
// 	struct power_supply *secondary_chrg;
// 	struct power_supply_desc desc;
// 	char name[28]; /* "bq25890-charger-%d" */
// 	int id;

// 	struct usb_phy *usb_phy;
// 	struct notifier_block usb_nb;
// 	struct work_struct usb_work;
// 	struct delayed_work pump_express_work;
// 	unsigned long usb_event;

// 	struct regmap *rmap;
// 	struct regmap_field *rmap_fields[F_MAX_FIELDS];

// 	bool skip_reset;
// 	bool read_back_init_data;
// 	bool force_hiz;
// 	uint32_t pump_express_vbus_max;
// 	uint32_t iinlim_percentage;
// 	enum bq25890_chip_version chip_version;
// 	struct bq25890_init_data init_data;
// 	struct bq25890_state state;

// 	struct mutex lock; /* protect state data */
// };