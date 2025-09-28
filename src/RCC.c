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

//	RCC->CR (Registre de contrôle de l’horloge ): Ce registre va contrôler l’activation des possibles sources d’horloge afin de générer les bonnes
//	fréquences. Quand une source se fait activer, il faut attendre qu’elle soit prête avant de pouvoir
//	l’utiliser. Pour cela, les drapeaux des sources sont aussi présents dans ce registre pour permettre au
//	programme d’attendre l’initialisation des sources avant de continuer. Pour activer une source, il faut
//	préalablement la configurer à l’aide des autres registres.
//
//	RCC->CFGR (Registre de configuration de l’horloge): Ce registre à deux utilités; déterminer le chemin de l’horloge et configurer les multiplicateurs et
//	diviseurs. Si la source d’horloge n’est pas prête quand elle est sélectionnée, système va continuer de
//	fonctionner sur l’ancien chemin et va transférer de source quand elle sera prêt. 
//
//	Registre d’activation des modules AHB : RCC->AHBENR:
//	Ce registre sert à activer l’horloge des périphériques systèmes du microcontrôleur. Il s’utilise de la
//	même manière. Dans le cadre de ce laboratoire, uniquement les GPIO sont utilisés.
