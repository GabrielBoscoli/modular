/***************************************************************************
*  $MCI Modulo de implementação: TESTTAB Teste tabuleiro
*
*  Arquivo gerado:              TESTTABULEIRO.C
*  Letras identificadoras:      TESTTAB
*
*  Projeto: Disciplina INF1301
*  Gestor:  DI/PUC-RIO, Professor Alessandro Garcia
*  Autores: gb - Gabriel Boscoli 
*
*  $HA Histórico de evolução:
*     Versão   Autor         Data         Observações
*      2.00      gb      30/04/2019   finalização desenvolvimento
*      1.00      gb      29/04/2019   início desenvolvimento
*
*  $ED Descrição do módulo
*     Este modulo contém as funções específicas para o teste do
*     módulo tabuleiro. Ilustra como redigir um interpretador de comandos
*     de teste específicos utilizando o arcabouço de teste para C.
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include	"TABULEIRO.H"

#include    "PECA.H"
#include	"TST_ESPC.H"
#include	"GENERICO.H"
#include	"LERPARM.H"

#define DIM_PECAS 6

PEC_tppPeca vtPecas[DIM_PECAS];

typedef void * pVoid ;

/* Tabela dos nomes dos comandos de teste específicos */

#define INICIALIZAR_CONTEXTO_CMD	"=inicializarcontexto"
#define CRIAR_TAB_CMD				"=criartab"        
#define PROCURAR_PECA_CMD			"=procurarpeca"     
#define OBTER_CONTEUDO_CASA_CMD		"=obterconteudocasa"   
#define AVANCAR_CASA_CMD            "=avancarcasa"      
#define RETIRAR_PECA_CASA_CMD       "=retirapecacasa"  
#define INSERIR_PECA_CASA_CMD       "=inserirpecacasa"  
#define IR_CASA_SAIDA_COR_CMD       "=ircasasaidacor"         
#define DESTRUIR_TAB_CMD            "=destruirtab"     
#define VERIFICA_CASA_FINAL_CMD     "=verificacasafinal"

/*****  Código das funções exportadas pelo módulo  *****/

