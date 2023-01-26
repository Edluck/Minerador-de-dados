#include "documentos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int posicao_palavra_documento;
    int frequencia_documento;
}indice_documentos;

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
void documentos_verifica_se_abriu_arquivo(char argv[]) {
    FILE* arq;
    arq = fopen(argv, "r");
    if(!arq) {
        printf("Erro ao tentar abrir o arquivo!\n");
        exit(1);
    }
    fclose(arq);
}

Documentos* documentos_constroi(char train[]) {
    FILE* train_txt;
    char nome_aux[100] = "";
    train_txt = fopen(train, "r");
    Documentos *d = (Documentos*)calloc(tam_vet_limite_documento, sizeof(Documentos));

    while(!feof(train_txt)) {
        if(tam_vet_atual_documento >= tam_vet_limite_documento) {
            tam_vet_limite_documento+=5;
            printf("expandindo tamanho total de documentos...\n");
            d = (Documentos*)realloc(d,tam_vet_limite_documento*sizeof(Documentos));
        }
        d[tam_vet_atual_documento] = (Documentos)calloc(1, sizeof(struct documentos));
        d[tam_vet_atual_documento]->idx_documentos = (indice_documentos*)calloc(1,sizeof(indice_documentos));
        d[tam_vet_atual_documento]->tam_vet_idx_documentos = 1;
        d[tam_vet_atual_documento]->classe = (char*)calloc(5, sizeof(char));

        fscanf(train_txt,"%s %s\n", nome_aux, d[tam_vet_atual_documento]->classe);
        d[tam_vet_atual_documento]->nome = strdup(nome_aux);
        tam_vet_atual_documento++;
    }
    for (int i = 0; i < tam_vet_atual_documento; i++)
    {
        printf("Documento: %d | Nome: %s | Classe: %s\n", i+1, d[i]->nome, d[i]->classe);
    }
    

    fclose(train_txt);
    return d;
}

void documentos_destroi(Documentos* d) {
    
    for (int i = 0; i < tam_vet_atual_documento; i++)
    {
        free(d[i]->idx_documentos);
        free(d[i]->nome);     
        free(d[i]->classe);  
        free(d[i]);
    }
    

    free(d);
}
