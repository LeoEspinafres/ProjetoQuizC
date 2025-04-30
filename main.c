/* *************************************************** */
/*                                                     */
/*                                                     */
/*   Quiz Dinâmico                                     */
/*                                                     */
/*   By: leonor joaquim                                */
/*                                                     */
/*   Created: 2025/04/28 10:27:49 by leonor            */
/*   Updated: 2025/04/28 10:27:49 by leonor            */
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
	int op;
    int contagem = 0;
	do
	{
		while (1) {
		limparEcra();
		printf("**********************************************************\n");
		if (num == 0)
			printf("              Bem vindo %s\n", jogador.nome);
		else
			printf("              Bem vindo de volta %s\n", jogador.nome);
		printf("**********************************************************\n");

		printf("*********************************************************\n");
		printf("*          Selecione o numero da opcao que quer:        *\n");
		printf("*                                                       *\n");
		printf("*     Qual o nivel de dificuldade que pretende jogar:   *\n");
		printf("*                                                       *\n");
		printf("*                1. Inicial                             *\n");
		printf("*                2. Medio                               *\n");
		printf("*                3. Avancado                            *\n");
		printf("*                                                       *\n");
		printf("*          4. Instrucoes de utilizacao do quiz          *\n");
		printf("*          5. Historico e TOP 10 Jogadores              *\n");
		printf("*          6. Adicionar mais questoes ao quiz           *\n");
		printf("*          7. Sair do programa                          *\n");
		printf("*********************************************************\n");
		printf("\nOpcao Escolhida: ");
			if (scanf("%d", &op) == 1) {
				if (op >= 1 && op <= 7) {
					break;
				} 
			else {
					printf("Numero fora do intervalo (1-7). Escolha um dos numeros mencionados por favor");
					som();
					pausa();
				}
			} else {
				printf("Por favor, insira um numero entre 1 e 7: ");
				som();
				pausa();
				while (getchar() != '\n');
			}
		}
		char sim;
		switch (op)
		{
		case 1:
			limparEcra();
			printf("Vai ter várias perguntas de facil dificuldade, mas que, consoante o tipo, valem entre 1 a 3 pontos. Quer prosseguir? (S/N)");
			scanf(" %c", &sim);
			if (sim == 's' || sim == 'S') {
                contagem++;
				fazerPerguntas(op, jogador);
			}
			break;
		case 2:
			limparEcra();
			printf("Vai ter várias perguntas de media dificuldade, mas que, consoante o tipo, valem entre 4 a 6 pontos. Quer prosseguir? (S/N)");
			scanf(" %c", &sim);
			if (sim == 's' || sim == 'S') {
                contagem++;
				fazerPerguntas(op, jogador);
			}
			break;
		case 3:
			limparEcra();
			printf("Vai ter várias perguntas de grande dificuldade, mas que, consoante o tipo, valem entre 7 a 9 pontos. Quer prosseguir? (S/N)");
			scanf(" %c", &sim);
			if (sim == 's' || sim == 'S') {
                contagem++;
				fazerPerguntas(op, jogador);
			}
			break;
		case 4:
			limparEcra();
			instrucoes();
			break;
		case 5:
			limparEcra();
			historico(jogador);
			break;
		case 6:
			printf("*********************************************************\n");
			printf("*          Selecione o numero da opcao que quer:        *\n");
			printf("*                                                       *\n");
			printf("*          1. Adicionar Perguntas Individualmente       *\n");
			printf("*          2. Adicionar um Ficheiro                     *\n");
			printf("*          3. Voltar ao menu inicial                    *\n");
			printf("*********************************************************\n");
			while(1){
				printf("\n\nOpcao Escolhida: ");
				scanf(" %c", &sim);
				if (sim == '1' || sim == '2' || sim == '3')
					break;
				printf("Por favor coloque (1), (2), (3)\n");
			}
			limparEcra();
			if (sim == '1')
				adicionarQuestoes();
			else if (sim == '2')
				adicionarFicheiro();
			break;
		case 7:
			limparEcra();
			break;
		default:
			printf("\nOpcao Invalida\n");
			Sleep(1000);
			limparEcra();
			printf("Escolha outra opcao, por favor\n");
			Sleep(2000);
			limparEcra();
		}
	} while (op != 7);
    if (contagem == 0)
		printf("Escolheu sair do programa. Obrigada na mesma! :)"); // questão de portugues
	else if (contagem == 1)
		printf("Escolheu sair do programa. Obrigada por jogar 1 vez! :)"); // questão de portugues
	else {
	    printf("Escolheu sair do programa. Obrigada por jogar %d vezes! :)", contagem);
		return -1;
    }
}

