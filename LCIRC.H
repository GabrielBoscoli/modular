#if ! defined( LCIRC_ )
#define LCIRC_
/***************************************************************************
 *
 *  $MCD Módulo de definição: LST Lista Duplamente Encadeada Circular
 *
 *  Arquivo gerado:              LCIRC.h
 *  Letras identificadoras:      LST
 *
 *  Projeto: INF 1301 / Jogo de Ludo (ou Furbica)
 *  Gestor:  Professor Alessandro Garcia
 *  Autores: lr, dcr, rvc
 *
 *  $HA Histórico de evolução:
 *     Versão |  Autor  |      Data     |    Observações
 *       2    |   lr    |  25/set/2016  | término desenvolvimento
 *       1    |   lr    |  16/set/2016  | início desenvolvimento
 *
 *  $ED Descrição do módulo
 *     Este módulo implementa listas duplamente encadeadas circulares
 *          genéricas.
 *     As listas possuem um apontador para o nó corrente da lista, para
 *          o proximo elemento à esquerda e à direita do corrente.
 *
 *     Cada lista é homogênea quanto ao tipo dos dados que armazena.
 *     Os ponteiros para os dados são copiados para elementos da lista.
 *     Não é copiado o valor apontado por estes ponteiros.
 *
 *     A destruição do valor de um elemento a ser excluído é realizado
 *        por uma função fornecida pelo usuário.
 *
 ***************************************************************************/

#if defined( LCIRC_OWN )
   #define LCIRC_EXT
#else
   #define LCIRC_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma lista */

typedef struct LST_tpCircular * LST_Circular ;

/***********************************************************************
 *
 *  $TC Tipo de dados: LST Condições de retorno
 *
 *
 *  $ED Descrição do tipo
 *     Condições de retorno das funções da lista duplamente encadeada
 *           circular.
 *
 ***********************************************************************/

typedef enum {
    
    LST_CondRetOK ,
    /* Concluiu corretamente */
    
    LST_CondRetNaoEncontrou ,
    /* Não encontrou o valor procurado */
    
    LST_CondRetMemoriaCheia ,
    /* Faltou memoria para alocar elemento */
    
    LST_CondRetVazia ,
    /* Não existe elementos na lista */

    LST_CondRetErroEstrutura
    /* A estrutura possui erros */
    
} LST_CondRet ;

/***********************************************************************
 *
 *  $FC Função: LST  &Criar lista
 *
 *  $ED Descrição da função
 *     Cria uma lista duplamente encadeada circular genérica.
 *     Os possíveis tipos são desconhecidos a priori.
 *
 *  $FV Valor retornado
 *     Se executou corretamente retorna o ponteiro para lista, neste
 *       momento ainda sem nenhum elemento (lista vazia).
 *     Este ponteiro será utilizado pelas funções que manipulem esta
 *        lista, atualizando o ponteiro do nó corrente, anterior e
 *        sucessor em cada inserção ou remoção.
 *
 *     Se ocorreu algum erro, por exemplo falta de memória ou dados
 *        errados, a função retornará LST_CondRetMemoriaCheia,
 *        apresentando uma mensagem de erro.
 *
 ***********************************************************************/

LST_CondRet LST_CriaLista ( LST_Circular * pLista,
                           void ( * ExcluirValor ) ( void *pValor ) );

/***********************************************************************
 *
 *  $FC Função: LST  &Remover elemento
 *
 *  $ED Descrição da função
 *     Remove o elemento procurado da lista dada.
 *     Se existir somente um elemento a lista tornou-se vazia.
 *
 *  $EP Parâmetros
 *     pLista     - ponteiro para a lista.
 *   elemento - ponteiro para elemento que se deseja retirar da lista.
 *
 *  $FV Valor retornado
 *     LST_CondRetOK            - se removeu corretamente
 *     LST_CondRetNaoEncontrou  - se elemento não foi encontrado
 *     LST_CondRetVazia         - se não há elemento na lista
 *
 ***********************************************************************/

LST_CondRet LST_RemoveElemento ( LST_Circular pLista, void * elemento  ) ;

