typedef struct mochila{
	int valor;
	struct mochila *anterior;
}mochila;


int peso_min(int valor, int *pesos, int* valores, int tamanho){
	int item = -1;
	int i;
	for (i=0; i<tamanho; i++){
		if(valores[i] == valor){
			if(item == -1 || pesos[i] < pesos[item]){
				item = i;
			}
		}
	}
	return item;
}

int mochila_ilimitada(int capacidade, int* pesos, int* valores, int* cont, tamanho){
	mochila* z = malloc((capacidade+1)*sizeof(mochila));
	int c, i;
	int solution, valor;
	z[0].valor = 0;
	z[0].anterior = NULL;
	mochila *atual;

	for(c = 1; c <= capacidade; c++){
		z.valor = z.valor;
		z.anterior = &(z);
		for (i=0; i< tamanho; i++){
			if (pesos[i] <= c){

			mochila *anterior = z + (c - pesos[i]);
			if (anterior -> valor + valores[i] > z.valor){
				z.valor = anterior->valor + valores[i];
				z.anterior = anterior;
			}
		}
	}
}

for (valor = z[capacidade].valor, atual = z[capacidade].anterior; atual != NULL; valor = atual->valor, autal = atual->anterior){
	count[peso_min(valor - atual->valor, pesos, valores, tamanho)]++;
}
solution = z[capacidade].valor;
free(z);
return solution;
}