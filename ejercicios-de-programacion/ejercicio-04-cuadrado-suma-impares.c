/*
 * Ejercicio 4 - Ejercicios calificables
 *
 * Enunciado:
 * Se puede calcular el cuadrado de un numero NUMERO al sumar los primeros
 * NUMERO numeros impares. Con esta logica, el cuadrado del numero 7 es la
 * sumatoria de los primeros 7 numeros impares, es decir
 * 1+3+5+7+9+11+13 = 49. Crear un programa que pida al usuario un numero y se
 * almacene en la variable NUMERO y luego imprima la suma de todos los numeros
 * impares y su resultado.
 *
 * Nota: segun las indicaciones generales, no se debe usar scanf, por lo cual
 * NUMERO se declara como variable dentro del programa.
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
    int NUMERO = 7;

    int i;
    int impar;
    long RESULTADO = 0;

    /* Solo tiene sentido para enteros positivos. */
    if (NUMERO <= 0) {
        return 0;
    }

    for (i = 0; i < NUMERO; i++) {
        impar = 2 * i + 1;
        RESULTADO += impar;

        if (i == 0) {
            printf("%d", impar);
        } else {
            printf(" + %d", impar);
        }
    }

    printf(" = %ld\n", RESULTADO);
    printf("{'Numero' : %d, 'Cuadrado' : %ld}\n", NUMERO, RESULTADO);

    return 0;
}
