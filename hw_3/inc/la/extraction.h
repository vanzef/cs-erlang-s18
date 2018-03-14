#pragma once

#include "la/types.h"
#include "la/constructor.h"
#include "la/utils.h"

la_result
la_extract_row_vector(la_matrix **,
                      const la_matrix *,
                      uint);

la_result
la_extract_column_vector(la_matrix **,
                         const la_matrix *,
                         uint);


/* WARNING: diagonals are vertical vectors */
la_result
la_extract_main_diagonal(la_matrix **,
                         const la_matrix *);

la_result
la_extract_antidiagonal(la_matrix **,
                        const la_matrix *);
