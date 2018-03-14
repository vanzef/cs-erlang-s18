#include "nif/conversion.h"

ERL_NIF_TERM
nif_to_array(ErlNifEnv *env,
             int argc,
             const ERL_NIF_TERM *argv)
{
  la_matrix const **mat_res;
  if(!enif_get_resource(env, argv[0], LA_MATRIX_TYPE,(void **) &mat_res))
    return enif_make_atom(env, "err");

  const la_matrix *mat_ptr = *mat_res;
  const uint       rows    = la_dim_rows(mat_ptr);
  const uint       columns = la_dim_columns(mat_ptr);

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

ERL_NIF_TERM
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
