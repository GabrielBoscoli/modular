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

#define MIN_JOGADORES 1
#define MAX_JOGADORES 4
#define NUM_PECAS 	  4
#define TAMANHO_MAX_INPUT 81

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

int ExisteMovimentoPossivel ( JOGO_Jogador jogador , TAB_tppTabuleiro tabuleiro , int dado );

int ExistePecaCasaInicial ( JOGO_Jogador jogador );

void EscolhePecaParaMovimentar ( TAB_tppTabuleiro tabuleiro , JOGO_Jogador* jogador , int dado );

int MovimentarPecaSePossivel ( TAB_tppTabuleiro tabuleiro , PEC_tppPeca peca , int dado );

void ExibePosicaoDasPecas ( TAB_tppTabuleiro tabuleiro , JOGO_Jogador* vetorJogadores , int numeroJogadores );

void ExibeComandosPossiveis();

int VerificaSeVenceu ( TAB_tppTabuleiro tabuleiro , JOGO_Jogador jogador );

int ComePecaOponenteSePossivel (TAB_tppTabuleiro tabuleiro , int cor );

int QuantidadePecaCasaSaidaComMesmaCor (TAB_tppTabuleiro tabuleiro , int cor );

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
}

void DefineJogadores( int numeroJogadores, JOGO_Jogador* vetorJogador )
{
	char input[TAMANHO_MAX_INPUT];
	int i;
	int j;
	int corValida = 1;
	int cor;
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
}

void CriarPecaJogador( JOGO_Jogador* jogador )
{
	int i;
	jogador->pecas = (PEC_tppPeca*) malloc (NUM_PECAS * sizeof(PEC_tppPeca));
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
}

void DestruirPecaJogador( JOGO_Jogador* jogador )
{
	int i;
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
}

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
}

void ExibeComandosPossiveis()
{
	printf( " Digite a letra - T - para exibir o Tabuleiro\n"
			" Digite a letra - L - para exibir a Legenda do tabuleiro\n"
			" Digite a letra - S - para encerrar a partida e Sair do jogo\n"
			" Digite a letra - D - para jogar o Dado\n");
	return;
}

static int JogarDado ( void )
{
	int valor ;
  
    srand ( (unsigned) time ( NULL ) ) ;
    valor = ( rand() % 6 ) + 1 ;
	
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
}

int ExisteMovimentoPossivel(JOGO_Jogador jogador, TAB_tppTabuleiro tabuleiro, int dado)
{
	int i;
	TAB_CondRet retornoTabuleiro;
	int volta;

	if (dado == 6 || dado == 1)
	{
		if( ExistePecaCasaInicial(jogador) && QuantidadePecaCasaSaidaComMesmaCor(tabuleiro, jogador.cor) < 2)
		{
			return 1;
		}
	}

	for ( i = 0; i < NUM_PECAS; i++ )
	{
		retornoTabuleiro = TAB_ProcurarPeca(tabuleiro, jogador.pecas[i]);
		PEC_ObterVolta(jogador.pecas[i], &volta);
		if( retornoTabuleiro == TAB_CondRetOK )
		{
			retornoTabuleiro = TAB_AvancarCasa(tabuleiro, jogador.cor, dado, !volta);
			if ( retornoTabuleiro == TAB_CondRetOK )
			{
				TAB_ProcurarPeca(tabuleiro, jogador.pecas[i]); /* volta casa corrente */
				return 1;
			}
		}
	}
	return 0;
}

int ExistePecaCasaInicial(JOGO_Jogador jogador)
{
	int i;
	int estaNaCasaInicial;
	for( i = 0; i < NUM_PECAS; i++ )
	{
		PEC_ObterInicio(jogador.pecas[i], &estaNaCasaInicial);
		if( estaNaCasaInicial )
		{
			return 1;
		}
	}
	return 0;
}

int QuantidadePecaCasaSaidaComMesmaCor(TAB_tppTabuleiro tabuleiro, int cor)
{
	int corAux;
	int contador = 0;
	LIS_tppLista listaPeca;
	PEC_tppPeca peca;

	TAB_IrCasaSaidaCor(tabuleiro, cor);
	TAB_ObterConteudoCasa(tabuleiro, &listaPeca);
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
}

void EscolhePecaParaMovimentar(TAB_tppTabuleiro tabuleiro, JOGO_Jogador* jogador, int dado)
{
	char input[TAMANHO_MAX_INPUT];
	int indPeca;
	int movimentoPossivel;
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
			movimentoPossivel = MovimentarPecaSePossivel(tabuleiro, jogador->pecas[--indPeca], dado);
			if(!movimentoPossivel)
			{
				indPeca = 0; /* BIZARRO ISSO */
				printf(" Essa peca nao pode se mover. Por favor, escolha outra.\n");
			}
		}
	}
	return;
}

