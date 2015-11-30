/***************************************************************************
*  $MCI M�dulo de implementa��o: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.c
*  Letras identificadoras:      LIS
*
*  Projeto: INF 1301
*  Autores: gbo - Gabriel Barbosa de Oliveira
*           gapm - Guilherme de Azevedo Pereira Marques
*           tdn - Thiago Duarte Naves
*           pa - Pedro Alvarez
*
*  $HA Hist�rico de evolu��o:
*     Vers�o        Autor              Data           Observa��es
*     3.00          gbo, gapm, tdn, pa 28/11/2015     Lista autoverific�vel.
*     2.00          gbo, gapm, tdn, pa 20/09/2015     Lista de ponteiros de void.
*     1.00          gbo, gapm, tdn     28/08/2015     In�cio do desenvolvimento.
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>
#include   "lista.h"

#ifdef _DEBUG
  #include  "conta.h"
  #include  "cespdin.h"
#endif

/***********************************************************************
*
*  $TC Tipo de dados: LIS Elemento da lista
*
*
***********************************************************************/

   typedef struct tagElemLista {

      #ifdef _DEBUG

      struct LIS_tagLista * pCabeca ;
            /* Ponteiro para a cabe�a */

      LIS_tpTipo pTipo ;
            /*Tipo do elemento*/

      int tamElem ;
            /*Tamanho em bytes do elemento*/

      int tamValor ;
            /*Tamanho em bytes do valor apontado pelo elemento*/

      #endif

      void * pValor ;
            /* valor contido no elemento */

      struct tagElemLista * pAnt ;
            /* Ponteiro para o elemento predecessor */

      struct tagElemLista * pProx ;
            /* Ponteiro para o elemento sucessor */

   } tpElemLista ;

/***********************************************************************
*
*  $TC Tipo de dados: LIS Descritor da cabe�a de lista
*
*
***********************************************************************/

   typedef struct LIS_tagLista {

         void (* pExcluir)( void * pValor) ;
               /* Ponteiro para a fun��o usada para
                * desalocar um elemento */

         tpElemLista * pOrigemLista ;
               /* Ponteiro para a origem da lista */

         tpElemLista * pFimLista ;
               /* Ponteiro para o final da lista */

         tpElemLista * pElemCorr ;
               /* Ponteiro para o elemento corrente da lista */

         int numElem ;
               /* N�mero de elementos da lista */

   } LIS_tpLista ;

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

   static void LiberarElemento( LIS_tppLista   lista ,
                                tpElemLista  * pElem   ) ;

   static tpElemLista * CriarElemento( LIS_tppLista lista , void * pValor
                                       #ifdef _DEBUG
                                       , LIS_tpTipo tipo
                                       #endif
                                     ) ;

   static void LimparCabeca( LIS_tppLista lista ) ;

   #ifdef _DEBUG
   static int DefineTamValor( LIS_tpTipo tipo ) ;
   #endif

/*****  Dados encapsulados no m�dulo  *****/

   #ifdef _DEBUG

   static char espacoLixo[ 256 ] =
          "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" ;
         /* Espa�o de dados lixo usado ao testar */

   #endif


/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: LIS &Criar lista
*  ****/

   LIS_tpCondRet LIS_CriarLista( LIS_tppLista * pLista,
                                 void (* pExcluir)( void * pValor))
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      *pLista = ( LIS_tppLista ) malloc( sizeof( LIS_tpLista )) ;
      if ( *pLista == NULL )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "LIS_CriarLista_FaltouMemoria" ) ;
         #endif
         return LIS_CondRetFaltouMemoria ;
      } /* if */

      #ifdef _DEBUG
         CNT_CONTAR( "LIS_CriarLista" ) ;
      #endif

      LimparCabeca( *pLista ) ;
      (*pLista)->pExcluir = pExcluir ;

      return LIS_CondRetOK;

   } /* Fim fun��o: LIS &Criar lista */


