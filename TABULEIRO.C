/***************************************************************************
*  $MCI Módulo de implementação: Módulo Tabuleiro
*
*  Arquivo gerado:              TABULEIRO.c
*  Letras identificadoras:      TAB
*
*  Projeto: Disciplina INF 1301
*  Gestor:  DI/PUC-RIO, Professor Alessandro Garcia
*  Autores: gb - Gabriel Boscoli
*
*  $HA Histórico de evolução:
*     Versão     Autor        Data         Observações
*	   3.00       gb       14/06/2019   ajustes e leves mudanças
*      2.00       gb       28/04/2019   término, revisão e aperfeiçoamento
*      1.00       gb       26/04/2019   início desenvolvimento, implementação
*										de funções básicas
*
*  $ED Descrição do módulo
*	  Este módulo contém a implementação das funções definidas em TABULEIRO.H.
*
***************************************************************************/
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TABULEIRO_OWN
#include "TABULEIRO.H"
#undef TABULEIRO_OWN
 
/***********************************************************************
*
*  $TC Tipo de dados: TAB Descritor da cabeça do tabuleiro
*
*  $ED Descrição do tipo
*	  Descreve a organização e estrutura do tabuleiro.
*	  A cabeça do tabuleiro é o ponto de acesso para determinado tabuleiro.
*
***********************************************************************/

	typedef struct TAB_tagTabuleiro 
	{
		LISCIR_tppListaCircular casas ;
			/* Ponteiro para a lista de casas */

		int estaNaRetaFinal ;
			/* Indica se a casa corrente esta na reta final: 1 caso verdadeiro, 0 caso falso */
 
	} TAB_tpTabuleiro ;
 
/***********************************************************************
*
*  $TC Tipo de dados: TAB Descritor da casa do tabuleiro
*
*  $ED Descrição do tipo
*	  Descreve a organização e estrutura das casas do tabuleiro
*
***********************************************************************/
 
	typedef struct tagCasaTabuleiro 
	{
		int cor ;
			/* Indica a cor da casa */
 
		LIS_tppLista conteudo ;
			/* Ponteiro para o conteudo da casa, representado por uma lista */
 
		LIS_tppLista retaFinal ;
			/* Ponteiro para a reta final */

		int numeroCasa ;
			/* Numero correspondente a casa */
 
	} tagCasaTabuleiro ;

/***** Dados encapsulados no módulo *****/

	typedef void ( *pFunc ) ( void * ) ;
		/* ponteiro para função void */

	typedef void **ppVoid ;
		/* ponteiro para ponteiro void */

	#define BRANCO 5
		/* define a cor branco como o inteiro 5 */

	#define NUM_CORES 4
		/* define a quantidade de cores no tabuleiro
				sem contar o branco, que é neutro */
	
	#define NUM_CASAS_BRANCAS_ENTRE_CASAS_SAIDA 12
		/* define a quantidade de casas brancas, ou
			seja, neutras, entre casas de saidas */

	#define NUM_CASAS_RETA_FINAL 6
		/* define a quantidade de casas na reta final */

	#define NUMERO_CASAS_TRAJETO_CIRCULAR 52
		/* define o numero de casas no trajeto circular */
 
/***** Protótipo das funções encapsuladas no módulo *****/
 
	static tagCasaTabuleiro *CriaCasa ( LIS_tppLista retaFinal, int cor , int numeroCasa ) ;

	static void IrInicioRetaFinalCor ( TAB_tpTabuleiro *pTabuleiro , int cor ) ;
 
	static void LiberarCasa ( tagCasaTabuleiro *pCasa ) ;
 
/*****  Código das funções exportadas pelo módulo  *****/
 
