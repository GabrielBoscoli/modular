/***************************************************************************
*  $MCI Módulo de implementação: TLISCIR Teste lista circular
*
*  Arquivo gerado:              TESTLISCIR.C
*  Letras identificadoras:      TLISCIR
*
*  Projeto: Disciplina INF 1301
*  Gestor:  DI/PUC-RIO, Professor Alessandro Garcia
*  Autores: gb - Gabriel Boscoli
*
*  $HA Histórico de evolução:
*     Versão      Autor       Data        Observações
*	   3.00		   gb      26/06/2019   ajustes e modificações leves
*      2.00        gb      22/04/2019   finalização desenvolvimento
*      1.00        gb      21/04/2019   início desenvolvimento
*
*  $ED Descrição do módulo
*     Este modulo contém as funções específicas para o teste do
*     módulo lista circular. Ilustra como redigir um interpretador de comandos
*     de teste específicos utilizando o arcabouço de teste para C.
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <stdlib.h>

#include    "GENERICO.H"
#include    "LERPARM.H"
#include    "TST_ESPC.H"

#include    "LISCIR.H"

typedef void ** ppVoid ;

typedef void ( *pFunc ) ( void * ) ;

#define DIM_VALORES 4

/* Tabela dos nomes dos comandos de teste específicos */
            
#define INICIALIZAR_CONTEXTO_CMD		"=inicializarcontexto"
#define CRIAR_LISTAC_CMD				"=criarlistac"
#define EXCLUIR_ELEMENTO_CMD            "=excluirelemento"          
#define DESTRUIR_LISTA_CMD              "=destruirlista"           
#define ESVAZIAR_LISTA_CMD              "=esvaziarlista"           
#define PROCURAR_ELEMENTO_CMD           "=procurarelemento"          
#define INSERIR_ELEMENTO_ANTES_CMD      "=inserirelementoantes"      
#define INSERIR_ELEMENTO_APOS_CMD       "=inserirelementoapos"      
#define OBTER_VALOR_CMD                 "=obtervalor"              
#define AVANCAR_ELEMENTO_CORRENTE_CMD   "=avancarelementocorrente" 

