/***************************************************************************
 *  $MCI Módulo de implementação: LISCIR Lista Duplamente Encadeada Circular
 *
 *  Arquivo gerado:              LISCIR.C
 *  Letras identificadoras:      LISCIR
 *
 *  Projeto: Disciplina INF 1301
 *  Gestor:  DI/PUC-RIO, Professor Alessandro Garcia
 *  Autores: gb - Gabriel Boscoli
 *
 *  $HA Histórico de evolução:
 *    Versão   Autor        Data         Observações
 *	   3.00	    gb       21/06/2019    instrumentação
 *     2.00     gb       20/04/2019    término, revisão e aperfeiçoamento
 *	   1.00     gb       19/04/2019    inicio desenvolvimento, implementação
 *									   funções básicas
 *
 *  $ED Descrição do módulo
 *     Este módulo contém a implementação das funções definidas em LISCIR.H.
 *
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#ifdef _DEBUG
	#include "CONTA.H"
#endif

#define LISCIR_OWN
#include "LISCIR.H"
#undef LISCIR_OWN


/***********************************************************************
 *
 *  $TC Tipo de dados: LISCIR Elemento da lista
 *
 *  $ED Descrição do tipo
 *     Descreve a organização e estrutura de um elemento da lista.
 *
 ***********************************************************************/

	typedef struct tagElemLista {
    
		void * valor ;
		/* Ponteiro para o valor contido no elemento */
    
		struct tagElemLista * ant ;
		/* Ponteiro para o elemento predecessor */
    
		struct tagElemLista * prox ;
		/* Ponteiro para o elemento sucessor */
    
	} tpElemLista ;

/***********************************************************************
 *
 *  $TC Tipo de dados: LISCIR Descritor da cabeça da lista
 *
 *  $ED Descrição do tipo
 *     Descreve a organização e estrutura da lista.
 *	   A cabeça da lista é o ponto de acesso para determinada lista.
 *
 ***********************************************************************/

	typedef struct LISCIR_tagListaCircular {
    
		tpElemLista * pElemCorr ;
		  /* Ponteiro para o elemento corrente */
    
		int numElem ;
 		  /* Numero de elementos da lista */
    
		void ( * ExcluirValor ) ( void * pValor ) ;
		  /* Ponteiro para a função de destruição do valor contido em um elemento */

	} LISCIR_tpListaCircular ;

