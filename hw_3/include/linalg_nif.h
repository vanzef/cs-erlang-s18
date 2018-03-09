#ifndef LINALG_NIF_H_
#define LINALG_NIF_H_

#include <erl_nif.h>

static ERL_NIF_TERM
hello(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]);

static ErlNifFunc nif_funcs[] = {
  {"hello", 0, hello}
};

ERL_NIF_INIT(Elixir.LinearAlgebra, nif_funcs, NULL, NULL, NULL, NULL)

#endif