/***** Protótipos das funções encapuladas no módulo *****/

   void DestruirValor( char * pValor ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***********************************************************************
*
*  $FC Função: TLISCIR Testar lista circular
*
*  $ED Descrição da função
*     Efetua os diversos comandos de teste específicos para o módulo
*     lista circular sendo testado.
*
*  $EP Parâmetros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     Ver TST_tpCondRet definido em TST_ESPC.H
*     
*     Comandos disponíveis:
*       
*     =criarlistac                       CondRetEsp
*     =removerelemento                   Valor CondRetEsp
*     =destruirlista                     CondRetEsp
*	  =esvaziarlista                     CondRetEsp
*     =buscarelemento                    Valor CondRetEsp
*     =inserirelementoesq                Valor CondRetEsp
*     =inserirelementodir                Valor CondRetEsp
*	  =obtervalor		                 CondRetEsp
*	  =avancarelementocorrente		   	 Numero CondRetEsp
*	  =inicializarcontexto
*
***********************************************************************/

	TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
	{

		int numLidos      = -1 ;
		int CondRetEsp    = -1 ;
		int CondRetObtido = -1 ;
		int num           = -1 ;
		int i;

		int indiceValores = -1;
		int* auxiliar;

		static LISCIR_tppListaCircular listaCircular = NULL;

		static char* valores[ DIM_VALORES ];

	/* Tratar: inicializar contexto */

		if( strcmp( ComandoTeste , INICIALIZAR_CONTEXTO_CMD ) == 0 )
		{
			numLidos = LER_LerParametros( "", &CondRetEsp) ;
			if ( numLidos != 0 )
			{
				return TST_CondRetParm;
			}

			for ( i = 0; i < DIM_VALORES; i++ )
			{
				valores[i] = ( char * ) malloc ( DIM_VALORES * sizeof ( char ) );
			}

			return TST_CondRetOK;

		} /* fim ativa: Tratar: inicializar contexto */
		
	/* Testar Criar Lista Circular */

         if ( strcmp( ComandoTeste , CRIAR_LISTAC_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" , &CondRetEsp ) ;

            if ( numLidos != 1  )
            {
               return TST_CondRetParm ;
            }
            
            CondRetObtido = LISCIR_CriarLista( &listaCircular, ( pFunc ) DestruirValor ) ;
			
            return TST_CompararInt( CondRetEsp , CondRetObtido ,
                     "Condicao de retorno errada ao Criar Lista Circular." ) ;

         } /* fim ativa: Testar Criar Lista Circular */
            
	/* Testar Remover Elemento */

         else if ( strcmp( ComandoTeste , EXCLUIR_ELEMENTO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" , &indiceValores, &CondRetEsp ) ;

            if (  numLidos != 2 )
            {
               return TST_CondRetParm ;
            }    

            CondRetObtido = LISCIR_ExcluirElemento( listaCircular, valores[indiceValores] ) ;
			
            return TST_CompararInt( CondRetEsp , CondRetObtido ,
                     "Condicao de retorno errada ao Remover Elemento." ) ;

         } /* fim ativa: Testar Remover Elemento */

           
	/* Testar Destruir Lista */

         else if ( strcmp( ComandoTeste , DESTRUIR_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i", &CondRetEsp ) ;

            if ( numLidos != 1 )
            {
               return TST_CondRetParm ;
            }

            CondRetObtido = LISCIR_DestruirLista( listaCircular ) ;
			listaCircular = NULL ;
			
            return TST_CompararInt( CondRetEsp , CondRetObtido ,
                     "Condicao de retorno errada ao Destruir Lista." ) ;

         } /* fim ativa: Testar Destruir Lista */

            
	/* Testar Esvaziar Lista */ 		
        
        else if ( strcmp( ComandoTeste , ESVAZIAR_LISTA_CMD ) == 0 )
        {
        
			numLidos = LER_LerParametros( "i" , &CondRetEsp ) ;
        
			if ( numLidos != 1 )
			{
				return TST_CondRetParm ;
			}
        
			CondRetObtido = LISCIR_EsvaziarLista( listaCircular ) ;
        			
			return TST_CompararInt( CondRetEsp , CondRetObtido ,
                    "Condicao de retorno errada ao Esvaziar Lista." ) ;
        
        } /* fim ativa: Testar Esvaziar Lista */    

                    
	/* Testar Buscar Elemento */	
    
        else if ( strcmp( ComandoTeste , PROCURAR_ELEMENTO_CMD ) == 0 )
        {
    
			numLidos = LER_LerParametros( "ii" , &indiceValores, &CondRetEsp ) ;
    
			if ( numLidos != 2 )
			{
				return TST_CondRetParm ;
			}

			CondRetObtido = LISCIR_ProcurarValor( listaCircular, valores[indiceValores] ) ;
    			
			return TST_CompararInt( CondRetEsp , CondRetObtido ,
                    "Condicao de retorno errada ao Buscar Elemento." ) ;
    
        } /* fim ativa: Testar Buscar Elemento */  

                
	/* Testar Inserir Elemento a Esquerda */
  
           else if ( strcmp( ComandoTeste , INSERIR_ELEMENTO_ANTES_CMD ) == 0 )
           {
  
              numLidos = LER_LerParametros( "ii" , &indiceValores, &CondRetEsp ) ;
  
              if ( numLidos != 2 )
              {
                 return TST_CondRetParm ;
              }

              CondRetObtido = LISCIR_InserirElementoAntes( listaCircular, (void *) valores[indiceValores] ) ;

              return TST_CompararInt( CondRetEsp , CondRetObtido ,
                       "Condicao de retorno errada ao Inserir Elemento a Esquerda." ) ;
  
           } /* fim ativa: Testar Inserir Elemento a Esquerda */  

              
	/* Testar Inserir Elemento a Direita */

         else if ( strcmp( ComandoTeste , INSERIR_ELEMENTO_APOS_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii", &indiceValores, &CondRetEsp ) ;

            if ( numLidos != 2 )
            {
               return TST_CondRetParm ;
            }

            CondRetObtido = LISCIR_InserirElementoApos( listaCircular, (void *) valores[indiceValores] ) ;

            return TST_CompararInt( CondRetEsp , CondRetObtido ,
                     "Condicao de retorno errada ao Inserir Elemento a Direita." ) ;

         } /* fim ativa: Testar Inserir Elemento a Direita */

           
	/* Testar Obter Valor */

         else if ( strcmp( ComandoTeste , OBTER_VALOR_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i", &CondRetEsp ) ;

            if ( numLidos != 1 )
            {
               return TST_CondRetParm ;
            }

            CondRetObtido = LISCIR_ObterValor( listaCircular, (ppVoid) &auxiliar ) ;
			
            return TST_CompararInt( CondRetEsp , CondRetObtido ,
                     "Condicao de retorno errada ao Obter Valor." ) ;

         } /* fim ativa: Testar Obter Valor */

	/* Testar Avançar Elemento Corrente */

         else if ( strcmp( ComandoTeste , AVANCAR_ELEMENTO_CORRENTE_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" , &num, &CondRetEsp ) ;

            if (  numLidos != 2 )
            {
               return TST_CondRetParm ;
            }

            CondRetObtido = LISCIR_AvancarElementoCorrente( listaCircular, num ) ;
			
            return TST_CompararInt( CondRetEsp , CondRetObtido ,
                     "Condicao de retorno errada ao Avançar Elemento Corrente." ) ;

         } /* fim ativa: Testar Avançar Elemento Corrente */
            
      return TST_CondRetNaoConhec ;

	} /* Fim função: TLISCIR &Testar lista circular */

/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: TLIS -Destruir valor
*
*  $ED Descrição da função
*		Destroi o elemento e libera a memoria alocada
*
***********************************************************************/

   void DestruirValor( char * pValor )
   {

      free( pValor ) ;

	  return;

   } /* Fim função: TLIS -Destruir valor */
 
/********** Fim do módulo de implementação: TLISCIR Teste lista circular **********/