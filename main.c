/* *************************************************** */
/*                                                     */
/*                                                     */
/*   Quiz Dinâmico                                     */
/*                                                     */
/*   By: leonor joaquim                                */
/*                                                     */
/*   Created: 2025/04/08 20:00:33 by leonor            */
/*   Updated: 2025/04/30 18:37:12 by leonor            */
/*   Trello:  https://trello.com/b/w9xdOht9            */
/*                                                     */
/* *************************************************** */
#include "biblioteca.h"

int main()
{
	Jogador jogador;
	while (1) { // até 30 caracteres
		limparEcra();
		cores(5); //Negrito
		printf("***********************************************\n");
		printf("*          Insira o seu nome ou nickname      *\n");
		printf("***********************************************\n");
		int tamMaximoNome;
			if(scanf("%s", jogador.nome) == 1) {
				tamMaximoNome = strlen(jogador.nome);
				if (tamMaximoNome > 29)
					printf("O nome e muito grande, por favor coloque um nome mais pequeno\n");
				else 
					break;
				pausa(2);
			}
	}
	int num = verificarJogador(jogador);
	jogador.pontuacao = 0;
	int op;
    int contagem = 0;
	do
	{
		cores(5); //Negrito
		while (1) {
		limparEcra();
		printf("*********************************************************\n");
		if (num == 0)
			printf("                 Bem vindo %s              \n", jogador.nome);
		else
		printf("               Bem vindo de volta %s           \n", jogador.nome);
		printf("*********************************************************\n");

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
		cores(0);//voltar a cor normal
		printf("\nOpcao Escolhida: ");
			if (scanf("%d", &op) == 1) {
				if (op >= 1 && op <= 7) {
					break;
				} 
			else {
					printf("Numero fora do intervalo (1-7). Escolha um dos numeros mencionados por favor");
					som(200,500);
				}
			} else {
				printf("Por favor, insira um numero entre 1 e 7: ");
				som(200,500);
				while (getchar() != '\n');
			}
		}
		char sim;
		switch (op)
		{
		case 1:
			limparEcra();
			cores(5); //Negrito
			printf("Vai ter varias perguntas de facil dificuldade, mas que, consoante o tipo, valem:\n1. V/F - 2 Pontos\n2. Escolha Multipla - 3 Pontos\n3. Numerico - 4 Pontos\n\nSe quiser prosseguir escreva (S), se nao escreva outra coisa qualquer\nResposta: ");
			scanf(" %c", &sim);
			if (sim == 's' || sim == 'S') {
                contagem++;
				som(500,200);
				fazerPerguntas(op, jogador);
			}
			cores(0);
			break;
		case 2:
			limparEcra();
			cores(5); //Negrito
			printf("Vai ter varias perguntas de media dificuldade, mas que, consoante o tipo, valem:\n1. V/F - 4 Pontos\n2. Escolha Multipla - 6 Pontos\n3. Numerico - 8 Pontos\n\nSe quiser prosseguir escreva (S), se nao escreva outra coisa qualquer\nResposta: ");
			scanf(" %c", &sim);
			if (sim == 's' || sim == 'S') {
                contagem++;
				som(500,200);
				fazerPerguntas(op, jogador);
			}
			cores(0);
			break;
		case 3:
			limparEcra();
			cores(5); //Negrito
			printf("Vai ter varias perguntas de grande dificuldade, mas que, consoante o tipo, valem:\n1. V/F - 6 Pontos\n2. Escolha Multipla - 9 Pontos\n3. Numerico - 12 Pontos\n\nSe quiser prosseguir escreva (S), se nao escreva outra coisa qualquer\nResposta: ");
			scanf(" %c", &sim);
			if (sim == 's' || sim == 'S') {
                contagem++;
				som(500,200);
				fazerPerguntas(op, jogador);
			}
			cores(0);
			break;
		case 4:
			som(500,200);
			limparEcra();
			instrucoes();
			break;
		case 5:
			som(500,200);
			limparEcra();
			historico(jogador);
			break;
		case 6:
			som(500,200);
			limparEcra();
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
				while (getchar() != '\n');
			}
			limparEcra();
			if (sim == '1')
				adicionarQuestoes();
			else if (sim == '2')
				adicionarFicheiro();
			break;
		case 7:
			som(500,200);
			limparEcra();
			break;
		default:
			printf("\nOpcao Invalida\n");
			pausa(1);
			limparEcra();
			printf("Escolha outra opcao, por favor\n");
			pausa(2);
			limparEcra();
		}
	} while (op != 7);
    if (contagem == 0)
		printf("Escolheu sair do programa. Obrigada na mesma! :)"); // questão de portugues
	else if (contagem == 1)
		printf("Escolheu sair do programa. Obrigada por jogar 1 vez! :)"); // questão de portugues
	else 
	    printf("Escolheu sair do programa. Obrigada por jogar %d vezes! :)", contagem);
	return 0;
}

