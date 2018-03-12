#pragma once

#include "la/types.h"
#include "la/constructor.h"

la_result
la_matrix_sum(la_matrix **,
              const la_matrix *,
              const la_matrix *);

la_result
la_matrix_mult(la_matrix **,
               const la_matrix *,
               const la_matrix *);

la_result
la_matrix_mult_by_scalar(la_matrix **,
                         const double,
                         const la_matrix *);
