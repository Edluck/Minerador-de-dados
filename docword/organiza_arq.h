#ifndef ORGANIZA_H
#define ORGANIZA_H

#include "documentos.h"
#include "palavras.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float organiza_arq_fator_ponderacao(int n_total_docs, int n_docs_p_aparece);
Palavras *organiza_arq_constroi_indice_palavra(Documentos *d, Palavras *p, int tam_vet_doc, int tam_vet_atual_pal, int tam_vet_limite_pal);
void organiza_arq_calcula_tfidf_palavra(Palavras *p,int n_total_doc,int tam_vet_pal);
void organiza_arq_constroi_indice_documento(Documentos *d, Palavras *p, int tam_vet_doc, int tam_vet_pal);
void organiza_arq_constroi_binario(Documentos *d,Palavras *p, FILE *index_bynarie);

#endif