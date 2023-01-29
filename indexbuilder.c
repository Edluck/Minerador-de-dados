#include "palavras.h"
#include "documentos.h"
#include "organiza_arq.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc <= 2)
    {
        printf("Sem caminho para o arquivo de entrada e de saida!\n");
        exit(1);
    }
    documentos_verifica_se_abriu_arquivo(argv[1]);
    // cria o arquivo de saída
    FILE *index_bynarie = fopen(argv[2], "wb");
    // alocando o espaco inicial
    Documentos *d = documentos_constroi(argv[1]);
    Palavras *p = palavras_constroi();
    int tam_vet_doc = documentos_retorna_tam_atual_vet(), tam_vet_pal = palavras_retorna_tam_atual_vet(), tam_vet_limite_pal = palavras_retorna_tam_limite_vet();
    // funcoes para construcao do indice
    p = organiza_arq_constroi_indice_palavra(d, p, tam_vet_doc, tam_vet_pal, tam_vet_limite_pal);
    tam_vet_pal = palavras_retorna_tam_atual_vet();

    organiza_arq_calcula_tfidf_palavra(p, tam_vet_doc, tam_vet_pal);
    organiza_arq_constroi_indice_documento(d, p, tam_vet_doc, tam_vet_pal);
    palavras_imprime_informacao(p);
    documentos_imprime_informacao(d);

    // constroi binario
     organiza_arq_constroi_binario(d,p, index_bynarie);
    // free no que foi alocado
    documentos_destroi(d);
    palavras_destroi(p);

    fclose(index_bynarie);
    return 0;
}