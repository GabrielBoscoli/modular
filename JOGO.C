/***************************************************************************
 *  $MCI Módulo de implementação: JOGO  Módulo Jogo / Principal
 *
 *  Arquivo gerado:              JOGO.c
 *  Letras identificadoras:      JOGO
 *
 *  Projeto: Disciplina INF 1301
 *  Gestor:  DI/PUC-RIO, Professor Alessandro Garcia
 *  Autores: gb - Gabriel Boscoli
 *
 *  $HA Histórico de evolução:
 *     Versão    Autores        Data          Observações
 *     2.00        gb        20/06/2019   término desenvolvimento
 *     1.00        gb        19/06/2019   início desenvolvimento
 *
 *  $ED Descrição do módulo
 *	  Este módulo contém a implementação de uma partida de Ludo.
 *
 ***************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#include "PECA.H"
#include "TABULEIRO.H"
#include "LISTA.H"

#define MIN_JOGADORES	  1
#define MAX_JOGADORES	  4
#define NUM_PECAS 		  4
#define TAMANHO_MAX_INPUT 81
#define VALOR_MAX_DADO	  6
#define VALOR_MIN_DADO	  1
#define NUM_CORES		  4

/***********************************************************************
*
*  $TC Tipo de dados: JOGO Descritor dos dados dos jogadores
*
***********************************************************************/

	typedef struct Jogador{

		char nome[TAMANHO_MAX_INPUT];
		/* Nome do Jogador */

		int cor;
		/* Cor do Jogador */

		PEC_tppPeca* pecas;
		/* Pecas do Jogador */

	} JOGO_Jogador;

/***** Protótipo das funções encapsuladas no módulo *****/

	int Ludo (void);

	int DefineNumeroJogadores();

	void DefineJogadores ( int numeroJogadores , JOGO_Jogador* vetorJogador );

	void CriarPecaJogador ( JOGO_Jogador* jogador );

	int VerificaComandoValido ( char* comando , int* dado , JOGO_Jogador* vtJogadores , int quantidadeJogadores , TAB_tppTabuleiro pTabuleiro );

	int ExisteMovimentoPossivel ( JOGO_Jogador jogador , TAB_tppTabuleiro pTabuleiro , int dado );

	int ExistePecaCasaInicial ( JOGO_Jogador jogador );

	void EscolhePecaParaMovimentar ( TAB_tppTabuleiro pTabuleiro , JOGO_Jogador* jogador , int dado );

	int MovimentarPecaSePossivel ( TAB_tppTabuleiro pTabuleiro , PEC_tppPeca peca , int dado );

	void ExibePosicaoDasPecas ( TAB_tppTabuleiro pTabuleiro , JOGO_Jogador* vetorJogadores , int numeroJogadores );

	void ExibeComandosPossiveis();

	int VerificaSeVenceu ( TAB_tppTabuleiro pTabuleiro , JOGO_Jogador jogador );

	int ComePecaOponenteSePossivel (TAB_tppTabuleiro pTabuleiro , int cor );

	int QuantidadePecaCasaSaidaComMesmaCor (TAB_tppTabuleiro pTabuleiro , int cor );

	void DestruirPecaJogador( JOGO_Jogador* jogador );

	int InputEhDigito ( char* string );

	char InputEhCaracter ( char* string );

	void TransformaInputEmMinusculo ( char* string );

	void RemoverNovaLinha(char* string);

	void LiberarMemoria( JOGO_Jogador* vtJogadores, int quantidadeJogadores, TAB_tppTabuleiro pTabuleiro );

/*****  Código da função principal do módulo  *****/

	int main ()
	{
		Ludo();
	}

	int Ludo (void)
	{
		int i;
		int dado;
		int possuiVencedor;
		int numJogadores;
		int pecaComida;
		char input[TAMANHO_MAX_INPUT];

		JOGO_Jogador* vtJogadores ; 
		TAB_tppTabuleiro  pTabuleiro  ;

		TAB_CondRet tabuleiroRetorno ;

		do {

			printf("\n Bem-vindo ao Jogo de Ludo.\n");
			printf(" Para saber as regras do jogo, por favor, verifique a especificacao de requisitos do projeto.\n\n");
    
			numJogadores = DefineNumeroJogadores();
			vtJogadores = (JOGO_Jogador*) malloc ( numJogadores * sizeof (JOGO_Jogador));
			
			if ( vtJogadores == NULL )
			{
				printf(" Memoria insuficiente para criar jogadores");
				scanf("%s");
				exit(1);
			}

			DefineJogadores(numJogadores, vtJogadores);

			tabuleiroRetorno = TAB_CriarTabuleiro( &pTabuleiro ) ;
	
			if ( tabuleiroRetorno != TAB_CondRetOK )
			{
				printf("\n\n\tMEMORIA INSUFICIENTE PARA CRIAR TABULEIRO!!!\n\n"); 
				scanf("%s");
				exit(1);
			}

			printf("\n\n----------------------------------------------------INICIO DO JOGO----------------------------------------------------\n\n");
			printf(" Tabuleiro:\n");
			TAB_ExibeTabuleiro();
			TAB_ExibeLegendaTabuleiro();
			printf("\n DIGITE A LETRA - D - PARA JOGAR O DADO OU ENTAO DIGITE - C - PARA VISUALIZAR TODOS OS COMANDOS VALIDOS\n\n");
			possuiVencedor = 0 ;

			while ( !possuiVencedor ) {
				for ( i = 0 ; i < numJogadores && possuiVencedor != 1 ; i++ ) 
				{	
					dado = 0;
					pecaComida = 0;
					printf( " VEZ DO JOGADOR : %s\n" , vtJogadores[i].nome ) ;
					fgets( input, TAMANHO_MAX_INPUT, stdin );
					RemoverNovaLinha( input );
					while ( !VerificaComandoValido( input, &dado, vtJogadores, numJogadores, pTabuleiro ) || !dado)
					{
						printf("\n DIGITE A LETRA - D - PARA JOGAR O DADO OU ENTAO DIGITE - C - PARA VISUALIZAR TODOS OS COMANDOS VALIDOS\n\n");
						fgets( input, TAMANHO_MAX_INPUT, stdin );
						RemoverNovaLinha( input );
					}

					if ( ExisteMovimentoPossivel(vtJogadores[i], pTabuleiro, dado) )
					{
						EscolhePecaParaMovimentar(pTabuleiro, &(vtJogadores[i]), dado);
						pecaComida = ComePecaOponenteSePossivel(pTabuleiro, vtJogadores[i].cor);
					}
					else
					{
						printf(" Voce nao pode realizar nenhum movimento\n\n");
					}

					ExibePosicaoDasPecas(pTabuleiro, vtJogadores, numJogadores);

					possuiVencedor = VerificaSeVenceu(pTabuleiro, vtJogadores[i]);

					if ( dado == 6 )
					{
						printf(" Voce pode jogar o dado novamente!!!\n\n");
						--i;
					}
					else if ( pecaComida )
					{
						printf(" Voce comeu %d peca(s) e pode jogar o dado novamente!!!\n\n", pecaComida);
						--i;
					}
				
				} 
			}

			printf(" Parabens, %s. Voce eh o grande campeao!!!\n\n", vtJogadores[--i].nome);
	
			LiberarMemoria( vtJogadores, numJogadores, pTabuleiro );

			printf(" Para jogar novamente, digite a letra - S -\n Caso contrario, digite qualquer coisa para sair.\n" );
			fgets( input, TAMANHO_MAX_INPUT, stdin );
			RemoverNovaLinha( input );

		} while ( strcmp ( input, "s" ) == 0 || strcmp ( input, "S" ) == 0 );

		return 0;

	}    /* Fim função: MAIN */

