#pragma once

#include "linalg/types.h"
#include "linalg/create.h"

/* operations with matrices (and vectors) */
la_result la_mat_mult(la_matrix**, const la_matrix*, const la_matrix*);
la_result la_mat_add(la_matrix**, const la_matrix*, const la_matrix*);

/* operations with matrices and scalars */
la_result la_mult_by_scalar(la_matrix**, double, const la_matrix*);


