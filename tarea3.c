#include <stdio.h>
#include <stdlib.h>
#include "tdas/list.h"
#include "tdas/queue.h"
#include "tdas/extra.h"
#include "tdas/stack.h"
//#include "tdas/heap.h"
#include <string.h>

// Definición de la estructura para el estado del puzzle
typedef struct {
    int square[3][3]; // Matriz 3x3 que representa el tablero
    int x;    // Posición x del espacio vacío
    int y;    // Posición y del espacio vacío

    List* actions; //Secuencia de movimientos para llegar al estado
} State;

int distancia_L1(State* state) {
    int ev=0;
    int k=1;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++){
            int val=state->square[i][j];
            if (val==0) continue;
            int ii=(val)/3;
            int jj=(val)%3;
            ev+= abs(ii-i) + abs(jj-j);
        }
    return ev;
}


// Función para imprimir el estado del puzzle
void imprimirEstado(State *estado) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (estado->square[i][j] == 0)
                printf("x "); // Imprime un espacio en blanco para el espacio vacío
            else
                printf("%d ", estado->square[i][j]);
        }
        printf("\n");
    }
}
//Comprueba si el estado es el buscado
int esEstadoFinal(State* estadoActual)
{
  int estadoF = estadoActual->square[0][0];
  for (int i = 0; i < 3; i++)
  {
    for(int j = 0; j < 3; j++)
    {
      if(i==0 && j == 0)continue;
      if(estadoActual->square[i][j] < estadoF)return 0;
      estadoF = estadoActual->square[i][j];
    }
  }
  return 1;
}

List* obtenerAcciones(List* lista)
{
  List* newList = list_create();
  if(newList == NULL) return NULL;

  void* auxAccion = list_first(lista);
  while(auxAccion != NULL)
  {
    list_pushBack(newList, auxAccion);
    auxAccion = list_next(lista);
  }
  return newList;
}

State* copiarEstado(const State* estado)
{
  State* newEstado = (State*)malloc(sizeof(State));
  if(newEstado == NULL) return NULL;
  for(int i = 0; i < 3; i++)
  {
    for(int k = 0; k < 3; k++)
    {
      newEstado->square[i][k]= estado->square[i][k];
    }
  }
  newEstado->x = estado->x;
  newEstado->y = estado->y;
  if(estado->actions != NULL){
    newEstado->actions = obtenerAcciones(estado->actions);
  }
  else{
    newEstado->actions = NULL;
  }
  return newEstado;
}

State* transition(State* estado, int accion)
{
  //obtener casillas vacias
  int X = estado->x; //X es la fila, representa la pos. del espacio vacio
  int Y = estado->y; //Y es la columna, representa la pos. del espacio vacio
  
  //Ptr, asignacion de memoria para almacenar la accion.
  int *ptrAccion = (int*)malloc(sizeof(int));
  if(ptrAccion == NULL) return NULL;
  *ptrAccion = accion;
  
  if(accion == 1 && (X-1) >= 0)
  {
    estado->square[X][Y] = estado->square[X-1][Y];
    estado->square[X-1][Y] = 0;
    estado->x--;
    list_pushBack(estado->actions, ptrAccion);
  }
  else if(accion == 2 && (X+1) <=2)
  {
    estado->square[X][Y] = estado->square[X+1][Y];
    estado->square[X+1][Y] = 0;
    estado->x++;
    list_pushBack(estado->actions, ptrAccion);
  }
  else if(accion == 3 && (Y-1) >=0)
  {
    estado->square[X][Y] = estado->square[X][Y-1];
    estado->square[X][Y-1] = 0;
    estado->y--;
    list_pushBack(estado->actions, ptrAccion);
  }
  else if(accion == 4 && (Y+1) <=2)
  {
    estado->square[X][Y] = estado->square[X][Y+1];
    estado->square[X][Y+1] = 0;
    estado->y++;
    list_pushBack(estado->actions, ptrAccion);
  }
  else{
    free(ptrAccion);
    estado->x = -1; //pos del espacio vacio se establece como no valida.
  }
}

List* getAdyEstados(State* estado)
{
  List* listaAdy = list_create();
  
  for(int i = 1; i <= 4; i++)
  {
    State* auxEstado = copiarEstado(estado);
    transition(auxEstado, i);
    if(auxEstado ->x != -1) // si el estado es valido
    {
      list_pushBack(listaAdy, auxEstado);
    }
    else
    {
      list_clean(auxEstado->actions);
    }
  }
  return listaAdy;
}

List* dfs(State* estadoInicial, int* contador)
{
  limpiarPantalla();
  printf("---------Solucion por DFS---------\n");
  printf("Se muestra el 8-puzzle inicial\n");
  
  printf("Estado Inicial:\n");
  imprimirEstado(estadoInicial);
  printf("\n");
  
  //Crear pila y agregar el estado inicial.
  Stack* pila = stack_create(NULL); // funcion stack_create necesita un argumento Stack *stack_create(Stack *stack), **en caso de no funcionar borrar argumento de funcion stack create **
  stack_push(pila, estadoInicial);

  while(stack_top(pila) != NULL)
  {
    State* estadoActual = stack_top(pila);
    stack_pop(pila);
    //Verificar si el estado actual es el estado final
    if(list_size(estadoActual->actions) >= 15)
      {
        //Si supero los 15 movimientos, continuar con el siguiente estado
        continue;
      }
    if(distancia_L1(estadoActual) == 0)
    {
      stack_clean(pila);
      return estadoActual->actions;
    }
    //Obtener los estados adyacentes al estado actual
    List* estadosAdyacentes = getAdyEstados(estadoActual);
    State* estadoAdy = list_first(estadosAdyacentes);
    //Agregar estados adyacentes a la pila
    while(estadoAdy != NULL)
    {
      if(distancia_L1(estadoAdy) <= 10){
        stack_push(pila, estadoAdy);
      }
      estadoAdy = list_next(estadosAdyacentes);
    }
    list_clean(estadosAdyacentes);
    list_clean(estadoActual->actions);
    (*contador)++;
    //Liberar memoria al pasar a otro estado
  }
  //liberar memoria
  stack_clean(pila);
  
  return NULL; //Si no se encuentra solucion.
}

