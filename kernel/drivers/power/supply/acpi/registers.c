/**
 * @author Ali Mirmohammad
 * @file registers.
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
 * 
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/**
 * @brief ACPI driver for kernel implemented.
 * Kernel registers.
*/
#include <alinix/ucapi/registers.h>
#include <alinix/ucapi/acpi.h>
#include <alinix/ucapi/context.h>
#include <alinix/ucapi/compiler.h>
#include <alinix/ucapi/api.h>
#include <alinix/kernel.h>
#include <alinix/stat.h>
#include <alinix/module.h>

MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("ACPI util driver module")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("0.1")

extern uacpi_status uacpi_kernel_raw_io_read(
    u64, u8, u64 *ret
);


struct uacpi_runtime_context g_uacpi_rt_ctx = { 0 };


enum register_kind {
    REGISTER_KIND_GAS,
    REGISTER_KIND_IO,
};

enum register_access_kind {
    REGISTER_ACCESS_KIND_PRESERVE,
    REGISTER_ACCESS_KIND_WRITE_TO_CLEAR,
    REGISTER_ACCESS_KIND_NORMAL,
};

struct register_spec {
    u8 kind;
    u8 access_kind;
    u8 access_width; // only REGISTER_KIND_IO
    void *accessor0, *accessor1;
    u64 write_only_mask;
    u64 preserve_mask;
};

/**
 * @brief Array of register specifications for ACPI registers.
 *
 * This array contains the specifications for different registers in the ACPI namespace. Each element in the array represents a specific register and its properties, such as kind, access kind, accessors, and masks.
 *
 * @note This array assumes the existence of the `g_uacpi_rt_ctx` global context structure and the `UACPI_REGISTER_MAX` constant.
 */
static struct register_spec registers[UACPI_REGISTER_MAX + 1] = {
    [UACPI_REGISTER_PM1_STS] = {
        .kind = REGISTER_KIND_GAS,
        .access_kind = REGISTER_ACCESS_KIND_WRITE_TO_CLEAR,
        .accessor0 = &g_uacpi_rt_ctx.pm1a_status_blk,
        .accessor1 = &g_uacpi_rt_ctx.pm1b_status_blk,
        .preserve_mask = ACPI_PM1_STS_IGN0_MASK,
    },
    [UACPI_REGISTER_PM1_EN] = {
        .kind = REGISTER_KIND_GAS,
        .access_kind = REGISTER_ACCESS_KIND_PRESERVE,
        .accessor0 = &g_uacpi_rt_ctx.pm1a_enable_blk,
        .accessor1 = &g_uacpi_rt_ctx.pm1b_enable_blk,
    },
    [UACPI_REGISTER_PM1_CNT] = {
        .kind = REGISTER_KIND_GAS,
        .access_kind = REGISTER_ACCESS_KIND_PRESERVE,
        .accessor0 = &g_uacpi_rt_ctx.fadt.x_pm1a_cnt_blk,
        .accessor1 = &g_uacpi_rt_ctx.fadt.x_pm1b_cnt_blk,
        .write_only_mask = ACPI_PM1_CNT_SLP_EN_MASK |
                           ACPI_PM1_CNT_GBL_RLS_MASK,
        .preserve_mask = ACPI_PM1_CNT_PRESERVE_MASK,
    },
    [UACPI_REGISTER_PM_TMR] = {
        .kind = REGISTER_KIND_GAS,
        .access_kind = REGISTER_ACCESS_KIND_PRESERVE,
        .accessor0 = &g_uacpi_rt_ctx.fadt.x_pm_tmr_blk,
    },
    [UACPI_REGISTER_PM2_CNT] = {
        .kind = REGISTER_KIND_GAS,
        .access_kind = REGISTER_ACCESS_KIND_PRESERVE,
        .accessor0 = &g_uacpi_rt_ctx.fadt.x_pm2_cnt_blk,
        .preserve_mask = ACPI_PM2_CNT_PRESERVE_MASK,
    },
    [UACPI_REGISTER_SLP_CNT] = {
        .kind = REGISTER_KIND_GAS,
        .access_kind = REGISTER_ACCESS_KIND_PRESERVE,
        .accessor0 = &g_uacpi_rt_ctx.fadt.sleep_control_reg,
        .write_only_mask = ACPI_SLP_CNT_SLP_EN_MASK,
        .preserve_mask = ACPI_SLP_CNT_PRESERVE_MASK,
    },
    [UACPI_REGISTER_SLP_STS] = {
        .kind = REGISTER_KIND_GAS,
        .access_kind = REGISTER_ACCESS_KIND_WRITE_TO_CLEAR,
        .accessor0 = &g_uacpi_rt_ctx.fadt.sleep_status_reg,
        .preserve_mask = ACPI_SLP_STS_PRESERVE_MASK,
    },
    [UACPI_REGISTER_RESET] = {
        .kind = REGISTER_KIND_GAS,
        .access_kind = REGISTER_ACCESS_KIND_NORMAL,
        .accessor0 = &g_uacpi_rt_ctx.fadt.reset_reg,
    },
    [UACPI_REGISTER_SMI_CMD] = {
        .kind = REGISTER_KIND_IO,
        .access_kind = REGISTER_ACCESS_KIND_NORMAL,
        .access_width = 1,
        .accessor0 = &g_uacpi_rt_ctx.fadt.smi_cmd,
    },
};

