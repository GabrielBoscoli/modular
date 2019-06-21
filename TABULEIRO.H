#if ! defined( TABULEIRO_ )
#define TABULEIRO_
/***************************************************************************
*
*  $MCD Módulo de definição: Módulo Tabuleiro
*
*  Arquivo gerado:              TABULEIRO.H
*  Letras identificadoras:      TAB
*
*  Projeto: Disciplina INF 1301
*  Gestor:  DI/PUC-RIO, Professor Alessandro Garcia
*  Autores: gb - Gabriel Boscoli 
*
*  $HA Histórico de evolução:
*     Versão   Autor        Data         Observações
*	   3.00     gb       14/06/2019   ajustes e leves mudanças
*      2.00     gb       28/04/2019   finalização do desenvolvimento
*      1.00     gb       26/04/2019   início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo implementa um tabuleiro de ludo.
*	  Podem existir n tabuleiros em operação simultaneamente.
*     O tabuleiro possui uma cabeça encapsulando o seu estado.
*     É possivel criar um tabuleiro, deletar um tabuleiro,
*     inserir peca em um tabuleiro, mover peca de um tabuleiro,
*     e obter informações sobre as casas do tabuleiro.
*	  A responsabilidade de liberar espaço alocado por peças
*	  é do cliente.
*   
***************************************************************************/

#if defined( TABULEIRO_OWN )
   #define TABULEIRO_EXT
#else
    #define TABULEIRO_EXT extern
#endif

#include "LISCIR.H"
#include "LISTA.H"
#include "PECA.H"

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para um tabuleiro */

typedef struct TAB_tagTabuleiro * TAB_tppTabuleiro;

/***********************************************************************
*
*  $TC Tipo de dados: TAB Condições de retorno
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do tabuleiro
*
***********************************************************************/

   typedef enum {

          TAB_CondRetOK,
          /* Concluiu corretamente */   

          TAB_CondRetFaltouMemoria, 
          /* Faltou Memoria */

          TAB_CondRetPecaNaoExiste,
          /* Peça não criada */
         
          TAB_CondRetPecaCasaInicial,
          /* Peça está na casa inicial */

          TAB_CondRetNaoEncontrouPeca,
          /* Não encontrou */

          TAB_CondRetCorInvalida,
          /* Cor inválida */
          
          TAB_CondRetFimTabuleiro,
          /* Chegou ao final do tabuleiro */

		  TAB_CondRetTabuleiroNaoExiste,
		  /* Tabuleiro não foi criado */

		  TAB_CondRetAvancoInvalido,
		  /* Número de casas para avancar é inválido */

		  TAB_CondRetConteudoNulo,
		  /* O conteudo de uma casa é igual a NULL */

		  TAB_CondRetTrajetoCircularInexistente,
		  /* O trajeto circular do tabuleiro é inexistente */

		  TAB_CondRetCasaNula
		  /* A casa obtida é igual a NULL */
   
   } TAB_CondRet ;


/***********************************************************************
*
*  $FC Função: TAB  &Cria Tabuleiro
*
*  $ED Descrição da função
*		Cria uma tabuleiro de ludo utilizando lista circular e lisa encadeada. 
*		Ele pode armazenar peças de qualquer tipo.
*
*  $EP Parâmetros
*		* pTabuleiro - ponteiro para tabuleiro a ser criado.
*
*  $FV Valor retornado
*		TAB_CondRetOK - se criou tabuleiro corretamente.
*		TAB_CondRetFaltouMemoria - se houve algum problema de memoria.
*
*  $EAE Assertivas de entrada
*		Deve existir memoria para criacao do tabuleiro
*
*  $EAE Assertivas de saida
*		SE TAB_CondRetOK
*			Tabuleiro é criado
*			Tabuleiro é referenciado pelo parametro pTabuleiro
*		SE NAO
*			Tabuleiro nao é criado
*			pTabuleiro = NULL
*
***********************************************************************/

TAB_CondRet TAB_CriarTabuleiro( TAB_tppTabuleiro * pTabuleiro ) ; 

/***********************************************************************
*
*  $FC Função: TAB  &Destroi tabuleiro
*
*  $ED Descrição da função
*		Destrói o tabuleiro criado.
*
*  $EP Parâmetros
*		pTabuleiro - ponteiro para tabuleiro a destruir.    
*
*  $FV Valor retornado
*		TAB_CondRetOK - destruiu corretamente.
*		TAB_CondRetTabuleiroNaoExiste - se tabuleiro a ser destruido nao existe.
*
*  $EAE Assertivas de entrada
*		pTabuleiro deve ser um tabuleiro existente (pTabuleiro != NULL)
*
*  $EAE Assertivas de saida
*		SE TAB_CondRetOK
*			O tabuleiro é destruido
*			Memoria alocada para o tabuleiro é liberada
*		SE NAO
*			Nada acontece
*
*
***********************************************************************/

