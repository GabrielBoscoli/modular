#if ! defined( LISCIR_ )
#define LISCIR_
/***************************************************************************
 *
 *  $MCD M�dulo de defini��o: LISCIR Lista Duplamente Encadeada Circular
 *
 *  Arquivo gerado:              LISCIR.H
 *  Letras identificadoras:      LISCIR
 *
 *  Projeto: Disciplina INF 1301
 *  Gestor:  DI/ PUC-RIO, Professor Alessandro Garcia
 *  Autores: gb - Gabriel Boscoli
 *
 *  $HA Hist�rico de evolu��o:
 *     Vers�o   Autor        Data         Observa��es
 *      2.00     gb      20/04/2019   t�rmino desenvolvimento
 *      1.00     gb      19/04/2019   in�cio desenvolvimento
 *
 *  $ED Descri��o do m�dulo
 *     Implementa listas circulares gen�ricas duplamente encadeadas.
 *	   Podem existir n listas em opera��o simultaneamente.
 *     As listas possuem uma cabe�a encapsulando o seu estado.
 *
 *     Cada lista � homog�nea quanto ao tipo dos dados que armazena.
 *     Cada elemento da lista referencia o valor que cont�m.
 *
 *     Os ponteiros para os dados s�o copiados para elementos da lista.
 *        N�o � copiado o valor apontado por estes ponteiros.
 *
 *     O controle da destrui��o do valor de um elemento a ser exclu�do
 *        � realizado por uma fun��o fornecida pelo usu�rio.
 *
 *     Cada lista referencia uma fun��o que determina como devem ser
 *        desalocados os dados nela contidos.
 *
 *     A fun��o de libera��o dos valores contidos nos elementos deve
 *        assegurar a libera��o de todos os espa�os refer�nciados pelo
 *        valor contido em um elemento.
 *        Esta fun��o � chamada antes de se desalocar um elemento
 *        de uma lista.
 *        Caso n�o seja necess�rio desalocar o valor referenciado pelo
 *        elemento, o ponteiro para a fun��o de libera��o poder� ser NULL .
 *        Caso o elemento da lista seja a �nica �ncora do valor referenciado,
 *        esta fun��o deve promover a destrui��o (free) desse valor e
 *        de todos os dados nele ancorados.
 *
 ***************************************************************************/

#if defined( LISCIR_OWN )
   #define LISCIR_EXT
#else
   #define LISCIR_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para uma lista */

	typedef struct LISCIR_tagListaCircular * LISCIR_tppListaCircular ;

/***********************************************************************
 *
 *  $TC Tipo de dados: LISCIR Condi��es de retorno
 *
 *
 *  $ED Descri��o do tipo
 *     Condi��es de retorno das fun��es da lista duplamente encadeada
 *           circular.
 *
 ***********************************************************************/

	typedef enum {
    
		LISCIR_CondRetOK ,
			/* Concluiu corretamente */
    
		LISCIR_CondRetNaoAchou ,
			/* N�o encontrou o valor procurado */
    
		LISCIR_CondRetMemoriaCheia ,
			/* Faltou memoria para alocar elemento */
    
		LISCIR_CondRetListaVazia ,
			/* A lista n�o contem elementos */

		LISCIR_CondRetListaNaoExiste
			/* A lista n�o existe */
    
	} LISCIR_CondRet ;

/***********************************************************************
 *
 *  $FC Fun��o: LISCIR  &Criar lista
 *
 *  $ED Descri��o da fun��o
 *     Cria uma lista duplamente encadeada circular gen�rica.
 *     Os poss�veis tipos s�o desconhecidos a priori.
 *
 *  $EP Par�metros
 *     * pLista		- ponteiro para a lista a ser criada.
 *     ExcluirValor	- ponteiro para a fun��o que processa a exclus�o
 *					  do valor referenciado pelo elemento a ser
 *					  exclu�do.
 *
 *  $FV Valor retornado
 *     LISCIR_CondRetOK			- se ocorreu tudo certo
 *	   LISCIR_CondRetMemoriaCheia	- se faltou memoria
 *
 *  $EAE Assertivas de entrada
 *		Deve existir mem�ria para a cria��o da lista
 *
 *  $EAE Assertivas de sa�da
 *		SE LISCIR_CondRetOK
 *			A lista � criada e referenciada por pLista
 *		SE NAO
 *			A lista n�o � criada
 *			pLista = NULL
 *
 ***********************************************************************/

	LISCIR_CondRet LISCIR_CriarLista ( LISCIR_tppListaCircular * pLista,
                           void ( * ExcluirValor ) ( void *pValor ) );