/**
 * Retrieves the register specification for the given index.
 *
 * @param idx The index of the register.
 * @return A pointer to the register specification structure if the index is valid,
 *         otherwise NULL.
 */
static struct register_spec *get_reg(u8 idx)
{
    if (idx > UACPI_REGISTER_MAX)
        return NULL;

    return &registers[idx];
}

static uacpi_status read_one(
    enum register_kind kind, void *reg, u8 byte_width,
    u64 *out_value
)
{
    if (kind == REGISTER_KIND_GAS) {
        struct acpi_gas *gas = reg;

        if (!gas->address)
            return UACPI_STATUS_OK;

        return uacpi_gas_read(reg, out_value);
    }

    return uacpi_kernel_raw_io_read(*(u32*)reg, byte_width, out_value);
}

/**
 * Reads a value from a register.
 *
 * @param kind The kind of register (REGISTER_KIND_GAS or other).
 * @param reg A pointer to the register.
 * @param byte_width The byte width of the register.
 * @param out_value A pointer to store the read value.
 * @return The status of the read operation.
 */
static uacpi_status write_one(
    enum register_kind kind, void *reg, u8 byte_width,
    u64 in_value
)
{
    if (kind == REGISTER_KIND_GAS) {
        struct acpi_gas *gas = reg;

        if (!gas->address)
            return UACPI_STATUS_OK;

        return uacpi_gas_write(reg, in_value);
    }

    return uacpi_kernel_raw_io_write(*(u32*)reg, byte_width, in_value);
}

/**
 * Reads the value of a register.
 *
 * @param reg A pointer to the register specification.
 * @param out_value A pointer to store the read value.
 * @return The status of the read operation.
 *
 * This function reads the value of a register specified by the given register specification.
 * It first reads the value from the first accessor using the `read_one` function.
 * If the register has a second accessor, it reads the value from the second accessor using the `read_one` function.
 * The values are then combined and stored in the `out_value` parameter.
 * If the register has a write-only mask, the write-only bits are cleared from the value.
 */
