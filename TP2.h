#ifndef grafof_H
#define grafof_H

typedef struct vertice vertice;
typedef struct lista_adjacente lista_adjacente;
typedef struct aresta aresta;

vertice* criar_vertices(int n);
lista_adjacente* criar_lista();
aresta* criar_aresta(int destino, int distancia);

void get_povos(FILE* entrada, vertice* grafo);

void add_aresta(vertice* grafo, int origem, int destino, int distancia);
void mostrar_povos(vertice* grafo);
void mostrar_adjacencia(vertice* grafo, int v);

void percorre_guloso(vertice* grafo, int n, int peso_max, int dist_max);
void calcular_instancia(FILE* entrada);

#endif