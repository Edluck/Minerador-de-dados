#include "palavras.h"
#include "documentos.h"
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
    if(argc <= 2) {
        printf("Sem caminho para o arquivo de entrada e de saida!\n");
    exit(1);
    }
   documentos_verifica_se_abriu_arquivo(argv[1]); 
   // cria o arquivo de saída
   FILE* index_bynarie = fopen(argv[2],"wb");

   Palavras *p = palavras_constroi();
   Documentos *d = documentos_constroi(argv[1]);

   documentos_destroi(d);
   palavras_destroi(p); 
   fclose(index_bynarie); 
    return 0;
}