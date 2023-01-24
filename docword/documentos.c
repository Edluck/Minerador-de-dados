#include "documentos.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int posicao_palavra_documento;
    int frequencia_documento;
}indice_documentos;

struct
{
    char *nome;
    char *classe;
    int posicao_vetor_documentos;
    indice_documentos *idx_documentos;
}documentos;

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

Documentos* documentos_constroi() {
    Documentos *d = (Documentos*)calloc(1, sizeof(Documentos));
    
    return d;
}

void documentos_destroi(Documentos* d) {
    
    free(d);
}
