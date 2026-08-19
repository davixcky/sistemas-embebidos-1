/*
 * Ejercicio 2 - Ejercicios calificables
 *
 * Enunciado:
 * De un numero entero positivo que esta guardado en una variable llamada
 * NUMERO, mostrar en pantalla su raiz cuadrada usando el metodo de Newton.
 * Para este ejercicio debe realizarse una funcion que acepte el valor de la
 * variable NUMERO y retorne el resultado usando el metodo de Newton, sin usar
 * una libreria que contenga esa funcion.
 * Resultado esperado en pantalla:
 * {'Numero' : NUMERO, 'Raiz cuadrada usando Newton' : RESULTADO}
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

#define TOLERANCIA   0.000001
#define MAX_ITER     100

/*
 * Metodo de Newton-Raphson para f(x) = x^2 - n:
 *
 *      x_(k+1) = x_k - f(x_k)/f'(x_k) = (x_k + n/x_k) / 2
 *
 * No se usa sqrt() ni ninguna funcion de <math.h>.
 */
double raiz_cuadrada_newton(int n)
{
    double x_actual;
    double x_siguiente;
    double error;
    int i;

    if (n == 0) {
        return 0.0;
    }

    x_actual = (double) n;   /* estimacion inicial */

    for (i = 0; i < MAX_ITER; i++) {
        x_siguiente = (x_actual + (double) n / x_actual) / 2.0;

        error = x_siguiente - x_actual;
        if (error < 0) {
            error = -error;
        }

        x_actual = x_siguiente;

        if (error < TOLERANCIA) {
            break;
        }
    }

    return x_actual;
}

int main(void)
{
    int NUMERO = 625;
    double RESULTADO;

    /* El metodo solo esta definido para enteros positivos. Si el dato no es
     * valido el programa no se puede ejecutar. */
    if (NUMERO < 0) {
        return 0;
    }

    RESULTADO = raiz_cuadrada_newton(NUMERO);

    printf("{'Numero' : %d, 'Raiz cuadrada usando Newton' : %.6f}\n",
           NUMERO, RESULTADO);

    return 0;
}
