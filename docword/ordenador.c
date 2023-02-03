#include "documentos.h"
#include "ordenador.h"
#include "palavras.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int compara_tfidf(const void *tfidf1, const void *tfidf2) {
     ordem_noticia t1 = *((ordem_noticia*)tfidf1);
     ordem_noticia t2 = *((ordem_noticia*)tfidf2);

      if(((t2.soma_tfidf) - (t1.soma_tfidf)) > 0) {
          return 1;
      }
      else if(((t2.soma_tfidf) - (t1.soma_tfidf)) < 0) {
          return -1;
      }
      else {
          return 0;
      }
}

void ordenador_incializa_vet(ordem_noticia vet[], int tam) {

     for (int i = 0; i < tam; i++)
     {
          vet[i].documento = -1;
          vet[i].soma_tfidf = 0.0;
     }
     
}

void ordenador_ordena_vetor_recomendados_e_imprime(ordem_noticia vet[], int tam) {   
     qsort(vet, tam, sizeof(ordem_noticia), compara_tfidf);
}

void ordenador_busca_noticia(Documentos* d, Palavras* p) {
     int tam_atual_doc = documentos_retorna_tam_atual_vet();
     ordem_noticia vet_recomendado[tam_atual_doc]; 
     ordenador_incializa_vet(vet_recomendado, tam_atual_doc);
     int tam_pesquisa = 5,tam_atual_pesquisa = 0, i = 0, qtd_aparicao_pal_no_doc = 0;
     char *pesquisa = (char*)malloc(tam_pesquisa*sizeof(char));
     printf("\nBusca: ");
     while(1) {
          if(tam_atual_pesquisa >= tam_pesquisa) {
               tam_pesquisa+=5;
               pesquisa = (char*)realloc(pesquisa, tam_pesquisa*sizeof(char));
          }
          scanf("%c", &pesquisa[i]);
          if(pesquisa[i] == '\n') {
          break;
          }
          tam_atual_pesquisa++;
          i++;
     }
     pesquisa[i] = '\0';
     printf("\n");
     char *teste1;
     
     teste1 = strtok(pesquisa, " ");
     while (teste1)
     {
          Palavras aux = palavras_verifica_se_existe(p, teste1);
          if(aux) {
               int tam_indx_pal = palavras_retorna_tam_atual_vet_idx_palavras(aux);
               for (int i = 0; i < tam_indx_pal; i++)
               {
                    float tfidf_aux = palavras_retorna_tfidf(aux, i);
                    int ind_doc_aux = palavras_retorna_ind_doc_da_palavra(aux, i);
                    vet_recomendado[ind_doc_aux].documento = ind_doc_aux;
                    vet_recomendado[ind_doc_aux].soma_tfidf += tfidf_aux;
                    qtd_aparicao_pal_no_doc++;
               }
               
          }
          teste1 = strtok(NULL, " ");
     }
     if(qtd_aparicao_pal_no_doc == 0) {
          printf("Não existem notícias contendo este texto\n");
          free(pesquisa);
          return;
     }
     ordenador_ordena_vetor_recomendados_e_imprime(vet_recomendado, tam_atual_doc);
     ordenador_imprime_recomendados(vet_recomendado, d);  
     free(pesquisa);
}

void ordenador_imprime_recomendados(ordem_noticia vet[], Documentos *d) {
     for (int i = 0; i < 10; i++)
     {
          if(!(vet[i].documento == -1))
          documentos_imprime_recomendacoes(i, vet[i].documento, vet[i].soma_tfidf, d);
     }
     
}

void ordenador_classifica_noticia(Documentos* d, Palavras* p) {

}

void ordenador_relatorio_palavras(Documentos* d, Palavras* p) {

}

void ordenador_relatorio_documentos(Documentos* d, Palavras* p) {
    
}