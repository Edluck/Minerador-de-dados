#include "documentos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int posicao_palavra;
    int frequencia_palavra_documento;
    float tf_idf;
} indice_documentos;

struct documentos
{
    char *nome;
    char *classe;

    indice_documentos *idx_documentos;
    int tam_vet_idx_documentos;
};

int tam_vet_limite_documento = 10;
int tam_vet_atual_documento = 0;
// Verifica se abriu corretamente o arquivo antes do programa
void documentos_verifica_se_abriu_arquivo(char argv[])
{
    FILE *arq;
    arq = fopen(argv, "r");
    if (!arq)
    {
        printf("Erro ao tentar abrir o arquivo!\n");
        exit(1);
    }
    fclose(arq);
}

Documentos *documentos_constroi(char train[])
{
    FILE *train_txt;
    char nome_aux[100] = ""; // utilizado para pegar o tamanho exato do nome
    train_txt = fopen(train, "r");
    Documentos *d = (Documentos *)calloc(tam_vet_limite_documento, sizeof(Documentos));

    while (!feof(train_txt))
    {
        if (tam_vet_atual_documento >= tam_vet_limite_documento)
        {
            tam_vet_limite_documento += 5;
            d = (Documentos *)realloc(d, tam_vet_limite_documento * sizeof(Documentos));
        }
        d[tam_vet_atual_documento] = (Documentos)calloc(1, sizeof(struct documentos));
        d[tam_vet_atual_documento]->idx_documentos = (indice_documentos *)calloc(1, sizeof(indice_documentos));
        d[tam_vet_atual_documento]->tam_vet_idx_documentos = 1;
        d[tam_vet_atual_documento]->classe = (char *)calloc(5, sizeof(char));

        fscanf(train_txt, "%s %s\n", nome_aux, d[tam_vet_atual_documento]->classe);
        d[tam_vet_atual_documento]->nome = strdup(nome_aux);
        tam_vet_atual_documento++;
    }

    fclose(train_txt);
    return d;
}

Documentos *documentos_constroi_com_binario(FILE *bynarie) {

    fread(&tam_vet_atual_documento, sizeof(int), 1, bynarie);
    Documentos *d = (Documentos *)calloc(tam_vet_atual_documento, sizeof(Documentos));
    int tam_nome = 0, tam_classe = 0;
    for (int i = 0; i < tam_vet_atual_documento; i++)
    {
        d[i] = (Documentos)calloc(1, sizeof(struct documentos));
        fread(&tam_nome, sizeof(int), 1, bynarie);
        fread(&tam_classe, sizeof(int), 1, bynarie);
        d[i]->nome = (char*)malloc(tam_nome*sizeof(char));
        d[i]->classe = (char*)malloc(tam_classe*sizeof(char));
        fread(d[i]->nome, sizeof(char), tam_nome, bynarie);
       
        fread(d[i]->classe, sizeof(char), tam_classe, bynarie);
        
        fread(&d[i]->tam_vet_idx_documentos, sizeof(int), 1, bynarie);
        d[i]->idx_documentos = (indice_documentos*)calloc(d[i]->tam_vet_idx_documentos, sizeof(indice_documentos));
       
        for (int j = 0; j < d[i]->tam_vet_idx_documentos - 1; j++)
        {
            fread(&d[i]->idx_documentos[j].frequencia_palavra_documento, sizeof(int), 1, bynarie);
            fread(&d[i]->idx_documentos[j].posicao_palavra, sizeof(int), 1, bynarie);
            fread(&d[i]->idx_documentos[j].tf_idf, sizeof(float), 1,bynarie);

        }
        
    }
    return d;
}

void documentos_faz_binario_inf_doc(Documentos *d, FILE *index_bynarie)
{
    fwrite(&tam_vet_atual_documento, sizeof(int), 1, index_bynarie);
    for (int i = 0; i < tam_vet_atual_documento; i++)
    {
        int tam_nome = strlen(d[i]->nome) +1, tam_class = strlen(d[i]->classe) +1;
        fwrite(&tam_nome,sizeof(int),1,index_bynarie);
        fwrite(&tam_class,sizeof(int),1,index_bynarie);
        fwrite(d[i]->nome, sizeof(char), tam_nome, index_bynarie);
        fwrite(d[i]->classe, sizeof(char), tam_class, index_bynarie);
        fwrite(&d[i]->tam_vet_idx_documentos, sizeof(int), 1, index_bynarie);
        for (int j = 0; j < d[i]->tam_vet_idx_documentos - 1; j++)
        {
            fwrite(&d[i]->idx_documentos[j].frequencia_palavra_documento, sizeof(int), 1, index_bynarie);
            fwrite(&d[i]->idx_documentos[j].posicao_palavra, sizeof(int), 1, index_bynarie);
            fwrite(&d[i]->idx_documentos[j].tf_idf, sizeof(float), 1,index_bynarie);
        }
    }
}

int documentos_retorna_tam_atual_vet()
{
    return tam_vet_atual_documento;
}

void documentos_retorna_nome_arq(Documentos d, char *nome_arq[])
{
    int tam = strlen(d->nome);
    *(nome_arq) = (char *)realloc(*(nome_arq), (tam + 1) * sizeof(char));
    strcpy(*(nome_arq), d->nome);
}

void documentos_preenche_vetor_idx_doc(Documentos *d, int ind_doc, int posica_pal, int freq, float tfidf)
{
    d[ind_doc]->idx_documentos[d[ind_doc]->tam_vet_idx_documentos - 1].posicao_palavra = posica_pal;
    d[ind_doc]->idx_documentos[d[ind_doc]->tam_vet_idx_documentos - 1].frequencia_palavra_documento = freq;
    d[ind_doc]->idx_documentos[d[ind_doc]->tam_vet_idx_documentos - 1].tf_idf = tfidf;
    d[ind_doc]->tam_vet_idx_documentos++;
    d[ind_doc]->idx_documentos = (indice_documentos *)realloc(d[ind_doc]->idx_documentos, (d[ind_doc]->tam_vet_idx_documentos) * sizeof(indice_documentos));
}

void documentos_imprime_informacao(Documentos *d)
{
    FILE *ind_doc = fopen("ind_doc.txt", "w");
    for (int i = 0; i < tam_vet_atual_documento; i++)
    {
        fprintf(ind_doc, "%d;%s;%s;%d:", i, d[i]->nome, d[i]->classe, d[i]->tam_vet_idx_documentos);
        for (int j = 0; j < d[i]->tam_vet_idx_documentos - 1; j++)
        {
            fprintf(ind_doc, "%d|%d|%f|", d[i]->idx_documentos[j].posicao_palavra, d[i]->idx_documentos[j].frequencia_palavra_documento, d[i]->idx_documentos[j].tf_idf);
        }
        fprintf(ind_doc, "\n");
    }
    fclose(ind_doc);
}

void documentos_imprime_recomendacoes(int i,int ind, float tfidf, Documentos* d) {
    printf("%d - %s,Classe: %s e Soma tfidf: %.04f\n", i, d[ind]->nome, d[ind]->classe, tfidf);
}

void documentos_destroi(Documentos *d)
{

    for (int i = 0; i < tam_vet_atual_documento; i++)
    {
        free(d[i]->idx_documentos);
        free(d[i]->nome);
        free(d[i]->classe);
        free(d[i]);
    }

    free(d);
}
