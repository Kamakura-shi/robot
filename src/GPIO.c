/****************************Proto 1********************************************
 Author : Hani Ouali, Alexandre Boldron & Léo Alagheband
 Date   : 09/17/2025
 Description :
 GPIO : -Registre d’activation des horloges de périphériques : RCC-> AHBENR [32 AHBENR [32:0] (32 bits)
        -Registre de mode du port E/S : GPIOA-> MODER [32 MODER [32:0] (32 bits)
        -Registre de type de sortie du port E/S : GPIOA-> OTYPER [32 OTYPER [32:0] (32 bits)
        -Registre de mode Pull-up/Pull-down du port E/S : GPIOA-> PUPDR [32 PUPDR [32:0]
        -Registre de vitesse du port E/S : GPIOA-> OSPEEDR [32 OSPEEDR [32:0] (32 bits)
        -Registre « LOW » de fonctions alternatives du port E/S : GPIOA-> AFRL[32 AFRL[32:0] (32 bits)
*/

#include "GPIO.h"

void Configure_GPIO(void) {
 RCC->AHBENR |= RCC_AHBENR_GPIOCEN; // Active l'horloge du port C
 GPIOC->MODER |= GPIO_MODER_MODER0_0 | // Mettre MODE en sortie pour PC0 .. PC3
 GPIO_MODER_MODER1_0 |
 GPIO_MODER_MODER2_0 |
 GPIO_MODER_MODER3_0;
 GPIOC->OTYPER &= ~(GPIO_OTYPER_OT_0 | // Sortie Push-Pull pour PC0
 GPIO_OTYPER_OT_1 |
 GPIO_OTYPER_OT_2 |
 GPIO_OTYPER_OT_3);
 GPIOC->PUPDR &= ~(GPIO_PUPDR_PUPDR0 | // Pas de resistance de Pull
 GPIO_PUPDR_PUPDR1 |
 GPIO_PUPDR_PUPDR2 |
 GPIO_PUPDR_PUPDR3);
 GPIOC->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEEDR0 | // Vitesse basse pour PC0
 GPIO_OSPEEDR_OSPEEDR1 |
 GPIO_OSPEEDR_OSPEEDR2 |
 GPIO_OSPEEDR_OSPEEDR3);
 GPIOC->ODR = 0; //Mettre la sortie à 0
}