/***************************************************************************
*
*  Fun��o: LIS &Definir Fun��o Excluir
*  ****/

   LIS_tpCondRet LIS_DefinirFuncaoExcluir( LIS_tppLista lista,
                                 void (* pExcluir)( void * pValor))
   {

      #ifdef _DEBUG
         assert( lista != NULL ) ;
         CNT_CONTAR( "LIS_DefinirFuncaoExcluir" ) ;
      #endif

      lista->pExcluir = pExcluir ;

      return LIS_CondRetOK;

   } /* Fim fun��o: LIS &Definir Fun��o Excluir */


/***************************************************************************
*
*  Fun��o: LIS &Destruir lista
*  ****/

   LIS_tpCondRet LIS_DestruirLista( LIS_tppLista lista )
   {

      #ifdef _DEBUG
         assert( lista != NULL ) ;
         CNT_CONTAR( "LIS_DestruirLista" ) ;
      #endif

      LIS_EsvaziarLista( lista ) ;

      free( lista ) ;

     return LIS_CondRetOK;

   } /* Fim fun��o: LIS &Destruir lista */


/***************************************************************************
*
*  Fun��o: LIS &Esvaziar lista
*  ****/

   LIS_tpCondRet LIS_EsvaziarLista( LIS_tppLista lista )
   {

      tpElemLista * pElem ;
      tpElemLista * pProx ;

      #ifdef _DEBUG
         assert( lista != NULL ) ;
         CNT_CONTAR( "LIS_EsvaziarLista" ) ;
      #endif

      pElem = lista->pOrigemLista ;
      while ( pElem != NULL )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "LIS_EsvaziarLista_while" ) ;
         #endif

         pProx = pElem->pProx ;
         LiberarElemento( lista , pElem ) ;
         pElem = pProx ;
      } /* while */

      LimparCabeca( lista ) ;

     return LIS_CondRetOK;

   } /* Fim fun��o: LIS &Esvaziar lista */


/***************************************************************************
*
*  Fun��o: LIS &Inserir elemento antes
*  ****/

   LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista lista , void * pValor
                                           #ifdef _DEBUG
                                           , LIS_tpTipo tipo
                                           #endif
                                         )
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( lista != NULL ) ;
      #endif

      /* Criar elemento a inerir antes */

      pElem = CriarElemento( lista , pValor
                             #ifdef _DEBUG
                             , tipo
                             #endif
                           ) ;
      if ( pElem == NULL )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "LIS_InserirElementoAntes_FaltouMemoria" ) ;
         #endif
         return LIS_CondRetFaltouMemoria ;
      } /* if */

      /* Encadear o elemento antes do elemento corrente */

      if ( lista->pElemCorr == NULL )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "LIS_InserirElementoAntes_CorrNULL" ) ;
         #endif
         lista->pOrigemLista = pElem ;
         lista->pFimLista = pElem ;
      } else
      {
         if ( lista->pElemCorr->pAnt != NULL )
         {
            #ifdef _DEBUG
               CNT_CONTAR( "LIS_InserirElementoAntes_Ant" ) ;
            #endif
            pElem->pAnt  = lista->pElemCorr->pAnt ;
            lista->pElemCorr->pAnt->pProx = pElem ;
         } else
         {
            #ifdef _DEBUG
               CNT_CONTAR( "LIS_InserirElementoAntes_AntNULL" ) ;
            #endif
            lista->pOrigemLista = pElem ;
         } /* if */

         pElem->pProx = lista->pElemCorr ;
         lista->pElemCorr->pAnt = pElem ;
      } /* if */

	  #ifdef _DEBUG
	     CED_DefinirTipoEspaco( pElem , tipo ) ;
      #endif

      lista->pElemCorr = pElem ;

      return LIS_CondRetOK ;

   } /* Fim fun��o: LIS &Inserir elemento antes */