void limparEcra() {
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
}

void pausa() {
	#ifdef _WIN32
		Sleep(2000);
	#else
		sleep(2);
	#endif
}

void som() {
    #ifdef _WIN32
        Beep(500, 500);
    #else
        printf("\a");
        fflush(stdout);
    #endif
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
	printf("***********************************************************\n");
	printf("*         Escolha inicialmente a opcao pretendida         *\n");
	printf("*      Para jogar o quiz tem 3 niveis de dificuldade      *\n");
	printf("*                 Facil , Medio e Dificil                 *\n");
	printf("*          Em que vai ter tres tipos de pergunta          *\n");
	printf("* Verdadeiro/Falso, Resposta Numerica e Escolha Multipla  *\n");
	printf("*                     Muito boa sorte :)                  *\n");
	printf("***********************************************************\n");
	printf("\n\n          Pressione um botao para sair deste menu");
	while (getchar() != '\n');
	getchar();
}

void adicionarQuestoes()
{
	printf("***********************************************************\n");
	printf("Este menu serve para adicionar questoes individualmente.");
	printf("***********************************************************\n");
	printf("Se quiser sair, escreva 'S'. Se quiser adicionar questoes, pressione enter\n");
	while(getchar() != '\n');
	char sair = getchar();
	if (sair == 'S' || sair == 's') {
		return;
	}
	printf("Vamos adicionar perguntas ao quiz :) !\n");
	int tipoPergunta;
	int tipoDificuldade = 0;
	while (1) {
		printf("Qual e o nivel de dificuldade a que quer adicionar perguntas? Selecione o numero que pretende\n1.Facil\n2.Medio\n3.Dificil\n");
		printf("Resposta: ");
		while (getchar() != '\n');
		if (scanf("%d", &tipoDificuldade) != 1)
			printf("Tem de ser um dos numeros elencados\nEscolha por favor (1), (2), (3)");
		else if (tipoDificuldade < 1 || tipoDificuldade > 3)
			printf("Tem de ser um dos numeros elencados\nEscolha por favor (1), (2), (3)");
		else if ((tipoDificuldade == 1) || (tipoDificuldade == 2) || (tipoDificuldade == 3))
			break;
		pausa();
		limparEcra();
	}
	while (1) {
		printf("\nQue tipo de perguntas quer acrescentar? Selecione o numero que pretende\n1. Numerica\n2. V/F\n3. Escolha Multipla");
		printf("\nResposta: ");
		while (getchar() != '\n');
		scanf(" %d", &tipoPergunta);
		if (tipoPergunta == 1 || tipoPergunta == 2 || tipoPergunta == 3)
			break;
		printf("Tem de ser um dos numeros elencados\nEscolha por favor (1), (2), (3)");
	}
	int tipoPerguntaFicheiro = 0;
	char perguntaAdicionar[tam_perguntas];
	int respostaAdicionarNum = 0;
	char respostaAdicionarChar;
	char respostaAdicionarString[4][tam_respostas];
	char feedback[tam_feedback];
	if (tipoPergunta == 1)
	{
		tipoPerguntaFicheiro = 1;
		while (getchar() != '\n');
		printf("\nEscreva a pergunta que quer adicionar: ");
		scanf(" %[^\n]", perguntaAdicionar);
		printf("\nQual e a resposta certa? Sendo uma pergunta numerica, por favor coloque um numero: ");
		while (1)
		{
			while (getchar() != '\n');
			if (scanf(" %d", &respostaAdicionarNum) == 1)
				break;
			printf("Nao e um numero! Por favor coloque um numero valido\n");
		}
		printf("\nQual e o feedback que quer dar? ");
		scanf(" %[^\n]", feedback);
	}
	else if (tipoPergunta == 2)
	{
		tipoPerguntaFicheiro = 0;
		while (getchar() != '\n');
		printf("\nEscreva a pergunta quer adicionar: ");
		scanf(" %[^\n]", perguntaAdicionar);
		printf("\nQual e a resposta certa? Sendo uma pergunta de verdadeiro/falso, por favor coloque um V ou F\nResposta: ");
		while (1)
		{
			scanf(" %c", &respostaAdicionarChar);
			respostaAdicionarChar = toupper(respostaAdicionarChar);
			if (respostaAdicionarChar == 'V' || respostaAdicionarChar == 'F')
				break;
			printf("Nao e um caracter valido! Por favor coloque V ou F :( \n");
		}
		printf("\nQual e o feedback que quer dar? ");
		scanf(" %[^\n]", feedback);
	}
	else
	{
		tipoPerguntaFicheiro = 2;
		printf("Escreva a pergunta que quer adicionar: ");
		scanf(" %[^\n]", perguntaAdicionar);
		printf("\nQual e a resposta certa? Sendo uma pergunta de escolha multipla, por favor coloque em 1º a opcao correta\ne depois pode colocar as restantes\n");
		int numRespostas = 0;
		int i = 0;
		while (numRespostas <= 3)
		{
			printf("\nOpcao %i\n", i + 1);
			scanf(" %[^\n]", respostaAdicionarString[i]);
			i++;
			numRespostas++;
		}
		printf("\nQual e o feedback que quer dar? ");
		scanf(" %[^\n]", feedback);
	}
	char ficheiro[30];
	if (tipoDificuldade == 1)
		strcpy(ficheiro, "perguntasfaceis.txt");
	else if (tipoDificuldade == 2)
		strcpy(ficheiro, "perguntasmedias.txt");
	else
		strcpy(ficheiro, "perguntasdificeis.txt");

	FILE *perguntas = fopen(ficheiro, "a");
	if (!perguntas) {
		printf("Ficheiro inexistente ou erro ao abrir\n");
		return;
	}

	if (tipoPergunta == 2) {
		fprintf(perguntas, "%d%s,%c,%s\n", tipoPerguntaFicheiro, perguntaAdicionar, respostaAdicionarChar, feedback);
	}
	else if (tipoPergunta == 1) {
		fprintf(perguntas, "%d%s,%d,%s\n", tipoPerguntaFicheiro, perguntaAdicionar, respostaAdicionarNum, feedback);
	}
	else if (tipoPergunta == 3) {
		fprintf(perguntas, "%d%s,%s,%s,%s,%s,%s\n", tipoPerguntaFicheiro, perguntaAdicionar, respostaAdicionarString[0], respostaAdicionarString[1],
				respostaAdicionarString[2], respostaAdicionarString[3], feedback);
	}
	fclose(perguntas);
	printf("Pergunta adicionada com sucesso!\n");
	while (1) {
		char repetir;
		printf("Quer adicionar mais uma pergunta? (S/N)\nResposta:");
		repetir = getchar();
		repetir = toupper(repetir);
		if(repetir == 'S' || repetir == 'N') {
			if (repetir == 'S') {
				adicionarQuestoes();
			} else {
				break;
			}
		} else {
			printf("Por favor coloque S ou N\n");
		}
	}
}