/****************  Código das funções encapsuladas no módulo  **********************/

/***************************************************************************
*
*  $FC Função: JOGO  -Define o numero de jogadores
*
*  $ED Descrição da função
*		Define o numero de jogadores que participarao da partida
*
*  $FV Valor retornado
*		Um inteiro com a quantidade de jogadores
*
***************************************************************************/

	int DefineNumeroJogadores()
	{
		char input[TAMANHO_MAX_INPUT];
		int jogadores = -1;
		printf(" Digite a quantidade de jogadores: ");
		while(1)
		{
			fgets( input, TAMANHO_MAX_INPUT, stdin );
			RemoverNovaLinha( input );
			if ( InputEhDigito( input ) )
			{
				jogadores = atoi( input );
			}
			if( jogadores < MIN_JOGADORES || jogadores > MAX_JOGADORES )
			{
				printf(" Por favor, digite um numero entre %d e %d.\n", MIN_JOGADORES, MAX_JOGADORES);
			}
			else
			{
				break;
			}
		}

		return jogadores;
	} /* Fim função: JOGO  -Define o numero de jogadores */

/***************************************************************************
*
*  $FC Função: JOGO  -Define os jogadores
*
*  $ED Descrição da função
*		Cria os jogadores, juntamente de suas peças, e define a cor de cada
*		jogador assim como seus nomes
*
*  $EP Parâmetros
*		numeroJogadores - int com o numero de jogadores da partida
*		vetorJogador	- vetor com jogadores da partida
*
*  $EAE Assertivas de entrada
*		numeroJogadores deve ser um inteiro entre MIN_JOGADORES e MAX_JOGADORES,
*		vetorJogador deve ser diferente de NULL
*
*  $EAE Assertivas de saida
*		Caso os dados de entrada estejam fora do padrao, o programa se encerra
*		Caso tudo ocorra corretamente, 
*			Os jogadores sao criados, assim como
*			As pecas dos jogadores sao criadas
*			A memoria necessária para as pecas é alocada
*
***************************************************************************/

	void DefineJogadores( int numeroJogadores, JOGO_Jogador* vetorJogador )
	{
		char input[TAMANHO_MAX_INPUT];
		int i;
		int j;
		int corValida = 1;
		int cor;

		if( vetorJogador == NULL )
		{
			printf(" Erro! jogadores inexistentes");
			scanf(" %s");
			exit(1);
		}

		if( numeroJogadores < MIN_JOGADORES || numeroJogadores > MAX_JOGADORES )
		{
			printf(" Erro! numero de jogadores invalido");
			scanf("%s");
			exit(1);
		}

		for(i = 0; i < numeroJogadores; i++)
		{
			printf(" Digite o nome do jogador %i: ", i + 1);
			fgets( vetorJogador[i].nome, TAMANHO_MAX_INPUT, stdin );
			RemoverNovaLinha( vetorJogador[i].nome );
			printf("\n");
			printf(" Digite a cor de %s: \n", vetorJogador[i].nome);
			printf(" 0 - Vermelho\n");
			printf(" 1 - Amarelo\n");
			printf(" 2 - Verde\n");
			printf(" 3 - Azul\n ");
			while(1)
			{
				fgets( input, TAMANHO_MAX_INPUT, stdin );
				RemoverNovaLinha( input );
				if( InputEhDigito( input ) )
				{
					cor = atoi( input );
				}
				else
				{
					cor = -1;
				}
				if( cor >= 0 && cor <= 3 )
				{
					for( j = 0; j < i; j++)
					{
						if( cor == vetorJogador[j].cor )
						{
							printf(" Por favor, escolha outra cor. Esta ja esta sendo usada por outro jogador.\n");
							corValida = 0;
							break;
						}
					}
					if(corValida)
					{
						vetorJogador[i].cor = cor;
						break;
					}
					corValida = 1;
				}
				else
				{
					printf(" Por favor, digite o numero equivalente a uma cor valida\n");
				}
			}
			CriarPecaJogador(&(vetorJogador[i]));
		}
	
		return;
	} /* Fim função: JOGO  -Define os jogadores */

/***************************************************************************
*
*  $FC Função: JOGO  -Criar as peças dos jogadores
*
*  $ED Descrição da função
*		Cria as pecas dos jogadores da partida
*
*  $EP Parâmetros
*		jogador - referencia para um jogador da partida
*
*  $EAE Assertivas de entrada
*		jogador deve ser diferente de NULL
*		jogador deve possuir pecas
*
*  $EAE Assertivas de saida
*		Caso o valor de entrada esteja fora do padrao, o programa encerra
*		Caso algum erro ocorra, o programa encerra
*		Caso tudo ocorra corretamente, 
*			As pecas do jogador sao criadas com a cor correspondente ao jogador
*			O espaco de memoria para as pecas é alocado devidamente
*
***************************************************************************/

	void CriarPecaJogador( JOGO_Jogador* jogador )
	{
		int i;

		if( jogador == NULL )
		{
			printf(" Erro! jogador nao existe");
			scanf(" %s");
			exit(1);
		}

		jogador->pecas = ( PEC_tppPeca* ) malloc ( NUM_PECAS * sizeof( PEC_tppPeca ) );

		if( jogador->pecas == NULL )
		{
			printf(" Erro ao criar pecas para o jogador");
			scanf(" %s");
			exit(1);
		}

		for ( i = 0; i < NUM_PECAS; i++)
		{
			if(PEC_CriarPeca( &( jogador->pecas[i] ), jogador->cor ) != PEC_CondRetOK )
			{
				printf(" ERRO AO CRIAR PECA!!!!");
				scanf("%s");
				exit(1);
			}
		}

		return;
	} /* Fim função: JOGO  -Criar as peças dos jogadores */

