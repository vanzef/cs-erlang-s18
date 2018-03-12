#include "la/destructor.h"

void
la_matrix_destructor(la_matrix **mat)
{
  for (uint r = 0; r < (*mat)->rows; r++)
    free((*mat)->data[r]);

  free((*mat)->data);
  free((*mat));
}
