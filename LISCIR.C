/***************************************************************************
 *  $MCI Módulo de implementação: LISCIR Lista Duplamente Encadeada Circular
 *
 *  Arquivo gerado:              LISCIR.C
 *  Letras identificadoras:      LISCIR
 *
 *  Projeto: Disciplina INF 1301
 *  Gestor:  DI/PUC-RIO, Professor Alessandro Garcia
 *  Autores: gb - Gabriel Boscoli
 *
 *  $HA Histórico de evolução:
 *    Versão   Autor        Data         Observações
 *     2.00     gb       20/04/2019    término, revisão e aperfeiçoamento
 *	   1.00     gb       19/04/2019    inicio desenvolvimento, implementação
 *									   funções básicas
 *
 *  $ED Descrição do módulo
 *     Este módulo contém a implementação das funções definidas em LISCIR.H.
 *
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define LISCIR_OWN
#include "LISCIR.H"
#undef LISCIR_OWN


/***********************************************************************
 *
 *  $TC Tipo de dados: LISCIR Elemento da lista
 *
 *  $ED Descrição do tipo
 *     Descreve a organização e estrutura de um elemento da lista.
 *
 ***********************************************************************/

	typedef struct tagElemLista {
    
		void * valor ;
		/* Ponteiro para o valor contido no elemento */
    
		struct tagElemLista * ant ;
		/* Ponteiro para o elemento predecessor */
    
		struct tagElemLista * prox ;
		/* Ponteiro para o elemento sucessor */
    
	} tpElemLista ;

/***********************************************************************
 *
 *  $TC Tipo de dados: LISCIR Descritor da cabeça da lista
 *
 *  $ED Descrição do tipo
 *     Descreve a organização e estrutura da lista.
 *	   A cabeça da lista é o ponto de acesso para determinada lista.
 *
 ***********************************************************************/

	typedef struct LISCIR_tagListaCircular {
    
		tpElemLista * pElemCorr ;
		  /* Ponteiro para o elemento corrente */
    
		int numElem ;
 		  /* Numero de elementos da lista */
    
		void ( * ExcluirValor ) ( void * pValor ) ;
		  /* Ponteiro para a função de destruição do valor contido em um elemento */

	} LISCIR_tpListaCircular ;

