#include <iostream>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

#define Metodo_contigua 1
#define Metodo_enlazada 2
#define Metodo_indexada 3

#define max_archivos 1000
#define max_bloques_X_archivos 2048

// Bloque
// Estado individual de cada bloque del disco simulado.
typedef struct {
    int id_bloque;
    int id_archivo;
    int siguiente_bloque; // Para asignación enlazada
    bool ocupado;
} Bloque;

// Archivo
// Metadatos lógicos y lista de bloques asignados a un archivo activo.
typedef struct {
    int id;
    bool tamano_bytes;
    int num_bloques_datos;
    int bloque_inicio;    // Para contigua y enlazada
    int bloque_indice;    // Para contigua y enlazada
    int bloques[max_bloques_X_archivos]; // Lista de bloques físicos
    bool activo;
} Archivo;

typedef struct {
    int total_mb;
    int bloque_kb;
    int tamano_bloque_bytes;
    int num_bloques_totales;
    int bloques_libres;
    int metodo;
    int min_tamano_kb;
    int max_tamano_kb;

    Bloque *tabla_bloques;
    Archivo archivos[max_archivos];
    int num_archivos_creados;
    int num_archivos_eliminados;

    long total_accesos_io;
    long total_lecturas_realizadas;
} Disco;

// Inicializa las estructuras del disco
// Reserva e inicializa el mapa de bloques del disco simulado
void disco_inicializado(Disco *disco, int mb, int kb, int metodo, int max_kb, int min_kb) {
    disco->total_mb = mb;
    disco->bloque_kb = kb;
    disco->tamano_bloque_bytes = 1024 * kb;
    disco->num_bloques_totales = (mb * 1024) / kb;
    disco->bloques_libres = disco->num_bloques_totales;
    disco->metodo = metodo;
    disco->min_tamano_kb = min_kb;
    disco->max_tamano_kb = max_kb;

    disco->tabla_bloques = (Bloque *)malloc(sizeof(Bloque) * disco->num_bloques_totales);
    for (int i = 0; i < disco->num_bloques_totales; i++) {
        disco->tabla_bloques[i].id_bloque = i;
        disco->tabla_bloques[i].ocupado = false;
        disco->tabla_bloques[i].id_archivo = -1;
        disco->tabla_bloques[i].siguiente_bloque = -1;
    }

    for (int i = 0; i < max_archivos; i++) {
        disco->archivos[i].activo = false;
    }

    disco->num_archivos_creados = 0;
    disco->num_archivos_eliminados = 0;
    disco->total_accesos_io = 0;
    disco->total_lecturas_realizadas = 0;
}

int calculo_fragmentacion_ext(Disco *disco) {
    int max_contiguo = 0;
    int actual_contiguo = 0;

    for (int i = 0; i < disco->num_bloques_totales; i++) {
        if (disco->tabla_bloques[i].ocupado) {
            actual_contiguo++;
            if (actual_contiguo > max_contiguo) {
                max_contiguo = actual_contiguo;
            }
        }else{
            actual_contiguo = 0;
        }
    }
    return disco->bloques_libres - max_contiguo;
}

using namespace std;
int main() {
    cout << "Hola";
    return 0;
}