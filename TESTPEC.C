/***************************************************************************
*  $MCI Módulo de implementação: TPEC Módulo de teste de peças
*
*  Arquivo gerado:              TESTPEC.C
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
*  $EIU Interface com o usuário pessoa
*     Comandos de teste específicos para testar o módulo peças:
*
*     =criarpeca        - chama a função PEC_CriaPeca()
*     =destruirpeca		- chama a função PEC_DestroiPeca()
*     =obtercor			- chama a função PEC_ObtemCor()
*     =obterfinal       - chama a função PEC_ObtemFinal()
*     =obterinicio		- chama a função PEC_ObtemInicio()
*     =obtervolta		- chama a função PEC_ObtemVolta()
*     =atualizafinal	- chama a função PEC_AtualizaFinalPeca()
*     =atualizainicio   - chama a função PEC_AtualizaInicioPeca()
*     =atualizavolta	- chama a função PEC_AtualizaVoltaPeca()
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>
#include    <stdlib.h>

#include    "PECAS.h"

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
*  $FC Função: TPEC Efetuar operações de teste específicas para peças
*
*  $ED Descrição da função
*     Efetua os diversos comandos de teste específicos para o módulo
*     peças sendo testado.
*
*  $EP Parâmetros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     Ver TST_tpCondRet definido em TST_ESPC.H
*
***********************************************************************/

TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
{
	int numLidos      = -1 ;
	int cor           = -1 ;
	int CondRetEsp    = -1 ;
	int CondRetObtido = -1 ;
	int auxiliar = -1 ;
	static PEC_tpPeca peca = NULL;

	/* Testar Criar */

	if( strcmp( ComandoTeste , CRIAR_PECA_CMD ) == 0 )
	{
		numLidos = LER_LerParametros( "ii", &cor ,&CondRetEsp);
		if( numLidos != 2 )
		{
			return TST_CondRetParm;
		}

		CondRetObtido = PEC_CriaPeca ( &peca, cor ) ;

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

		CondRetObtido = PEC_DestroiPeca ( peca ) ;
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


            CondRetObtido = PEC_ObtemCor( peca, &cor ) ;
			
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


            CondRetObtido = PEC_ObtemFinal( peca, &auxiliar ) ;
			
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


            CondRetObtido = PEC_ObtemInicio( peca, &auxiliar ) ;
			
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

            CondRetObtido = PEC_ObtemVoltaCompleta( peca, &auxiliar ) ;
			
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


            CondRetObtido = PEC_AtualizaFinalPeca( peca, auxiliar) ;
			
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


            CondRetObtido = PEC_AtualizaInicioPeca( peca, auxiliar) ;
			
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


            CondRetObtido = PEC_AtualizaVoltaPeca( peca, auxiliar) ;
			
            return TST_CompararInt( CondRetEsp , CondRetObtido ,
                     "Condicao de retorno errada ao Atualiza Peca." ) ;

         } /* fim ativa: Testar Atualiza Volta Peca */

    return TST_CondRetNaoConhec ;
			
}  /* Fim função: TPEC &Testar peça */

/********** Fim do módulo de implementação: TPEC Teste lista de símbolos **********/