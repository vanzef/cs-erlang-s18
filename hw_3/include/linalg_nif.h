/* This file declares NIF wrappers around C functions */
#pragma once

#include <erl_nif.h>
#include "linalg.h"

ErlNifResourceType *MATRIX_TYPE;

void nif_destructor(ErlNifEnv*, void*);

int
load(ErlNifEnv*, void**, ERL_NIF_TERM);

static ERL_NIF_TERM
nif_la_matrix_new(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]);

/* static ERL_NIF_TERM */
/* nif_la_vvector_new(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]); */

/* static ERL_NIF_TERM */
/* nif_la_hvector_new(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]); */

/* static ERL_NIF_TERM */
/* nif_la_mat_add(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]); */

/* static ERL_NIF_TERM */
/* nif_la_mult_by_scalar(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]); */

/* static ERL_NIF_TERM */
/* nif_la_from_array(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]); */

/* static ERL_NIF_TERM */
/* nif_la_to_array(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]); */

static ErlNifFunc nif_funcs[] = {
  {"matrix_new", 2, nif_la_matrix_new}
};

ERL_NIF_INIT(Elixir.LinearAlgebra, nif_funcs, &load, NULL, NULL, NULL)
