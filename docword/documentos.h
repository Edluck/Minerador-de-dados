#ifndef DOCUMENTOS_H
#define DOCUMENTOS_H

typedef struct documentos *Documentos;

Documentos* documentos_constroi(char train[]);
int documentos_retorna_tam_atual_vet();
void documentos_destroi(Documentos* d);

void documentos_verifica_se_abriu_arquivo(char argv[]);
void documentos_retorna_nome_arq(Documentos d, char *nome_arq[]);

#endif