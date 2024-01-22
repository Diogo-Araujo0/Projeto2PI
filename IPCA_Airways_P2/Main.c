#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <locale.h>
#include <time.h>

//Limpar Ecrã
void clrscr()
{
	system("@cls||clear");
}

struct Frota {
	int CodReg;
	char Marca[100];
	char Modelo[100];
	int NumLug;
	double Velocidade;
	double Consumo;
}frota[100];
void InserirFrota()
{
	FILE* fp;
	int choice;
	printf("Quer criar um novo ficheiro?\n");
	printf("1 - Sim   2 - Não\n");
	scanf("%d", &choice);
	do
		if (choice == 1)
		{
			fp = fopen("Frota.txt", "w");
		}
		else
		{
			fp = fopen("Frota.txt", "r");
			fread(frota, sizeof(frota), 1, fp);
			fclose(fp);
			fp = fopen("Frota.txt", "r+");
		}
	while (choice != 1 && choice != 2);
	int decisao = 0;
	static int i = 0;
	//O valor de i nunca se altera mesmo que se volte a usar esta função
	if (frota[i].CodReg == 0)
	{
		clrscr();
		printf("Inserir código: ");
		scanf("%d", &frota[i].CodReg);
		for (int j = 0; j < 100; j++) {
			if (frota[j].CodReg == frota[i].CodReg && j != i) {
				printf("\nO código de Registo já está em uso\n");
				frota[i].CodReg = 0;
				break;
			}
		}
		if (frota[i].CodReg != 0) {
			printf("Inserir marca: ");
			scanf("%s", &frota[i].Marca);

			printf("Inserir modelo: ");
			scanf("%s", &frota[i].Modelo);

			printf("Inserir número de lugares: ");
			scanf("%d", &frota[i].NumLug);

			printf("Inserir velocidade: ");
			scanf("%lf", &frota[i].Velocidade);

			printf("Inserir consumo: ");
			scanf("%lf", &frota[i].Consumo);

			fwrite(frota, sizeof(frota), 1, fp);

			i++;

			clrscr();
		}
	}
	else
	{
		i++;
	}
	fclose(fp);
}
void ModificarFrota()
{
	int cod;
	int nfrota = 0;
	printf("Insira o código da frota a modificar: ");
	scanf("%d", &cod);
	//Procura o código na lista
	FILE* fp;
	fp = fopen("Frota.txt", "w");
	fread(frota, sizeof(frota), 1, fp);

	for (int i = 0; i < 100; i++)
	{
		if (frota[i].CodReg == cod && cod != 0)
		{
			nfrota = 1;
			clrscr();
			printf("Inserir código: ");
			scanf("%d", &frota[i].CodReg);

			printf("Inserir marca: ");
			scanf("%s", &frota[i].Marca);

			printf("Inserir modelo: ");
			scanf("%s", &frota[i].Modelo);

			printf("Inserir número do lugar: ");
			scanf("%d", &frota[i].NumLug);

			printf("Inserir velocidade: ");
			scanf("%lf", &frota[i].Velocidade);

			printf("Inserir consumo: ");
			scanf("%lf", &frota[i].Consumo);
			fwrite(frota, sizeof(frota), 1, fp);
		}
	}
	if (nfrota != 0) {
		printf("\nFrota modificada com sucesso\n");
	}
	else {
		printf("\nNão existe uma frota com esse código de registo\n");
	}
	fclose(fp);
	printf("\nPrima enter para continuar\n");
	getchar();
}
void ListarFrota()
{
	//Lista todas as frotas que não tiverem o Código 0
	/*for (int i = 0; i < 100; i++)
	{
		if (frota[i].CodReg != 0)
		{
			printf("Código: %d", frota[i].CodReg);
			printf("\nMarca: %s", frota[i].Marca);
			printf("\nModelo: %s", frota[i].Modelo);
			printf("\nNúmero do Lugar: %d", frota[i].NumLug);
			printf("\nVelocidade: %.2lf", frota[i].Velocidade);
			printf("\nConsumo: %.2lf\n\n", frota[i].Consumo);
		}
	}
	printf("\nPrima enter para continuar\n");*/
	int f = 0;
	FILE* fp;
	fp = fopen("Frota.txt", "r");
	fread(frota, sizeof(frota), 1, fp);
	for (int i = 0; i < 100; ++i)
	{
		if (frota[i].CodReg != 0)
		{
			f++;
		}
	}
	for (int j = 0; j < f; ++j)
	{
		printf("Código: %d\n", frota[j].CodReg);
		printf("Marca: %s\n", frota[j].Marca);
		printf("Modelo: %s\n", frota[j].Modelo);
		printf("Número de Lugares: %d\n", frota[j].NumLug);
		printf("Velocidade: %.2f Km/H\n", frota[j].Velocidade);
		printf("Consumo: %.2f L\n\n", frota[j].Consumo);
	}
	fclose(fp);
	getchar();

}
void RemoverFrota()
{
	FILE* fp;
	fp = fopen("Frota.txt", "w");
	fread(frota, sizeof(frota), 1, fp);
	int cod, remove = -1;
	int nfrotas = 0;
	printf("Insira o código da frota a retirar: ");
	scanf("%d", &cod);

	//Procura o código na lista
	for (int i = 0; i < 100; i++)
	{
		if (frota[i].CodReg == cod && cod != 0)
		{
			nfrotas = 1;
			remove = i;
			break;
		}

	}
	if (nfrotas != 1) {
		printf("\nNão existe uma frota com esse código de registo\n");
	}
	//Puxa todos os elementos após o retirado 1 casa para a esquerda
	if (remove != -1)
	{

		for (int i = remove; i < 100 - 1; i++)
		{
			frota[i] = frota[i - 1];
			fwrite(frota, sizeof(frota), 1, fp);

		}
		printf("\nFrota id %d removida com sucesso\n", cod);
	}
	fclose(fp);

	printf("\nPrima enter para continuar\n");
	getchar();
};
void ProcurarFrota()
{
	/*int cod;
	int nfrota = 0;
	printf("Insira o código da frota a procurar: ");
	scanf("%d", &cod);
	//Procura o código na lista
	for (int i = 0; i < 100; i++)
	{
		if (frota[i].CodReg == cod && cod != 0)
		{
			nfrota = 1;
			printf("\nCódigo: %d", frota[i].CodReg);
			printf("\nMarca: %s", frota[i].Marca);
			printf("\nModelo: %s", frota[i].Modelo);
			printf("\nNúmero do Lugar: %d", frota[i].NumLug);
			printf("\nVelocidade: %.2lf", frota[i].Velocidade);
			printf("\nConsumo: %.2lf\n\n", frota[i].Consumo);
		}
	}
	if (nfrota != 0) {
		printf("\nFrota encontrada\n");
	}
	else {
		printf("\nNão existe uma frota com esse código de registo\n");
	}
	printf("\nPrima enter para continuar\n");*/
	int cod, f = 0;
	FILE* fp;
	fp = fopen("Frota.txt", "r");
	fread(frota, sizeof(frota), 1, fp);

	printf("Insira o código da frota a procurar: ");
	scanf("%d", &cod);
	for (int i = 0; i < 100; ++i)
	{
		if (frota[i].CodReg != 0)
		{
			f++;
		}
	}
	for (int j = 0; j < f; ++j)
	{
		if (frota[j].CodReg == cod)
		{
			printf("\nCódigo: %d", frota[j].CodReg);
			printf("\nMarca: %s", frota[j].Marca);
			printf("\nModelo: %s", frota[j].Modelo);
			printf("\nNúmero do Lugar: %d", frota[j].NumLug);
			printf("\nVelocidade: %.2lf", frota[j].Velocidade);
			printf("\nConsumo: %.2lf\n\n", frota[j].Consumo);
		}
	}
	fclose(fp);
	getchar();
}

