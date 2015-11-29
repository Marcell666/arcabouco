#if ! defined( LISTA_ )
#define LISTA_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.h
*  Letras identificadoras:      LIS
*
*  Projeto: INF 1301
*  Autores: gbo - Gabriel Barbosa de Oliveira
*           gapm - Guilherme de Azevedo Pereira Marques
*           tdn - Thiago Duarte Naves
*           pa - Pedro Alvarez
*
*  $HA Hist�rico de evolu��o:
*     Vers�o   Autor               Data           Observa��es
*       2.00   gbo, gapm, tdn      20/09/2015     Lista de ponteiros de void.
*       1.00   gbo, gapm, tdn, pa  30/08/2015     In�cio do desenvolvimento.
*
*  $ED Descri��o do m�dulo
*     Implementa listas gen�ricas duplamente encadeadas.
*     Podem existir n listas em opera��o simultaneamente.
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

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para uma lista */

typedef struct LIS_tagLista * LIS_tppLista ;


/***********************************************************************
*
*  $TC Tipo de dados: LIS Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es da lista
*
***********************************************************************/

   typedef enum {

         LIS_CondRetOK = 0,
               /* Concluiu corretamente */

         LIS_CondRetListaVazia = 1 ,
               /* A lista n�o cont�m elementos */

         LIS_CondRetFimLista =2,
               /* Foi atingido o fim de lista */

         LIS_CondRetNaoAchou = 3,
               /* N�o encontrou o valor procurado */

         LIS_CondRetFaltouMemoria = 4 ,
               /* Faltou mem�ria ao tentar criar um elemento de lista */

       LIS_CondRetErroEstrutura = 5
               /* Estrutura da lista est� errada */

   } LIS_tpCondRet ;

/***********************************************************************
*
*  $TC Tipo de dados: LIS Modos de deturpar
*
*
***********************************************************************/

#ifdef _DEBUG

   typedef enum {

      LIS_DeturpaPtrProx = 0,
         /* Faz ponteiro para o pr�ximo 
         elemento da lista apontar para lixo*/
      LIS_DeturpaPtrAnt = 1,
         /* Faz ponteiro para o pr�ximo 
         elemento da lista apontar para lixo*/
      LIS_DeturpaPtrOrigem = 2,
         /* Faz ponteiro para a origem 
         da lista apontar para nulo */
      LIS_DeturpaCorrNulo = 3
         /* Anula ponteiro corrente */

   } LIS_tpDeturpa ;

#endif


/***********************************************************************
*
*  $TC Tipo de dados: LIS Tipo de dado
*
*
***********************************************************************/

#ifdef _DEBUG

   typedef enum {

      LIS_tpInteiro = 0 ,
         /* Tipo de dados inteiro */

      LIS_tpChar = 1 ,
         /* Tipo de dados caracter */

      LIS_tpFloat = 2 ,
         /* Tipo de dados ponto flutuante */

      LIS_tpDouble = 3
         /* Tipo de dados ponto flutuante de precis�o dupla */

   } LIS_tpTipo ;

#endif


/***********************************************************************
*
*  $FC Fun��o: LIS  &Criar lista
*
*  $ED Descri��o da fun��o
*     Cria uma lista gen�rica duplamente encadeada
*     e a retorna atrav�s do ponteiro passado como 
*     par�metro.
*
*
*  $EP Par�metros
*     pLista    -   ponteiro para o retorno da lista
*     pExcluir  -   ponteiro para uma fun��o chamada ao desalocar um
*                   elemento
*
*  Assertivas de entrada:
*     - pLista deve ser um ponteiro v�lido.
*     - pExcluir deve ser um ponteiro de fun��o v�lido ou NULL.
*
*  Assertivas de sa�da:
*     - *pLista deve conter uma inst�ncia v�lida de lista com a fun��o
*       de desaloca��o igual a pExcluir.
*
*  $FV Valor retornado
*    LIS_CondRetOK - Criou sem problemas
*    LIS_CondRetFaltouMemoria  -  Ocorreu um erro por falta de mem�ria
*
***********************************************************************/

   LIS_tpCondRet LIS_CriarLista( LIS_tppLista * pLista,
                                 void (* pExcluir)( void * pValor)) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Definir Fun��o Excluir
