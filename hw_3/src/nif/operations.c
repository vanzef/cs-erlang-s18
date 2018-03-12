#include "nif/operations.h"

ERL_NIF_TERM
nif_matrix_sum(ErlNifEnv *env,
               int argc,
               const ERL_NIF_TERM *argv)
{
  la_matrix const **mat_res;
  if(!enif_get_resource(env, argv[0], LA_MATRIX_TYPE,(void **) &mat_res))
    return enif_make_atom(env, "err");

  la_matrix const *mat_ptr = *mat_res;

  la_matrix const **right_res;
  if(!enif_get_resource(env, argv[1], LA_MATRIX_TYPE,(void **) &right_res))
    return enif_make_atom(env, "err");

  la_matrix const *right_ptr = *right_res;

  la_matrix *res;

  la_result result = la_matrix_sum(&res, mat_ptr, right_ptr);
  if (result != ok)
    return result;

  return nif_resource_from_la_matrix(env, res);
}

ERL_NIF_TERM
nif_matrix_mult_by_scalar(ErlNifEnv *env,
                          int argc,
                          const ERL_NIF_TERM *argv)
{
  double scalar;
  if (!enif_get_double(env, argv[0], &scalar))
    return enif_make_badarg(env);
  
  la_matrix const **mat_res;
  if(!enif_get_resource(env, argv[1], LA_MATRIX_TYPE,(void **) &mat_res))
    return enif_make_atom(env, "err");

  la_matrix const *mat_ptr = *mat_res;

  la_matrix *res;

  la_result result = la_matrix_mult_by_scalar(&res, scalar, mat_ptr);
  if (result != ok)
    return result;

  return nif_resource_from_la_matrix(env, res);
}
