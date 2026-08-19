/*
 * Ejercicio 6 - Ejercicios calificables
 *
 * Enunciado:
 * Leer un numero entero en la variable VALOR. Utilizar operadores de bits
 * (bitwise) para determinar si el numero es par o impar (verificando el bit
 * menos significativo) y mostrar el resultado. No esta permitido usar el
 * operador de modulo (%).
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

int main(void)
{
    int VALOR = 27;

    int bit_menos_significativo;

    /* La mascara 0x01 deja unicamente el bit 0 (LSB):
     *   LSB = 0 -> el numero es par
     *   LSB = 1 -> el numero es impar */
    bit_menos_significativo = VALOR & 0x01;

    if (bit_menos_significativo == 0) {
        printf("{'Valor' : %d, 'LSB' : %d, 'Resultado' : 'Par'}\n",
               VALOR, bit_menos_significativo);
    } else {
        printf("{'Valor' : %d, 'LSB' : %d, 'Resultado' : 'Impar'}\n",
               VALOR, bit_menos_significativo);
    }

    return 0;
}
