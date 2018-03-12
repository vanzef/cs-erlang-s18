#pragma once

#include <erl_nif.h>
#include "la.h"

#include "nif/types.h"
#include <string.h>

int
load(ErlNifEnv *,
     void **,
     ERL_NIF_TERM);

static ERL_NIF_TERM
return_one(ErlNifEnv *,
           int,
           const ERL_NIF_TERM *);

static ERL_NIF_TERM
nif_matrix_constructor(ErlNifEnv *,
                       int,
                       const ERL_NIF_TERM *);

static ERL_NIF_TERM
nif_to_array(ErlNifEnv *,
             int,
             const ERL_NIF_TERM *);

static ERL_NIF_TERM
nif_from_array(ErlNifEnv *,
               int,
               const ERL_NIF_TERM *);

/* static ERL_NIF_TERM */
/* nif_vvector_constructor(ErlNifEnv *, */
/*                         int, */
/*                         const ERL_NIF_TERM *); */

/* static ERL_NIF_TERM */
/* nif_vvector_constructor(ErlNifEnv *, */
/*                         int, */
/*                         const ERL_NIF_TERM *); */

void nif_matrix_destructor(ErlNifEnv *,
                           void *);

static ERL_NIF_TERM
nif_matrix_rows(ErlNifEnv *,
                int,
                const ERL_NIF_TERM *);

static ERL_NIF_TERM
nif_matrix_columns(ErlNifEnv *,
                   int,
                   const ERL_NIF_TERM *);

static ERL_NIF_TERM
nif_matrix_sum(ErlNifEnv *,
               int,
               const ERL_NIF_TERM *);

/* static ERL_NIF_TERM */
/* nif_matrix_mult(ErlNifEnv *, */
/*                 int, */
/*                 const ERL_NIF_TERM *); */

static ERL_NIF_TERM
nif_matrix_mult_by_scalar(ErlNifEnv *,
                          int,
                          const ERL_NIF_TERM *);

static ErlNifFunc nif_funcs[] = {
  {"one",        0, return_one},
  {"matrix",     2, nif_matrix_constructor},
  {"matrix",     3, nif_from_array},
  {"rows",       1, nif_matrix_rows},
  {"columns",    1, nif_matrix_columns},
  {"to_array",   1, nif_to_array},
  {"sum",            2, nif_matrix_sum},
  /* {"mult",           2, nif_matrix_mult}, */
  {"mult_by_scalar", 2, nif_matrix_mult_by_scalar},
};

ERL_NIF_INIT(Elixir.LinearAlgebra,
             nif_funcs,
             &load,
             NULL, NULL, NULL)
