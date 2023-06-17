//Método dos mínimos quadrados
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 21

void escrever_alfa1(float alfa1) {
	FILE *file = fopen("resultado-alfa1.txt","a+"); // cria o arquivo de resultados das coeficientes alfa1

	if(file) {
		fprintf(file,"%.4f\n",alfa1); // escreve no arquivo as novas resultados dos coeficientes alfa1

		fclose(file);
	} else
		printf("\n\t-->ERRO ao abrir arquivo!\n");
}

void escrever_alfa2(float alfa2) {
	FILE *file = fopen("resultado-alfa2.txt","a+"); // cria o arquivo de resultados das coeficientes alfa2

	if(file) {
		fprintf(file,"%.4f\n",alfa2); // escreve no arquivo as novas resultados dos coeficientes alfa2

		fclose(file);
	} else
		printf("\n\t-->ERRO ao abrir arquivo!\n");
}

void escrever_alfa3(float alfa3) {
	FILE *file = fopen("resultado-alfa3.txt","a+"); // cria o arquivo de resultados das coeficientes alfa3

	if(file) {
		fprintf(file,"%.4f\n",alfa3); // escreve no arquivo as novas resultados dos coeficientes alfa3

		fclose(file);
	} else
		printf("\n\t-->ERRO ao abrir arquivo!\n");
}

void escrever_previsao(float previsao) {
	FILE *file = fopen("previsao.txt","a+"); // cria o arquivo de resultados das previsões

	if(file) {
		fprintf(file,"%.4f\n",previsao); // escreve no arquivo as previsões

		fclose(file);
	} else
		printf("\n\t-->ERRO ao abrir arquivo!\n");
}


void sistema_linear(double v1, double v2, double v3, double v4, double v5, double v6, double v7, double v8, double v9, double v10, double v11, double v12, double proximodia) {

	double matriz[3][4]; // matriz para calcular o sistema linear
	int i,j;
	matriz[0][0] = v1;
	matriz[0][1] = v2;
	matriz[0][2] = v3;
	matriz[0][3] = v4;
	matriz[1][0] = v5;
	matriz[1][1] = v6;
	matriz[1][2] = v7;
	matriz[1][3] = v8;
	matriz[2][0] = v9;
	matriz[2][1] = v10;
	matriz[2][2] = v11;
	matriz[2][3] = v12;

	for (i=0; i<3; i++) {
		for (j = i + 1; j < 3; j++) {
			if (fabs(matriz[i][i]) < fabs(matriz[j][i])) {
				for (int k = 0; k <= 3; k++) {
					double temp = matriz[i][k];
					matriz[i][k] = matriz[j][k];
					matriz[j][k] = temp;
				}
			}
		}
		for (j=i+1; j<3; j++) {
			double temp = matriz[j][i] / matriz[i][i];
			for (int k = 0; k <= 3; k++) {
				matriz[j][k] -= temp * matriz[i][k];
			}
		}
	}

	double alfa1=0,alfa2=0,alfa3=0;

	alfa3 = matriz[2][3] / matriz[2][2];
	alfa2 = (matriz[1][3] - matriz[1][2] * alfa3) / matriz[1][1];
	alfa1 = (matriz[0][3] - matriz[0][1] * alfa2 - matriz[0][2] * alfa3) / matriz[0][0];

	escrever_alfa1(alfa1);
	escrever_alfa2(alfa2);
	escrever_alfa3(alfa3);

	double previsao=0;

	previsao = ( (alfa1*(pow(proximodia,2))) + (alfa2*proximodia) + (alfa3) );

	escrever_previsao(previsao);
}


int main(int argc, char** argv) {
	printf("Calculando...\n");
	double x[N] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21}; // x
	double y[N] = {3095,3095,3095,3095,3095,3096,3096,3096,3096,3096,3096,3096,3099,3099,3100,3105,3105,3107,3108,3116,3118}; // f(x)

	double g1[N], g2[N], g3[N]; // Função = alfa1 * x² + alfa2 * x + alfa3 * 1
	//onde
	//g1=x²
	//g2=x
	//g3=1

	int i;

	for(i=0; i<N; i++) {
		g1[i] = pow(x[i],2);
		g2[i] = x[i];
		g3[i] = 1;
	}

	double fxg1=0, fxg2=0, fxg3=0, g1xg1=0, g1xg2=0, g1xg3=0, g2xg3=0, g2xg2=0, g3xg3=0;

	for(i=0; i<N; i++) {
		fxg1 += y[i] * g1[i];
		fxg2 += y[i] * g2[i];
		fxg3 += y[i] * g3[i];
		g1xg1 += g1[i] * g1[i];
		g1xg2 += g1[i] * g2[i];
		g1xg3 += g1[i] * g3[i];
		g2xg3 += g2[i] * g3[i];
		g2xg2 += g2[i] * g2[i];
		g3xg3 += g3[i] * g3[i];
	}

	sistema_linear(g1xg1,g1xg2,g1xg3,fxg1,g1xg2,g2xg2,g2xg3,fxg2,g1xg3,g2xg3,g3xg3,fxg3,(x[N-1]+1));

	double casos_acumulados;

	FILE *file = fopen("casos-acumulados.txt","r"); // Abertura do arquivo com os novos valores para serem incluidos nas casos acumulados

	if(file) {

		while(fscanf(file,"%lf",&casos_acumulados) != EOF) {

			for(i=0; i<N-1; i++) { // Eliminando o menor dia
				x[i] = x[i+1];
			}
			x[N-1] += 1; // acrescenta mais um dia corrido

			for(i=0; i<N-1; i++) { // Eliminando o menor valor acumulado
				y[i] = y[i+1];
			}

			y[N-1] = casos_acumulados; // Novo valor atribuido

			// Refazendo os calculos

			for(i=0; i<N; i++) {
				g1[i] = pow(x[i],2);
				g2[i] = x[i];
				g3[i] = 1;
			}

			double fxg1=0, fxg2=0, fxg3=0, g1xg1=0, g1xg2=0, g1xg3=0, g2xg3=0, g2xg2=0, g3xg3=0;

			for(i=0; i<N; i++) {
				fxg1 += y[i] * g1[i];
				fxg2 += y[i] * g2[i];
				fxg3 += y[i] * g3[i];
				g1xg1 += g1[i] * g1[i];
				g1xg2 += g1[i] * g2[i];
				g1xg3 += g1[i] * g3[i];
				g2xg3 += g2[i] * g3[i];
				g2xg2 += g2[i] * g2[i];
				g3xg3 += g3[i] * g3[i];
			}

			sistema_linear(g1xg1,g1xg2,g1xg3,fxg1,g1xg2,g2xg2,g2xg3,fxg2,g1xg3,g2xg3,g3xg3,fxg3,(x[N-1]+1));

		}
		fclose(file);
	}else
	printf("Erro ao abrir o arquivo casos-acumulados\n");
	printf("Concluido!");
	return 0;
}
