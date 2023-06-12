#include "../system/include/cmsis/stm32f4xx.h"


#define PIN 0x0

void EXTI0_IRQHandler(void){
	if((EXTI->PR & EXTI_PR_PR0) != 0x00){
        GPIOD->ODR ^= GPIO_ODR_OD12;
		EXTI->PR |= EXTI_PR_PR0;
	}
}

int main(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    GPIOA->MODER &= ~(0x03 << (2 * PIN));
    GPIOA->PUPDR |= (0x1 << (2 * PIN + 1));

    EXTI->IMR |= (1 << PIN);
    EXTI->FTSR |= (1 << PIN);
    EXTI->PR |= (1 << PIN);

    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	SYSCFG->EXTICR[0] &= ~(0x0F);

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    GPIOD->MODER |= GPIO_MODER_MODER12_0;

    NVIC_EnableIRQ(EXTI0_IRQn);//enabling exti11 at NVIC level

	while(1) {

	}
}


