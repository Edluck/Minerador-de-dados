#include "palavras.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int indice_documentos;
    int frequencia_no_documento;
    float tf_idf;
}indice_palavras;

struct {
    char *nome;
    int posicao_vetor_palavras;
    indice_palavras *idx_palavras;
}palavras;

Palavras* palavras_constroi() {
    Palavras *p = (Palavras*)calloc(1, sizeof(Palavras));
    
    return p;
}

void palavras_destroi(Palavras *p) {

    free(p);
}
