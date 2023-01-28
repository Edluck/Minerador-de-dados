#include "palavras.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int indice_documentos;
    int frequencia_no_documento;
    float tf_idf;
}indice_palavras;

struct palavras
{
    char *nome;
    int posicao_vetor_palavras;
    indice_palavras *idx_palavras;
    int tam_vet_idx_palavras;

    // salvar o tamanho do vetor
    int tam_vet_palavras;
};

int tam_vet_limite_palavra = 200;
int tam_vet_atual_palavra_global = 0;

int palavras_comparador_nomes(const void *nome1, const void *nome2) {
    Palavras p1 = *((Palavras*)nome1);
    Palavras p2 = *((Palavras*)nome2);

    return strcmp(p1->nome, p2->nome);
}

Palavras* palavras_constroi() {
    Palavras *p = (Palavras*)calloc(tam_vet_limite_palavra, sizeof(Palavras));
    return p;
}

Palavras* palavras_realoca_vet(Palavras* p, int tam_limite) {
    p = (Palavras*)realloc(p, tam_limite*sizeof(Palavras));
    return p;
}
void palavras_aloca_vetor(Palavras* p, int ind) {
    p[ind] = (Palavras)calloc(1, sizeof(struct palavras));
    p[ind]->idx_palavras = (indice_palavras*)calloc(1,sizeof(indice_palavras));
    p[ind]->tam_vet_idx_palavras = 1;
}

int palavras_retorna_tam_atual_vet() {
    return tam_vet_atual_palavra_global;
}
int palavras_retorna_tam_limite_vet() {
    return tam_vet_limite_palavra;
}

void palavras_imprime_informacao(Palavras *p) {

    FILE* out = fopen("ind_pal.txt", "w");
    for (int i = 0; i < tam_vet_atual_palavra_global; i++)
    {
        fprintf(out,"--%d => %s | ", i, p[i]->nome);
        for (int j = 0; j < p[i]->tam_vet_idx_palavras; j++)
        {
            fprintf(out,"freq %d no doc %d e TFIDF %.02f |", p[i]->idx_palavras[j].frequencia_no_documento, p[i]->idx_palavras[j].indice_documentos, p[i]->idx_palavras[j].tf_idf);
        }
        fprintf(out,"\n");
    }
    fclose(out);
} 

int palavras_adiciona_ao_vetor(Palavras* p,int tam_vet_atual_pal,char nome[],int num_doc) {
    Palavras *aux, puxar_nome = (Palavras)calloc(1, sizeof(struct palavras));
    puxar_nome->nome = strdup(nome);
    puxar_nome->idx_palavras = (indice_palavras*)calloc(1, sizeof(indice_palavras));
    puxar_nome->tam_vet_idx_palavras = 1;

    aux = (Palavras*)bsearch(&puxar_nome,p,tam_vet_atual_pal,sizeof(Palavras),palavras_comparador_nomes);
    if(aux) {
        
        if((*aux)->idx_palavras[(*aux)->tam_vet_idx_palavras-1].indice_documentos == num_doc) {
            (*aux)->idx_palavras[(*aux)->tam_vet_idx_palavras-1].frequencia_no_documento++;
        }
        else {
            (*aux)->tam_vet_idx_palavras++;
            (*aux)->idx_palavras = (indice_palavras*)realloc((*aux)->idx_palavras, (*aux)->tam_vet_idx_palavras*sizeof(indice_palavras));
            (*aux)->idx_palavras[(*aux)->tam_vet_idx_palavras-1].indice_documentos = num_doc;
            (*aux)->idx_palavras[(*aux)->tam_vet_idx_palavras-1].frequencia_no_documento = 1;
            (*aux)->idx_palavras[(*aux)->tam_vet_idx_palavras-1].tf_idf = 0;

        }
        palavra_destroi_vetor_palavra(puxar_nome);
        return 1; // caso exista a palavra
    }
    else {
        palavra_destroi_vetor_palavra(p[tam_vet_atual_pal]);// para não perder a referencia do calloc feito neste vetor, e poder igualar ao "puxar_nome"
        p[tam_vet_atual_pal] = puxar_nome;
        p[tam_vet_atual_pal]->idx_palavras[p[tam_vet_atual_pal]->tam_vet_idx_palavras-1].frequencia_no_documento = 1;
        p[tam_vet_atual_pal]->idx_palavras[p[tam_vet_atual_pal]->tam_vet_idx_palavras-1].tf_idf = 0;
        p[tam_vet_atual_pal]->idx_palavras[p[tam_vet_atual_pal]->tam_vet_idx_palavras-1].indice_documentos = num_doc;
        tam_vet_atual_palavra_global++;
        return 0; // caso nao exista
    }
    
}  
void palavras_ordena_vetor(Palavras* p,int tam_vet_atual_pal) {

    qsort(p,tam_vet_atual_pal,sizeof(Palavras),palavras_comparador_nomes);
    
}

void  palavra_destroi_vetor_palavra(Palavras p) {
    
        free(p->idx_palavras);
        free(p->nome);
        free(p);
}

void palavras_destroi(Palavras *p) {
    for (int i = 0; i < tam_vet_atual_palavra_global; i++)
    {
         palavra_destroi_vetor_palavra(p[i]);
    }
    
    free(p);
}
