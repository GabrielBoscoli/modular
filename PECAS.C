/***************************************************************************
*  $MCI Módulo de implementação: PEC Módulo Peças
*
*  Arquivo gerado:              PECAS.C
*  Letras identificadoras:      PEC
*
*  Projeto: INF 1301 / Jogo de Ludo (ou Furbica)
*  Gestor:  Professor Alessandro Garcia
*  Autores: lr - Lucas Rodrigues
*
*  $HA Histórico de evolução:
*     Versão |  Autor   |      Data     |    Observações
*       2    |   lr     |  28/set/2016  | término desenvolvimento
*       1    |   lr     |  28/set/2016  | início desenvolvimento	
*
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "PECAS.H"
#define PECAS_OWN
#undef PECAS_OWN

/***********************************************************************
*
*  $TC Tipo de dados: LST Descritor da lista
*
*
***********************************************************************/

typedef struct Peca {

	int cor ;
	    /* Cor definida entre 0 e 3 */

	int final;
	    /* Se a peça está na casa final do jogo (1) ou não (0) */

	int inicio;
        /* Se a peça está nas casas iniciais (1) ou não (0) */

	int voltaCompleta;
		/* Se a peça já completou uma volta (1) ou não (0) */

} PEC_Peca;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: PEC  &Criar Peca
*  ****/

PEC_CondRet PEC_CriaPeca ( PEC_Peca ** pPeca, int cor ) 
{
	if ( cor < 0 || cor > 3 )
	{
		return PEC_CondRetCorInvalida ;
	}

	*pPeca = ( PEC_Peca * ) malloc ( sizeof ( PEC_Peca ) ) ;

	if ( *pPeca == NULL ) 
	{
		return PEC_CondRetFaltaMemoria ;
	}

	(*pPeca)->cor    = cor ;
	(*pPeca)->final  = 0   ;
	(*pPeca)->inicio = 0 ;
	(*pPeca)->voltaCompleta = 0 ;

	return PEC_CondRetOK ;

} /* Fim função: PEC  &Criar Peca */

/***************************************************************************
*
*  Função: PEC  &Destroi Peca
*  ****/

PEC_CondRet PEC_DestroiPeca ( PEC_Peca * pPeca )
{
	if ( pPeca == NULL )
		return PEC_CondRetNaoExiste ;
	
	free( pPeca );

	return PEC_CondRetOK ;

} /* Fim função: PEC  &Destroi Peca */


/***************************************************************************
*
*  Função: PEC  &Obtem cor
*  ****/

PEC_CondRet PEC_ObtemCor ( PEC_Peca * pPeca , int * cor )
{
	if(pPeca==NULL)
	{
		return PEC_CondRetNaoExiste;
	}

	* cor    = pPeca->cor    ;

	return PEC_CondRetOK ;

} /* Fim função: PEC  &Obtem cor */


/***************************************************************************
*
*  Função: PEC  &Obtem final
*  ****/

PEC_CondRet PEC_ObtemFinal ( PEC_Peca * pPeca , int * final )
{
	if(pPeca==NULL)
	{
		return PEC_CondRetNaoExiste;
	}

	* final  = pPeca->final  ;

	return PEC_CondRetOK ;

} /* Fim função: PEC  &Obtem final */


/***************************************************************************
*
*  Função: PEC  &Obtem inicio
*  ****/

PEC_CondRet PEC_ObtemInicio ( PEC_Peca * pPeca , int * inicio)
{
	if(pPeca==NULL)
	{
		return PEC_CondRetNaoExiste;
	}

	* inicio = pPeca->inicio ;

	return PEC_CondRetOK ;

} /* Fim função: PEC  &Obtem status */

/***************************************************************************
*
*  Função: PEC  &Obtem volta completa
*  ****/

PEC_CondRet PEC_ObtemVoltaCompleta ( PEC_Peca * pPeca , int * voltaCompleta)
{
	if(pPeca==NULL)
	{
		return PEC_CondRetNaoExiste;
	}

	* voltaCompleta = pPeca->voltaCompleta ;

	return PEC_CondRetOK ;

} /* Fim função: PEC  &Obtem volta completa */


/***************************************************************************
*
*  Função: PEC  &Atualiza se a Peca esta na casa final
*  ****/

PEC_CondRet PEC_AtualizaFinalPeca ( PEC_Peca * pPeca , int final) 
{

	if(pPeca==NULL)
	{
		return PEC_CondRetNaoExiste;
	}

	if ( final < 0 || final > 1 )
	{
		return PEC_CondRetArgumentoInvalido ;
	}

	pPeca->final = final;

	return PEC_CondRetOK ;

} /* Fim função: PEC  &Atualiza Peca */

/***************************************************************************
*
*  Função: PEC  &Atualiza volta completa da Peca
*  ****/

PEC_CondRet PEC_AtualizaVoltaPeca ( PEC_Peca * pPeca , int voltaCompleta) 
{

	if(pPeca==NULL)
	{
		return PEC_CondRetNaoExiste;
	}

	if ( voltaCompleta < 0 || voltaCompleta > 1 )
	{
		return PEC_CondRetArgumentoInvalido ;
	}

	pPeca->voltaCompleta = voltaCompleta;

	return PEC_CondRetOK ;

} /* Fim função: PEC  &Atualiza volta completa da Peca */

/***************************************************************************
*
*  Função: PEC  &Atualiza se a Peca esta na casa inicial
*  ****/

PEC_CondRet PEC_AtualizaInicioPeca ( PEC_Peca * pPeca , int inicio) 
{

	if(pPeca==NULL)
	{
		return PEC_CondRetNaoExiste;
	}

	if ( inicio < 0 || inicio > 1 )
	{
		return PEC_CondRetArgumentoInvalido ;
	}

	pPeca->inicio = inicio;

	return PEC_CondRetOK ;

} /* Fim função: PEC  &Atualiza se a Peca esta na casa inicial */

/********** Fim do módulo de implementação: PEC Módulo PECAS **********/
