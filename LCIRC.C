/***************************************************************************
 *  $MCI Módulo de implementação: LST  Lista duplamente encadeada circular
 *
 *  Arquivo gerado:              LCIRC.c
 *  Letras identificadoras:      LST
 *
 *  Projeto: INF 1301 / Jogo de Ludo (ou Furbica)
 *  Gestor:  Professor Alessandro Garcia
 *  Autores: lr, dcr, rvc
 *
 *  $HA Histórico de evolução:
 *    Versão |  Autor  |      Data     |    Observações
 *      5    |   rvc   |  14/out/2016  |  finalização desenvolvimento
 *		4    |   rvc   |  14/out/2016  |  ajustes de desenvolvimento
 *      3    |   lr    |  25/set/2016  |  formalização do módulo
 *		2    |   rvc   |  24/set/2016  |  ajustes de desenvolvimento
 *	    1    |   dcr   |  17/set/2016  |  início desenvolvimento
 *
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define LCIRC_OWN
#include "LCIRC.h"
#undef LCIRC_OWN


/***********************************************************************
 *
 *  $TC Tipo de dados: LST Elemento da lista
 *
 *
 ***********************************************************************/

typedef struct tagElemLista {
    
    void * valor ;
    /* Ponteiro para o valor contido no elemento */
    
    struct tagElemLista * ant ;
    /* Ponteiro para o elemento predecessor */
    
    struct tagElemLista * prox ;
    /* Ponteiro para o elemento sucessor */
    
} LST_Elem ;

/***********************************************************************
 *
 *  $TC Tipo de dados: LST Descritor da lista
 *
 *
 ***********************************************************************/

typedef struct LST_tpCircular {
    
    LST_Elem * pElemCorr ;
      /* Ponteiro para o elemento corrente */
    
    int numElem ;
 	  /* Numero de elementos da lista */
    
    void ( * ExcluirValor ) ( void * pValor ) ;
      /* Ponteiro para a função de destruição do valor contido em um elemento */

} LST_tppCircular ;


/*****  Dados encapsulados no módulo  *****/


/***** Protótipo das funções encapsuladas no módulo *****/

static void LiberarElemento ( LST_tppCircular *pLista , LST_Elem  * pElem ) ;

static LST_Elem * CriaElemento ( LST_tppCircular * pLista , void * valor ) ;

