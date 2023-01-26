#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "documentos.h"
#include "palavras.h"

struct hash
{
    Palavras *palavras_hash;
};

Hash* hash_constroi() {
    Hash *h = (Hash*)calloc(TAM_VET_HASH, sizeof(Hash));
    for (int i = 0; i < TAM_VET_HASH; i++)
    {
        h[i] = (Hash)calloc(1, sizeof(struct hash));
        h[i]->palavras_hash = palavras_constroi();
    }
    
    return h;
}

int hash_calcula_valor_string(char palavra[]) { // o padrao do calculo hash seguira o valor de cada caractere multiplicado pela sua posicao+1
    int hash = 0, i = 0, tam = strlen(palavra);

    for (i = 0; i < tam ; i++) // o \0 nao entra na conta
    {
        hash = hash + (palavra[i]*(i+1));
    }
    return hash%TAM_VET_HASH; // foi escolhido um numero primo, pois aumenta a dispersao de valores no vetor
} // para driblar a situacao em que palavras diferentes possuirem o mesmo hash, sera feito um vetor que armazene essas repeticoes em um vetor

void hash_preenche_vetor_idx_palavras(Hash *h,Documentos *d,Palavras* p) {
    
}


void hash_destroi(Hash* h) {

    for (int i = 0; i < TAM_VET_HASH; i++)
    {
        palavras_destroi(h[i]->palavras_hash);
        free(h[i]);
    }
    free(h);
}

