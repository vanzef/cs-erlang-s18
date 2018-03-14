#pragma once

#include "la/types.h"
#include <stdlib.h>
#include <stdbool.h>

la_result
la_matrix_constructor(la_matrix **,
                      const uint,
                      const uint);

la_result
la_vertical_vector_constructor(la_matrix **,
                               const uint);

la_result
la_horizontal_vector_constructor(la_matrix **,
                                 const uint);

la_result
la_copy_meta(la_matrix **,
             const la_matrix *);