/***************************************************************************
*
*  $FC Função: JOGO  -Destruir as peças do jogador
*
*  $ED Descrição da função
*		Destroi as pecas de um jogador da partida, desalocando a memoria que
*		estava reservada para elas
*
*  $EP Parâmetros
*		jogador - referencia para um jogador da partida
*
*  $EAE Assertivas de entrada
*		jogador deve ser diferente de NULL
*		jogador deve possuir pecas
*
*  $EAE Assertivas de saida
*		Caso o valor de entrada esteja fora do padrao, o programa encerra
*		Caso ocorra algum erro, o programa encerra
*		Caso tudo ocorra corretamente, 
*			As peças sao destruidas
*			A memoria alocada para as pecas é liberada
*
***************************************************************************/

	void DestruirPecaJogador( JOGO_Jogador* jogador )
	{
		int i;

		if( jogador == NULL )
		{
			printf(" Erro! jogador nao existe");
			scanf(" %s");
			exit(1);
		}

		if( jogador->pecas == NULL )
		{
			printf(" Erro! o jogador nao possui pecas");
			scanf(" %s");
			exit(1);
		}

		for ( i = 0; i < NUM_PECAS; i++)
		{
			if( PEC_DestruirPeca( jogador->pecas[i] ) != PEC_CondRetOK )
			{
				printf(" ERRO AO DESTRUIR PECA!!!!");
				scanf("%s");
				exit(1);
			}
		}

		free( jogador->pecas );

		return;
	} /* Fim função: JOGO  -Destruir as peças do jogador */

/***************************************************************************
*
*  $FC Função: JOGO  -Verifica comandos validos
*
*  $ED Descrição da função
*		Verifica se um comando é valido e, se for, realiza a funcao que
*		que esta atribuida a ele
*
*  $EP Parâmetros
*		comando - string que contem o comando
*		dado - ponteiro para armazenar o valor do dado, caso o comando
*				seja o de jogar o dado
*		vtJogadores - vetor com os jogadores da partida
*		quantidadeJogadores - inteiro com a quantidade de jogadores na partida
*		pTabuleiro - ponteiro para tabuleiro passado como referencia
*
*  $FV Valor retornado
*		1 - caso o comando seja de fato válido
*		0 - caso o comando nao seja válido
*
*  $EAE Assertivas de entrada
*		comando deve ser "d", "c", "t", "l" ou "s"
*		comando pode ser tanto maiusculo quanto minusculo
*		vtJogadores deve ser diferente de NULL
*		quantidadeJogadores deve ser inteiro entre MIN_JOGADORES e MAX_JOGADORES	
*		pTabuleiro deve ser diferente de NULL
*
*  $EAE Assertivas de saida
*		Caso o comando seja invalido, uma mensagem é imprimida e 0 é retornado
*		Caso o comando seja == "s", se os valores de entrada nao estao no padrao,
*		o programa encerra. Se os valores estao no padrao, 1 é retornado.
*		Caso o comando seja == "d", 1 é retornado e dado recebe um valor que
*		representa o lancamento do dado
*		Caso o comando seja qualquer outro valido, 1 é retornado
*
***************************************************************************/

	int VerificaComandoValido( char* comando, int* dado, JOGO_Jogador* vtJogadores, int quantidadeJogadores, TAB_tppTabuleiro pTabuleiro )
	{
		char resposta[21];
		char caracter = InputEhCaracter( comando );

		if ( caracter == NULL )
		{
			printf(" Por favor, digite apenas um caractere.\n");
			return 0;
		}

		caracter = tolower( caracter );

		if ( caracter == 'd' )
		{
			*dado = JogarDado();
			return 1;
		}
		else if ( caracter == 'c' )
		{
			ExibeComandosPossiveis();
			return 1;
		}
		else if ( caracter == 't' )
		{
			printf(" Tabuleiro:\n");
			TAB_ExibeTabuleiro();
			return 1;
		}
		else if ( caracter == 'l' )
		{
			TAB_ExibeLegendaTabuleiro();
			return 1;
		}
		else if ( caracter == 's' )
		{
			printf( " Tem certeza que deseja sair do jogo?\n"
					" Digite 's', no caso afirmativo\n"
					" Digite qualquer outra coisa, no caso negativo\n");
			fgets( resposta, TAMANHO_MAX_INPUT, stdin );
			RemoverNovaLinha( resposta );
			caracter = InputEhCaracter( resposta );
			caracter = tolower( caracter );
			if ( caracter == 's' )
			{
				if( vtJogadores == NULL )
				{
					printf(" Erro! jogadores nao existem");
					scanf("%s");
					exit(1);
				}

				if( quantidadeJogadores < MIN_JOGADORES || quantidadeJogadores > MAX_JOGADORES)
				{
					printf(" Erro! quantidade de jogadores invalida");
					scanf("%s");
					exit(1);
				}

				if( pTabuleiro == NULL )
				{
					printf(" Erro! tabuleiro nao existe");
					scanf("%s");
					exit(1);
				}

				printf("Obrigado por jogar");
				LiberarMemoria( vtJogadores, quantidadeJogadores, pTabuleiro );
				exit(0);
			}
			return 1;
		}
		else
		{
			printf(" Por favor, digite um comando valido.\n");
		}
		return 0;
	} /* Fim função: JOGO  -Verifica comandos validos */

/***************************************************************************
*
*  $FC Função: JOGO  -Exibe os comandos possiveis
*
*  $ED Descrição da função
*		Exibe os possiveis comandos que o usuario pode escrever
*
*  $EAE Assertivas de saida
*		Os comandos sao imprimidos na tela
*
***************************************************************************/

	void ExibeComandosPossiveis()
	{
		printf( " Digite a letra - T - para exibir o Tabuleiro\n"
				" Digite a letra - L - para exibir a Legenda do tabuleiro\n"
				" Digite a letra - S - para encerrar a partida e Sair do jogo\n"
				" Digite a letra - D - para jogar o Dado\n");
		return;
	} /* Fim função: JOGO  -Exbie os comandos possiveis */