int verificarJogador(Jogador jogador) //confirmar se o jogador ja existe no historico
{
	FILE *historico = fopen("jogadores.txt", "r");
	if (!historico)
	{
		printf("Erro, não ha historico de jogadores ainda!");
		pausa(2);
		return -1;
	}
	int flag = 0;
	char linha[255];
	char dataHora[30];
	char nomeHistorico[30];
	while (fgets(linha, sizeof(linha), historico)) {
		if (sscanf(linha, "%29[^|]||%29[^|]", dataHora, nomeHistorico) == 2) {
			if (strcmp(nomeHistorico, jogador.nome) == 0) {
				flag = 1;
				break;
			}
			else
        		printf("Linha invalida no historico: %s\n", linha);
		}
	}
	fclose(historico);
	return flag;
}

void instrucoes()
{
	printf("*********************************************************\n");
	printf("*                       Instrucoes                      *\n");
	printf("*********************************************************\n\n");

	printf("*********************************************************\n");
	printf("*                                                       *\n");
	printf("*    Para jogar o quiz tem 3 niveis de dificuldade      *\n");
	printf("*    - Facil                                            *\n");
	printf("*    - Medio                                            *\n");
	printf("*    - Dificil                                          *\n");
	printf("*                                                       *\n");
	printf("*    Vai ter tres tipos de pergunta diferentes:         *\n");
	printf("*    - Verdadeiro/Falso                                 *\n");
	printf("*    - Resposta Numerica                                *\n");
	printf("*    - Escolha Multipla                                 *\n");
	printf("*                                                       *\n");
	printf("*    Cada dificuldade e tipo de pergunta tem a sua      *\n");
	printf("*    propria pontuacao. Se responder em 10 segundos     *\n");
	printf("*    tem a pontuacao completa. Se for depois, perde     *\n");
	printf("*    pontuacao consoante o tipo e dificuldade :)        *\n");
	printf("*                                                       *\n");
	printf("*                  Muito boa sorte :)                   *\n");
	printf("*********************************************************\n");
	printf("\n\n          Pressione enter para sair deste menu\n");
	while (getchar() != '\n');
	getchar();
}

