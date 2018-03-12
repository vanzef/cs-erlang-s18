#include "nif/utils.h"

ERL_NIF_TERM
nif_resource_from_la_matrix(ErlNifEnv *env,
                            const la_matrix *matrix) {
  la_matrix **resource = enif_alloc_resource(LA_MATRIX_TYPE, sizeof(la_matrix *));

  memcpy((void *) resource, (void *) &matrix, sizeof(la_matrix *));

  ERL_NIF_TERM term = enif_make_resource(env, resource);
  enif_release_resource(resource);

  return term;
}

/* la_matrix */
/* nif_la_matrix_from_resource(la_matrix **res, */
/*                             ErlNifEnv *env, */
/*                             const ERL_NIF_TERM *argv, */
/*                             int index) */
/* { */
  
/* } */

