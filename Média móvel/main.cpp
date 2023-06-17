//M�dia M�vel
#include <stdio.h>
#include <stdlib.h>

#define N 7 // n�mero de elementos na m�dia m�vel

void escrever(double media_m) {
	FILE *file = fopen("resultado-media-movel.txt","a+"); // cria o arquivo de resultados das m�dias m�veis

	if(file) {
		fprintf(file,"%lf\n",media_m); // escreve no arquivo as novas m�dias m�veis

		fclose(file);
	} else
		printf("\n\t-->ERRO ao abrir arquivo!\n");
}

int main() {
	printf("Calculando...\n");
	int i;
	double valores[N]= {0,0,0,0,0,1,0}; // dados a serem utilizados no in�cio da m�dia m�vel
	double media_movel = 0, novo_valor, numero_lido, valor_antigo;

	for (int i = 0; i < N; i++) { // calcular a m�dia m�vel inicial
		media_movel += valores[i];
	}
	media_movel /= N;

	escrever(media_movel); // escreve a primeira media movel no arquivo

	FILE *file = fopen("valores.txt","r"); // Abertura do arquivo com os novos valores para serem incluidos na m�dia m�vel
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
			media_movel /= N; // calculando a nova m�dia m�vel 
			
			escrever(media_movel); // chama a fun��o que escreve as novas m�dias m�veis no arquivo
		}
		fclose(file);
	} else
		printf("\n\t-->ERRO ao abrir arquivo!\n");
	
	printf("Concluido!");

	return 0;
}

