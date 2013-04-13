#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

const uint16_t LEDS = GPIO_Pin_1;
const uint16_t LED = GPIO_Pin_1;
const uint16_t USER_BUTTON = GPIO_Pin_0;

void init();
void loop();

void delay();

void initLeds();
void initButton();

uint8_t lastButtonStatus = 0;

int main(void)
{
	init();
    while(1)
    {
    	loop();
    }
}

void init() {
	initLeds();
	initButton();
}

void loop() {
    uint8_t currentButtonStatus = GPIO_ReadInputDataBit(GPIOA, USER_BUTTON);
    if (lastButtonStatus != currentButtonStatus && currentButtonStatus != RESET) {
        GPIO_ToggleBits(GPIOA, LED);
        delay();
    }
    lastButtonStatus = currentButtonStatus;
}

void initLeds() {
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef gpio;
    GPIO_StructInit(&gpio);
    gpio.GPIO_Mode = GPIO_Mode_OUT;
    gpio.GPIO_Pin = LEDS;
    GPIO_Init(GPIOA, &gpio);
}

void initButton() {
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef gpio;
    GPIO_StructInit(&gpio);
    gpio.GPIO_Mode = GPIO_Mode_IN;
    gpio.GPIO_Pin = USER_BUTTON;
    GPIO_Init(GPIOA, &gpio);

    lastButtonStatus = GPIO_ReadInputDataBit(GPIOA, USER_BUTTON);
}

void delay(uint32_t ms) {
    ms *= 3360;
    while(ms--) {
        __NOP();
    }
}
