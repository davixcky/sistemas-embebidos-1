/*
 * Ejercicio 1 - Ejercicios calificables
 *
 * Enunciado:
 * Una variable llamada NUMERO contiene un entero de 4 digitos (mayor o igual a
 * 1000 y menor o igual 9999). En caso que la variable NUMERO este fuera del
 * rango (menor a 1000 o mayor a 9999) entonces no se debe ejecutar el programa.
 * Mostrar en pantalla cual es la unidad de mil, la centena, la decena y la
 * unidad. No usar arreglos, vectores, listas o cualquier otro dato de ese tipo,
 * la variable NUMERO debe ser de tipo entero.
 * Resultado esperado en pantalla:
 * {'Numero' : NUMERO, 'Unidad' : UNIDAD, 'Decena' : DECENA,
 *  'Centena' : CENTENA, 'Unidad de mil' : UNIDAD_DE_MIL}
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
    int NUMERO = 4827;

    int UNIDAD_DE_MIL, CENTENA, DECENA, UNIDAD;

    /* Validacion: si el dato no es un entero de 4 digitos el programa no se
     * puede ejecutar, por lo tanto no se muestra nada en pantalla. */
    if (NUMERO < 1000 || NUMERO > 9999) {
        return 0;
    }

    UNIDAD_DE_MIL = NUMERO / 1000;
    CENTENA       = (NUMERO / 100) % 10;
    DECENA        = (NUMERO / 10) % 10;
    UNIDAD        = NUMERO % 10;

    printf("{'Numero' : %d, 'Unidad' : %d, 'Decena' : %d, 'Centena' : %d, 'Unidad de mil' : %d}\n",
           NUMERO, UNIDAD, DECENA, CENTENA, UNIDAD_DE_MIL);

    return 0;
}
