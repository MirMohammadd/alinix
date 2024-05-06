#ifndef __ALINIX_KERNEL_DRIVERS_E_1000_NVM_H
#define __ALINIX_KERNEL_DRIVERS_E_1000_NVM_H

#include <alinix/types.h>
#include "hw.h"


void e1000_init_nvm_ops_generic(struct e1000_hw *hw);
sint32_t  e1000e_acquire_nvm(struct e1000_hw *hw);

sint32_t  e1000e_poll_eerd_eewr_done(struct e1000_hw *hw, int ee_reg);
sint32_t  e1000_read_mac_addr_generic(struct e1000_hw *hw);
sint32_t  e1000_read_pba_string_generic(struct e1000_hw *hw, u8 *pba_num,
                                   u32 pba_num_size);
sint32_t  e1000e_read_nvm_eerd(struct e1000_hw *hw, u16 offset, u16 words,
                         u16 *data);
sint32_t  e1000e_valid_led_default(struct e1000_hw *hw, u16 *data);
sint32_t  e1000e_validate_nvm_checksum_generic(struct e1000_hw *hw);
sint32_t  e1000e_write_nvm_spi(struct e1000_hw *hw, u16 offset, u16 words,
                         u16 *data);
sint32_t  e1000e_update_nvm_checksum_generic(struct e1000_hw *hw);
void e1000e_release_nvm(struct e1000_hw *hw);

#define E1000_STM_OPCODE  0xDB00


#endif /*__ALINIX_KERNEL_DRIVERS_E_1000_NVM_H*/