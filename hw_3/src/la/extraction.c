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
  if ((row > matrix->rows) || row == 0)
    return dimensional_problems;

  la_result result = la_horizontal_vector_constructor(res, matrix->columns);
  if (result != ok)
    return result;

  (*res)->data[0] = matrix->data[row - 1];
  return ok;
}

la_result
la_extract_column_vector (la_matrix **res,
                          const la_matrix *matrix,
                          uint column)
{
  if ((column > matrix->columns) || (column == 0))
    return dimensional_problems;

  la_result result = la_vertical_vector_constructor(res, matrix->rows);
  if (result != ok)
    return result;

  for (uint i = 0; i < matrix->rows; i++)
    (*res)->data[i] = matrix->data[i] + (column - 1);

  return ok;
}


la_result
la_extract_main_diagonal(la_matrix **res,
                         const la_matrix *matrix)
{
  uint boundary = min(matrix->rows, matrix->columns);
  la_result result = la_vertical_vector_constructor(res, boundary);
  if (result != ok)
    return result;

  for (uint i = 0; i < boundary; i++)
    (*res)->data[i] = matrix->data[i] + i;

  return ok;
}

la_result
la_extract_antidiagonal(la_matrix **res,
                        const la_matrix *matrix)
{
  uint boundary = min(matrix->rows, matrix->columns);
  la_result result = la_vertical_vector_constructor(res, boundary);
  if (result != ok)
    return result;

  for (uint i = 0; i < boundary; i++)
    (*res)->data[i] = matrix->data[i] + (boundary - 1) - i;

  return ok;
}

