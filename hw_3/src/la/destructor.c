#include "la/destructor.h"

void
la_matrix_destructor(la_matrix **mat)
{
  free((*mat)->data);
  free((*mat));
}
