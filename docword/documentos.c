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

Documentos* documentos_constroi() {

    return NULL;
}

void documentos_destroi() {


}
