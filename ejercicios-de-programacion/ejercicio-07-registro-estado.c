/*
 * Ejercicio 7 - Ejercicios calificables
 *
 * Enunciado:
 * En sistemas embebidos, los registros suelen empaquetar varios estados. Leer
 * una variable de 8 bits llamada REGISTRO_ESTADO. El programa debe extraer y
 * mostrar por separado el valor de los 4 bits menos significativos (nibble
 * inferior) y el estado (0 o 1) del bit numero 5. Usar exclusivamente
 * operadores de bits (&, >>).
 *
 * Nota: se toma el bit numero 5 como el de indice 5 (b7 b6 b5 b4 b3 b2 b1 b0),
 * es decir el sexto bit contando desde el bit 0.
 *
 * Integrantes:
 *   - Integrante 1
 *   - Integrante 2
 *   - Integrante 3
 *
 * Compilador usado: OnlineGDB (https://www.onlinegdb.com/online_c_compiler)
 *                   GCC en modo C (C11)
 */

#include <stdio.h>

int main(void)
{
    unsigned char REGISTRO_ESTADO = 0xAD;   /* 1010 1101 */

    unsigned char NIBBLE_INFERIOR;
    unsigned char BIT_5;

    /* Nibble inferior: se enmascaran los 4 bits menos significativos. */
    NIBBLE_INFERIOR = REGISTRO_ESTADO & 0x0F;

    /* Bit 5: se desplaza 5 posiciones a la derecha y se enmascara con 1. */
    BIT_5 = (REGISTRO_ESTADO >> 5) & 0x01;

    printf("{'Registro' : 0x%02X, 'Nibble inferior' : %u, 'Bit 5' : %u}\n",
           REGISTRO_ESTADO, NIBBLE_INFERIOR, BIT_5);

    return 0;
}
