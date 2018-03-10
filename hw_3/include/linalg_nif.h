/* This file declares NIF wrappers around C functions */

#pragma once

#include <erl_nif.h>
#include <stdio.h>              /* TODO: delete */

#include "linalg.h"

void dosmth();                  /* TODO: delete */

static ERL_NIF_TERM
hello(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]);

static ErlNifFunc nif_funcs[] = {
  {"hello", 0, hello}
};

ERL_NIF_INIT(Elixir.LinearAlgebra, nif_funcs, NULL, NULL, NULL, NULL)
