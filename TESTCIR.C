/***************************************************************************
*  $MCI Módulo de implementação: TLST Teste lista circular
*
*  Arquivo gerado:              TESTCIR.C
*  Letras identificadoras:      TLST
*
*  Projeto: Disciplina INF 1301
*  Gestor:  DI/PUC-RIO, Professor Alessandro Garcia
*  Autores: gb - Gabriel Boscoli
*
*  $HA Histórico de evolução:
*     Versão      Autor       Data        Observações
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

#include    "LCIRC.H"

/* Tabela dos nomes dos comandos de teste específicos */
            
#define CRIAR_LISTAC_CMD                  "=criarlistac"             
#define REMOVE_ELEMENTO_CMD               "=removerelemento"          
#define DESTRUIR_LISTA_CMD                "=destruirlista"           
#define ESVAZIAR_LISTA_CMD                "=esvaziarlista"           
#define BUSCAR_ELEMENTO_CMD               "=buscarelemento"          
#define INSERIR_ELEMENTO_ESQ_CMD          "=inserirelementoesq"      
#define INSERIR_ELEMENTO_DIR_CMD          "=inserirelementodir"      
#define OBTER_VALOR_CMD                   "=obtervalor"              
#define AVANCAR_ELEMENTO_CORRENTE_CMD     "=avancarelementocorrente" 

typedef void ** ppVoid ;

/***** Protótipos das funções encapuladas no módulo *****/

   static void DestruirValor( void * pValor ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***********************************************************************
*
*  $FC Função: TLST Efetuar operações de teste específicas para lista circular
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
*
***********************************************************************/

/***********************************************************************/

	TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
	{

		int numLidos      = -1 ;
		int CondRetEsp    = -1 ;
		int CondRetObtido = -1 ;
		int num           = -1 ;

		int indiceValores = -1;
		int* auxiliar;

		static int valores[3] = {1, 2, 3};

		static LST_Circular listaCircular = NULL;
		
	/* Testar Criar Lista Circular */

         if ( strcmp( ComandoTeste , CRIAR_LISTAC_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" , &CondRetEsp ) ;

            if ( numLidos != 1  )
            {
               return TST_CondRetParm ;
            }
            
            CondRetObtido = LST_CriaLista( &listaCircular, NULL ) ;
			
            return TST_CompararInt( CondRetEsp , CondRetObtido ,
                     "Condicao de retorno errada ao Criar Lista Circular." ) ;

         } /* fim ativa: Testar Criar Lista Circular */
            

	/* Testar Remover Elemento */

         else if ( strcmp( ComandoTeste , REMOVE_ELEMENTO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" , &indiceValores, &CondRetEsp ) ;

            if (  numLidos != 2 )
            {
               return TST_CondRetParm ;
            }    

            CondRetObtido = LST_RemoveElemento( listaCircular, &valores[indiceValores] ) ;
			
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

            CondRetObtido = LST_DestruirLista( listaCircular ) ;
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
        
			CondRetObtido = LST_EsvaziarLista( listaCircular ) ;
        			
			return TST_CompararInt( CondRetEsp , CondRetObtido ,
                    "Condicao de retorno errada ao Esvaziar Lista." ) ;
        
        } /* fim ativa: Testar Esvaziar Lista */    

                    
	/* Testar Buscar Elemento */	
    
        else if ( strcmp( ComandoTeste , BUSCAR_ELEMENTO_CMD ) == 0 )
        {
    
			numLidos = LER_LerParametros( "ii" , &indiceValores, &CondRetEsp ) ;
    
			if ( numLidos != 2 )
			{
				return TST_CondRetParm ;
			}

			CondRetObtido = LST_BuscaElemento( listaCircular, &valores[indiceValores] ) ;
    			
			return TST_CompararInt( CondRetEsp , CondRetObtido ,
                    "Condicao de retorno errada ao Buscar Elemento." ) ;
    
        } /* fim ativa: Testar Buscar Elemento */  

                
	/* Testar Inserir Elemento a Esquerda */
  
           else if ( strcmp( ComandoTeste , INSERIR_ELEMENTO_ESQ_CMD ) == 0 )
           {
  
              numLidos = LER_LerParametros( "ii" , &indiceValores, &CondRetEsp ) ;
  
              if ( numLidos != 2 )
              {
                 return TST_CondRetParm ;
              }

              CondRetObtido = LST_InsereElemEsquerda( listaCircular, (void *) &valores[indiceValores] ) ;

              return TST_CompararInt( CondRetEsp , CondRetObtido ,
                       "Condicao de retorno errada ao Inserir Elemento a Esquerda." ) ;
  
           } /* fim ativa: Testar Inserir Elemento a Esquerda */  

              
	/* Testar Inserir Elemento a Direita */

         else if ( strcmp( ComandoTeste , INSERIR_ELEMENTO_DIR_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii", &indiceValores, &CondRetEsp ) ;

            if ( numLidos != 2 )
            {
               return TST_CondRetParm ;
            }

            CondRetObtido = LST_InsereElemDireita( listaCircular, (void *) &valores[indiceValores] ) ;

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

            CondRetObtido = LST_ObterValor( listaCircular, (ppVoid) &auxiliar ) ;
			
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

            CondRetObtido = LST_AvancarElementoCorrente( listaCircular, num ) ;
			
            return TST_CompararInt( CondRetEsp , CondRetObtido ,
                     "Condicao de retorno errada ao Avançar Elemento Corrente." ) ;

         } /* fim ativa: Testar Avançar Elemento Corrente */
            
      return TST_CondRetNaoConhec ;

	} /* Fim função: TLST &Testar lista circular */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: TLST - Destruir valor
*
***********************************************************************/

   void DestruirValor( void * pValor )
   {
		int* auxiliar = (int*) pValor;
		free( auxiliar ) ;

   } /* Fim função: TLST -Destruir valor */
 
/********** Fim do módulo de implementação: TLST Teste lista circular **********/