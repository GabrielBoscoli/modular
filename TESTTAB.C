/***************************************************************************
*  $MCI Modulo de implementação: TTAB Teste tabuleiro
*
*  Arquivo gerado:              TESTTAB.C
*  Letras identificadoras:      TTAB
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

#include    "PECAS.H"
#include	"TST_ESPC.H"
#include	"GENERICO.H"
#include	"LERPARM.H"


#define INICIALIZAR_CONTEXTO_CMD	"=inicializarcontexto"
#define CRIAR_TAB_LUDO_CMD          "=criartab"        
#define PROCURA_PECA_CMD            "=procurarpeca"     
#define OBTER_PECA_CASA_CMD         "=obterpecacasa"   
#define AVANCA_CASA_CMD             "=avancarcasa"      
#define RETIRA_PECA_CASA_CMD        "=retirapecacasa"  
#define INSERE_PECA_CASA_CMD        "=inserirpecacasa"  
#define IR_CASA_SAIDA_COR_CMD       "=ircasasaidacor"         
#define DESTRUIR_TAB_CMD            "=destruirtab"     
#define EH_CASA_FINAL_CMD           "=ehcasafinal"


#define DIM_PECAS 6

PEC_tpPeca vtPecas[DIM_PECAS];

typedef void * pVoid ;

/*****  Código das funções exportadas pelo módulo  *****/

/***********************************************************************
*
*  $FC Função: TTAB &Testar tabuleiro
*
*  $ED Descrição da função
*     Testa as funçoes de manipulação de um tabuleiro
*
*     Comandos disponíveis:
*
*     =criartab                        CondRetEsp
*     =procurapeca                     IndPeca Avanco CondRetEsp
*     =obterpecacasa                   IndPeca CondRetEsp
*	  =avancacasa   				   CondRetEsp
*	  =retirapecacasa				   IndPeca CondRetEsp
*	  =inserepecacasa   			   CondRetEsp
*	  =ircasasaidacor   			   CondRetEsp
*	  =lancardado   				   CondRetEsp
*	  =destruirtab   				   CondRetEsp
*     =ehcasafinal                     IndPeca CondRetEsp
*
***********************************************************************/

/***********************************************************************/

TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
{
	int tab           =-1 ;
	int ret           =-1 ;
	int avanco        =-1 ;
	int CondRetEsp    =-1 ;
	int CondRetObtido =-1 ;
	int numLidos      =-1 ;
	int indPeca       =-1 ;
	int cor           =-1 ;
	int valor             ;
	int i                 ;
	int casaFinal         ;

	static TAB_tpLudo pTabuleiro = NULL;
	
	static PEC_tpPeca pPeca1 = NULL;
	static PEC_tpPeca pPeca2 = NULL;
	static PEC_tpPeca pPeca3 = NULL;
	static PEC_tpPeca pPeca4 = NULL;
	static PEC_tpPeca pPecaNULL = NULL;
	static PEC_tpPeca pPecaPerdida = NULL;

	LIS_tppLista listaPecas = NULL;

	/* Tratar: inicializar contexto */

	if( strcmp( ComandoTeste , INICIALIZAR_CONTEXTO_CMD ) == 0 )
	{
		PEC_CriaPeca(&pPeca1, PEC_Vermelho);
		PEC_CriaPeca(&pPeca2, PEC_Azul);
		PEC_CriaPeca(&pPeca3, PEC_Amarelo);
		PEC_CriaPeca(&pPeca4, PEC_Verde);
		PEC_CriaPeca(&pPecaPerdida, PEC_Vermelho);

		PEC_AtualizaInicioPeca(pPecaPerdida, 0);

		vtPecas[0] = pPecaNULL;
		vtPecas[1] = pPeca1;
		vtPecas[2] = pPeca2;
		vtPecas[3] = pPeca3;
		vtPecas[4] = pPeca4;
		vtPecas[5] = pPecaPerdida;

		return TST_CondRetOK;

	} /* fim ativa: Tratar: inicializar contexto */

	/* Testar Criar Tabuleiro */

	if( strcmp( ComandoTeste , CRIAR_TAB_LUDO_CMD ) == 0 )
	{
		numLidos = LER_LerParametros( "i", &CondRetEsp) ;
		if( numLidos != 1 )
		{
			return TST_CondRetParm;
		}

		CondRetObtido = TAB_CriaTabuleiro_Ludo ( &pTabuleiro ) ;

		return TST_CompararInt ( CondRetEsp, CondRetObtido, "Retorno errado ao criar tabuleiro") ;


	} /* fim ativa: Criar Tabuleiro */


	/* Testar Procurar Peça */

	else if( strcmp( ComandoTeste , PROCURA_PECA_CMD ) == 0 )
	{
		numLidos = LER_LerParametros( "ii", &indPeca, &CondRetEsp ) ;
		if( numLidos != 2 )
		{
			return TST_CondRetParm;
		}

		CondRetObtido = TAB_ProcuraPeca ( pTabuleiro, vtPecas [indPeca] ) ;

		return TST_CompararInt ( CondRetEsp, CondRetObtido, "Retorno errado ao procurar peça") ;


	} /* fim ativa: Procurar Peça */


	/* Testar Obter peça casa */

	else if( strcmp( ComandoTeste , OBTER_PECA_CASA_CMD ) == 0 )
	{
		numLidos = LER_LerParametros( "i", &CondRetEsp ) ;
		if( numLidos != 1 )
		{
			return TST_CondRetParm;
		}

		CondRetObtido = TAB_ObterPecaCasa ( pTabuleiro, &listaPecas ) ;

		return TST_CompararInt ( CondRetEsp, CondRetObtido, "Retorno errado ao Obter peça casa") ;


	} /* fim ativa: Obter peça casa */

	/* Testar Eh Casa Final */

	else if( strcmp( ComandoTeste , EH_CASA_FINAL_CMD ) == 0 )
	{
		numLidos = LER_LerParametros( "i", &CondRetEsp ) ;
		if( numLidos != 1 )
		{
			return TST_CondRetParm;
		}

		CondRetObtido = TAB_EhCasaFinal ( pTabuleiro, &casaFinal ) ;

		return TST_CompararInt ( CondRetEsp, CondRetObtido, "Retorno errado ao verificar Eh Casa Final") ;


	} /* fim ativa: Eh Casa Final */

	/* Testar Avança casa */

	else if( strcmp( ComandoTeste , AVANCA_CASA_CMD ) == 0 )
	{
		numLidos = LER_LerParametros( "iii", &cor, &avanco, &CondRetEsp ) ;
		if( numLidos != 3 )
		{
			return TST_CondRetParm;
		}

		CondRetObtido = TAB_AvancaCasa ( pTabuleiro, cor, avanco ) ;

		return TST_CompararInt ( CondRetEsp, CondRetObtido, "Retorno errado ao Avançar casa") ;


	} /* fim ativa: Avança casa */


	/* Testar Retira peça casa */

	else if( strcmp( ComandoTeste , RETIRA_PECA_CASA_CMD ) == 0 )
	{
		numLidos = LER_LerParametros( "ii", &indPeca, &CondRetEsp ) ;
		if( numLidos != 2 )
		{
			return TST_CondRetParm;
		}

		CondRetObtido = TAB_RetiraPecaCasa ( pTabuleiro, vtPecas [indPeca] ) ;

		return TST_CompararInt ( CondRetEsp, CondRetObtido, "Retorno errado ao Retirar peça casa") ;


	} /* fim ativa: Retirar peça casa */


	/* Testar Insere peça casa */

	else if( strcmp( ComandoTeste , INSERE_PECA_CASA_CMD ) == 0 )
	{
		numLidos = LER_LerParametros( "ii", &indPeca, &CondRetEsp ) ;
		if( numLidos != 2 )
		{
			return TST_CondRetParm;
		}

		CondRetObtido = TAB_InserePecaCasa ( pTabuleiro, vtPecas [indPeca] ) ;

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

}  /* Fim função: TTAB &Testar tabuleiro */

/********** Fim do módulo de implementação: TTAB Teste lista de símbolos **********/