#include "documentos.h"
#include "ordenador.h"
#include "palavras.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    // verificando se os argumentos estao corretos
    if (argc <= 2)
    {
        printf("Argumentos insuficientes!\n");
        exit(1);
    }
    documentos_verifica_se_abriu_arquivo(argv[1]);
    // Atribuindo as informacoes do binario as estruturas
    FILE *bin = fopen(argv[1], "rb");
    ordena_pointer f;
    Documentos *d = documentos_constroi_com_binario(bin);
    Palavras *p = palavras_constroi_com_binario(bin);

    int escolha = 0;// k = argv[2] - '0';
    do
    {
        printf("\nO que deseja?\n\n");
        printf("0 - Sair\n1 - Buscar noticia\n2 - Classificar noticia\n3 - Relatorio de palavras\n4 - Relatorio de documentos\n\nEscolha: ");
        scanf("%d%*c", &escolha);
        switch (escolha)
        {
        case 1:
            f = ordenador_busca_noticia;
            break;
        case 2:
            f = ordenador_classifica_noticia;
            break;
        case 3:
            f = ordenador_relatorio_palavras;
            break;
        case 4:
            f = ordenador_relatorio_documentos;
            break;
        default:
            break;
        }
        if (escolha)
            f(d, p);
    } while (escolha);

    documentos_destroi(d);
    palavras_destroi(p);

    fclose(bin);
    return 0;
}
