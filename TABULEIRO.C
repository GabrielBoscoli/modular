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
 
	} tagCasaTabuleiro ;

/***** Dados encapsulados no módulo *****/

	typedef void ( *pFunc ) ( void * ) ;
		/* ponteiro para função void */

	typedef void **ppVoid ;
		/* ponteiro para ponteiro void */

	#define BRANCO 5
		/* define a cor branco como o inteiro 5 */
 
/***** Protótipo das funções encapsuladas no módulo *****/
 
	static tagCasaTabuleiro *CriaCasa ( LIS_tppLista retaFinal, int cor ) ;

	static void IrRetaFinalCor ( TAB_tpTabuleiro *pTabuleiro , int cor ) ;
 
	static void LiberarCasa ( tagCasaTabuleiro *pCasa ) ;
 
/*****  Código das funções exportadas pelo módulo  *****/
 
/*************************************************************************** 
*
*  Função: TAB Criar tabuleiro
*  ****/
 
	TAB_CondRet TAB_CriarTabuleiro( TAB_tpTabuleiro **pTabuleiro )  
	{   
		int i, k , j ;
 
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
 
		for( i = 0 ; i < 4 ; i++ )
		{
         
			for( k = 0; k < 12 ; k++ )
			{
 
				casa = CriaCasa ( NULL, BRANCO ) ;

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

			casa = CriaCasa ( pListaSimples, i ) ;

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

			for ( j = 0 ; j < 6 ; j++ )
			{
 
				casa = CriaCasa ( NULL, i ) ;
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
			IrRetaFinalCor ( pTabuleiro , cor ) ;

			LISCIR_ObterValor ( lista_circular , ( ppVoid ) &casa ) ;
			lista_simples = casa->retaFinal ;
			IrInicioLista ( lista_simples ) ;
    
			do{

				aux = (tagCasaTabuleiro*) LIS_ObterValor ( lista_simples ) ;
				IrInicioLista(aux->conteudo);

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

			IrInicioLista(aux->conteudo);

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

		if (pTabuleiro == NULL)
		{
			return TAB_CondRetTabuleiroNaoExiste;
		}
    
		lista_circular = pTabuleiro->casas ;
		LISCIR_ObterValor ( lista_circular , ( ppVoid ) &casa );

		if ( pTabuleiro->estaNaRetaFinal  ) 
		{
			lista_simples = casa->retaFinal ;
			casa = (tagCasaTabuleiro*) LIS_ObterValor ( lista_simples ) ;
		}/* se estiver na reta final */

		*pListaPeca = casa->conteudo ;

		return TAB_CondRetOK ; 

	}   /* Fim função: TAB Obter as peças que estão na casa */

/*************************************************************************** 
*
*  Função: TAB Avança Casa
*  ****/

	TAB_CondRet TAB_AvancarCasa ( TAB_tpTabuleiro *pTabuleiro , int cor , int n )
	{
		tagCasaTabuleiro *casa ;
		LISCIR_tppListaCircular lista_circular ;
		LIS_tppLista lista_simples ;
		LIS_tpCondRet retorno_lis ;

		if (pTabuleiro == NULL)
		{
			return TAB_CondRetTabuleiroNaoExiste;
		}

		if ( cor < 0 || cor > 3 )
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

		while ( casa->cor != cor && n != 0) 
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

		PEC_AtualizarFinalPeca ( pPeca , 0) ;

		PEC_AtualizarInicioPeca ( pPeca, 1) ;

		PEC_AtualizarVoltaPeca ( pPeca, 0) ;

		return TAB_CondRetOK ;

	}   /* Fim função: TAB Retira uma peça da casa */

/*************************************************************************** 
*
*  Função: TAB Insere uma peça na casa
*  ****/

	TAB_CondRet TAB_InserirPecaCasa ( TAB_tpTabuleiro *pTabuleiro , PEC_tppPeca pPeca ) 
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
		}/* se o corrente estiver na reta final */

		PEC_AtualizarInicioPeca ( pPeca, 0 ) ;

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

		if ( cor < 0 || cor > 3 )
		{
			return TAB_CondRetCorInvalida ;
		}

		lista_circular = pTabuleiro->casas ;

		IrRetaFinalCor ( pTabuleiro , cor ) ;
    
		LISCIR_AvancarElementoCorrente ( lista_circular , 2 ) ;

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
 
 
/****************  Código das funções encapsuladas no módulo  **********************/
 
/*************************************************************************** 
*
*  Função: TAB Criar Casa
*  ****/

	static tagCasaTabuleiro * CriaCasa ( LIS_tppLista retaFinal , int cor )
	{
		tagCasaTabuleiro *nv ;

		LIS_tppLista pListaConteudo;
     
		nv  = (tagCasaTabuleiro *) malloc ( sizeof ( tagCasaTabuleiro ) ) ;
     
		if( nv == NULL )
		{
			return NULL ;
		}

		pListaConteudo = LIS_CriarLista( ( pFunc ) PEC_DestruirPeca) ;
 
		nv->cor = cor ;
 
		nv->retaFinal = retaFinal ;
 
		nv->conteudo = pListaConteudo ;
 
		return nv ;

	}  /* Fim função: TAB Criar Casa */


/*************************************************************************** 
*
*  Função: TAB Ir Reta Final Cor
*  ****/

	static void IrRetaFinalCor ( TAB_tpTabuleiro *pTabuleiro , int cor )
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