/***** Protótipo das funções encapsuladas no módulo *****/

	static void LiberarElemento ( LISCIR_tpListaCircular *pLista , tpElemLista  * pElem ) ;

	static tpElemLista * CriaElemento ( LISCIR_tpListaCircular * pLista , void * valor ) ;

	static void LimparCabeca ( LISCIR_tpListaCircular *pLista ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
 *
 *  Função: LISCIR  &Criar lista
 *  ****/

	LISCIR_CondRet LISCIR_CriarLista ( LISCIR_tpListaCircular **pLista, void ( * ExcluirValor ) ( void *pValor ) )
	{
		#ifdef _DEBUG
			CNT_CONTAR( "LISCIR_CriaLista" ) ;
		#endif

		*pLista = ( LISCIR_tpListaCircular *) malloc ( sizeof ( LISCIR_tpListaCircular ) ) ;
    
		if ( *pLista == NULL )
		{
			#ifdef _DEBUG
				CNT_CONTAR( "LISCIR_CriaLista_if_erroMalloc" ) ;
			#endif

			return LISCIR_CondRetMemoriaCheia ;
		}

		#ifdef _DEBUG
			CNT_CONTAR( "LISCIR_CriaLista_pos_if" ) ;
		#endif
    
		LimparCabeca ( *pLista ) ;
		(*pLista)->ExcluirValor = ExcluirValor ;

		#ifdef _DEBUG
			CNT_CONTAR( "LISCIR_CriaLista_pre_return" ) ;
		#endif

		return 	LISCIR_CondRetOK ;
    
	} /* Fim função: LISCIR  &Criar lista */

/***************************************************************************
 *
 *  Função: LISCIR  &Excluir Elemento
 *  ****/

	LISCIR_CondRet LISCIR_ExcluirElemento ( LISCIR_tpListaCircular *pLista, void * pElemento )
	{
		tpElemLista * pElem    ;
		LISCIR_CondRet retorno ;

		#ifdef _DEBUG
			CNT_CONTAR( "LISCIR_ExcluirElemento" ) ;
		#endif

		if(pLista == NULL)
		{
			#ifdef _DEBUG
				CNT_CONTAR( "LISCIR_ExcluirElemento_if_listaNaoExiste" ) ;
			#endif

			return LISCIR_CondRetListaNaoExiste;
		}

		#ifdef _DEBUG
			CNT_CONTAR( "LISCIR_ExcluirElemento_pos_if_listaNaoExiste" ) ;
		#endif

		if ( ( retorno = LISCIR_ProcurarValor ( pLista , pElemento ) ) != LISCIR_CondRetOK )
		{
			#ifdef _DEBUG
				CNT_CONTAR( "LISCIR_ExcluirElemento_if_erroProcurarValor" ) ;
			#endif

			return retorno ;
		}

		#ifdef _DEBUG
			CNT_CONTAR( "LISCIR_ExcluirElemento_pos_if_erroProcurarValor" ) ;
		#endif

		pElem = pLista->pElemCorr ;
    
		if ( pElem->ant != pElem )
		{
			#ifdef _DEBUG
				CNT_CONTAR( "LISCIR_ExcluirElemento_if_elementoNaoUnicoNaLista" ) ;
			#endif

			pElem->ant->prox = pElem->prox ;
			pElem->prox->ant = pElem->ant  ;
			pLista->pElemCorr   = pElem->ant  ;
		}
		else
		{
			#ifdef _DEBUG
				CNT_CONTAR( "LISCIR_ExcluirElemento_else_elementoUnicoNaLista" ) ;
			#endif

			pLista->pElemCorr = NULL ;
		}

		#ifdef _DEBUG
			CNT_CONTAR( "LISCIR_ExcluirElemento_pos_else" ) ;
		#endif

		LiberarElemento( pLista , pElem ) ;

		#ifdef _DEBUG
			CNT_CONTAR( "LISCIR_ExcluirElemento_pre_return" ) ;
		#endif

		return LISCIR_CondRetOK ;
    
	} /* Fim função: LISCIR  &Excluir Elemento */

/***************************************************************************
 *
 *  Função: LISCIR  &Destruir lista
 *  ****/

	LISCIR_CondRet LISCIR_DestruirLista ( LISCIR_tpListaCircular *pLista )
	{
		#ifdef _DEBUG
			CNT_CONTAR( "LISCIR_DestruirLista" ) ;
		#endif

		if(pLista == NULL)
		{
			#ifdef _DEBUG
				CNT_CONTAR( "LISCIR_DestruirLista_if" ) ;
			#endif

			return LISCIR_CondRetListaNaoExiste;
		}

		#ifdef _DEBUG
			CNT_CONTAR( "LISCIR_DestruirLista_pos_if" ) ;
		#endif

		LISCIR_EsvaziarLista( pLista ) ;

		#ifdef _DEBUG
			CNT_CONTAR( "LISCIR_DestruirLista_pre_return" ) ;
		#endif

		return LISCIR_CondRetOK;
    
	} /* Fim função: LISCIR  &Destruir lista */

/***************************************************************************
 *
 *  Função: LISCIR  &Esvaziar lista
 *  ****/

	LISCIR_CondRet LISCIR_EsvaziarLista( LISCIR_tpListaCircular *pLista )
	{
    
		tpElemLista * pElem ;
		tpElemLista * pProx ;

		#ifdef _DEBUG
			CNT_CONTAR( "LISCIR_EsvaziarLista" ) ;
		#endif

		if(pLista == NULL)
		{
			#ifdef _DEBUG
				CNT_CONTAR( "LISCIR_EsvaziarLista_if_listaNaoExiste" ) ;
			#endif

			return LISCIR_CondRetListaNaoExiste;
		}

		#ifdef _DEBUG
			CNT_CONTAR( "LISCIR_EsvaziarLista_pos_if_listaNaoExiste" ) ;
		#endif

		if( pLista->pElemCorr == NULL )
		{
			#ifdef _DEBUG
				CNT_CONTAR( "LISCIR_EsvaziarLista_if_listaVazia" ) ;
			#endif

			return LISCIR_CondRetListaVazia ;
		}

		#ifdef _DEBUG
			CNT_CONTAR( "LISCIR_EsvaziarLista_pos_if_listaVazia" ) ;
		#endif
    
		pElem = pLista->pElemCorr ;
    
		do
		{
			#ifdef _DEBUG
				CNT_CONTAR( "LISCIR_EsvaziarLista_do_while" ) ;
			#endif

			pProx = pElem->prox ;
			LiberarElemento( pLista , pElem ) ;
			pElem = pProx ;
        
		} while ( pElem != pLista->pElemCorr ) ; /* arrasto = 1 */

		#ifdef _DEBUG
			CNT_CONTAR( "LISCIR_EsvaziarLista_pos_do_while" ) ;
		#endif
    
		LimparCabeca( pLista ) ;

		#ifdef _DEBUG
			CNT_CONTAR( "LISCIR_EsvaziarLista_pre_return" ) ;
		#endif

		return LISCIR_CondRetOK;
    
	} /* Fim função: LISCIR  &Esvaziar lista */

/***************************************************************************
 *
 *  Função: LISCIR  &Procurar elemento na lista
 *  ****/

	LISCIR_CondRet LISCIR_ProcurarValor ( LISCIR_tpListaCircular *pLista , void * pValor )
	{
		tpElemLista * pElem ;

		#ifdef _DEBUG
			CNT_CONTAR( "LISCIR_ProcurarValor" ) ;
		#endif

		if(pLista == NULL)
		{
			#ifdef _DEBUG
				CNT_CONTAR( "LISCIR_ProcurarValor_if_listaNaoExiste" ) ;
			#endif

			return LISCIR_CondRetListaNaoExiste;
		}

		#ifdef _DEBUG
			CNT_CONTAR( "LISCIR_ProcurarValor_pos_if_listaNaoExiste" ) ;
		#endif
    
		if ( pLista->pElemCorr == NULL )
		{
			#ifdef _DEBUG
				CNT_CONTAR( "LISCIR_ProcurarValor_if_listaVazia" ) ;
			#endif

			return LISCIR_CondRetListaVazia;
		}

		#ifdef _DEBUG
			CNT_CONTAR( "LISCIR_ProcurarValor_pos_if_listaVazia" ) ;
		#endif
    
		pElem = pLista->pElemCorr ;
    
		do
		{
			#ifdef _DEBUG
				CNT_CONTAR( "LISCIR_ProcurarValor_do_while" ) ;
			#endif

			if ( pElem->valor == pValor )
			{
				#ifdef _DEBUG
					CNT_CONTAR( "LISCIR_ProcurarValor_if_encontrouValor" ) ;
				#endif

				pLista->pElemCorr = pElem ;
				return LISCIR_CondRetOK ;
			}

			#ifdef _DEBUG
				CNT_CONTAR( "LISCIR_ProcurarValor_pos_if_encontrouValor" ) ;
			#endif

			pElem = pElem->prox ;
        
		} while ( pElem != pLista->pElemCorr ) ; /* arrasto = 1 ou 2? Acho que é 2. Lembrar que tem return! */

		#ifdef _DEBUG
			CNT_CONTAR( "LISCIR_ProcurarValor_pos_do_while" ) ;
		#endif

		return LISCIR_CondRetNaoAchou;
    
	} /* Fim função: LISCIR  &Procurar elemento na lista */

/***************************************************************************
 *
 *  Função: LISCIR  &Inserir elemento à esquerda
 *  ****/

	LISCIR_CondRet LISCIR_InserirElementoAntes ( LISCIR_tpListaCircular * pLista, void * pValor )
	{
		tpElemLista *pElem ;
		tpElemLista *p     ;

		#ifdef _DEBUG
			CNT_CONTAR( "LISCIR_InserirElementoAntes" ) ;
		#endif

		if(pLista == NULL)
		{
			#ifdef _DEBUG
				CNT_CONTAR( "LISCIR_InserirElementoAntes_if_listaNaoExiste" ) ;
			#endif

			return LISCIR_CondRetListaNaoExiste;
		}

		#ifdef _DEBUG
			CNT_CONTAR( "LISCIR_InserirElementoAntes_pos_if_listaNaoExiste" ) ;
		#endif

		pElem = CriaElemento( pLista ,  pValor ) ;
    
		if ( pElem == NULL )
		{
			#ifdef _DEBUG
				CNT_CONTAR( "LISCIR_InserirElementoAntes_if_erroCriarElemento" ) ;
			#endif

			return LISCIR_CondRetMemoriaCheia ;
		}

		#ifdef _DEBUG
			CNT_CONTAR( "LISCIR_InserirElementoAntes_pos_if_erroCriarElemento" ) ;
		#endif

		p = pLista->pElemCorr ;

		if ( p == NULL )
		{
			#ifdef _DEBUG
				CNT_CONTAR( "LISCIR_InserirElementoAntes_if_listaVazia" ) ;
			#endif

			pElem->ant = pElem->prox = pElem ;
		}
    
		else
		{
			#ifdef _DEBUG
				CNT_CONTAR( "LISCIR_InserirElementoAntes_else_listaNaoVazia" ) ;
			#endif

			p->ant->prox = pElem  ;
			pElem->ant   = p->ant ;
			pElem->prox  = p      ;
			p->ant       = pElem  ;
		}

		#ifdef _DEBUG
			CNT_CONTAR( "LISCIR_InserirElementoAntes_pos_else" ) ;
		#endif

		pLista->pElemCorr = pElem ;
		pLista->numElem++ ;

		#ifdef _DEBUG
			CNT_CONTAR( "LISCIR_InserirElementoAntes_pre_return" ) ;
		#endif

		return LISCIR_CondRetOK ;
    
	} /* Fim função: LISCIR  &Inserir elemento à esquerda */

/***************************************************************************
 *
 *  Função: LISCIR  &Inserir elemento à direita
 *  ****/

	LISCIR_CondRet LISCIR_InserirElementoApos ( LISCIR_tpListaCircular *pLista , void * pValor )
	{
		tpElemLista *pElem ;
		tpElemLista * p ;

		#ifdef _DEBUG
			CNT_CONTAR( "LISCIR_InserirElementoApos" ) ;
		#endif

		if(pLista == NULL)
		{
			#ifdef _DEBUG
				CNT_CONTAR( "LISCIR_InserirElementoApos_if_listaNaoExiste" ) ;
			#endif

			return LISCIR_CondRetListaNaoExiste;
		}

		#ifdef _DEBUG
			CNT_CONTAR( "LISCIR_InserirElementoApos_pos_if_listaNaoExiste" ) ;
		#endif

		pElem = CriaElemento ( pLista , pValor ) ;

		if ( pElem == NULL )
		{
			#ifdef _DEBUG
				CNT_CONTAR( "LISCIR_InserirElementoApos_if_erroCriarElemento" ) ;
			#endif

			return LISCIR_CondRetMemoriaCheia ;
		}

		#ifdef _DEBUG
			CNT_CONTAR( "LISCIR_InserirElementoApos_pos_if_erroCriarElemento" ) ;
		#endif
    
		p = pLista->pElemCorr ;

		if ( p == NULL )
		{
			#ifdef _DEBUG
				CNT_CONTAR( "LISCIR_InserirElementoApos_if_listaVazia" ) ;
			#endif

			pElem->ant = pElem->prox = pElem ;
		}
    
		else
		{
			#ifdef _DEBUG
				CNT_CONTAR( "LISCIR_InserirElementoApos_else_listaNaoVazia" ) ;
			#endif

			p->prox->ant = pElem   ;
			pElem->ant   = p       ;
			pElem->prox  = p->prox ;
			p->prox      = pElem   ;
		}

		#ifdef _DEBUG
			CNT_CONTAR( "LISCIR_InserirElementoApos_pos_else" ) ;
		#endif

		pLista->pElemCorr = pElem ;
		pLista->numElem++ ;

		#ifdef _DEBUG
			CNT_CONTAR( "LISCIR_InserirElementoApos_pre_return" ) ;
		#endif

		return LISCIR_CondRetOK ;
    
	} /* Fim função: LISCIR  &Inserir elemento à direita */

/***************************************************************************
 *
 *  Função: LISCIR  &Obter valor
 *  ****/

	LISCIR_CondRet LISCIR_ObterValor ( LISCIR_tpListaCircular *pLista , void ** ppValor )
	{
		#ifdef _DEBUG
			CNT_CONTAR( "LISCIR_ObterValor" ) ;
		#endif

		if(pLista == NULL)
		{
			#ifdef _DEBUG
				CNT_CONTAR( "LISCIR_ObterValor_if_listaNaoExiste" ) ;
			#endif

			return LISCIR_CondRetListaNaoExiste;
		}

		#ifdef _DEBUG
			CNT_CONTAR( "LISCIR_ObterValor_pos_if_listaNaoExiste" ) ;
		#endif

		if( pLista->pElemCorr == NULL )
		{
			#ifdef _DEBUG
				CNT_CONTAR( "LISCIR_ObterValor_if_listaVazia" ) ;
			#endif

			return LISCIR_CondRetListaVazia ;
		}

		#ifdef _DEBUG
			CNT_CONTAR( "LISCIR_ObterValor_pos_if_listaVazia" ) ;
		#endif

		*ppValor = pLista->pElemCorr->valor ;

		#ifdef _DEBUG
			CNT_CONTAR( "LISCIR_ObterValor_pre_return" ) ;
		#endif

		return LISCIR_CondRetOK ;
    
	}/* Fim função: LISCIR  &Obter valor */

/***************************************************************************
 *
 *  Função: LISCIR  &Avançar Elemento Corrente
 *  ****/

	LISCIR_CondRet LISCIR_AvancarElementoCorrente ( LISCIR_tpListaCircular *pLista , int num )
	{
		tpElemLista *pElem ;

		#ifdef _DEBUG
			CNT_CONTAR( "LISCIR_AvancarElementoCorrente" ) ;
		#endif

		if(pLista == NULL)
		{
			#ifdef _DEBUG
				CNT_CONTAR( "LISCIR_AvancarElementoCorrente_if_listaNaoExiste" ) ;
			#endif

			return LISCIR_CondRetListaNaoExiste;
		}

		#ifdef _DEBUG
			CNT_CONTAR( "LISCIR_AvancarElementoCorrente_pos_if_listaNaoExiste" ) ;
		#endif
    
		if( pLista->pElemCorr == NULL )
		{
			#ifdef _DEBUG
				CNT_CONTAR( "LISCIR_AvancarElementoCorrente_if_listaVazia" ) ;
			#endif

			return LISCIR_CondRetListaVazia ;
		}

		#ifdef _DEBUG
			CNT_CONTAR( "LISCIR_AvancarElementoCorrente_pos_if_listaVazia" ) ;
		#endif

		pElem = pLista->pElemCorr ;

		if ( num > 0 )
		{
			#ifdef _DEBUG
				CNT_CONTAR( "LISCIR_AvancarElementoCorrente_if_avancoMaiorQueZero" ) ;
			#endif

			while( num )
			{
				#ifdef _DEBUG
					CNT_CONTAR( "LISCIR_AvancarElementoCorrente_while_avancoMaiorQueZero" ) ;
				#endif

				pElem = pElem->prox ;
				num-- ;
			} /* arrasto = 1 */

			/* botar contador aqui? */
		}
		else if ( num < 0 )
		{
			#ifdef _DEBUG
				CNT_CONTAR( "LISCIR_AvancarElementoCorrente_else_if_avancoMenorQueZero" ) ;
			#endif

			while( num )
			{
				#ifdef _DEBUG
					CNT_CONTAR( "LISCIR_AvancarElementoCorrente_while_avancoMenorQueZero" ) ;
				#endif

				pElem = pElem->ant ;
				num++ ;
			} /* arrasto = 1 */

			/* botar contador aqui? */
		}

		#ifdef _DEBUG
			CNT_CONTAR( "LISCIR_AvancarElementoCorrente_pos_else_if" ) ;
		#endif

		pLista->pElemCorr = pElem ;

		#ifdef _DEBUG
			CNT_CONTAR( "LISCIR_AvancarElementoCorrente_pre_return" ) ;
		#endif

		return LISCIR_CondRetOK ;
    
	}/* Fim função: LISCIR  &Avançar Elemento Corrente */

/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
 *
 *  $FC Função: LISCIR  -Liberar elemento da lista
 *
 *  $ED Descrição da função
 *     Elimina os espaços apontados pelo valor do elemento e o
 *     próprio elemento.
 *
 *  $EP Parâmetros
 *	   pLista - ponteiro para a lista
 *	   pElem - ponteiro para o elemento da lista
 *
 *  $EAE Assertivas de entrada
 *	   pLista deve ser diferente de NULL
 *	   pElem deve ser diferente de NULL
 *
 *  $EAE Assertivas de saida
 *		Caso os valores de entrada esteja fora do padrao, o programa encerra
 *		Caso tudo ocorra corretamente,
 *			Se a lista possui uma funcao para excluir o valor do elemento,
 *				tal funcao é acionada e o espaco referente é desalocado
 *			Se a lista nao possui uma funcao para excluir o valor do elemento,
 *				o valor do elemento nao é desalocado
 *			O proprio elemento é desalocado e destruido
 *			A lista nao possui mais tal elemento
 *			Se o elemento era unico na lista, ela fica vazia
 *
 ***********************************************************************/

	void LiberarElemento ( LISCIR_tpListaCircular *pLista , tpElemLista  * pElem )
	{
		#ifdef _DEBUG
			CNT_CONTAR( "LiberarElemento" ) ;
		#endif

		if ( pLista == NULL )
		{
			#ifdef _DEBUG
				CNT_CONTAR( "LiberarElemento_erroListaNULL" ) ;
			#endif

			printf(" Erro! Lista nao existe");
			scanf("%s");
			exit(1);
		}

		#ifdef _DEBUG
			CNT_CONTAR( "LiberarElemento_pos_erroListaNULL" ) ;
		#endif

		if ( pElem == NULL )
		{
			#ifdef _DEBUG
				CNT_CONTAR( "LiberarElemento_erroElementoNULL" ) ;
			#endif

			printf(" Erro! Elemento nao existe");
			scanf("%s");
			exit(1);
		}

		#ifdef _DEBUG
			CNT_CONTAR( "LiberarElemento_pos_erroElementoNULL" ) ;
		#endif

		if ( ( pLista->ExcluirValor != NULL ) && ( pElem->valor != NULL )    )
		{
			#ifdef _DEBUG
				CNT_CONTAR( "LiberarElemento_if" ) ;
			#endif

			pLista->ExcluirValor( pElem->valor ) ;

		} /* if */

		#ifdef _DEBUG
			CNT_CONTAR( "LiberarElemento_pos_if" ) ;
		#endif

		pElem->valor = NULL ;
		pLista->numElem-- ;

		free(pElem);

		#ifdef _DEBUG
			CNT_CONTAR( "LiberarElemento_pre_return" ) ;
		#endif

		return;
    
	} /* Fim função: LISCIR  -Liberar elemento da lista */

/***********************************************************************
 *
 *  $FC Função: LISCIR  -Cria elemento da lista
 *
 *  $ED Descrição da função
 *     Cria elemento da lista e inicializa os valores contidos nele.
 *
 *  $EP Parâmetros
 *		pLista - ponteiro para lista
 *		valor - referencia para o valor que sera inserido na lista
 *
 *  $FV Valor retornado
 *		tpElemLista * - ponteiro para elemento da lista
 *		NULL - caso tenha ocorrido erro na alocacao de memoria
 *
 *  $EAE Assertivas de entrada
 *		pLista deve ser diferente de NULL
 *
 *  $EAE Assertivas de saida
 *		Caso pLista == NULL, o programa encerra
 *		Caso ocorra erro no malloc, 
 *			Retorna NULL
 *			O elemento nao é criado
 *		Caso tudo ocorra corretamente,
 *			O elemento é criado
 *			O elemento contém o valor passado
 *			O elemento nao possui outros elementos no seu lado
 *			Retorna o ponteiro para tal elemento
 *
 ***********************************************************************/

	tpElemLista * CriaElemento ( LISCIR_tpListaCircular * pLista , void * valor )
	{
		tpElemLista * pElem ;

		#ifdef _DEBUG
			CNT_CONTAR( "CriaElemento" ) ;
		#endif

		if ( pLista == NULL )
		{
			#ifdef _DEBUG
				CNT_CONTAR( "CriaElemento_erroListaNULL" ) ;
			#endif

			printf(" Erro! Lista nao existe");
			scanf("%s");
			exit(1);
		}

		#ifdef _DEBUG
			CNT_CONTAR( "CriaElemento_pos_erroListaNULL" ) ;
		#endif
    
		pElem = ( tpElemLista * ) malloc ( sizeof ( tpElemLista ) ) ;
		if ( pElem == NULL )
		{
			#ifdef _DEBUG
				CNT_CONTAR( "CriaElemento_erroMalloc" ) ;
			#endif

			return NULL ;
		}

		#ifdef _DEBUG
			CNT_CONTAR( "CriaElemento_pos_erroMalloc" ) ;
		#endif
    
		pLista = NULL ;

		pElem->valor = valor ;
		pElem->prox  = NULL  ;
		pElem->ant   = NULL  ;

		#ifdef _DEBUG
			CNT_CONTAR( "CriaElemento_pre_return" ) ;
		#endif
    
		return pElem ;
    
	} /* Fim função: LISCIR  -Cria elemento da lista */

/***********************************************************************
 *
 *  $FC Função: LISCIR  -Limpar a cabeça da lista
 *
 *  $ED Descrição da função
 *		Zera a cabeca da lista, como se fosse uma lista recem criada
 *
 *  $EP Parâmetros
 *		pLista - ponteiro para a lista
 *
 *  $EAE Assertivas de entrada
 *		pLista deve ser diferente de NULL
 *
 *  $EAE Assertivas de saida
 *		Caso pLista == NULL, o programa encerra
 *		Caso tudo ocorra corretamente,
 *			O elemento corrente da lista passa a ser NULL
 *			A lista passa a ter 0
 *			Se a lista possuisse elementos antes, eles nao sao desalocados,
 *			podendo gerar memory leak
 *
 ***********************************************************************/

	void LimparCabeca ( LISCIR_tpListaCircular *pLista )
	{
		#ifdef _DEBUG
			CNT_CONTAR( "LimparCabeca" ) ;
		#endif

		if ( pLista == NULL )
		{
			#ifdef _DEBUG
				CNT_CONTAR( "LimparCabeca_erro" ) ;
			#endif

			printf(" Erro! Lista nao existe");
			scanf("%s");
			exit(1);
		}

		#ifdef _DEBUG
			CNT_CONTAR( "LimparCabeca_pos_erro" ) ;
		#endif

		pLista->pElemCorr = NULL ;
		pLista->numElem  = 0    ;

		#ifdef _DEBUG
			CNT_CONTAR( "LimparCabeca_pre_return" ) ;
		#endif

		return;
    
	} /* Fim função: LISCIR  -Limpar a cabeça da lista */

/********** Fim do módulo de implementação: LISCIR  Lista Duplamente Encadeada Circular **********/