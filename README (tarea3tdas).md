# Programa resolver el puzzle 8 elegido.

## Descripción

Este programa permite mediante ya sea por una busqueda en profundidad o una busqueda en anchura, obtener la solucion de un puzzle 8 elegido, mostrando para ambas busquedas la cantidad de movimientos asi como los respectivos movimientos ya sea arriba, abajo, izquierda o derecha para llegar a la solucion.

## Cómo compilar y ejecutar

Dado que el sistema está diseñado para ser accesible y fácil de probar, recomendamos usar [Repl.it](http://repl.it/) para una rápida configuración y ejecución. Sigue estos pasos para comenzar:

1. Visita [Repl.it](https://repl.it/).
2. Crea una nueva cuenta o inicia sesión si ya tienes una.
3. Una vez en tu dashboard, selecciona "New Repl" y elige "Import from GitHub".
4. Pega la URL del repositorio: `https://github.com/YosoyelDario/Tarea-3-Dario-Fuentes.git`.
5. [Repl.it](http://repl.it/) clonará el repositorio y preparará un entorno de ejecución.
6. En la pestaña "Configurate Repl", sección "Configure the Compile Command", escriba o pegue de preferencia el siguiente comando "gcc tdas/*.c main.c -Wno-unused-result -o main" y presione "done".
7. Presiona el botón "Run" para compilar y ejecutar la aplicación.
## Funcionalidades 

### Funcionando correctamente:

-Busqueda en Profundidad funcionando correctamente, muestra la cantidad de pasos y los movimientos para llegar a una solucion.
-Buscar en Anchura funcionando correctamente, muestra la cantidad de pasos y los movimientos para llegar a una solucion.

### Problemas conocidos:

- PROBLEMA IMPORTANTE!!!!!!!!!!!!!!!!!!
Mientras el programa se este ejecutando, ya sea si se elige el Busqueda en Profundidad o el Buscar en Anchura, si se elige uno luego en el mismo tiempo de ejecucion no se puede elegir el otro, ya que el siguiente a elegir dira que no tiene solucion. Es necesario cerrar el programa si se quiere probar el otro metodo.
  

### A mejorar:

- Implementar una interfaz de usuario más amigable.
- Implementar que luego de cierto tiempo en una opcion, si no se han ingresado datos, volver al menu principal.
- Mejorar la lectura de datos para aceptar errores del usuario.
- Implementar solucion de poder usar ambas funciones en el mismo tiempo de ejecucion sin generar errores.
- Implementar la funcion "Buscar Mejor Primero".

## Ejemplo de uso:
### EL USUARIO CERRARA EL PROGRAMA CUANDO DESEE USAR OTRO TIPO DE BUSQUEDA.

### MENU:
````
Estado inicial del puzzle:
x 2 8 
1 3 4 
6 5 7 

Vamos a resolver el puzzle-8 elegido

========================================
     Escoge método de búsqueda
========================================
1) Búsqueda en Profundidad
2) Buscar en Anchura
3) Buscar Mejor Primero
4) Salir
Ingrese su opción:

````
#### Paso 1: Busqueda en profundidad

Se ingresa la opcion 1.
````
---------Solucion por DFS---------
Se muestra el 8-puzzle inicial
Estado Inicial:
x 2 8 
1 3 4 
6 5 7 

Se encontro una solución.
Secuencia de movimientos para llegar a la solución:

Movimiento 1: Mov. hacia abajo
1 2 8 
x 3 4 
6 5 7 
Movimiento 2: Mov. hacia la derecha
1 2 8 
3 x 4 
6 5 7 
Movimiento 3: Mov. hacia la derecha
1 2 8 
3 4 x 
6 5 7 
Movimiento 4: Mov. hacia la izquierda
1 2 8 
3 x 4 
6 5 7 
Movimiento 5: Mov. hacia la derecha
1 2 8 
3 4 x 
6 5 7 
Movimiento 6: Mov. hacia arriba
1 2 x 
3 4 8 
6 5 7 
Movimiento 7: Mov. hacia la izquierda
1 x 2 
3 4 8 
6 5 7 
Movimiento 8: Mov. hacia abajo
1 4 2 
3 x 8 
6 5 7 
Movimiento 9: Mov. hacia abajo
1 4 2 
3 5 8 
6 x 7 
Movimiento 10: Mov. hacia la derecha
1 4 2 
3 5 8 
6 7 x 
Movimiento 11: Mov. hacia arriba
1 4 2 
3 5 x 
6 7 8 
Movimiento 12: Mov. hacia la izquierda
1 4 2 
3 x 5 
6 7 8 
Movimiento 13: Mov. hacia arriba
1 x 2 
3 4 5 
6 7 8 
Movimiento 14: Mov. hacia la izquierda
x 1 2 
3 4 5 
6 7 8 

Número de estados visitados: 12795

````
Se muestran todos los movimientos hasta llegar al estado final de nuestro puzzle-8 usando DFS.

#### Paso 2: Buscar en Anchura

Se ingresa la opcion 2.
````
---------Solucion por BFS---------
Se muestra el 8-puzzle inicial
Estado Inicial:
x 2 8 
1 3 4 
6 5 7 

Se encontro una solución.
Secuencia de movimientos para llegar a la solución:

Movimiento 1: Mov. hacia abajo
1 2 8 
x 3 4 
6 5 7 
Movimiento 2: Mov. hacia la derecha
1 2 8 
3 x 4 
6 5 7 
Movimiento 3: Mov. hacia la derecha
1 2 8 
3 4 x 
6 5 7 
Movimiento 4: Mov. hacia arriba
1 2 x 
3 4 8 
6 5 7 
Movimiento 5: Mov. hacia la izquierda
1 x 2 
3 4 8 
6 5 7 
Movimiento 6: Mov. hacia abajo
1 4 2 
3 x 8 
6 5 7 
Movimiento 7: Mov. hacia abajo
1 4 2 
3 5 8 
6 x 7 
Movimiento 8: Mov. hacia la derecha
1 4 2 
3 5 8 
6 7 x 
Movimiento 9: Mov. hacia arriba
1 4 2 
3 5 x 
6 7 8 
Movimiento 10: Mov. hacia la izquierda
1 4 2 
3 x 5 
6 7 8 
Movimiento 11: Mov. hacia arriba
1 x 2 
3 4 5 
6 7 8 
Movimiento 12: Mov. hacia la izquierda
x 1 2 
3 4 5 
6 7 8 

Número de estados visitados: 190886

````
Se muestran todos los movimientos hasta llegar al estado final de nuestro puzzle-8 usando BFS.
