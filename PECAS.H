#if ! defined ( PEC_ )
#define PEC_

/***************************************************************************
*
*  $MCD Módulo de definição: PEC Módulo de Peça
*
*  Arquivo gerado:              PECAS.H  
*  Letras identificadoras:      PEC
*
*  Projeto: INF 1301 / Jogo de Ludo (ou Furbica)
*  Gestor:  Professor Alessandro Garcia
*  Autores: lr -> Lucas Rodrigues
*
*  $HA Histórico de evolução:
*     Versão |  Autor  |      Data     |    Observações
*       2    |   lr    |  28/set/2016  | término desenvolvimento
*       1    |   lr    |  28/set/2016  | início desenvolvimento
*
*  $ED Descrição do módulo
*     Cria uma Peça.
*     Destroi uma Peça.
*     Obtem, dado uma Peça, informações sobre ela.
*     Atualiza as informações de uma Peça.
*
*
**************************************************************************/

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
*     Cria uma peça.
*
*  $EP Parametros
*  * pPeça - ponteiro para peça a ser criada
* 	 cor   - cor da peça
*
*  $FV Valor retornado
*     PEC_CondRetOK - se ocorreu tudo certo
*     PEC_CondRetFaltaMemoria - se faltou memoria
*     PEC_CondRetJaExiste - Se peca ja existe
*     PEC_CondRetCorInvalida - se a cor passada não for entre 0 e 3
*
***********************************************************************/

/* Assertivas de Entrada PEC_CriaPeca
*  Existir mémoria para criacao da peça
*  A cor dada (int) tem que ser entre 0 e 3
*
*  Fim Assertiva de Entrada PEC_CriaPeca */

PEC_CondRet PEC_CriaPeca ( PEC_tpPeca * pPeca, int cor ) ;

/* Assertivas de Saida PEC_CriaPeca
*  A memoria referente a estrutura da peca tem que ser alocada
*  Para todo pPeca criado, pPeca->cor entre 0 e 3
*  A funcao retornara um PEC_CondRet
*
*  Fim Assertiva de Saida PEC_CriaPeca */

/***********************************************************************
*
*  $FC função: PEC &Destruir peça
*
*  $ED Descrição da função
*     Destroi uma peça.
*
*  $EP Parametros
*   *pPeca  -  peca a ser destruida.
*
*  $FV Valor retornado
*     PEC_CondRetOK - se ocorreu tudo certo
*     PEC_CondRetNaoExiste - se peca nao existe
*
***********************************************************************/

/* Assertivas de Entrada PEC_DestroiPeca
*  Existir peça ja criada (para todo pPeca , pPeca != NULL)
*
*  Fim Assertiva de Entrada PEC_DestroiPeca */

PEC_CondRet PEC_DestroiPeca ( PEC_tpPeca pPeca ) ;
 
/* Assertiva de Saida PEC_DestroiPeca
*  A peca deve ser destruida (para todo pPeca , pPeca = NULL)
*  A memoria alocada para peca deve ser liberada 
*  A funcao retorna um PEC_CondRet
*
*  Fim Assertiva de Saida PEC_DestroiPeca */

/***********************************************************************
*
*  $FC Função: PEC  &Obtem cor
*
*  $ED Descrição da função
*     Dada uma peça, informa sua cor.
*
*  $EP Parametros
*   pPeca - peça que procura saber a cor
*  * cor - ponteiro passado para receber a cor
*
*  $FV Valor retornado
*     PEC_CondRetOK - se ocorreu tudo certo
*     PEC_CondRetNaoExiste - se peca nao existe
*
***********************************************************************/

/* Assertivas de Entrada PEC_ObtemCor
*  Deve existir uma cor valida na peca (para todo pPeca, pPeca->cor entre 0 e 3)
*
*  Fim Assertiva de Entrada PEC_ObtemCor */

PEC_CondRet PEC_ObtemCor ( PEC_tpPeca pPeca , int * cor ) ;

/*  Assertiva de Saida PEC_ObtemCor
*   Deverá ser retornado uma cor válida (inteiro entre 0 e 3)
*   A funcao retorna um PEC_CondRet
*
*   Fim Assertiva de Saida PEC_ObtemCor */

/***********************************************************************
*
*  $FC Função: PEC  &Obtem final
*
*  $ED Descrição da função
*     Dada uma peça, informa se está na casa final.
*
*  $EP Parametros
*   pPeca - peça que procura saber o final
*  * final - ponteiro passado para receber o final
*
*  $FV Valor retornado
*     PEC_CondRetOK - se ocorreu tudo certo
*     PEC_CondRetNaoExiste - se peca nao existe
*
***********************************************************************/

/* Assertivas de Entrada PEC_ObtemFinal
*  Deve existir um valor final valido na peca
*
*  Fim Assertiva de Entrada PEC_ObtemFinal */

PEC_CondRet PEC_ObtemFinal ( PEC_tpPeca pPeca , int * final ) ;

/*  Assertiva de Saida PEC_ObtemFinal
*   Deverá ser retornado um final válido (inteiro 1 ou 0)
*   A funcao retorna um PEC_CondRet
*
*   Fim Assertiva de Saida PEC_ObtemFinal */

/***********************************************************************
*
*  $FC Função: PEC  &Obtem inicio
*
*  $ED Descrição da função
*     Dada uma peça, informa se está na casa inicial.
*
*  $EP Parametros
*   pPeca - peça que procura saber o inicio
*  * inicio - ponteiro passado para receber o inicio
*
*  $FV Valor retornado
*     PEC_CondRetOK - se ocorreu tudo certo
*     PEC_CondRetNaoExiste - se peca nao existe
*
***********************************************************************/

