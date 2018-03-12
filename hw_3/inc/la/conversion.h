#pragma once

#include "la/types.h"
#include "la/constructor.h"
#include <stdlib.h>

la_result
la_from_array(la_matrix **,
              const double *,
              const uint,
              const uint);

la_result
la_to_array(double **,
            const la_matrix *);
