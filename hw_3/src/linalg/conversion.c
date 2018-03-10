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
  for (uint r = 0; r < rows; r++)
    for (uint c = 0; c < columns; c++)
      (*res)->data[r][c] = array[r * columns + c];

  return ok;
}

la_result
la_to_array(double **array,
            const la_matrix *mat)
{
  uint rows = mat->rows;
  uint columns = mat->columns;
  *array = malloc(rows * columns * sizeof(double));
  if (*array == NULL)
    return null_ptr;

  for (uint r = 0; r < rows; r++)
    for (uint c = 0; c < columns; c++)
      (*array)[r * columns + c] = mat->data[r][c];

  return ok;
}
