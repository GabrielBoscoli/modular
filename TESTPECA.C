/***************************************************************************
*  $MCI Módulo de implementação: TPEC Teste peça
*
*  Arquivo gerado:              TESTPECA.C
*  Letras identificadoras:      TPEC
*
*  Projeto: Disciplina INF 1301
*  Gestor:  DI/PUC-RIO, Professor Alessandro Garcia
*  Autores: gb - Gabriel Boscoli
*
*  $HA Histórico de evolução:
*     Versão   Autor         Data          Observações
*      2.00     gb       25/04/2019   término desenvolvimento
*      1.00     gb       23/04/2019   início desenvolvimento
*
*  $ED Descrição do módulo
*     Este modulo contém as funções específicas para o teste do
*     módulo peças. Ilustra como redigir um interpretador de comandos
*     de teste específicos utilizando o arcabouço de teste para C.
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>
#include    <stdlib.h>

#include    "PECA.h"

#include	"TST_ESPC.H"
#include    "GENERICO.H"
#include    "LERPARM.H"

/* Tabela dos nomes dos comandos de teste específicos */

#define CRIAR_PECA_CMD          "=criarpeca"     
#define DESTRUIR_PECA_CMD       "=destruirpeca"  
#define OBTER_COR_CMD           "=obtercor"      
#define OBTER_FINAL_CMD         "=obterfinal"    
#define OBTER_INICIO_CMD        "=obterinicio"
#define OBTER_VOLTA_CMD         "=obtervolta"
#define ATUALIZAR_FINAL_CMD     "=atualizafinal"
#define ATUALIZAR_INICIO_CMD    "=atualizainicio"  
#define ATUALIZAR_VOLTA_CMD     "=atualizavolta"  

/*****  Código das funções exportadas pelo módulo  *****/

/***********************************************************************
*
*  $FC Função: TPEC Testar peça
*
*  $ED Descrição da função
*     Efetua os diversos comandos de teste específicos para o módulo
*     peça sendo testado.
*
*  $EP Parâmetros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     Ver TST_tpCondRet definido em TST_ESPC.H
*
*     Comandos disponíveis:
*
*     =criarpeca				CondRetEsp
*     =destruirpeca				CondRetEsp
*     =obtercor					CondRetEsp
*     =obterfinal				CondRetEsp
*     =obterinicio              CondRetEsp
*     =obtervolta               CondRetEsp
*     =atualizafinal            Valor CondRetEsp
*     =atualizainicio           Valor CondRetEsp
*     =atualizavolta            Valor CondRetEsp
*
***********************************************************************/

TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
{
	int numLidos      = -1 ;
	int cor           = -1 ;
	int CondRetEsp    = -1 ;
	int CondRetObtido = -1 ;
	int auxiliar = -1 ;
	static PEC_tppPeca peca = NULL;

	/* Testar Criar */

	if( strcmp( ComandoTeste , CRIAR_PECA_CMD ) == 0 )
	{
		numLidos = LER_LerParametros( "ii", &cor ,&CondRetEsp);
		if( numLidos != 2 )
		{
			return TST_CondRetParm;
		}

		CondRetObtido = PEC_CriarPeca ( &peca, cor ) ;

		return TST_CompararInt ( CondRetEsp, CondRetObtido, "Retorno errado") ;


	} /* fim ativa: Testar Criar */
	
	/* Testar Destruir */
	
	else if ( strcmp( ComandoTeste , DESTRUIR_PECA_CMD ) == 0 )
	{
		numLidos = LER_LerParametros( "i", &CondRetEsp ) ;

		if ( numLidos != 1 )
		{
			return TST_CondRetParm ;
		}

		CondRetObtido = PEC_DestruirPeca ( peca ) ;
		peca = NULL ;

		return TST_CompararInt (CondRetEsp, CondRetObtido, "Retorno errado") ;

	}  /* fim ativa: Testar */

		/* Testar Obter Cor */

         else if ( strcmp( ComandoTeste , OBTER_COR_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i", &CondRetEsp ) ;

            if (  numLidos != 1 )
            {
               return TST_CondRetParm ;
            }


            CondRetObtido = PEC_ObterCor( peca, &cor ) ;
			
            return TST_CompararInt( CondRetEsp , CondRetObtido ,
                     "Condicao de retorno errada ao obter status." ) ;

         } /* fim ativa: Testar Obter Cor */

    /* Testar Obter Final */

         else if ( strcmp( ComandoTeste , OBTER_FINAL_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii", &CondRetEsp ) ;

            if (  numLidos != 1 )
            {
               return TST_CondRetParm ;
            }


            CondRetObtido = PEC_ObterFinal( peca, &auxiliar ) ;
			
            return TST_CompararInt( CondRetEsp , CondRetObtido ,
                     "Condicao de retorno errada ao obter status." ) ;

         } /* fim ativa: Testar Obter Final */

     /* Testar Obter Inicio */

         else if ( strcmp( ComandoTeste , OBTER_INICIO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i", &CondRetEsp ) ;

            if (  numLidos != 1 )
            {
               return TST_CondRetParm ;
            }


            CondRetObtido = PEC_ObterInicio( peca, &auxiliar ) ;
			
            return TST_CompararInt( CondRetEsp , CondRetObtido ,
                     "Condicao de retorno errada ao obter status." ) ;

         } /* fim ativa: Testar Obter Inicio */

		 /* Testar Obter Volta Completa */

         else if ( strcmp( ComandoTeste , OBTER_VOLTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i", &CondRetEsp ) ;

            if (  numLidos != 1 )
            {
               return TST_CondRetParm ;
            }

            CondRetObtido = PEC_ObterVoltaCompleta( peca, &auxiliar ) ;
			
            return TST_CompararInt( CondRetEsp , CondRetObtido ,
                     "Condicao de retorno errada ao obter status." ) ;

         } /* fim ativa: Testar Obter Volta Completa */

		/* Testar Atualiza Final Peca */

         else if ( strcmp( ComandoTeste , ATUALIZAR_FINAL_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii", &auxiliar, &CondRetEsp ) ;

            if (  numLidos != 2 )
            {
               return TST_CondRetParm ;
            }


            CondRetObtido = PEC_AtualizarFinalPeca( peca, auxiliar) ;
			
            return TST_CompararInt( CondRetEsp , CondRetObtido ,
                     "Condicao de retorno errada ao Atualiza Peca." ) ;

         } /* fim ativa: Testar Atualiza Final Peca */

		 /* Testar Atualiza Inicio Peca */

         else if ( strcmp( ComandoTeste , ATUALIZAR_INICIO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii", &auxiliar, &CondRetEsp ) ;

            if (  numLidos != 2 )
            {
               return TST_CondRetParm ;
            }


            CondRetObtido = PEC_AtualizarInicioPeca( peca, auxiliar) ;
			
            return TST_CompararInt( CondRetEsp , CondRetObtido ,
                     "Condicao de retorno errada ao Atualiza Peca." ) ;

         } /* fim ativa: Testar Atualiza Inicio Peca */

		 /* Testar Atualiza Volta Peca */

         else if ( strcmp( ComandoTeste , ATUALIZAR_VOLTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii", &auxiliar, &CondRetEsp ) ;

            if (  numLidos != 2 )
            {
               return TST_CondRetParm ;
            }


            CondRetObtido = PEC_AtualizarVoltaPeca( peca, auxiliar) ;
			
            return TST_CompararInt( CondRetEsp , CondRetObtido ,
                     "Condicao de retorno errada ao Atualiza Peca." ) ;

         } /* fim ativa: Testar Atualiza Volta Peca */

    return TST_CondRetNaoConhec ;
			
}  /* Fim função: TPEC &Testar peça */

/********** Fim do módulo de implementação: TPEC Teste peça **********/