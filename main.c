#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include "biblioteca.h"
#include <time.h>
#include <ctype.h> 

#define tam_perguntas 255
#define tam_respostas 100

typedef struct jogador{
    char nome[20];
    int score;
}Jogador;

typedef struct perguntas {
    char pergunta[100][tam_perguntas]; //falta const
    char resposta[100][tam_perguntas];
    char tipo[100];
	char multiplaCorreta[100][tam_respostas];	
}Perguntas;

void randomPerguntas(FILE *perguntas, char arrayRandom[100][tam_perguntas]);
void instrucoes();
void adicionarQuestoes();
void fazerPerguntas(int op);
void separarRespostas(char linha[255], char opcoes[4][100]);
void baralharRespostas(char opcoes[4][100]);
//void tamanhoDoFicheiro(int op, int numeroLinhas);

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
	char sim;
		switch (op) 
		{
			case 1:
				system("cls");
				printf("As perguntas faceis sao de verdadeiro e falso\nQuer prosseguir com as faceis?  (s/n)");
				scanf(" %c", &sim);
				if (sim == 's' || sim == 'S')
					fazerPerguntas(op);
				else
					break;
			case 2:
				//system("cls");
				printf("As perguntas medias sao de escolha multipla\nQuer prosseguir com as medias?  (s/n)");
				scanf(" %c", &sim);
				if (sim == 's' || sim == 'S')
					fazerPerguntas(op);
				break;
			case 3: 
				//system("cls");
				printf("As perguntas dificeis sao de resposta numerica\nQuer prosseguir com as dificeis?  (s/n)");
				scanf(" %c", &sim);
				if (sim == 's' || sim == 'S')
					fazerPerguntas(op);
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
		printf("Escreva a pergunta que quer adicionar: \n");
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

void fazerPerguntas(int op){
	FILE *perguntas;

	if (op == 1)
		perguntas = fopen("perguntasfaceis.txt", "r");
	else if(op == 2)
		perguntas = fopen("perguntasmedias.txt", "r");
	else
		perguntas = fopen("perguntasdificeis.txt", "r");
		
	if (perguntas == NULL) { // testar se abriu
		perror("Erro ao abrir o ficheiro de perguntas médias");
		return;
	}
	Perguntas p; 
	char c;
	printf("As perguntas vao aparecer de forma aleatoria ate ao numero que selecionou\n");
	int numPerguntas = 0;
   	do {
   	 	printf("Quantas perguntas quer responder?\nResposta: ");
   		if(scanf("%d", &numPerguntas) == 1 && numPerguntas > 0)
		   break;
		while((c = getchar()) != '\n');
   		printf("\nInsira por favor um numero positivo :)\n");
	} while(1);
	char linha[tam_perguntas + tam_respostas + 5];
	char pergunta[tam_perguntas];
	char resposta1[tam_respostas];
	char resposta2[tam_respostas];
	char resposta3[tam_respostas];
	char resposta4[tam_respostas];
	char baralhado[100][tam_perguntas];

	randomPerguntas(perguntas, baralhado); //tive que baralhar antes de as copiar individualmente.
	//posso colocar numa função à parte também
	for (int i = 0; i < numPerguntas; i++){
		strncpy(linha, baralhado[i], tam_perguntas);
		linha[strcspn(linha, "\n")] = 0;
		p.tipo[i] = linha[0];  // Tipo da pergunta
		if (p.tipo[i] == '0' || p.tipo[i] == '1') {
			if (sscanf(linha + 1, "%255[^,],%[^\n]", pergunta, resposta1) == 2) {
				strncpy(p.pergunta[i], pergunta, tam_perguntas);
				strncpy(p.resposta[i], resposta1, tam_respostas);
				strncpy(p.multiplaCorreta[i], "nada", tam_respostas);
			}
		}
		else if (p.tipo[i] == '2') {
			if (sscanf(linha + 1, "%255[^,],%99[^,],%99[^,],%99[^,],%99[^\n]", pergunta, resposta1, resposta2, resposta3, resposta4) == 5) {
				snprintf(p.pergunta[i], tam_perguntas, "%s", pergunta);
				snprintf(p.resposta[i], tam_respostas, "%s,%s,%s,%s", resposta1, resposta2, resposta3, resposta4);
				strncpy(p.multiplaCorreta[i], resposta1, tam_respostas); // Resposta correta
			}
		}
	}
	int i = 0;
	while(i < numPerguntas) {
		printf("%d - Pergunta: %s... Resposta: %s ...", i + 1, p.pergunta[i], p.resposta[i]);
		printf("%s\n", p.multiplaCorreta[i]);
		i++;
	}

	int pontos = 0;
	char respostaVF;
	char respostaNumerica[tam_respostas];
	int respostaEscolhaMultipla = 0;
	for (int j = 0; j < numPerguntas; j++) {
		if(p.tipo[j] == '0') {
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
		else if(p.tipo[j] == '1') {
			printf("Pergunta %d: %s\n", j + 1, p.pergunta[j]);
			printf("Resposta: ");
			scanf(" %s", &respostaNumerica);
			if (strcmp(respostaNumerica, p.resposta[j]) == 0){
				printf("Acertouuu\n\n");
				pontos += 3;
			}
			else
				printf("Falhou\n\n");
		}
		else if (p.tipo[j] == '2') {
			printf("Pergunta %d: %s\n", j + 1, p.pergunta[j]);
			printf("Selecione a opcao correta!\n");
			char opcoes[4][100];
			separarRespostas(p.resposta[j], opcoes);
			baralharRespostas(opcoes); //baralhar as respostas

			for (int k = 0; k < 4; k++) 
				printf("%d. %s\n", k + 1, opcoes[k]);
			printf("Resposta: ");
			scanf(" %d", &respostaEscolhaMultipla); //recebo um int de resposta certa
			if (strcmp(p.multiplaCorreta[j], opcoes[respostaEscolhaMultipla -1]) == 0){
				printf("Acertou!!\n");
				pontos += 3;
			}
			else
				printf("Falhouuu\n");
		}
	}
}
void separarRespostas(char linha[255], char opcoes[4][100]){ //alterar nomes var
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

void baralharRespostas(char opcoes[4][100]) {
	for (int i = 3; i > 0; i--) {
		int j = rand() % (i + 1);

		char temp[100];
		strcpy(temp, opcoes[i]);
		strcpy(opcoes[i], opcoes[j]); 
		strcpy(opcoes[j], temp);
	}
}

void randomPerguntas(FILE *perguntas, char arrayRandom[100][tam_perguntas]) {
	char linha[tam_perguntas];
	srand(time(NULL));
    int i = 0;
	int numeroLinhas = 0;
    while (fgets(linha, sizeof(linha), perguntas))
    {
        strncpy(arrayRandom[i], linha, tam_perguntas);
        i++;
		numeroLinhas++;
    }
	printf("\n\n%d\n\n", numeroLinhas);
	for (int i = 0; i < numeroLinhas; i++) { 
		int j = rand() % (i + 1); 
		
		char tempPergunta[tam_perguntas];
		strncpy(tempPergunta, arrayRandom[i], tam_perguntas);
		strncpy(arrayRandom[i], arrayRandom[j], tam_perguntas);
		strncpy(arrayRandom[j], tempPergunta, tam_perguntas); 
	}
	i = 0;
	while (i < numeroLinhas)
	{
		printf("%s", arrayRandom[i]);
		i++;
	}
}
/*
void tamanhoDoFicheiro(int op, int numeroLinhas) {

	FILE *perguntas;
	if (op == 1)
		perguntas = fopen("perguntasfaceis.txt", "r");
	else if(op == 2)
		perguntas = fopen("perguntasmedias.txt", "r");
	else
		perguntas = fopen("perguntasdificeis.txt", "r");

	char linha[tam_perguntas];
	while (fgets(linha, sizeof(linha), perguntas) != NULL) {
		// Ignora linhas só com newline ou espaços
		if (linha[0] != '\n' && strlen(linha) > 1)
			numeroLinhas++;
	}
	fclose(perguntas);
}*/
//19/04 tentei baralhar depois de as dividir. má ideia
//randomPerguntas (p.pergunta, p.resposta, numPerguntas, p.multiplaCorreta); //Amanha Ver desta funçao 
/*void randomPerguntas(Perguntas *p, int numPerguntas){
 //função que não demos, dá reset ao rand() para que seja sempre random o baralhar
	for (int i = numPerguntas - 1; i > 0; i--) {
		int j = rand() % (i + 1); // vai definir o numero random
		
		char tempPergunta[tam_perguntas];
		strncpy(tempPergunta, perguntas[i], tam_perguntas); //aqui, ou usava pointers mas não demos, então com o string copy guardo aquela pergunta inicial numa variavel temporaria
		strncpy(perguntas[i], perguntas[j], tam_perguntas); //depois a pergunta selecionada pelo rand() é colocada na primeira posiçáo
		strncpy(perguntas[j], tempPergunta, tam_perguntas); // e a primeira pergunta é colocada no lugar da selecionada pelo rand
		
		char tempResposta[tam_respostas];
		strncpy(tempResposta, resposta[i], tam_respostas);
		strncpy(resposta[i], resposta[j], tam_respostas);
		strncpy(resposta[j], tempResposta, tam_respostas);

		char tempEscolhaMultipla[tam_respostas];
		strncpy(tempEscolhaMultipla, escolhaMultipla[i], tam_respostas);
		strncpy(escolhaMultipla[i], escolhaMultipla[j], tam_respostas);
		strncpy(escolhaMultipla[j], tempEscolhaMultipla, tam_respostas);

		char tempTipo;
		tempTipo= tipo[i];
		tipo[i] = tipo[j];
		tipo[j] = tempTipo;

		char temp[tam_perguntas];
        strcpy(temp, p->pergunta[i]);
        strcpy(p->pergunta[i], p->pergunta[j]);
        strcpy(p->pergunta[j], temp);
        
        // Trocar respostas
        strcpy(temp, p->resposta[i]);
        strcpy(p->resposta[i], p->resposta[j]);
        strcpy(p->resposta[j], temp);
        
        // Trocar tipos
        char tempTipo = p->tipo[i];
        p->tipo[i] = p->tipo[j];
        p->tipo[j] = tempTipo;
		}
}
*/
/*
void randomPerguntas(Perguntas *p, int numPerguntas) {
	srand(time(NULL));
	for (int i = numPerguntas - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		// Copiar dados para temp
		char tmpPergunta[tam_perguntas];
		strncpy(tmpPergunta, p->pergunta[i], tam_perguntas);
		strncpy(p->pergunta[i], p->pergunta[j], tam_perguntas);
		strncpy(p->pergunta[j], tmpPergunta, tam_perguntas);

		// Trocar resposta
		char tmpResposta[tam_respostas];
		strncpy(tmpResposta, p->resposta[i], tam_respostas);
		strncpy(p->resposta[i], p->resposta[j], tam_respostas);
		strncpy(p->resposta[j], tmpResposta, tam_respostas);

		// Trocar tipo
		char tmpTipo = p->tipo[i];
		p->tipo[i] = p->tipo[j];
		p->tipo[j] = tmpTipo;

		// Trocar multiplaCorreta (se for do tipo 2)
		char tmpMultipla[tam_respostas];
		strncpy(tmpMultipla, p->multiplaCorreta[i], tam_respostas);
		strncpy(p->multiplaCorreta[i], p->multiplaCorreta[j], tam_respostas);
		strncpy(p->multiplaCorreta[j], tmpMultipla, tam_respostas);
	}
}
*/

/*
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
		if (sscanf(linha, "%255[^,],%99[^\n]", pergunta, resposta) == 2) {
        	strncpy(p.pergunta[i], pergunta, tam_perguntas);
        	printf("%s\n", pergunta);
        	strncpy(p.resposta[i], resposta, tam_respostas);
        	printf("%s\n", resposta);
        	i++;
    	}
    }
    fclose(perguntas);
}
*/