/***********************************************************************
 *
 *  $FC Função: LST  &Destruir Lista
 *
 *  $ED Descrição da função
 *     Destrói a lista fornecida.
 *
 *  $EP Parâmetros
 *     pLista     - ponteiro para a lista na qual deve ser destruida.
 *
 *  $FV Valor retornado
 *     LST_CondRetOK      - destruiu lista sem problemas.
 *
 ***********************************************************************/

LST_CondRet LST_DestruirLista ( LST_Circular pLista ) ;

/***********************************************************************
 *
 *  $FC Função: LST  &Esvaziar lista
 *
 *  $ED Descrição da função
 *     Elimina todos os elementos, sem contudo eliminar a lista
 *
 *  $EP Parâmetros
 *     pLista - ponteiro para a lista a ser esvaziada
 *
 *  $FV Valor retornado
 *     LST_CondRetOK      - esvaziou lista sem problemas.
 *
 ***********************************************************************/

LST_CondRet LST_EsvaziarLista ( LST_Circular pLista ) ;

/***********************************************************************
 *
 *  $FC Função: LST  &Procurar elemento na lista
 *
 *  $ED Descrição da função
 *     Procura o elemento desejado e o deixa na posição corrente.
 *
 *  $EP Parâmetros
 *     pLista     - ponteiro para a lista onde procura
 *     *valor   - ponteiro pra o endereço do elemento desejado
 *
 *  $FV Valor retornado
 *     LST_CondRetOK              - se encontrou o elemento.
 *     LST_CondRetNaoEncontrou    - se o elemento não foi encontrado.
 *     LST_CondRetVazia           - se a lista está vazia
 *
 ***********************************************************************/

LST_CondRet LST_BuscaElemento ( LST_Circular pLista , void * valor ) ;

/***********************************************************************
 *
 *  $FC Função: LST  &Inserir elemento à esquerda
 *
 *  $ED Descrição da função
 *     Insere novo elemento antes do elemento corrente.
 *     Caso a lista esteja vazia, insere o primeiro elemento da lista.
 *
 *  $EP Parâmetros
 *     pLista - ponteiro para a lista onde deve ser inserido o elemento
 *     *valor - ponteiro para o valor do novo elemento
 *              Pode ser NULL
 *
 *  $FV Valor retornado
 *     LST_CondRetOK           - se a inserção ocorreu perfeitmente.
 *   LST_CondRetMemoriaCheia - se não possui memória suficiente para
 *                                  inserir
 *
 ***********************************************************************/

LST_CondRet LST_InsereElemEsquerda ( LST_Circular pLista , void * valor  ) ;

/***********************************************************************
 *
 *  $FC Função: LST  &Inserir elemento à direita
 *
 *  $ED Descrição da função
 *     Insere novo elemento após o elemento corrente.
 *     Caso a lista esteja vazia, insere o primeiro elemento da lista.
 *
 *  $EP Parâmetros
 *     pLista - ponteiro para a lista onde deve ser inserido o elemento
 *     *valor - ponteiro para o valor do novo elemento
 *              Pode ser NULL
 *
 *  $FV Valor retornado
 *     LST_CondRetOK           - se a inserção ocorreu perfeitmente.
 *   LST_CondRetMemoriaCheia - se não possui memória suficiente para
 *                                  inserir
 *
 ***********************************************************************/

LST_CondRet LST_InsereElemDireita ( LST_Circular pLista , void * valor ) ;

/***********************************************************************
 *
 *  $FC Função: LST  &Obter valor
 *
 *  $ED Descrição da função
 *     Obtem o valor contido no elemento corrente da lista.
 *
 *  $EP Parâmetros
 *     pLista   - ponteiro para a lista de onde se quer o valor
 *     * valor - ponteiro para armazenar o valor desejado
 *
 *  $FV Valor retornado
 *     LST_CondRetOK    - se o elemento corrente existe
 *     LST_CondRetVazia - se a lista estiver vazia
 *
 ***********************************************************************/

LST_CondRet LST_ObterValor ( LST_Circular pLista , void ** valor ) ;

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
 *     LST_CondRetOK      - se 'num' elementos tiverem sido andados
 *     LST_CondRetVazia   - se a lista está vazia
 *
 ***********************************************************************/

LST_CondRet LST_AvancarElementoCorrente ( LST_Circular pLista , int num ) ;

#undef LCIRC_EXT

/****** Fim do módulo de definição: LCIRC Módulo Lista Circular ******/

#else
#endif
