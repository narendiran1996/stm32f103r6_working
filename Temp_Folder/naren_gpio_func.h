#ifndef __NAREN_GPIO_FUNC_H
#define __NAREN_GPIO_FUNC_H


enum PORTS_MINE {A=0, B=1, C=2, D=3, E=4, F=5, G=66};
enum CONFIGURATION_MODE{GPIO_OUTPUT_PUSH_PULL, GPIO_OUTPUT_OPEN_DRAIN, AFIO_OUTPUT_PUSH_PULL, AFIO_OUTPUT_OPEN_DRAIN, ANALOG_IN, FLOATING_IN, PD_IN, PU_IN};




void GPIOA_config(unsigned char pin_,enum CONFIGURATION_MODE config_);
void GPIOB_config(unsigned char pin_,enum CONFIGURATION_MODE config_);
void GPIOB_config(unsigned char pin_,enum CONFIGURATION_MODE config_);
void GPIO_config(enum PORTS_MINE port_, unsigned char pin_, enum CONFIGURATION_MODE config_);

unsigned char GPIO_read_out(enum PORTS_MINE port_, unsigned char pin_, unsigned char in0_out1);


#endif /* __NAREN_GPIO_FUNC_H */