struct Aeroporto {
	char IATA[100];
	char Nome[100];
	char Cidade[100];
	double Altitude;
} aeroporto[100];
void InserirAeroporto()
{
	FILE* fp2;
	int choice;
	int comparacao;
	printf("Quer criar um novo ficheiro?\n");
	printf("1 - Sim   2 - Não\n");
	scanf("%d", &choice);
	do
		if (choice == 1)
		{
			fp2 = fopen("Aeroporto.txt", "w");
		}
		else
		{
			fp2 = fopen("Aeroporto.txt", "r");
			fread(aeroporto, sizeof(aeroporto), 1, fp2);
			fclose(fp2);
			fp2 = fopen("Aeroporto.txt", "r+");
		}
	while (choice != 1 && choice != 2);
	int decisao = 0;
	static int i = 0;
	//O valor de i nunca se altera mesmo que se volte a usar esta função
	do
	{
		if (strlen(aeroporto[i].IATA) == 0)
		{
			clrscr();
			printf("Inserir IATA: ");
			scanf("%s", &aeroporto[i].IATA);
			for (int j = 0; j < 100; j++) {
				comparacao = strcmp(aeroporto[j].IATA, aeroporto[i].IATA);
				if (comparacao == 0 && j != i) {
					printf("\nO código IATA já está em uso\n");
					aeroporto[i] = aeroporto[j + 10];
					break;
				}
			}
			if (comparacao != 0) {
				printf("Inserir nome: ");
				scanf("%s", &aeroporto[i].Nome);

				printf("Inserir cidade: ");
				scanf("%s", &aeroporto[i].Cidade);

				printf("Inserir altitude: ");
				scanf("%lf", &aeroporto[i].Altitude);

				fwrite(aeroporto, sizeof(aeroporto), 1, fp2);
				i++;

				clrscr();
			}
		}
		else
		{
			i++;
		}
		printf("\nInserir outro aeroporto?\n ");
		printf("1 - Sim   2 - Não\n");
		scanf("%d", &decisao);

		if (decisao != 1 && decisao != 2)
		{
			do {
				clrscr();
				printf("Opção inválida\n ");
				printf("Inserir outro aeroporto?\n ");
				printf("1 - Sim   2 - Não\n");
				scanf("%d", &decisao);

			} while (decisao != 1 && decisao != 2);
		}



	} while (decisao != 2);
	fclose(fp2);


};
void ListarAeroporto() {
	int f = 0;
	FILE* fp2;
	fp2 = fopen("Aeroporto.txt", "r");
	fread(aeroporto, sizeof(aeroporto), 1, fp2);
	for (int i = 0; i < 100; ++i)
	{
		if (strlen(aeroporto[i].IATA) != 0)
		{
			f++;
		}
	}
	for (int j = 0; j < f; ++j)
	{
		printf("\nIATA: %s", aeroporto[j].IATA);
		printf("\nNome do aeroporto: %s", aeroporto[j].Nome);
		printf("\nNome da cidade: %s", aeroporto[j].Cidade);
		printf("\nAltitude do aeroporto: %.2lf\n", aeroporto[j].Altitude);
	}
	fclose(fp2);
	getchar();



}
void ModificarAeroporto()
{
	int comparacao = 0;
	char cod[50];
	int naeroporto = 0;
	printf("Insira a IATA do aeroporto a modificar:");
	scanf("%s", &cod);
	//Procura o código na lista
	for (int i = 0; i < 100; i++)
	{
		comparacao = strcmp(aeroporto[i].IATA, cod);
		if (comparacao == 0)
		{
			naeroporto = 1;
			clrscr();
			printf("Inserir IATA do aeroporto: ");
			scanf("%s", &aeroporto[i].IATA);

			printf("Inserir nome do aeroporto: ");
			scanf("%s", &aeroporto[i].Nome);

			printf("Inserir cidade do aeroporto: ");
			scanf("%s", &aeroporto[i].Cidade);

			printf("Inserir altitude do aeroporto: ");
			scanf("%lf", &aeroporto[i].Altitude);
		}
	}
	if (naeroporto != 0) {
		printf("\nAeroporto modificada com sucesso\n");
	}
	else {
		printf("\nNão existe um aeroporto com esse código de registo\n");
	}
	printf("\nPrima enter para continuar\n");
	getchar();
}
void RemoverAeroporto()
{
	int remove = -1;
	int comparacao = 0;
	char cod[50];
	int naeroporto = 0;
	printf("Insira o código IATA do aeroporto a retirar: ");
	scanf("%s", &cod);

	//Procura o código na lista
	for (int i = 0; i < 100; i++)
	{
		comparacao = strcmp(aeroporto[i].IATA, cod);
		if (comparacao == 0)
		{
			naeroporto = 1;
			remove = i;
			break;
		}

	}
	if (naeroporto != 1) {
		printf("\nNão existe um aeroporto com esse código de IATA\n");
	}
	//Puxa todos os elementos após o retirado 1 casa para a esquerda
	if (remove != -1)
	{

		for (int i = remove; i < 100 - 1; i++)
		{
			aeroporto[i] = aeroporto[i + 1];
		}
		printf("\nAeroporto IATA %s removida com sucesso\n", cod);
	}
	printf("\nPrima enter para continuar\n");
	getchar();
};
void ProcurarAeroporto()
{
	char cod[50];
	int naeroporto = 0;
	int comparacao = 0;
	printf("Insira o código da IATA a procurar: ");
	scanf("%s", &cod);
	//Procura o código na lista
	for (int i = 0; i < 100; i++)
	{
		comparacao = strcmp(aeroporto[i].IATA, cod);
		if (comparacao == 0)
		{
			naeroporto = 1;
			printf("\nCódigo IATA: %s", aeroporto[i].IATA);
			printf("\nNome do aeroporto: %s", aeroporto[i].Nome);
			printf("\nCidade do aeroporto: %s", aeroporto[i].Cidade);
			printf("\nAltitude do aeroporto: %.2lf", aeroporto[i].Altitude);

		}
	}
	if (naeroporto != 0) {
		printf("\nAeroporto encontrado\n");
	}
	else {
		printf("\nNão existe um aeroporto com esse código de IATA\n");
	}
	printf("\nPrima enter para continuar\n");
	getchar();
}

