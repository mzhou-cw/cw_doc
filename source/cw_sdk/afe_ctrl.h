#include <stdint.h>
#include <stdbool.h>
#include "reg_afe_type.h"
#include "HAL_def.h"
#ifndef _AFE_CTRL_H
#define _AFE_CTRL_H

#define AFE_IO_GROUP_LVIO 0
#define AFE_IO_GROUP_HVIO 1

#define LVIO1 ((AFE_IO_GROUP_LVIO) << 4 | 0)
#define LVIO2 ((AFE_IO_GROUP_LVIO) << 4 | 1)
#define LVIO3 ((AFE_IO_GROUP_LVIO) << 4 | 2)
#define LVIO4 ((AFE_IO_GROUP_LVIO) << 4 | 3)
#define LVIO5 ((AFE_IO_GROUP_LVIO) << 4 | 4)
#define LVIO6 ((AFE_IO_GROUP_LVIO) << 4 | 5)
#define LVIO7 ((AFE_IO_GROUP_LVIO) << 4 | 6)

#define HVIO1 ((AFE_IO_GROUP_HVIO) << 4 | 0)
#define HVIO2 ((AFE_IO_GROUP_HVIO) << 4 | 1)
#define HVIO3 ((AFE_IO_GROUP_HVIO) << 4 | 2)

#define INPUT_EN_POS REG_AFE_LVIO1_IN_EN_POS
#define INPUT_EN_MASK REG_AFE_LVIO1_IN_EN_MASK
#define OUTPUT_EN_POS REG_AFE_LVIO1_OUT_EN_POS
#define OUTPUT_EN_MASK REG_AFE_LVIO1_OUT_EN_MASK
#define OUTPUT_DATA_POS REG_AFE_LVIO1_OUT_DATA_POS
#define OUTPUT_DATA_MASK REG_AFE_LVIO1_OUT_DATA_MASK
#define LVIO_PU_POS REG_AFE_LVIO1_PU_POS 
#define LVIO_PU_MASK REG_AFE_LVIO1_PU_MASK
#define LVIO_OUT_TYPE_POS REG_AFE_LVIO1_OUT_TYPE_POS
#define LVIO_OUT_TYPE_MASK REG_AFE_LVIO1_OUT_TYPE_MASK
#define LVIO_BIAS_POS REG_AFE_LVIO1_ENBIAS_POS
#define LVIO_BIAS_MASK REG_AFE_LVIO1_ENBIAS_MASK

/**@brief IO pull type */
typedef enum
{
    IO_PULL_DOWN = 0,
    IO_PULL_UP = 0x1,
}io_pull_type_t;

/**@brief IO out type */
typedef enum
{
    IO_OUT_OPEN_DRAIN = 0,
    IO_OUT_PUSH_PULL = 0x1,
}io_out_type_t;

/**@brief IO trigger */
enum
{
    IO_TRIGGER_EDGE = 0,
    IO_TRIGGER_LEVEL = 0x1,
};

/**@brief IO level/edge */
enum
{
    LOW_LEVEL_FALLING_EDGE = 0,
    HIGH_LEVEL_RISING_EDGE = 0x1,
};

typedef struct 
{
    uint8_t num : 4, /*!< io pin */
            group : 4;  /*!< io group */
}afe_io_pin_t;

typedef struct
{
    uint8_t pol : 1, /*!< high/low level, rising/falling edge */
            lev : 1, /*!< level or edge trigger */
            int_en : 1, /*!< interrupt enable */
            rsvd : 5;
}afe_io_int_cfg_t;


#define AFE_FIELD_WR(addr, field, val) afe_field_wr(addr, field##_POS, field##_MASK, val)
#define AFE_FIELD_RD(addr, field, val_ptr) afe_field_rd(addr, field##_POS, field##_MASK, val_ptr)
#define AFE_REG_WR(addr, val) afe_reg_wr(addr, val)
#define AFE_reg_RD(addr, val_ptr) afe_reg_rd(addr, val_ptr)

bool afe_field_wr(uint8_t addr, uint8_t pos, uint8_t mask, uint8_t val);
bool afe_field_rd(uint8_t addr, uint8_t pos, uint8_t mask, uint8_t *val_ptr);
bool afe_reg_wr(uint8_t addr, uint8_t val);
bool afe_reg_rd(uint8_t addr, uint8_t *val_ptr);

void afe_ctrl_init(void);
bool afe_io_cfg_output(uint8_t pin);
bool afe_io_cfg_input(uint8_t pin);
bool afe_io_cfg_disable(uint8_t pin);
bool afe_io_write_pin(uint8_t pin, uint8_t val);
bool afe_io_set_pin(uint8_t pin);
bool afe_io_clr_pin(uint8_t pin);
bool afe_io_toggle_pin(uint8_t pin);
bool afe_io_get_output_data(uint8_t pin, uint8_t *val_ptr);
bool afe_io_read_input_pin(uint8_t pin, uint8_t *val_ptr);
bool afe_lvio_pull_write(uint8_t pin, io_pull_type_t pull);
bool afe_lvio_pull_read(uint8_t pin, io_pull_type_t *pull_ptr);
bool afe_lvio_out_type_write(uint8_t pin, io_out_type_t type);
bool afe_lvio_out_type_read(uint8_t pin, io_out_type_t *type_ptr);
bool afe_lvio_bias_write(uint8_t pin, bool en);
bool afe_lvio_bias_read(uint8_t pin, bool *en_ptr);
bool afe_io_int_cfg_set(uint8_t pin, afe_io_int_cfg_t cfg);
bool afe_io_int_cfg_get(uint8_t pin, afe_io_int_cfg_t *cfg_ptr);
bool afe_io_int_enable(uint8_t pin, bool en);

#endif
