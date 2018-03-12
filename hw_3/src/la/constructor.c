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
  (*res)->data = malloc(rows * sizeof(double*));
  if ((*res)->data == NULL) {
    free(*res);
    return null_ptr;
  }

  //allocate memory for each row
  uint i = 0;
  bool failed = false;
  for (; i < rows; i++) {
    (*res)->data[i] = malloc(columns * sizeof(double));
    if ((*res)->data[i] == NULL) {
      failed = true;
      break;
    }
  }

  if (failed) {
    // one step back, since i-th row wasn't allocated
    i -= 1;
    for(; i < ~((uint) 0); i--)
      free((*res)->data[i]);

    free((*res)->data);
    free(*res);
    return null_ptr;
  }

  (*res)->rows    = rows;
  (*res)->columns = columns;

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