struct Data {
	int Dia;
	int Mes;
	int Ano;
	int Horas;
	int Minutos;
};
struct Voo {
	int NumVoo;
	struct Data Partida;
	struct Data Chegada;
	char Origem[100];
	char Destino[100];
	int Aviao;
	int LugRestantes;
	int TotalLug;
}voo[100];
void InserirVoo() {
	FILE* fp3;
	FILE* fp;
	int choice, aviaoTemp;

	printf("Quer criar um novo ficheiro?\n");
	printf("1 - Sim   2 - Não\n");
	scanf("%d", &choice);
	do
		if (choice == 1)
		{
			fp3 = fopen("Voo.txt", "w");
		}
		else
		{
			fp3 = fopen("Voo.txt", "r");
			fread(voo, sizeof(voo), 1, fp3);
			fclose(fp3);
			fp3 = fopen("Voo.txt", "r+");
		}
	while (choice != 1 && choice != 2);
	int decisao = 0;
	static int i = 0;
	//O valor de i nunca se altera mesmo que se volte a usar esta função
	do
	{

		if (voo[i].NumVoo == 0)
		{
			clrscr();
			printf("Inserir número do voo: ");
			scanf("%d", &voo[i].NumVoo);
			for (int j = 0; j < 100; j++) {
				if (voo[j].NumVoo == voo[i].NumVoo && j != i) {
					printf("\nO código de Voo já está em uso\n");
					voo[i].NumVoo = 0;
					break;
				}
			}
			if (voo[i].NumVoo != 0) {
				printf("Inserir Dia de Partida: \n");
				scanf("%d", &voo[i].Partida.Dia);
				printf("Inserir Mês de Partida: \n");
				scanf("%d", &voo[i].Partida.Mes);
				printf("Inserir Ano de Partida: \n");
				scanf("%d", &voo[i].Partida.Ano);
				printf("Inserir Hora de Partida: \n");
				scanf("%d", &voo[i].Partida.Horas);
				printf("Inserir Minutos de Partida: \n");
				scanf("%d", &voo[i].Partida.Minutos);

				printf("Inserir Dia de Chegada: \n");
				scanf("%d", &voo[i].Chegada.Dia);
				printf("Inserir Mês de Chegada: \n");
				scanf("%d", &voo[i].Chegada.Mes);
				printf("Inserir Ano de Chegada: \n");
				scanf("%d", &voo[i].Chegada.Ano);
				printf("Inserir Hora de Chegada: \n");
				scanf("%d", &voo[i].Chegada.Horas);
				printf("Inserir Minutos de Chegada: \n");
				scanf("%d", &voo[i].Chegada.Minutos);

				printf("Inserir Origem do Voo: \n");
				scanf("%s", &voo[i].Origem);

				printf("Inserir Destino: \n");
				scanf("%s", &voo[i].Destino);
				fp = fopen("Frota.txt", "r");
				fread(frota, sizeof(frota), 1, fp);
				printf("Lista de códigos de aviões:\n");
				for (int j = 0; j < 100; j++) {
					if (frota[j].CodReg != 0) {
						printf("Código: %d\n", frota[j].CodReg);
					}
				}
				int lugares = 0;
				int check = 0;
				while (check == 0) {
					printf("\nInserir Código de avião: \n");
					scanf("%d", &aviaoTemp);
					for (int j = 0; j < 100; j++) {
						if (aviaoTemp == frota[j].CodReg && aviaoTemp != 0) {
							lugares = frota[j].NumLug;
							check++;
						}
					}
					if (check != 0) {
						voo[i].Aviao = aviaoTemp;
						voo[i].LugRestantes = lugares;
						voo[i].TotalLug = lugares;
					}
					else {
						printf("Código de avião inválido\n");
					}
				}

				fclose(fp);
				fwrite(voo, sizeof(voo), 1, fp3);

				i++;

				clrscr();
			}
		}
		else
		{
			i++;
		}
		printf("\nInserir outro Voo?\n ");
		printf("1 - Sim   2 - Não\n");
		scanf("%d", &decisao);

		if (decisao != 1 && decisao != 2)
		{
			do {
				clrscr();
				printf("Opção inválida\n ");
				printf("Inserir outra Voo?\n ");
				printf("1 - Sim   2 - Não\n");
				scanf("%d", &decisao);

			} while (decisao != 1 && decisao != 2);
		}



	} while (decisao != 2);
	fclose(fp3);

}
void ListarVoo() {
	int f = 0;
	FILE* fp3;
	fp3 = fopen("Voo.txt", "r");
	fread(voo, sizeof(voo), 1, fp3);
	for (int i = 0; i < 100; ++i)
	{
		if (voo[i].NumVoo != 0)
		{
			f++;
		}
	}
	for (int j = 0; j < f; ++j)
	{
		printf("Número do Voo: %d\n", voo[j].NumVoo);
		printf("Partida: %d/%d/%d %d:%dm\n", voo[j].Partida.Dia, voo[j].Partida.Mes, voo[j].Partida.Ano, voo[j].Partida.Horas, voo[j].Partida.Minutos);
		printf("Chegada: %d/%d/%d %d:%dm\n", voo[j].Chegada.Dia, voo[j].Chegada.Mes, voo[j].Chegada.Ano, voo[j].Chegada.Horas, voo[j].Chegada.Minutos);
		printf("Origem: %s\n", voo[j].Origem);
		printf("Destino: %s \n", voo[j].Destino);
		printf("Avião: %d \n", voo[j].Aviao);
		printf("Lugares Restantes: %d \n", voo[j].LugRestantes);
		printf("Total Lugares: %d \n\n", voo[j].TotalLug);


	}
	fclose(fp3);
	getchar();
}
void ModificarVoo() {
	int cod;
	int nVoo = 0;
	printf("Insira o código do voo a modificar: ");
	scanf("%d", &cod);

	FILE* fp3;
	fp3 = fopen("Voo.txt", "w");
	fread(voo, sizeof(voo), 1, fp3);

	for (int i = 0; i < 100; i++)
	{
		if (voo[i].NumVoo == cod && cod != 0)
		{
			nVoo = 1;
			clrscr();
			printf("Inserir Dia de Partida: \n");
			scanf("%d", &voo[i].Partida.Dia);
			printf("Inserir Mês de Partida: \n");
			scanf("%d", &voo[i].Partida.Mes);
			printf("Inserir Ano de Partida: \n");
			scanf("%d", &voo[i].Partida.Ano);
			printf("Inserir Hora de Partida: \n");
			scanf("%d", &voo[i].Partida.Horas);
			printf("Inserir Minutos de Partida: \n");
			scanf("%d", &voo[i].Partida.Minutos);

			printf("Inserir Dia de Chegada: \n");
			scanf("%d", &voo[i].Chegada.Dia);
			printf("Inserir Mês de Chegada: \n");
			scanf("%d", &voo[i].Chegada.Mes);
			printf("Inserir Ano de Chegada: \n");
			scanf("%d", &voo[i].Chegada.Ano);
			printf("Inserir Hora de Chegada: \n");
			scanf("%d", &voo[i].Chegada.Horas);
			printf("Inserir Minutos de Chegada: \n");
			scanf("%d", &voo[i].Chegada.Minutos);

			printf("Inserir Origem do Voo: \n");
			scanf("%s", &voo[i].Origem);

			printf("Inserir Destino: \n");
			scanf("%s", &voo[i].Destino);

			printf("Inserir Aviao: \n");
			scanf("%d", &voo[i].Aviao);
			fwrite(voo, sizeof(voo), 1, fp3);
		}
	}
	if (nVoo != 0) {
		printf("\nVoo modificado com sucesso\n");
	}
	else {
		printf("\nNão existe um Voo com esse número\n");
	}
	fclose(fp3);
	printf("\nPrima enter para continuar\n");
	getchar();
}
void RemoverVoo() {
	FILE* fp3;
	fp3 = fopen("Voo.txt", "w");
	fread(voo, sizeof(voo), 1, fp3);
	int cod, remove = -1;
	int nVoos = 0;
	printf("Insira o código do Voo a retirar: ");
	scanf("%d", &cod);

	//Procura o código na lista
	for (int i = 0; i < 100; i++)
	{
		if (voo[i].NumVoo == cod && cod != 0)
		{
			nVoos = 1;
			remove = i;
			break;
		}

	}
	if (nVoos != 1) {
		printf("\nNão existe uma Bilhete com esse código de registo\n");
	}
	//Puxa todos os elementos após o retirado 1 casa para a esquerda
	if (remove != -1)
	{

		for (int i = remove; i < 100 - 1; i++)
		{

			voo[i] = voo[i + 1];
			fwrite(voo, sizeof(voo), 1, fp3);


		}
		printf("\nVoo id %d removido com sucesso\n", cod);
	}
	fclose(fp3);

	printf("\nPrima enter para continuar\n");
	getchar();
}
void ProcurarVoo() {
	int cod, f = 0;
	FILE* fp3;
	fp3 = fopen("Voo.txt", "r");
	fread(voo, sizeof(voo), 1, fp3);

	printf("Insira o código do Voo a procurar: ");
	scanf("%d", &cod);
	for (int i = 0; i < 100; ++i)
	{
		if (voo[i].NumVoo != 0)
		{
			f++;
		}
	}
	for (int j = 0; j < f; ++j)
	{
		if (voo[j].NumVoo == cod)
		{
			printf("Número do Voo: %d\n", voo[j].NumVoo);
			printf("Partida: %d/%d/%d %d:%dm\n", voo[j].Partida.Dia, voo[j].Partida.Mes, voo[j].Partida.Ano, voo[j].Partida.Horas, voo[j].Partida.Minutos);
			printf("Chegada: %d/%d/%d %d:%dm\n", voo[j].Chegada.Dia, voo[j].Chegada.Mes, voo[j].Chegada.Ano, voo[j].Chegada.Horas, voo[j].Chegada.Minutos);
			printf("Origem: %s\n", voo[j].Origem);
			printf("Destino: %s \n", voo[j].Destino);
			printf("Aviao: %d \n\n", voo[j].Aviao);
			printf("Lugares Restantes: %d \n\n", voo[j].LugRestantes);
			printf("Total Lugares: %d \n\n", voo[j].TotalLug);


		}
	}
	fclose(fp3);
	getchar();
}