/***************************************************************************
*
*  Fun��o: LIS &Inserir elemento ap�s
*  ****/

LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista lista, void * pValor
                                       #ifdef _DEBUG
                                       , LIS_tpTipo tipo
                                       #endif
                                     )
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( lista != NULL ) ;
      #endif

      /* Criar elemento a inerir ap�s */

      pElem = CriarElemento( lista , pValor
                             #ifdef _DEBUG
                             , tipo
                             #endif
                           ) ;
      if ( pElem == NULL )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "LIS_InserirElementoApos_FaltouMemoria" ) ;
         #endif
         return LIS_CondRetFaltouMemoria ;
      } /* if */

      /* Encadear o elemento ap�s o elemento */

      if ( lista->pElemCorr == NULL )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "LIS_InserirElementoApos_CorrNULL" ) ;
         #endif
         lista->pOrigemLista = pElem ;
         lista->pFimLista = pElem ;
      } else
      {
         if ( lista->pElemCorr->pProx != NULL )
         {
            #ifdef _DEBUG
               CNT_CONTAR( "LIS_InserirElementoApos_Prox" ) ;
            #endif
            pElem->pProx  = lista->pElemCorr->pProx ;
            lista->pElemCorr->pProx->pAnt = pElem ;
         } else
         {
            #ifdef _DEBUG
               CNT_CONTAR( "LIS_InserirElementoApos_ProxNULL" ) ;
            #endif
            lista->pFimLista = pElem ;
         } /* if */

         pElem->pAnt = lista->pElemCorr ;
         lista->pElemCorr->pProx = pElem ;

      } /* if */

      lista->pElemCorr = pElem ;

      return LIS_CondRetOK ;

   } /* Fim fun��o: LIS &Inserir elemento ap�s */

/***************************************************************************
*
*  Fun��o: LIS &Excluir elemento
*  ****/

   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista lista )
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( lista  != NULL ) ;
      #endif

      if ( lista->pElemCorr == NULL )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "LIS_ExcluirElemento_Vazia" ) ;
         #endif
         return LIS_CondRetListaVazia ;
      } /* if */

      pElem = lista->pElemCorr ;

      /* Desencadeia � esquerda */

      if ( pElem->pAnt != NULL )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "LIS_ExcluirElemento_Ant" ) ;
         #endif
         pElem->pAnt->pProx   = pElem->pProx ;
         lista->pElemCorr     = pElem->pAnt ;
      } else
      {
         #ifdef _DEBUG
            CNT_CONTAR( "LIS_ExcluirElemento_AntNULL" ) ;
         #endif
         lista->pElemCorr     = pElem->pProx ;
         lista->pOrigemLista  = lista->pElemCorr ;
      } /* if */

      /* Desencadeia � direita */

      if ( pElem->pProx != NULL )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "LIS_ExcluirElemento_Prox" ) ;
         #endif
         pElem->pProx->pAnt = pElem->pAnt ;
      } else
      {
         #ifdef _DEBUG
            CNT_CONTAR( "LIS_ExcluirElemento_ProxNULL" ) ;
         #endif
         lista->pFimLista = pElem->pAnt ;
      } /* if */

      LiberarElemento( lista , pElem ) ;

      return LIS_CondRetOK ;

   } /* Fim fun��o: LIS &Excluir elemento */

/***************************************************************************
*
*  Fun��o: LIS &Obter refer�ncia para o valor contido no elemento
*  ****/

   LIS_tpCondRet LIS_ObterValor(LIS_tppLista lista, void ** pValor)
   {

      #ifdef _DEBUG
         assert( lista != NULL ) ;
         assert( pValor != NULL ) ;
      #endif

      if ( lista->pElemCorr == NULL )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "LIS_ObterValor_NaoAchou" ) ;
         #endif
         return LIS_CondRetNaoAchou;
      } /* if */

      #ifdef _DEBUG
         CNT_CONTAR( "LIS_ObterValor_Achou" ) ;
      #endif
      *pValor = lista->pElemCorr->pValor;

      return LIS_CondRetOK;

   } /* Fim fun��o: LIS &Obter refer�ncia para o valor contido no elemento */

