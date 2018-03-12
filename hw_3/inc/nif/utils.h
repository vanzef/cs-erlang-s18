#pragma once

#include <erl_nif.h>
#include "la.h"
#include "nif/types.h"

#include <stdlib.h>
#include <string.h>

ERL_NIF_TERM
nif_resource_from_la_matrix(ErlNifEnv *,
                            const la_matrix *);

/* la_matrix */
/* nif_la_matrix_from_resource(la_matrix **, */
/*                             ErlNifEnv *, */
/*                             const ERL_NIF_TERM *, */
/*                             int); */