/***********************************************************************
 *
 *  $FC Fun��o: LISCIR  &Excluir elemento
 *
 *  $ED Descri��o da fun��o
 *     Remove o elemento procurado da lista dada.
 *     Se existir somente um elemento a lista tornou-se vazia.
 *
 *  $EP Par�metros
 *     pLista		- ponteiro para a lista.
 *     pElemento		- ponteiro para elemento que se deseja retirar da lista.
 *
 *  $FV Valor retornado
 *     LISCIR_CondRetOK				- se removeu corretamente
 *     LISCIR_CondRetNaoAchou			- se elemento n�o foi encontrado
 *     LISCIR_CondRetListaVazia        - se n�o h� elemento na lista
 *	   LISCIR_CondRetListaNaoExiste	- se lista nao existe
 *
 *  $EAE Assertivas de entrada
 *		pLista deve ser uma lista existente (pLista != NULL)
 *		O elemento procurado deve existir
 *		O elemento procurado deve estar na lista
 *
 *  $EAE Assertivas de sa�da
 *		SE LISCIR_CondRetOK
 *			O elemento � removido
 *			O elemento corrente � o elemento anterior ao que foi removido
 *			Caso nao exista elemento anterior, a lista fica vazia
 *		SE NAO
 *			O elemento nao � removido
 *			Lista continua da mesma forma
 *
 ***********************************************************************/

	LISCIR_CondRet LISCIR_ExcluirElemento ( LISCIR_tppListaCircular pLista, void * pElemento  ) ;

/***********************************************************************
 *
 *  $FC Fun��o: LISCIR  &Destruir Lista
 *
 *  $ED Descri��o da fun��o
 *     Destr�i a lista fornecida.
 *
 *  $EP Par�metros
 *     pLista     - ponteiro para a lista na qual deve ser destruida.
 *
 *  $FV Valor retornado
 *     LISCIR_CondRetOK				- destruiu lista sem problemas.
 *	   LISCIR_CondRetListaNaoExiste	- se lista nao existe
 *
 *  $EAE Assertivas de entrada
 *		pLista deve ser uma lista existente (pLista != NULL)
 *
 *  $EAE Assertivas de sa�da
 *		SE LISCIR_CondRetOK
 *			A lista � destruida
 *			A memoria alocada � liberada
 *		SE LISCIR_CondRetListaNaoExiste
 *			Nada acontece
 *
 ***********************************************************************/

	LISCIR_CondRet LISCIR_DestruirLista ( LISCIR_tppListaCircular pLista ) ;

/***********************************************************************
 *
 *  $FC Fun��o: LISCIR  &Esvaziar lista
 *
 *  $ED Descri��o da fun��o
 *     Elimina todos os elementos, sem eliminar a lista
 *
 *  $EP Par�metros
 *     pLista - ponteiro para a lista a ser esvaziada
 *
 *  $FV Valor retornado
 *     LISCIR_CondRetOK				- esvaziou lista sem problemas.
 *	   LISCIR_CondRetListaVazia		- lista em questao ja estava vazia
 *	   LISCIR_CondRetListaNaoExiste	- se lista nao existe
 *
 *  $EAE Assertivas de entrada
 *		pLista deve ser uma lista existente  (pLista != NULL)
 *
 *  $EAE Assertivas de sa�da
 *		SE LISCIR_CondRetOK
 *			Todos os elementos da lista s�o removidos
 *			A memoria alocada para os elementos deve ser liberada
 *			A lista fica vazia
 *		SE NAO
 *			Nada acontece
 *
 ***********************************************************************/

	LISCIR_CondRet LISCIR_EsvaziarLista ( LISCIR_tppListaCircular pLista ) ;

/***********************************************************************
 *
 *  $FC Fun��o: LISCIR  &Procurar elemento na lista
 *
 *  $ED Descri��o da fun��o
 *     Procura o elemento desejado e o deixa na posi��o corrente.
 *
 *  $EP Par�metros
 *     pLista		- ponteiro para a lista onde procura
 *     * pValor		- ponteiro pra o endere�o do elemento desejado
 *
 *  $FV Valor retornado
 *     LISCIR_CondRetOK				- se encontrou o elemento.
 *     LISCIR_CondRetNaoAchou			- se o elemento n�o foi encontrado.
 *     LISCIR_CondRetListaVazia        - se a lista est� vazia
 *	   LISCIR_CondRetListaNaoExiste	- se lista nao existe
 *
 *  $EAE Assertivas de entrada
 *		pLista deve ser uma lista existente  (pLista != NULL)
 *		valor deve ser um ponteiro que esta armazenado na lista
 *
 *  $EAE Assertivas de sa�da
 *		SE LISCIR_CondRetOK
 *			O elemento corrente � o elemento com o valor procurado
 *		SE NAO
 *			Nada acontece
 *
 ***********************************************************************/

	LISCIR_CondRet LISCIR_ProcurarValor ( LISCIR_tppListaCircular pLista , void * pValor ) ;