/*************************************************************************** 
*
*  Função: TAB Criar tabuleiro
*  ****/
 
	TAB_CondRet TAB_CriarTabuleiro( TAB_tpTabuleiro **pTabuleiro )  
	{   
		int i, k , j ;

		int numeroCasa = 1;

		int numeroTotalCasasTrajetoCircular = NUMERO_CASAS_TRAJETO_CIRCULAR;

		int numeroCasaRetaFinal = numeroTotalCasasTrajetoCircular + 1;
 
		LISCIR_tppListaCircular pListaCirc ;
 
		LIS_tppLista pListaSimples ;

		tagCasaTabuleiro *casa ;
 
		LISCIR_CondRet retorno_LISCIR ;
 
		LIS_tpCondRet retorno_lis ;

		*pTabuleiro = ( TAB_tpTabuleiro *) malloc ( sizeof ( TAB_tpTabuleiro ) ) ;
    
		if ( *pTabuleiro == NULL )
		{
			return TAB_CondRetFaltouMemoria ;
		}
 
		retorno_LISCIR = LISCIR_CriarLista ( &pListaCirc , ( pFunc ) LiberarCasa ) ;

		if ( retorno_LISCIR != LISCIR_CondRetOK )
		{
			return TAB_CondRetFaltouMemoria ;
		} 
 
		for( i = 0 ; i < NUM_CORES ; i++ )
		{
         
			for( k = 0; k < NUM_CASAS_BRANCAS_ENTRE_CASAS_SAIDA ; k++ )
			{
 
				casa = CriaCasa ( NULL, BRANCO, numeroCasa) ;
				numeroCasa++;

				if ( casa == NULL )
				{
					return TAB_CondRetFaltouMemoria ;
				}

				retorno_LISCIR = LISCIR_InserirElementoApos( pListaCirc , casa ) ;

				if ( retorno_LISCIR != LISCIR_CondRetOK )
				{
					return TAB_CondRetFaltouMemoria ;
				}
 
			}/* cria 12 casas neutras para o trajeto circular */
 
			pListaSimples =  LIS_CriarLista( ( pFunc ) LiberarCasa) ;

			casa = CriaCasa ( pListaSimples, i , numeroCasa) ;
			numeroCasa++;

			if ( casa == NULL )
			{
				return TAB_CondRetFaltouMemoria ;
			}

			retorno_LISCIR = LISCIR_InserirElementoApos ( pListaCirc , casa ) ;
			/* insere uma casa de saida colorida no trajeto circular */

			if ( retorno_LISCIR !=  LISCIR_CondRetOK )
			{
				return TAB_CondRetFaltouMemoria ;
			}

			for ( j = 0 ; j < NUM_CASAS_RETA_FINAL ; j++ )
			{
 
				casa = CriaCasa ( NULL, i , numeroCasaRetaFinal) ;
				numeroCasaRetaFinal++;

				if ( casa == NULL )
				{
					return TAB_CondRetFaltouMemoria ;
				}
				retorno_lis = LIS_InserirElementoApos( pListaSimples , casa ) ;
				if ( retorno_lis != LIS_CondRetOK )
				{
					return TAB_CondRetFaltouMemoria ;
				}
                 
			}/* cria 6 casas para a reta final */
 
		}
 
		(*pTabuleiro)->casas = pListaCirc ;
		(*pTabuleiro)->estaNaRetaFinal = 0 ;
    
		return TAB_CondRetOK ;
 
	} /* Fim função: TAB Criar tabuleiro */

