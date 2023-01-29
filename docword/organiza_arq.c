#include "documentos.h"
#include "palavras.h"
#include "organiza_arq.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

Palavras *organiza_arq_constroi_indice_palavra(Documentos *d, Palavras *p, int tam_vet_doc, int tam_vet_atual_pal, int tam_vet_limite_pal)
{
    FILE *arq_train;
    char aux[100] = "", *nome_arq = (char *)calloc(1, sizeof(char));
    int j = 0;
    for (int i = 0; i < tam_vet_doc; i++)
    {
        documentos_retorna_nome_arq(d[i], &nome_arq);
        sprintf(aux, "datasets/tiny/%s", nome_arq);
        arq_train = fopen(aux, "r");
        while (!feof(arq_train))
        {
            if (tam_vet_atual_pal >= tam_vet_limite_pal)
            {
                tam_vet_limite_pal *= 2;
                p = palavras_realoca_vet(p, tam_vet_limite_pal);
            }

            char nome_palavra[100] = "";
            fscanf(arq_train, "%s", nome_palavra);
            palavras_aloca_vetor(p, tam_vet_atual_pal);
            if (palavras_adiciona_ao_vetor(p, tam_vet_atual_pal, nome_palavra, i) == 1)
            {

                palavra_destroi_vetor_palavra(p[tam_vet_atual_pal]);
                tam_vet_atual_pal--;
            }
            tam_vet_atual_pal++;
            palavras_ordena_vetor(p, tam_vet_atual_pal);
            j++;
        }
        fclose(arq_train);
    }

    free(nome_arq);
    return p;
}

void organiza_arq_constroi_indice_documento(Documentos *d, Palavras *p, int tam_vet_doc, int tam_vet_pal)
{

    for (int i = 0; i < tam_vet_pal; i++)
    {
        int tam_vet_idx_palavras = palavras_retorna_tam_atual_vet_idx_palavras(p[i]);
        for (int j = 0; j < tam_vet_idx_palavras; j++)
        {
            int ind_doc = palavras_retorna_ind_doc_da_palavra(p[i], j);
            int freq_pal_doc = palavras_retorna_freq_doc_da_palavra(p[i], j);
            documentos_preenche_vetor_idx_doc(d, ind_doc, i, freq_pal_doc);
        }
    }
}
float organiza_arq_fator_ponderacao(int n_total_docs, int n_docs_p_aparece) {
    float idf = 0;

    idf = (log((1.0+n_total_docs)/(1.0+n_docs_p_aparece))) + 1.0;

    return idf;
}

void organiza_arq_calcula_tfidf_palavra(Palavras *p,int n_total_doc,int tam_vet_pal) {
    float tfidf = 0, idf = 0;
    for (int i = 0; i < tam_vet_pal; i++)
    {
        int tam_vet_idx_pal = palavras_retorna_tam_atual_vet_idx_palavras(p[i]);
        for (int j = 0; j < tam_vet_idx_pal; j++)
        {   
            int freq_no_doc = palavras_retorna_freq_doc_da_palavra(p[i], j);
            idf = organiza_arq_fator_ponderacao(n_total_doc, tam_vet_idx_pal);
            tfidf = freq_no_doc*idf;
            palavras_atribui_tfidf_estrutura(p, tfidf, i, j);
        }

    }
    
}

void organiza_arq_constroi_binario(Documentos *d,Palavras *p, FILE *index_bynarie) {
    documentos_constroi_binario_inf_doc(d, index_bynarie);
     palavras_constroi_binario_inf_pal(p,index_bynarie);
}