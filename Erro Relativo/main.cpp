//Erro relativo
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void escrever(double valor) {
	FILE *file3 = fopen("resultado-erro-relativo.txt","a+");

	if(file3) {
		fprintf(file3,"%lf\n",valor);
	} else
		printf("Falha na abertura do arquivo!");

	fclose(file3);
}

int main(int argc, char** argv) {
	printf("Calculando...\n");
	FILE *file = fopen("previsao.txt","r");
	FILE *file2 = fopen("dado.txt","r");
	double v_previsao=0, v_dado=0,erro_relativo=0;

	if(file && file2) {
		while((fscanf(file,"%lf",&v_previsao) != EOF) && (fscanf(file2,"%lf",&v_dado) != EOF)) { // pega os dados dos arquivos comparando se os dois chegaram ao final
			erro_relativo = fabs(v_previsao - v_dado) / v_dado; // calculo do erro relativo
			escrever(erro_relativo); // escreve o valor do erro relativo em porcentagem no arquivo
			erro_relativo = 0;
		}

	} else
		printf("Falha na abertura do arquivo!");
	fclose(file);
	fclose(file2);
	printf("Concluido!");
	return 0;
}
