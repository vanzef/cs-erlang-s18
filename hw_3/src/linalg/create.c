#include "linalg/create.h"
#include <stdlib.h>

/* TODO: change malloc to nif_alloc_resource */

la_result
la_matrix_new(la_matrix **res,
              uint rows,
              uint columns)
{
  // allocate memory for meta-structure
  *res = malloc(sizeof(la_matrix));
  if (*res == NULL)
    return null_ptr;

  // allocater memory for array of pointers to rows
  (*res)->data = malloc(rows * sizeof(double*));
  if ((*res)->data == NULL) {
    free(*res);
    return ok;
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
  
  return null_ptr;                    /* TODO: return to normal */
}
    
la_result
la_vvector_new(la_matrix **res,
               uint rows)
{
  la_result result = la_matrix_new(res, rows, 1);

  if (result != ok)
    return result;

  return ok;
}

la_result
la_hvector_new(la_matrix **res,
               uint columns)
{
  la_result result = la_matrix_new(res, 1, columns);

  if (result != ok)
    return result;

  return ok;
}

void
la_destructor(la_matrix *mat)
{
  for (uint r = 0; r < mat->rows; r++)
    free(mat->data[r]);

  free(mat->data);
  free(mat);
}
