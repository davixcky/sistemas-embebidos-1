/*
 * Ejercicio 10 - Ejercicios calificables
 *
 * Enunciado:
 * Los sensores analogicos suelen presentar ruido. Definir una lista de 10
 * lecturas llamada LECTURAS_ADC. Crear un programa que calcule una nueva lista
 * donde cada elemento sea el promedio de la lectura actual y las dos anteriores
 * (esto se le conoce como filtro de media movil). Para la primera posicion,
 * segunda y ultima posicion de la nueva lista, dejar en 0.
 *
 * Integrantes:
 *   - David Orozco
 *   - Jose Torres
 *   - Leo Rojas
 *
 * Compilador usado: OnlineGDB (https://www.onlinegdb.com/online_c_compiler)
 *                   GCC en modo C (C11)
 */

#include <stdio.h>

#define CANTIDAD_LECTURAS 10

int main(void)
{
    int LECTURAS_ADC[CANTIDAD_LECTURAS] = {512, 530, 498, 505, 640, 610, 590, 300, 310, 305};

    double LECTURAS_FILTRADAS[CANTIDAD_LECTURAS];
    int i;

    /* Todas las posiciones inician en 0; asi las posiciones 0, 1 y la ultima
     * quedan en 0 tal como lo pide el enunciado. */
    for (i = 0; i < CANTIDAD_LECTURAS; i++) {
        LECTURAS_FILTRADAS[i] = 0.0;
    }

    /* Media movil de 3 muestras: lectura actual y las dos anteriores. */
    for (i = 2; i < CANTIDAD_LECTURAS - 1; i++) {
        LECTURAS_FILTRADAS[i] = (LECTURAS_ADC[i] + LECTURAS_ADC[i - 1] + LECTURAS_ADC[i - 2]) / 3.0;
    }

    printf("{'Lecturas ADC' : [");
    for (i = 0; i < CANTIDAD_LECTURAS; i++) {
        printf("%d", LECTURAS_ADC[i]);
        if (i < CANTIDAD_LECTURAS - 1) {
            printf(", ");
        }
    }
    printf("],\n");

    printf(" 'Lecturas filtradas' : [");
    for (i = 0; i < CANTIDAD_LECTURAS; i++) {
        printf("%.2f", LECTURAS_FILTRADAS[i]);
        if (i < CANTIDAD_LECTURAS - 1) {
            printf(", ");
        }
    }
    printf("]}\n");

    return 0;
}
