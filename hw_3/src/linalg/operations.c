#include "linalg/operations.h"

la_result
la_mult_by_scalar(la_matrix **res,
                  double scalar,
                  const la_matrix *mat)
{
  la_result result = la_matrix_new(res, mat->rows, mat->columns);
  if (result != ok)
    return result;

  ulint size = (*res)->columns * (*res)->rows;
  for (ulint i = 0; i < size; i++)
    (*res)->data[i] = scalar * mat->data[i];

  return ok;
}

la_result
la_mat_add(la_matrix **res,
           const la_matrix *left,
           const la_matrix *right)
{
  if ((left->rows != right->rows) || (left->columns != right->columns))
    return mat_size_err;

  la_result result = la_matrix_new(res, left->rows, left->columns);
  if (result != ok)
    return result;

  ulint size = (*res)->columns * (*res)->rows;
  for (ulint i = 0; i < size; i++)
    (*res)->data[i] = left->data[i] + right->data[i];

  return ok;
}
