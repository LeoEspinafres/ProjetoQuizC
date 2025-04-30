/* *************************************************** */
/*                                                     */
/*                                                     */
/*   Quiz Dinâmico                                     */
/*                                                     */
/*   By: leonor joaquim                                */
/*                                                     */
/*   Created: 2025/04/08 22:02:57 by leonor            */
/*   Updated: 2025/04/30 17:25:01 by leonor            */
/*   Trello:  https://trello.com/b/w9xdOht9            */
/*                                                     */
/* *************************************************** */

#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

# ifndef tam_perguntas
#  define tam_perguntas 255
# endif
# ifndef tam_respostas
#  define tam_respostas 100
# endif
# ifndef tam_feedback
#  define tam_feedback 255
# endif

typedef struct jogador
{
	char nome[30];
	int pontuacao;
} Jogador;

typedef struct ranking
{ 
	Jogador jogadores[100];
	int numJogadores;
} Rank;

typedef struct perguntas
{
	char pergunta[tam_perguntas]; // falta const
	char resposta[tam_perguntas];
	char tipo;
	char multiplaCorreta[tam_respostas];
	char opcoes[4][tam_respostas];
	char feedback[tam_feedback];
} Perguntas;

void randomPerguntas(FILE *perguntas, Perguntas arrayRandom[100]);
void instrucoes();
void adicionarQuestoes();
void fazerPerguntas(int dificuldade, Jogador jogador);
void separarRespostas(char linha[255], char opcoes[4][100]);
void baralharRespostas(char opcoes[4][100]);
void historico(Jogador jogador);
void ordenarRank();
int verificarJogador(Jogador jogador);
void adicionarFicheiro();
int contarLinhas(FILE *perguntas);
void ficheiroRecebidoParaBin(int dificuldade);
//Funções utilitárias
void limparEcra();
void pausa(int segundos);
void som(int freq, int duracao);
void cores(int cor);

#endif //BIBLIOTECA_H