/***************************************************************************
*
*  Fun��o: LIS &Ir para o elemento inicial
*  ****/

   LIS_tpCondRet LIS_IrInicioLista( LIS_tppLista lista )
   {

      #ifdef _DEBUG
         assert( lista != NULL ) ;
         CNT_CONTAR( "LIS_IrInicioLista" ) ;
      #endif

      lista->pElemCorr = lista->pOrigemLista ;

      return LIS_CondRetOK;

   } /* Fim fun��o: LIS &Ir para o elemento inicial */

/***************************************************************************
*
*  Fun��o: LIS &Ir para o elemento final
*  ****/

   LIS_tpCondRet LIS_IrFinalLista( LIS_tppLista lista )
   {

      #ifdef _DEBUG
         assert( lista != NULL ) ;
         CNT_CONTAR( "LIS_IrFinalLista" ) ;
      #endif

      lista->pElemCorr = lista->pFimLista ;

      return LIS_CondRetOK;

   } /* Fim fun��o: LIS &Ir para o elemento final */

/***************************************************************************
*
*  Fun��o: LIS  &Avan�ar elemento
*  ****/

   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista  lista ,
                                              int numElem )
   {

      int i ;
      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( lista != NULL ) ;
      #endif

      /* Tratar lista vazia */
      if ( lista->pElemCorr == NULL )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "LIS_AvancarElementoCorrente_Vazia" ) ;
         #endif

         return LIS_CondRetListaVazia ;
      } /* fim ativa: Tratar lista vazia */

      /* Tratar avan�ar para frente */
      if ( numElem > 0 )
      {
         pElem = lista->pElemCorr ;
         for( i = numElem ; i > 0 ; i-- )
         {
            if ( pElem == NULL )
            {
               #ifdef _DEBUG
                  CNT_CONTAR( "LIS_AvancarElementoCorrente_FrenteForElemNull" ) ;
               #endif
               break ;
            } else
            {
               #ifdef _DEBUG
                  CNT_CONTAR( "LIS_AvancarElementoCorrente_FrenteForElem" ) ;
               #endif
            } /* if */

            pElem = pElem->pProx ;
         } /* for */

         if ( pElem != NULL )
         {
            #ifdef _DEBUG
               CNT_CONTAR( "LIS_AvancarElementoCorrente_FrenteElem" ) ;
            #endif
            lista->pElemCorr = pElem ;
            return LIS_CondRetOK ;
         } /* if */

         #ifdef _DEBUG
            CNT_CONTAR( "LIS_AvancarElementoCorrente_Frente" ) ;
         #endif

         lista->pElemCorr = lista->pFimLista ;
         return LIS_CondRetFimLista ;

      } /* fim ativa: Tratar avan�ar para frente */

      /* Tratar avan�ar para tr�s */
      else if ( numElem < 0 )
      {
         pElem = lista->pElemCorr ;
         for( i = numElem ; i < 0 ; i++ )
         {
            if ( pElem == NULL )
            {
               #ifdef _DEBUG
                  CNT_CONTAR( "LIS_AvancarElementoCorrente_TrasForElemNULL" ) ;
               #endif
               break ;
            } else
            {
               #ifdef _DEBUG
                  CNT_CONTAR( "LIS_AvancarElementoCorrente_TrasForElem" ) ;
               #endif
            } /* if */
            pElem    = pElem->pAnt ;
         } /* for */

         if ( pElem != NULL )
         {
            #ifdef _DEBUG
               CNT_CONTAR( "LIS_AvancarElementoCorrente_TrasElem" ) ;
            #endif
            lista->pElemCorr = pElem ;
            return LIS_CondRetOK ;
         } /* if */

         #ifdef _DEBUG
            CNT_CONTAR( "LIS_AvancarElementoCorrente_Tras" ) ;
         #endif

         lista->pElemCorr = lista->pOrigemLista ;
         return LIS_CondRetFimLista ;
      } /* fim ativa: Tratar avan�ar para tr�s */

      /* Tratar n�o avan�ar */
      #ifdef _DEBUG
         CNT_CONTAR( "LIS_AvancarElementoCorrente_NaoAvancar" ) ;
      #endif
      return LIS_CondRetOK ;

   } /* Fim fun��o: LIS &Avan�ar elemento */