/***********************************************************************
 *
 *  $FC Fun��o: LISCIR  &Inserir elemento � esquerda
 *
 *  $ED Descri��o da fun��o
 *     Insere novo elemento antes do elemento corrente.
 *     Caso a lista esteja vazia, insere o primeiro elemento da lista.
 *
 *  $EP Par�metros
 *     pLista - ponteiro para a lista onde deve ser inserido o elemento
 *     * pValor - ponteiro para o valor do novo elemento
 *                Pode ser NULL
 *
 *  $FV Valor retornado
 *     LISCIR_CondRetOK				- se a inser��o ocorreu perfeitamente.
 *     LISCIR_CondRetMemoriaCheia		- se n�o possui mem�ria suficiente para inserir
 *	   LISCIR_CondRetListaNaoExiste	- se lista nao existe
 *
 *  $EAE Assertivas de entrada
 *		pLista deve ser uma lista existente (pLista != NULL)
 *		Deve existir memoria para inserir o novo elemento
 *
 *  $EAE Assertivas de sa�da
 *		SE LISCIR_CondRetOK
 *			O elemento � inserido antes do elemento corrente
 *			Caso a lista esteja vazia, o elemento inserido � o primeiro da lista
 *			Elemento inserido se torna o novo corrente
 *		SE NAO
 *			Nada acontece
 *
 ***********************************************************************/

	LISCIR_CondRet LISCIR_InserirElementoAntes ( LISCIR_tppListaCircular pLista , void * pValor  ) ;

/***********************************************************************
 *
 *  $FC Fun��o: LISCIR  &Inserir elemento � direita
 *
 *  $ED Descri��o da fun��o
 *     Insere novo elemento ap�s o elemento corrente.
 *     Caso a lista esteja vazia, insere o primeiro elemento da lista.
 *
 *  $EP Par�metros
 *     pLista - ponteiro para a lista onde deve ser inserido o elemento
 *     * pValor - ponteiro para o valor do novo elemento
 *                Pode ser NULL
 *
 *  $FV Valor retornado
 *     LISCIR_CondRetOK           - se a inser��o ocorreu perfeitmente.
 *     LISCIR_CondRetMemoriaCheia - se n�o possui mem�ria suficiente para inserir
 *	   LISCIR_CondRetListaNaoExiste - se lista nao existe
 *
 *  $EAE Assertivas de entrada
 *		pLista deve ser uma lista existente (pLista != NULL)
 *		Deve existir memoria para inserir o novo elemento
 *
 *  $EAE Assertivas de sa�da
 *		SE LISCIR_CondRetOK
 *			O elemento � inserido depois do elemento corrente
 *			Caso a lista esteja vazia, o elemento inserido � o primeiro da lista
 *			Elemento inserido se torna o novo corrente
 *		SE NAO
 *			Nada acontece
 *
 ***********************************************************************/

	LISCIR_CondRet LISCIR_InserirElementoApos ( LISCIR_tppListaCircular pLista , void * pValor ) ;

/***********************************************************************
 *
 *  $FC Fun��o: LISCIR  &Obter valor
 *
 *  $ED Descri��o da fun��o
 *     Obtem o valor contido no elemento corrente da lista.
 *
 *  $EP Par�metros
 *     pLista   - ponteiro para a lista de onde se quer o valor
 *     * ppValor - ponteiro para armazenar o valor desejado
 *
 *  $FV Valor retornado
 *     LISCIR_CondRetOK				- se o elemento corrente existe
 *     LISCIR_CondRetListaVazia		- se a lista estiver vazia
 *	   LISCIR_CondRetListaNaoExiste	- se lista nao existe
 *
 *  $EAE Assertivas de entrada
 *		pLista deve ser uma lista existente (pLista != NULL)
 *
 *  $EAE Assertivas de sa�da
 *		SE LISCIR_CondRetOK
 *			O valor do elemento corrente da lista � armazenado no
 *			par�metro valor
 *		SE NAO
 *			O parametro valor � inalterado
 *
 ***********************************************************************/

	LISCIR_CondRet LISCIR_ObterValor ( LISCIR_tppListaCircular pLista , void ** ppValor ) ;

/***********************************************************************
 *
 *  $FC Fun��o: LIS  &Avan�ar elemento
 *
 *  $ED Descri��o da fun��o
 *     Avan�a o elemento corrente 'num' elementos na lista.
 *     Se 'num' for positivo avan�a em dire��o ao final.
 *     Se 'num' for negativo avan�a em dire��o ao in�cio.
 *     Se 'num' for zero n�o avan�a nenhuma elemento.
 *
 *  $EP Par�metros
 *     pLista  - ponteiro para a lista a ser manipulada
 *     num    - o n�mero de elementos a andar
 *
 *  $FV Valor retornado
 *     LISCIR_CondRetOK				- se 'num' elementos tiverem sido andados
 *     LISCIR_CondRetListaVazia		- se a lista est� vazia
 *	   LISCIR_CondRetListaNaoExiste	- se lista nao existe
 *
 *  $EAE Assertivas de entrada
 *		pLista deve ser uma lista existente (pLista != NULL)
 *
 *  $EAE Assertivas de sa�da
 *		SE LISCIR_CondRetOK
 *			Novo elemento corrente � o elemento corrente antigo mais o
 *			deslocamento de "num" elementos
 *		SE NAO
 *			Nada acontece
 *
 ***********************************************************************/

	LISCIR_CondRet LISCIR_AvancarElementoCorrente ( LISCIR_tppListaCircular pLista , int num ) ;

#undef LISCIR_EXT

/****** Fim do m�dulo de defini��o: LISCIR M�dulo Lista Circular ******/

#else
#endif
