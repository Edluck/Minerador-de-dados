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

    return NULL;
}

void palavras_destroi() {

}
