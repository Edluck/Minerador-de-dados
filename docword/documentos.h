#ifndef DOCUMENTOS_H
#define DOCUMENTOS_H

typedef struct documentos *Documentos;

Documentos* documentos_constroi(char train[]);
void documentos_destroi(Documentos* d);

void documentos_verifica_se_abriu_arquivo(char argv[]);


#endif