/***************************************************************************
*
*  $FC Função: JOGO  -Jogar o dado
*
*  $ED Descrição da função
*		Realiza o lançamento do dado
*
*  $FV Valor retornado
*		Um inteiro que representa o numero tirado no dado
*
***************************************************************************/

	static int JogarDado ()
	{
		int valor ;
  
		srand ( (unsigned) time ( NULL ) ) ;
		valor = ( rand() % VALOR_MAX_DADO ) + 1 ;
	
		printf("\t\t\t+------+    \n");   
		printf("\t\t\t|`.    | `. \n");  
		printf("\t\t\t|  `+--+---+\n"); 
		printf("\t\t\t|   |  |   |\n");
		printf("\t\t\t+---+--+.  |\n");  
		printf("\t\t\t `. |    `.|\n");
		printf("\t\t\t   `+------+\n");
		printf("\n");
		printf("************  AO JOGAR O DADO VOCE OBTEVE O NUMERO: %d *************\n\n", valor);
		return valor;
	} /* Fim função: JOGO  -Jogar o dado */

/***************************************************************************
*
*  $FC Função: JOGO  -Verifica se existe movimento possivel
*
*  $ED Descrição da função
*		Verifica se pelo menos uma das pecas de um jogador pode realizar
*		um movimento
*
*  $EP Parâmetros
*		jogador - jogador da partida
*		pTabuleiro - ponteiro para tabuleiro passado como referencia
*		dado - inteiro com o valor tirado no dado relativo ao avanco da peca
*
*  $FV Valor retornado
*		1 - caso existe movimento possivel para o jogador
*		0 - caso nao exista movimento possivel para o jogador
*
*  $EAE Assertivas de entrada
*		jogador deve ser representado por uma cor valida, inteiro de 0 a NUM_CORES - 1
*		jogador deve possuir pecas
*		pTabuleiro deve ser diferente de NULL
*		dado deve se um inteiro de VALOR_MIN_DADO a VALOR_MAX_DADO
*
*  $EAE Assertivas de saida
*		Caso os valores de entrada nao sigam o padrao, o programa encerra
*		Caso ocorra tudo corretamente
*			Se pelo menos um movimento seja possivel, 1 é retornado
*			Se nenhum movimento seja possivel, 0 é retornado
*			A casa corrente do tabuleiro permanece a mesma em qualquer caso
*			A peca continua na casa que estava originalmente em qualquer caso
*		
*
***************************************************************************/

	int ExisteMovimentoPossivel(JOGO_Jogador jogador, TAB_tppTabuleiro pTabuleiro, int dado)
	{
		int i;
		TAB_CondRet retornoTabuleiro;
		int volta;

		if ( pTabuleiro == NULL )
		{
			printf(" Erro! valor do dado invalido");
			scanf("%s");
			exit(1);
		}

		if ( dado < VALOR_MIN_DADO || dado > VALOR_MAX_DADO )
		{
			printf(" Erro! valor do dado invalido");
			scanf("%s");
			exit(1);
		}

		if ( jogador.cor <= 0 || jogador.cor < NUM_CORES - 1 )
		{
			printf(" Erro! cor do jogador invalida");
			scanf("%s");
			exit(1);
		}

		if ( jogador.pecas == NULL )
		{
			printf(" Erro! jogador nao possui pecas");
			scanf("%s");
			exit(1);
		}

		if ( dado == 6 || dado == 1 )
		{
			if( ExistePecaCasaInicial(jogador) && QuantidadePecaCasaSaidaComMesmaCor(pTabuleiro, jogador.cor) < 2)
			{
				return 1;
			}
		}

		for ( i = 0; i < NUM_PECAS; i++ )
		{
			retornoTabuleiro = TAB_ProcurarPeca(pTabuleiro, jogador.pecas[i]);
			PEC_ObterVolta(jogador.pecas[i], &volta);
			if( retornoTabuleiro == TAB_CondRetOK )
			{
				retornoTabuleiro = TAB_AvancarCasa(pTabuleiro, jogador.cor, dado, !volta);
				if ( retornoTabuleiro == TAB_CondRetOK )
				{
					TAB_ProcurarPeca(pTabuleiro, jogador.pecas[i]); /* volta casa corrente */
					return 1;
				}
			}
		}

		return 0;
	} /* Fim função: JOGO  -Verifica se existe movimento possivel */

/***************************************************************************
*
*  $FC Função: JOGO  -Verifica se existe peca na casa inicial
*
*  $ED Descrição da função
*		Verifica se alguma peca do jogador esta na casa inicial
*
*  $EP Parâmetros
*		jogador - jogador da partida
*
*  $FV Valor retornado
*		1 - caso exista alguma peca na casa  inicial
*		0 - caso nao exista pecas na casa inicial
*
*  $EAE Assertivas de entrada
*		jogador deve possuir pecas
*
*  $EAE Assertivas de saida
*		Caso o jogador passado como entrada nao possua pecas, o programa encerra
*		Caso tudo ocorra corretamente, 
*			Se existem pecas na casa incial, retorna 1
*			Se nao existem pecas na casa inicial, retorna 0
*
***************************************************************************/

	int ExistePecaCasaInicial(JOGO_Jogador jogador)
	{
		int i;
		int estaNaCasaInicial;

		if ( jogador.pecas == NULL )
		{
			printf(" Erro! jogador nao possui pecas");
			scanf("%s");
			exit(1);
		}

		for( i = 0; i < NUM_PECAS; i++ )
		{
			PEC_ObterInicio(jogador.pecas[i], &estaNaCasaInicial);
			if( estaNaCasaInicial )
			{
				return 1;
			}
		}

		return 0;
	} /* Fim função: JOGO  -Verifica se existe peca na casa inicial */

