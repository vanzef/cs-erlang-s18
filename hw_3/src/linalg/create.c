#include "linalg/create.h"
#include <stdlib.h>

/* TODO: change malloc to nif_alloc_resource */

la_result
la_matrix_new(la_matrix **res,
              uint rows,
              uint columns)
{
  ulint size = rows * columns;
  double *pre_data = malloc(size);
  if (pre_data == NULL)
    return null_ptr;
  
  *res = malloc(sizeof(la_matrix));
  
  if (*res == NULL) {
    free(pre_data);
    return null_ptr;
  }

  (*res)->columns = columns;
  (*res)->rows = rows;
  (*res)->data = pre_data;
  return ok;
}

la_result
la_matrix_new_zeros(la_matrix **res,
                    uint rows,
                    uint columns)
{
  la_result result = la_matrix_new(res, rows, columns);

  if (result != ok)
    return result;

  for (ulint i = 0; i < rows * columns; i++)
    (*res)->data[i] = 0;

  return ok;
}

la_result
la_vvector_new(la_matrix **res,
               uint rows)
{
  return la_matrix_new(res, rows, 1);
}

la_result
la_vvector_new_zeros(la_matrix **res,
                     uint rows)
{
  return la_matrix_new_zeros(res, rows, 1);
}

la_result
la_hvector_new(la_matrix **res,
               uint columns)
{
  return la_matrix_new(res, 1, columns);
}

la_result
la_hvector_new_zeros(la_matrix **res,
                     uint columns)
{
  return la_matrix_new_zeros(res, 1, columns);
}
