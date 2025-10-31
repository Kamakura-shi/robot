#include "adc.h"

int accumulateur_gauche = 0;
int accumulateur_droite = 0;
uint32_t count_gauche = 0;
uint32_t count_droite = 0;
float posMin_moteur_G = 0;
float posMax_moteur_G = 0;
float negMin_moteur_G = 0;
float negMax_moteur_G = 0;
float posMin_moteur_D = 0;
float posMax_moteur_D = 0;
float negMin_moteur_D = 0;
float negMax_moteur_D = 0;

float borne(float x, float inf, float sup) {
    if (x < inf) {
        return inf;
    } else if (x > sup) {
        return sup;
    } else {
        return x;
    }
}

void ADC_Somme(float* vitesse_moteur_D, float* vitesse_moteur_G) {
    uint32_t tmp_moteur_G, tmp_moteur_D;
    float points_moteur_G, points_moteur_D;
    __set_PRIMASK(1);
    points_moteur_G = accumulateur_gauche;
    points_moteur_D = accumulateur_droite;

    tmp_moteur_G = count_gauche;
    tmp_moteur_D = count_droite;
    accumulateur_gauche = 0;
    accumulateur_droite = 0;
    count_gauche = 0;
    count_droite = 0;

    __set_PRIMASK(0);
    float moyenne_moteur_G = points_moteur_G / tmp_moteur_G;
    float moyenne_moteur_D = points_moteur_D / tmp_moteur_D;
    /* Moteur gauche */
    if (moyenne_moteur_G <= 0) {
        moyenne_moteur_G = borne(moyenne_moteur_G, negMax_moteur_G, negMin_moteur_G);
        *vitesse_moteur_G = -(moyenne_moteur_G - negMin_moteur_G) / (negMax_moteur_G - negMin_moteur_G);
    }
    else if (moyenne_moteur_G > 0) {
        moyenne_moteur_G = borne(moyenne_moteur_G, posMin_moteur_G, posMax_moteur_G);
        *vitesse_moteur_G = (moyenne_moteur_G - posMin_moteur_G) / (posMax_moteur_G - posMin_moteur_G);
    } 
    
    /* Moteur droit */
    if (moyenne_moteur_D <= 0) {
        moyenne_moteur_D = borne(moyenne_moteur_D, negMax_moteur_D, negMin_moteur_D);
        *vitesse_moteur_D = -(moyenne_moteur_D - negMin_moteur_D) / (negMax_moteur_D - negMin_moteur_D);
    }
    else if (moyenne_moteur_D > 0) {
        moyenne_moteur_D = borne(moyenne_moteur_D, posMin_moteur_D, posMax_moteur_D);
        *vitesse_moteur_D = (moyenne_moteur_D - posMin_moteur_D) / (posMax_moteur_D - posMin_moteur_D);
    }
}