struct Bilhete {
	int NumID;
	char Passageiro[100];
	//Voo
	int Voo;
	int Lugar;
	double Preco;
	double Distancia;
} bilhete[100];
void InserirBilhete() {
	FILE* fp4;
	FILE* fp3;
	int choice;
	printf("Quer criar um novo ficheiro?\n");
	printf("1 - Sim   2 - Não\n");
	scanf("%d", &choice);
	do
		if (choice == 1)
		{
			fp4 = fopen("Bilhete.txt", "w");
		}
		else
		{
			fp4 = fopen("Bilhete.txt", "r");
			fread(bilhete, sizeof(bilhete), 1, fp4);
			fclose(fp4);
			fp4 = fopen("Bilhete.txt", "r+");
		}
	while (choice != 1 && choice != 2);
	int decisao = 0;
	static int i = 0;
	//O valor de i nunca se altera mesmo que se volte a usar esta função
	do
	{
		int vooTemp;
		int idTemp = 0;
		if (bilhete[i].NumID == 0)
		{
			clrscr();
			printf("Inserir ID");
			scanf("%d", &idTemp);
			for (int j = 0; j < 100; j++) {
				if (bilhete[j].NumID == idTemp && j != i) {
					printf("\nO ID já está em uso\n");
					bilhete[i].NumID = 0;
					break;
				}
			}
			if (idTemp != 0) {


				fp3 = fopen("Voo.txt", "r");
				fread(voo, sizeof(voo), 1, fp3);
				fp4 = fopen("Bilhete.txt", "r");
				fread(bilhete, sizeof(bilhete), 1, fp4);
				printf("Lista de códigos de Voos:\n");
				for (int j = 0; j < 100; j++) {
					if (voo[j].NumVoo != 0) {
						printf("Código: %d\n", voo[j].NumVoo);
					}
				}

				int check = 0;
				while (check == 0) {
					printf("\nInserir Código de Voo: \n");
					scanf("%d", &vooTemp);
					for (int j = 0; j < 100; j++) {
						if (vooTemp == voo[j].NumVoo && vooTemp != 0) {
							fp3 = fopen("Voo.txt", "w");

							voo[j].LugRestantes = voo[j].LugRestantes - 1;
							fwrite(voo, sizeof(voo), 1, fp3);
							check++;
						}
					}
					if (check != 0) {
						bilhete[i].Voo = vooTemp;
					}
					else {
						printf("Código de voo inválido\n");
					}
				}



				//Vai ver se existe voos com o mesmo número se existir coloca o mesmo preço e distancia se não pergunta.
				int existe = 0;
				for (int j = 0; j < 100; j++) {
					if (bilhete[j].Voo == bilhete[i].Voo && j != i) {
						bilhete[i].NumID = idTemp;
						bilhete[i].Preco = bilhete[j].Preco;
						bilhete[i].Distancia = bilhete[j].Distancia;
						existe = 1;
						fp4 = fopen("Bilhete.txt", "r+");
						printf("Inserir Passageiro: ");
						scanf("%s", &bilhete[i].Passageiro);
						printf("Inserir Lugar: ");
						scanf("%d", &bilhete[i].Lugar);
						fwrite(bilhete, sizeof(bilhete), 1, fp4);
					}
				}
				if (existe != 1) {
					bilhete[i].NumID = idTemp;

					printf("Inserir Passageiro: ");
					scanf("%s", &bilhete[i].Passageiro);
					printf("Inserir Lugar: ");
					scanf("%d", &bilhete[i].Lugar);

					printf("Inserir Preco: ");
					scanf("%lf", &bilhete[i].Preco);

					printf("Inserir Distancia: ");
					scanf("%lf", &bilhete[i].Distancia);
					fp4 = fopen("Bilhete.txt", "r+");
					fwrite(bilhete, sizeof(bilhete), 1, fp4);

				}



				i++;
				fclose(fp3);
				clrscr();
			}
		}
		else
		{
			i++;
		}
		printf("\nInserir outro Bilhete?\n ");
		printf("1 - Sim   2 - Não\n");
		scanf("%d", &decisao);

		if (decisao != 1 && decisao != 2)
		{
			do {
				clrscr();
				printf("Opção inválida\n ");
				printf("Inserir outri Bilhete?\n ");
				printf("1 - Sim   2 - Não\n");
				scanf("%d", &decisao);

			} while (decisao != 1 && decisao != 2);
		}



	} while (decisao != 2);

	fclose(fp4);

}
void ListarBilhete() {
	int f = 0;
	FILE* fp4;
	fp4 = fopen("Bilhete.txt", "r");
	fread(bilhete, sizeof(bilhete), 1, fp4);
	for (int i = 0; i < 100; ++i)
	{
		if (bilhete[i].NumID != 0)
		{
			f++;
		}
	}
	for (int j = 0; j < f; ++j)
	{
		printf("ID: %d\n", bilhete[j].NumID);
		printf("Passageiro: %s\n", bilhete[j].Passageiro);
		printf("Voo: %d\n", bilhete[j].Voo);
		printf("Lugar: %d\n", bilhete[j].Lugar);
		printf("Preço: %.2f Km/H\n", bilhete[j].Preco);
		printf("Distancia: %.2f L\n\n", bilhete[j].Distancia);
	}
	fclose(fp4);
	getchar();
}
/*void ModificarBilhete() {
	int cod;
	int nBilhete = 0;
	printf("Insira o código da Bilhete a modificar: ");
	scanf("%d", &cod);
	//Procura o código na lista
	FILE* fp4;
	fp4 = fopen("Bilhete.txt", "w");
	fread(Bilhete, sizeof(Bilhete), 1, fp4);

	for (int i = 0; i < 100; i++)
	{
		if (Bilhete[i].NumID == cod && cod != 0)
		{
			nBilhete = 1;
			clrscr();
			printf("Inserir ID: ");
			scanf("%d", &Bilhete[i].NumID);

			printf("Inserir Passageiro: ");
			scanf("%s", &Bilhete[i].Passageiro);

			printf("Inserir Voo: ");
			scanf("%d", &Bilhete[i].Voo);

			printf("Inserir Lugar: ");
			scanf("%d", &Bilhete[i].Lugar);

			printf("Inserir Preco: ");
			scanf("%lf", &Bilhete[i].Preco);

			printf("Inserir Distancia: ");
			scanf("%lf", &Bilhete[i].Distancia);
			fwrite(Bilhete, sizeof(Bilhete), 1, fp4);
		}
	}
	if (nBilhete != 0) {
		printf("\nBilhete modificado com sucesso\n");
	}
	else {
		printf("\nNão existe um Bilhete com esse ID\n");
	}
	fclose(fp4);
	printf("\nPrima enter para continuar\n");
	getchar();

}*/
void RemoverBilhete() {
	FILE* fp4;

	fp4 = fopen("Bilhete.txt", "w");

	fread(bilhete, sizeof(bilhete), 1, fp4);
	int cod, remove = -1;
	int nBilhetes = 0;
	printf("Insira o código do Bilhete a retirar: ");
	scanf("%d", &cod);
	int voo = 0;
	//Procura o código na lista
	for (int i = 0; i < 100; i++)
	{

		if (bilhete[i].NumID == cod && cod != 0)
		{
			nBilhetes = 1;
			remove = i;
			voo = bilhete[i].Voo;
			break;
		}

	}
	if (nBilhetes != 1) {
		printf("\nNão existe uma Bilhete com esse código de registo\n");
	}
	FILE* fp3;
	fp3 = fopen("Voo.txt", "r+");
	fread(voo, sizeof(voo), 1, fp3);
	//Puxa todos os elementos após o retirado 1 casa para a esquerda
	if (remove != -1)
	{

		for (int i = remove; i < 100 - 1; i++)
		{
			bilhete[i] = bilhete[i + 1];
			fwrite(bilhete, sizeof(bilhete), 1, fp4);

		}
		printf("\nBilhete id %d removido com sucesso\n", cod);
	}
	fclose(fp3);
	fclose(fp4);

	printf("\nPrima enter para continuar\n");
	getchar();
}
void ProcurarBilhete() {
	int cod, f = 0;
	FILE* fp4;
	fp4 = fopen("Bilhete.txt", "r");
	fread(bilhete, sizeof(bilhete), 1, fp4);

	printf("Insira o código da Bilhete a procurar: ");
	scanf("%d", &cod);
	for (int i = 0; i < 100; ++i)
	{
		if (bilhete[i].NumID != 0)
		{
			f++;
		}
	}
	for (int j = 0; j < f; ++j)
	{
		if (bilhete[j].NumID == cod)
		{
			printf("\nID: %d", bilhete[j].NumID);
			printf("\nPassageiro: %s", bilhete[j].Passageiro);
			printf("\nVoo: %d", bilhete[j].Voo);
			printf("\nLugar: %d", bilhete[j].Lugar);
			printf("\nPreco: %.2lf", bilhete[j].Preco);
			printf("\nDistancia: %.2lf\n\n", bilhete[j].Distancia);
		}
	}
	fclose(fp4);
	getchar();
}


