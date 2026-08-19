/*
 * Ejercicio 9 - Ejercicios calificables
 *
 * Enunciado:
 * Simular un detector de secuencia para una cerradura electronica (simulacion
 * de una maquina de estados). El programa debe recibir una lista de bits uno
 * por uno que ingresa el usuario. Si detecta que los ultimos bits ingresados
 * tienen la secuencia especifica 1011, el mensaje debe ser "Cerradura abierta".
 * Si el bit ingresado rompe la secuencia, no debe mostrar nada.
 *
 * Nota: segun las indicaciones generales, no se debe usar scanf, por lo cual
 * los bits que "ingresa el usuario" se definen en la variable BITS y se
 * procesan uno por uno.
 *
 * Maquina de estados (deteccion de 1011 con solapamiento):
 *
 *   S0 --1--> S1 --0--> S2 --1--> S3 --1--> ABIERTA
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

#define S0  0   /* no se ha detectado nada    */
#define S1  1   /* se detecto 1               */
#define S2  2   /* se detecto 10              */
#define S3  3   /* se detecto 101             */

int main(void)
{
    int BITS[] = {0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1};
    int CANTIDAD_BITS = (int) (sizeof(BITS) / sizeof(BITS[0]));

    int estado = S0;
    int bit;
    int i;

    for (i = 0; i < CANTIDAD_BITS; i++) {
        bit = BITS[i];

        /* Solo se aceptan bits validos (0 o 1). */
        if (bit != 0 && bit != 1) {
            printf("El tipo de dato no es el correcto, el programa no se puede ejecutar.\n");
            return 0;
        }

        switch (estado) {
            case S0:
                estado = (bit == 1) ? S1 : S0;
                break;

            case S1:
                estado = (bit == 0) ? S2 : S1;
                break;

            case S2:
                estado = (bit == 1) ? S3 : S0;
                break;

            case S3:
                if (bit == 1) {
                    printf("Cerradura abierta\n");
                    estado = S1;   /* permite solapamiento: el 1 final inicia 1... */
                } else {
                    estado = S2;   /* ...10 */
                }
                break;

            default:
                estado = S0;
                break;
        }
    }

    return 0;
}
