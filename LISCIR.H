#if ! defined( LISCIR_ )
#define LISCIR_
/***************************************************************************
 *
 *  $MCD Módulo de definição: LISCIR Lista Duplamente Encadeada Circular
 *
 *  Arquivo gerado:              LISCIR.H
 *  Letras identificadoras:      LISCIR
 *
 *  Projeto: Disciplina INF 1301
 *  Gestor:  DI/ PUC-RIO, Professor Alessandro Garcia
 *  Autores: gb - Gabriel Boscoli
 *
 *  $HA Histórico de evolução:
 *     Versão   Autor        Data         Observações
 *      2.00     gb      20/04/2019   término desenvolvimento
 *      1.00     gb      19/04/2019   início desenvolvimento
 *
 *  $ED Descrição do módulo
 *     Implementa listas circulares genéricas duplamente encadeadas.
 *	   Podem existir n listas em operação simultaneamente.
 *     As listas possuem uma cabeça encapsulando o seu estado.
 *
 *     Cada lista é homogênea quanto ao tipo dos dados que armazena.
 *     Cada elemento da lista referencia o valor que contém.
 *
 *     Os ponteiros para os dados são copiados para elementos da lista.
 *        Não é copiado o valor apontado por estes ponteiros.
 *
 *     O controle da destruição do valor de um elemento a ser excluído
 *        é realizado por uma função fornecida pelo usuário.
 *
 *     Cada lista referencia uma função que determina como devem ser
 *        desalocados os dados nela contidos.
 *
 *     A função de liberação dos valores contidos nos elementos deve
 *        assegurar a liberação de todos os espaços referênciados pelo
 *        valor contido em um elemento.
 *        Esta função é chamada antes de se desalocar um elemento
 *        de uma lista.
 *        Caso não seja necessário desalocar o valor referenciado pelo
 *        elemento, o ponteiro para a função de liberação poderá ser NULL .
 *        Caso o elemento da lista seja a única âncora do valor referenciado,
 *        esta função deve promover a destruição (free) desse valor e
 *        de todos os dados nele ancorados.
 *
 ***************************************************************************/

#if defined( LISCIR_OWN )
   #define LISCIR_EXT
#else
   #define LISCIR_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma lista */

	typedef struct LISCIR_tagListaCircular * LISCIR_tppListaCircular ;

/***********************************************************************
 *
 *  $TC Tipo de dados: LISCIR Condições de retorno
 *
 *
 *  $ED Descrição do tipo
 *     Condições de retorno das funções da lista duplamente encadeada
 *           circular.
 *
 ***********************************************************************/

	typedef enum {
    
		LISCIR_CondRetOK ,
			/* Concluiu corretamente */
    
		LISCIR_CondRetNaoAchou ,
			/* Não encontrou o valor procurado */
    
		LISCIR_CondRetMemoriaCheia ,
			/* Faltou memoria para alocar elemento */
    
		LISCIR_CondRetListaVazia ,
			/* A lista não contem elementos */

		LISCIR_CondRetListaNaoExiste
			/* A lista não existe */
    
	} LISCIR_CondRet ;

/***********************************************************************
 *
 *  $FC Função: LISCIR  &Criar lista
 *
 *  $ED Descrição da função
 *     Cria uma lista duplamente encadeada circular genérica.
 *     Os possíveis tipos são desconhecidos a priori.
 *
 *  $EP Parâmetros
 *     * pLista		- ponteiro para a lista a ser criada.
 *     ExcluirValor	- ponteiro para a função que processa a exclusão
 *					  do valor referenciado pelo elemento a ser
 *					  excluído.
 *
 *  $FV Valor retornado
 *     LISCIR_CondRetOK			- se ocorreu tudo certo
 *	   LISCIR_CondRetMemoriaCheia	- se faltou memoria
 *
 *  $EAE Assertivas de entrada
 *		Deve existir memória para a criação da lista
 *
 *  $EAE Assertivas de saída
 *		SE LISCIR_CondRetOK
 *			A lista é criada e referenciada por pLista
 *		SE NAO
 *			A lista não é criada
 *			pLista = NULL
 *
 ***********************************************************************/

	LISCIR_CondRet LISCIR_CriarLista ( LISCIR_tppListaCircular * pLista,
                           void ( * ExcluirValor ) ( void *pValor ) );