int contarLinhas(FILE *perguntas) {
    int numLinhas = 0;
    char linha[255];
    while (fgets(linha, sizeof(linha), perguntas) != NULL)
        numLinhas++;
    rewind(perguntas); // Voltar ao início do ficheiro
    return numLinhas;
}

void randomPerguntas(FILE *perguntas, Perguntas arrayRandom[100]) {
    srand(time(NULL));
    int i = 0;
    int numeroLinhas = 0;

    while (fread(&arrayRandom[i], sizeof(Perguntas), 1, perguntas) == 1) {
        i++;
        numeroLinhas++;
    }
    for (int i = 0; i < numeroLinhas; i++) {
        int j = rand() % (i + 1);
        Perguntas temp = arrayRandom[i];
        arrayRandom[i] = arrayRandom[j];
        arrayRandom[j] = temp;
    }
}

void ficheiroRecebidoParaBin(int dificuldade) {
	const char *txt[] = {"perguntasfaceis.txt", "perguntasmedias.txt", "perguntasdificeis.txt"};
    const char *bin[] = {"perguntasfaceis.bin", "perguntasmedias.bin", "perguntasdificeis.bin"};
	dificuldade--; // Para usar como índice (0, 1, 2)
    FILE *FicheiroTXT = fopen(txt[dificuldade], "r");
    FILE *FicheiroBIN = fopen(bin[dificuldade], "wb");

    char linha[512];
    while (fgets(linha, sizeof(linha), FicheiroTXT)) {
        Perguntas p;
        char tipo = linha[0];
        char *conteudo = linha + 1; // Ignorar o tipo (0, 1 ou 2)

        if (tipo == '0' || tipo == '1') {
            // Perguntas de Verdadeiro/Falso ou Abertas
            p.tipo = tipo;
            char *pergunta = strtok(conteudo, ",");
            char *resposta = strtok(NULL, ",");
            char *feedback = strtok(NULL, "\n");

            if (pergunta && resposta && feedback) {
                snprintf(p.pergunta, sizeof(p.pergunta), "%s?", pergunta);
                strncpy(p.resposta, resposta, sizeof(p.resposta) - 1);
                strncpy(p.feedback, feedback, sizeof(p.feedback) - 1);
            } else {
                printf("Formato inválido: %s\n", linha);
                continue;
            }
        }
        else if (tipo == '2') {
            // Perguntas de múltipla escolha
            p.tipo = tipo;
            char *tokens[6];
            int i = 0;

            tokens[i++] = strtok(conteudo, ",\n");
            while (i < 6 && (tokens[i++] = strtok(NULL, ",")));

            if (tokens[0] && tokens[1] && tokens[2] && tokens[3] && tokens[4] && tokens[5]) {
                snprintf(p.pergunta, sizeof(p.pergunta), "%s?", tokens[0]);
                for (int j = 0; j < 4; j++) {
                    strncpy(p.opcoes[j], tokens[j + 1], sizeof(p.opcoes[j]) - 1);
                }
                strncpy(p.multiplaCorreta, tokens[1], sizeof(p.multiplaCorreta) - 1); // correta = primeira opção
                strncpy(p.feedback, tokens[5], sizeof(p.feedback) - 1); // feedback
            }
            else {
                printf("Formato inválido (multipla escolha): %s\n", linha);
                continue;
            }
        }
        else {
            printf("Tipo desconhecido: %c\n", tipo);
            continue;
        }

        fwrite(&p, sizeof(Perguntas), 1, FicheiroBIN);
    }

    fclose(FicheiroTXT);
    fclose(FicheiroBIN);
}


