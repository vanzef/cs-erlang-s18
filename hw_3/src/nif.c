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

void
nif_matrix_destructor(ErlNifEnv *env,
                      void *res)
{
  la_matrix_destructor((la_matrix *) res);
}

static ERL_NIF_TERM
nif_to_array(ErlNifEnv *env,
             int argc,
             const ERL_NIF_TERM *argv)
{
  la_matrix const **mat_res;
  if(!enif_get_resource(env, argv[0], LA_MATRIX_TYPE,(void **) &mat_res))
    return enif_make_atom(env, "err");

  const la_matrix *mat_ptr = *mat_res;
  const uint       rows    = mat_ptr->rows;
  const uint       columns = mat_ptr->columns;

  double *array;
  la_result result = la_to_array(&array, mat_ptr);
  
  if (result != ok)
    return enif_make_atom(env, "err");

  /* convert array of C's doubles to array of Erlang's doubles */
  ERL_NIF_TERM *erl_array = enif_alloc(rows * columns * sizeof(ERL_NIF_TERM));
  if (erl_array == NULL) {
    free(array);
    return enif_make_atom(env, "err");
  }

  for (ulint i = 0; i < rows * columns; i++)
    erl_array[i] = enif_make_double(env, array[i]);

  free(array);
  ERL_NIF_TERM term = enif_make_list_from_array(env,
                                                erl_array,
                                                rows * columns);
  enif_free(erl_array);
  return term;
}

static ERL_NIF_TERM
nif_from_array(ErlNifEnv *env,
               int argc,
               const ERL_NIF_TERM *argv)
{
  uint rows, columns;
  if(!(enif_get_uint(env, argv[1], &rows)
       && enif_get_uint(env, argv[2], &columns)))
    return enif_make_badarg(env);
  
  /* get list's size */
  uint erl_list_size;
  if (!enif_get_list_length(env,
                            argv[0],
                            &erl_list_size))
    return enif_make_badarg(env);

  if (erl_list_size != (rows * columns))
    return enif_make_badarg(env);

  /* allocate array */
  double *array = malloc(erl_list_size * sizeof(double));
  if (array == NULL)
    return enif_make_atom(env, "err");

  /* obtaining list */
  ERL_NIF_TERM erl_list;
  ERL_NIF_TERM erl_list_head;
  ERL_NIF_TERM erl_list_tail;

  /* take split argv[0] into head and tail */
  if (!enif_get_list_cell(env,
                          argv[0],
                          &erl_list_head,
                          &erl_list_tail)) {
    free(array);
    return enif_make_badarg(env);
  }

  if (!enif_get_double(env,
                         erl_list_head,
                         &array[0])) {
      free(array);
      return enif_make_badarg(env);
    }
  
  uint i = 1;
  while (i < erl_list_size) {
    erl_list = erl_list_tail;

    /* split tail into head and new tail */
    if (!enif_get_list_cell(env,
                            erl_list,
                            &erl_list_head,
                            &erl_list_tail)) {
      free(array);
      return enif_make_badarg(env);
    }
    
    /* put head elem into array */
    if (!enif_get_double(env,
                         erl_list_head,
                         &array[i])) {
      free(array);
      return enif_make_badarg(env);
    }
    i++;    
  }
  
  la_matrix *mat_ptr;
  la_result result = la_from_array(&mat_ptr, array, rows, columns);
  if (result != ok)
    return enif_make_atom(env, "err");

  ERL_NIF_TERM term = nif_resource_from_la_matrix(env, mat_ptr);
  free(array);

  return term;
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


static ERL_NIF_TERM
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

static ERL_NIF_TERM
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
