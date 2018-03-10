#include "linalg/conversion.h"
#include <stdlib.h>

la_result
la_from_array(la_matrix **res,
              uint rows,
              uint columns,
              const double *array)
{
  la_result result = la_matrix_new(res, rows, columns);
  if (result != ok)
    return result;

  /* WARNING: array doesn't carry it's own size, so be carefull */
  for (uint i = 0; i < rows * columns; i++)
    (*res)->data[i] = array[i];

  return ok;
}

la_result
la_to_array(double **array,
            const la_matrix *mat)
{
  ulint size = mat->rows * mat->columns;
  *array = malloc(size);
  if (*array == NULL)
    return null_ptr;

  for (uint i = 0; i < size; i++)
    *array[i] = mat->data[i];

  return ok;
}