static uacpi_status do_read_register(
    struct register_spec *reg, u64 *out_value
)
{
    uacpi_status ret;
    u64 value0, value1 = 0;

    ret = read_one(reg->kind, reg->accessor0, reg->access_width, &value0);
    if (uacpi_unlikely_error(ret))
        return ret;

    if (reg->accessor1) {
        ret = read_one(reg->kind, reg->accessor1, reg->access_width, &value1);
        if (uacpi_unlikely_error(ret))
            return ret;
    }

    *out_value = value0 | value1;
    if (reg->write_only_mask)
        *out_value &= ~reg->write_only_mask;

    return UACPI_STATUS_OK;
}

/**
 * Reads the value of a register.
 *
 * @param reg_enum The enumeration value representing the register.
 * @param out_value A pointer to store the read value.
 * @return The status of the read operation.
 *
 * This function reads the value of a register specified by the given enumeration value.
 * It first retrieves the register specification using the `get_reg` function.
 * If the register specification is not found, it returns `UACPI_STATUS_INVALID_ARGUMENT`.
 * Otherwise, it calls the `do_read_register` function to perform the actual read operation.
 */
uacpi_status uacpi_read_register(
    enum uacpi_register reg_enum, u64 *out_value
)
{
    struct register_spec *reg;

    reg = get_reg(reg_enum);
    if (uacpi_unlikely(reg == NULL))
        return UACPI_STATUS_INVALID_ARGUMENT;

    return do_read_register(reg, out_value);
}

static uacpi_status do_write_register(
        struct register_spec *reg, u64 in_value
)
{
    uacpi_status ret;

    if (reg->preserve_mask) {
        in_value &= ~reg->preserve_mask;

        if (reg->access_kind == REGISTER_ACCESS_KIND_PRESERVE) {
            u64 data;

            ret = do_read_register(reg, &data);
            if (uacpi_unlikely_error(ret))
                return ret;

            in_value |= data & reg->preserve_mask;
        }
    }

    ret = write_one(reg->kind, reg->accessor0, reg->access_width, in_value);
    if (uacpi_unlikely_error(ret))
        return ret;

    if (reg->accessor1)
        ret = write_one(reg->kind, reg->accessor1, reg->access_width, in_value);

    return ret;
}

uacpi_status uacpi_write_register(
    enum uacpi_register reg_enum, u64 in_value
)
{
    struct register_spec *reg;

    reg = get_reg(reg_enum);
    if (uacpi_unlikely(reg == NULL))
        return UACPI_STATUS_INVALID_ARGUMENT;

    return do_write_register(reg, in_value);
}

uacpi_status uacpi_write_registers(
    enum uacpi_register reg_enum, u64 in_value0, u64 in_value1
)
{
    uacpi_status ret;
    struct register_spec *reg;

    reg = get_reg(reg_enum);
    if (uacpi_unlikely(reg == NULL))
        return UACPI_STATUS_INVALID_ARGUMENT;

    ret = write_one(reg->kind, reg->accessor0, reg->access_width, in_value0);
    if (uacpi_unlikely_error(ret))
        return ret;

    if (reg->accessor1)
        ret = write_one(reg->kind, reg->accessor1, reg->access_width, in_value1);

    return ret;
}

struct register_field {
    u8 reg;
    u8 offset;
    u16 mask;
};

