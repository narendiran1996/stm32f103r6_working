#ifndef __NAREN_LCD_FUNC_H
#define __NAREN_LCD_FUNC_H

// connect PC0 TO RS
// connect PC1 TO EN
// connect PC[5:2] TO D[7:4]
#define set_En GPIOC->BSRR = (1<<1);
#define clear_En GPIOC->BRR = (1<<1);

#define set_RS GPIOC->BSRR = (1<<0);
#define clear_RS GPIOC->BRR = (1<<0);

#define set_MSB(val_) \
						GPIOC->BRR = 0b111100;\
						GPIOC->BSRR = ((val_ & 0xF0)>>2);
#define set_LSB(val_) \
						GPIOC->BRR = 0b111100;\
						GPIOC->BSRR = ((val_ & 0x0F)<<2);


void custom_delay(unsigned char del_val);
void port_init_lcd(void);
void lcd_send_cmd(unsigned char cmd_);
void lcd_send_data(unsigned char data_);
void lcd_clear(void);
void lcd_home(void);
void initialization_lcd(void);
void lcd_print_left(void);
void lcd_print_right(void);
void lcd_shift_left(void);
void lcd_shift_right(void);
void lcd_display_off(void);
void lcd_display_on_cursor_off_blink_off(void);
void lcd_display_on_cursor_on_blink_off(void);
void lcd_display_on_cursor_off_blink_on(void);
void lcd_display_on_cursor_on_blink_on(void);
void lcd_cursor_leftShift(void);
void lcd_cursor_rightShift(void);
void lcd_display_leftShift(void);
void lcd_display_rightShift(void);
void lcd_send_string(char *c_string);
void lcd_set_cursor(unsigned char  r,unsigned char  c);
void send_string_l(unsigned char  *c_string,unsigned char  len);
void lcd_init(void);
void lcd_print_num(int num, int base);
						
#endif