/*************************************************************************** 
*
*  Função: TAB Procura uma peça no tabuleiro
*  ****/

	TAB_CondRet TAB_ProcurarPeca ( TAB_tpTabuleiro *pTabuleiro , PEC_tppPeca pPeca )        
	{
		PEC_CondRet retorno_pec ;

		tagCasaTabuleiro *casa , *aux ;

		LISCIR_tppListaCircular lista_circular ;

		LIS_tppLista lista_simples ;

		LIS_tpCondRet retorno_lis ;

		int cor ;

		int status ;

		if (pTabuleiro == NULL)
		{
			return TAB_CondRetTabuleiroNaoExiste;
		}

		retorno_pec = PEC_ObterInicio(pPeca ,&status ) ;

		lista_circular = pTabuleiro->casas;

		if ( retorno_pec != PEC_CondRetOK )
		{
			return TAB_CondRetPecaNaoExiste ;
		}

		if ( status == 1 )
		{
			return TAB_CondRetPecaCasaInicial;
		}/* verifica peca na casa inicial */

		retorno_pec = PEC_ObterFinal(pPeca, &status);

		if ( retorno_pec != PEC_CondRetOK )
		{
			return TAB_CondRetPecaNaoExiste ;
		}

		if(status == 1)
		{
			PEC_ObterCor ( pPeca , &cor ) ;
			IrInicioRetaFinalCor ( pTabuleiro , cor ) ;

			LISCIR_ObterValor ( lista_circular , ( ppVoid ) &casa ) ;
			lista_simples = casa->retaFinal ;
			IrInicioLista ( lista_simples ) ;
    
			do{

				aux = (tagCasaTabuleiro*) LIS_ObterValor ( lista_simples ) ;
				IrInicioLista( aux->conteudo );

				if ( LIS_ProcurarValor(aux->conteudo, (void*) pPeca) == LIS_CondRetOK) 
				{
					pTabuleiro->estaNaRetaFinal = 1 ;      /* para indicar que entrou na reta final */
					return TAB_CondRetOK ;
				}

				retorno_lis = LIS_AvancarElementoCorrente ( lista_simples , 1 ) ;

			} while ( retorno_lis != LIS_CondRetFimLista ) ;
		}/* verifica peca na reta final de sua cor */

		lista_circular = pTabuleiro->casas ;
		LISCIR_ObterValor ( lista_circular , ( ppVoid ) &casa ) ;
		aux = casa ;
    
		do {
			IrInicioLista( aux->conteudo );

			if ( LIS_ProcurarValor(aux->conteudo, (void*) pPeca) == LIS_CondRetOK ) 
			{
				pTabuleiro->estaNaRetaFinal = 0 ;	/* nao esta na reta final */
				return TAB_CondRetOK ;
			}

			LISCIR_AvancarElementoCorrente ( lista_circular , 1 ) ;
			LISCIR_ObterValor ( lista_circular , ( ppVoid ) &aux ) ;

		} while ( aux != casa ) ; /* verifica peca no trajeto circular */

		return TAB_CondRetNaoEncontrouPeca ;
   
	}  /* Fim função: TAB Procura uma peca no tabuleiro */

/*************************************************************************** 
*
*  Função: TAB Obter as peças que estão na casa
*  ****/

	TAB_CondRet TAB_ObterConteudoCasa ( TAB_tpTabuleiro *pTabuleiro, LIS_tppLista *pListaPeca )
	{
		tagCasaTabuleiro *casa ;
		LISCIR_tppListaCircular lista_circular ;
		LIS_tppLista lista_simples ;

		if ( pTabuleiro == NULL )
		{
			return TAB_CondRetTabuleiroNaoExiste;
		}
    
		lista_circular = pTabuleiro->casas ;
		LISCIR_ObterValor ( lista_circular , ( ppVoid ) &casa );

		if ( pTabuleiro->estaNaRetaFinal  ) 
		{
			lista_simples = casa->retaFinal ;
			casa = ( tagCasaTabuleiro* ) LIS_ObterValor ( lista_simples ) ;
		}/* se estiver na reta final */

		*pListaPeca = casa->conteudo ;
		if ( *pListaPeca == NULL )
		{
			return TAB_CondRetConteudoNulo;
		}

		return TAB_CondRetOK ; 

	}   /* Fim função: TAB Obter as peças que estão na casa */