void CustoLucro()
{
	int idvoo, numpass = 0, taxas = 5000, tripulacao = 400, lucro, horas = 0, galao = 207.09;
	float distancia = 0, preco = 0;
	double sec = 0;
	//Utiliza a biblioteca time.h
	struct tm start_date;
	struct tm end_date;
	time_t start_time, end_time;
	FILE* fp4;
	FILE* fp3;
	fp4 = fopen("Bilhete.txt", "r");
	fread(bilhete, sizeof(bilhete), 1, fp4);
	fp3 = fopen("Voo.txt", "r");
	fread(voo, sizeof(voo), 1, fp3);
	printf("Insira o Id do voo: ");
	scanf("%d", &idvoo);
	idvoo = idvoo - 1;

	for (int i = 0; i < 100; i++)
	{
		if (bilhete[i].Voo == voo[idvoo].NumVoo)
		{
			distancia = bilhete[i].Distancia;
			preco = bilhete[i].Preco;
			numpass = numpass + 1;

			start_date.tm_hour = voo[idvoo].Partida.Horas; start_date.tm_min = voo[idvoo].Partida.Minutos; start_date.tm_sec = 0;
			//Diferença de anos entre 1900 e o ano escolhido, a livraria time.h lê os meses a partir do 0
			start_date.tm_mon = voo[idvoo].Partida.Mes - 1; start_date.tm_mday = voo[idvoo].Partida.Dia; start_date.tm_year = voo[idvoo].Partida.Ano - 1900;

			end_date.tm_hour = voo[idvoo].Chegada.Horas; end_date.tm_min = voo[idvoo].Chegada.Minutos; end_date.tm_sec = 0;
			end_date.tm_mon = voo[idvoo].Chegada.Mes - 1; end_date.tm_mday = voo[idvoo].Chegada.Dia; end_date.tm_year = voo[idvoo].Chegada.Ano - 1900;

			start_time = mktime(&start_date);
			end_time = mktime(&end_date);

			//Diferença em segundos
			sec = difftime(end_time, start_time);
			horas = sec / 3600;
		}
	}

	int pagamentotripulacao = tripulacao * horas;
	lucro = numpass * preco;
	//km para milhas nauticas
	float milhas = distancia * 1.852;
	//1 galao por 51 milhas nauticas
	float numgaloes = milhas / 51;
	float dinheirogastoemgaloes = galao * numgaloes;

	float prejuizo = pagamentotripulacao + dinheirogastoemgaloes + taxas;
	float balance = lucro - prejuizo;

	if (balance < 0)
	{
		balance = -balance;
		printf("Houve um prejuizo de %.2f euros no voo %d", balance, voo[idvoo].NumVoo);
	}
	else
	{
		printf("Houve um lucro de %.2f euros no voo %d", balance, voo[idvoo].NumVoo);
	}
	fclose(fp4);
	fclose(fp3);
	getchar();
}


