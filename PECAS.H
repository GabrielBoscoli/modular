#if ! defined ( PEC_ )
#define PEC_
/***************************************************************************
*  $MCD Módulo de definição: PEC Módulo Peças
*
*  Arquivo gerado:              PECAS.H
*  Letras identificadoras:      PEC
*
*  Projeto: Disciplina INF 1301
*  Gestor:  DI/PUC-Rio, Professor Alessandro Garcia
*  Autores: gb - Gabriel Boscoli
*
* $HA Histórico de evolução:
*     Versão    Autor       Data          Observações
*	   2.00      gb      24/04/2019   término, revisão e aperfeiçoamento
*      1.00      gb      22/04/2019   início desenvolvimento, implementação de
*									  funções básicas
*
*  $ED Descrição do módulo
*     Cria uma Peça.
*     Destroi uma Peça.
*     Obtem informações sobre uma Peça.
*     Atualiza as informações de uma Peça.
*
***************************************************************************/

#if defined( PEC_OWN )
#define PEC_EXT
#else
   #define PEC_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma peça */

typedef struct Peca * PEC_tpPeca; 

/***********************************************************************
*
*  $TC Tipo de dados: PEC condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da peça
*
***********************************************************************/

typedef enum {

	PEC_CondRetOK ,
		/* Ocorreu tudo certo */

	PEC_CondRetFaltaMemoria , 
		/* Faltou memória na alocação */

	PEC_CondRetCorInvalida ,
		/* Cor inválida */

	PEC_CondRetNaoExiste ,
		/* Peca nao existe */

	PEC_CondRetArgumentoInvalido
		/* Argumento passado para a função é invalido */
	

} PEC_CondRet;

/***********************************************************************
*
*  $TC Tipo de dados: PEC condições de retorno
*
*
*  $ED Descrição do tipo
*     Possiveis cores para os jogadores e suas peças
*
***********************************************************************/

typedef enum {

	PEC_Vermelho ,

	PEC_Amarelo ,
	
	PEC_Verde ,

	PEC_Azul 
	
} PEC_Cores;

/***********************************************************************
*
*  $FC Função: PEC &Criar PEC
*
*  $ED Descrição da função
*		Cria uma peça.
*
*  $EP Parametros
*		* pPeça - ponteiro para peça a ser criada
* 		cor   - cor da peça
*
*  $FV Valor retornado
*		PEC_CondRetOK - se ocorreu tudo certo
*		PEC_CondRetFaltaMemoria - se faltou memoria
*		PEC_CondRetCorInvalida - se a cor passada não for entre 0 e 3
*
*  $EAE Assertivas de entrada
*		Deve existir memoria para criacao da peca
*		A cor dada deve ser um int de 0 a 3
*
*  $EAE Assertivas de saída
*		SE PEC_CondRetOK
*			A peca é criada e referenciada por pPeca
*		SE PEC_CondRetFaltaMemoria
*			A peca não é criada
*			pPeca = NULL
*		SE PEC_CondRetCorInvalida
*			A peca não é criada
*			pPeca permanece com o mesmo valor de entrada
*
*
***********************************************************************/

PEC_CondRet PEC_CriaPeca ( PEC_tpPeca * pPeca, int cor ) ;

/***********************************************************************
*
*  $FC função: PEC &Destruir peça
*
*  $ED Descrição da função
*		Destroi uma peça.
*
*  $EP Parametros
*		pPeca  -  peca a ser destruida.
*
*  $FV Valor retornado
*		PEC_CondRetOK - se ocorreu tudo certo
*		PEC_CondRetNaoExiste - se peca nao existe
*
*  $EAE Assertivas de entrada
*		pPeca deve ser uma peca existente (pPeca != NULL )
*
*  $EAE Assertivas de saída
*		SE PEC_CondRetOK
*			A peca é destruida
*			Memoria alocada para a peca é liberada
*		SE PEC_CondRetNaoExiste
*			Nada acontece
*
*
*
***********************************************************************/

PEC_CondRet PEC_DestroiPeca ( PEC_tpPeca pPeca ) ;

/***********************************************************************
*
*  $FC Função: PEC  &Obtem cor
*
*  $ED Descrição da função
*		Dada uma peça, informa sua cor.
*
*  $EP Parametros
*		pPeca - peça que procura saber a cor
*		* cor - ponteiro passado para receber a cor
*
*  $FV Valor retornado
*		PEC_CondRetOK - se ocorreu tudo certo
*		PEC_CondRetNaoExiste - se peca nao existe
*
*  $EAE Assertivas de entrada
*		pPeca deve ser uma peca existente (pPeca != NUll)
*
*  $EAE Assertivas de saída
*		SE PEC_CondRetOK
*			A cor da peca, int de 0 a 3, é armazenada na variavel cor
*		SE PEC_CondRetNaoExiste
*			A variavel cor continua com seu valor original
*
*
***********************************************************************/

PEC_CondRet PEC_ObtemCor ( PEC_tpPeca pPeca , int * cor ) ;

/***********************************************************************
*
*  $FC Função: PEC  &Obtem final
*
*  $ED Descrição da função
*		Dada uma peça, informa se está na reta final.
*
*  $EP Parametros
*		pPeca - peça que procura saber o final
*		* final - ponteiro passado para receber o final
*
*  $FV Valor retornado
*		PEC_CondRetOK - se ocorreu tudo certo
*		PEC_CondRetNaoExiste - se peca nao existe
*
*  $EAE Assertivas de entrada
*		pPeca deve ser uma peca existente (pPeca != NUll)
*
*  $EAE Assertivas de saída
*		SE PEC_CondRetOK
*			final é 0 caso a peca nao esteja na reta final e 1 caso contrario
*		SE PEC_CondRetNaoExiste
*			A variavel final continua com seu valor original
*
*
***********************************************************************/