TAB_CondRet TAB_DestruirTabuleiro ( TAB_tppTabuleiro pTabuleiro ) ;

/***********************************************************************
*
*  $FC Função: TAB  &Procura Peça
*
*  $ED Descrição da função
*		Procura uma determinada peça no tabuleiro.
*
*  $EP Parâmetros
*		pTabuleiro - ponteiro tabuleiro passado como referencia  
*		pPeca - ponteiro para peça a ser procuurada. 
*
*  $FV Valor retornado
*		TAB_CondRetOK - se peça procurada foi encontrada.
*		TAB_CondRetPecaNaoExiste - se peça procurada não existe.
*		TAB_CondRetPecaCasaInicial - se peça está na casa inicial.
*		TAB_CondRetNaoEncontrouPeca - se a peça procurada não foi encontrada.
*		TAB_CondRetTabuleiroNaoExiste - se tabuleiro nao existe.
*
*  $EAE Assertivas de entrada
*		pTabueleiro deve ser um tabuleiro existente (pTabuleiro != NULL)
*		pPeca deve ser uma peca existente (pPeca != NULL)
*
*  $EAE Assertivas de saida
*		SE TAB_CondRetOK
*			A peca é encontrada
*			O elemento corrente do tabuleiro é a casa em que está a peca
*		SE NAO
*			Elemento corrente do tabuleiro permanece o mesmo
*
***********************************************************************/

TAB_CondRet TAB_ProcurarPeca ( TAB_tppTabuleiro pTabuleiro , PEC_tppPeca pPeca ) ;

/***********************************************************************
*
*  $FC Função: TAB  &Obter Peça Casa
*
*  $ED Descrição da função
*		Obtem as peças da casa corrente do tabuleiro.
*
*  $EP Parâmetros
*		pTabuleiro - ponteiro para tabuleiro passado como referencia.
*		pListaPeca - ponteiro para lugar a ser aramzenado dados da Peça da casa   
*
*  $FV Valor retornado
*		TAB_CondRetOK - se ocorreu tudo certo.
*		TAB_CondRetTabuleiroNaoExiste - se tabuleiro nao existe.
*		TAB_CondRetConteudoNulo - se o conteudo da casa é nulo.
*
*  $EAE Assertivas de entrada
*		pTabuleiro deve ser um tabuleiro existente (pTabuleiro != NULL)
*
*  $EAE Assertivas de saida
*		SE TAB_CondRetOK
*			As pecas da casa corrente sao obtidas
*			pListaPeca referencia as pecas
*			Caso a casa corrente nao tenha pecas, pListaPeca é uma lista vazia
*		SE TAB_CondRetConteudoNulo
*			pListaPeca é igual a NULL
*		SE NAO
*			pListaPeca permanece com o valor original
*
***********************************************************************/

TAB_CondRet TAB_ObterConteudoCasa ( TAB_tppTabuleiro pTabuleiro, LIS_tppLista *pListaPeca ) ;

/***********************************************************************
*
*  $FC Função: TAB  &Avança Casa
*
*  $ED Descrição da função
*		Avança, dado um valor n, n casas no tabuleiro.
*
*  $EP Parâmetros
*		pTabuleiro - ponteiro para tabuleiro passado como referencia.
*		cor - informação da cor da peca que pretende avancar. 
*		n - numero inteiro de casas a ser avançadas.
*		volta - inteiro de controle para, caso a casa corrente seja
*				uma casa de saida com mesma cor, decidir se deve 
*				fazer a volta (!= 0) ou então entrar direto na reta final (0)
*
*  $FV Valor retornado
*		TAB_CondRetOK - se ocorreu tudo certo.
*		TAB_CondRetCorInvalida - caso a cor passada seja inválida.
*		TAB_CondRetFimTabuleiro - caso tenha chegado ao "fim" do tabuleiro.
*		TAB_CondRetTabuleiroNaoExiste - se tabuleiro nao existe.
*		TAB_CondRetAvancoInvalido - se o numero de casa para avancar é negativo.
*
*  $EAE Assertivas de entrada
*		pTabuleiro deve ser um tabuleiro existente (pTabuleiro != NULL)
*		cor deve ser um inteiro de 0 a 3
*		n deve ser um inteiro positivo
*
*  $EAE Assertivas de saida
*		SE TAB_CondRetOK
*			O elemento corrente se desloca n elementos para frente
*		SE NAO
*			Elemento corrente permanece o mesmo
*
***********************************************************************/

TAB_CondRet TAB_AvancarCasa ( TAB_tppTabuleiro pTabuleiro , int cor , int n , int volta ) ;

