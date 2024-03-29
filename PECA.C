/***************************************************************************
*  $MCI Módulo de implementação: PEC Módulo Peça
*
*  Arquivo gerado:              PECA.C
*  Letras identificadoras:      PEC
*
*  Projeto: Disciplina INF 1301
*  Gestor:  DI/PUC-RIO, Professor Alessandro Garcia
*  Autores: gb - Gabriel Boscoli
*
*  $HA Histórico de evolução:
*     Versão     Autor        Data         Observações
*	   3.00       gb       15/06/2019   ajustes e leves mudanças
*      2.00       gb       24/04/2019   término, revisão e aperfeiçoamento
*      1.00       gb       22/04/2019   início desenvolvimento, implementação
*										de funções básicas
*
* $ED Descrição do módulo
*     Este módulo contém a implementação das funções definidas em PECA.h.
*
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define	 PECA_OWN
#include "PECA.H"
#undef	 PECA_OWN

#define NUM_CORES 4

/***********************************************************************
*
*  $TC Tipo de dados: PEC Descritor da peça
*
*  $ED Descrição do tipo
*     Descreve a organização e estrutura de uma peça
*
***********************************************************************/

	typedef struct PEC_tagPeca {

		int cor ;
			/* Cor definida entre 0 e NUM_CORES - 1 */

		int final;
			/* Se a peça está na reta final do jogo (1) ou não (0) */

		int inicio;
			/* Se a peça está nas casas iniciais (1) ou não (0) */

		int volta;
			/* Se a peça esta realizando uma volta (1) ou se ainda não se moveu (0) */

	} PEC_tpPeca;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: PEC Criar Peca
*  ****/

	PEC_CondRet PEC_CriarPeca ( PEC_tpPeca ** pPeca, int cor )
	{
		if ( cor < 0 || cor > NUM_CORES - 1 )
		{
			return PEC_CondRetCorInvalida ;
		}

		*pPeca = ( PEC_tpPeca * ) malloc ( sizeof ( PEC_tpPeca ) ) ;

		if ( *pPeca == NULL ) 
		{
			return PEC_CondRetFaltaMemoria ;
		}

		(*pPeca)->cor    = cor ;
		(*pPeca)->final  = 0   ;
		(*pPeca)->inicio = 1 ;
		(*pPeca)->volta = 0 ;

		return PEC_CondRetOK ;

	} /* Fim função: PEC Criar Peca */

/***************************************************************************
*
*  Função: PEC Destroi Peca
*  ****/

	PEC_CondRet PEC_DestruirPeca ( PEC_tpPeca * pPeca )
	{
		if ( pPeca == NULL )
			return PEC_CondRetNaoExiste ;
	
		free( pPeca );

		return PEC_CondRetOK ;

	} /* Fim função: PEC Destroi Peca */


/***************************************************************************
*
*  Função: PEC Obtem cor
*  ****/

	PEC_CondRet PEC_ObterCor ( PEC_tpPeca * pPeca , int * pCor )
	{
		if(pPeca == NULL)
		{
			return PEC_CondRetNaoExiste;
		}

		* pCor    = pPeca->cor    ;

		return PEC_CondRetOK ;

	} /* Fim função: PEC  Obtem cor */


/***************************************************************************
*
*  Função: PEC Obtem final
*  ****/

	PEC_CondRet PEC_ObterFinal ( PEC_tpPeca * pPeca , int * pFinal )
	{
		if(pPeca == NULL)
		{
			return PEC_CondRetNaoExiste;
		}

		* pFinal  = pPeca->final  ;

		return PEC_CondRetOK ;

	} /* Fim função: PEC Obtem final */


/***************************************************************************
*
*  Função: PEC Obtem inicio
*  ****/

	PEC_CondRet PEC_ObterInicio ( PEC_tpPeca * pPeca , int * pInicio)
	{
		if(pPeca == NULL)
		{
			return PEC_CondRetNaoExiste;
		}

		* pInicio = pPeca->inicio ;

		return PEC_CondRetOK ;

	} /* Fim função: PEC Obtem inicio */

/***************************************************************************
*
*  Função: PEC Obtem volta
*  ****/

	PEC_CondRet PEC_ObterVolta ( PEC_tpPeca * pPeca , int * pVolta)
	{
		if(pPeca == NULL)
		{
			return PEC_CondRetNaoExiste;
		}

		* pVolta = pPeca->volta ;

		return PEC_CondRetOK ;

	} /* Fim função: PEC Obtem volta */


/***************************************************************************
*
*  Função: PEC Atualiza se a Peca esta na reta final
*  ****/

	PEC_CondRet PEC_AtualizarFinalPeca ( PEC_tpPeca * pPeca , int final) 
	{

		if(pPeca == NULL)
		{
			return PEC_CondRetNaoExiste;
		}

		if ( final < 0 || final > 1 )
		{
			return PEC_CondRetArgumentoInvalido ;
		}

		pPeca->final = final;

		return PEC_CondRetOK ;

	} /* Fim função: PEC Atualiza Final Peca */

/***************************************************************************
*
*  Função: PEC Atualiza se a Peca deu uma volta
*  ****/

	PEC_CondRet PEC_AtualizarVoltaPeca ( PEC_tpPeca * pPeca , int volta) 
	{

		if(pPeca == NULL)
		{
			return PEC_CondRetNaoExiste;
		}

		if ( volta < 0 || volta > 1 )
		{
			return PEC_CondRetArgumentoInvalido ;
		}

		pPeca->volta = volta;

		return PEC_CondRetOK ;

	} /* Fim função: PEC Atualiza se a Peca deu uma volta */

/***************************************************************************
*
*  Função: PEC Atualiza se a Peca esta na casa inicial
*  ****/

	PEC_CondRet PEC_AtualizarInicioPeca ( PEC_tpPeca * pPeca , int inicio) 
	{

		if(pPeca == NULL)
		{
			return PEC_CondRetNaoExiste;
		}

		if ( inicio < 0 || inicio > 1 )
		{
			return PEC_CondRetArgumentoInvalido ;
		}

		pPeca->inicio = inicio;

		return PEC_CondRetOK ;

	} /* Fim função: PEC Atualiza se a Peca esta na casa inicial */

/********** Fim do módulo de implementação: PEC Módulo Peça **********/
