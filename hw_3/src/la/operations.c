#include "la/operations.h"

la_result
la_matrix_sum(la_matrix **res,
              const la_matrix *left,
              const la_matrix *right)
{
  const uint rows    = left->rows;
  const uint columns = left->columns;
  if ((rows != right->rows) || (columns != right->columns))
    return dimensional_problems;

  la_result result = la_matrix_constructor(res, rows, columns);
  if (result != ok)
    return result;

  for (uint r = 0; r < rows; r++)
    for (uint c = 0; c < columns; c++)
      (*res)->data[r][c] = left->data[r][c] + right->data[r][c];

  return ok;
}

/* la_result */
/* la_matrix_mult(la_matrix **, */
/*                const la_matrix *, */
/*                const la_matrix *); */

la_result
la_matrix_mult_by_scalar(la_matrix **res,
                         const double scalar,
                         const la_matrix *mat)
{
  const uint rows    = mat->rows;
  const uint columns = mat->columns;

  la_result result = la_matrix_constructor(res, rows, columns);
  if (result != ok)
    return result;

  for (uint r = 0; r < rows; r++)
    for (uint c = 0; c < columns; c++)
      (*res)->data[r][c] = scalar * mat->data[r][c];

  return ok;
}
