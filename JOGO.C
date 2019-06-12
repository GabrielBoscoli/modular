/***************************************************************************
 *  $MCI Módulo de implementação: JOGO  Módulo Jogo / Principal
 *
 *  Arquivo gerado:              JOGO.c
 *  Letras identificadoras:      JOGO
 *
 *  Projeto: INF 1301 / Jogo de Ludo (ou Furbica)
 *  Gestor:  Professor Alessandro Garcia
 *  Autores: lr, dcr, rvc
 *
 *  $HA Histórico de evolução:
 *     Versão |  Autores   |      Data     |    Observações
 *       2    | lr,dcr,rvc |  01/dez/2016  | término desenvolvimento
 *       1    | lr,dcr,rvc |  25/nov/2016  | início desenvolvimento
 *
 ***************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "PECA.H"
#include "TABULEIRO.H"
#include "LISTA.H"

#define MIN_JOGADORES 1
#define MAX_JOGADORES 4
#define MAX_PECAS 	  4

/***********************************************************************
*
*  $TC Tipo de dados: JOGO Descritor dos dados dos jogadores
*
***********************************************************************/

typedef struct Jogador{

	char nome[81];
	/* Nome do Jogador */

	int cor;
	/* Cor do Jogador */

	PEC_tppPeca* pecas;
	/* Pecas do Jogador */

} JOGO_Jogador;

/***** Protótipo das funções encapsuladas no módulo *****/

int Ludo (void);

static int JogarDado ( void );

static void DesenhaPlacar ( PEC_tppPeca * pPecas , JOGO_Jogador * vtJogadores, int num_jogadores );

static void ordenaRanking ( JOGO_Jogador *vtJogadores , int *qtdfim , int n ) ;

static int VerificaVencedor ( PEC_tppPeca * pPecas, int num_jogadores, JOGO_Jogador * vtJogadores );

static int ValidaMovimento ( TAB_tppTabuleiro pTabuleiro , PEC_tppPeca pPeca , int n ) ;

static void RealizaMovimento ( TAB_tppTabuleiro pTabuleiro , PEC_tppPeca pPeca , int n ) ;

static int ValidaInsercao ( TAB_tppTabuleiro pTabuleiro , PEC_tppPeca pPeca ) ;

static void InserePecaJogo ( TAB_tppTabuleiro pTabuleiro , PEC_tppPeca pPeca ) ;

static int ObtemOrdemJogador ( void ) ;

static void MostraMovimentosValidos ( int *mapa ) ;

static void ZeraMapa ( int *mapa ) ;

static int TemMovimento ( int *mapa ) ;

int DefineNumeroJogadores();

void DefineJogadores ( int numeroJogadores , JOGO_Jogador* vetorJogador );

void CriarPecaJogador ( JOGO_Jogador* jogador );

int VerificaComandoValido ( char comando , int* dado );

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

/*****  Código da função principal do módulo  *****/

int main ()
{
	Ludo();
}

