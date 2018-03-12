#include "nif/destructor.h"

void
nif_matrix_destructor(ErlNifEnv *env,
                      void *res)
{
  la_matrix_destructor((la_matrix *) res);
}


