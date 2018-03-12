#include "la/conversion.h"

la_result
la_from_array(la_matrix **res,
              const double *array,
              const uint rows,
              const uint columns)
{
  la_result result = la_matrix_constructor(res, rows, columns);
  if (result != ok)
    return result;

  /* WARNING: may be dangerous due array doesn't carry any info
     about it's size  */
  for (uint r = 0; r < rows; r++)
    for (uint c = 0; c < columns; c++)
      (*res)->data[r][c] = array[r * columns + c];

  return ok;
}

/* Be carefull, dimensions are not returned */
la_result
la_to_array(double **res,
            la_matrix const *matrix)
{
  const uint rows    = matrix->rows;
  const uint columns = matrix->columns;

  (*res) = malloc(rows * columns * sizeof(double));
  if (*res == NULL)
    return null_ptr;

  for (uint r = 0; r < rows; r++)
    for (uint c = 0; c < columns; c++)
      (*res)[r * columns + c] = matrix->data[r][c];

  return ok;
}

