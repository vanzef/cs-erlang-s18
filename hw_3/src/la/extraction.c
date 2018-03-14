#include "la/extraction.h"

static inline uint
min(uint a,
    uint b)
{
  return a < b ? a : b;
}

la_result
la_extract_row_vector (la_matrix **res,
                       const la_matrix *matrix,
                       uint row)
{
  if (row > matrix->rows)
    return dimensional_problems;

  (*res) = malloc(sizeof(la_matrix));
  if (*res == NULL)
    return null_ptr;

  (*res)->rows    = 1;
  (*res)->columns = matrix->columns;
  (*res)->data    = matrix->data
    + ((row - 1)
       * matrix->step
       * matrix->columns);
  (*res)->step    = 1;

  return ok;
}

la_result
la_extract_column_vector (la_matrix **res,
                          const la_matrix *matrix,
                          uint column)
{
  if (column > matrix->columns)
    return dimensional_problems;

  la_result result = la_copy_meta(res, matrix);
  if (result != ok)
    return result;

  (*res)->columns = 1;
  (*res)->data   += column - 1;
  (*res)->step   += matrix->columns - 1;

  return ok;
}

la_result
la_extract_main_diagonal(la_matrix **res,
                         const la_matrix *matrix)
{
  const uint boundary = min(matrix->rows, matrix->columns);

  la_result result = la_copy_meta(res, matrix);
  if (result != ok)
    return result;

  (*res)->columns = 1;
  (*res)->rows    = boundary;
  (*res)->step   += matrix->columns;

  return ok;
}

la_result
la_extract_antidiagonal(la_matrix **res,
                         const la_matrix *matrix)
{
  const uint boundary = min(matrix->rows, matrix->columns);

  la_result result = la_copy_meta(res, matrix);
  if (result != ok)
    return result;

  (*res)->columns = 1;
  (*res)->rows    = boundary;
  (*res)->data   += matrix->columns - 1;
  (*res)->step   += matrix->columns - 2;

  return ok;
}