List* bfs(State* estadoInicial, int* contador)
{
  limpiarPantalla();
  printf("---------Solucion por BFS---------\n");
  printf("Se muestra el 8-puzzle inicial\n");

  printf("Estado Inicial:\n");
  imprimirEstado(estadoInicial);
  printf("\n");
  
  Queue* cola = queue_create(cola);
  if(cola == NULL) exit(EXIT_FAILURE);
  queue_insert(cola, estadoInicial);
  
  while(queue_front(cola) != NULL)
  {
    State* estadoActual = queue_front(cola);
    queue_remove(cola);
    if(list_size(estadoActual->actions) >= 15)continue;
    
    if(esEstadoFinal(estadoActual))
    {
      //printf("Se encontro una solución\n");
      //imprimirEstado(estadoActual);
      return estadoActual->actions;
    }
    List* estadosAdyacentes = getAdyEstados(estadoActual);
    State* estadoAdy = list_first(estadosAdyacentes);
    while(estadoAdy != NULL)
    {
      queue_insert(cola, estadoAdy);
      estadoAdy = list_next(estadosAdyacentes);
    }
    list_clean(estadosAdyacentes);
    list_clean(estadoActual->actions);
    (*contador)++;
    
  }
  queue_clean(cola);
  printf("No se encontro solucion\n");
}
//Mostrar la secuencia de movimientos para llegar al estado final
void imprimirSecuenciaTransiciones(State estInicial, List* pasos)
{
  //lista nula
  if(pasos == NULL){
    printf("No se encontró solución\n");
  }
  else{
    int contador = 1;
    int *auxAccion = list_first(pasos);

    printf("Se encontro una solución.\n");
    printf("Secuencia de movimientos para llegar a la solución:\n\n");
    while(auxAccion != NULL)
    {
      printf("Movimiento %d: ", contador); //muestra el mov. realizado
      if(*auxAccion == 1) printf("Mov. hacia arriba\n");
      else if(*auxAccion == 2) printf("Mov. hacia abajo\n");
      else if(*auxAccion == 3) printf("Mov. hacia la izquierda\n");
      else printf("Mov. hacia la derecha\n");
      //mostrar matriz despues del mov.
      transition(&estInicial, *auxAccion);
      imprimirEstado(&estInicial);
      contador++;
      auxAccion = list_next(pasos);
    }
    list_clean(pasos);
    //free(pasos);
  }
  printf("\n");
}

int main()
{
  // Estado inicial del puzzle
  State estado_inicial = {
       {{0, 2, 8}, // Primera fila (0 representa espacio vacío)
        {1, 3, 4}, // Segunda fila
        {6, 5, 7}, // Tercera fila
        },  
      0, 0   // Posición del espacio vacío (fila 0, columna 1)
  };
  estado_inicial.actions = list_create();

  // Imprime el estado inicial
  printf("Estado inicial del puzzle:\n");
  imprimirEstado(&estado_inicial);
  printf("\n");
  
  char opcion;
  int contadorPila = 0;
  int contadorCola = 0;
  List* resultadoDfs = NULL;
  List* resultadoBfs = NULL;
    
  do
  {
      printf("Vamos a resolver el puzzle-8 elegido\n\n");
      puts("========================================");
      puts("     Escoge método de búsqueda");
      puts("========================================");
        
      puts("1) Búsqueda en Profundidad");
      puts("2) Buscar en Anchura");
      puts("3) Buscar Mejor Primero");
      puts("4) Salir");
    
      printf("Ingrese su opción: ");
      scanf(" %c", &opcion);
    
      switch (opcion)
      {
        case '1':
          resultadoDfs= dfs(&estado_inicial, &contadorPila);
          imprimirSecuenciaTransiciones(estado_inicial, resultadoDfs);
          printf("Número de estados visitados: %d\n", contadorPila);
          break;
        case '2':
          resultadoBfs = bfs(&estado_inicial, &contadorCola);
          imprimirSecuenciaTransiciones(estado_inicial, resultadoBfs);
          printf("Número de estados visitados: %d\n", contadorCola);
          break;
        case '3':
          printf("Esta opción no se encuentra implementada.\n");
          //best_first(estado_inicial);
          break;
        case '4':
          printf("Cerrando el programa...\n");
          break;
        default:
          printf("Opción invalida. Intentelo denuevo.\n");
          break;
      }
      presioneTeclaParaContinuar();
      limpiarPantalla();

  } while (opcion != '4');
  list_clean(estado_inicial.actions);
  return 0;
}
