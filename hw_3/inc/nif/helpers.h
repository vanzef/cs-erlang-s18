#pragma once

#include <erl_nif.h>
#include "la.h"

#include "nif/types.h"
#include <string.h>

#include "nif/utils.h"

ERL_NIF_TERM
return_one(ErlNifEnv *,
           int,
           const ERL_NIF_TERM *);

ERL_NIF_TERM
nif_matrix_rows(ErlNifEnv *,
                int,
                const ERL_NIF_TERM *);

ERL_NIF_TERM
nif_matrix_columns(ErlNifEnv *,
                   int,
                   const ERL_NIF_TERM *);

ERL_NIF_TERM
nif_matrix_dim_rows(ErlNifEnv *,
                    int,
                    const ERL_NIF_TERM *);

ERL_NIF_TERM
nif_matrix_dim_columns(ErlNifEnv *,
                       int,
                       const ERL_NIF_TERM *);

ERL_NIF_TERM
nif_matrix_offset(ErlNifEnv *,
                  int,
                  const ERL_NIF_TERM *);

ERL_NIF_TERM
nif_matrix_step(ErlNifEnv *,
                int,
                const ERL_NIF_TERM *);


