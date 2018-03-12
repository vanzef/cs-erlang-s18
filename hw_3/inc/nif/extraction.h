#pragma once

#include <erl_nif.h>
#include "nif/utils.h"
#include "la.h"

ERL_NIF_TERM
nif_extract_row_vector(ErlNifEnv *,
                       int,
                       const ERL_NIF_TERM *);

ERL_NIF_TERM
nif_extract_column_vector(ErlNifEnv *,
                          int,
                          const ERL_NIF_TERM *);

ERL_NIF_TERM
nif_extract_main_diagonal(ErlNifEnv *,
                          int,
                          const ERL_NIF_TERM *);

ERL_NIF_TERM
nif_extract_antidiagonal(ErlNifEnv *,
                         int,
                         const ERL_NIF_TERM *);
