#include "nif/extraction.h"

ERL_NIF_TERM
nif_extract_row_vector(ErlNifEnv *env,
                       int argc,
                       const ERL_NIF_TERM *argv)
{
  la_matrix const **mat_res;
  if(!enif_get_resource(env, argv[0], LA_MATRIX_TYPE,(void **) &mat_res))
    return enif_make_badarg(env);

  la_matrix const *mat_ptr = *mat_res;

  uint row;
  if (!enif_get_uint(env, argv[1], &row))
    return enif_make_badarg(env);

  la_matrix *res;

  la_result result = la_extract_row_vector(&res, mat_ptr, row);
  if (result != ok)
    return enif_make_atom(env, "err");

  return nif_resource_from_la_matrix(env, res);
}

ERL_NIF_TERM
nif_extract_column_vector(ErlNifEnv *env,
                          int argc,
                          const ERL_NIF_TERM *argv)
{
  la_matrix const **mat_res;
  if(!enif_get_resource(env, argv[0], LA_MATRIX_TYPE,(void **) &mat_res))
    return enif_make_badarg(env);

  la_matrix const *mat_ptr = *mat_res;

  uint column;
  if (!enif_get_uint(env, argv[1], &column))
    return enif_make_badarg(env);

  la_matrix *res;

  la_result result = la_extract_column_vector(&res, mat_ptr, column);
  if (result != ok)
    return enif_make_atom(env, "err");

  return nif_resource_from_la_matrix(env, res);
}

ERL_NIF_TERM
nif_extract_main_diagonal(ErlNifEnv *env,
                          int argc,
                          const ERL_NIF_TERM *argv)
{
  la_matrix const **mat_res;
  if(!enif_get_resource(env, argv[0], LA_MATRIX_TYPE,(void **) &mat_res))
    return enif_make_badarg(env);

  la_matrix const *mat_ptr = *mat_res;

  la_matrix *res;

  la_result result = la_extract_main_diagonal(&res, mat_ptr);
  if (result != ok)
    return enif_make_atom(env, "err");

  return nif_resource_from_la_matrix(env, res);
}

ERL_NIF_TERM
nif_extract_antidiagonal(ErlNifEnv *env,
                         int argc,
                         const ERL_NIF_TERM *argv)
{
  la_matrix const **mat_res;
  if(!enif_get_resource(env, argv[0], LA_MATRIX_TYPE,(void **) &mat_res))
    return enif_make_badarg(env);

  la_matrix const *mat_ptr = *mat_res;

  la_matrix *res;

  la_result result = la_extract_antidiagonal(&res, mat_ptr);
  if (result != ok)
    return enif_make_atom(env, "err");

  return nif_resource_from_la_matrix(env, res);
}
