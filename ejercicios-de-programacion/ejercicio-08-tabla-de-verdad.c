/*
 * Ejercicio 8 - Ejercicios calificables
 *
 * Enunciado:
 * Crear una funcion que reciba tres variables booleanas (A, B, C) y retorne el
 * resultado de la siguiente expresion logica:
 *
 *      F = (A . B) + not(C)
 *
 * El resultado debe mostrarse como una pequena tabla de verdad en la consola
 * para todas las combinaciones posibles de las entradas.
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
#include <stdbool.h>

/* F = (A AND B) OR (NOT C) */
bool funcion_logica(bool A, bool B, bool C)
{
    return (A && B) || (!C);
}

int main(void)
{
    bool A, B, C, F;
    int a, b, c;

    printf("+---+---+---+---+\n");
    printf("| A | B | C | F |\n");
    printf("+---+---+---+---+\n");

    for (a = 0; a <= 1; a++) {
        for (b = 0; b <= 1; b++) {
            for (c = 0; c <= 1; c++) {
                A = (bool) a;
                B = (bool) b;
                C = (bool) c;

                F = funcion_logica(A, B, C);

                printf("| %d | %d | %d | %d |\n", a, b, c, (int) F);
            }
        }
    }

    printf("+---+---+---+---+\n");

    return 0;
}
