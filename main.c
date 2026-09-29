#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================================================
   ESTRUCTURA DEL REGISTRO
   ========================================================= */

typedef struct comparte
{
    char nombre[50];
    char direccion[50];
    int edad;

    struct comparte *next;
    struct comparte *prev;

} Registro;


/* =========================================================
   ESTRUCTURA DE LA LISTA
   ========================================================= */

typedef struct l
{
    Registro *Inicial;
    Registro *Final;

    int len;

} Lista;


/* =========================================================
   CREAR UN NUEVO NODO
   ========================================================= */

Registro *crear()
{
    Registro *T;

    T = (Registro *)malloc(sizeof(Registro));

    if (T == NULL)
        return NULL;

    T->next = NULL;
    T->prev = NULL;

    return T;
}


/* =========================================================
   CREAR LA LISTA
   ========================================================= */

void crear_lista(Lista *lista)
{
    Registro *N_inicial;
    Registro *N_final;

    N_inicial = crear();
    N_final = crear();

    lista->Inicial = N_inicial;
    lista->Final = N_final;

    lista->len = 0;

    lista->Inicial->next = N_final;
    lista->Inicial->prev = NULL;

    lista->Final->prev = N_inicial;
    lista->Final->next = NULL;
}


/* =========================================================
   AGREGAR ELEMENTO AL FINAL DE LA LISTA

   Esta función sirve tanto para FIFO como para LIFO.

   FIFO:
   Se inserta por el final y se saca por el inicio.

   LIFO:
   Se inserta por el final y se saca también por el final.
   ========================================================= */

int agregar(Lista *lista, char nombre[50], char direccion[50], int edad)
{
    Registro *N;

    N = crear();

    if (N == NULL)
        return 0;

    strcpy(N->nombre, nombre);
    strcpy(N->direccion, direccion);

    N->edad = edad;

    /*
        El nuevo nodo se coloca justo antes
        del nodo Final.
    */

    N->prev = lista->Final->prev;
    N->next = lista->Final;

    lista->Final->prev->next = N;
    lista->Final->prev = N;

    lista->len++;

    return 1;
}


/* =========================================================
   FIFO
   FIRST IN - FIRST OUT

   El primero que entra es el primero que sale.

   Se elimina el nodo que está después de Inicial.
   ========================================================= */

int sacar_FIFO(Lista *lista, Registro *salida)
{
    Registro *aux;

    /*
        Verificamos si la cola está vacía.
    */

    if (lista->len == 0)
    {
        return 0;
    }

    /*
        El primer dato real está después
        del nodo Inicial.
    */

    aux = lista->Inicial->next;


    /*
        Copiamos los datos antes de eliminar
        el nodo.
    */

    if (salida != NULL)
    {
        strcpy(salida->nombre, aux->nombre);
        strcpy(salida->direccion, aux->direccion);

        salida->edad = aux->edad;
    }


    /*
        Reconectamos los punteros.
    */

    lista->Inicial->next = aux->next;

    aux->next->prev = lista->Inicial;


    /*
        Liberamos memoria.
    */

    free(aux);


    /*
        Disminuimos el tamaño.
    */

    lista->len--;


    return 1;
}


/* =========================================================
   LIFO
   LAST IN - FIRST OUT

   El último que entra es el primero que sale.

   Se elimina el nodo que está antes de Final.
   ========================================================= */

int sacar_LIFO(Lista *lista, Registro *salida)
{
    Registro *aux;


    /*
        Verificamos si la pila está vacía.
    */

    if (lista->len == 0)
    {
        return 0;
    }


    /*
        El último dato real está antes
        del nodo Final.
    */

    aux = lista->Final->prev;


    /*
        Copiamos los datos antes de eliminar
        el nodo.
    */

    if (salida != NULL)
    {
        strcpy(salida->nombre, aux->nombre);
        strcpy(salida->direccion, aux->direccion);

        salida->edad = aux->edad;
    }


    /*
        Reconectamos los punteros.
    */

    lista->Final->prev = aux->prev;

    aux->prev->next = lista->Final;


    /*
        Liberamos memoria.
    */

    free(aux);


    /*
        Disminuimos el tamaño.
    */

    lista->len--;


    return 1;
}


/* =========================================================
   IMPRIMIR LISTA
   ========================================================= */

void print_list(Lista *lista)
{
    Registro *iter;

    if (lista->len == 0)
    {
        printf("\nLa lista esta vacia.\n");

        return;
    }


    printf("\n=================================\n");
    printf("ELEMENTOS DE LA LISTA\n");
    printf("=================================\n");


    for (iter = lista->Inicial->next;
         iter != lista->Final;
         iter = iter->next)
    {

        printf("\nNombre: %s\n", iter->nombre);

        printf("Direccion: %s\n", iter->direccion);

        printf("Edad: %d\n", iter->edad);

        printf("---------------------------------\n");
    }

    printf("Cantidad de elementos: %d\n", lista->len);
}


