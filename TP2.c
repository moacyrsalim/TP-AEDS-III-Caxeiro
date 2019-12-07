#include <stdio.h>
#include <stdlib.h>

typedef struct vertice vertice;
typedef struct lista_adjacente lista_adjacente;
typedef struct aresta aresta;

typedef struct vertice{
	int peso;
	int habilidade;
	struct lista_adjacente* lista;
}vertice;

typedef struct lista_adjacente{
	aresta* inicio;
	aresta* fim;
}lista_adjacente;

typedef struct aresta{
	int destino;
	int distancia;
	aresta* prox;
}aresta;

lista_adjacente* criar_lista();

vertice* criar_vertices(int n){
	vertice* grafo = calloc(n+1, sizeof(vertice));
	grafo[0].peso = n;

	while(n > 0){
		grafo[n].lista = criar_lista();
		n--;
	}
	return grafo;
}

void get_povos(FILE* entrada, vertice* grafo){
	int i, j;
	for(i=0; i < grafo[0].peso; i++){
		fscanf(entrada, "%d", &j);
		fscanf(entrada, "%d %d", &grafo[j].peso, &grafo[j].habilidade);
	}
}

lista_adjacente* criar_lista(){
	lista_adjacente* nova_lista = malloc(sizeof(lista_adjacente));
	nova_lista->inicio = NULL;
	nova_lista->fim = NULL;
	return nova_lista;
}

aresta* criar_aresta(int destino, int distancia){
	aresta* nova_aresta = malloc(sizeof(aresta));
	nova_aresta->destino = destino;
	nova_aresta->distancia = distancia;
	nova_aresta->prox = NULL;
	return nova_aresta;
}

void add_aresta(vertice* grafo, int origem, int destino, int distancia){
	aresta* aux = grafo[origem].lista->fim;
	if (aux == NULL){
		aux = criar_aresta(destino, distancia);
		grafo[origem].lista->inicio = aux;
		grafo[origem].lista->fim = aux;
	}
	else {
		aux->prox = criar_aresta(destino, distancia);
		grafo[origem].lista->fim = aux->prox;
	}
}

void mostrar_povos(vertice* grafo){
	int i;
	printf("      Hab    Peso\n");
	for(i = 1; i <= grafo[0].peso; i++){
		printf(" %-5d %-6d %d\n", i, grafo[i].habilidade, grafo[i].peso);
	}
}

void mostrar_adjacencia(vertice* grafo, int v){
	aresta* aux = grafo[v].lista->inicio;
	if(aux == NULL){
		printf("Não há vertices adjacentes\n");
		return;
	}
	else{
		while(aux != NULL){
			printf("Vertice: %-3d Distancia: %d\n", aux->destino, aux->distancia);
			aux = aux->prox;
		}
	}
}

void percorre_guloso(vertice* grafo, int n, int peso_max, int dist_max){
	int *vet = calloc(n, sizeof(int));
	int *x = calloc(n, sizeof(int));
	vertice* aux = grafo;
	aresta* aresta;
	int melhor, i, j, soldados;
	int habilidade_total;
	melhor = 1;
	j = 0;
	for (i = 2; i < n; i++){
		if ((float)grafo[i].habilidade/grafo[i].peso > (float)grafo[melhor].habilidade/grafo[melhor].peso){
			melhor = i;
		}
	}
	vet[j] = melhor;
	soldados = peso_max / grafo[melhor].peso;
	peso_max = peso_max % grafo[melhor].peso;
	habilidade_total = soldados*grafo[melhor].habilidade;

	x[j] = soldados;
	j++;
	aresta = grafo[melhor].lista->inicio;
	melhor = aresta->destino;
	while(peso_max > 0 && j <= n){
		while (aresta != NULL){
			if(grafo[aresta->destino].habilidade/grafo[aresta->destino].peso > grafo[melhor].habilidade/grafo[melhor].peso){
				melhor = aresta->destino;
				printf("%p\n", aresta);
			}
			aresta = aresta->prox;
			soldados = peso_max / grafo[melhor].peso;
			peso_max = peso_max % grafo[melhor].peso;
			habilidade_total = habilidade_total + soldados*grafo[melhor].habilidade;
			x[j] = soldados;
		}
		j++;
		printf("%d\n", j);
	}
	printf("%d ", habilidade_total);
	for(i = 0; vet[i]>0; i++){
		printf("%d %d\n", vet[i], x[i]);
	}
}

void calcular_instancia(FILE* entrada){
	int povos, dist_max, peso_max, caminhos;
	int origem, destino, distancia;
	vertice* grafo;
	fscanf (entrada, "%d %d %d %d", &povos, &dist_max, &peso_max, &caminhos);
	printf(" povos: %d\n dmax:%d\n peso_max:%d \n camihnos:%d\n", povos, dist_max, peso_max, caminhos);
	grafo = criar_vertices(povos);

	get_povos(entrada, grafo);
	mostrar_povos(grafo);

	while(caminhos > 0){
		fscanf(entrada, "%d %d %d", &origem, &destino, &distancia);
		printf("%d %d %d\n", origem, destino, distancia);
		add_aresta(grafo, origem, destino, distancia);
		add_aresta(grafo, destino, origem, distancia);
		caminhos--;
		
	}
	
	percorre_guloso(grafo, povos, peso_max, dist_max);
	free(grafo);
}


int main(){
	FILE* entrada;
	int instancia;
	entrada = fopen("povos.txt","r");
	fscanf(entrada,"%d", &instancia);

	while(instancia != 0){
		calcular_instancia(entrada);
		instancia--;
	}
	fclose(entrada);
	return 0;
}