/***********************************************************************
*
*  $FC Função: TESTTAB &Testar tabuleiro
*
*  $ED Descrição da função
*     Efetua os diversos comandos de teste específicos para o módulo
*     tabuleiro sendo testado.
*
*  $EP Parâmetros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     Ver TST_tpCondRet definido em TST_ESPC.H
*
*     Comandos disponíveis:
*
*     =criartab                        CondRetEsp
*     =procurarpeca                    IndPeca Avanco CondRetEsp
*     =obterconteudocasa               IndPeca CondRetEsp
*	  =avancarcasa   				   CondRetEsp
*	  =retirapecacasa				   IndPeca CondRetEsp
*	  =inserirpecacasa   			   CondRetEsp
*	  =ircasasaidacor   			   CondRetEsp
*	  =destruirtab   				   CondRetEsp
*     =verificacasafinal               IndPeca CondRetEsp
*	  =inicializarcontexto
*
***********************************************************************/


	TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
	{
		int avanco        =-1 ;
		int CondRetEsp    =-1 ;
		int CondRetObtido =-1 ;
		int numLidos      =-1 ;
		int indPeca       =-1 ;
		int cor           =-1 ;
		int casaFinal         ;

		static TAB_tppTabuleiro pTabuleiro = NULL;
	
		static PEC_tppPeca pPeca1 = NULL;
		static PEC_tppPeca pPeca2 = NULL;
		static PEC_tppPeca pPeca3 = NULL;
		static PEC_tppPeca pPeca4 = NULL;
		static PEC_tppPeca pPecaNULL = NULL;
		static PEC_tppPeca pPecaPerdida = NULL;

		LIS_tppLista listaPecas = NULL;

		/* Tratar: inicializar contexto */

		if( strcmp( ComandoTeste , INICIALIZAR_CONTEXTO_CMD ) == 0 )
		{
			PEC_CriarPeca(&pPeca1, PEC_Vermelho);
			PEC_CriarPeca(&pPeca2, PEC_Azul);
			PEC_CriarPeca(&pPeca3, PEC_Amarelo);
			PEC_CriarPeca(&pPeca4, PEC_Verde);
			PEC_CriarPeca(&pPecaPerdida, PEC_Vermelho);

			PEC_AtualizarInicioPeca(pPecaPerdida, 0);

			vtPecas[0] = pPecaNULL;
			vtPecas[1] = pPeca1;
			vtPecas[2] = pPeca2;
			vtPecas[3] = pPeca3;
			vtPecas[4] = pPeca4;
			vtPecas[5] = pPecaPerdida;

			return TST_CondRetOK;

		} /* fim ativa: Tratar: inicializar contexto */

		/* Testar Criar Tabuleiro */

		if( strcmp( ComandoTeste , CRIAR_TAB_CMD ) == 0 )
		{
			numLidos = LER_LerParametros( "i", &CondRetEsp) ;
			if( numLidos != 1 )
			{
				return TST_CondRetParm;
			}

			CondRetObtido = TAB_CriarTabuleiro ( &pTabuleiro ) ;

			return TST_CompararInt ( CondRetEsp, CondRetObtido, "Retorno errado ao criar tabuleiro") ;


		} /* fim ativa: Criar Tabuleiro */


		/* Testar Procurar Peça */

		else if( strcmp( ComandoTeste , PROCURAR_PECA_CMD ) == 0 )
		{
			numLidos = LER_LerParametros( "ii", &indPeca, &CondRetEsp ) ;
			if( numLidos != 2 )
			{
				return TST_CondRetParm;
			}

			CondRetObtido = TAB_ProcurarPeca ( pTabuleiro, vtPecas [indPeca] ) ;

			return TST_CompararInt ( CondRetEsp, CondRetObtido, "Retorno errado ao procurar peça") ;


		} /* fim ativa: Procurar Peça */


		/* Testar Obter peça casa */

		else if( strcmp( ComandoTeste , OBTER_CONTEUDO_CASA_CMD ) == 0 )
		{
			numLidos = LER_LerParametros( "i", &CondRetEsp ) ;
			if( numLidos != 1 )
			{
				return TST_CondRetParm;
			}

			CondRetObtido = TAB_ObterConteudoCasa ( pTabuleiro, &listaPecas ) ;

			return TST_CompararInt ( CondRetEsp, CondRetObtido, "Retorno errado ao Obter peça casa") ;


		} /* fim ativa: Obter peça casa */

		/* Testar Eh Casa Final */

		else if( strcmp( ComandoTeste , VERIFICA_CASA_FINAL_CMD ) == 0 )
		{
			numLidos = LER_LerParametros( "i", &CondRetEsp ) ;
			if( numLidos != 1 )
			{
				return TST_CondRetParm;
			}

			CondRetObtido = TAB_VerificaCasaFinal ( pTabuleiro, &casaFinal ) ;

			return TST_CompararInt ( CondRetEsp, CondRetObtido, "Retorno errado ao verificar Eh Casa Final") ;


		} /* fim ativa: Eh Casa Final */

		/* Testar Avança casa */

		else if( strcmp( ComandoTeste , AVANCAR_CASA_CMD ) == 0 )
		{
			numLidos = LER_LerParametros( "iii", &cor, &avanco, &CondRetEsp ) ;
			if( numLidos != 3 )
			{
				return TST_CondRetParm;
			}

			CondRetObtido = TAB_AvancarCasa ( pTabuleiro, cor, avanco ) ;

			return TST_CompararInt ( CondRetEsp, CondRetObtido, "Retorno errado ao Avançar casa") ;


		} /* fim ativa: Avança casa */


		/* Testar Retira peça casa */

		else if( strcmp( ComandoTeste , RETIRAR_PECA_CASA_CMD ) == 0 )
		{
			numLidos = LER_LerParametros( "ii", &indPeca, &CondRetEsp ) ;
			if( numLidos != 2 )
			{
				return TST_CondRetParm;
			}

			CondRetObtido = TAB_RetirarPecaCasa ( pTabuleiro, vtPecas [indPeca] ) ;

			return TST_CompararInt ( CondRetEsp, CondRetObtido, "Retorno errado ao Retirar peça casa") ;


		} /* fim ativa: Retirar peça casa */


		/* Testar Insere peça casa */

		else if( strcmp( ComandoTeste , INSERIR_PECA_CASA_CMD ) == 0 )
		{
			numLidos = LER_LerParametros( "ii", &indPeca, &CondRetEsp ) ;
			if( numLidos != 2 )
			{
				return TST_CondRetParm;
			}

			CondRetObtido = TAB_InserirPecaCasa ( pTabuleiro, vtPecas [indPeca] ) ;

			return TST_CompararInt ( CondRetEsp, CondRetObtido, "Retorno errado ao Inserir peça casa") ;


		} /* fim ativa: Insere peça casa */


		/* Testar Ir Casa Saida Cor */

		else if( strcmp( ComandoTeste , IR_CASA_SAIDA_COR_CMD ) == 0 )
		{
			numLidos = LER_LerParametros( "ii", &cor, &CondRetEsp ) ;
			if( numLidos != 2 )
			{
				return TST_CondRetParm;
			}

			CondRetObtido = TAB_IrCasaSaidaCor ( pTabuleiro, cor ) ;

			return TST_CompararInt ( CondRetEsp, CondRetObtido, "Retorno errado ao Inserir peça casa") ;


		} /* fim ativa: Ir Casa Saida Cor */

		/* Testar Destruir tabuleiro */

		else if( strcmp( ComandoTeste , DESTRUIR_TAB_CMD ) == 0 )
		{
			numLidos = LER_LerParametros( "i", &CondRetEsp ) ;
			if( numLidos != 1 )
			{
				return TST_CondRetParm;
			}

			CondRetObtido = TAB_DestruirTabuleiro ( pTabuleiro ) ;

			return TST_CompararInt ( CondRetEsp, CondRetObtido, "Retorno errado ao Destruir tabuleiro") ;


		} /* fim ativa: Destruir tabuleiro */

		return TST_CondRetNaoConhec ;

	}  /* Fim função: TESTTAB &Testar tabuleiro */

/********** Fim do módulo de implementação: TESTTAB Teste tabuleiro **********/