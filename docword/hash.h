#ifndef HASH_H
#define HASH_H


#include "documentos.h"
#include "palavras.h"
#define TAM_VET_HASH 20123

typedef struct hash *Hash;

Hash* hash_constroi();
int hash_calcula_valor_string(char palavra[]);
void hash_preenche_vetor_idx_palavras(Hash *h,Documentos *d,Palavras* p);

void hash_destroi(Hash* h);

#endif