/***********************************************************************
*
*  $FC Função: TAB  &Retira Peça da Casa
*
*  $ED Descrição da função
*		Retira uma determinada peça passada como parâmetro de sua casa.
*
*  $EP Parâmetros
*		pTabuleiro - ponteiro para tabuleiro passado como referencia.
*		pPeca - ponteiro para peça a ser retirada.
*
*  $FV Valor retornado
*		TAB_CondRetOK - se ocorreu tudo certo.
*		TAB_CondRetPecaNaoExiste - se peça a ser retirada não existe.
*		TAB_CondRetPecaCasaInicial - se peça está na casa inicial.
*		TAB_CondRetNaoEncontrouPeca - se a peça a ser retirada não foi encontrada.
*		TAB_CondRetTabuleiroNaoExiste - se tabuleiro nao existe.
*
*  $EAE Assertivas de entrada
*		pTabuleiro deve ser um tabuleiro existente (pTabuleiro != NULL)
*		pPeca deve ser uma peca existente (pPeca != NULL)
*
*  $EAE Assertivas de saida
*		SE TAB_CondRetOK
*			A peca em questao é retirada
*			Se so tinha uma peca, a casa fica vazia
*			O elemento corrente se torna a casa em que a peca retirada estava
*		SE NAO
*			Elemento corrente permanece o mesmo
*			Peca nao é removida
*
*
***********************************************************************/

TAB_CondRet TAB_RetirarPecaCasa ( TAB_tppTabuleiro pTabuleiro , PEC_tppPeca pPeca ) ;

/***********************************************************************
*
*  $FC Função: TAB  &Insere Peça da Casa
*
*  $ED Descrição da função
*		Insere a peça na casa corrente do tabuleiro.
*
*  $EP Parâmetros
*		pTabuleiro - ponteiro para tabuleiro passado como referencia.
*		pPeca - ponteiro para peça a ser retirada.
*		volta - inteiro de controle que define se a peca foi colocada
*				de volta no tabuleiro de uma casa inicial (0) ou entao 
*				se esta apenas realizando sua volta (!= 0)
*
*  $FV Valor retornado
*		TAB_CondRetOK - se ocorreu tudo certo.
*		TAB_CondRetPecaNaoExiste - se peça a ser inserida não existe.
*		TAB_CondRetTabuleiroNaoExiste - se tabuleiro nao existe.
*
*  $EAE Assertivas de entrada
*		pTabuleiro deve ser um tabuleiro existente (pTabuleiro != NULL)
*		pPeca deve ser uma peca existente (pPeca != NULL)
*
*  $EAE Assertivas de saida
*		SE TAB_CondRetOK
*			A peca é inserida na casa corrente
*		SE NAO
*			A peca nao é inserida
*
***********************************************************************/

TAB_CondRet TAB_InserirPecaCasa ( TAB_tppTabuleiro pTabuleiro , PEC_tppPeca pPeca , int volta ) ;

/***********************************************************************
*
*  $FC Função: TAB  &Ir Casa Saída Cor
*
*  $ED Descrição da função
*		Dado uma cor, vai à sua casa de saída no tabuleiro.
*
*  $EP Parâmetros
*		pTabuleiro - ponteiro para tabuleiro passado como referencia.
*		cor - valor correspondente a cor que se deseja ir à casa de saída.
*
*  $FV Valor retornado
*		TAB_CondRetOK - se ocorreu tudo certo.
*		TAB_CondRetCorInvalida - se a cor passada é inválida
*		TAB_CondRetTabuleiroNaoExiste - se tabuleiro nao existe.
*
*  $EAE Assertivas de entrada
*		pTabuleiro deve ser um tabuleiro existente (pTabuleiro != NULL)
*		cor deve ser um inteiro de 0 a 3
*
*  $EAE Assertivas de saida
*		SE TAB_CondRetOK
*			O elemento corrente se torna a casa de saida da cor passada 
*			como parametro
*		SE NAO
*			Elemento corrente do tabuleiro permanece o mesmo
*
***********************************************************************/

TAB_CondRet TAB_IrCasaSaidaCor ( TAB_tppTabuleiro pTabuleiro , int cor ) ;

/***********************************************************************
*
*  $FC Função: TAB  &Verifica Casa Final
*
*  $ED Descrição da função
*		Verifica se a casa corrente do tabuleiro é a final.
*
*  $EP Parâmetros
*		pTabuleiro - ponteiro para tabuleiro passado como referencia.
*		pResposta - ponteiro para armazenar resposta, 1 se é casa final e 0 se não é.
*
*  $FV Valor retornado
*		TAB_CondRetOK - se ocorreu tudo certo.
*		TAB_CondRetTabuleiroNaoExiste - se tabuleiro nao existe.
*
*  $EAE Assertivas de entrada
*		pTabuleiro deve ser um tabuleiro existente (pTabuleiro != NULL)
*
*  $EAE Assertivas de saida
*		SE TAB_CondRetOK
*			pResposta tem o valor 1 caso a casa corrente seja final
*			pResposta tem o valor 0 caso a casa corrente nao seja final
*		SE NAO
*			pResposta permanece com o valor original
*
*
***********************************************************************/

