#if ! defined( MATRIZ_ )
#define MATRIZ_
/***************************************************************************
*
*  $MCD Módulo de definição: Módulo matriz
*
*  Arquivo gerado:              matriz.h
*  Letras identificadoras:      MAT
*
*  Projeto: Disciplina INF 1301
*  Autores: gbo - Gabriel Barbosa de Oliveira
*           gapm - Guilherme de Azevedo Peraira Marques
*           tdn - Thiago Duarte Naves
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       1.00   tdn   21/08/2015 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo implementa um conjunto simples de funções para criar e
*     manipular matrizes.
*
*     A matriz é referenciada pelo usuário utilizando um ponteiro para
*     uma estrutura alocada pela função MAT_CriarMatriz.
*     Ao ser criada uma matriz não possui linhas nem colunas. Estas
*     devem ser adicionadas utilizando as funções MAT_InserirLinha e
*     MAT_InserirColuna. A primeira chamada de qualquer dessas funções
*     cria um única célula vazia.
*     Cada célula da matriz pode conter uma lista do tipo LIS_tppLista.
*
***************************************************************************/

/***********************************************************************
*
*  Módulo de lista duplamente encadeada
*
*
***********************************************************************/

#include "lista.h"


/***********************************************************************
*
*  $TC Tipo de dados: MAT Matriz da matriz visto pelo usuário
*
*
***********************************************************************/

typedef void * MAT_tpMatriz;


/***********************************************************************
*
*  $TC Tipo de dados: MAT Condicoes de retorno
*
*
***********************************************************************/

   typedef enum {

         MAT_CondRetOK = 0 ,
               /* Executou correto */

         MAT_CondRetNaoCriouMatriz = 1 ,
               /* Não criou o handle */

         MAT_CondRetErroEstrutura = 2 ,
               /* Estrutura da mariz está errada */

         MAT_CondRetMatrizNaoExiste = 3 ,
               /* Mariz não existe */

         MAT_CondRetMatrizVazia = 4 ,
               /* Mariz está vazia */

         MAT_CondRetNaoPossuiCelula = 5 ,
               /* Matriz não possui a célula desejada */

         MAT_CondRetNaoPossuiColuna = 6 ,
               /* Matriz não possui a coluna desejada */

         MAT_CondRetNaoPossuiLinha = 7 ,
               /* Matriz não possui a linha desejada */

         MAT_CondRetFaltouMemoria = 8 ,
               /* Faltou memória ao alocar dados */

         MAT_CondRetPonteiroRetornoNulo = 9
               /* Ponteiro passado por parâmetro para retorno é NULL */

   } MAT_tpCondRet ;


/***********************************************************************
*
*  $FC Função: MAT Criar mariz
*
*  $ED Descrição da função
*     Cria uma nova mariz vazia
*     Se não for possível criar a matriz, Matriz será NULL
*
*  $EP Parâmetros
*     $P Matriz - parâmetro para retorno do matriz
*                 Este parâmetro é passado por referência
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetNaoCriouMatriz
*     MAT_CondRetFaltouMemoria
*
***********************************************************************/

   MAT_tpCondRet MAT_CriarMatriz( MAT_tpMatriz * pMatriz ) ;


/***********************************************************************
*
*  $FC Função: MAT Destruir mariz
*
*  $ED Descrição da função
*     Destrói o corpo e o handle da mariz, anulando a mariz passada
*     Essa função se encarrega de destruir as listas contidas na matriz
*     Faz nada caso a mariz passada não exista
*
*  $EP Parâmetros
*     $P Matriz - matriz a ser destruída
*
*  $FV Valor retornado
*     MAT_CondRetOK
*
***********************************************************************/

   MAT_tpCondRet MAT_DestruirMatriz( MAT_tpMatriz Matriz ) ;


/***********************************************************************
*
*  $FC Função: MAT Inserir coluna
*
*  $ED Descrição da função
*     Adiciona uma coluna vazia à direita da matriz
*
*  $EP Parâmetros
*     $P Matriz - matriz a ser estendida
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetErroEstrutura
*     MAT_CondRetFaltouMemoria
*
***********************************************************************/

   MAT_tpCondRet MAT_InserirColuna( MAT_tpMatriz Matriz ) ;


/***********************************************************************
*
*  $FC Função: MAT Inserir linha
*
*  $ED Descrição da função
*     Adiciona uma linha vazia abaixo da matriz
*
*  $EP Parâmetros
*     $P Matriz - matriz a ser estendida
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetErroEstrutura
*     MAT_CondRetFaltouMemoria
*
***********************************************************************/

   MAT_tpCondRet MAT_InserirLinha( MAT_tpMatriz Matriz ) ;


/***********************************************************************
*
*  $FC Função: MAT Ler célula
*
*  $ED Descrição da função
*     Obtém a lista contida em uma célula da matriz
*
*  $EP Parâmetros
*     $P Matriz - matriz a ser lida
*     $P Coluna - coluna da célula desejada
*                 a coluna mais à esquerda tem índice 0
*     $P Linha  - linha da célula desejada
*                 a linha mais à esquerda tem índice 0
*     $P Lista  - retorno da lista armazenada na célula
*                 Este parâmetro é passado por referência
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*     MAT_CondRetNaoPossuiCelula
*     MAT_CondRetPonteiroRetornoNulo
*
***********************************************************************/

   MAT_tpCondRet MAT_LerCelula( MAT_tpMatriz Matriz , int Coluna , int Linha , LIS_tppLista * Lista ) ;


/***********************************************************************
*
*  $FC Função: MAT Escrever célula
*
*  $ED Descrição da função
*     Adiciona uma lista a uma célula da matriz
*
*  $EP Parâmetros
*     $P Matriz - matriz a ser modificada
*     $P Coluna - coluna da célula desejada
*                 a coluna mais à esquerda tem índice 0
*     $P Linha  - linha da célula desejada
*                 a linha mais à esquerda tem índice 0
*     $P Lista  - lista a armazenar na célula
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*     MAT_CondRetNaoPossuiCelula
*
***********************************************************************/

   MAT_tpCondRet MAT_EscreverCelula( MAT_tpMatriz Matriz , int Coluna , int Linha , LIS_tppLista Lista ) ;


/***********************************************************************
*
*  $FC Função: MAT Excluir coluna
*
*  $ED Descrição da função
*     Exclui a coluna especificada da matriz
*     Essa função se encarrega de destruir as listas contidas na coluna excluida
*
*  $EP Parâmetros
*     $P Matriz - matriz a ser modificada
*     $P Coluna - coluna que se deseja excluir
*                 a coluna mais à esquerda tem índice 0
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*     MAT_CondRetNaoPossuiColuna
*
***********************************************************************/

   MAT_tpCondRet MAT_ExcluirColuna( MAT_tpMatriz Matriz , int Coluna ) ;


/***********************************************************************
*
*  $FC Função: MAT Excluir linha
*
*  $ED Descrição da função
*     Exclui a linha especificada da matriz
*     Essa função se encarrega de destruir as listas contidas na linha excluida
*
*  $EP Parâmetros
*     $P Matriz - matriz a ser modificada
*     $P Linha  - linha que se deseja excluir
*                 a linha mais à esquerda tem índice 0
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*     MAT_CondRetNaoPossuiLinha
*
***********************************************************************/

   MAT_tpCondRet MAT_ExcluirLinha( MAT_tpMatriz Matriz , int Linha ) ;


/********** Fim do módulo de definição: Módulo mariz **********/

#endif
