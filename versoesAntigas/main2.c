/* *************************************************** */
/*                                                     */
/*                                                     */
/*   Quiz Dinâmico                                     */
/*                                                     */
/*   By: leonor joaquim                                */
/*                                                     */
/*   Created: 2025/04/24 18:00:49 by leonor            */
/*   Updated: 2025/04/24 18:00:49 by leonor            */
/*   Trello: https://trello.com/b/w9xdOht9             */
/*                                                     */
/* *************************************************** */

#include "biblioteca.h"

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
			printf("           Bem vindo %s\n", jogador.nome);
		else
			printf("           Bem vindo de volta %s\n", jogador.nome);
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
			if (sim == 's' || sim == 'S') {
				fazerPerguntas(op, jogador);
				contagem++;
			}
			break;
		case 2:
			system("cls");
			printf("Vai ter várias perguntas de média dificuldade, mas que valem 3 pontos. Quer prosseguir? (S/N)");
			scanf(" %c", &sim);
			if (sim == 's' || sim == 'S') {
				fazerPerguntas(op, jogador);
				contagem++;
			}
			break;
		case 3:
			system("cls");
			printf("Vai ter várias perguntas de grande dificuldade, mas que valem 5 pontos. Quer prosseguir? (S/N)");
			scanf(" %c", &sim);
			if (sim == 's' || sim == 'S') {
				fazerPerguntas(op, jogador);
				contagem++;
			}
			break;
		case 4:
			instrucoes();
			break;
		case 5:
			historico(jogador);
			break;
		case 6:
			printf("Quer adicionar uma pergunta (P) ou adicionar um ficheiro txt (F)   (P/F)\nResposta: ");
			while(1)
			{
				scanf(" %c", &sim);
				sim = toupper(sim);
				if (sim == 'P' || sim == 'F')
					break;
				printf("Por favor coloque P ou F\nResposta: ");
			}
			if (sim == 'P')
				adicionarQuestoes();
			else if (sim == 'F')
				adicionarFicheiro();
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
	printf("Qual é o nivel de dificuldade a que quer adicionar perguntas?\n (1) - Facil   (2) - Medio   (3) - Dificil\n\n");
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
	while (1)
	{
		printf("Que tipo de perguntas quer acrescentar?\n\nNumerica (N)         V/F (V)        Escolha Multipla (E)");
		while ((c = getchar()) != '\n');
		tipoPergunta = getchar();
		tipoPergunta = toupper(tipoPergunta);
		if (tipoPergunta == 'N' || tipoPergunta == 'V' || tipoPergunta == 'E')
			break;
		printf("Caracter invalido! Experimente outro por favor");
	}
	int tipoPerguntaFicheiro = 0;
	if (tipoPergunta == 'V')    //Melhorar isto, não precisa de ser assim
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
			while (getchar() != '\n')
				;
			if (scanf(" %d", &respostaAdicionarNum) == 1)
				break;
			printf("Nao e um numero! Por favor coloque um numero valido");
		}
	}
	else if (tipoPergunta == 'V')
	{
		while ((c = getchar()) != '\n')
			;
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
	{
		perror("Erro ao abrir o ficheiro de perguntas");
		return;
	}

	Perguntas p[100]; //armazenar todas as perguntas
	char c;
	printf("As perguntas vão aparecer de forma aleatória até ao número que selecionou\n");
	int numPerguntas = 0;
	do
	{
		printf("Quantas perguntas quer responder?\nResposta: ");
		if (scanf("%d", &numPerguntas) == 1 && numPerguntas > 0)
			break;
		while ((c = getchar()) != '\n')
			;
		printf("\nInsira por favor um número positivo :)\n");
	} while (1);

	char baralhado[100][tam_perguntas];
	randomPerguntas(perguntas, baralhado);

	for (int i = 0; i < numPerguntas; i++)
	{
		char linha[tam_perguntas + tam_respostas * 4];
		strncpy(linha, baralhado[i], sizeof(linha));
		linha[strcspn(linha, "\n")] = 0;

		p[i].tipo = linha[0];

		if (p[i].tipo == '0' || p[i].tipo == '1')
		{
			sscanf(linha + 1, " %[^,],%[^\n]", p[i].pergunta, p[i].resposta);
		}
		else if (p[i].tipo == '2')
		{
			sscanf(linha + 1, " %[^,],%[^,],%[^,],%[^,],%[^\n]",
				   p[i].pergunta,
				   p[i].opcoes[0], p[i].opcoes[1],
				   p[i].opcoes[2], p[i].opcoes[3]);
			strcpy(p[i].multiplaCorreta, p[i].opcoes[0]); // assume que a 1ª é correta
		}
	}

	for (int j = 0; j < numPerguntas; j++)
	{
		printf("Pergunta %d/%d - Pontos: %d\n", j + 1, numPerguntas, jogador.pontuacao);
		printf("%s\n", p[j].pergunta);

		if (p[j].tipo == '0') // V/F
		{
			char respostaVF;
			while (1)
			{
				printf("Resposta (V/F): ");
				scanf(" %c", &respostaVF);
				respostaVF = toupper(respostaVF);
				if (respostaVF == 'V' || respostaVF == 'F')
					break;
				while (getchar() != '\n')
					;
				printf("Opção inválida, tente novamente.\n");
			}

			if (respostaVF == p[j].resposta[0])
			{
				printf("Acertou!\n");
				jogador.pontuacao += dificuldade;
			}
			else
				printf("Falhou.\n");
		}
		else if (p[j].tipo == '1') // numérica
		{
			char respostaNumerica[tam_respostas];
			while (1)
			{
				printf("Resposta (número): ");
				if (scanf(" %s", respostaNumerica) == 1)
					break;
				while (getchar() != '\n')
					;
				printf("Entrada inválida, tente novamente.\n");
			}
			if (strcmp(respostaNumerica, p[j].resposta) == 0)
			{
				printf("Acertou!\n");
				jogador.pontuacao += dificuldade + 1;
			}
			else
				printf("Falhou.\n");
		}
		else if (p[j].tipo == '2') // escolha múltipla
		{
			char opcoesTemp[4][tam_respostas];
			for (int k = 0; k < 4; k++)
				strcpy(opcoesTemp[k], p[j].opcoes[k]);

			baralharRespostas(opcoesTemp);

			for (int k = 0; k < 4; k++)
				printf("%d. %s\n", k + 1, opcoesTemp[k]);

			int escolha;
			while (1)
			{
				printf("Resposta (1-4): ");
				if (scanf(" %d", &escolha) == 1 && escolha >= 1 && escolha <= 4)
					break;
				while (getchar() != '\n')
					;
				printf("Opção inválida, tente novamente.\n");
			}

			if (strcmp(opcoesTemp[escolha - 1], p[j].multiplaCorreta) == 0)
			{
				printf("Acertou!\n");
				jogador.pontuacao += dificuldade + 2;
			}
			else
				printf("Falhou.\n");
		}
	}

	FILE *nomejogador = fopen("jogadores.txt", "a");
	time_t agora = time(NULL);
	struct tm *t = localtime(&agora);
	char dataHora[100];
	strftime(dataHora, sizeof(dataHora), "%Y-%m-%d %H:%M:%S", t);
	fprintf(nomejogador, "%s||%s||%d\n", dataHora, jogador.nome, jogador.pontuacao);
	fclose(nomejogador);

	historico(jogador);
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

void historico(Jogador jogador)
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
	while (fgets(jogadorAtributos, sizeof(jogadorAtributos), historico))
	{
		strncpy(arrayTemp[i], jogadorAtributos, tam_perguntas);
		i++;
		numLinhas++;
	}
	i = 0;
	i = 0;
	printf("Data e Hora        ||   Jogador	  ||  Pontuacao\n");   //acabar isto
	while (i < numLinhas)
	{
		char linhaTemp[255];
		strcpy(linhaTemp, arrayTemp[i]);

		char *token = strtok(linhaTemp, "||");
		token = strtok(NULL, "||");
		if (token && strcmp(token, jogador.nome) == 0)
			printf("%s", arrayTemp[i]); 
		i++;
	}
	fclose(historico);
	while (1)
	{
		printf("\nPretende ver o top 10 jogadores?\nResposta: ");
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
		printf("%-10d%-20s%-10d\n", i + 1, ranking.jogadores[i].nome, ranking.jogadores[i].pontuacao);
}

void adicionarFicheiro() {
	char ficheiroAdicionado[tam_respostas];
	printf("Nao se esqueca que o ficheiro das perguntas tem de ter o formato correto\n");
	printf("O formato correto e o seguinte (Exemplo):\n");
	printf("1Em que ano foi implementado o Euro em Portugal?,2002\n");
	printf("0O fado e considerado patrimonio imaterial da humanidade?,V\n2Qual destas comidas e típica portuguesa?,Feijoada a transmontana,Burrito,Hamburguer,Sushi\n");
	printf("\nEm que o primeiro numero indica o tipo de pergunta (0 V/F, 1 Numerica, 2 Escolha Multipla), seguido de uma pergunta e de uma resposta, estas duas separadas por uma virgula\n");
	printf("\n\nInsira, por favor, o nome do ficheiro que quer adicionar (com a extensao .txt)\nResposta: ");
	scanf(" %[^\n]", ficheiroAdicionado);
	FILE *perguntas1 = fopen(ficheiroAdicionado, "r");
	if (!perguntas1)
	{
		printf("Erro ao abrir o ficheiro\n");
		return;
	}
	printf("Ficheiro aberto com sucesso!\n");

	printf("As Perguntas novas que adicionou são de que dificuldade? (1)- Facil, (2) - Medio, (3) - Dificil\nResposta: ");
	int dificuldade;
	while(1) {
		scanf("%d", &dificuldade);
		if (dificuldade == 1 || dificuldade == 2 || dificuldade == 3)
			break;
		printf("Por favor coloque 1, 2 ou 3\nResposta: ");
	}
	FILE *perguntas;
    if (dificuldade == 1) {
        perguntas = fopen("perguntasfaceis.txt", "a");
    } else if (dificuldade == 2) {
        perguntas = fopen("perguntasmedias.txt", "a");
    } else {
        perguntas = fopen("perguntasdificeis.txt", "a");
    }
	char linha[255];
	while (fgets(linha, sizeof(linha), perguntas1)) {
		if (linha[strlen(linha) - 1] != '\n') {
            // Se não terminar com '\n', adicionamos um '\n'
            fprintf(perguntas, "%s\n", linha);
        } else {
            // Se já terminar com '\n', só escrevemos a linha
            fprintf(perguntas, "%s", linha);
        }
    }
	fclose(perguntas);
	fclose(perguntas1);
}