/* Assertivas de Entrada PEC_ObtemInicio
*  Deve existir um valor de inicio valido na peca
*
*  Fim Assertiva de Entrada PEC_ObtemInicio */

PEC_CondRet PEC_ObtemInicio ( PEC_tpPeca pPeca , int * inicio ) ;

/*  Assertiva de Saida PEC_ObtemInicio
*   Deverá ser retornado um status válido (inteiro 1 ou 0)
*   A funcao retorna um PEC_CondRet
*
*   Fim Assertiva de Saida PEC_ObtemInicio */

/***********************************************************************
*
*  $FC Função: PEC  &Obtem volta completa
*
*  $ED Descrição da função
*     Dada uma peça, informa se realizou uma volta completa.
*
*  $EP Parametros
*   pPeca - peça que procura saber a volta completa
*  * inicio - ponteiro passado para receber a volta completa
*
*  $FV Valor retornado
*     PEC_CondRetOK - se ocorreu tudo certo
*     PEC_CondRetNaoExiste - se peca nao existe
*
***********************************************************************/

/* Assertivas de Entrada PEC_ObtemVoltaCompleta
*  Deve existir um valor de inicio valido na peca
*
*  Fim Assertiva de Entrada PEC_ObtemVoltaCompleta */

PEC_CondRet PEC_ObtemVoltaCompleta ( PEC_tpPeca pPeca , int * voltaCompleta ) ;

/*  Assertiva de Saida PEC_ObtemVoltaCompleta
*   Deverá ser retornado um status válido (inteiro 1 ou 0)
*   A funcao retorna um PEC_CondRet
*
*   Fim Assertiva de Saida PEC_ObtemVoltaCompleta */

/***********************************************************************
*
*  $FC Função: PEC  &Atualiza final peça
*
*  $ED Descrição da função
*     Dado uma peça, atualiza o final da peça.
*
*  $EP Parametros
*   pPeca - peça que procura saber a cor
*   final - atualizar se peça está no estágio final
*
*  $FV Valor retornado
*     PEC_CondRetOK - se ocorreu tudo certo
*     PEC_CondRetArgumentoInvalido - se final dado está invalido
*     PEC_CondRetNaoExiste - se peca nao existe
*
***********************************************************************/

/* Assertivas de Entrada PEC_AtualizaFinalPeca
*  Deve existir um valor final valido na peca
*  A peça deve existir antes de chamar a função.
*
*  Fim Assertiva de Entrada PEC_AtualizaFinalPeca */

PEC_CondRet PEC_AtualizaFinalPeca ( PEC_tpPeca pPeca , int final) ;

/*  Assertiva de Saida PEC_AtualizaFinalPeca
*   Deverá ser atualizado um final válido (inteiro 1 ou 0)
*   A funcao retorna um PEC_CondRet
*
*   Fim Assertiva de Saida PEC_AtualizaFinalPeca */

/***********************************************************************
*
*  $FC Função: PEC  &Atualiza volta peça
*
*  $ED Descrição da função
*     Dado uma peça, atualiza a volta da peça.
*
*  $EP Parametros
*   pPeca - peça que procura saber a cor
*   volta - atualizar se peça já completou uma volta
*
*  $FV Valor retornado
*     PEC_CondRetOK - se ocorreu tudo certo
*     PEC_CondRetArgumentoInvalido - se volta dado está invalido
*     PEC_CondRetNaoExiste - se peca nao existe
*
***********************************************************************/

/* Assertivas de Entrada PEC_AtualizaVoltaPeca
*  Deve existir um valor volta valido na peca
*  A peça deve existir antes de chamar a função.
*
*  Fim Assertiva de Entrada PEC_AtualizaVoltaPeca */

PEC_CondRet PEC_AtualizaVoltaPeca ( PEC_tpPeca pPeca , int volta) ;

/*  Assertiva de Saida PEC_AtualizaVoltaPeca
*   Deverá ser atualizado uma volta válida (inteiro 1 ou 0)
*   A funcao retorna um PEC_CondRet
*
*   Fim Assertiva de Saida PEC_AtualizaVoltaPeca */

/***********************************************************************
*
*  $FC Função: PEC  &Atualiza inicio peça
*
*  $ED Descrição da função
*     Dado uma peça, atualiza o inicio da peça.
*
*  $EP Parametros
*   pPeca - peça que procura saber a cor
*   inicio - atualizar se peça está nas casas iniciais
*
*  $FV Valor retornado
*     PEC_CondRetOK - se ocorreu tudo certo
*     PEC_CondRetArgumentoInvalido - se inicio dado está invalido
*     PEC_CondRetNaoExiste - se peca nao existe
*
***********************************************************************/

/* Assertivas de Entrada PEC_AtualizaInicioPeca
*  Deve existir um valor inicio valido na peca
*  A peça deve existir antes de chamar a função.
*
*  Fim Assertiva de Entrada PEC_AtualizaInicioPeca */

PEC_CondRet PEC_AtualizaInicioPeca ( PEC_tpPeca pPeca , int inicio) ;

/*  Assertiva de Saida PEC_AtualizaVoltaPeca
*   Deverá ser atualizado um inicio válido (inteiro 1 ou 0)
*   A funcao retorna um PEC_CondRet
*
*   Fim Assertiva de Saida PEC_AtualizaInicioPeca */

#undef PEC_EXT

/********** Fim do módulo de definição: PEC Módulo Peças **********/
 
#else
#endif