TAB_CondRet TAB_VerificaCasaFinal ( TAB_tppTabuleiro pTabuleiro , int * pResposta ) ;

/***********************************************************************
*
*  $FC Função: TAB  &Exibe Tabuleiro
*
*  $ED Descrição da função
*		Imprime na tela o formato de um tabuleiro.
*		Todos os tabuleiros criados tem o mesmo formato.
*
*  $FV Valor retornado
*		TAB_CondRetOK - se ocorreu tudo certo.
*
*  $EAE Assertivas de saida
*		SE TAB_CondRetOK
*			O tabuleiro é exibido
*
***********************************************************************/

TAB_CondRet TAB_ExibeTabuleiro ();

/***********************************************************************
*
*  $FC Função: TAB  &Exibe Legenda Tabuleiro
*
*  $ED Descrição da função
*		Imprime na tela a legenda do tabuleiro.
*		Todos os tabuleiros criados seguem a mesma legenda.
*
*  $FV Valor retornado
*		TAB_CondRetOK - se ocorreu tudo certo.
*
*  $EAE Assertivas de saida
*		SE TAB_CondRetOK
*			A legenda do tabuleiro é exibida
*
***********************************************************************/

TAB_CondRet TAB_ExibeLegendaTabuleiro ();

/***********************************************************************
*
*  $FC Função: TAB  &Obter Numero Casa
*
*  $ED Descrição da função
*		Obtem o numero da casa corrente do tabuleiro
*		O numero de uma casa é uma forma de identifica-la
*
*  $EP Parâmetros
*		pTabuleiro - ponteiro para tabuleiro passado como referencia.
*		pNumeroCasa - ponteiro para armazenar o numero da casa.
*
*  $FV Valor retornado
*		TAB_CondRetOK - se ocorreu tudo certo.
*		TAB_CondRetTabuleiroNaoExiste - se tabuleiro nao existe.
*		TAB_CondRetTrajetoCircularInexistente - se tabuleiro nao possui trajeto circular.
*		TAB_CondRetCasaNula - se a casa corrente é igual a NULL.
*
*  $EAE Assertivas de entrada
*		pTabuleiro deve ser um tabuleiro existente (pTabuleiro != NULL)
*		O tabuleiro deve conter um trajeto circular
*		O trajeto circular deve conter casas
*		Todas as casas no trajeto devem ser diferentes de NULL
*
*  $EAE Assertivas de saida
*		SE TAB_CondRetOK
*			O numero da casa é obtido
*			pNumeroCasa faz referencia ao numero obtido
*		SE NAO
*			pNumeroCasa permanece com o valor original
*
***********************************************************************/

TAB_CondRet TAB_ObterNumeroCasa ( TAB_tppTabuleiro pTabuleiro, int* pNumeroCasa );

/***********************************************************************
*
*  $FC Função: TAB  &Verifica Casa de Saida
*
*  $ED Descrição da função
*		Verifica se a casa corrente do tabuleiro é uma casa de saída.
*
*  $EP Parâmetros
*		pTabuleiro - ponteiro para tabuleiro passado como referencia.
*		pResposta - ponteiro para armazenar resposta, 1 se é casa de saída e 0 se não é.
*
*  $FV Valor retornado
*		TAB_CondRetOK - se ocorreu tudo certo.
*		TAB_CondRetTabuleiroNaoExiste - se tabuleiro nao existe.
*		TAB_CondRetTrajetoCircularInexistente - se tabuleiro nao possui trajeto circular.
*		TAB_CondRetCasaNula - se a casa corrente é igual a NULL.
*
*  $EAE Assertivas de entrada
*		pTabuleiro deve ser um tabuleiro existente (pTabuleiro != NULL)
*
*  $EAE Assertivas de saida
*		SE TAB_CondRetOK
*			pResposta tem o valor 1 caso a casa corrente seja final
*			pResposta tem o valor 0 caso a casa corrente nao seja final
*		SE NAO
*			pResposta permanece com o valor original
*
*
***********************************************************************/

TAB_CondRet TAB_VerificaCasaSaida ( TAB_tppTabuleiro pTabuleiro , int * pResposta ) ;

#undef TABULEIRO_EXT

/*********** Fim do módulo de definição: TAB Módulo Tabuleiro **********/

#else
#endif