void fazerPerguntas(int dificuldade, Jogador jogador) {
	ficheiroRecebidoParaBin(dificuldade);
	const char *txt[] = {"perguntasfaceis.txt", "perguntasmedias.txt", "perguntasdificeis.txt"};
    const char *bin[] = {"perguntasfaceis.bin", "perguntasmedias.bin", "perguntasdificeis.bin"};
	dificuldade--; // se não era 1 2 3 e saía fora do array
	FILE *tempTXT = fopen(txt[dificuldade], "r");
	int MaxPerguntas = contarLinhas(tempTXT);
	fclose(tempTXT);
	FILE *perguntas = fopen(bin[dificuldade], "rb");
    if (perguntas == NULL) {
        printf("Erro ao abrir o ficheiro de perguntas");
        return;
    }

    Perguntas arrayRandom[100];
    randomPerguntas(perguntas, arrayRandom); // Baralha as perguntas
    int numPerguntas = 0;
    printf("Quantas perguntas quer responder?\nResposta: ");
    if (scanf("%d", &numPerguntas) == 1 && numPerguntas > 0 && MaxPerguntas >= numPerguntas) {
		printf("Vao ser feitas %d perguntas\n", numPerguntas);
	} else {
		printf("Numero invalido. O maximo de perguntas disponiveis são: (%d).\nVao ser feitas %d perguntas, em vez das %d pedidas inicialmente\n", MaxPerguntas, MaxPerguntas, numPerguntas);
		numPerguntas = MaxPerguntas;
	}
	dificuldade++; //para voltar a ser 1, 2, 3 para o sistema de pontos
	printf("Quando estiver a fazer as perguntas, tem 10 segundos para responder\n");
	printf("Caso nao responda dentro do tempo, será descontado pontos consoante o tipo de pergunta\n");
	printf("Quando estiver pronto, pressione um botao para continuar\n");
	printf("Best of luck summoner :)\n");
	while(getchar() != '\n');
	getchar();
    for (int i = 0; i < numPerguntas; i++) {
		limparEcra();
		time_t inicio = time(NULL);
		printf("Pergunta %d/%d - Pontos: %d\n", i + 1, numPerguntas, jogador.pontuacao);
        printf("%s\n", arrayRandom[i].pergunta);
        if (arrayRandom[i].tipo == '0') { // Verdadeiro/Falso
            char respostaVF;
            while (1) {
                printf("Resposta (V/F): ");
                scanf(" %c", &respostaVF);
                respostaVF = toupper(respostaVF);
                if (respostaVF == 'V' || respostaVF == 'F')
                    break;
                while (getchar() != '\n');
                printf("Opção inválida, tente novamente.\n");
				pausa();
            }
			time_t fim = time(NULL);
            if (respostaVF == arrayRandom[i].resposta[0]) {
                printf("Acertou!\n");
				if(difftime(fim, inicio) > 10) {
                	printf("Foi mais que 10 segundos :(, vou ter que deduzir 1 ponto\n");
					pausa();
					jogador.pontuacao += dificuldade * 2 - 1;
				}
				else
					jogador.pontuacao += dificuldade * 2;
			}
    		 else {
                printf("Falhou.\n");
            }
			printf("Feedback: %s\n", arrayRandom[i].feedback);
			printf("Pressione um botao para continuar\n");
			while(getchar() != '\n');
			getchar();
		}
        else if (arrayRandom[i].tipo == '1') {
            char respostaNumerica[100];
            while (1) {
                printf("Resposta: ");
                if (scanf(" %s", respostaNumerica) == 1)
                    break;
                while (getchar() != '\n');
                printf("Entrada inválida, tente novamente.\n");
            }
			time_t fim = time(NULL);
            if (strcmp(respostaNumerica, arrayRandom[i].resposta) == 0) {
				printf("Acertou!\n");
				if(difftime(fim, inicio) > 10) {
                	printf("Foi mais que 10 segundos :(, vou ter que deduzir 3 pontos\n");
					pausa();
					jogador.pontuacao += dificuldade * 4 - 3;
				}
				else
					jogador.pontuacao += dificuldade * 4;
            }
			else
				printf("Falhou.\n");
			printf("Feedback: %s\n", arrayRandom[i].feedback);
			printf("Pressione um botao para continuar\n");
			while(getchar() != '\n');
			getchar();
        }
        else if (arrayRandom[i].tipo == '2') { // Multipla escolha
            char opcoesTemp[4][100];
            for (int k = 0; k < 4; k++)
                strcpy(opcoesTemp[k], arrayRandom[i].opcoes[k]);
            baralharRespostas(opcoesTemp);
            for (int k = 0; k < 4; k++)
                printf("%d. %s\n", k + 1, opcoesTemp[k]);

            int escolha;
            while (1) {
                printf("Resposta (1-4): ");
                if (scanf(" %d", &escolha) == 1 && escolha >= 1 && escolha <= 4)
                    break;
                while (getchar() != '\n')
                    ;
                printf("Opção inválida, tente novamente.\n");
            }
			time_t fim = time(NULL);
            if (strcmp(opcoesTemp[escolha - 1], arrayRandom[i].multiplaCorreta) == 0) {
				printf("Acertou!\n");
				if(difftime(fim, inicio) > 10) {
					printf("Mas foi mais que 10 segundos :(, vou ter que deduzir 3 pontos\n");
					pausa();
					jogador.pontuacao += dificuldade * 3 - 2;
				}
				else
					jogador.pontuacao += dificuldade * 3;
            } else {
                printf("Falhou.\n");
            }
			printf("Feedback: %s\n", arrayRandom[i].feedback);
			printf("Pressione um botao para continuar\n");
			while(getchar() != '\n'); //sem isto o programa não esperava
			getchar();
        }
    }
	FILE *nomejogador = fopen("jogadores.txt", "a");
	time_t agora = time(NULL);
	struct tm *t = localtime(&agora);
	char dataHora[100];
	strftime(dataHora, sizeof(dataHora), "%Y-%m-%d %H:%M:%S", t);
	fprintf(nomejogador, "%s||%s||%d\n", dataHora, jogador.nome, jogador.pontuacao);
	fclose(nomejogador);
    fclose(perguntas);
	historico(jogador);
}