/***********************************************************************
 *
 *  $FC Função: LISCIR  &Excluir elemento
 *
 *  $ED Descrição da função
 *     Remove o elemento procurado da lista dada.
 *     Se existir somente um elemento a lista tornou-se vazia.
 *
 *  $EP Parâmetros
 *     pLista		- ponteiro para a lista.
 *     pElemento		- ponteiro para elemento que se deseja retirar da lista.
 *
 *  $FV Valor retornado
 *     LISCIR_CondRetOK				- se removeu corretamente
 *     LISCIR_CondRetNaoAchou			- se elemento não foi encontrado
 *     LISCIR_CondRetListaVazia        - se não há elemento na lista
 *	   LISCIR_CondRetListaNaoExiste	- se lista nao existe
 *
 *  $EAE Assertivas de entrada
 *		pLista deve ser uma lista existente (pLista != NULL)
 *		O elemento procurado deve existir
 *		O elemento procurado deve estar na lista
 *
 *  $EAE Assertivas de saída
 *		SE LISCIR_CondRetOK
 *			O elemento é removido
 *			O elemento corrente é o elemento anterior ao que foi removido
 *			Caso nao exista elemento anterior, a lista fica vazia
 *		SE NAO
 *			O elemento nao é removido
 *			Lista continua da mesma forma
 *
 ***********************************************************************/

	LISCIR_CondRet LISCIR_ExcluirElemento ( LISCIR_tppListaCircular pLista, void * pElemento  ) ;

/***********************************************************************
 *
 *  $FC Função: LISCIR  &Destruir Lista
 *
 *  $ED Descrição da função
 *     Destrói a lista fornecida.
 *
 *  $EP Parâmetros
 *     pLista     - ponteiro para a lista na qual deve ser destruida.
 *
 *  $FV Valor retornado
 *     LISCIR_CondRetOK				- destruiu lista sem problemas.
 *	   LISCIR_CondRetListaNaoExiste	- se lista nao existe
 *
 *  $EAE Assertivas de entrada
 *		pLista deve ser uma lista existente (pLista != NULL)
 *
 *  $EAE Assertivas de saída
 *		SE LISCIR_CondRetOK
 *			A lista é destruida
 *			A memoria alocada é liberada
 *		SE LISCIR_CondRetListaNaoExiste
 *			Nada acontece
 *
 ***********************************************************************/

	LISCIR_CondRet LISCIR_DestruirLista ( LISCIR_tppListaCircular pLista ) ;

/***********************************************************************
 *
 *  $FC Função: LISCIR  &Esvaziar lista
 *
 *  $ED Descrição da função
 *     Elimina todos os elementos, sem eliminar a lista
 *
 *  $EP Parâmetros
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
 *  $EAE Assertivas de saída
 *		SE LISCIR_CondRetOK
 *			Todos os elementos da lista são removidos
 *			A memoria alocada para os elementos deve ser liberada
 *			A lista fica vazia
 *		SE NAO
 *			Nada acontece
 *
 ***********************************************************************/

	LISCIR_CondRet LISCIR_EsvaziarLista ( LISCIR_tppListaCircular pLista ) ;

/***********************************************************************
 *
 *  $FC Função: LISCIR  &Procurar elemento na lista
 *
 *  $ED Descrição da função
 *     Procura o elemento desejado e o deixa na posição corrente.
 *
 *  $EP Parâmetros
 *     pLista		- ponteiro para a lista onde procura
 *     * pValor		- ponteiro pra o endereço do elemento desejado
 *
 *  $FV Valor retornado
 *     LISCIR_CondRetOK				- se encontrou o elemento.
 *     LISCIR_CondRetNaoAchou			- se o elemento não foi encontrado.
 *     LISCIR_CondRetListaVazia        - se a lista está vazia
 *	   LISCIR_CondRetListaNaoExiste	- se lista nao existe
 *
 *  $EAE Assertivas de entrada
 *		pLista deve ser uma lista existente  (pLista != NULL)
 *		valor deve ser um ponteiro que esta armazenado na lista
 *
 *  $EAE Assertivas de saída
 *		SE LISCIR_CondRetOK
 *			O elemento corrente é o elemento com o valor procurado
 *		SE NAO
 *			Nada acontece
 *
 ***********************************************************************/

	LISCIR_CondRet LISCIR_ProcurarValor ( LISCIR_tppListaCircular pLista , void * pValor ) ;