/***************************************************************************
*
*  $FC Função: JOGO  -Verifica a quantidade de pecas em uma casa de saida
*															de mesma cor
*
*  $ED Descrição da função
*		Verifica a quantidade de pecas que estao na casa de saida da cor
*		especificada
*
*  $EP Parâmetros
*		pTabuleiro - ponteiro para tabuleiro passado como referencia
*		cor - inteiro referente a cor da casa de saida que deve ser analisada
*
*  $FV Valor retornado
*		Um inteiro com a quantidade de pecas que estao na casa saida com a cor
*		especificada
*
*  $EAE Assertivas de entrada
*		pTabuleiro deve ser diferente de NULL
*		cor deve ser um inteiro de 0 a NUM_CORES - 1
*
*  $EAE Assertivas de saida
*		Caso os valores de entrada nao estejam seguindo o padrao, o programa encerra
*		Caso algum erro ocorra, o programa encerra
*		Caso tudo ocorra corretamente, 
*			Retorna a quantidade de pecas na casa de saida com a cor especificada
*			A casa corrente do tabuleiro se torna tal casa de saida
*
***************************************************************************/

	int QuantidadePecaCasaSaidaComMesmaCor(TAB_tppTabuleiro pTabuleiro, int cor)
	{
		int corAux;
		int contador = 0;
		LIS_tppLista listaPeca;
		PEC_tppPeca peca;

		if ( pTabuleiro == NULL )
		{
			printf(" Erro! tabuleiro nao existe");
			scanf("%s");
			exit(1);
		}

		if ( cor <= 0 || cor > NUM_CORES - 1 )
		{
			printf(" Erro! cor invalida");
			scanf("%s");
			exit(1);
		}

		if ( TAB_IrCasaSaidaCor(pTabuleiro, cor) != TAB_CondRetOK )
		{
			printf(" Erro ao ir para casa de saida do tabuleiro");
			scanf("%s");
			exit(1);
		}

		if ( TAB_ObterConteudoCasa(pTabuleiro, &listaPeca) != TAB_CondRetOK )
		{
			printf(" Erro ao obter conteudo da casa do tabuleiro");
			scanf("%s");
			exit(1);
		}

		IrInicioLista( listaPeca );

		do {

			peca = (PEC_tppPeca) LIS_ObterValor( listaPeca );
	
			if ( peca != NULL )
			{
				PEC_ObterCor(peca, &corAux);
				if ( corAux == cor )
				{
					contador++;
				}
			} 
	
		} while ( LIS_AvancarElementoCorrente( listaPeca, 1 ) == LIS_CondRetOK );

		IrInicioLista( listaPeca );
		return contador;
	} /* Fim função: JOGO  -Verifica a quantidade de pecas em uma casa de
													saida de mesma cor*/

/***************************************************************************
*
*  $FC Função: JOGO  -Escolhe uma peca para movimentar
*
*  $ED Descrição da função
*		Permite que o jogador escolha uma de suas pecas para movimentar e realiza
*		a movimentação de tal peca escolhida
*
*  $EP Parâmetros
*		pTabuleiro - ponteiro para tabuleiro passado como referencia
*		jogador - referencia para um jogador da partida
*		dado - inteiro com o valor tirado no dado relativo ao avanco da peca
*
*  $EAE Assertivas de entrada
*		pTabuleiro deve ser diferente de NULL
*		jogador deve ser diferente de NULL
*		dado deve ser um inteiro de VALOR_MIN_DADO a VALOR_MAX_DADO
*		O jogador deve possuir pelo menos uma peca que tenha a possibilidade
*		de se movimentar
*
*  $EAE Assertivas de saida
*		Caso os valores de entrada nao estejam conforme o padrao, o programa encerra
*		Caso tudo ocorra corretamente,
*			Uma das pecas do jogador irá avancar o valor contido em dado
*			Se a peca estiver na casa inicial, irá para a casa de saida de sua cor
*			A casa corrente do tabuleiro se torna a casa que a peca atingiu
*
***************************************************************************/

	void EscolhePecaParaMovimentar(TAB_tppTabuleiro pTabuleiro, JOGO_Jogador* jogador, int dado)
	{
		char input[TAMANHO_MAX_INPUT];
		int indPeca;
		int movimentoPossivel;

		if( jogador == NULL )
		{
			printf(" Erro! jogador nao existe");
			scanf("%s");
			exit(1);
		}

		if( pTabuleiro == NULL )
		{
			printf(" Erro! tabuleiro nao existe");
			scanf("%s");
			exit(1);
		}

		if( dado < VALOR_MIN_DADO || dado > VALOR_MAX_DADO )
		{
			printf(" Erro! valor do dado invalido");
			scanf("%s");
			exit(1);
		}

		if( ExisteMovimentoPossivel( *jogador, pTabuleiro, dado ) == 0 )
		{
			printf(" Erro! jogador nao pode realizar movimento com nenhuma peca");
			scanf("%s");
			exit(1);
		}

		printf(" Escolha uma peca para movimentar:\n");
		printf(" 1 - Peca 1\n");
		printf(" 2 - Peca 2\n");
		printf(" 3 - Peca 3\n");
		printf(" 4 - Peca 4\n");

		movimentoPossivel = 0;

		while(!movimentoPossivel)
		{
			fgets( input, TAMANHO_MAX_INPUT, stdin );
			RemoverNovaLinha( input );

			if( InputEhDigito( input ) )
			{
				indPeca = atoi( input );
			}
			else
			{
				indPeca = -1;
			}

			if(indPeca < 1 || indPeca > NUM_PECAS)
			{
				printf(" Por favor, digite um numero entre 1 e 4.\n");
			}
			else
			{
				movimentoPossivel = MovimentarPecaSePossivel(pTabuleiro, jogador->pecas[--indPeca], dado);
				if(!movimentoPossivel)
				{
					indPeca = 0;
					printf(" Essa peca nao pode se mover. Por favor, escolha outra.\n");
				}
			}
		}

		return;
	} /* Fim função: JOGO  -Escolhe uma peca para movimentar */