void AlterarAviao()
{
	int alterar = 0;
	int cheios = 0;
	char origemVoo[100];
	int nVoo;
	int possivel = 0;
	int troca = 0;
	int lugOcupados;
	int lugTotal;
	int lugRestantes;
	int lugOcupados2;
	int lugTotal2;
	int lugRestantes2;
	int aviaoTemp;
	int aviaoTemp2;

	FILE* fp3;


	fp3 = fopen("Voo.txt", "r");



	fread(voo, sizeof(voo), 1, fp3);

	for (int i = 0; i < 99; i++) {
		if (voo[i].NumVoo != 0 && voo[i].LugRestantes == 0) {
			printf("Voo com lotação cheia: %d\n", voo[i].NumVoo);
			cheios = 1;
		}
	}
	if (cheios != 0) {
		printf("Diga com qual voo quer trocar \n");
		scanf("%d", &alterar);
	}
	else {
		printf("Nenhum voo cheio");
	}

	for (int i = 0; i < 99; i++) {
		if (voo[i].NumVoo != 0 && voo[i].NumVoo == alterar) {

			for (int j = 0; j < 99; j++) {
				if (!strcmp(voo[i].Origem, voo[j].Origem) && voo[j].NumVoo != alterar && voo[j].LugRestantes != 0) {
					if (voo[j].Partida.Ano >= voo[i].Partida.Ano && voo[j].Partida.Mes >= voo[i].Partida.Mes && voo[j].Partida.Dia >= voo[i].Partida.Dia && voo[j].TotalLug > voo[i].TotalLug && voo[j].TotalLug - voo[j].LugRestantes <= voo[i].TotalLug) {
						printf("Estes são os aviões que podes alterar %d\n", voo[j].NumVoo);
						possivel = 1;
					}
				}
			}
		}
	}
	if (possivel != 0) {
		printf("Qual é o voo que pretendes alterar o avião?\n");
		scanf("%d", &troca);
	}
	for (int i = 0; i < 99; i++) {
		if (voo[i].NumVoo == troca) {
			lugOcupados = voo[i].TotalLug - voo[i].LugRestantes;
			lugTotal = voo[i].TotalLug;
			aviaoTemp = voo[i].Aviao;

		}
		if (voo[i].NumVoo == alterar) {
			lugOcupados2 = voo[i].TotalLug - voo[i].LugRestantes;
			lugTotal2 = voo[i].TotalLug;
			aviaoTemp2 = voo[i].Aviao;

		}
	}
	fp3 = fopen("Voo.txt", "w");
	for (int i = 0; i < 99; i++) {
		if (voo[i].NumVoo == troca) {
			voo[i].LugRestantes = lugTotal2 - lugOcupados;
			voo[i].TotalLug = lugTotal2;
			voo[i].Aviao = aviaoTemp;
		}
		if (voo[i].NumVoo == alterar) {
			voo[i].LugRestantes = lugTotal - lugOcupados2;
			voo[i].TotalLug = lugTotal;
			voo[i].Aviao = aviaoTemp2;

		}
	}
	fwrite(voo, sizeof(voo), 1, fp3);


	fclose(fp3);

	getchar();
}
void VooEscalado() {


	FILE* fp3;
	FILE* fp4;

	char origem[100];
	char destino[100];

	struct tm start_date;
	struct tm end_date;
	time_t start_time, end_time;
	struct Data Saida;
	struct Data Saida2;
	fp3 = fopen("Voo.txt", "r");
	fread(voo, sizeof(voo), 1, fp3);

	fp4 = fopen("Bilhete.txt", "r");
	fread(bilhete, sizeof(bilhete), 1, fp4);

	Saida.Dia = 0;
	Saida.Mes = 0;
	Saida.Ano = 0;
	Saida.Horas = 0;
	Saida.Minutos = 0;

	printf("Qual a origem do voo?\n");
	scanf("%s", origem);
	printf("Qual o destino do voo?\n");
	scanf("%s", destino);
	printf("Qual a data de saída? Dia/Mes/Ano Horas:Minutos\n");
	scanf("%d", &Saida.Dia);
	scanf("%d", &Saida.Mes);
	scanf("%d", &Saida.Ano);
	scanf("%d", &Saida.Horas);
	scanf("%d", &Saida.Minutos);

	printf("%s\n", origem);
	printf("%s\n", destino);

	printf("%d/%d/%d %d:%d\n", Saida.Dia, Saida.Mes, Saida.Ano, Saida.Horas, Saida.Minutos);

	start_date.tm_hour = Saida.Horas; start_date.tm_min = Saida.Minutos; start_date.tm_sec = 0;
	start_date.tm_mon = Saida.Mes - 1; start_date.tm_mday = Saida.Dia; start_date.tm_year = Saida.Ano - 1900;

	for (int i = 0; i < 99; i++) {

		int horas = 0;
		double sec = 0;

		if (!strcmp(voo[i].Origem, origem)) {
			char proxDestino[100];
			end_date.tm_hour = voo[i].Partida.Horas; end_date.tm_min = voo[i].Partida.Minutos; end_date.tm_sec = 0;
			end_date.tm_mon = voo[i].Partida.Mes - 1; end_date.tm_mday = voo[i].Partida.Dia; end_date.tm_year = voo[i].Partida.Ano - 1900;
			start_time = mktime(&start_date);
			end_time = mktime(&end_date);
			sec = difftime(end_time, start_time);
			horas = sec / 3600;

			//if (horas == 0) {
				//printf("Aviões para com essa Origem %d\n", voo[i].NumVoo);
			//}
			strcpy(proxDestino, voo[i].Destino);
			for (int j = 0; j < 99; j++) {
				if (!strcmp(voo[j].Origem, proxDestino)) {
					int precoTotal = 0;
					if (!strcmp(voo[j].Destino, destino)) {
						for (int l = 0; l < 99; l++) {
							if (bilhete[l].Voo == voo[i].NumVoo || bilhete[l].Voo == voo[j].NumVoo) {
								precoTotal += bilhete[l].Preco;
							}
						}
						printf("Voo %d -> Voo %d\n", voo[i].NumVoo, voo[j].NumVoo);
						printf("Por um preço total de %d\n", precoTotal);
					}
					//printf("De seguida pode apanhar o avião %d\n", voo[j].NumVoo);
					for (int k = 0; k < 99; k++) {
						int precoTotal = 0;
						if (!strcmp(voo[k].Origem, voo[j].Destino)) {
							if (strcmp(voo[k].Destino, destino)) {
								printf("De seguida ao aviao %d podes apanhar o avião %d\n", voo[j].NumVoo, voo[k].NumVoo);
							}
							else {

								for (int l = 0; l < 99; l++) {
									if (bilhete[l].Voo == voo[i].NumVoo || bilhete[l].Voo == voo[j].NumVoo || bilhete[l].Voo == voo[k].NumVoo) {
										precoTotal += bilhete[l].Preco;
									}
								}
								printf("Voo %d -> Voo %d -> Voo %d\n", voo[i].NumVoo, voo[j].NumVoo, voo[k].NumVoo);
								printf("Por um preço total de %d\n", precoTotal);
							}

						}
					}
				}
			}

		}
	}






	//Diferença em segundos
	//sec = difftime(end_time, start_time);
	//horas = sec / 3600;

	//printf("%d\n", horas);
	getchar();
}