/***********************************************************************
 *
 *  $FC Função: LISCIR  &Inserir elemento à esquerda
 *
 *  $ED Descrição da função
 *     Insere novo elemento antes do elemento corrente.
 *     Caso a lista esteja vazia, insere o primeiro elemento da lista.
 *
 *  $EP Parâmetros
 *     pLista - ponteiro para a lista onde deve ser inserido o elemento
 *     * pValor - ponteiro para o valor do novo elemento
 *                Pode ser NULL
 *
 *  $FV Valor retornado
 *     LISCIR_CondRetOK				- se a inserção ocorreu perfeitamente.
 *     LISCIR_CondRetMemoriaCheia		- se não possui memória suficiente para inserir
 *	   LISCIR_CondRetListaNaoExiste	- se lista nao existe
 *
 *  $EAE Assertivas de entrada
 *		pLista deve ser uma lista existente (pLista != NULL)
 *		Deve existir memoria para inserir o novo elemento
 *
 *  $EAE Assertivas de saída
 *		SE LISCIR_CondRetOK
 *			O elemento é inserido antes do elemento corrente
 *			Caso a lista esteja vazia, o elemento inserido é o primeiro da lista
 *			Elemento inserido se torna o novo corrente
 *		SE NAO
 *			Nada acontece
 *
 ***********************************************************************/

	LISCIR_CondRet LISCIR_InserirElementoAntes ( LISCIR_tppListaCircular pLista , void * pValor  ) ;

/***********************************************************************
 *
 *  $FC Função: LISCIR  &Inserir elemento à direita
 *
 *  $ED Descrição da função
 *     Insere novo elemento após o elemento corrente.
 *     Caso a lista esteja vazia, insere o primeiro elemento da lista.
 *
 *  $EP Parâmetros
 *     pLista - ponteiro para a lista onde deve ser inserido o elemento
 *     * pValor - ponteiro para o valor do novo elemento
 *                Pode ser NULL
 *
 *  $FV Valor retornado
 *     LISCIR_CondRetOK           - se a inserção ocorreu perfeitmente.
 *     LISCIR_CondRetMemoriaCheia - se não possui memória suficiente para inserir
 *	   LISCIR_CondRetListaNaoExiste - se lista nao existe
 *
 *  $EAE Assertivas de entrada
 *		pLista deve ser uma lista existente (pLista != NULL)
 *		Deve existir memoria para inserir o novo elemento
 *
 *  $EAE Assertivas de saída
 *		SE LISCIR_CondRetOK
 *			O elemento é inserido depois do elemento corrente
 *			Caso a lista esteja vazia, o elemento inserido é o primeiro da lista
 *			Elemento inserido se torna o novo corrente
 *		SE NAO
 *			Nada acontece
 *
 ***********************************************************************/

	LISCIR_CondRet LISCIR_InserirElementoApos ( LISCIR_tppListaCircular pLista , void * pValor ) ;

/***********************************************************************
 *
 *  $FC Função: LISCIR  &Obter valor
 *
 *  $ED Descrição da função
 *     Obtem o valor contido no elemento corrente da lista.
 *
 *  $EP Parâmetros
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
 *  $EAE Assertivas de saída
 *		SE LISCIR_CondRetOK
 *			O valor do elemento corrente da lista é armazenado no
 *			parâmetro valor
 *		SE NAO
 *			O parametro valor é inalterado
 *
 ***********************************************************************/

	LISCIR_CondRet LISCIR_ObterValor ( LISCIR_tppListaCircular pLista , void ** ppValor ) ;

/***********************************************************************
 *
 *  $FC Função: LIS  &Avançar elemento
 *
 *  $ED Descrição da função
 *     Avança o elemento corrente 'num' elementos na lista.
 *     Se 'num' for positivo avança em direção ao final.
 *     Se 'num' for negativo avança em direção ao início.
 *     Se 'num' for zero não avança nenhuma elemento.
 *
 *  $EP Parâmetros
 *     pLista  - ponteiro para a lista a ser manipulada
 *     num    - o número de elementos a andar
 *
 *  $FV Valor retornado
 *     LISCIR_CondRetOK				- se 'num' elementos tiverem sido andados
 *     LISCIR_CondRetListaVazia		- se a lista está vazia
 *	   LISCIR_CondRetListaNaoExiste	- se lista nao existe
 *
 *  $EAE Assertivas de entrada
 *		pLista deve ser uma lista existente (pLista != NULL)
 *
 *  $EAE Assertivas de saída
 *		SE LISCIR_CondRetOK
 *			Novo elemento corrente é o elemento corrente antigo mais o
 *			deslocamento de "num" elementos
 *		SE NAO
 *			Nada acontece
 *
 ***********************************************************************/

	LISCIR_CondRet LISCIR_AvancarElementoCorrente ( LISCIR_tppListaCircular pLista , int num ) ;

#undef LISCIR_EXT

/****** Fim do módulo de definição: LISCIR Módulo Lista Circular ******/

#else
#endif
