#include "nif/constructor.h"

ERL_NIF_TERM
nif_matrix_constructor(ErlNifEnv *env,
                       int argc,
                       const ERL_NIF_TERM *argv)
{
  uint rows, columns;
  if(!(enif_get_uint(env, argv[0], &rows)
       && enif_get_uint(env, argv[1], &columns)))
    return enif_make_badarg(env);

  la_matrix *mat_ptr;
  la_result result = la_matrix_constructor(&mat_ptr, rows, columns);
  if (result != ok)
    return enif_make_atom(env, "err");

  return nif_resource_from_la_matrix(env, mat_ptr);
}

/* ERL_NIF_TERM */
/* nif_vertical_vector_constructor(ErlNifEnv *env, */
/*                                 int argc, */
/*                                 const ERL_NIF_TERM *argv) */
/* { */
/*   uint rows; */
/*   if(!enif_get_uint(env, argv[0], &rows)) */
/*     return enif_make_badarg(env); */

/*   la_matrix *mat_ptr; */
/*   la_result result = la_vertical_vector_constructor(&mat_ptr, rows); */
/*   if (result != ok) */
/*     return enif_make_atom(env, "err"); */

/*   return nif_resource_from_la_matrix(env, mat_ptr); */
/* } */

/* ERL_NIF_TERM */
/* nif_horizontal_vector_constructor(ErlNifEnv *env, */
/*                                   int argc, */
/*                                   const ERL_NIF_TERM *argv) */
/* { */
/*   uint columns; */
/*   if(!enif_get_uint(env, argv[0], &columns)) */
/*     return enif_make_badarg(env); */

/*   la_matrix *mat_ptr; */
/*   la_result result = la_horizontal_vector_constructor(&mat_ptr, columns); */
/*   if (result != ok) */
/*     return enif_make_atom(env, "err"); */

/*   return nif_resource_from_la_matrix(env, mat_ptr); */
/* } */
