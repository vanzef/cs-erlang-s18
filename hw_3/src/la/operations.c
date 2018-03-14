#include "la/operations.h"

la_result
la_matrix_sum(la_matrix **res,
              const la_matrix *left,
              const la_matrix *right)
{
  const uint rows    = la_dim_rows(left);
  const uint columns = la_dim_columns(left);
  if ((rows != la_dim_rows(right)) || (columns != la_dim_columns(right)))
    return dimensional_problems;

  la_result result = la_matrix_constructor(res, rows, columns);
  if (result != ok)
    return result;

  for (uint i = 0; i < rows * columns; i++)
    (*res)->data[i] = left->data[left->offset + i * left->step]
      + right->data[right->offset + i * right->step];

  return ok;
}

la_result
la_matrix_mult(la_matrix **res,
               const la_matrix *left,
               const la_matrix *right)
{
  const uint lrows = la_dim_rows(left);
  const uint lcolumns = la_dim_columns(left);
  const uint rrows = la_dim_rows(right);
  const uint rcolumns = la_dim_columns(right);

  if (lcolumns != rrows)
    return dimensional_problems;

  const uint rows    = lrows;
  const uint columns = rcolumns;

  la_result result = la_matrix_constructor(res, rows, columns);
  if (result != ok)
    return result;

  for (uint r = 0; r < rows; r++) {
    for (uint c = 0; c < columns; c++) {
      double tmp = 0;
      for (uint i = 0; i < lcolumns; i++)
        tmp = 0;                /* TODO */
        /* tmp += left->data[r][i] */
        /*   * right->data[i][c]; */

      (*res)->data[r * columns + c] = tmp;
    }
  }

  return ok;
}

la_result
la_matrix_mult_by_scalar(la_matrix **res,
                         const double scalar,
                         const la_matrix *mat)
{
  const uint rows    = la_dim_rows(mat);
  const uint columns = la_dim_columns(mat);

  la_result result = la_matrix_constructor(res, rows, columns);
  if (result != ok)
    return result;

  for (uint i = 0; i < rows * columns; i++)
    (*res)->data[i] = scalar
      * mat->data[mat->offset + i * mat->step];

  return ok;
}
