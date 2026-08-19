/*
 * Ejercicio 3 - Ejercicios calificables
 *
 * Enunciado:
 * Crear un programa que pida al usuario un numero entero positivo y
 * almacenarlo en la variable NUMERO. Usando NUMERO como limite, aplicar la
 * Criba de Eratostenes e imprimir en pantalla todos los numeros menores a
 * NUMERO que son primos.
 *
 * Nota: segun las indicaciones generales de la seccion "Ejercicios de
 * programacion", en ningun ejercicio se le debe pedir al usuario que ingrese un
 * valor por medio de scanf o similar, por lo cual NUMERO se declara como
 * variable dentro del programa.
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

#define LIMITE_MAXIMO 100000

int main(void)
{
    int NUMERO = 50;

    int criba[LIMITE_MAXIMO];   /* criba[i] = 1 -> i es primo */
    int i, j;
    int primeros;

    /* El limite debe ser un entero positivo y manejable por el arreglo. */
    if (NUMERO < 2 || NUMERO > LIMITE_MAXIMO) {
        return 0;
    }

    for (i = 0; i < NUMERO; i++) {
        criba[i] = 1;
    }
    criba[0] = 0;
    if (NUMERO > 1) {
        criba[1] = 0;
    }

    /* Criba de Eratostenes: se marcan los multiplos de cada primo. */
    for (i = 2; i * i < NUMERO; i++) {
        if (criba[i] == 1) {
            for (j = i * i; j < NUMERO; j += i) {
                criba[j] = 0;
            }
        }
    }

    printf("{'Numero' : %d, 'Primos menores a NUMERO' : [", NUMERO);

    primeros = 1;
    for (i = 2; i < NUMERO; i++) {
        if (criba[i] == 1) {
            if (primeros == 1) {
                printf("%d", i);
                primeros = 0;
            } else {
                printf(", %d", i);
            }
        }
    }

    printf("]}\n");

    return 0;
}