/*************************************************************************** 
*
*  Função: TAB Avança Casa
*  ****/

	TAB_CondRet TAB_AvancarCasa ( TAB_tpTabuleiro *pTabuleiro , int cor , int n , int volta )
	{
		tagCasaTabuleiro *casa ;
		LISCIR_tppListaCircular lista_circular ;
		LIS_tppLista lista_simples ;
		LIS_tpCondRet retorno_lis ;
		int controle = 0;

		if (pTabuleiro == NULL)
		{
			return TAB_CondRetTabuleiroNaoExiste;
		}

		if ( cor < 0 || cor > NUM_CORES - 1 )
		{
			return TAB_CondRetCorInvalida ;
		}

		if( n < 0 )
		{
			return TAB_CondRetAvancoInvalido;
		}
    
		lista_circular = pTabuleiro->casas ;
		LISCIR_ObterValor ( lista_circular , ( ppVoid ) &casa ) ;
    
		if ( pTabuleiro->estaNaRetaFinal  ) 
		{
			lista_simples = casa->retaFinal ;
			retorno_lis = LIS_AvancarElementoCorrente ( lista_simples , n ) ;
			if ( retorno_lis == LIS_CondRetFimLista )
				return TAB_CondRetFimTabuleiro ;
				/* nao da para avancar */

			return TAB_CondRetOK ;

		}/* se estiver na reta final */

		if( casa->cor == cor && n > 0 && volta)
		{
			LISCIR_AvancarElementoCorrente ( lista_circular , 1 ) ;
			LISCIR_ObterValor ( lista_circular , ( ppVoid ) &casa ) ;
			--n;
		}

		while ( casa->cor != cor && n != 0 ) 
		{

			LISCIR_AvancarElementoCorrente ( lista_circular , 1 ) ;
			LISCIR_ObterValor ( lista_circular , ( ppVoid ) &casa ) ;
			n-- ;

		}/* avanca ate chegar na casa de saida da cor ou acabar o movimento */

		if ( n != 0 ) 
		{
			lista_simples = casa->retaFinal ;
			IrInicioLista ( lista_simples ) ;
			retorno_lis = LIS_AvancarElementoCorrente ( lista_simples , n - 1 ) ;
			if ( retorno_lis == LIS_CondRetFimLista )
				return TAB_CondRetFimTabuleiro ;
			pTabuleiro->estaNaRetaFinal = 1 ;
		}/* caso tenha passado pela casa de saida da cor */

		return TAB_CondRetOK ;

	}   /* Fim função: TAB Avança Casa */

/*************************************************************************** 
*
*  Função: TAB Retira uma peça da casa
*  ****/

	TAB_CondRet TAB_RetirarPecaCasa ( TAB_tpTabuleiro *pTabuleiro , PEC_tppPeca pPeca ) 
	{
		LISCIR_tppListaCircular lista_circular ;
		LIS_tppLista lista_simples ;
		tagCasaTabuleiro *casa ;
		TAB_CondRet retorno_tab ;

		if (pTabuleiro == NULL)
		{
			return TAB_CondRetTabuleiroNaoExiste;
		}

		retorno_tab = TAB_ProcurarPeca ( pTabuleiro , pPeca ) ;

		if ( retorno_tab != TAB_CondRetOK )
		{
			return retorno_tab ;
		}

		lista_circular = pTabuleiro->casas ;

		LISCIR_ObterValor ( lista_circular , ( ppVoid ) &casa ) ;

		if ( pTabuleiro->estaNaRetaFinal  ) 
		{
			lista_simples = casa->retaFinal ;
			casa = (tagCasaTabuleiro*) LIS_ObterValor ( lista_simples) ;
		}/* se a peca esta na reta final */
    
		IrInicioLista(casa->conteudo);
		LIS_ProcurarValor(casa->conteudo, (void *) pPeca);
		LIS_ExcluirElemento(casa->conteudo);

		PEC_AtualizarFinalPeca ( pPeca , 0 ) ;

		PEC_AtualizarInicioPeca ( pPeca, 1 ) ;

		PEC_AtualizarVoltaPeca ( pPeca, 0 ) ;

		return TAB_CondRetOK ;

	}   /* Fim função: TAB Retira uma peça da casa */

