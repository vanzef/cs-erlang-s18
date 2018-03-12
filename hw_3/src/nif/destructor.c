#include "nif/destructor.h"

#include <stdio.h>

void
nif_matrix_destructor(ErlNifEnv *env,
                      void *res)
{
  la_matrix_destructor((la_matrix **) res);
}


