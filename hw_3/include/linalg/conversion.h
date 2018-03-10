#pragma once

#include "linalg/types.h"
#include "linalg/create.h"

/* conversion from/to array */
la_result la_from_array(la_matrix**, uint, uint, const double*);
la_result la_to_array(double**, const la_matrix*);

