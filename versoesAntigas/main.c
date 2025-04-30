#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include "biblioteca.h"
#include <time.h>
#include <ctype.h>
#include <locale.h> //serve de nada
#include <sys/stat.h>

#define tam_perguntas 255
#define tam_respostas 100

typedef struct jogador
{
	char nome[20];
	int pontuacao;
} Jogador;

typedef struct ranking
{ // vai servir apenas para guardar o ranking ordenado para o top 10
	Jogador jogadores[10];
	int numJogadores;
} Rank;

typedef struct perguntas
{
	char pergunta[100][tam_perguntas]; // falta const
	char resposta[100][tam_perguntas];
	char tipo[100];
	char multiplaCorreta[100][tam_respostas];
	char opcoes[4][tam_respostas];
} Perguntas;

void randomPerguntas(FILE *perguntas, char arrayRandom[100][tam_perguntas]);
void instrucoes();
void adicionarQuestoes();
void fazerPerguntas(int dificuldade, Jogador jogador);
void separarRespostas(char linha[255], char opcoes[4][100]);
void baralharRespostas(char opcoes[4][100]);
void historico();
void ordenarRank(char arrayTemp[100][255], int numLinhas);
int verificarJogador(Jogador jogador);

int main()
{
	printf("***********************************************\n");
	printf("*         Insira o seu nome ou nickname       *\n");
	printf("***********************************************\n");

	Jogador jogador;
	scanf(" %s", jogador.nome);
	int num = verificarJogador(jogador);
	jogador.pontuacao = 0;
	system("cls");
	int op;
	do
	{
		printf("**********************************************************\n");
		if (num == 0)
			printf("        Bem vindo %s\n", jogador.nome);
		else
			printf("        Bem vindo de volta %s\n", jogador.nome);
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
			printf("Vai ter várias perguntas de fácil dificuldade, mas que valem 1 ponto. Quer prosseguir (S/N) ?");
			scanf(" %c", &sim);
			if (sim == 's' || sim == 'S')
				fazerPerguntas(op, jogador);
			break;
		case 2:
			system("cls");
			printf("Vai ter várias perguntas de média dificuldade, mas que valem 3 pontos. Quer prosseguir? (S/N)");
			scanf(" %c", &sim);
			if (sim == 's' || sim == 'S')
				fazerPerguntas(op, jogador);
			break;
		case 3:
			system("cls");
			printf("Vai ter várias perguntas de grande dificuldade, mas que valem 5 pontos. Quer prosseguir? (S/N)");
			scanf(" %c", &sim);
			if (sim == 's' || sim == 'S')
				fazerPerguntas(op, jogador);
			break;
		case 4:
			instrucoes();
			break;
		case 5:
			historico();
			break;
		case 6:
			adicionarQuestoes();
			break;
		case 7:
			system("cls");
			if (contagem == 0)
				printf("Escolheu sair do programa. Obrigada na mesma! :)"); // questão de portugues
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
		while (getchar() != '\n');
	} while (op != 7);
}

int verificarJogador(Jogador jogador)
{
	FILE *historico = fopen("jogadores.txt", "r");
	if (!historico)
	{
		printf("Erro, não há historico de jogadores ainda!");
		return -2;
	}
	int flag = 0;
	char linha[255];
	char dataHora[100];
	char nomeHistorico[20];
	while (fgets(linha, sizeof(linha), historico))
	{
		if (sscanf(linha, "%99[^|]||%99[^|]", dataHora, nomeHistorico) == 2)
		{
			if (strcmp(nomeHistorico, jogador.nome) == 0)
			{
				flag = 1;
				break;
			}
		}
	}
	fclose(historico);
	return flag;
}

