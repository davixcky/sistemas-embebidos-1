/*
 * Ejercicio 5 - Ejercicios calificables
 *
 * Enunciado:
 * Preguntar al usuario un numero entero y almacenar en la variable NUMERO.
 * Imprimir el valor de la posicion NUMERO de la secuencia de Fibonacci
 * asumiendo que f0 = 0 y f1 = 1. Verificar que NUMERO debe ser >= 2, en caso
 * contrario, mostrar un mensaje que NUMERO debe cumplir esa condicion.
 *
 * Nota: segun las indicaciones generales, no se debe usar scanf, por lo cual
 * NUMERO se declara como variable dentro del programa.
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
    int NUMERO = 10;

    long f_anterior = 0;   /* f0 */
    long f_actual   = 1;   /* f1 */
    long f_siguiente;
    int i;

    if (NUMERO < 2) {
        printf("NUMERO debe ser mayor o igual a 2. El programa no se puede ejecutar.\n");
        return 0;
    }

    for (i = 2; i <= NUMERO; i++) {
        f_siguiente = f_anterior + f_actual;
        f_anterior  = f_actual;
        f_actual    = f_siguiente;
    }

    printf("{'Numero' : %d, 'Fibonacci' : %ld}\n", NUMERO, f_actual);

    return 0;
}
