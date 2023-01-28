#include "documentos.h"
#include "palavras.h"
#include "organiza_arq.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Palavras *documento_palavra_constroi_indice(Documentos* d,Palavras* p, int tam_vet_doc, int tam_vet_atual_pal, int tam_vet_limite_pal) {
     FILE *arq_train;
    char aux[100] = "", *nome_arq = (char*)calloc(1, sizeof(char));
    int j = 0;
    for (int i = 0; i < tam_vet_doc; i++)
    {
        documentos_retorna_nome_arq(d[i], &nome_arq);
        sprintf(aux, "datasets/tiny/%s", nome_arq);
        arq_train = fopen(aux, "r");
        while (!feof(arq_train))
        {
            if(tam_vet_atual_pal >= tam_vet_limite_pal) {
                tam_vet_limite_pal *= 2;
                p = palavras_realoca_vet(p, tam_vet_limite_pal);
            }

            char nome_palavra[100] = "";
            fscanf(arq_train, "%s", nome_palavra);
            palavras_aloca_vetor(p, tam_vet_atual_pal);
            if(palavras_adiciona_ao_vetor(p, tam_vet_atual_pal, nome_palavra, i) == 1) {
                
                palavra_destroi_vetor_palavra(p[tam_vet_atual_pal]);
                tam_vet_atual_pal--;
            }  
            tam_vet_atual_pal++;
            palavras_ordena_vetor(p, tam_vet_atual_pal);
            j++;
        }
        fclose(arq_train);
    }
    
    free(nome_arq);
    return p;
}