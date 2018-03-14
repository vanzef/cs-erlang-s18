#include "la/constructor.h"

la_result
la_matrix_constructor(la_matrix **res,
                      const uint rows,
                      const uint columns)
{
  if (rows == 0 || columns == 0)
    return dimensional_problems;

  // allocate memory for meta-structure
  *res = malloc(sizeof(la_matrix));
  if (*res == NULL)
    return null_ptr;

  // allocater memory for array of pointers to rows
  (*res)->data = malloc(rows * columns * sizeof(double));
  if ((*res)->data == NULL) {
    free(*res);
    return null_ptr;
  }

  (*res)->rows    = rows;
  (*res)->columns = columns;
  /* (*res)->offset  = 0; */
  (*res)->step    = 1;

  return ok;
}

la_result
la_vertical_vector_constructor(la_matrix **res,
                               const uint rows)
{
  return la_matrix_constructor(res, rows, 1);
}

la_result
la_horizontal_vector_constructor(la_matrix **res,
                                 const uint columns)
{
  return la_matrix_constructor(res, 1, columns);
}

la_result
la_copy_meta(la_matrix **res,
             const la_matrix *matrix)
{
  (*res) = malloc(sizeof(la_matrix));
  if (*res == NULL)
    return null_ptr;


  (*res)->rows    = matrix->rows;
  (*res)->columns = matrix->columns;
  (*res)->data    = matrix->data;
  /* (*res)->offset  = matrix->offset; */
  (*res)->step    = matrix->step;

  return ok;
}
