#pragma once

#include <erl_nif.h>
#include "la.h"

#include "nif/types.h"
#include <string.h>

#include "nif/utils.h"

ERL_NIF_TERM
nif_to_array(ErlNifEnv *,
             int,
             const ERL_NIF_TERM *);

ERL_NIF_TERM
nif_from_array(ErlNifEnv *,
               int,
               const ERL_NIF_TERM *);