int MovimentarPecaSePossivel(TAB_tppTabuleiro tabuleiro, PEC_tppPeca peca, int dado)
{
	int inicio;
	int cor;
	int realizandoVolta;
	TAB_CondRet retornoTabuleiro;
	PEC_ObterInicio(peca, &inicio);
	PEC_ObterCor(peca, &cor);

	if(inicio)
	{
		if((dado == 6 || dado == 1) && QuantidadePecaCasaSaidaComMesmaCor(tabuleiro, cor) < 2)
		{
			realizandoVolta = 0;
			PEC_ObterCor(peca, &cor);
			TAB_IrCasaSaidaCor(tabuleiro, cor);
			TAB_InserirPecaCasa(tabuleiro, peca, realizandoVolta);
			return 1;
		}
		else
		{
			return 0;
		}
	}

	retornoTabuleiro = TAB_ProcurarPeca(tabuleiro, peca);
	if ( retornoTabuleiro == TAB_CondRetOK )
	{
		PEC_ObterVolta(peca, &realizandoVolta);
		retornoTabuleiro = TAB_AvancarCasa(tabuleiro, cor, dado, !realizandoVolta);
		if ( retornoTabuleiro == TAB_CondRetOK )
		{
			TAB_RetirarPecaCasa(tabuleiro, peca);
			TAB_AvancarCasa(tabuleiro, cor, dado, !realizandoVolta);
			TAB_InserirPecaCasa(tabuleiro, peca, 1);
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
}

void ExibePosicaoDasPecas(TAB_tppTabuleiro tabuleiro, JOGO_Jogador* vetorJogadores, int numeroJogadores)
{
	int i;
	int j;
	int numeroCasa;
	int casaFinal;
	TAB_CondRet tabuleiroRetorno;
	JOGO_Jogador jogador;
	for ( i = 0; i < numeroJogadores; i++ )
	{
		jogador = vetorJogadores[i];
		printf(" Disposicao das pecas de %s:\n", jogador.nome);
		for( j = 0; j < NUM_PECAS; j++ )
		{
			printf(" Peca %d - Casa ", j + 1);

			tabuleiroRetorno = TAB_ProcurarPeca(tabuleiro, jogador.pecas[j]);

			if ( tabuleiroRetorno == TAB_CondRetOK)
			{
				tabuleiroRetorno = TAB_ObterNumeroCasa(tabuleiro, &numeroCasa);
				if ( tabuleiroRetorno == TAB_CondRetOK )
				{
					printf("%d", numeroCasa);
					TAB_VerificaCasaFinal(tabuleiro, &casaFinal);
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
}

int VerificaSeVenceu( TAB_tppTabuleiro tabuleiro, JOGO_Jogador jogador )
{
	int i;
	int casaFinal;
	for ( i = 0; i < NUM_PECAS; i++ )
	{
		TAB_ProcurarPeca(tabuleiro, jogador.pecas[i]);
		TAB_VerificaCasaFinal(tabuleiro, &casaFinal);
		if(!casaFinal)
		{
			return 0;
		}
	}
	return 1;
}

int ComePecaOponenteSePossivel(TAB_tppTabuleiro tabuleiro, int cor)
{
	int casaSaida;
	int corAux;
	int contador = 0;
	LIS_tppLista listaPeca;
	PEC_tppPeca peca;
	TAB_VerificaCasaSaida(tabuleiro, &casaSaida);
	
	if ( casaSaida )
	{
		return 0;
	}

	TAB_ObterConteudoCasa(tabuleiro, &listaPeca);
	IrInicioLista( listaPeca );

	do {

		peca = (PEC_tppPeca) LIS_ObterValor( listaPeca );
	
		if ( peca != NULL )
		{
			PEC_ObterCor(peca, &corAux);
			if ( corAux != cor )
			{
				contador++;
				PEC_AtualizarInicioPeca( peca, 1 );
				PEC_AtualizarVoltaPeca( peca, 0 );
				PEC_AtualizarFinalPeca( peca, 0 );
				LIS_ExcluirElemento( listaPeca );
				IrInicioLista( listaPeca );
			}
		} 
	
	} while ( LIS_AvancarElementoCorrente( listaPeca, 1 ) == LIS_CondRetOK );

	return contador;
}

int InputEhDigito(char* string)
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
}

char InputEhCaracter(char* string)
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
}

void TransformaInputEmMinusculo(char* string)
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
}

void RemoverNovaLinha(char* string)
{
	if ((strlen(string) > 0) && (string[strlen (string) - 1] == '\n'))
	{
        string[strlen (string) - 1] = '\0';
	}
}

void LiberarMemoria( JOGO_Jogador* vtJogadores, int quantidadeJogadores, TAB_tppTabuleiro pTabuleiro )
{
	int i;
	for ( i = 0; i < quantidadeJogadores; i++ )
	{
		DestruirPecaJogador( &(vtJogadores[i]) );
	}
	free ( vtJogadores );
	TAB_DestruirTabuleiro ( pTabuleiro );
	return;
}

/************* Fim do módulo de implementação: JOGO Módulo jogo / Principal ****************/