/***** Protótipo das funções encapsuladas no módulo *****/

	static void LiberarElemento ( LISCIR_tpListaCircular *pLista , tpElemLista  * pElem ) ;

	static tpElemLista * CriaElemento ( LISCIR_tpListaCircular * pLista , void * valor ) ;

	static void LimparCabeca ( LISCIR_tpListaCircular *pLista ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
 *
 *  Função: LISCIR  &Criar lista
 *  ****/

	LISCIR_CondRet LISCIR_CriarLista ( LISCIR_tpListaCircular **pLista, void ( * ExcluirValor ) ( void *pValor ) )
	{

		*pLista = ( LISCIR_tpListaCircular *) malloc ( sizeof ( LISCIR_tpListaCircular ) ) ;
    
		if ( *pLista == NULL )
		{
			return LISCIR_CondRetMemoriaCheia ;
		}
    
		LimparCabeca ( *pLista ) ;
		(*pLista)->ExcluirValor = ExcluirValor ;

		return 	LISCIR_CondRetOK ;
    
	} /* Fim função: LISCIR  &Criar lista */

/***************************************************************************
 *
 *  Função: LISCIR  &Remove Elemento
 *  ****/

	LISCIR_CondRet LISCIR_ExcluirElemento ( LISCIR_tpListaCircular *pLista, void * pElemento )
	{
		tpElemLista * pElem    ;
		LISCIR_CondRet retorno ;

		if(pLista == NULL)
		{
			return LISCIR_CondRetListaNaoExiste;
		}

		if ( ( retorno = LISCIR_ProcurarValor ( pLista , pElemento ) ) != LISCIR_CondRetOK )
		{
			return retorno ;
		}

		pElem = pLista->pElemCorr ;
    
		if ( pElem->ant != pElem )
		{
			pElem->ant->prox = pElem->prox ;
			pElem->prox->ant = pElem->ant  ;
			pLista->pElemCorr   = pElem->ant  ;
		}
		else
		{
			pLista->pElemCorr = NULL ;
		}

		LiberarElemento( pLista , pElem ) ;

		return LISCIR_CondRetOK ;
    
	} /* Fim função: LISCIR  &Remove Elemento */

/***************************************************************************
 *
 *  Função: LISCIR  &Destruir lista
 *  ****/

	LISCIR_CondRet LISCIR_DestruirLista ( LISCIR_tpListaCircular *pLista )
	{
		if(pLista == NULL)
		{
			return LISCIR_CondRetListaNaoExiste;
		}

		LISCIR_EsvaziarLista( pLista ) ;

		return LISCIR_CondRetOK;
    
	} /* Fim função: LISCIR  &Destruir lista */

/***************************************************************************
 *
 *  Função: LISCIR  &Esvaziar lista
 *  ****/

	LISCIR_CondRet LISCIR_EsvaziarLista( LISCIR_tpListaCircular *pLista )
	{
    
		tpElemLista * pElem ;
		tpElemLista * pProx ;

		if(pLista == NULL)
		{
			return LISCIR_CondRetListaNaoExiste;
		}

		if( pLista->pElemCorr == NULL )
		{
			return LISCIR_CondRetListaVazia ;
		}
    
		pElem = pLista->pElemCorr ;
    
		do
		{
			pProx = pElem->prox ;
			LiberarElemento( pLista , pElem ) ;
			pElem = pProx ;
        
		} while ( pElem != pLista->pElemCorr ) ;
    
		LimparCabeca( pLista ) ;

		return LISCIR_CondRetOK;
    
	} /* Fim função: LISCIR  &Esvaziar lista */

/***************************************************************************
 *
 *  Função: LISCIR  &Procurar elemento na lista
 *  ****/

	LISCIR_CondRet LISCIR_ProcurarValor ( LISCIR_tpListaCircular *pLista , void * pValor )
	{
		tpElemLista * pElem ;

		if(pLista == NULL)
		{
			return LISCIR_CondRetListaNaoExiste;
		}
    
		if ( pLista->pElemCorr == NULL )
		{
			return LISCIR_CondRetListaVazia;
		}
    
		pElem = pLista->pElemCorr ;
    
		do
		{
			if ( pElem->valor == pValor )
			{
				pLista->pElemCorr = pElem ;
				return LISCIR_CondRetOK ;
			}
			pElem = pElem->prox ;
        
		} while ( pElem != pLista->pElemCorr ) ;

		return LISCIR_CondRetNaoAchou;
    
	} /* Fim função: LISCIR  &Procurar elemento na lista */

/***************************************************************************
 *
 *  Função: LISCIR  &Inserir elemento à esquerda
 *  ****/

	LISCIR_CondRet LISCIR_InserirElementoAntes ( LISCIR_tpListaCircular * pLista, void * pValor )
	{
		tpElemLista *pElem ;
		tpElemLista *p     ;

		if(pLista == NULL)
		{
			return LISCIR_CondRetListaNaoExiste;
		}

		pElem = CriaElemento( pLista ,  pValor ) ;
    
		if ( pElem == NULL )
		{
			return LISCIR_CondRetMemoriaCheia ;
		}

		p = pLista->pElemCorr ;

		if ( p == NULL )
		{
			pElem->ant = pElem->prox = pElem ;
		}
    
		else
		{
			p->ant->prox = pElem  ;
			pElem->ant   = p->ant ;
			pElem->prox  = p      ;
			p->ant       = pElem  ;
		}

		pLista->pElemCorr = pElem ;
		pLista->numElem++ ;


		return LISCIR_CondRetOK ;
    
	} /* Fim função: LISCIR  &Inserir elemento à esquerda */

/***************************************************************************
 *
 *  Função: LISCIR  &Inserir elemento à direita
 *  ****/

	LISCIR_CondRet LISCIR_InserirElementoApos ( LISCIR_tpListaCircular *pLista , void * pValor )
	{
		tpElemLista *pElem ;
		tpElemLista * p ;

		if(pLista == NULL)
		{
			return LISCIR_CondRetListaNaoExiste;
		}

		pElem = CriaElemento ( pLista , pValor ) ;

		if ( pElem == NULL )
		{
			return LISCIR_CondRetMemoriaCheia ;
		}
    
		p = pLista->pElemCorr ;

		if ( p == NULL )
		{
			pElem->ant = pElem->prox = pElem ;
		}
    
		else
		{
			p->prox->ant = pElem   ;
			pElem->ant   = p       ;
			pElem->prox  = p->prox ;
			p->prox      = pElem   ;
		}
		pLista->pElemCorr = pElem ;
		pLista->numElem++ ;

		return LISCIR_CondRetOK ;
    
	} /* Fim função: LISCIR  &Inserir elemento à direita */

/***************************************************************************
 *
 *  Função: LISCIR  &Obter valor
 *  ****/

	LISCIR_CondRet LISCIR_ObterValor ( LISCIR_tpListaCircular *pLista , void ** ppValor )
	{
		if(pLista == NULL)
		{
			return LISCIR_CondRetListaNaoExiste;
		}

		if( pLista->pElemCorr == NULL )
		{
			return LISCIR_CondRetListaVazia ;
		}

		*ppValor = pLista->pElemCorr->valor ;

		return LISCIR_CondRetOK ;
    
	}/* Fim função: LISCIR  &Obter valor */

/***************************************************************************
 *
 *  Função: LISCIR  &Avançar Elemento Corrente
 *  ****/

	LISCIR_CondRet LISCIR_AvancarElementoCorrente ( LISCIR_tpListaCircular *pLista , int num )
	{
		tpElemLista *pElem ;

		if(pLista == NULL)
		{
			return LISCIR_CondRetListaNaoExiste;
		}
    
		if( pLista->pElemCorr == NULL )
		{
			return LISCIR_CondRetListaVazia ;
		}

		pElem = pLista->pElemCorr ;

		if ( num > 0 )
		{
			while( num )
			{
				pElem = pElem->prox ;
				num-- ;
			}
		}
		else if ( num < 0 )
		{
			while( num )
			{
				pElem = pElem->ant ;
				num++ ;
			}
		}

		pLista->pElemCorr = pElem ;

		return LISCIR_CondRetOK ;
    
	}/* Fim função: LISCIR  &Avançar Elemento Corrente */

/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
 *
 *  $FC Função: LISCIR  -Liberar elemento da lista
 *
 *  $ED Descrição da função
 *     Elimina os espaços apontados pelo valor do elemento e o
 *     próprio elemento.
 *
 ***********************************************************************/

	void LiberarElemento ( LISCIR_tpListaCircular *pLista , tpElemLista  * pElem )
	{
		if ( ( pLista->ExcluirValor != NULL ) && ( pElem->valor != NULL )    )
		{
			pLista->ExcluirValor( pElem->valor ) ;

		} /* if */

		pElem->valor = NULL ;
		pLista->numElem-- ;

		free(pElem);
    
	} /* Fim função: LISCIR  -Liberar elemento da lista */

/***********************************************************************
 *
 *  $FC Função: LISCIR  -Cria elemento da lista
 *
 ***********************************************************************/

	tpElemLista * CriaElemento ( LISCIR_tpListaCircular * pLista , void * valor )
	{
		tpElemLista * pElem ;
    
		pElem = ( tpElemLista * ) malloc ( sizeof ( tpElemLista ) ) ;
		if ( pElem == NULL )
		{
			return NULL ;
		}
    
		pLista = NULL ;

		pElem->valor = valor ;
		pElem->prox  = NULL  ;
		pElem->ant   = NULL  ;
    
		return pElem ;
    
	} /* Fim função: LISCIR  -Cria elemento da lista */

/***********************************************************************
 *
 *  $FC Função: LISCIR  -Limpar a cabeça da lista
 *
 ***********************************************************************/

	void LimparCabeca ( LISCIR_tpListaCircular *pLista )
	{
		pLista->pElemCorr = NULL ;
		pLista->numElem  = 0    ;
    
	} /* Fim função: LISCIR  -Limpar a cabeça da lista */

/********** Fim do módulo de implementação: LISCIR  Lista Duplamente Encadeada Circular **********/