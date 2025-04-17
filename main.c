#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include "biblioteca.h"
#include <time.h>
#include <ctype.h> 

#define tam_perguntas 255
#define tam_respostas 40

typedef struct jogador{
    char nome[20];
    int score;
}Jogador;

typedef struct perguntas
{
    char pergunta[100][tam_perguntas]; //falta const
    char resposta[100][tam_perguntas];
    char tipo[100];
	char multiplaCorreta[100][tam_respostas];	
}Perguntas;

void perguntasFaceis();
void randomPerguntas (char perguntas[100][tam_perguntas], char resposta[100][tam_respostas], int numPerguntas, char escolhaMultipla[100][tam_respostas]);
void instrucoes();
void adicionarQuestoes();
void perguntasMedias();
void separarRespostas(char linha[4], char opcoes[4][100]);

int main() {
    printf("***********************************************\n");
    printf("*         Insira o seu nome ou nickname       *\n");
    printf("***********************************************\n");
    
    Jogador jogador;
    scanf("%s", jogador.nome);
    system("cls");
	int op; 
    do {
    printf("**********************************************************\n");
    printf("                   Bem vindo %s\n", jogador.nome);
    printf("**********************************************************\n");

    printf("*********************************************************\n");
    printf("*          Selecione o numero da opcao que quer:        *\n");
    printf("*                                                       *\n");
    printf("*     Qual o nivel de dificuldade que pretende jogar:   *\n");
    printf("*       Inicial (1)     Medio (2)     Avancado (3)      *\n");
    printf("*                                                       *\n");
    printf("*        Instrucoes de utilizacao do quiz  (4)          *\n");
    printf("*                                                       *\n");
	printf("*            Historico e TOP 10 Jogadores  (5)          *\n");
    printf("*                                                       *\n");
	printf("*           Adicionar mais questoes ao quiz (6)         *\n");
	printf("*                                                       *\n");
    printf("*                 Sair do programa (7)                  *\n");
    printf("*********************************************************\n");
	
	int contagem = 0;
	scanf("%d", &op);
	srand(time(NULL));
	char sim;
		switch (op) 
		{
			case 1:
				system("cls");
				printf("As perguntas faceis sao de verdadeiro e falso\nQuer prosseguir com as faceis?  (s/n)");
				scanf(" %c", &sim);
				if (sim == 's' || sim == 'S')
					perguntasFaceis();
				else
					break;
			case 2:
				//system("cls");
				printf("As perguntas medias sao de escolha multipla\nQuer prosseguir com as medias?  (s/n)");
				scanf(" %c", &sim);
				if (sim == 's' || sim == 'S')
					perguntasMedias();
				break;
			case 3: 
				//system("cls");
				printf("As perguntas dificeis sao de resposta numerica\nQuer prosseguir com as dificeis?  (s/n)");
				scanf(" %c", &sim);
				//if (sim == 's' || sim == 'S')
				//else
				break;
			case 4:
				instrucoes();
				break;
			case 5:
			case 6:
				adicionarQuestoes();
				break;
			case 7:
				//system("cls");
				if(contagem == 0)
					printf("Escolheu sair do programa. Obrigada na mesma! :)"); //questão de portugues
				else if (contagem == 1)
					printf("Escolheu sair do programa. Obrigada por jogar 1 vez! :)");
				else
					printf("Escolheu sair do programa. Obrigada por jogar %d vezes! :)", contagem);
				return -1;   
			default:
				printf("\nOpcao Invalida\n");
				Sleep(1000);
				system("cls"); 
				printf("Escolha outra opcao, por favor\n");
				Sleep(2000);
				system("cls"); 
		}
	} while( op != '7');
	
    FILE *jogadores = fopen("jogador1.txt", "a");
    fprintf(jogadores, "\n%s", jogador.nome);
    fclose(jogadores);
}