/***************************************************************************
*
*  Fun��o: LIS &Procurar elemento contendo valor
*  ****/

   LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista lista ,
                                    void * pValor        )
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( lista  != NULL ) ;
      #endif

      if ( lista->pElemCorr == NULL )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "LIS_ProcurarValor_Vazia" ) ;
         #endif
         return LIS_CondRetListaVazia ;
      } /* if */

      for ( pElem  = lista->pElemCorr ;
            pElem != NULL ;
            pElem  = pElem->pProx )
      {
         if ( pElem->pValor == pValor )
         {
            #ifdef _DEBUG
               CNT_CONTAR( "LIS_ProcurarValor_ForAchou" ) ;
            #endif
            lista->pElemCorr = pElem ;
            return LIS_CondRetOK ;
         } /* if */

         #ifdef _DEBUG
            CNT_CONTAR( "LIS_ProcurarValor_For" ) ;
         #endif
      } /* for */

      #ifdef _DEBUG
         CNT_CONTAR( "LIS_ProcurarValor" ) ;
      #endif
      return LIS_CondRetNaoAchou ;

   } /* Fim fun��o: LIS &Procurar elemento contendo valor */


/*****  C�digo das fun��es encapsuladas no m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: LIS Liberar elemento da lista
*
*  $ED Descri��o da fun��o
*     Elimina os espa�os apontados pelo valor do elemento e o
*     pr�prio elemento.
*
***********************************************************************/

 static void LiberarElemento( LIS_tppLista   lista ,
                              tpElemLista  * pElem   )
   {

      if ( lista->pExcluir )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "LiberarElemento_Excluir" ) ;
         #endif
         lista->pExcluir( pElem->pValor ) ;
      } else
      {
         #ifdef _DEBUG
            CNT_CONTAR( "LiberarElemento_ExcluirNULL" ) ;
         #endif
      } /* if */

      free( pElem ) ;

      lista->numElem-- ;

   } /* Fim fun��o: LIS Liberar elemento da lista */


/***********************************************************************
*
*  $FC Fun��o: LIS Criar o elemento
*
***********************************************************************/

   static tpElemLista * CriarElemento( LIS_tppLista lista , void * pValor
                                       #ifdef _DEBUG
                                       , LIS_tpTipo tipo
                                       #endif
                                     )
   {

      tpElemLista * pElem ;

      pElem = ( tpElemLista * ) malloc( sizeof( tpElemLista )) ;
      if ( pElem == NULL )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "CriarElemento_FaltouMemoria" ) ;
         #endif
         return NULL;
      } /* if */

      pElem->pValor = pValor ;
      pElem->pAnt   = NULL  ;
      pElem->pProx  = NULL  ;

     #ifdef _DEBUG

      CNT_CONTAR( "CriarElemento" ) ;

      pElem->pTipo = tipo ;
      pElem->pCabeca = lista ;
      pElem->tamElem = sizeof( tpElemLista ) ;
      pElem->tamValor = DefineTamValor( tipo ) ;

      #endif

      lista->numElem ++ ;

      return pElem;

   } /* Fim fun��o: LIS Criar o elemento */


