/****************************Proto 1********************************************
 Author : Hani Ouali, Alexandre Boldron & Léo Alagheband
 Date   : 09/17/2025
 Description :
 GPIO : -User button (PB0 et PB1)
        -Reset button (NRST)
        -LED bleu (PC8) et verte (PC9)
        -Led externe au board (PC0-PC7)
        -I2C1 SDA (PB7) et SCL (PB6)
        -ADC (PA4 et PA5)
        -Bit Direction_FB (PA6 et PA7)
        -Bit Direction Gauche (LSB : PB12 MSB : PB13)
        -Bit Direction Droit (LSB : PB14 MSB : PB15)
        -Bit calibration (PA8)
        -PWM sur timer 3 channel 1 (PB4) et 2 (PB5)
        -USART2 RX (PA2) et TX (PA3)
*/

#include <stdio.h> /*sprintf*/
#include "main.h"

// Fr�quence des Ticks du SysTick (en Hz)
#define MillisecondsIT ((uint32_t) 1000)

void SysTick_Handler(void) {

}


int main(void) {

	// Configure les composantes du robot
	__set_PRIMASK(1);
    Configure_RCC_Clock();
    Configure_GPIO();
    /*Initialisation des p�riph�riques*/

	__set_PRIMASK(0);
	/*volatile uint32_t counter = 0;*/
    while (1) {
    	/*Boucle principale du programme*/
    	/*counter++;*/
        for (int i = 0; i < 80000; i++); // Petit delai
        GPIOC->ODR ++; //Incrémenter ODR
    }
    return (0);
}

/*End of file*/