static struct register_field fields[UACPI_REGISTER_FIELD_MAX + 1] = {
    [UACPI_REGISTER_FIELD_TMR_STS] = {
        .reg = UACPI_REGISTER_PM1_STS,
        .offset = ACPI_PM1_STS_TMR_STS_IDX,
        .mask = ACPI_PM1_STS_TMR_STS_MASK,
    },
    [UACPI_REGISTER_FIELD_BM_STS] = {
        .reg = UACPI_REGISTER_PM1_STS,
        .offset = ACPI_PM1_STS_BM_STS_IDX,
        .mask = ACPI_PM1_STS_BM_STS_MASK,
    },
    [UACPI_REGISTER_FIELD_GBL_STS] = {
        .reg = UACPI_REGISTER_PM1_STS,
        .offset = ACPI_PM1_STS_GBL_STS_IDX,
        .mask = ACPI_PM1_STS_GBL_STS_MASK,
    },
    [UACPI_REGISTER_FIELD_PWRBTN_STS] = {
        .reg = UACPI_REGISTER_PM1_STS,
        .offset = ACPI_PM1_STS_PWRBTN_STS_IDX,
        .mask = ACPI_PM1_STS_PWRBTN_STS_MASK,
    },
    [UACPI_REGISTER_FIELD_SLPBTN_STS] = {
        .reg = UACPI_REGISTER_PM1_STS,
        .offset = ACPI_PM1_STS_SLPBTN_STS_IDX,
        .mask = ACPI_PM1_STS_SLPBTN_STS_MASK,
    },
    [UACPI_REGISTER_FIELD_RTC_STS] = {
        .reg = UACPI_REGISTER_PM1_STS,
        .offset = ACPI_PM1_STS_RTC_STS_IDX,
        .mask = ACPI_PM1_STS_RTC_STS_MASK,
    },
    [UACPI_REGISTER_FIELD_HWR_WAK_STS] = {
        .reg = UACPI_REGISTER_SLP_STS,
        .offset = ACPI_SLP_STS_WAK_STS_IDX,
        .mask = ACPI_SLP_STS_WAK_STS_MASK,
    },
    [UACPI_REGISTER_FIELD_WAK_STS] = {
        .reg = UACPI_REGISTER_PM1_STS,
        .offset = ACPI_PM1_STS_WAKE_STS_IDX,
        .mask = ACPI_PM1_STS_WAKE_STS_MASK,
    },
    [UACPI_REGISTER_FIELD_PCIEX_WAKE_STS] = {
        .reg = UACPI_REGISTER_PM1_STS,
        .offset = ACPI_PM1_STS_PCIEXP_WAKE_STS_IDX,
        .mask = ACPI_PM1_STS_PCIEXP_WAKE_STS_MASK,
    },
    [UACPI_REGISTER_FIELD_TMR_EN] = {
        .reg = UACPI_REGISTER_PM1_EN,
        .offset = ACPI_PM1_EN_TMR_EN_IDX,
        .mask = ACPI_PM1_EN_TMR_EN_MASK,
    },
    [UACPI_REGISTER_FIELD_GBL_EN] = {
        .reg = UACPI_REGISTER_PM1_EN,
        .offset = ACPI_PM1_EN_GBL_EN_IDX,
        .mask = ACPI_PM1_EN_GBL_EN_MASK,
    },
    [UACPI_REGISTER_FIELD_PWRBTN_EN] = {
        .reg = UACPI_REGISTER_PM1_EN,
        .offset = ACPI_PM1_EN_PWRBTN_EN_IDX,
        .mask = ACPI_PM1_EN_PWRBTN_EN_MASK,
    },
    [UACPI_REGISTER_FIELD_SLPBTN_EN] = {
        .reg = UACPI_REGISTER_PM1_EN,
        .offset = ACPI_PM1_EN_SLPBTN_EN_IDX,
        .mask = ACPI_PM1_EN_SLPBTN_EN_MASK,
    },
    [UACPI_REGISTER_FIELD_RTC_EN] = {
        .reg = UACPI_REGISTER_PM1_EN,
        .offset = ACPI_PM1_EN_RTC_EN_IDX,
        .mask = ACPI_PM1_EN_RTC_EN_MASK,
    },
    [UACPI_REGISTER_FIELD_PCIEXP_WAKE_DIS] = {
        .reg = UACPI_REGISTER_PM1_EN,
        .offset = ACPI_PM1_EN_PCIEXP_WAKE_DIS_IDX,
        .mask = ACPI_PM1_EN_PCIEXP_WAKE_DIS_MASK,
    },
    [UACPI_REGISTER_FIELD_SCI_EN] = {
        .reg = UACPI_REGISTER_PM1_CNT,
        .offset = ACPI_PM1_CNT_SCI_EN_IDX,
        .mask = ACPI_PM1_CNT_SCI_EN_MASK,
    },
    [UACPI_REGISTER_FIELD_BM_RLD] = {
        .reg = UACPI_REGISTER_PM1_CNT,
        .offset = ACPI_PM1_CNT_BM_RLD_IDX,
        .mask = ACPI_PM1_CNT_BM_RLD_MASK,
    },
    [UACPI_REGISTER_FIELD_GBL_RLS] = {
        .reg = UACPI_REGISTER_PM1_CNT,
        .offset = ACPI_PM1_CNT_GBL_RLS_IDX,
        .mask = ACPI_PM1_CNT_GBL_RLS_MASK,
    },
    [UACPI_REGISTER_FIELD_SLP_TYP] = {
        .reg = UACPI_REGISTER_PM1_CNT,
        .offset = ACPI_PM1_CNT_SLP_TYP_IDX,
        .mask = ACPI_PM1_CNT_SLP_TYP_MASK,
    },
    [UACPI_REGISTER_FIELD_SLP_EN] = {
        .reg = UACPI_REGISTER_PM1_CNT,
        .offset = ACPI_PM1_CNT_SLP_EN_IDX,
        .mask = ACPI_PM1_CNT_SLP_EN_MASK,
    },
    [UACPI_REGISTER_FIELD_HWR_SLP_TYP] = {
        .reg = UACPI_REGISTER_SLP_CNT,
        .offset = ACPI_SLP_CNT_SLP_TYP_IDX,
        .mask = ACPI_SLP_CNT_SLP_TYP_MASK,
    },
    [UACPI_REGISTER_FIELD_HWR_SLP_EN] = {
        .reg = UACPI_REGISTER_SLP_CNT,
        .offset = ACPI_SLP_CNT_SLP_EN_IDX,
        .mask = ACPI_SLP_CNT_SLP_EN_MASK,
    },
    [UACPI_REGISTER_FIELD_ARB_DIS] = {
        .reg = UACPI_REGISTER_PM2_CNT,
        .offset = ACPI_PM2_CNT_ARB_DIS_IDX,
        .mask = ACPI_PM2_CNT_ARB_DIS_MASK,
    },
};