int main(void)
{
	setlocale(LC_ALL, "Portuguese");

	int op = NULL;
	int escolha = NULL;
	printf("Bem Vindo ao IPCA AIRWAYS\t Prima Enter para continuar");
	do {
		getchar();
		clrscr();

		printf("\n\t......................IPCA AIRWAYS......................");
		printf("\n\n\t\t1-Gerir Frota de Aviões");
		printf("\n\n\t\t2-Gerir Aeroportos");
		printf("\n\n\t\t3-Gerir Voos");
		printf("\n\n\t\t4-Gerir Bilhetes");
		printf("\n\n\t\t5-Lucro");
		printf("\n\n\t\t6-Alterar aviões de voos cheios");
		printf("\n\n\t\t7-Ver voos com escala");


		scanf("%d", &op);

		switch (op) {
		case 1: {
			clrscr();
			printf("\n\n\t\t1-Inserir Frota");
			printf("\n\t\t2-Modificar Frota");
			printf("\n\t\t3-Listar Frota");
			printf("\n\t\t4-Remover Frota");
			printf("\n\t\t5-Procurar Frota");
			printf("\n\t\t0-Voltar atrás");
			printf("\n\t\t");
			scanf("%d", &escolha);
			switch (escolha) {

			case 1: {clrscr(); InserirFrota(); break; }
			case 2: {clrscr(); ModificarFrota(); break; }
			case 3: {clrscr(); ListarFrota(); break; }
			case 4: {clrscr(); RemoverFrota(); break; }
			case 5: {clrscr(); ProcurarFrota(); break; }
			}
			break;
		}
		case 2: {
			clrscr();
			printf("\n\n\t\t1-Inserir Aeroporto");
			printf("\n\t\t2-Modificar Aeroporto");
			printf("\n\t\t3-Listar Aeroporto");
			printf("\n\t\t4-Remover Aeroporto");
			printf("\n\t\t5-Procurar Aeroporto");
			printf("\n\t\t0-Voltar atrás");
			printf("\n\t\t");
			scanf("%d", &escolha);
			switch (escolha) {
			case 1: {clrscr(); InserirAeroporto(); break; }
			case 2: {clrscr(); ModificarAeroporto(); break; }
			case 3: {clrscr(); ListarAeroporto(); break; }
			case 4: {clrscr(); RemoverAeroporto(); break; }
			case 5: {clrscr(); ProcurarAeroporto(); break; }

			}
			break;
		}
		case 3: {
			clrscr();
			printf("\n\n\t\t1-Inserir Voo");
			printf("\n\t\t2-Modificar Voo");
			printf("\n\t\t3-Listar Voo");
			printf("\n\t\t4-Remover Voo");
			printf("\n\t\t5-Procurar Voo");
			printf("\n\t\t0-Voltar Atrás");
			printf("\n\t\t");
			scanf("%d", &escolha);
			switch (escolha) {
			case 1: {clrscr(); InserirVoo(); break; }
			case 2: {clrscr(); ModificarVoo(); break; }
			case 3: {clrscr(); ListarVoo(); break; }
			case 4: {clrscr(); RemoverVoo(); break; }
			case 5: {clrscr(); ProcurarVoo(); break; }

			}
			break;

		}
		case 4: {
			clrscr();
			printf("\n\n\t\t1-Inserir Bilhete");
			//printf("\n\t\t2-Modificar Bilhete");
			printf("\n\t\t2-Listar Bilhete");
			printf("\n\t\t3-Remover Bilhete");
			printf("\n\t\t4-Procurar Bilhete");
			printf("\n\t\t0-Voltar atrás");
			printf("\n\t\t");
			scanf("%d", &escolha);
			switch (escolha) {
			case 1: {clrscr(); InserirBilhete(); break; }
				  //case 2: {clrscr(); ModificarBilhete(); break; }
			case 2: {clrscr(); ListarBilhete(); break; }
			case 3: {clrscr(); RemoverBilhete(); break; }
			case 4: {clrscr(); ProcurarBilhete(); break; }

			}
			break;

		}
		case 5: {
			clrscr();
			CustoLucro();
			break;
		}
		case 6: {
			clrscr();
			AlterarAviao();
			break;
		}
		case 7: {
			clrscr();
			VooEscalado();
			break;
		}

		case 0: {
			break;
		}
		}
	} while (op != 0);
}