PEC_CondRet PEC_ObtemFinal ( PEC_tpPeca pPeca , int * final ) ;

/***********************************************************************
*
*  $FC Função: PEC  &Obtem inicio
*
*  $ED Descrição da função
*		Dada uma peça, informa se está na casa inicial.
*
*  $EP Parametros
*		pPeca - peça que procura saber o inicio
*		* inicio - ponteiro passado para receber o inicio
*
*  $FV Valor retornado
*		PEC_CondRetOK - se ocorreu tudo certo
*		PEC_CondRetNaoExiste - se peca nao existe
*
*  $EAE Assertivas de entrada
*		pPeca deve ser uma peca existente (pPeca != NUll)
*
*  $EAE Assertivas de saída
*		SE PEC_CondRetOK
*			inicio é 0 caso a peca nao esteja na casa inicial e 1 caso contrario
*		SE PEC_CondRetNaoExiste
*			A variavel inicio continua com seu valor original
*
*
***********************************************************************/

PEC_CondRet PEC_ObtemInicio ( PEC_tpPeca pPeca , int * inicio ) ;

/***********************************************************************
*
*  $FC Função: PEC  &Obtem volta completa
*
*  $ED Descrição da função
*		Dada uma peça, informa se realizou uma volta completa.
*
*  $EP Parametros
*		pPeca - peça que procura saber a volta completa
*		* inicio - ponteiro passado para receber a volta completa
*
*  $FV Valor retornado
*		PEC_CondRetOK - se ocorreu tudo certo
*		PEC_CondRetNaoExiste - se peca nao existe
*
*  $EAE Assertivas de entrada
*		pPeca deve ser uma peca existente (pPeca != NUll)
*
*  $EAE Assertivas de saída
*		SE PEC_CondRetOK
*			voltaCompleta é 0 caso a peca tenha realizado uma volta e 1 caso contrario
*		SE PEC_CondRetNaoExiste
*			A variavel voltaCompleta continua com seu valor original
*
*
***********************************************************************/

PEC_CondRet PEC_ObtemVoltaCompleta ( PEC_tpPeca pPeca , int * voltaCompleta ) ;

/***********************************************************************
*
*  $FC Função: PEC  &Atualiza final peça
*
*  $ED Descrição da função
*		Dado uma peça, atualiza se ela esta na reta final ou nao.
*
*  $EP Parametros
*		pPeca - peça que procura saber a cor
*		final - valor atualizado de final
*
*  $FV Valor retornado
*		PEC_CondRetOK - se ocorreu tudo certo
*		PEC_CondRetArgumentoInvalido - se final dado está invalido
*		PEC_CondRetNaoExiste - se peca nao existe
*
*  $EAE Assertivas de entrada
*		pPeca deve ser uma peca existente (pPeca != NULL)
*		final deve ser um int 0, caso peca esteja na reta final, ou 1, caso contrario
*
*  $EAE Assertivas de saída
*		SE PEC_CondRetOK
*			A peca é atualizada com o novo valor de final
*		SE NAO
*			A peca não é atualizada
*
*
***********************************************************************/

PEC_CondRet PEC_AtualizaFinalPeca ( PEC_tpPeca pPeca , int final) ;

/***********************************************************************
*
*  $FC Função: PEC  &Atualiza volta peça
*
*  $ED Descrição da função
*		Dado uma peça, atualiza se a peca realizou uma volta ou nao.
*
*  $EP Parametros
*		pPeca - peça que procura saber a cor
*		volta - valor atualizado de volta
*
*  $FV Valor retornado
*		PEC_CondRetOK - se ocorreu tudo certo
*		PEC_CondRetArgumentoInvalido - se volta dado está invalido
*		PEC_CondRetNaoExiste - se peca nao existe
*
*  $EAE Assertivas de entrada
*		pPeca deve ser uma peca existente (pPeca != NULL)
*		volta deve ser um int 0, caso peca realizou uma volta, ou 1, caso contrario
*
*  $EAE Assertivas de saída
*		SE PEC_CondRetOK
*			A peca é atualizada com o novo valor de volta
*		SE NAO
*			A peca não é atualizada
*
*
***********************************************************************/

PEC_CondRet PEC_AtualizaVoltaPeca ( PEC_tpPeca pPeca , int volta) ;

/***********************************************************************
*
*  $FC Função: PEC  &Atualiza inicio peça
*
*  $ED Descrição da função
*		Dado uma peça, atualiza se a peca esta na casa inicial ou nao.
*
*  $EP Parametros
*		pPeca - peça que procura saber a cor
*		inicio - valor atualizado de inicio
*
*  $FV Valor retornado
*		PEC_CondRetOK - se ocorreu tudo certo
*		PEC_CondRetArgumentoInvalido - se inicio dado está invalido
*		PEC_CondRetNaoExiste - se peca nao existe
*
*  $EAE Assertivas de entrada
*		pPeca deve ser uma peca existente (pPeca != NULL)
*		inicio deve ser um int 0, caso peca esteja na casa inicial, ou 1, caso contrario
*
*  $EAE Assertivas de saída
*		SE PEC_CondRetOK
*			A peca é atualizada com o novo valor de inicio
*		SE NAO
*			A peca não é atualizada
*
*
***********************************************************************/

PEC_CondRet PEC_AtualizaInicioPeca ( PEC_tpPeca pPeca , int inicio) ;

#undef PEC_EXT

/********** Fim do módulo de definição: PEC Módulo Peças **********/
 
#else
#endif