/***************************************************************************
*
*  $FC Função: JOGO  -Movimenta a peca se for possivel
*
*  $ED Descrição da função
*		Avanca com a peca determinado numero de casas no tabuleiro, se possivel
*
*  $EP Parâmetros
*		pTabuleiro - ponteiro para tabuleiro passado por referencia
*		peca - ponteiro para peca que pretende se mover
*		dado - inteiro com o valor a ser avancado pela peca
*
*  $FV Valor retornado
*		1 - caso seja possivel realizar o movimento
*		0 - caso nao seja possivel movimentar a peca
*
*  $EAE Assertivas de entrada
*		pTabuleiro deve ser diferente de NULL
*		peca deve ser diferente de NULL
*		dado deve ser um inteiro de VALOR_MIN_DADO a VALOR_MAX_DADO
*
*  $EAE Assertivas de saida
*		Caso os valores de entrada estejam fora do padrao, o programa encerra
*		Caso ocorra um erro, o programa encerra
*		Caso ocorra tudo corretamente,
*			Se for possivel mover a peca, a peca avanca o valor contido em dado
*			ou entao sai da casa inicial para a casa de saida e a funcao 
*			retorna 1. A casa corrente do tabuleiro se torna a casa atingida pela 
*			peca em sua movimentacao.
*			Se nao for possivel mover, a peca permanece em sua casa, a funcao
*			retorna 0 e a casa corrente do tabuleiro continua a mesma que era
*
***************************************************************************/

	int MovimentarPecaSePossivel(TAB_tppTabuleiro pTabuleiro, PEC_tppPeca peca, int dado)
	{
		int inicio;
		int cor;
		int realizandoVolta;
		TAB_CondRet retornoTabuleiro;

		if( pTabuleiro == NULL )
		{
			printf(" Erro! tabuleiro nao existe");
			scanf("%s");
			exit(1);
		}

		if( peca == NULL )
		{
			printf(" Erro! peca nao existe");
			scanf("%s");
			exit(1);
		}

		if( dado < VALOR_MIN_DADO || dado > VALOR_MAX_DADO )
		{
			printf(" Erro! valor do dado invalido");
			scanf("%s");
			exit(1);
		}

		if( PEC_ObterInicio(peca, &inicio) != PEC_CondRetOK )
		{
			printf(" Erro ao obter inicio da peca");
			scanf("%s");
			exit(1);
		}

		if( PEC_ObterCor(peca, &cor) != PEC_CondRetOK )
		{
			printf(" Erro ao obter inicio da peca");
			scanf("%s");
			exit(1);
		}

		if( inicio )
		{
			if( ( dado == 6 || dado == 1 ) && QuantidadePecaCasaSaidaComMesmaCor( pTabuleiro, cor ) < 2 )
			{
				realizandoVolta = 0;
				if( PEC_ObterCor(peca, &cor) != PEC_CondRetOK )
				{
					printf(" Erro ao obter inicio da peca");
					scanf("%s");
					exit(1);
				}

				if( TAB_IrCasaSaidaCor(pTabuleiro, cor) != TAB_CondRetOK )
				{
					printf(" Erro ao ir para a casa de saida do tabuleiro");
					scanf("%s");
					exit(1);
				}

				if( TAB_InserirPecaCasa(pTabuleiro, peca, realizandoVolta) != TAB_CondRetOK )
				{
					printf(" Erro ao inserir peca na casa");
					scanf("%s");
					exit(1);
				}

				return 1;
			}
			else
			{
				return 0;
			}
		}

		retornoTabuleiro = TAB_ProcurarPeca(pTabuleiro, peca);

		if ( retornoTabuleiro == TAB_CondRetOK )
		{
			if( PEC_ObterVolta(peca, &realizandoVolta) != PEC_CondRetOK )
			{
				printf(" Erro ao obter volta da peca");
				scanf("%s");
				exit(1);
			}

			retornoTabuleiro = TAB_AvancarCasa(pTabuleiro, cor, dado, !realizandoVolta);

			if ( retornoTabuleiro == TAB_CondRetOK )
			{
				if( TAB_RetirarPecaCasa(pTabuleiro, peca) != TAB_CondRetOK )
				{
					printf(" Erro ao retirar peca");
					scanf("%s");
					exit(1);
				}

				if( TAB_AvancarCasa(pTabuleiro, cor, dado, !realizandoVolta) != TAB_CondRetOK )
				{
					printf(" Erro ao avancar casa");
					scanf("%s");
					exit(1);
				}

				if( TAB_InserirPecaCasa(pTabuleiro, peca, 1) != TAB_CondRetOK )
				{
					printf(" Erro ao inserir peca na casa");
					scanf("%s");
					exit(1);
				}

				return 1;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			printf(" Erro ao procurar peca no tabuleiro. \n");
			scanf("%s");
			exit(1);
		}
	} /* Fim função: JOGO  -Movimenta a pecas se for possivel */

/***************************************************************************
*
*  $FC Função: JOGO  -Exibe posicao das pecas
*
*  $ED Descrição da função
*		Exibe a posicao no tabuleiro de todas as pecas de todos os jogadores
*
*  $EP Parâmetros
*		pTabuleiro - ponteiro para tabuleiro passado por referencia
*		vetorJogadores - vetor com os jogadores da partida
*		numeroJogadores - inteiro com a quantidade de jogadores na partida
*
*  $EAE Assertivas de entrada
*		pTabuleiro deve ser diferente de NULL
*		vetorJogadores deve ser diferente de NULL
*		numeroJogadores deve ser inteiro de MIN_JOGADORES a MAX_JOGADORES
*
*  $EAE Assertivas de saida
*		Caso os valores de entrada estejam fora do padrao, o programa encerra
*		Caso ocorra algum erro, o programa encerra
*		Caso tudo ocorra corretamente, 
*			A disposicao das pecas no tabuleiro é imprimida na tela
*			A casa corrente do tabuleiro se torna a casa da ultima peca do ultimo jogador
*
***************************************************************************/

	void ExibePosicaoDasPecas(TAB_tppTabuleiro pTabuleiro, JOGO_Jogador* vetorJogadores, int numeroJogadores)
	{
		int i;
		int j;
		int numeroCasa;
		int casaFinal;
		TAB_CondRet tabuleiroRetorno;
		JOGO_Jogador jogador;

		if( pTabuleiro == NULL )
		{
			printf(" Erro! tabuleiro nao existe");
			scanf("%s");
			exit(1);
		}

		if( vetorJogadores == NULL )
		{
			printf(" Erro! jogadores nao existem");
			scanf("%s");
			exit(1);
		}

		if( numeroJogadores < MIN_JOGADORES || numeroJogadores > MAX_JOGADORES )
		{
			printf(" Erro! numero de jogadores invalido");
			scanf("%s");
			exit(1);
		}

		for ( i = 0; i < numeroJogadores; i++ )
		{
			jogador = vetorJogadores[i];
			printf(" Disposicao das pecas de %s:\n", jogador.nome);
			for( j = 0; j < NUM_PECAS; j++ )
			{
				printf(" Peca %d - Casa ", j + 1);

				tabuleiroRetorno = TAB_ProcurarPeca(pTabuleiro, jogador.pecas[j]);

				if ( tabuleiroRetorno == TAB_CondRetOK)
				{
					tabuleiroRetorno = TAB_ObterNumeroCasa(pTabuleiro, &numeroCasa);
					if ( tabuleiroRetorno == TAB_CondRetOK )
					{
						printf("%d", numeroCasa);
						if ( TAB_VerificaCasaFinal(pTabuleiro, &casaFinal) != TAB_CondRetOK )
						{
							printf(" Erro ao verificar casa final do tabuleiro");
							scanf("%s");
							exit(1);
						}
						if( casaFinal )
						{
							printf(" (Casa Final)\n");
						}
						else
						{
							printf("\n");
						}
					}
					else
					{
						printf("\n ERRO AO OBTER O NUMERO DA CASA!!!\n");
					}
				}
				else if ( tabuleiroRetorno == TAB_CondRetPecaCasaInicial)
				{
					printf("Inicial \n");
				}
				else
				{
					printf("\n ERRO AO PROCURAR PECA!!! %d\n", tabuleiroRetorno);
					scanf("%s");
					exit(1);
				}

			}
			printf("\n");
		}
	} /* Fim função: JOGO  -Exibe posicao das pecas */

/***************************************************************************
*
*  $FC Função: JOGO  -Verifica se o jogador venceu
*
*  $ED Descrição da função
*		Verifica se determinado jogador venceu a partida
*
*  $EP Parâmetros
*		pTabuleiro - ponteiro para tabuleiro passado por referencia
*		jogador - jogador da partida
*
*  $FV Valor retornado
*		1 - caso o jogador tenha ganhado o jogo
*		0 - caso o jogador nao tenha ganhado o jogo
*
*  $EAE Assertivas de entrada
*		pTabuleiro deve ser diferente de NULL
*		jogador deve possuir pecas
*
*  $EAE Assertivas de saida
*		Caso os valores de entrada estejam fora do padrão, programa encerra
*		Caso ocorra um erro, o programa encerra
*		Caso tudo ocorra corretamente,
*			Se o jogador venceu, retorna 1 e a casa corrente do tabuleiro se
*			torna a casa final da cor do jogador
*			Se o jogador nao venceu, retorna 0 e a casa corrente do tabuleiro
*			se torna a casa da primeira peca que nao esta na casa final
*
***************************************************************************/

	int VerificaSeVenceu( TAB_tppTabuleiro pTabuleiro, JOGO_Jogador jogador )
	{
		int i;
		int casaFinal;
		TAB_CondRet retornoTabuleiro;

		if ( pTabuleiro == NULL )
		{
			printf(" Erro! tabuleiro nao existe");
			scanf("%s");
			exit(1);
		}

		if ( jogador.pecas == NULL )
		{
			printf(" Erro! jogador nao possui pecas");
			scanf("%s");
			exit(1);
		}

		for ( i = 0; i < NUM_PECAS; i++ )
		{
			retornoTabuleiro = TAB_ProcurarPeca( pTabuleiro, jogador.pecas[i] );

			if ( retornoTabuleiro != TAB_CondRetOK && retornoTabuleiro != TAB_CondRetPecaCasaInicial)
			{
				printf(" Erro ao procurar peca");
				scanf("%s");
				exit(1);
			}

			if ( TAB_VerificaCasaFinal( pTabuleiro, &casaFinal ) != TAB_CondRetOK )
			{
				printf(" Erro ao verificar casa final");
				scanf("%s");
				exit(1);
			}

			if ( !casaFinal )
			{
				return 0;
			}

		}

		return 1;
	} /* Fim função: JOGO  -Verifica se o jogador venceu */

/***************************************************************************
*
*  $FC Função: JOGO  -Come peca do oponente se possivel
*
*  $ED Descrição da função
*		Come as pecas do oponente se for possivel
*
*  $EP Parâmetros
*		pTabuleiro - ponteiro para tabuleiro passado por referencia
*		cor - inteiro com o valor referente a cor do jogador que
*				possivelmente irá comer
*
*  $FV Valor retornado
*		1 - caso seja de fato possivel comer pecas do oponente
*		0 - caso nao seja possivel comer pecas do oponente
*
*  $EAE Assertivas de entrada
*		pTabuleiro deve ser diferente de NULL
*		cor deve ser um inteiro entre 0 e NUM_CORES - 1
*
*  $EAE Assertivas de saida
*		Caso os valores de entrada estejam fora do padrão, o programa encerra
*		Caso ocorra algum erro, o programa encerra
*		Caso tudo ocorra corretamente
*			Se for possivel comer uma ou mais pecas, as pecas do oponente
*			voltam para a casa inicial e a funcao retorna 1.
*			Se nao for possivel comer pecas, a funcar apenas retorna 0
*
***************************************************************************/

	int ComePecaOponenteSePossivel(TAB_tppTabuleiro pTabuleiro, int cor)
	{
		int casaSaida;
		int corAux;
		int contador = 0;
		LIS_tppLista listaPeca;
		PEC_tppPeca peca;

		if ( pTabuleiro == NULL )
		{
			printf(" Erro! tabuleiro nao existe");
			scanf("%s");
			exit(1);
		}

		if ( cor <= 0 || cor > NUM_CORES - 1 )
		{
			printf(" Erro! cor invalida");
			scanf("%s");
			exit(1);
		}

		if ( TAB_VerificaCasaSaida(pTabuleiro, &casaSaida) != TAB_CondRetOK )
		{
			printf(" Erro ao verificar se é casa de saida");
			scanf("%s");
			exit(1);
		}
	
		if ( casaSaida )
		{
			return 0;
		}

		if ( TAB_ObterConteudoCasa( pTabuleiro, &listaPeca ) != TAB_CondRetOK )
		{
			printf(" Erro ao obter conteudo da casa");
			scanf("%s");
			exit(1);
		}

		IrInicioLista( listaPeca );

		do {

			peca = (PEC_tppPeca) LIS_ObterValor( listaPeca );
	
			if ( peca != NULL )
			{
				if ( PEC_ObterCor(peca, &corAux) != PEC_CondRetOK )
				{

				}

				if ( corAux != cor )
				{
					contador++;

					if ( PEC_AtualizarInicioPeca( peca, 1 ) != PEC_CondRetOK )
					{
						printf(" Erro ao atualizar inicio da peca");
						scanf("%s");
						exit(1);
					}

					if ( PEC_AtualizarVoltaPeca( peca, 0 ) != PEC_CondRetOK )
					{
						printf(" Erro ao atualizar volta da peca");
						scanf("%s");
						exit(1);
					}

					if ( PEC_AtualizarFinalPeca( peca, 0 ) != PEC_CondRetOK )
					{
						printf(" Erro ao atualizar final da peca");
						scanf("%s");
						exit(1);
					}

					LIS_ExcluirElemento( listaPeca );
					IrInicioLista( listaPeca );
				}
			} 
	
		} while ( LIS_AvancarElementoCorrente( listaPeca, 1 ) == LIS_CondRetOK );

		return contador;
	} /* Fim função: JOGO  -Come peca do elemento se possivel */

/***************************************************************************
*
*  $FC Função: JOGO  -Verifica se input do usuario é digito
*
*  $ED Descrição da função
*		Verifica se o input do usuario é um digito, isto é, verifica se a
*		string passada é composta exclusivamente de caracteres de 0 a 9.
*
*  $EP Parâmetros
*		string - string contendo o input do usuario
*
*  $FV Valor retornado
*		1 - caso a string seja um digito
*		0 - caso a string não seja um digito
*
***************************************************************************/

	int InputEhDigito( char* string )
	{
		int i;
		int tamanho;

		tamanho = strlen(string);

		for ( i = 0; i < tamanho; i++ )
		{
			if ( !isdigit( string[i] ) )
			{
				return 0;
			}
		}

		return 1;
	} /* Fim função: JOGO  -Verifica se input do usuario é digito */

/***************************************************************************
*
*  $FC Função: JOGO  -Verifica se input do usuario é um caractere
*
*  $ED Descrição da função
*		Verifica se o input do usuário é um caractere, isto é, verifica se
*		a string passada é composta de apenas um caractere
*
*  $EP Parâmetros
*		string - string contendo o input do usuario
*
*  $FV Valor retornado
*		O proprio caractere - caso a string seja um caractere
*		NULL - caso a string não seja um caractere
*
***************************************************************************/

	char InputEhCaracter( char* string )
	{
		int tamanho;
		char caracter;

		tamanho = strlen(string);

		if( tamanho == 1 )
		{
			caracter = string[0];
			return caracter;
		}
		else
		{
			return NULL;
		}
	} /* Fim função: JOGO  -Verifica se input do usuario é caractere */

/***************************************************************************
*
*  $FC Função: JOGO  -Transforma input do usuario em minusculo
*
*  $ED Descrição da função
*		Transforma o input do usuario em minusculo
*		Se já estiver minusculo, permanece da mesma forma
*		Digitos nao podem ficar minusculos
*
*  $EP Parâmetros
*		string - string contendo o input do usuario
*
*  $EAE Assertivas de saida
*		A string passada como parametro é modificada
*		Se a string ja era minuscula, permanece igual
*
***************************************************************************/

	void TransformaInputEmMinusculo( char* string )
	{
		int i;
		int tamanho;

		tamanho = strlen(string);

		for ( i = 0; i < tamanho; i++ )
		{
			string[i] = tolower(string[i]);
		}

		string[i] = '\0';
		return;
	} /* Fim função: JOGO  -Transforma input do usuario em minusculo */

/***************************************************************************
*
*  $FC Função: JOGO  -Remove caractere \n de um string
*
*  $ED Descrição da funçã
*		Remove o caractere \n, que indica nova linha, se a string possuir
*
*  $EP Parâmetros
*		string - string contendo o input do usuario
*
*  $EAE Assertivas de saida
*		A string é modificada e passa a nao ter mais o \n
*		Se ja nao tinha \n, a string nao sofre alteração
*
***************************************************************************/

	void RemoverNovaLinha( char* string )
	{
		if ( ( strlen ( string ) > 0 ) && ( string [ strlen ( string ) - 1 ] == '\n' ) )
		{
			string [ strlen ( string ) - 1 ] = '\0';
		}
	} /* Fim função: JOGO  -Remove caractere \n de um string */

/***************************************************************************
*
*  $FC Função: JOGO  -Liberar a memoria alocada
*
*  $ED Descrição da função
*		Libera a memoria alocada para armazenar os jogadores da partida, suas
*		pecas e tambem o tabuleiro utilizado no jogo
*
*  $EP Parâmetros
*		vtJogadores - vetor com os jogadores da partida
*		quantidadeJogadores - inteiro com a quantidade de jogadores na partida
*		pTabuleiro - ponteiro para tabuleiro passado por referencia
*
*  $EAE Assertivas de entrada
*		vtJogadores deve ser diferente de NULL
*		quantidadeJogadores deve ser inteiro entre MIN_JOGADORES e MAX_JOGADORES
*		pTabuleiro nao deve ser NULL
*
*  $EAE Assertivas de saida
*		Caso os valores de entrada estejam fora do padrao, o programa encerra
*		Caso ocorra algum erro, o programa encerra
*		Caso tudo ocorra corretamente, 
*			O espaco de memoria alocado para os jogadores é liberado
*			As pecas dos jogadores sao destruidas, com memoria desalocada
*			O tabuleiro é destruido, com espaco de memoria alocado liberado
*
***************************************************************************/

	void LiberarMemoria( JOGO_Jogador* vtJogadores, int quantidadeJogadores, TAB_tppTabuleiro pTabuleiro )
	{
		int i;

		if ( vtJogadores == NULL )
		{
			printf(" Erro! jogadores nao existem");
			scanf("%s");
			exit(1);
		}

		if ( quantidadeJogadores < MIN_JOGADORES || quantidadeJogadores > MAX_JOGADORES )
		{
			printf(" Erro! quantidade de jogadores invalida");
			scanf("%s");
			exit(1);
		}

		if ( pTabuleiro == NULL ) 
		{
			printf(" Erro! tabuleiro nao existe");
			scanf("%s");
			exit(1);
		}

		for ( i = 0; i < quantidadeJogadores; i++ )
		{
			DestruirPecaJogador( &( vtJogadores[i] ) );
		}

		free ( vtJogadores );

		if ( TAB_DestruirTabuleiro ( pTabuleiro ) != TAB_CondRetOK )
		{
			printf(" Erro ao destruir tabuleiro");
			scanf("%s");
			exit(1);
		}

		return;
	} /* Fim função: JOGO  -Liberar a memoria alocada */

/************* Fim do módulo de implementação: JOGO Módulo jogo / Principal ****************/