/***********************************************************************
*
*  $FC Fun��o: LIS Limpar a cabe�a da lista
* ****/

   static void LimparCabeca( LIS_tppLista lista )
   {

      #ifdef _DEBUG
         CNT_CONTAR( "LimparCabeca" ) ;
      #endif

      lista->pOrigemLista = NULL ;
      lista->pFimLista = NULL ;
      lista->pElemCorr = NULL ;
      lista->numElem   = 0 ;
      lista->pExcluir = NULL ;

   } /* Fim fun��o: LIS Limpar a cabe�a da lista */

#ifdef _DEBUG

/***************************************************************************
*
*  $FC Fun��o: LIS &Verificar uma lista
* ****/

   LIS_tpCondRet LIS_VerificarLista( LIS_tppLista lista )
   {

      tpElemLista * pElem;

      if ( LIS_VerificarCabeca( lista ) != LIS_CondRetOK )
      {
         CNT_CONTAR( "LIS_VerificarLista_Cabeca" ) ;
         return LIS_CondRetErroEstrutura;
      } /* if */

      pElem = lista->pElemCorr;

      /* Assegura que cada par de elementos adjacentes em uma
         lista sejam adjacentes somente entre si */
      while ( pElem != NULL )
      {
         if ( pElem->pProx != NULL )
         {
            if ( pElem->pProx->pAnt != pElem->pValor)
            {
               CNT_CONTAR( "LIS_VerificarLista_ProxAnt" ) ;
               return LIS_CondRetErroEstrutura ;
            } /* if */

            CNT_CONTAR( "LIS_VerificarLista_Prox" ) ;
         } /* if */

         if ( pElem->pAnt != NULL )
         {
            if ( pElem->pAnt->pProx != pElem->pValor)
            {
               CNT_CONTAR( "LIS_VerificarLista_AntProx" ) ;
               return LIS_CondRetErroEstrutura ;
            } /* if */

            CNT_CONTAR( "LIS_VerificarLista_Ant" ) ;
         } /* if */

         CNT_CONTAR( "LIS_VerificarLista_While" ) ;
         pElem = pElem->pProx ;
      } /* while */

      CNT_CONTAR( "LIS_VerificarLista" ) ;
      return LIS_CondRetOK ;

   } /* Fim fun��o: LIS &Verificar uma lista */


/***************************************************************************
*
*  $FC Fun��o: LIS  &Verificar uma cabe�a de lista
* ****/

   LIS_tpCondRet LIS_VerificarCabeca( LIS_tppLista lista )
   {

      if ( lista->numElem == 0 &&
           lista->pElemCorr == NULL &&
           lista->pOrigemLista == NULL &&
           lista->pFimLista == NULL )
      {
         CNT_CONTAR( "LIS_VerificarCabeca_Vazia" ) ;
         return LIS_CondRetOK ;
      } /* if */

      if ( lista->numElem > 0 &&
           lista->pElemCorr != NULL )
      {
         CNT_CONTAR( "LIS_VerificarCabeca_NaoVazia" ) ;
         return LIS_CondRetOK ;
      } /* if */

      if ( lista->numElem == 1 &&
           lista->pElemCorr == lista->pOrigemLista &&
           lista->pOrigemLista == lista->pFimLista )
      {
         CNT_CONTAR( "LIS_VerificarCabeca_1Elem" ) ;
         return LIS_CondRetOK ;
      } /* if */

      CNT_CONTAR( "LIS_VerificarCabeca_Erro" ) ;
      return LIS_CondRetErroEstrutura ;

   } /* Fim fun��o: LIS &Verificar uma cabe�a de lista */


   /***************************************************************************
   *
   *  $FC Fun��o: LIS &Define o TamValor
   * ****/

   static int DefineTamValor( LIS_tpTipo tipo )
   {

      if ( tipo == LIS_tpInteiro )
      {
         CNT_CONTAR( "DefineTamValor_Int" ) ;
         return sizeof( int ) ;
      } /*if*/

      if ( tipo == LIS_tpChar )
      {
         CNT_CONTAR( "DefineTamValor_Char" ) ;
         return sizeof( char ) ;
      } /*if*/

      if ( tipo == LIS_tpFloat )
      {
         CNT_CONTAR( "DefineTamValor_Float" ) ;
         return sizeof( float ) ;
      } /*if*/

      if ( tipo == LIS_tpDouble )
      {
         CNT_CONTAR( "DefineTamValor_Double" ) ;
         return sizeof( double ) ;
      } /*if*/

      /* Tipo inv�lido. Nunca deveria chegar aqui */
      assert( 0 ) ;

   } /* Fim fun��o: LIS &Define Tamanho Valor */


