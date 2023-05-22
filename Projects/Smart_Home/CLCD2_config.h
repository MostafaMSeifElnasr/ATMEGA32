#ifndef CLCD2_CONFIG_H_
#define CLCD2_CONFIG_H_

#define LCD_DATA_PORT       DIO_u8PORTB
#define LCD_CONTROL_PORT    DIO_u8PORTC

#define RS_PIN              DIO_u8PIN7
#define RW_PIN              DIO_u8PIN6
#define EN_PIN              DIO_u8PIN5

#define LCD_MODE            _8_BIT    /* _8_BIT , _4_BIT */


#endif