/*************************************************************************** 
*
*  Função: TAB Insere uma peça na casa
*  ****/

	TAB_CondRet TAB_InserirPecaCasa ( TAB_tpTabuleiro *pTabuleiro , PEC_tppPeca pPeca , int volta ) 
	{
		LISCIR_tppListaCircular lista_circular ;
		LIS_tppLista lista_simples ;
		tagCasaTabuleiro *casa ;
		PEC_CondRet retorno_pec ;
		int cor ;

		if (pTabuleiro == NULL)
		{
			return TAB_CondRetTabuleiroNaoExiste;
		}

		retorno_pec = PEC_ObterCor ( pPeca , &cor ) ;
		if ( retorno_pec != PEC_CondRetOK )
		{
			return TAB_CondRetPecaNaoExiste ;
		}

		lista_circular = pTabuleiro->casas ;
		LISCIR_ObterValor ( lista_circular , ( ppVoid ) &casa ) ;

		if ( pTabuleiro->estaNaRetaFinal  ) 
		{
			lista_simples = casa->retaFinal ;
			casa = (tagCasaTabuleiro*)LIS_ObterValor ( lista_simples ) ;
			PEC_AtualizarFinalPeca ( pPeca, 1 );
		}/* se o corrente estiver na reta final */

		PEC_AtualizarInicioPeca ( pPeca, 0 ) ;

		if ( volta )
		{
			PEC_AtualizarVoltaPeca ( pPeca, 1 ) ;
		}
		else
		{
			PEC_AtualizarVoltaPeca ( pPeca, 0 ) ;
		}

		LIS_InserirElementoApos(casa->conteudo, (void *) pPeca);

		return TAB_CondRetOK ;

	}  /* Fim função: TAB Insere uma peça na casa */


/*************************************************************************** 
*
*  Função: TAB Ir para a casa de saída da cor
*  ****/
 
	TAB_CondRet TAB_IrCasaSaidaCor ( TAB_tpTabuleiro *pTabuleiro , int cor )
	{
		LISCIR_tppListaCircular lista_circular ;

		if (pTabuleiro == NULL)
		{
			return TAB_CondRetTabuleiroNaoExiste;
		}

		if ( cor < 0 || cor > NUM_CORES - 1 )
		{
			return TAB_CondRetCorInvalida ;
		}

		lista_circular = pTabuleiro->casas ;

		IrInicioRetaFinalCor ( pTabuleiro , cor ) ;
    
		//LISCIR_AvancarElementoCorrente ( lista_circular , 2 ) ;

		return TAB_CondRetOK ;

	}   /* Fim função: TAB Ir para a casa de saída da cor */

/***************************************************************************
*
*  Função: TAB Destroi Tabuleiro
*  ****/
 
	TAB_CondRet TAB_DestruirTabuleiro ( TAB_tpTabuleiro *pTabuleiro )
	{
		if (pTabuleiro == NULL)
		{
			return TAB_CondRetTabuleiroNaoExiste;
		}
 
		LISCIR_DestruirLista ( pTabuleiro->casas ) ;
 
		return TAB_CondRetOK ;
 
	} /* Fim função: TAB Destroi Tabuleiro */

/***************************************************************************
*
*  Função: TAB Verifica se é casa final
*  ****/

	TAB_CondRet TAB_VerificaCasaFinal ( TAB_tpTabuleiro *pTabuleiro , int *pResposta )
	{
		tagCasaTabuleiro *casa ;
		LISCIR_tppListaCircular lista_circular ;
		LIS_tppLista lista_simples ;
		LIS_tpCondRet retorno_lis ;

		if (pTabuleiro == NULL)
		{
			return TAB_CondRetTabuleiroNaoExiste;
		}
    
		if ( pTabuleiro->estaNaRetaFinal ) 
		{
			lista_circular = pTabuleiro->casas ;
			LISCIR_ObterValor ( lista_circular , ( ppVoid ) &casa ) ;
        
			lista_simples = casa->retaFinal ;
			retorno_lis = LIS_AvancarElementoCorrente ( lista_simples , 1 ) ;
			if ( retorno_lis == LIS_CondRetFimLista )
			{
				* pResposta = 1 ;
			}
			else 
			{
				LIS_AvancarElementoCorrente ( lista_simples , -1 ) ;
				* pResposta = 0 ;
			}
		}
		else
			*pResposta = 0 ;

		return TAB_CondRetOK ;

	}  /* Fim função: TAB Verifica se é casa final */