static void LimparCabeca ( LST_tppCircular *pLista ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
 *
 *  Função: LST  &Criar lista
 *  ****/

LST_CondRet LST_CriaLista ( LST_tppCircular **pLista, void ( * ExcluirValor ) ( void *pValor ) )
{

    *pLista = ( LST_tppCircular *) malloc ( sizeof ( LST_tppCircular ) ) ;
    
    if ( *pLista == NULL )
    {
        return LST_CondRetMemoriaCheia ;
    }
    
    LimparCabeca ( *pLista ) ;
    (*pLista)->ExcluirValor = ExcluirValor ;

    return 	LST_CondRetOK ;
    
} /* Fim função: LST  &Criar lista */

/***************************************************************************
 *
 *  Função: LST  &Remove Elemento
 *  ****/

LST_CondRet LST_RemoveElemento ( LST_tppCircular *pLista, void * elemento )
{
    LST_Elem * pElem    ;
    LST_CondRet retorno ;

    if ( ( retorno = LST_BuscaElemento ( pLista , elemento ) ) != LST_CondRetOK )
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
    return LST_CondRetOK ;
    
} /* Fim função: LST  &Remove Elemento */

/***************************************************************************
 *
 *  Função: LST  &Destruir lista
 *  ****/

LST_CondRet LST_DestruirLista ( LST_tppCircular *pLista )
{

    LST_EsvaziarLista( pLista ) ;

    return LST_CondRetOK;
    
} /* Fim função: LST  &Destruir lista */

/***************************************************************************
 *
 *  Função: LST  &Esvaziar lista
 *  ****/

LST_CondRet LST_EsvaziarLista( LST_tppCircular *pLista )
{
    
    LST_Elem * pElem ;
    LST_Elem * pProx ;

    if( pLista->pElemCorr == NULL )
    {
        return LST_CondRetVazia ;
    }
    
    pElem = pLista->pElemCorr ;
    
    do
    {
        pProx = pElem->prox ;
        LiberarElemento( pLista , pElem ) ;
        pElem = pProx ;
        
    } while ( pElem != pLista->pElemCorr ) ;
    
    LimparCabeca( pLista ) ;

    return LST_CondRetOK;
    
} /* Fim função: LST  &Esvaziar lista */

/***************************************************************************
 *
 *  Função: LST  &Procurar elemento na lista
 *  ****/

LST_CondRet LST_BuscaElemento ( LST_tppCircular *pLista , void * valor )
{
    LST_Elem * pElem ;
    
    if ( pLista->pElemCorr == NULL )
    {
        return LST_CondRetVazia;
    }
    
    pElem = pLista->pElemCorr ;
    
    do
    {
        if ( pElem->valor == valor )
        {
            pLista->pElemCorr = pElem ;
            return LST_CondRetOK ;
        }
        pElem = pElem->prox ;
        
    } while ( pElem != pLista->pElemCorr ) ;

    return LST_CondRetNaoEncontrou;
    
} /* Fim função: LST  &Procurar elemento na lista */

/***************************************************************************
 *
 *  Função: LST  &Inserir elemento à esquerda
 *  ****/

LST_CondRet LST_InsereElemEsquerda ( LST_tppCircular * pLista, void * valor )
{
    LST_Elem *pElem ;
    LST_Elem *p     ;

    pElem = CriaElemento( pLista ,  valor ) ;
    
    if ( pElem == NULL )
    {
        return LST_CondRetMemoriaCheia ;
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


    return LST_CondRetOK ;
    
} /* Fim função: LST  &Inserir elemento à esquerda */

/***************************************************************************
 *
 *  Função: LST  &Inserir elemento à direita
 *  ****/

LST_CondRet LST_InsereElemDireita ( LST_tppCircular *pLista , void * valor )
{
    LST_Elem *pElem ;
    LST_Elem * p ;
    pElem = CriaElemento ( pLista , valor ) ;

    if ( pElem == NULL )
    {
        return LST_CondRetMemoriaCheia ;
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

    return LST_CondRetOK ;
    
} /* Fim função: LST  &Inserir elemento à direita */

/***************************************************************************
 *
 *  Função: LST  &Obter valor
 *  ****/

LST_CondRet LST_ObterValor ( LST_tppCircular *pLista , void ** valor )
{

    if( pLista->pElemCorr == NULL )
    {
        return LST_CondRetVazia ;
    }

    *valor = pLista->pElemCorr->valor ;

    return LST_CondRetOK ;
    
}/* Fim função: LST  &Obter valor */

/***************************************************************************
 *
 *  Função: LST  &Avançar Elemento Corrente
 *  ****/

LST_CondRet LST_AvancarElementoCorrente ( LST_tppCircular *pLista , int num )
{
    LST_Elem *pElem ;
    
    if( pLista->pElemCorr == NULL )
    {
        return LST_CondRetVazia ;
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

    return LST_CondRetOK ;
    
}/* Fim função: LST  &Avançar Elemento Corrente */

/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
 *
 *  $FC Função: LST  -Liberar elemento da lista
 *
 *  $ED Descrição da função
 *     Elimina os espaços apontados pelo valor do elemento e o
 *     próprio elemento.
 *
 ***********************************************************************/

void LiberarElemento ( LST_tppCircular *pLista , LST_Elem  * pElem )
{
    if ( ( pLista->ExcluirValor != NULL ) && ( pElem->valor != NULL )    )
    {
        pLista->ExcluirValor( pElem->valor ) ;

    } /* if */

	pElem->valor = NULL ;
    pLista->numElem-- ;
    
} /* Fim função: LST  -Liberar elemento da lista */

/***********************************************************************
 *
 *  $FC Função: LST  -Cria elemento da lista
 *
 *  $ED Descrição da função
 *     Cria elemento da lista e inicializa os valores contidos nele.
 *
 ***********************************************************************/

LST_Elem * CriaElemento ( LST_tppCircular * pLista , void * valor )
{
    LST_Elem * pElem ;
    
    pElem = ( LST_Elem * ) malloc ( sizeof ( LST_Elem ) ) ;
    if ( pElem == NULL )
    {
        return NULL ;
    }
    
	pLista = NULL ;

    pElem->valor = valor ;
    pElem->prox  = NULL  ;
    pElem->ant   = NULL  ;
    
    return pElem ;
    
} /* Fim função: LST  &Cria elemento da lista */

/***********************************************************************
 *
 *  $FC Função: LST  -Limpar a cabeça da lista
 *
 ***********************************************************************/

void LimparCabeca ( LST_tppCircular *pLista )
{
    pLista->pElemCorr = NULL ;
    pLista->numElem  = 0    ;
    
} /* Fim função: LST  -Limpar a cabeça da lista */

/********** Fim do módulo de implementação: LST  Lista duplamente encadeada circular **********/