void perguntasFaceis() {
	Perguntas p;
    int c;
    int numPerguntas;
   	do {
   	 	printf("Quantas perguntas quer responder?\nResposta: ");
   		if(scanf("%d", &numPerguntas) == 1 && numPerguntas > 0)
		   break;
		while((c = getchar()) != '\n');
   		printf("\nInsira por favor um numero positivo :)\n");
	} while(1);
	
	int i = 0;
	FILE *perguntas = fopen("perguntas.txt", "r");
	char linha[tam_perguntas + tam_respostas + 5];
	while (fgets(linha, sizeof(linha), perguntas) != NULL && i < numPerguntas) {
		linha[strcspn(linha, "\n")] = 0;
		
		char pergunta[tam_perguntas];
		char resposta[tam_respostas];
		if (sscanf(linha, "%255[^,],%99[^\n]", pergunta, resposta) == 2) { //Ver outra forma 
        	strncpy(p.pergunta[i], pergunta, tam_perguntas);
        	printf("%s\n", pergunta);
        	strncpy(p.resposta[i], resposta, tam_respostas);
        	printf("%s\n", resposta);
        	i++;
    	} else {
        	fprintf(stderr, "Linha inválida: %s\n", linha);
    	}
    }
    fclose(perguntas);
}
//randomPerguntas (p.pergunta, p.resposta, numPerguntas, p.multiplaCorreta); //Amanha Ver desta funçao 
void randomPerguntas (char perguntas[100][tam_perguntas], char resposta[100][tam_respostas], int numPerguntas, char escolhaMultipla[100][tam_respostas]){
 //função que não demos, dá reset ao rand() para que seja sempre random o baralhar
	for (int i = numPerguntas - 1; i > 0; i--) {
		int j = rand() % (i + 1); // vai definir o numero random

		char tempPergunta[tam_perguntas];
		strcpy(tempPergunta, perguntas[i]); //aqui, ou usava pointers mas não demos, então com o string copy guardo aquela pergunta inicial numa variavel temporaria
		strcpy(perguntas[i], perguntas[j]); //depois a pergunta selecionada pelo rand() é colocada na primeira posiçáo
		strcpy(perguntas[j], tempPergunta); // e a primeira pergunta é colocada no lugar da selecionada pelo rand
		
		char tempResposta[tam_respostas];
		strcpy(tempResposta, resposta[i]);
		strcpy(resposta[i], resposta[j]);
		strcpy(resposta[j], tempResposta);
	}
	for (int i = 0; i < 12; i++) {
		printf("%s\n", perguntas[i]);
	}
	for (int i = 0; i < 12; i++) {
		printf("%s\n", resposta[i]);
	}
	for (int i = 0; i < 12; i++) {
		printf("%s\n", escolhaMultipla[i]);
	}
}

void instrucoes() {
	printf("***********************************************************\n");
	printf("*      Escolha inicialmente a dificuldade pretendida      *\n");
	printf("*   Vao aparecer 10 questoes sobre a cultura portuguesa   *\n");
	printf("*               Todas de Verdadeiro ou Falso              *\n");
	printf("*          E so colocar 'V' ou 'v' para verdadeiro        *\n");
	printf("*          Ou entao 'F' ou 'f' se achar que e falsa       *\n");
	printf("***********************************************************\n");
	printf("\n\n          Pressione um botao para sair deste menu");
	getch();
	Sleep(1000);
	system("cls");	
}

