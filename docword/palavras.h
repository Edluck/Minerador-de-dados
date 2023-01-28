#ifndef PALAVRAS_H
#define PALAVRAS_H

typedef struct palavras *Palavras;

int palavras_comparador_nomes(const void *nome1, const void *nome2);
Palavras* palavras_constroi(); // alocar espaco para a TAD de palavras e seus indices
Palavras* palavras_realoca_vet(Palavras* p, int tam_limite);
int palavras_retorna_tam_atual_vet();
int palavras_retorna_tam_limite_vet();

int palavras_adiciona_ao_vetor(Palavras* p,int tam_vet_atual_pal,char nome[],int num_doc);  
void palavras_ordena_vetor(Palavras* p,int tam_vet_atual_pal);

void palavras_imprime_informacao(Palavras *p);
void palavras_aloca_vetor(Palavras* p, int ind);

void  palavra_destroi_vetor_palavra(Palavras p);
void palavras_destroi(Palavras *p); // desaloca o espaco da TAD palavras



#endif