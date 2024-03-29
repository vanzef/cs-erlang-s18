#pragma once

#include <erl_nif.h>
#include <string.h>
#include "la/types.h"
#include "la/constructor.h"
#include "nif/types.h"
#include "nif/utils.h"

ERL_NIF_TERM
nif_matrix_constructor(ErlNifEnv *,
                       int,
                       const ERL_NIF_TERM *);

/* ERL_NIF_TERM */
/* nif_vertical_vector_constructor(ErlNifEnv *, */
/*                                 int, */
/*                                 const ERL_NIF_TERM *); */

/* ERL_NIF_TERM */
/* nif_horizontal_vector_constructor(ErlNifEnv *, */
/*                                   int, */
/*                                   const ERL_NIF_TERM *); */