void adicionarQuestoes() {
	char tipoPergunta;
	char c;
	//while(1){
	//	printf("Qual é o nivel de dificuldade a que quer adicionar perguntas?")
	//}
	while(1) {
		printf("Que tipo de perguntas quer acrescentar?\n Numerica (N)     V/F (V)    Escolha Multipla (E)");
		while((c = getchar()) != '\n');
		tipoPergunta = getchar();
		tipoPergunta = toupper(tipoPergunta);
		if(tipoPergunta == 'N' || tipoPergunta == 'V' || tipoPergunta == 'E') 
			break;
		printf("Caracter invalido! Experimente outro por favor");
		Sleep(2000);
		system("cls");
	}
	char perguntaAdicionar[tam_perguntas];
	int respostaAdicionarNum = 0;
	char respostaAdicionarChar;
	char respostaAdicionarString[4][tam_respostas];
	if (tipoPergunta == 'N'){
		while((c = getchar()) != '\n');
		printf("Escreva a pergunta que quer adicionar\n");
		scanf(" %[^\n]", perguntaAdicionar);
		//tamanhoPerguntaAdicionar = strlen(perguntaAdicionar);
		//if (perguntaAdicionar[tamanhoPerguntaAdicionar - 1] != '?')
		printf("Qual é a resposta certa? Sendo uma pergunta numerica, por favor coloque um numero");
		while(1) {
			if (scanf(" %d", &respostaAdicionarNum) == 1)
				break;
			printf("Nao e um numero! Por favor coloque um numero valido");
		}
		printf("Pergunta adicionada com sucesso! Obrigada :)");
		FILE *perguntasNumericas = fopen("perguntas.txt", "a");
		fprintf(perguntasNumericas, "%s,%d\n", perguntaAdicionar, respostaAdicionarNum);
		fclose(perguntasNumericas);
	}
	else if (tipoPergunta == 'V') {
		while((c = getchar()) != '\n');
		printf("Escreva a pergunta quer adicionar: \n");
		scanf(" %[^\n]", perguntaAdicionar);
		printf("Qual é a resposta certa? Sendo uma pergunta de verdadeiro/falso, por favor coloque um V ou F\n");
		while(1) {
			scanf(" %c", &respostaAdicionarChar);
			respostaAdicionarChar = toupper(respostaAdicionarChar);
			if (respostaAdicionarChar == 'V' || respostaAdicionarChar == 'F')
				break;
			printf("Nao e um caracter valido! Por favor coloque V ou F :( \n");
		}
		printf("Pergunta adicionada com sucesso! Obrigada :)");
		FILE *perguntasVerdadeiroFalso = fopen("perguntas.txt", "a");
		fprintf(perguntasVerdadeiroFalso, "%s,%c\n", perguntaAdicionar, respostaAdicionarChar);
		fclose(perguntasVerdadeiroFalso);
	}
	else {
		printf("Escreva a pergunta quer adicionar: \n");
		scanf(" %[^\n]", perguntaAdicionar);
		printf("Qual é a resposta certa? Sendo uma pergunta de escolha multipla, por favor coloque 1 a opcao correta\ne depois pode colocar as falsas perfazer as 4");
		int numRespostas = 0;
		int i = 0;
		while(numRespostas <= 3)
		{
			printf("\nOpcao %i", i + 1);
			scanf(" %[^\n]", respostaAdicionarString[i]);
			i++;
			numRespostas++;
		}
		FILE *perguntasEscolhaMultipla = fopen("perguntas.txt", "a");
		fprintf(perguntasEscolhaMultipla, "%s,%s,%s,%s,%s\n", perguntaAdicionar, respostaAdicionarString[0], respostaAdicionarString[1],respostaAdicionarString[2],respostaAdicionarString[3]);
		fclose(perguntasEscolhaMultipla);
	}
}

