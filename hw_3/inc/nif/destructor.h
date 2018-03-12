#pragma once

#include <erl_nif.h>
#include "la/types.h"
#include "la/destructor.h"
#include "nif/types.h"

void nif_matrix_destructor(ErlNifEnv *,
                           void *);
