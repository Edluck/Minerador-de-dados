#ifndef ORDENADOR_H
#define ORDENADOR_H
#include "documentos.h"
#include "palavras.h"

typedef struct
{
    int documento; // posicao do doc no vetor de documentos
    float soma_tfidf; // soma de tf idfs para a recomendacao
}ordem_noticia;

void ordenador_incializa_vet(ordem_noticia vet[], int tam);
void ordenador_ordena_vetor_recomendados_e_imprime(ordem_noticia vet[], int tam);

typedef void (*ordena_pointer)(Documentos*, Palavras*);

void ordenador_busca_noticia(Documentos*, Palavras*);
void ordenador_classifica_noticia(Documentos*, Palavras*);
void ordenador_relatorio_palavras(Documentos*, Palavras*);
void ordenador_relatorio_documentos(Documentos*, Palavras*);
void ordenador_imprime_recomendados(ordem_noticia vet[], Documentos *d);

#endif