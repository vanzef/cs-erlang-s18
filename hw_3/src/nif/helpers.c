#include "nif/helpers.h"

ERL_NIF_TERM
return_one(ErlNifEnv *env,
           int argc,
           const ERL_NIF_TERM *argv)
{
  return enif_make_uint(env, (unsigned int) 1);
}

ERL_NIF_TERM
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

ERL_NIF_TERM
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

ERL_NIF_TERM
nif_matrix_dim_rows(ErlNifEnv *env,
                    int argc,
                    const ERL_NIF_TERM *argv)
{
  la_matrix const **mat_res;
  if(!enif_get_resource(env, argv[0], LA_MATRIX_TYPE,(void **) &mat_res))
    return enif_make_atom(env, "err");

  la_matrix const *mat_ptr = *mat_res;

  return enif_make_uint(env, la_dim_rows(mat_ptr));
}

ERL_NIF_TERM
nif_matrix_dim_columns(ErlNifEnv *env,
                       int argc,
                       const ERL_NIF_TERM *argv)
{
  la_matrix const **mat_res;
  if(!enif_get_resource(env, argv[0], LA_MATRIX_TYPE,(void **) &mat_res))
    return enif_make_atom(env, "err");

  la_matrix const *mat_ptr = *mat_res;

  return enif_make_uint(env, la_dim_columns(mat_ptr));
}

ERL_NIF_TERM
nif_matrix_offset(ErlNifEnv *env,
                   int argc,
                   const ERL_NIF_TERM *argv)
{
  la_matrix const **mat_res;
  if(!enif_get_resource(env, argv[0], LA_MATRIX_TYPE,(void **) &mat_res))
    return enif_make_atom(env, "err");

  la_matrix const *mat_ptr = *mat_res;

  return enif_make_uint(env, mat_ptr->offset);
}

ERL_NIF_TERM
nif_matrix_step(ErlNifEnv *env,
                   int argc,
                   const ERL_NIF_TERM *argv)
{
  la_matrix const **mat_res;
  if(!enif_get_resource(env, argv[0], LA_MATRIX_TYPE,(void **) &mat_res))
    return enif_make_atom(env, "err");

  la_matrix const *mat_ptr = *mat_res;

  return enif_make_uint(env, mat_ptr->step);
}
