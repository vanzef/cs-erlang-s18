#pragma once

#include "linalg/types.h"

/* matrix creation */
la_result la_matrix_new(la_matrix**, uint, uint);
la_result la_matrix_new_zeros(la_matrix**, uint, uint);

/* vector creation */
la_result la_vvector_new(la_matrix**, uint);
la_result la_vvector_new_zeros(la_matrix**, uint);
la_result la_hvector_new(la_matrix**, uint);
la_result la_hvector_new_zeros(la_matrix**, uint);