*
*  $ED Descri��o da fun��o
*     Define a fun��o que ser� chamada ao excluir um elemento da lista.
*     Essa fun��o substitui a fun��o definida pelo par�metro pExcluir
*     da fun��o LIS_CriarLista( ).
*
*  $EP Par�metros
*     lista     -   Lista cuja fun��o deve ser redefinida
*     pExcluir  -   ponteiro para uma fun��o chamada ao desalocar um
*                   elemento
*
*  Assertivas de entrada:
*     - lista deve ser uma inst�ncia v�lida de lista.
*     - pExcluir deve ser um ponteiro de fun��o v�lido ou NULL.
*
*  Assertivas de sa�da:
*     - A fun��o de desaloca��o de dados da lista passada passa a ser
*       a fun��o apontada por pExcluir ou NULL.
*
*  $FV Valor retornado
*     LIS_CondRetOK    - definiu sem problemas
*
***********************************************************************/

   LIS_tpCondRet LIS_DefinirFuncaoExcluir( LIS_tppLista lista,
                                 void (* pExcluir)( void * pValor)) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Destruir lista
*
*  $ED Descri��o da fun��o
*     Destr�i a lista fornecida.
*     O par�metro ponteiro para a lista n�o � modificado.
*     Se ocorrer algum erro durante a destrui��o, a lista resultar�
*     estruturalmente incorreta.
*     OBS. n�o existe previs�o para poss�veis falhas de execu��o.
*
*  $EP Par�metros
*     lista  -  Lista a ser destru�da
*
*  Assertivas de entrada:
*     - lista deve ser uma inst�ncia v�lida de lista.
*
*  Assertivas de sa�da:
*     - A mem�ria ocupada pela lista passada deve ser liberada.
*
*  $FV Valor retornado
*     LIS_CondRetOK    - destruiu sem problemas
*
***********************************************************************/

   LIS_tpCondRet LIS_DestruirLista( LIS_tppLista lista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Esvaziar lista
*
*  $ED Descri��o da fun��o
*     Elimina todos os elementos, sem contudo eliminar a lista
*     OBS. n�o existe previs�o para poss�veis falhas de execu��o.
*
*  $EP Par�metros
*     lista - ponteiro para a lista a ser esvaziada
*
*  Assertivas de entrada:
*     - lista deve ser uma inst�ncia v�lida de lista.
*
*  Assertivas de sa�da:
*     - Todos os elementos contidos na lista devem ser removidos e a
*       mem�ria ocupada por eles liberada.
*
*  $FV Valor retornado
*     LIS_CondRetOK  -  Esvaziou sem problemas
*
***********************************************************************/

   LIS_tpCondRet LIS_EsvaziarLista( LIS_tppLista lista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Inserir elemento antes
*
*  $ED Descri��o da fun��o
*     Insere novo elemento antes do elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Par�metros
*     lista - ponteiro para a lista onde deve ser inserido o elemento
*     pValor - valor do novo elemento
*     tipo - tipo de dado armazenado no elemento
*
*  Assertivas de entrada:
*     - lista deve ser uma inst�ncia v�lida de lista.
*
*  Assertivas de sa�da:
*     - Um novo elemento deve ser alocado e este deve conter o dado
*       pValor. Este elemento ser� inserido na posi��o anterior ao
*       elemente corrente na lista passada.
*
*  $FV Valor retornado
*     LIS_CondRetOK  -  inseriu sem problemas
*     LIS_CondRetFaltouMemoria  -  ocorreu um erro por falta de mem�ria
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista lista , void * pValor
                                           #ifdef _DEBUG
                                           , LIS_tpTipo tipo
                                           #endif
                                         ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Inserir elemento ap�s
*
*  $ED Descri��o da fun��o
*     Insere novo elemento ap�s o elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Par�metros
*     lista - ponteiro para a lista onde deve ser inserido o elemento
*     pValor - valor do novo elemento
*     tipo - tipo de dado armazenado no elemento
*
*  Assertivas de entrada:
*     - lista deve ser uma inst�ncia v�lida de lista.
*
*  Assertivas de sa�da:
*     - Um novo elemento deve ser alocado e este deve conter o dado
*       pValor. Este elemento ser� inserido na posi��o seguinte ao
*       elemente corrente na lista passada.
*
*  $FV Valor retornado
*     LIS_CondRetOK  -  inseriu sem problemas
*     LIS_CondRetFaltouMemoria  -  ocorreu um erro por falta de mem�ria
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista lista , void * pValor
                                           #ifdef _DEBUG
                                           , LIS_tpTipo tipo
                                           #endif
                                         ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Excluir elemento
*
*  $ED Descri��o da fun��o
*     Exclui o elemento corrente da lista dada.
*     Se existir o elemento a esquerda do corrente ser� o novo corrente.
*     Se n�o existir e existir o elemento � direita, este se tornar�
*     corrente.
*     Se este tamb�m n�o existir a lista tornou-se vazia.
*
*  $EP Par�metros
*     lista    - lista na qual deve excluir.
*
*  Assertivas de entrada:
*     - lista deve ser uma inst�ncia v�lida de lista.
*     - A lista deve conter ao menos 1 elemento.
*
*  Assertivas de sa�da:
*     - O elemento corrente da lista deve ser exclu�do e a mem�ria
*       utilizada pelo elemento deve ser liberada.
*
*  $FV Valor retornado
*     LIS_CondRetOK  -  exclu�do sem problemas
*     LIS_CondRetListaVazia  -  a lista est� vazia
*
***********************************************************************/

   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista lista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Obter refer�ncia para o valor contido no elemento
*
*  $ED Descri��o da fun��o
*     Obtem a refer�ncia para o valor contido no elemento corrente da
*     lista
*
*  $EP Par�metros
*     lista - lista de onde se quer o valor
*     ppValor - ponteiro para retorno do elemento
*
*  Assertivas de entrada:
*     - lista deve ser uma inst�ncia v�lida de lista.
*     - A lista deve conter ao menos 1 elemento.
*     - ppValor deve ser um ponteiro v�lido.
*
*  Assertivas de sa�da:
*     - *ppValor ir� conter o valor armazenado no elemento corrente da
*       lista.
*
*  $FV Valor retornado
*     LIS_CondRetOk -  se o elemento corrente existe
*     LIS_CondRetNaoAchou -  se a lista estiver vazia
*
***********************************************************************/

   LIS_tpCondRet LIS_ObterValor( LIS_tppLista lista, void ** ppValor ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Ir para o elemento inicial
*
*  $ED Descri��o da fun��o
*     Torna corrente o primeiro elemento da lista.
*     Faz nada se a lista est� vazia.
*
*  $EP Par�metros
*     lista - ponteiro para a lista a manipular
*
*  Assertivas de entrada:
*     - lista deve ser uma inst�ncia v�lida de lista.
*
*  Assertivas de sa�da:
*     - O elemento corrente da lista passa a ser o primeiro elemento
*       da lista ou NULL, caso a lista esteja vazia.
*
*  $FV Valor retornado
*     LIS_CondRetOk - fun��o executou sem problemas
*
***********************************************************************/

   LIS_tpCondRet LIS_IrInicioLista( LIS_tppLista lista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Ir para o elemento final
*
*  $ED Descri��o da fun��o
*     Torna corrente o elemento final da lista.
*     Faz nada se a lista est� vazia.
*
*  $EP Par�metros
*     lista - ponteiro para a lista a manipular
*
*  Assertivas de entrada:
*     - lista deve ser uma inst�ncia v�lida de lista.
*
*  Assertivas de sa�da:
*     - O elemento corrente da lista passa a ser o �ltimo elemento
*       da lista ou NULL, caso a lista esteja vazia.
*
*  $FV Valor retornado
*     LIS_CondRetOk - fun��o executou sem problemas
*
***********************************************************************/

   LIS_tpCondRet LIS_IrFinalLista( LIS_tppLista lista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Avan�ar elemento
*
*  $ED Descri��o da fun��o
*     Avan�a o elemento corrente numElem elementos na lista
*     Se numElem for positivo avan�a em dire��o ao final
*     Se numElem for negativo avan�a em dire��o ao in�cio
*     numElem pode ser maior do que o n�mro de elementos existentes na
*               dire��o desejada
*     Se numElem for zero somente verifica se a lista est� vazia
*
*  $EP Par�metros
*     lista  - ponteiro para a lista a ser manipulada
*     numElem - o n�mero de elementos a andar
*
*  Assertivas de entrada:
*     - lista deve ser uma inst�ncia v�lida de lista.
*     - lista deve conter ao menos 'numElem' elementos na dire��o
*       desejada contados a partir do elemento corrente.
*
*  Assertivas de sa�da:
*     - O elemento corrente da lista passa a ser o elemento distante
*       'numElem' posi��es do elemento corrente atual na dire��o
*       indicada pelo sinal de 'numElem'.
*
*  $FV Valor retornado
*     CondRetOK         - se numElem elementos tiverem sido andados
*     CondRetFimLista   - se encontrou o fim da lista antes de andar numElem
*                         elementos
*     CondRetListaVazia - se a lista est� vazia
*
***********************************************************************/

   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista lista ,
                                              int numElem ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Procurar elemento contendo valor
*
*  $ED Descri��o da fun��o
*     Procura o elemento que referencia o valor dado.
*     A fun��o compara ponteiro e n�o conte�do apontado.
*
*  $EP Par�metros
*     lista  - ponteiro para a lista onde procura
*     pValor  - ponteiro para o valor procurado
*               Pode ser NULL
*
*  Assertivas de entrada:
*     - lista deve ser uma inst�ncia v�lida de lista.
*     - lista deve conter ao menos um elemento com o dado igual a
*       pValor.
*
*  Assertivas de sa�da:
*     - O elemento corrente da lista passa a ser o elemento cujo
*       valor � igual a 'pValor'.
*
*  $FV Valor retornado
*     LIS_CondRetOK  - se encontrou.
*                      O elemento corrente � o primeiro elemento do
*                      elemento corrente inclusive para o fim da lista
*                      e que cont�m o ponteiro procurado
*
*     LIS_CondRetNaoEncontrou - se o ponteiro n�o foi encontrado
*                               O elemento corrente continua o mesmo
*     LIS_CondRetListaVazia   - se a lista estiver vazia
*
***********************************************************************/

   LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista lista ,
                                    void * pValor        ) ;
									
/***********************************************************************
*
*  $FC Fun��o: LIS  &Verificar uma lista
*
*  $ED Descri��o da fun��o
*     Verifica completamente uma determinada lista duplamente encadeada.
*     Tamb�m marca todos os espa�os por ela ocupados.
*  $EP Par�metros
*     lista  - ponteiro para a lista
*
***********************************************************************/

#ifdef _DEBUG

   LIS_tpCondRet LIS_VerificarLista( LIS_tppLista lista ) ;

#endif

/***********************************************************************
*
*  $FC Fun��o: LIS  &Verificar um n� cabe�a
*
*  $ED Descri��o da fun��o
*     Verifica a integridade de um n� cabe�a da lista.
*
*  $EP Par�metros
*     lista  - ponteiro para a lista
*
*  $FV Valor retornado
*     Condi��o de retorno de teste
*
***********************************************************************/

#ifdef _DEBUG

   LIS_tpCondRet LIS_VerificarCabeca( LIS_tppLista lista ) ;

#endif


/***********************************************************************
*
*  $FC Fun��o: LIS  &Deturpar lista
*
*  $ED Descri��o da fun��o
*     Corrompe elementos espec�ficos da estrutura da lista.
*     Essa fun��o destina-se a preparar os cen�rios de teste dos
*     casos de teste utilizados ao testar os verificadores estruturais
*     da lista.
*
*  $EP Par�metros
*     $P lista  - lista a ser deturpada
*     $P ModoDeturpar - identifica como deve ser feita a deturpa��o
*                       LIS_tpDeturpa identifica os modos de
*                       deturpa��o conhecidos
*
***********************************************************************/

#ifdef _DEBUG

   void LIS_Deturpar( LIS_tppLista lista ,
                      LIS_tpDeturpa modoDeturpar ) ;

#endif


/********** Fim do m�dulo de defini��o: LIS  Lista duplamente encadeada **********/

#else
#endif
