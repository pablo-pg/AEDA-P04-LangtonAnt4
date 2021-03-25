# La Hormiga de Langton
# Práctica 3 Algoritmos y Estructuras de Datos Avanzadas

## La Hormiga de Langton
La hormiga de Langton es un una máquina de Turing bidimensional con un conjunto de reglas muy sencillo, que sin embargo da lugar a comportamientos emergentes complejos.​ La hormiga de Langton clásica opera sobre una rejilla espacial cuadrada, en que cada celda puede estar en uno de dos estados (blanca o negra, 1 o 0, viva o muerta, etc). Fue inventada por Chris Langton en 1986 y su universalidad se demostró en el año 2000.2​ La idea ha sido generalizada de varias maneras, entre las que se encuentran turmites que agregan más estados, así como reglas para agregar nuevos colores, rejillas tridimensionales3​ o finitas.
<br><br>
## Reglas del comportamiento de la hormiga (modificados)
Al hacer este programa me he orientado usando la versión española:
* La hormiga está en casilla blanca. La marca a negro, gira a la izquierda 45º y avanza una casilla.
* La hormiga está en casilla negra. La marca a blanco, gira a la derecha 45º y avanza una casilla.
<br><br>
## Características y detalles de implementación
Programa hecho en C++ como cuarta práctica para la asignatura Algoritmos y Estructuras de Datos Avanzadas, para la Universidad de La Laguna.

Consiste en recrear La Hormiga de Langton modificada (múltiples hormigas, mundos finitos o infinitos y dos estados).


Este programa tiene un pequeño menú interactivo. Primero le solicitará el tipo de mundo.
* ***0*** : El mundo será infinito, es decir, se expande si llega a bordes.
* ***1*** : El mundo será finito, es decir, si llega a un borde reaparece por el otro.

Después le saldrá un menú con 4 opciones del mundo:
* ***1*** : Ejecuta el programa usando una malla cuadrada. Aparentemente va a ser rectangular, pero tiene el mismo número de celdas horizontal y verticalmente.
Se pedirá el tamaño y el número de pasos a ejecutar.
* ***2*** : Ejecuta el programa usando una malla rectangular. Se pedirá el número de celdas horizontales, luego verticales y finalmente el número de pasos.
* ***3*** : Ejecuta el programa usando una malla que a la vista es cuadrada. Realmente posee el doble de celdas en el eje horizontal que en el vertical.
* ***q*** : Termina el programa.

Por último, le pedirá el número de hormigas que desea ejecutar, así como las posiciones de las mismas y sus direcciones de inicio. Posteriormente. le preguntará si quiere que cada hormiga sea de tipo normal (como se comenta en las reglas del comportamiento) o inverso (es decir, en vez de girar a la izquierda, gira a la derecha y vicecersa).
<br><br>

El estado blanco será representado por " " y el negro por "X".

La hormiga se indicará según su dirección con "A", "I", "B", "D", "R", "Q", "J", "C".

Si la hormiga llega al extremo de la malla, esta se expande.

El programa ejecuta automáticamente los pasos de la hormiga, permitiendo ver en cada momento la malla y se indica las coordenadas de la posición de la hormiga.

Al termitar todos los pasos se finaliza el programa.
<br><br>
## Compilación y ejecución
Para compilar, ejecute `make`.

Para ejecutar tiene dos formas:

`make run` <br>
`./langton_ant`


<br><br>

## Referencias
[1] La Hormiga de Langton (Wikipedia español): https://es.wikipedia.org/wiki/Hormiga_de_Langton

[2] Langton's Ant (Wikipedia inglés): https://en.wikipedia.org/wiki/Langton%27s_ant