void adicionarQuestoes()
{
	limparEcra();
	som(500,300);
	printf("Vamos adicionar perguntas ao quiz :) !\n");
	int tipoPergunta;
	int tipoDificuldade = 0;
	while (1) {
		printf("Qual e o nivel de dificuldade a que quer adicionar perguntas? Selecione o numero que pretende\n1. Facil\n2. Medio\n3. Dificil\n");
		printf("Resposta: ");
		while (getchar() != '\n');
		if (scanf("%d", &tipoDificuldade) != 1)
			printf("Tem de ser um dos numeros elencados\nEscolha por favor (1), (2), (3)");
		else if (tipoDificuldade < 1 || tipoDificuldade > 3)
			printf("Tem de ser um dos numeros elencados\nEscolha por favor (1), (2), (3)");
		else if ((tipoDificuldade == 1) || (tipoDificuldade == 2) || (tipoDificuldade == 3))
			break;
		pausa(2);
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
		printf("\nQual e a resposta certa? Sendo uma pergunta de escolha multipla, por favor coloque em primeiro a opcao correta\ne depois pode colocar as restantes\n");
		int numRespostas = 0;
		int i = 0;
		while (numRespostas <= 3)
		{
			printf("Opcao %i: ", i + 1);
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
		fprintf(perguntas, "%d%s|%c|%s\n", tipoPerguntaFicheiro, perguntaAdicionar, respostaAdicionarChar, feedback);
	}
	else if (tipoPergunta == 1) {
		fprintf(perguntas, "%d%s|%d|%s\n", tipoPerguntaFicheiro, perguntaAdicionar, respostaAdicionarNum, feedback);
	}
	else if (tipoPergunta == 3) {
		fprintf(perguntas, "%d%s|%s|%s|%s|%s|%s\n", tipoPerguntaFicheiro, perguntaAdicionar, respostaAdicionarString[0], respostaAdicionarString[1],
				respostaAdicionarString[2], respostaAdicionarString[3], feedback);
	}
	fclose(perguntas);
	printf("Pergunta adicionada com sucesso!\n");
	while (1) {
		char repetir;
		printf("Quer adicionar mais uma pergunta? (S/N)\nResposta:");
		while (getchar() != '\n');
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
    char linha[500];
    while (fgets(linha, sizeof(linha), perguntas) != NULL)
        numLinhas++;
    rewind(perguntas); // Voltar ao início do ficheiro, melhor que abir e voltar a fechar
    return numLinhas;
}

void randomPerguntas(FILE *perguntas, Perguntas p[100]) {
    srand(time(NULL));
    int i = 0;
    int numeroLinhas = 0;

    while (fread(&p[i], sizeof(Perguntas), 1, perguntas) == 1) {
        i++;
        numeroLinhas++;
    }
    for (int i = 0; i < numeroLinhas; i++) {
        int j = rand() % (i + 1);
        Perguntas temp = p[i];
        p[i] = p[j];
        p[j] = temp;
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
        char *conteudo = linha + 1;

        if (tipo == '0' || tipo == '1') {
            p.tipo = tipo;
            char *pergunta = strtok(conteudo, "|");
            char *resposta = strtok(NULL, "|");
            char *feedback = strtok(NULL, "\n");

            if (pergunta && resposta && feedback) {
                snprintf(p.pergunta, sizeof(p.pergunta), "%s", pergunta);
                strncpy(p.resposta, resposta, sizeof(p.resposta) - 1);
                strncpy(p.feedback, feedback, sizeof(p.feedback) - 1);
            } else {
                printf("Formato invalido: %s\n", linha);
                continue;
            }
        }
        else if (tipo == '2') {
            p.tipo = tipo;
            char *parte[6]; // 1 pergunta + 4 opcoes + 1 feedback = 6 partes da linha
            int i = 0;

            parte[i++] = strtok(conteudo, "|\n");
            while (i < 6 && (parte[i++] = strtok(NULL, "|")));

            if (parte[0] && parte[1] && parte[2] && parte[3] && parte[4] && parte[5]) {
                snprintf(p.pergunta, sizeof(p.pergunta), "%s", parte[0]);
                for (int j = 0; j < 4; j++) {
                    strncpy(p.opcoes[j], parte[j + 1], sizeof(p.opcoes[j]) - 1);
                }
                strncpy(p.multiplaCorreta, parte[1], sizeof(p.multiplaCorreta) - 1); // correta = primeira opção
                strncpy(p.feedback, parte[5], sizeof(p.feedback) - 1); // feedback
            }
            else
                printf("Formato invalido: %s\n", linha);
        }
        fwrite(&p, sizeof(Perguntas), 1, FicheiroBIN);
    }
    fclose(FicheiroTXT);
    fclose(FicheiroBIN);
}


void fazerPerguntas(int dificuldade, Jogador jogador) {
	limparEcra();
	ficheiroRecebidoParaBin(dificuldade);
	const char *txt[] = {"perguntasfaceis.txt", "perguntasmedias.txt", "perguntasdificeis.txt"};
    const char *bin[] = {"perguntasfaceis.bin", "perguntasmedias.bin", "perguntasdificeis.bin"};
	dificuldade--; // se não era 1 2 3 e saía fora do array
	FILE *tempTXT = fopen(txt[dificuldade], "r");
	if (tempTXT == NULL) {
		printf("Erro ao abrir %s\n", txt[dificuldade]);
		return;
	}
	int maxPerguntas = contarLinhas(tempTXT);
	fclose(tempTXT);
	FILE *perguntas = fopen(bin[dificuldade], "rb");
    if (perguntas == NULL) {
        printf("Erro ao abrir o ficheiro de perguntas");
        return;
    }

    Perguntas p[100];
    randomPerguntas(perguntas, p); // Baralha as perguntas
    int numPerguntas = 0;
	while (1) {
		printf("Quantas perguntas quer responder? Tendo em conta a dificuldade que selecionou, existem no maximo %d perguntas\nResposta: ", maxPerguntas);
		if (scanf("%d", &numPerguntas) == 1 && numPerguntas > 0 && maxPerguntas >= numPerguntas) {
			printf("Vao ser feitas %d perguntas\n", numPerguntas);
			break;
		}
		else
			printf("Insira um numero entre 1 e %d\n", maxPerguntas);
		while (getchar() != '\n');
	}
	dificuldade++; //para voltar a ser 1, 2, 3 para o sistema de pontos
	limparEcra();
	printf("*************************************************************************************************\n");
	printf("*              Quando estiver a responder as perguntas, tem 10 segundos para responder          *\n");
	printf("*    Caso nao responda dentro do tempo, sera descontado pontos consoante o tipo de pergunta     *\n");
	printf("*                                                                                               *\n");
	printf("*                                   Best of luck summoner :)                                    *\n");
	printf("*************************************************************************************************\n");

	printf("                     Quando estiver pronto, pressione enter para continuar                       \n");
	while(getchar() != '\n');
	getchar();
    for (int i = 0; i < numPerguntas; i++) {
		limparEcra();
		time_t inicio = time(NULL);
		cores(3); 
		printf("Pergunta %d/%d - Pontos: %d \n", i + 1, numPerguntas, jogador.pontuacao);
		printf("%s\n", p[i].pergunta);
		cores(0);
		if (p[i].tipo == '0') { // Verdadeiro/Falso
			char respostaVF;
			while (1) {
				printf("Resposta (V/F): ");
				scanf(" %c", &respostaVF);
				respostaVF = toupper(respostaVF);
				if (respostaVF == 'V' || respostaVF == 'F')
					break;
				while (getchar() != '\n');
				printf("Opcao invalida, tente novamente por favor :).\n");
			}
			
			time_t fim = time(NULL);
			if (respostaVF == p[i].resposta[0]) {
				cores(2);
				som(600, 200);
				printf("\nAcertou!");
				cores(0);
				if (difftime(fim, inicio) > 10) {
					printf("\nFoi mais que 10 segundos :( vou ter que deduzir 1 ponto");
					jogador.pontuacao += dificuldade * 2 - 1;
				} else {
					jogador.pontuacao += dificuldade * 2;
				}
			} else {
				cores(1);
				som(100, 200);
				printf("\nFalhou.");
			}
		}
		else if (p[i].tipo == '1') { //Numerico  
			char respostaNumerica[100];
			while (1) {
				int flag = 0;
				printf("Resposta: ");
				if (scanf(" %s", respostaNumerica) == 1) {
					for (int i = 0; respostaNumerica[i] != '\0'; i++) {
						if (isdigit(respostaNumerica[i])) {
							flag = 1;
							break;
						}
					}
					if (flag == 1)
						break;
					else
						printf("Tem de inserir um numero valido, por favor :)\n");
				}
				while (getchar() != '\n');
			}
			time_t fim = time(NULL);
			if (strcmp(respostaNumerica, p[i].resposta) == 0) {
				som(600, 200);
				cores(2);
				printf("\nAcertou!");
				cores(0);
				if (difftime(fim, inicio) > 10) {
					printf("\nMas foi mais que 10 segundos :( vou ter que deduzir 3 pontos\n");
					jogador.pontuacao += dificuldade * 4 - 3;
				} else {
					jogador.pontuacao += dificuldade * 4;
				}
			} else {
				cores(1);
				som(100, 200);
				printf("\nFalhou.");
			}
		}
		else if (p[i].tipo == '2') { // Multipla escolha
			char opcoesTemp[4][100];
			for (int k = 0; k < 4; k++)
				strcpy(opcoesTemp[k], p[i].opcoes[k]);
			baralharRespostas(opcoesTemp);
			for (int k = 0; k < 4; k++)
				printf("%d. %s\n", k + 1, opcoesTemp[k]);
			int escolha;
			while (1) {
				printf("Resposta (1-4): ");
				if (scanf(" %d", &escolha) == 1 && escolha >= 1 && escolha <= 4)
					break;
				while (getchar() != '\n');
				printf("Opcao invalida, tente novamente.\n");
			}
			printf("\n");
			time_t fim = time(NULL);
			if (strcmp(opcoesTemp[escolha - 1], p[i].multiplaCorreta) == 0) {
				cores(2); // Verde para Acertou
				som(600, 200);
				printf("Acertou!");
				cores(0);
				if (difftime(fim, inicio) > 10) {
					printf("\nMas foi mais que 10 segundos :( vou ter que deduzir 3 pontos\n");
					jogador.pontuacao += dificuldade * 3 - 2;
				} else 
					jogador.pontuacao += dificuldade * 3;
			} else {
				som(100, 200);
				cores(1); // Vermelho para Falhou
				printf("\nFalhou.");
			}
		}
		cores(0);
		cores(4);
		printf("\nFeedback: %s", p[i].feedback);
		cores(0);
		printf("\nPressione enter para continuar\n");
		while(getchar() != '\n'); 
		getchar();
	}
	
	FILE *nomejogador = fopen("jogadores.txt", "a");
	time_t agora = time(NULL);
	struct tm *t = localtime(&agora);
	char dataHora[100];
	strftime(dataHora, sizeof(dataHora), "%Y-%m-%d %H:%M:%S", t);
	fprintf(nomejogador, "%s||%s||%d\n", dataHora, jogador.nome, jogador.pontuacao);
	fclose(nomejogador);
    fclose(perguntas);
	ordenarRank();
}

void separarRespostas(char linha[255], char opcoes[4][100])
{
	int i = 0;	 // index
	int res = 0; // resposta
	int caracter = 0;
	while (res < 4 && linha[i] != '\0')
	{
		if (linha[i] == '|')
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
	srand(time(NULL));
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
	cores(6);
	printf("***********************************************************\n");
	printf("*                       Historico                         *\n");
	printf("***********************************************************\n");
	cores(0);
	cores(5);
	printf("Data e Hora               Jogador                 Pontuacao\n");
	for (int i = 0; i < numLinhas; i++) {
		char dataHora[50], nome[50];
		int pontos;
		if (sscanf(arrayTemp[i], "%[^|]||%[^|]||%d", dataHora, nome, &pontos) == 3) {
			if (strcmp(nome, jogador.nome) == 0) {
				printf("%-25s %-25s %d\n", dataHora, nome, pontos);
                flag = 1;
            }
		}
	}
	cores(0);
    if (flag == 0) 
            printf("\nNao existe historico para o jogador %s\n", jogador.nome);
    char resposta;
	while (1)
	{
		printf("\nPretende ver o top 10 melhores jogadores? (S/N)\nResposta: ");
		scanf(" %c", &resposta);
		resposta = toupper(resposta);
		if (resposta == 'S' || resposta == 'N')
			break;
		printf("Por favor coloque S ou N");
		limparEcra();
	}
	if (resposta == 'S')
		ordenarRank();
}

void ordenarRank()
{
	FILE *historico = fopen("jogadores.txt", "r");
	char arrayTemp[100][255];
	char jogadorAtributos[255];
	int numLinhas = 0;
	while (fgets(jogadorAtributos, sizeof(jogadorAtributos), historico)) {
   		strncpy(arrayTemp[numLinhas], jogadorAtributos, sizeof(jogadorAtributos));
    	numLinhas++;
	}
	fclose(historico);
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
	cores(6);
	printf("*****************************************************\n");
	printf("*                      Ranking                      *\n");
	printf("*****************************************************\n");
	cores(0);
	cores(5);
	printf("%-12s %-26s %13s\n", "Posicao", "Nome", "Pontuacao");
	for (int i = 0; i < ranking.numJogadores; i++)
		printf("%-12d %-26s %10d\n", i + 1, ranking.jogadores[i].nome, ranking.jogadores[i].pontuacao);
	cores(0);
	printf("\n\nPressione enter para sair deste menu");
	while (getchar() != '\n');
	getchar();
}

void adicionarFicheiro() {
	som(500,300);
	char ficheiroAdicionado[tam_respostas];
	limparEcra();
	printf("Pode adicionar um ficheiro ao sistema com o seguinte formato:\n");
	cores(3);
	printf("********************************************************************************************\n");
	printf("*                                TipoPergunta|Resposta|Feedback                            *\n");
	printf("********************************************************************************************\n\n");
	cores(1);
	printf("Nao se esqueca que o ficheiro das perguntas tem de ter o formato correto\n");
	cores(0);
	printf("Exemplos:\n");
	printf("1Em que ano foi implementado o Euro em Portugal?|2002|O Euro foi implementado em Portugal em 1 de janeiro de 2002, substituindo o Escudo.\n");
	printf("0O fado e considerado patrimonio imaterial da humanidade?|V|O fado foi reconhecido como Patrimonio Cultural Imaterial da Humanidade pela UNESCO em 2011.\n");
	printf("2Qual destas comidas e tipica portuguesa?|Feijoada a transmontana|Burrito|Hamburguer|Sushi|A Feijoada a Transmontana e um prato tradicional portugues; os outros sao de origem estrangeira.\n\n");
	printf("Em que o primeiro numero indica o tipo de pergunta (0 V/F, 1 Numerica, 2 Escolha Multipla)\nSeguido de uma pergunta e de uma resposta, estas duas separadas por uma barra vertical '|'(ou varias consoante o tipo de pergunta)\nE finalmente, finalizar com o feedback\n");
	printf("\n\nInsira, por favor, o nome do ficheiro que quer adicionar (com a extensao incluida)\n");
	printf("Se preferir voltar atras, escreva apenas 'S'");
	printf("\nResposta: ");
	scanf(" %[^\n]", ficheiroAdicionado);
	if (strcmp(ficheiroAdicionado, "S") == 0)
		return;
	FILE *perguntasAdicionadas = fopen(ficheiroAdicionado, "r");
	if (!perguntasAdicionadas)
	{
		printf("Erro ao abrir o ficheiro\n");
		pausa(2);
		return;
	}
	printf("Ficheiro aberto com sucesso!\n");

	printf("As Perguntas novas que adicionou sao de que dificuldade? (1)- Facil, (2) - Medio, (3) - Dificil\nResposta: ");
	int dificuldade;
	while(1) {
		scanf("%d", &dificuldade);
		if (dificuldade == 1 || dificuldade == 2 || dificuldade == 3)
			break;
		printf("Por favor coloque 1, 2 ou 3\nResposta: ");
		while (getchar() != '\n');
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
	while (fgets(linha, sizeof(linha), perguntasAdicionadas)) {
		if (linha[strlen(linha) - 1] != '\n') {  //tive de incluir porque se não tivesse o \n no final, não funcionava
            fprintf(perguntas, "%s\n", linha);
        } else {
            fprintf(perguntas, "%s", linha);
        }
    }
	fclose(perguntas);
	fclose(perguntasAdicionadas);
	printf("Perguntas adicionadas com sucesso, obrigada :)!\n");
	pausa(2);
}

//Funções Utilitárias
void cores(int cor) {
    switch (cor) {
        case 1: // Vermelho
            printf("\033[48;5;210m");
            break;
        case 2: // Verde
            printf("\033[48;5;28m");
            break;
		case 3: //fundo do cabeçalho das perguntas
			printf("\033[48;5;0m");
			printf("\033[38;5;15m");
			break;
		case 4: //azul feedback
			printf("\033[36m");
			break;
		case 5: // negrito
			printf("\033[1m");
			break;
		case 6: // cabeçalhos no quiz
			printf("\033[48;5;0m");
			break;
        default:
			printf("\033[0m");
            break;
    }
}

void limparEcra() {
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
}

void pausa(int segundos) {
    #ifdef _WIN32
        Sleep(segundos * 1000);
    #else
        sleep(segundos);
    #endif
}


void som(int freq, int duracao) {
    #ifdef _WIN32
        Beep(freq, duracao);
    #else
        printf("\a");
        fflush(stdout);
    #endif
}