/* =========================================================
   DESTRUIR LISTA
   ========================================================= */

void destruir_lista(Lista *lista)
{
    Registro *actual;
    Registro *siguiente;

    actual = lista->Inicial;


    while (actual != NULL)
    {
        siguiente = actual->next;

        free(actual);

        actual = siguiente;
    }


    lista->Inicial = NULL;
    lista->Final = NULL;

    lista->len = 0;
}


/* =========================================================
   LEER DATOS
   ========================================================= */

void leer_datos(char nombre[50], char direccion[50], int *edad)
{
    printf("\nIngrese nombre: ");

    scanf(" %49[^\n]", nombre);


    printf("Ingrese direccion: ");

    scanf(" %49[^\n]", direccion);


    printf("Ingrese edad: ");

    scanf("%d", edad);
}


/* =========================================================
   PROGRAMA PRINCIPAL
   ========================================================= */

int main()
{
    Lista listaFIFO;
    Lista listaLIFO;

    Registro salida;

    char nombre[50];
    char direccion[50];

    int edad;

    int opcion;


    /*
        Creamos las dos estructuras.
    */

    crear_lista(&listaFIFO);

    crear_lista(&listaLIFO);


    do
    {
        printf("\n");
        printf("============================================\n");
        printf("        IMPLEMENTACION FIFO Y LIFO\n");
        printf("============================================\n");

        printf("\n");

        printf("1. Agregar elemento a FIFO\n");

        printf("2. Sacar elemento de FIFO\n");

        printf("3. Mostrar FIFO\n");

        printf("\n");

        printf("4. Agregar elemento a LIFO\n");

        printf("5. Sacar elemento de LIFO\n");

        printf("6. Mostrar LIFO\n");

        printf("\n");

        printf("0. Salir\n");

        printf("\nSeleccione una opcion: ");

        scanf("%d", &opcion);


        switch (opcion)
        {

        /* =================================================
           AGREGAR FIFO
           ================================================= */

        case 1:

            printf("\n--- AGREGAR A FIFO ---\n");

            leer_datos(nombre, direccion, &edad);


            if (agregar(&listaFIFO,
                        nombre,
                        direccion,
                        edad))
            {
                printf("\nElemento agregado correctamente a FIFO.\n");
            }
            else
            {
                printf("\nError al agregar el elemento.\n");
            }

            break;



        /* =================================================
           SACAR FIFO
           ================================================= */

        case 2:

            printf("\n--- SACAR DE FIFO ---\n");


            if (sacar_FIFO(&listaFIFO, &salida))
            {
                printf("\nElemento extraido:\n");

                printf("\nNombre: %s\n",
                       salida.nombre);

                printf("Direccion: %s\n",
                       salida.direccion);

                printf("Edad: %d\n",
                       salida.edad);
            }
            else
            {
                printf("\nFIFO esta vacia.\n");
            }

            break;



        /* =================================================
           MOSTRAR FIFO
           ================================================= */

        case 3:

            printf("\n--- FIFO ---\n");

            print_list(&listaFIFO);

            break;



        /* =================================================
           AGREGAR LIFO
           ================================================= */

        case 4:

            printf("\n--- AGREGAR A LIFO ---\n");

            leer_datos(nombre, direccion, &edad);


            if (agregar(&listaLIFO,
                        nombre,
                        direccion,
                        edad))
            {
                printf("\nElemento agregado correctamente a LIFO.\n");
            }
            else
            {
                printf("\nError al agregar el elemento.\n");
            }

            break;



        /* =================================================
           SACAR LIFO
           ================================================= */

        case 5:

            printf("\n--- SACAR DE LIFO ---\n");


            if (sacar_LIFO(&listaLIFO, &salida))
            {
                printf("\nElemento extraido:\n");

                printf("\nNombre: %s\n",
                       salida.nombre);

                printf("Direccion: %s\n",
                       salida.direccion);

                printf("Edad: %d\n",
                       salida.edad);
            }
            else
            {
                printf("\nLIFO esta vacia.\n");
            }

            break;



        /* =================================================
           MOSTRAR LIFO
           ================================================= */

        case 6:

            printf("\n--- LIFO ---\n");

            print_list(&listaLIFO);

            break;



        /* =================================================
           SALIR
           ================================================= */

        case 0:

            printf("\nSaliendo del programa...\n");

            break;



        default:

            printf("\nOpcion incorrecta.\n");

            break;
        }


    } while (opcion != 0);


    /*
        Liberamos toda la memoria utilizada.
    */

    destruir_lista(&listaFIFO);

    destruir_lista(&listaLIFO);


    return 0;
}