void perguntasMedias(){
	FILE *perguntasMedias = fopen("perguntasmedias.txt", "r");
	if (perguntasMedias == NULL) {
		perror("Erro ao abrir o ficheiro de perguntas médias");
		return;
	} 
	Perguntas p; 
	printf("Estas perguntas são de Media dificuldade, valem 3 pontos cada. Quer mesmo prosseguir?"); //S ou S
	char res;
	scanf(" %c", &res);
	res = tolower(res);
	if (res != 's')
		return;
	printf("As perguntas vao aparecer de forma aleatoria ate ao numero que selecionou");
	int numPerguntas = 0;
	char c;
   	do {
   	 	printf("Quantas perguntas quer responder?\nResposta: ");
   		if(scanf("%d", &numPerguntas) == 1 && numPerguntas > 0)
		   break;
		while((c = getchar()) != '\n');
   		printf("\nInsira por favor um numero positivo :)\n");
	} while(1);
	int i = 0;
	char linha[tam_perguntas + tam_respostas + 5];
	char pergunta[tam_perguntas];
	char resposta1[tam_respostas];
	char resposta2[tam_respostas];
	char resposta3[tam_respostas];
	char resposta4[tam_respostas];

	while (fgets(linha, sizeof(linha), perguntasMedias) != NULL && i < numPerguntas) {
		linha[strcspn(linha, "\n")] = 0; //nao

		p.tipo[i] = linha[0];

		if (p.tipo[i] == '0' || p.tipo[i] == '1') {
			if (sscanf(linha + 1, "%255[^,],%[^\n]", pergunta, resposta1) == 2) {
				strncpy(p.pergunta[i], pergunta, tam_perguntas);
				strncpy(p.resposta[i], resposta1, tam_respostas);
				i++;
			}
		} 
		else if (p.tipo[i] == '2') {
			if (sscanf(linha + 1, "%255[^,],%99[^,],%99[^,],%99[^,],%99[^\n]", pergunta, resposta1, resposta2, resposta3, resposta4) == 5) {
				snprintf(p.pergunta[i], tam_perguntas, "%s", pergunta); //alterar
				snprintf(p.resposta[i], tam_respostas, "%s,%s,%s,%s", resposta1, resposta2, resposta3, resposta4); //alterar
				strncpy(p.multiplaCorreta[i], resposta1, tam_respostas);
				i++;
			}
		}
	}
	randomPerguntas (p.pergunta, p.resposta, numPerguntas, p.multiplaCorreta);

	for( int i = 0; i < numPerguntas; i++) {
		printf("Pergunta: %s\n", p.pergunta[i]);
		printf("Resposta: %s\n", p.resposta[i]);
		printf("Tipo: %c\n", p.tipo[i]);
	}
	int pontos = 0;
	int k = 0;
	char respostaVF;
	char respostaNumerica[tam_respostas];
	int respostaEscolhaMultipla = 0;
	for (int j = 0; j < numPerguntas; j++) {
		if(p.tipo[k] == '0') {
			printf("Pergunta %d: %s\n", j + 1, p.pergunta[j]);
			printf("Resposta: ");
			scanf(" %c", &respostaVF);
			respostaVF = toupper(respostaVF);
			if (respostaVF == 'V' || respostaVF == 'F'){
				if(respostaVF == p.resposta[j][0]){
					printf("Acertou!\n");
					pontos += 3;
				}
				else 
					printf("Falhou\n");
			}
		}
		else if(p.tipo[k] == '1') {
			printf("Pergunta %d: %s\n", j + 1, p.pergunta[j]);
			printf("Resposta: ");
			scanf(" %s", &respostaNumerica);
			if (strcmp(respostaNumerica, p.resposta[j]) == 0){
				printf("Acertouuu");
				pontos += 3;
			}
			else
				printf("Falhou");
		}
		else if (p.tipo[k] == '2') {
			printf("Pergunta %d: %s\n", j + 1, p.pergunta[j]);
			printf("Selecione a opcao correta!\n");
			char opcoes[4][100];
			separarRespostas(p.resposta[j], opcoes);
			printf("Resposta correta: %s\n", p.multiplaCorreta[j]);
			for (int k = 0; k < 4; k++) 
				printf("%d. %s\n", k + 1, opcoes[k]);
			printf("Resposta: ");
			scanf(" %d", &respostaEscolhaMultipla);
			int respostaCerta = 1;
			if (respostaEscolhaMultipla == respostaCerta){
				printf("Acertou!!\n");
				pontos += 3;
			}
			else
				printf("Falhouuu\n");
		}
		k++;
	}
}
void separarRespostas(char linha[255], char opcoes[4][100]){ //altearar nomes var
	int i = 0; //index
	int res= 0; //resposta
	int caracter = 0;
	while(res < 4 && linha[i] != '\0') {
		if (linha[i] == ',') {
			opcoes[res][caracter] = '\0'; // para meter nulo para terminar a string
			res++; //avançar na resposta
			caracter = 0; //voltar ao primeiro caracter
		}
		else
			opcoes[res][caracter++] = linha[i]; //copiar o que esta na linha para a opcao
		i++;
	}
	opcoes[res][caracter] = '\0';
}