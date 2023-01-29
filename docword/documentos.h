#ifndef DOCUMENTOS_H
#define DOCUMENTOS_H
#include <stdio.h>
typedef struct documentos *Documentos;

Documentos *documentos_constroi(char train[]);
int documentos_retorna_tam_atual_vet();
void documentos_destroi(Documentos *d);

void documentos_preenche_vetor_idx_doc(Documentos *d, int ind_doc, int posica_pal, int freq);
void documentos_imprime_informacao(Documentos *d);
void documentos_verifica_se_abriu_arquivo(char argv[]);
void documentos_constroi_binario_inf_doc(Documentos* d,FILE *index_bynarie);
void documentos_retorna_nome_arq(Documentos d, char *nome_arq[]);

#endif