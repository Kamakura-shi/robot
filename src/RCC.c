/*
 * RCC.c
 *
 *  Created on: Sep 24, 2025
 *      Author: aq81820@ens.ad.etsmtl.ca
 */
#include "RCC.h"

void Configure_RCC_Clock(void){
	/*Il faut ajouter le code pour l'initialisation du RCC*/
	RCC->CR = (uint32_t) RCC_CR_HSION; // HSEON = 0, HSEBYP = 1, HSION = 1
	RCC->CFGR = (uint32_t) RCC_CFGR_PLLMUL6 | RCC_CFGR_SW_1 | RCC_CFGR_PLLSRC_0  ; // PLLCLK = (HSE(8MHz))*(6) = 48MHz
	// SYSCLK = PLLCLK
	// MCO = HSE
	RCC->CR |= RCC_CR_PLLON; // Active le PLL
	while (!(RCC->CR & RCC_CR_PLLRDY));// Attend que le PLL soit prêt
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN; // Active l'horloge du port A
	GPIOA->MODER |= GPIO_MODER_MODER8_1; // Mettre MODE en AF pour PA8
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR8_0 || // Vitesse MAX pour PC0
	GPIO_OSPEEDR_OSPEEDR8_1;

	SystemCoreClockUpdate();	// Met � jour SystemCoreClock avec la config du RCC
    SysTick_Config(SystemCoreClock/MillisecondsIT);	// Configure le SysTick � 1 ms
}
