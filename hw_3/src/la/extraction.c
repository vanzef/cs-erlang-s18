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
  if (row > la_dim_rows(matrix))
    return dimensional_problems;

  (*res) = malloc(sizeof(la_matrix));
  if (*res == NULL)
    return null_ptr;

  (*res)->rows    = 1;
  (*res)->columns = la_dim_columns(matrix);
  (*res)->data    = matrix->data + matrix->offset
    + ((row - 1)
       * matrix->step
       * la_dim_columns(matrix));
  (*res)->offset  = 0;          /* see the commentary in la/utils.c */
  (*res)->step    = 1;          /* same as above */

  return ok;
}

la_result
la_extract_column_vector (la_matrix **res,
                          const la_matrix *matrix,
                          uint column)
{
  /* TODO */
  if (column > la_dim_columns(matrix))
    return dimensional_problems;

  la_result result = la_copy_meta(res, matrix);
  if (result != ok)
    return result;

  (*res)->offset  = matrix->offset + column - 1;
  (*res)->step    = matrix->step + la_dim_columns(matrix) - 1;

  return ok;
}

la_result
la_extract_main_diagonal(la_matrix **res,
                         const la_matrix *matrix)
{
  const uint boundary = min(la_dim_rows(matrix), la_dim_columns(matrix));

  la_result result = la_copy_meta(res, matrix);
  if (result != ok)
    return result;

  (*res)->rows    = boundary;
  (*res)->step    = matrix->step + la_dim_columns(matrix);

  return ok;
}

/* TODO */
la_result
la_extract_antidiagonal(la_matrix **res,
                         const la_matrix *matrix)
{
  const uint boundary = min(la_dim_rows(matrix), la_dim_columns(matrix));

  la_result result = la_copy_meta(res, matrix);
  if (result != ok)
    return result;

  (*res)->rows    = boundary;
  (*res)->offset  = matrix->offset + la_dim_columns(matrix) - 1;
  (*res)->step    = matrix->step + la_dim_columns(matrix) - 2;

  return ok;
}
