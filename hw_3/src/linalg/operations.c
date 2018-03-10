#include "linalg/operations.h"

la_result
la_mat_add(la_matrix **res,
           const la_matrix *left,
           const la_matrix *right)
{
  const uint rows    = left->rows;
  const uint columns = left->columns;

  if ((rows != right->rows) ||
      (columns != right->columns))
    return dimensional_problems;

  la_result result = la_matrix_new(res, rows, columns);
  if (result != ok)
    return result;

  // finally
  for (uint r = 0; r < rows; r++)
    for (uint c = 0; c < columns; c++)
      (*res)->data[r][c] = left->data[r][c] + right->data[r][c];

  return ok;
}

la_result
la_mult_by_scalar(la_matrix **res,
                  double scalar,
                  const la_matrix *mat)
{
  la_result result = la_matrix_new(res, mat->rows, mat->columns);
  if (result != ok)
    return result;

  for (uint r = 0; r < mat->rows; r++)
    for (uint c = 0; c < mat->columns; c++)
      (*res)->data[r][c] = scalar * mat->data[r][c];

  return ok;
}