/***************************************************************************
*
*  Função: TAB Exibe Tabuleiro
*  ****/

	TAB_CondRet TAB_ExibeTabuleiro ( )
	{
		printf(					" .-----------------------.---.---.---.-----------------------.\n" 
                                " |                       |23 |24 |25 |                       |\n" 
                                " |                       |---+---+---.                       |\n" 
								" |                       |22 |59 |26 |--> CSY                |\n" 
                                " |                       |---+---+---.                       |\n" 
                                " |                       |21 |60 |27 |                       |\n" 
                                " |                       |---+---+---|                       |\n" 
                                " |                       |20 |61 |28 |                       |\n" 
                                " |                       |---+---+---|                       |\n" 
                                " |                       |19 |62 |29 |                       |\n" 
                                " |    CSR                |---+---+---|                       |\n" 
                                " |     |                 |18 |63 |30 |                       |\n" 
                                " |---.---.---.---.---.---+---+---+---+---.---.---.---.---.---|\n" 
                                " |12 |13 |14 |15 |16 |17 |   |64 |   |31 |32 |33 |34 |35 |36 |\n" 
                                " |---+---+---+---+---+---+---+---+---+---+---+---+---+---+---|\n" 
                                " |11 |53 |54 |55 |56 |57 |58 |   |70 |69 |68 |67 |66 |65 |37 |\n" 
                                " |---+---+---+---+---+---+---+---+---+---+---+---+---+---+---|\n" 
								" |10 | 9 | 8 | 7 | 6 | 5 |   |76 |   |43 |42 |41 |40 |39 |38 |\n" 
                                " |---^---^---^---^---^---+---+---+---+---^---^---^---^---^---|\n" 
                                " |                       | 4 |75 |44 |                 |     |\n" 
                                " |                       |---+---+---|                CSG    |\n" 
                                " |                       | 3 |74 |45 |                       |\n" 
                                " |                       |---+---+---|                       |\n" 
                                " |                       | 2 |73 |46 |                       |\n" 
                                " |                       |---+---+---|                       |\n" 
                                " |                       | 1 |72 |47 |                       |\n" 
                                " |                       |---+---+---|                       |\n" 
                                " |                CSB <--|52 |71 |48 |                       |\n" 
                                " |                       |---+---+---|                       |\n" 
                                " |                       |51 |50 |49 |                       |\n" 
								" ^-----------------------^---^---^---^-----------------------^\n" );

		return TAB_CondRetOK ;

	}  /* Fim função: TAB Exibe Tabuleiro */

/***************************************************************************
*
*  Função: TAB Exibe Legenda do Tabuleiro
*  ****/

	TAB_CondRet TAB_ExibeLegendaTabuleiro ( )
	{
		printf(" Legenda: \n"
			" Os numeros nas casa servem como uma forma de identificacao.\n"
			" CSB - casa numero 52: casa de saida de cor azul (Blue).\n"
			" CSR - casa numero 13: casa de saida de cor vermelha (Red).\n"
			" CSY - casa numero 26: casa de saida de cor amarela (Yellow).\n"
			" CSG - casa numero 39: casa de saida de cor verde (Green).\n"
			" Casas de numero 71 a 76: reta final de cor azul, sendo a casa 76 a casa final.\n"
			" Casas de numero 53 a 58: reta final de cor vermelha, sendo a casa 58 a casa final.\n"
			" Casas de numero 59 a 64: reta final de cor amarela, sendo a casa 64 a casa final.\n"
			" Casas de numero 65 a 70: reta final de cor verde, sendo a casa 70 a casa final.\n"
			" As demais casas fazem parte do trajeto circular e nao possuem funcao especifica.\n");

		return TAB_CondRetOK ;

	}  /* Fim função: TAB Exibe Legenda do Tabuleiro */

/***************************************************************************
*
*  Função: TAB Obter Numero de uma Casa
*  ****/

	TAB_CondRet TAB_ObterNumeroCasa( TAB_tpTabuleiro *pTabuleiro, int* pNumeroCasa )
	{
		tagCasaTabuleiro *casa ;
		LISCIR_tppListaCircular listaCircular ;
		LIS_tppLista listaSimples ;

		if (pTabuleiro == NULL)
		{
			return TAB_CondRetTabuleiroNaoExiste;
		}

		listaCircular = pTabuleiro->casas ;
		if ( LISCIR_ObterValor ( listaCircular , ( ppVoid ) &casa ) != LIS_CondRetOK )
		{
			return TAB_CondRetTrajetoCircularInexistente;
		}

		if ( pTabuleiro->estaNaRetaFinal )
		{
			listaSimples = casa->retaFinal;
			casa = (tagCasaTabuleiro*) LIS_ObterValor(listaSimples);
		}

		if ( casa == NULL )
		{
			return TAB_CondRetCasaNula;
		}

		*pNumeroCasa = casa->numeroCasa;
		return TAB_CondRetOK ;

	}  /* Fim função: TAB Obter Numero de uma Casa */

