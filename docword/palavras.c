#include "palavras.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int indice_documentos;
    int frequencia_no_documento;
    float tf_idf;
    int hash_value;
}indice_palavras;

struct palavras
{
    char *nome;
    int posicao_vetor_palavras;
    indice_palavras *idx_palavras;
};

int tam_vet_palavra = 10;
int tam_vet_atual_palavra = 0;

Palavras* palavras_constroi() {
    Palavras *p = (Palavras*)calloc(1, sizeof(Palavras));
    return p;
}

void palavras_destroi(Palavras *p) {

    free(p);
}
