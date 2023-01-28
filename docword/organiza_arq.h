#ifndef ORGANIZA_H
#define ORGANIZA_H

#include "documentos.h"
#include "palavras.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Palavras *documento_palavra_constroi_indice(Documentos* d,Palavras* p, int tam_vet_doc, int tam_vet_atual_pal, int tam_vet_limite_pal);

#endif