/***************************************************************************
*
*  Função: TAB Verifica se é casa de saida
*  ****/

	TAB_CondRet TAB_VerificaCasaSaida ( TAB_tpTabuleiro *pTabuleiro , int *pResposta )
	{
		tagCasaTabuleiro *casa ;
		LISCIR_tppListaCircular listaCircular ;

		if ( pTabuleiro == NULL )
		{
			return TAB_CondRetTabuleiroNaoExiste;
		}

		if ( pTabuleiro->estaNaRetaFinal )
		{
			*pResposta = 0;
		}
		else
		{
			listaCircular = pTabuleiro->casas ;
			if( LISCIR_ObterValor ( listaCircular , ( ppVoid ) &casa ) != LIS_CondRetOK )
			{
				return TAB_CondRetTrajetoCircularInexistente;
			}
			if ( casa == NULL )
			{
				return TAB_CondRetCasaNula;
			}
			if ( casa->retaFinal != NULL )
			{
				*pResposta = 1;
			}
			else
			{
				*pResposta = 0;
			}
		}

		return TAB_CondRetOK ;

	}  /* Fim função: TAB Verifica se é casa de saida */
 
 
/****************  Código das funções encapsuladas no módulo  **********************/
 
/*************************************************************************** 
*
*  Função: TAB Criar Casa
*  ****/

	static tagCasaTabuleiro * CriaCasa ( LIS_tppLista retaFinal , int cor, int numeroCasa )
	{
		tagCasaTabuleiro *nv ;

		LIS_tppLista pListaConteudo;
     
		nv  = (tagCasaTabuleiro *) malloc ( sizeof ( tagCasaTabuleiro ) ) ;
     
		if( nv == NULL )
		{
			return NULL ;
		}

		pListaConteudo = LIS_CriarLista( /*( pFunc ) PEC_DestruirPeca*/ NULL) ;
 
		nv->cor = cor ;
 
		nv->retaFinal = retaFinal ;
 
		nv->conteudo = pListaConteudo ;

		nv->numeroCasa = numeroCasa;
 
		return nv ;

	}  /* Fim função: TAB Criar Casa */


/*************************************************************************** 
*
*  Função: TAB Ir Reta Final Cor
*  ****/

	static void IrInicioRetaFinalCor ( TAB_tpTabuleiro *pTabuleiro , int cor )
	{
		tagCasaTabuleiro *casa ;
		LISCIR_tppListaCircular lista_circular ;

		lista_circular = pTabuleiro->casas ;

		LISCIR_ObterValor ( lista_circular , ( ppVoid ) &casa ) ;
		while ( casa->cor != cor ) 
		{
			LISCIR_AvancarElementoCorrente ( lista_circular , 1 ) ;
			LISCIR_ObterValor ( lista_circular , ( ppVoid ) &casa ) ;
		}
		pTabuleiro->estaNaRetaFinal = 0 ;

	}  /* Fim função: TAB Ir Reta Final Cor */


/*************************************************************************** 
*
*  Função: TAB Liberar Casa
*  ****/

	static void LiberarCasa ( tagCasaTabuleiro *pCasa ) 
	{
 
		if ( pCasa->retaFinal != NULL )
		{
			LIS_DestruirLista( pCasa->retaFinal ) ;
		}
 
		if ( pCasa->conteudo != NULL )
		{
			LIS_DestruirLista( pCasa->conteudo ) ;
		}
     
		pCasa = NULL ;

	}   /* Fim função: TAB Liberar Casa */

/*********** Fim do módulo de implementação: TAB Modulo Tabuleiro **********/