int Ludo (void)
{
	int i;
	int dado     	;
	int possuiVencedor     	;
	int cor = 0  	;
	int indPeca;
	int numJogadores = 0;
	int pecaComida;
	char digito ;

	JOGO_Jogador* vtJogadores ; 
	PEC_tppPeca peca ;
	TAB_tppTabuleiro  pTabuleiro  ;

	PEC_CondRet pecasRetorno     ;
	TAB_CondRet tabuleiroRetorno ;

	printf("\n Bem-vindo ao Jogo de Ludo.\n");
	printf(" Para saber as regras do jogo, por favor, verifique a especificacao de requisitos do projeto.\n\n");
    
    numJogadores = DefineNumeroJogadores();
	vtJogadores = (JOGO_Jogador*) malloc ( numJogadores * sizeof (JOGO_Jogador));
	DefineJogadores(numJogadores, vtJogadores);

    tabuleiroRetorno = TAB_CriarTabuleiro( &pTabuleiro ) ;
	
	if ( tabuleiroRetorno != TAB_CondRetOK )
	{
		printf("\n\n\tMEMORIA INSUFICIENTE PARA CRIAR TABULEIRO !!\n\n"); 
		scanf("%d");
		exit(1);
	}

	printf("\n\n----------------------------------------------------INICIO DO JOGO----------------------------------------------------\n\n");
	printf(" Tabuleiro:\n");
	TAB_ExibeTabuleiro();
	TAB_ExibeLegendaTabuleiro();
	printf("\n\n DIGITE A LETRA - D - PARA JOGAR O DADO OU ENTAO DIGITE - C - PARA VISUALIZAR TODOS OS COMANDOS VALIDOS\n\n");
	possuiVencedor = 0 ;

	while ( !possuiVencedor ) {
		for ( i = 0 ; i < numJogadores && possuiVencedor != 1 ; i++ ) 
		{	
			dado = 0;
			pecaComida = 0;
			printf( " VEZ DO JOGADOR : %s\n" , vtJogadores[i].nome ) ;
			scanf ( " %c" , &digito ) ;
			while ( !VerificaComandoValido( digito, &dado ) || !dado)
			{
				printf("\n\n DIGITE A LETRA - D - PARA JOGAR O DADO OU ENTAO DIGITE - C - PARA VISUALIZAR TODOS OS COMANDOS VALIDOS\n\n");
				scanf ( " %c" , &digito ) ;
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

	for ( i = 0; i < numJogadores; i++ )
	{
		DestruirPecaJogador( &(vtJogadores[i]) );
	}

	printf(" Parabens, %s. Voce eh o grande campeao!!!\n", vtJogadores[--i].nome);
	free( vtJogadores );
	TAB_DestruirTabuleiro( pTabuleiro );
	
	scanf("%d");
	return 0;
	/*
	DesenhaPlacar( vtPecas, vtJogadores , num_jogadores );

    for (i = 0 ; i < MAX_PECAS * num_jogadores ; i++ ) 
    {
    	PecasRetorno = PEC_DestroiPeca ( vtPecas[i] );
    	switch ( PecasRetorno ) 
			{
				case PEC_CondRetOK :
					break ;
				case PEC_CondRetNaoExiste : {
					printf("\n\n\tPECA NAO EXISTE !!\n\n");
					exit(1);
				}
				default :
					printf("\n\n\tERRO INESPERADO !!\n\n");
					exit(1);
			}
    }

    TabuleiroRetorno = TAB_DestruirTabuleiro ( pTabuleiro ) ; 

	printf("\n\n");
	printf("\t\t__/\\\\\\\\\\\\\\\\\\_________________________________________\n"); 
	printf("\t\t _\\/\\\\///////////___________________________________________\n"); 
	printf("\t\t  _\\/\\\\______________/\\\\___________________________________\n"); 
	printf("\t\t   _\\/\\\\\\\\\\\\_____\\///_____/\\\\\\__/\\\\\\_______________\n"); 
	printf("\t\t    _\\/\\\\///////_______/\\\\__/\\\\\\///\\\\\\///\\\\__________\n"); 
	printf("\t\t     _\\/\\\\____________\\/\\\\_\\/\\\\__\\//\\\\___\\/\\\\_______\n"); 
	printf("\t\t      _\\/\\\\____________\\/\\\\_\\/\\\\__\\//\\\\___\\/\\\\_______\n"); 
	printf("\t\t       _\\/\\\\____________\\/\\\\_\\/\\\\__\\//\\\\___\\/\\\\_______\n"); 
	printf("\t\t        _\\///______________\\///_ _\\///____\\////_____\\////________\n"); 
	printf("\n\n");

	return 0;*/

}    /* Fim função: MAIN */

/****************  Código das funções encapsuladas no módulo  **********************/

int DefineNumeroJogadores()
{
	int jogadores;
	printf(" Digite a quantidade de jogadores: ");
	while(1)
	{
		scanf("%d", &jogadores);
		if( jogadores < MIN_JOGADORES || jogadores > MAX_JOGADORES )
		{
			printf(" Por favor, digite um numero entre 2 e 4.\n");
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
	int i;
	int j;
	int corValida = 1;
	int cor;
	for(i = 0; i < numeroJogadores; i++)
	{
		printf(" Digite o nome do jogador %i: ", i + 1);
		scanf(" %80[^\n]", vetorJogador[i].nome);
		printf("\n");
		printf(" Digite a cor de %s: \n", vetorJogador[i].nome);
		printf(" 0 - Vermelho\n");
		printf(" 1 - Amarelo\n");
		printf(" 2 - Verde\n");
		printf(" 3 - Azul\n ");
		while(1)
		{
			scanf(" %d", &cor);
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
	jogador->pecas = (PEC_tppPeca*) malloc (MAX_PECAS * sizeof(PEC_tppPeca));
	for ( i = 0; i < MAX_PECAS; i++)
	{
		if(PEC_CriarPeca(&(jogador->pecas[i]), jogador->cor != PEC_CondRetOK))
		{
			printf(" ERRO AO CRIAR PECA!!!!");
			scanf("%d");
			exit(1);
		}
	}

	return;
}

void DestruirPecaJogador( JOGO_Jogador* jogador )
{
	int i;
	for ( i = 0; i < MAX_PECAS; i++)
	{
		if( PEC_DestruirPeca( jogador->pecas[i] ) != PEC_CondRetOK )
		{
			printf(" ERRO AO DESTRUIR PECA!!!!");
			scanf("%d");
			exit(1);
		}
	}

	free( jogador->pecas );

	return;
}

int VerificaComandoValido( char comando, int* dado )
{
	char resposta;
	if ( comando == 'd' || comando == 'D' )
	{
		*dado = JogarDado();
		return 1;
	}
	else if ( comando == 'c' || comando == 'C' )
	{
		ExibeComandosPossiveis();
		return 1;
	}
	else if ( comando == 't' || comando == 'T' )
	{
		printf(" Tabuleiro:\n");
		TAB_ExibeTabuleiro();
		return 1;
	}
	else if ( comando == 'l' || comando == 'L' )
	{
		TAB_ExibeLegendaTabuleiro();
		return 1;
	}
	else if ( comando == 's' || comando == 'S' )
	{
		printf( " Tem certeza que deseja sair do jogo?\n"
				" Digite 's', no caso afirmativo\n"
				" Digite qualquer outra letra, no caso negativo\n");
		scanf(" %c", &resposta);
		if ( resposta == 's' || resposta == 'S' )
		{
			printf("Obrigado por jogar");
			exit(0);
		}
		return 1;
	}
	else if ( comando == 'r' || comando == 'R' )
	{
		printf( " Tem certeza que deseja reiniciar a partida?\n"
				" Digite 's', no caso afirmativo\n"
				" Digite qualquer outra letra, no caso negativo\n");
		scanf(" %c", &resposta);
		if ( resposta == 's' || resposta == 'S' )
		{
			printf("Partida reiniciado...\n");
			Ludo();/* REVER ------------------------------------------------------------------------------------------------------------------------------------------*/
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
	printf( " Digite a letra - T - para exibir o tabuleiro\n"
			" Digite a letra - L - para exibir a legenda do tabuleiro\n"
			" Digite a letra - S - para sair do jogo\n"
			" Digite a letra - R - para reiniciar a partida\n"
			" Digite a letra - D - para jogar o dado\n");
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

	for ( i = 0; i < MAX_PECAS; i++ )
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
	for( i = 0; i < MAX_PECAS; i++ )
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
		scanf(" %d", &indPeca);
		printf("spielberg -> %d\n", 'd');
		if(indPeca < 1 || indPeca > MAX_PECAS)
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
		scanf("%d");
		exit(1);
	}
}

void ExibePosicaoDasPecas(TAB_tppTabuleiro tabuleiro, JOGO_Jogador* vetorJogadores, int numeroJogadores)
{
	int i;
	int j;
	int numeroCasa;
	TAB_CondRet tabuleiroRetorno;
	JOGO_Jogador jogador;
	for ( i = 0; i < numeroJogadores; i++ )
	{
		jogador = vetorJogadores[i];
		printf(" Disposicao das pecas de %s:\n", jogador.nome);
		for( j = 0; j < MAX_PECAS; j++ )
		{
			printf(" Peca %d - Casa ", j + 1);

			tabuleiroRetorno = TAB_ProcurarPeca(tabuleiro, jogador.pecas[j]);

			if ( tabuleiroRetorno == TAB_CondRetOK)
			{
				tabuleiroRetorno = TAB_ObterNumeroCasa(tabuleiro, &numeroCasa);
				if ( tabuleiroRetorno == TAB_CondRetOK )
				{
					printf("%d\n", numeroCasa);
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
				scanf("%d");
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
	for ( i = 0; i < MAX_PECAS; i++ )
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


/*

static void DesenhaPlacar ( PEC_tppPeca * pPecas , JOGO_Jogador * vtJogadores , int num_jogadores )
{
	int i, k, final ;
	int qtdfim[] = { 0 , 0 , 0 , 0 };
	PEC_CondRet PecasRetorno ;

	for(i = 0 ; i < num_jogadores ; i++)
	{
		for( k = 4 * i ; k < (4 * i) + 4 ; k++ )
		{
			PecasRetorno = PEC_ObtemFinal ( pPecas[k] , &final );
			switch ( PecasRetorno ) 
			{
				case PEC_CondRetOK :
					break ;

				case PEC_CondRetNaoExiste : {
					printf("\n\n\tPECA NAO EXISTE !!\n\n");
					exit(1) ;
				}
				default : {
					printf("\n\n\tERRO INESPERADO !!\n\n");
					exit(1) ;
				}
			}
			
			if ( final == 1 )
				qtdfim[i]++ ;
		}
	}
	
	ordenaRanking ( vtJogadores , qtdfim , num_jogadores ) ;

	for ( i = 0 ; i < num_jogadores ; i++ )
	{
		printf("JOGADOR: %s OBTEVE %d PONTOS !!\n", vtJogadores[i].nome ,qtdfim[i] );
	}
	printf("\n");
}



static int VerificaVencedor ( PEC_tppPeca * pPecas, int cor, JOGO_Jogador * vtJogadores )
{
	int i , final ;
	PEC_CondRet PecasRetorno ;
	for ( i = cor * MAX_PECAS ; i < (cor * MAX_PECAS) + MAX_PECAS ; i++ ) {
		PecasRetorno = PEC_ObtemFinal ( pPecas[i] , &final ) ;
		if ( final != 1 )
			return 0 ;
	}

	printf("\n\n");
	printf("\t\t.----------------------------------------------.\n");
    printf("\t\t|                                              |\n");
    printf("\t\t|     PARABENS !!! TEMOS UM VENCEDOR . . .     |\n");
    printf("\t\t|                                              |\n");
    printf("\t\t.----------------------------------------------.\n");
    printf("\n\n");
	printf("O JOGADOR %s E O VENCEDOR DO JOGO!!!\n\n", vtJogadores[cor].nome ); 

	return 1 ;
}



static void ordenaRanking ( JOGO_Jogador * vtJogadores , int *qtdfim , int n ) {		//ordenação descrescente 

	int fim , i ;
	int menor , aux ;

	JOGO_Jogador jogador_aux ;
	
	for ( fim = n - 1 ; fim > 0 ; fim-- ) {
		menor = 0 ;
		for ( i = 1 ; i <= fim ; i++ )
			if ( qtdfim[i] < qtdfim[menor] )
				menor = i ;
		
		aux = qtdfim[fim] ;
		qtdfim[fim] = qtdfim[menor] ;
		qtdfim[menor] = aux ; 

		jogador_aux = vtJogadores[fim] ;
		vtJogadores[fim] = vtJogadores[menor] ;
		vtJogadores[menor] = jogador_aux ;

	}

}		

static int ValidaMovimento ( TAB_tppTabuleiro pTabuleiro , PEC_tppPeca pPeca , int n )
{
	int cor , cor2 ;
	int final ;
	PEC_tppPeca conteudo ;
	TAB_CondRet TabuleiroRetorno ;
	PEC_CondRet PecasRetorno ;

	if ( n <= 0 || n > 6 )
		return 0 ;

	PecasRetorno = PEC_ObtemFinal ( pPeca , &final ) ;
	if ( PecasRetorno != PEC_CondRetOK ) {
		printf("\n\n\tPECA NAO EXISTE !!\n\n");
		exit(1) ;
	}

	if ( final == 1 )
		return 0 ;

	TabuleiroRetorno = TAB_ProcuraPeca ( pTabuleiro ,  pPeca ) ;
	switch ( TabuleiroRetorno ) {

		case TAB_CondRetOK : 
			break ;
		
		case TAB_CondRetNaoEncontrouPeca : {
			printf("\n\n\tPECA NAO ENCONTRADA !!\n\n");
			exit(1) ;
		}
		case TAB_CondRetPecaMorta : {
			return 0 ;
		}
		default : {
			printf("\n\n\tERRO INESPERADO !!\n\n");
			exit(1) ;
		}

	}

	PEC_ObtemCor ( pPeca , &cor ) ;

	TabuleiroRetorno = TAB_AvancaCasa ( pTabuleiro , cor , n ) ;
	if ( TabuleiroRetorno == TAB_CondRetFimTabuleiro )
		return 0 ;

	TAB_ObterPecaCasa ( pTabuleiro , &conteudo ) ;
	if ( conteudo != NULL ) {
		PEC_ObtemCor ( conteudo , &cor2 ) ;
		if ( cor == cor2 )
			return 0 ;
	}

	return 1 ;
}

static void RealizaMovimento ( TAB_tppTabuleiro pTabuleiro , PEC_tppPeca pPeca , int n )
{
	PEC_tppPeca conteudo ;
	TAB_CondRet TabuleiroRetorno ;
	int valid , cond , cor ;

	valid = ValidaMovimento ( pTabuleiro , pPeca , n ) ;
	if ( !valid ) {
		printf("\n\n\tMOVIMENTO INVALIDO !!\n\n");
		exit(1) ;
	}

	TabuleiroRetorno = TAB_RetiraPecaCasa ( pTabuleiro , pPeca ) ; 

	PEC_ObtemCor ( pPeca , &cor ) ;
	TAB_AvancaCasa ( pTabuleiro , cor , n ) ;

	TAB_EhCasaFinal ( pTabuleiro , &cond ) ;
	if ( cond )
		PEC_AtualizaPeca ( pPeca , 1 , 'D' ) ;

	else {
		TAB_ObterPecaCasa ( pTabuleiro , &conteudo ) ;

		if ( conteudo != NULL )
			PEC_AtualizaPeca ( conteudo , 0 , 'F' ) ;

		TAB_InserePecaCasa ( pTabuleiro , pPeca ) ;
	}




}

static int ValidaInsercao ( TAB_tppTabuleiro pTabuleiro , PEC_tppPeca pPeca ) 
{
	int cor , cor2 ;
	char status ;
	PEC_tppPeca conteudo ;
	PEC_CondRet PecasRetorno ;
	TAB_CondRet TabuleiroRetorno ;

	PecasRetorno = PEC_ObtemStatus ( pPeca , &status ) ;
	if ( PecasRetorno != PEC_CondRetOK ) {
		printf("\n\n\tPECA NAO EXISTE !!\n\n");
		exit(1) ;
	}
	if ( status == 'D' )
		return 0 ;

	PEC_ObtemCor ( pPeca , &cor ) ; 

	TabuleiroRetorno = TAB_IrInicioCor ( pTabuleiro , cor ) ;
	if ( TabuleiroRetorno != TAB_CondRetOK ) {
		printf("\n\n\tCOR INVALIDA !!\n\n");
		exit(1) ;
	}

	TAB_ObterPecaCasa ( pTabuleiro , &conteudo ) ;
	if ( conteudo != NULL ) {
		PEC_ObtemCor ( conteudo , &cor2 ) ;
		if ( cor == cor2 )
			return 0 ;
	}

	return 1 ;
} 

static void InserePecaJogo ( TAB_tppTabuleiro pTabuleiro , PEC_tppPeca pPeca )
{
	int cor , valid ;
	char status ;
	TAB_CondRet TabuleiroRetorno ;
	PEC_CondRet PecasRetorno ;

	valid = ValidaInsercao ( pTabuleiro , pPeca ) ;
	if ( !valid ) {
		printf("\n\n\tINSERCAO INVALIDA !!\n\n");
		exit(1) ;
	}

	PecasRetorno = PEC_ObtemStatus ( pPeca , &status ) ;
	if ( PecasRetorno != PEC_CondRetOK ) {
		printf("\n\n\tPECA NAO EXISTE !!\n\n");
		exit(1) ;
	}

	if ( status == 'D' ) {
		printf("\n\n\tPECA JA INSERIDA !!\n\n");
		exit(1) ;
	}


	PecasRetorno = PEC_ObtemCor ( pPeca , &cor ) ;

	TabuleiroRetorno = TAB_IrInicioCor ( pTabuleiro , cor ) ;
	if ( TabuleiroRetorno != TAB_CondRetOK ) {
		printf("\n\n\tCOR INVALIDA !!\n\n");
		exit(1) ;
	}

	TAB_InserePecaCasa ( pTabuleiro , pPeca ) ;

}

static int ObtemOrdemJogador ( void )
{
	int num ;
	printf ( "DIGITE O NUMERO DA PECA QUE DESEJA MOVIMENTAR : " ) ;
	scanf ( "%d" , &num ) ; 
	while ( num < 0 || num > 3 ) {
		printf("\n\n\tNUMERO INVALIDO !!\n\n");
		printf ( "DIGITE O NUMERO DA PECA QUE DESEJA MOVIMENTAR : " ) ;
		scanf ( "%d" , &num ) ; 
	}
	printf("\n\n");
	return num ;
}

static void MostraMovimentosValidos ( int *mapa )
{
	int i ; 
	printf("PECAS QUE PODEM SER MOVIDAS : ");
	for ( i = 0 ; i < MAX_PECAS ; i++ )
	{
		if ( mapa[i] == 1 )
			printf( "P%d " , i ) ;
	}
	printf("\n") ;
}

static void ZeraMapa ( int *mapa )
{
	int i ; 
	for ( i = 0 ; i < MAX_PECAS ; i++ )
		mapa[i] = 0 ;
}

static int TemMovimento ( int *mapa )
{
	int i ;
	for ( i = 0 ; i < MAX_PECAS ; i++ )
		if ( mapa[i] == 1 )
			return 1 ;
	return 0 ;
}*/


/************* Fim do módulo de implementação: JOGO Módulo jogo / Principal ****************/
