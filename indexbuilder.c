#include "palavras.h"
#include "documentos.h"

int main (int argc, char *argv[]) {
   documentos_verifica_se_abriu_arquivo(argv[1]); 
   Palavras *p = palavras_constroi();
   Documentos *d = documentos_constroi();
    
    return 0;
}