uacpi_status uacpi_read_register_field(
    enum uacpi_register_field field_enum, u64 *out_value
)
{
    uacpi_status ret;
    u8 field_idx = field_enum;
    struct register_field *field;
    struct register_spec *reg;

    if (uacpi_unlikely(field_idx > UACPI_REGISTER_FIELD_MAX))
        return UACPI_STATUS_INVALID_ARGUMENT;

    field = &fields[field_idx];
    reg = &registers[field->reg];

    ret = do_read_register(reg, out_value);
    if (uacpi_unlikely_error(ret))
        return ret;

    *out_value = (*out_value & field->mask) >> field->offset;
    return UACPI_STATUS_OK;
}

uacpi_status uacpi_write_register_field(
    enum uacpi_register_field field_enum, u64 in_value
)
{
    uacpi_status ret;
    u8 field_idx = field_enum;
    struct register_field *field;
    struct register_spec *reg;
    u64 data;

    if (uacpi_unlikely(field_idx > UACPI_REGISTER_FIELD_MAX))
        return UACPI_STATUS_INVALID_ARGUMENT;

    field = &fields[field_idx];
    reg = &registers[field->reg];

    in_value = (in_value << field->offset) & field->mask;

    if (reg->kind == REGISTER_ACCESS_KIND_WRITE_TO_CLEAR) {
        if (in_value == 0)
            return UACPI_STATUS_OK;

        return do_write_register(reg, in_value);
    }

    ret = do_read_register(reg, &data);
    if (uacpi_unlikely_error(ret))
        return ret;

    data &= ~field->mask;
    data |= in_value;

    return do_write_register(reg, data);
}