void instrucoes()
{
	printf("***********************************************************\n"); // alterar isto, veio do outro quiz
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

void adicionarQuestoes()
{
	char tipoPergunta;
	char c;
	printf("Qual é o nivel de dificuldade a que quer adicionar perguntas?\n (1) - Fácil   (2) - Médio   (3) - Díficil\n");
	printf("Escreva (1), (2) ou (3) consoante a dificuldade que pretende\nResposta: ");
	int tipoDificuldade;
	do
	{
		if (scanf("%d", &tipoDificuldade) != 1)
		{
			while (getchar() != '\n');
			printf("Tem de ser um dos numeros elencados\nEscolha por favor (1), (2), (3)");
		}
		else if ((tipoDificuldade == 1) || (tipoDificuldade == 2) || (tipoDificuldade == 3))
			break;
	} while (1);
	printf("%d", tipoDificuldade);
	while (1)
	{
		printf("Que tipo de perguntas quer acrescentar?\n Numerica (N)     V/F (V)    Escolha Multipla (E)");
		while ((c = getchar()) != '\n');
		tipoPergunta = getchar();
		tipoPergunta = toupper(tipoPergunta);
		if (tipoPergunta == 'N' || tipoPergunta == 'V' || tipoPergunta == 'E')
			break;
		printf("Caracter invalido! Experimente outro por favor");
		Sleep(2000);
		system("cls");
	}
	int tipoPerguntaFicheiro = 0;
	if (tipoPergunta == 'V')
		tipoPerguntaFicheiro = '0';
	else if (tipoPergunta == 'N')
		tipoPerguntaFicheiro = '1';
	else
		tipoPerguntaFicheiro = '2';
	char perguntaAdicionar[tam_perguntas];
	int respostaAdicionarNum = 0;
	char respostaAdicionarChar;
	char respostaAdicionarString[4][tam_respostas];
	if (tipoPergunta == 'N')
	{
		while ((c = getchar()) != '\n');
		printf("Escreva a pergunta que quer adicionar\n");
		scanf(" %[^\n]", perguntaAdicionar);
		// tamanhoPerguntaAdicionar = strlen(perguntaAdicionar); 
		// if (perguntaAdicionar[tamanhoPerguntaAdicionar - 1] != '?')
		printf("Qual é a resposta certa? Sendo uma pergunta numerica, por favor coloque um numero");
		while (1)
		{
			while (getchar() != '\n');
			if (scanf(" %d", &respostaAdicionarNum) == 1)
				break;
			printf("Nao e um numero! Por favor coloque um numero valido");
		}
	}
	else if (tipoPergunta == 'V')
	{
		while ((c = getchar()) != '\n');
		printf("Escreva a pergunta quer adicionar: \n");
		scanf(" %[^\n]", perguntaAdicionar);
		printf("Qual é a resposta certa? Sendo uma pergunta de verdadeiro/falso, por favor coloque um V ou F\n");
		while (1)
		{
			scanf(" %c", &respostaAdicionarChar);
			respostaAdicionarChar = toupper(respostaAdicionarChar);
			if (respostaAdicionarChar == 'V' || respostaAdicionarChar == 'F')
				break;
			printf("Nao e um caracter valido! Por favor coloque V ou F :( \n");
		}
	}
	else
	{
		printf("Escreva a pergunta que quer adicionar: \n");
		scanf(" %[^\n]", perguntaAdicionar);
		printf("Qual é a resposta certa? Sendo uma pergunta de escolha multipla, por favor coloque 1 a opcao correta\ne depois pode colocar as falsas perfazer as 4");
		int numRespostas = 0;
		int i = 0;
		while (numRespostas <= 3)
		{
			printf("\nOpcao %i", i + 1);
			scanf(" %[^\n]", respostaAdicionarString[i]);
			i++;
			numRespostas++;
		}
	}
	if (tipoPergunta == 'V')
	{ // se eu meter o file com o msemo nome não preciso disto tudo
		if (tipoDificuldade == 1)
		{
			FILE *perguntasVerdadeiroFalso = fopen("perguntasfaceis.txt", "a");
			fprintf(perguntasVerdadeiroFalso, "%c%s,%c\n", tipoPerguntaFicheiro, perguntaAdicionar, respostaAdicionarChar);
			fclose(perguntasVerdadeiroFalso);
		}
		else if (tipoDificuldade == 2)
		{
			FILE *perguntasVerdadeiroFalso = fopen("perguntasmedias.txt", "a");
			fprintf(perguntasVerdadeiroFalso, "%c%s,%c\n", tipoPerguntaFicheiro, perguntaAdicionar, respostaAdicionarChar);
			fclose(perguntasVerdadeiroFalso);
		}
		else
		{
			FILE *perguntasVerdadeiroFalso = fopen("perguntasdificeis.txt", "a");
			fprintf(perguntasVerdadeiroFalso, "%c%s,%c\n", tipoPerguntaFicheiro, perguntaAdicionar, respostaAdicionarChar);
			fclose(perguntasVerdadeiroFalso);
		}
	}
	else if (tipoPergunta == 'N')
	{
		if (tipoDificuldade == 1)
		{
			FILE *perguntasNumericas = fopen("perguntasfaceis.txt", "a");
			fprintf(perguntasNumericas, "%c%s,%d\n", tipoPerguntaFicheiro, perguntaAdicionar, respostaAdicionarNum);
			fclose(perguntasNumericas);
		}
		else if (tipoDificuldade == 2)
		{
			FILE *perguntasNumericas = fopen("perguntasmedias.txt", "a");
			fprintf(perguntasNumericas, "%c%s,%d\n", tipoPerguntaFicheiro, perguntaAdicionar, respostaAdicionarNum);
			fclose(perguntasNumericas);
		}
		else
		{
			FILE *perguntasNumericas = fopen("perguntasdificeis.txt", "a");
			fprintf(perguntasNumericas, "%c%s,%d\n", tipoPerguntaFicheiro, perguntaAdicionar, respostaAdicionarNum);
			fclose(perguntasNumericas);
		}
	}
	else
	{
		if (tipoDificuldade == 1)
		{
			FILE *perguntasEscolhaMultipla = fopen("perguntasfaceis.txt", "a");
			fprintf(perguntasEscolhaMultipla, "%s,%s,%s,%s,%s\n", perguntaAdicionar, respostaAdicionarString[0], respostaAdicionarString[1], respostaAdicionarString[2], respostaAdicionarString[3]);
			fclose(perguntasEscolhaMultipla);
		}
		else if (tipoDificuldade == 2)
		{
			FILE *perguntasEscolhaMultipla = fopen("perguntasmedias.txt", "a");
			fprintf(perguntasEscolhaMultipla, "%s,%s,%s,%s,%s\n", perguntaAdicionar, respostaAdicionarString[0], respostaAdicionarString[1], respostaAdicionarString[2], respostaAdicionarString[3]);
			fclose(perguntasEscolhaMultipla);
		}
		else
		{
			FILE *perguntasEscolhaMultipla = fopen("perguntasdificeis.txt", "a");
			fprintf(perguntasEscolhaMultipla, "%s,%s,%s,%s,%s\n", perguntaAdicionar, respostaAdicionarString[0], respostaAdicionarString[1], respostaAdicionarString[2], respostaAdicionarString[3]);
			fclose(perguntasEscolhaMultipla);
		}
	}
}

void fazerPerguntas(int dificuldade, Jogador jogador)
{
	FILE *perguntas;

	if (dificuldade == 1)
		perguntas = fopen("perguntasfaceis.txt", "r");
	else if (dificuldade == 2)
		perguntas = fopen("perguntasmedias.txt", "r");
	else
		perguntas = fopen("perguntasdificeis.txt", "r");

	if (perguntas == NULL)
	{ // estar se abriut
		perror("Erro ao abrir o ficheiro de perguntas médias");
		return;
	}
	Perguntas p;
	char c;
	printf("As perguntas vao aparecer de forma aleatoria ate ao numero que selecionou\n");
	int numPerguntas = 0;
	do
	{
		printf("Quantas perguntas quer responder?\nResposta: ");
		if (scanf("%d", &numPerguntas) == 1 && numPerguntas > 0)
			break;
		while ((c = getchar()) != '\n');
		printf("\nInsira por favor um numero positivo :)\n");
	} while (1);
	char linha[tam_perguntas + tam_respostas + 5];
	char pergunta[tam_perguntas];
	char resposta1[tam_respostas];
	char resposta2[tam_respostas];
	char resposta3[tam_respostas];
	char resposta4[tam_respostas];
	char baralhado[100][tam_perguntas];

	randomPerguntas(perguntas, baralhado); // tive que baralhar antes de as copiar individualmente.
	// posso colocar numa função à parte também
	for (int i = 0; i < numPerguntas; i++)
	{
		strncpy(linha, baralhado[i], tam_perguntas);
		linha[strcspn(linha, "\n")] = 0;
		p.tipo[i] = linha[0]; // Tipo da pergunta
		if (p.tipo[i] == '0' || p.tipo[i] == '1')
		{
			if (sscanf(linha + 1, "%255[^,],%[^\n]", pergunta, resposta1) == 2)
			{
				strncpy(p.pergunta[i], pergunta, tam_perguntas);
				strncpy(p.resposta[i], resposta1, tam_respostas);
				strncpy(p.multiplaCorreta[i], "nada", tam_respostas);
			}
		}
		else if (p.tipo[i] == '2')
		{
			if (sscanf(linha + 1, "%255[^,],%99[^,],%99[^,],%99[^,],%99[^\n]", pergunta, resposta1, resposta2, resposta3, resposta4) == 5)
			{
				snprintf(p.pergunta[i], tam_perguntas, "%s", pergunta);
				snprintf(p.resposta[i], tam_respostas, "%s,%s,%s,%s", resposta1, resposta2, resposta3, resposta4);
				strncpy(p.multiplaCorreta[i], resposta1, tam_respostas); // Resposta correta
			}
		}
	}
	char respostaVF;
	char respostaNumerica[tam_respostas];
	int respostaEscolhaMultipla = 0;
	for (int j = 0; j < numPerguntas; j++)
	{
		printf("Pergunta %d/%d - Pontos: %d \n", j + 1, numPerguntas, jogador.pontuacao);
		printf("%s\n", p.pergunta[j]);
		if (p.tipo[j] == '0')
		{
			while (1)
			{
				printf("Resposta: ");
				scanf(" %c", &respostaVF);
				if (respostaVF == 'V' || respostaVF == 'F')
					break;
				while (getchar() != '\n')
					;
				printf("Nao e um caracter valido! Por favor coloque V ou F :( \n");
			}
			respostaVF = toupper(respostaVF);
			if (respostaVF == 'V' || respostaVF == 'F')
			{
				if (respostaVF == p.resposta[j][0])
				{
					printf("Acertou!\n");
					if (dificuldade == 1)
					jogador.pontuacao += 1;
					else if (dificuldade == 2)
					jogador.pontuacao += 2;
					else if (dificuldade == 3)
					jogador.pontuacao += 3;
				}
				else
					printf("Falhou\n");
			}
		}
		else if (p.tipo[j] == '1')
		{
			while (1)
			{
				while (getchar() != '\n');
				printf("Resposta: ");
				if (scanf(" %d", &respostaNumerica) == 1)
					break;
				printf("Nao e um numero! Por favor coloque um numero valido\n");
			}
			if (strcmp(respostaNumerica, p.resposta[j]) == 0)
			{
				printf("Acertouuu\n\n");
				if (dificuldade == 1)
				jogador.pontuacao += 2;
				else if (dificuldade == 2)
				jogador.pontuacao += 3;
				else if (dificuldade == 3)
				jogador.pontuacao += 4;
			}
			else
				printf("Falhou\n\n");
		}
		else if (p.tipo[j] == '2')
		{
			char opcoes[4][100];
			separarRespostas(p.resposta[j], opcoes);
			baralharRespostas(opcoes); // baralhar as respostas
			for (int k = 0; k < 4; k++)
				printf("%d. %s\n", k + 1, opcoes[k]);
			while(1) {
				printf("Resposta: ");
				scanf(" %d", &respostaEscolhaMultipla); // recebo um int de resposta certa
				if (respostaEscolhaMultipla >= 1 && respostaEscolhaMultipla <= 4)
					break;
				printf("Tem de inserir uma opção válida, por favor\n");
				while (getchar() != '\n');
			}
			if (strcmp(p.multiplaCorreta[j], opcoes[respostaEscolhaMultipla - 1]) == 0)
			{
				printf("Acertou!!\n");
				if (dificuldade == 1)
				jogador.pontuacao += 3;
				else if (dificuldade == 2)
				jogador.pontuacao += 4;
				else if (dificuldade == 3)
				jogador.pontuacao += 5;
			}
			else
				printf("Falhouuu\n");
		}
	}
	FILE *nomejogador = fopen("jogadores.txt", "a");
	time_t agora = time(NULL);
	struct tm *t = localtime(&agora); // https://stackoverflow.com/questions/25030055/add-date-and-time-to-a-file-name-in-c
	char dataHora[100];
	strftime(dataHora, sizeof(dataHora), "%Y-%m-%d %H:%M:%S", t);
	fprintf(nomejogador, "%s||%s||%d\n", dataHora, jogador.nome, jogador.pontuacao);
	fclose(nomejogador);
}

void separarRespostas(char linha[255], char opcoes[4][100])
{				 // alterar nomes var
	int i = 0;	 // index
	int res = 0; // resposta
	int caracter = 0;
	while (res < 4 && linha[i] != '\0')
	{
		if (linha[i] == ',')
		{
			opcoes[res][caracter] = '\0'; // para meter nulo para terminar a string
			res++;						  // avançar na resposta
			caracter = 0;				  // voltar ao primeiro caracter
		}
		else
			opcoes[res][caracter++] = linha[i]; // copiar o que esta na linha para a opcao
		i++;
	}
	opcoes[res][caracter] = '\0';
}

void baralharRespostas(char opcoes[4][100])
{
	for (int i = 3; i > 0; i--)
	{
		int j = rand() % (i + 1);

		char temp[100];
		strcpy(temp, opcoes[i]);
		strcpy(opcoes[i], opcoes[j]);
		strcpy(opcoes[j], temp);
	}
}

void randomPerguntas(FILE *perguntas, char arrayRandom[100][tam_perguntas])
{
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
	for (int i = 0; i < numeroLinhas; i++)
	{
		int j = rand() % (i + 1);

		char tempPergunta[tam_perguntas];
		strncpy(tempPergunta, arrayRandom[i], tam_perguntas);
		strncpy(arrayRandom[i], arrayRandom[j], tam_perguntas);
		strncpy(arrayRandom[j], tempPergunta, tam_perguntas);
	}
	i = 0;
}

void historico()
{
	FILE *historico = fopen("jogadores.txt", "r");
	if (!historico)
	{
		printf("Erro, não há historico de jogadores ainda!");
		return;
	}
	char arrayTemp[100][255];
	char jogadorAtributos[255];
	int i = 0;
	int numLinhas = 0;
	char resposta;
	while (1)
	{
		printf("Pretende ver o historico de todos os jogadores? (S/N)\nResposta:  ");
		scanf(" %c", &resposta);
		resposta = toupper(resposta);
		if (resposta == 'S' || resposta == 'N')
			break;
		printf("Por favor coloque S ou N");
	}
	while (fgets(jogadorAtributos, sizeof(jogadorAtributos), historico))
	{
		strncpy(arrayTemp[i], jogadorAtributos, tam_perguntas);
		i++;
		numLinhas++;
	}
	i = 0;
	if (resposta == 'S')
	{
		while (i < numLinhas)
		{
			printf("%d : %s\n", i, arrayTemp[i]);
			i++;
		}
	}
	fclose(historico);
	while (1)
	{
		printf("Pretende ver o top 10 jogadores?\nResposta: ");
		scanf(" %c", &resposta);
		resposta = toupper(resposta);
		if (resposta == 'S' || resposta == 'N')
			break;
		printf("Por favor coloque S ou N");
	}
	if (resposta == 'S')
		ordenarRank(arrayTemp, numLinhas);
}

void ordenarRank(char arrayTemp[100][255], int numLinhas)
{
    Rank ranking;
    char nome[tam_respostas];
    int pontos = 0;
    int k = 0;
	char dataHora[20];
    for (int i = 0; i < numLinhas; i++)
    {
        if (sscanf(arrayTemp[i], "%[^|]||%[^|]||%d", dataHora, nome, &pontos) == 3)
        {
            strcpy(ranking.jogadores[k].nome, nome);
            ranking.jogadores[k].pontuacao = pontos;
            k++;
        }
    }
    ranking.numJogadores = k; 

    for (int i = 0; i < ranking.numJogadores - 1; i++)
    {
        for (int j = i + 1; j < ranking.numJogadores; j++)
        {
            if (ranking.jogadores[i].pontuacao < ranking.jogadores[j].pontuacao)
            {
                int tempPontos = ranking.jogadores[i].pontuacao;
                ranking.jogadores[i].pontuacao = ranking.jogadores[j].pontuacao;
                ranking.jogadores[j].pontuacao = tempPontos;

                char tempNome[tam_respostas];
                strcpy(tempNome, ranking.jogadores[i].nome);
                strcpy(ranking.jogadores[i].nome, ranking.jogadores[j].nome);
                strcpy(ranking.jogadores[j].nome, tempNome);
            }
            else if (ranking.jogadores[i].pontuacao == ranking.jogadores[j].pontuacao)
            {
                if (strcmp(ranking.jogadores[i].nome, ranking.jogadores[j].nome) > 0)
                {
                    char tempNome[tam_respostas];
                    strcpy(tempNome, ranking.jogadores[i].nome);
                    strcpy(ranking.jogadores[i].nome, ranking.jogadores[j].nome);
                    strcpy(ranking.jogadores[j].nome, tempNome);
                }
            }
        }
    }
	printf("Posicao    Nome          Pontuacao\n");
    for (int i = 0; i < ranking.numJogadores; i++)
		printf("%-10d%-20s%-10d\n", i+1, ranking.jogadores[i].nome, ranking.jogadores[i].pontuacao);
}
