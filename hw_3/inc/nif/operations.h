#pragma once

#include <erl_nif.h>
#include "la.h"

#include "nif/types.h"
#include "nif/utils.h"

ERL_NIF_TERM
nif_matrix_sum(ErlNifEnv *,
               int,
               const ERL_NIF_TERM *);

ERL_NIF_TERM
nif_matrix_mult(ErlNifEnv *,
                int,
                const ERL_NIF_TERM *);

ERL_NIF_TERM
nif_matrix_mult_by_scalar(ErlNifEnv *,
                          int,
                          const ERL_NIF_TERM *);
