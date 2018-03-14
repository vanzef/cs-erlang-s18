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

  for (uint i = 0; i < rows * columns; i++)
    (*res)->data[i] = left->data[i * left->step]
      + right->data[i * right->step];

  return ok;
}

la_result
la_matrix_mult(la_matrix **res,
               const la_matrix *left,
               const la_matrix *right)
{
  const uint lrows    = left->rows;
  const uint lcolumns = left->columns;
  const uint rrows    = right->rows;
  const uint rcolumns = right->columns;

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
        tmp += left->data[r * left->columns * left->step + i * left->step]
          * right->data[i * left->columns * left->step + c * left->step];

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
  const uint rows    = mat->rows;
  const uint columns = mat->columns;

  la_result result = la_matrix_constructor(res, rows, columns);
  if (result != ok)
    return result;

  for (uint i = 0; i < rows * columns; i++)
    (*res)->data[i] = scalar
      * mat->data[i * mat->step];

  return ok;
}
