#pragma once

#include <erl_nif.h>
#include "la.h"

#include "nif/types.h"
#include <string.h>

#include "nif/constructor.h"
#include "nif/destructor.h"
#include "nif/operations.h"
#include "nif/conversion.h"
#include "nif/extraction.h"
#include "nif/utils.h"
#include "nif/helpers.h"

int
load(ErlNifEnv *,
     void **,
     ERL_NIF_TERM);

static ErlNifFunc nif_funcs[] = {
  {"one",            0, return_one},
  {"matrix",         2, nif_matrix_constructor},
  {"matrix",         3, nif_from_array},
  {"rows",           1, nif_matrix_rows},
  {"columns",        1, nif_matrix_columns},
  {"row",            2, nif_extract_row_vector},
  {"column",         2, nif_extract_column_vector},
  {"main_diagonal",  1, nif_extract_main_diagonal},
  {"antidiagonal",   1, nif_extract_antidiagonal},
  {"to_array",       1, nif_to_array},
  {"sum",            2, nif_matrix_sum},
  {"mult",           2, nif_matrix_mult},
  {"mult_by_scalar", 2, nif_matrix_mult_by_scalar},
};

ERL_NIF_INIT(Elixir.LinearAlgebra,
             nif_funcs,
             &load,
             NULL, NULL, NULL)