/***************************************************************************
*
*  Fun��o: LIS  &Deturpar lista
*  ****/

   void LIS_Deturpar( LIS_tppLista lista , LIS_tpDeturpa modoDeturpar )
   {

      LIS_tpLista * pLista ;

      if ( lista == NULL )
      {
         return ;
      } /* if */

      pLista = ( LIS_tpLista * ) lista ;

      switch ( modoDeturpar )
      {

       /* Elimina o elemento corrente da lista */

        case LIS_DeturpaCorrElimina:
       {

          free( pLista->pElemCorr ) ;

          break ;

       } /* Fim ativa: Elimina elemento corrente */

       /* Faz o ponteiro pr�ximo apontar para NULL */

       case LIS_DeturpaPtrProxNulo:
       {

          pLista->pElemCorr->pProx = NULL ;

          break ;

       } /* Fim ativa: Faz o ponteiro pr�ximo apontar para NULL */

       /* Faz o ponteiro anterior apontar para NULL */

       case LIS_DeturpaPtrAntNulo:
       {

          pLista->pElemCorr->pAnt = NULL ;

          break ;

       } /* Fim ativa: Faz o ponteiro anterior apontar para NULL */


       /* Faz ponteiro pr�ximo apontar para lixo */

       case LIS_DeturpaPtrProxLixo:
       {

          pLista->pElemCorr->pProx = ( tpElemLista * )( espacoLixo ) ;

          break ;

       } /* Fim ativa: Faz ponteiro pr�ximo apontar para lixo */

       /* Faz ponteiro anterior apontar para lixo */

       case LIS_DeturpaPtrAntLixo:
       {

          pLista->pElemCorr->pAnt = ( tpElemLista * )( espacoLixo ) ;

          break ;

       } /* Fim ativa: Faz ponteiro anterior apontar para lixo */

       /* Atribui NULL ao ponteiro para o cont�do do n� */

       case LIS_DeturpaPtrValNulo:
       {

          pLista->pElemCorr->pValor = NULL ;

          break ;

       } /* Fim ativa: Atribui NULL ao ponteiro para o cont�do do n� */

       /* Altera o tipo de estrutura apontado pelo n� */

       case LIS_DeturpaTipo:
       {

          pLista->pElemCorr->pTipo = LIS_tpInvalido ;

          break ;

       } /* Fim ativa: Altera o tipo de estrutura apontado pelo n� */

       /* Desencadeia o n� sem liber�-lo */

       case LIS_DeturpaDesencadeiaNo:
       {

          pLista->pElemCorr->pAnt->pProx = NULL ;
          pLista->pElemCorr->pProx->pAnt = NULL ;

          break ;

       } /* Fim ativa: Desencadeia o n� sem liber�-lo */

       /* Anula ponteiro corrente */

         case LIS_DeturpaCorrNulo:
         {

            pLista->pElemCorr = NULL ;

            break ;

         } /* Fim ativa: Anula ponteiro corrente */

         /* Anula ponteiro origem */

         case LIS_DeturpaPtrOrigem:
         {

            pLista->pOrigemLista = NULL ;

            break ;

         } /* Fim ativa: Anula ponteiro origem */

      }
   }

#endif

/********** Fim do m�dulo de implementa��o: LIS Lista duplamente encadeada **********/

