#ifndef PALAVRAS_H
#define PALAVRAS_H

typedef struct palavras *Palavras;

Palavras* palavras_constroi(); // alocar espaco para a TAD de palavras e seus indices
void palavras_destroi(Palavras *p); // desaloca o espaco da TAD palavras



#endif