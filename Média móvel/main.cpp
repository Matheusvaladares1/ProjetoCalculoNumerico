//Média Móvel
#include <stdio.h>
#include <stdlib.h>

#define N 7 // número de elementos na média móvel

void escrever(double media_m) {
	FILE *file = fopen("resultado-media-movel.txt","a+"); // cria o arquivo de resultados das médias móveis

	if(file) {
		fprintf(file,"%lf\n",media_m); // escreve no arquivo as novas médias móveis

		fclose(file);
	} else
		printf("\n\t-->ERRO ao abrir arquivo!\n");
}

int main() {
	printf("Calculando...\n");
	int i;
	double valores[N]= {0,0,0,0,0,1,0}; // dados a serem utilizados no início da média móvel
	double media_movel = 0, novo_valor, numero_lido, valor_antigo;

	for (int i = 0; i < N; i++) { // calcular a média móvel inicial
		media_movel += valores[i];
	}
	media_movel /= N;

	escrever(media_movel); // escreve a primeira media movel no arquivo

	FILE *file = fopen("valores.txt","r"); // Abertura do arquivo com os novos valores para serem incluidos na média móvel
	if(file) {
		while(fscanf(file,"%lf",&numero_lido) != EOF) {

			for(i=0; i<N ; i++) { // Eliminando o menor valor
				valores[i] = valores[i+1];
			}
			valores[i-1] = numero_lido; // atribuindo o novo valor lido
			
			media_movel = 0; // zerando media_movel antes de calcular a nova
			
			for (int i = 0; i < N; i++) { 
				media_movel += valores[i];
			}
			media_movel /= N; // calculando a nova média móvel 
			
			escrever(media_movel); // chama a função que escreve as novas médias móveis no arquivo
		}
		fclose(file);
	} else
		printf("\n\t-->ERRO ao abrir arquivo!\n");
	
	printf("Concluido!");

	return 0;
}

