//Desvio quadrático médio
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define N 21

void escrever(double valor) {
	FILE *file = fopen("resultado-EQM.txt","a+");

	if(file) {
		fprintf(file,"%lf\n",valor);
	} else
		printf("Falha na abertura do arquivo!");

	fclose(file);
}


int main(int argc, char** argv) {
	printf("Calculando...\n");
	double dia[N] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21}; // dias iniciais
	double y[N] = {3095,3095,3095,3095,3095,3096,3096,3096,3096,3096,3096,3096,3099,3099,3100,3105,3105,3107,3108,3116,3118}; // dados iniciais

	FILE *file = fopen("resultado-alfa1.txt","r");
	FILE *file2 = fopen("resultado-alfa2.txt","r");
	FILE *file3 = fopen("resultado-alfa3.txt","r");
	FILE *file4 = fopen("casos-acumulados.txt","r");

	double v_alfa1=0,v_alfa2=0,v_alfa3=0,dado=0,aux[N];
	int i;
	double yi=0,diferenca=0,soma=0,resultado=0;

	if(file && file2 && file3) {
		while((fscanf(file,"%lf",&v_alfa1) != EOF) && (fscanf(file2,"%lf",&v_alfa2) != EOF) && (fscanf(file3,"%lf",&v_alfa3) != EOF) && (fscanf(file4,"%lf",&dado) != EOF)) {

			for (i=0; i<N; i++) {
				yi = ( (v_alfa1*(pow(dia[i],2))) + (v_alfa2*dia[i]) + (v_alfa3) );
				diferenca = yi- y[i];
				aux[i] = pow(diferenca,2);
				soma += aux[i];
			}

			soma /= 21;
			resultado = sqrt (soma);
			escrever(resultado);
			soma=0;
			resultado=0;

			for(i=0; i<N-1; i++) { // Eliminando o menor dia
				dia[i] = dia[i+1];
			}
			dia[N-1] += 1;

			for(i=0; i<N-1; i++) { // Eliminando o primeiro dado
				y[i] = y[i+1];
			}
			y[N-1] = dado;

		}
	}
	printf("Concluido!");
	return 0;
}
