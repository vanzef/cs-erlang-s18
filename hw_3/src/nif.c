#include "nif.h"
#include <stdio.h>

int
load(ErlNifEnv *env,
     void **priv_data,
     ERL_NIF_TERM load_info)
{
  int flags = ERL_NIF_RT_CREATE | ERL_NIF_RT_TAKEOVER;
  if ((LA_MATRIX_TYPE = enif_open_resource_type(env,
                                                NULL,
                                                "matrix",
                                                nif_matrix_destructor,
                                                flags,
                                                NULL))
      == NULL)
    return 1;
  return 0;
}

static ERL_NIF_TERM
return_one(ErlNifEnv *env,
           int argc,
           const ERL_NIF_TERM *argv)
{
  return enif_make_uint(env, (unsigned int) 1);
}

static ERL_NIF_TERM
nif_matrix_rows(ErlNifEnv *env,
                int argc,
                const ERL_NIF_TERM *argv)
{
  la_matrix const **mat_res;
  if(!enif_get_resource(env, argv[0], LA_MATRIX_TYPE,(void **) &mat_res))
    return enif_make_atom(env, "err");

  la_matrix const *mat_ptr = *mat_res;

  return enif_make_uint(env, mat_ptr->rows);
}

static ERL_NIF_TERM
nif_matrix_columns(ErlNifEnv *env,
                   int argc,
                   const ERL_NIF_TERM *argv)
{
  la_matrix const **mat_res;
  if(!enif_get_resource(env, argv[0], LA_MATRIX_TYPE,(void **) &mat_res))
    return enif_make_atom(env, "err");

  la_matrix const *mat_ptr = *mat_res;

  return enif_make_uint(env, mat_ptr->columns);
}