void separarRespostas(char linha[255], char opcoes[4][100])
{
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

void historico(Jogador jogador)
{
	FILE *historico = fopen("jogadores.txt", "r");
	if (!historico)
	{
		printf("Erro, não ha historico de jogadores ainda!");
		return;
	}
	char arrayTemp[100][255];
	char jogadorAtributos[255];
	int numLinhas = 0;
    int flag = 0;
	while (fgets(jogadorAtributos, sizeof(jogadorAtributos), historico))
	{
		strncpy(arrayTemp[numLinhas], jogadorAtributos, tam_perguntas);
		numLinhas++;
	}
	fclose(historico);
	printf("***********************************************************\n");
	printf("*                       Historico                         *\n");
	printf("***********************************************************\n");
	printf("Data e Hora           Jogador         Pontuacao\n");
	for (int i = 0; i < numLinhas; i++)
	{
		char dataHora[50], nome[50];
		int pontos;

		if (sscanf(arrayTemp[i], "%[^|]||%[^|]||%d", dataHora, nome, &pontos) == 3)
		{
			if (strcmp(nome, jogador.nome) == 0) {
				printf("%-21s %-19s %d\n", dataHora, nome, pontos);
                flag = 1;
            }
		}
	}
    if (flag == 0) 
            printf("\nNao existe historico para o jogador %s\n", jogador.nome);
    char resposta;
	while (1)
	{
		printf("\nPretende ver o top 10 melhores jogadores?\nResposta: ");
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
	if (k > 10)
		k = 10; // dava erro se tivesse mais de 10 jogadores
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
	limparEcra();
	printf("***********************************************************\n");
	printf("*                        Ranking                          *\n");
	printf("***********************************************************\n");
	printf("Posicao    Nome          Pontuacao\n");
	for (int i = 0; i < ranking.numJogadores; i++)
		printf("%-10d%-20s%-10d\n", i + 1, ranking.jogadores[i].nome, ranking.jogadores[i].pontuacao);
	printf("\n\nPressione um botao para sair deste menu");
	while(getchar() != '\n'); //sem isto o programa não esperava
	getchar();
}

void adicionarFicheiro() { //rescrever não precisa de ser .txt
	char ficheiroAdicionado[tam_respostas];
	limparEcra(); 
	printf("Nao se esqueca que o ficheiro das perguntas tem de ter o formato correto\n");
	printf("O formato correto e o seguinte (Exemplo):\n");
	printf("****************************************************************************************************************");
	printf("\n*TipoPergunta,Resposta,Feedback*\n");
	printf("**********************************************Exemplo*********************************************************\n");
	printf("*1Em que ano foi implementado o Euro em Portugal?,2002\n*");
	printf("*0O fado e considerado patrimonio imaterial da humanidade?,V\n2Qual destas comidas e típica portuguesa?,Feijoada a transmontana,Burrito,Hamburguer,Sushi\n");
	printf("\n*Em que o primeiro numero indica o tipo de pergunta (0 V/F, 1 Numerica, 2 Escolha Multipla),\nseguido de uma pergunta e de uma resposta, estas duas separadas por uma virgula\n*");
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
    if (dificuldade == 1) { //rescrever
        perguntas = fopen("perguntasfaceis.txt", "a");
    } else if (dificuldade == 2) {
        perguntas = fopen("perguntasmedias.txt", "a");
    } else {
        perguntas = fopen("perguntasdificeis.txt", "a");
    }
	char linha[255];
	while (fgets(linha, sizeof(linha), perguntas1)) {
		if (linha[strlen(linha) - 1] != '\n') {  //tive de incluir porque se não tivesse o \n no final, não funcionava
            fprintf(perguntas, "%s\n", linha);
        } else {
            fprintf(perguntas, "%s", linha);
        }
    }
	fclose(perguntas);
	fclose(perguntas1);
	printf("Perguntas adicionadas com sucesso, obrigada :)!\n");
	ficheiroRecebidoParaBin(dificuldade);
}