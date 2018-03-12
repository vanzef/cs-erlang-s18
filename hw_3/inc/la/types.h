#pragma once

typedef unsigned int uint;
typedef unsigned long int ulint;

typedef enum la_result {
  ok,
  null_ptr,
  dimensional_problems,
} la_result;

typedef struct la_matrix {
  uint rows, columns;
  double **data;
} la_matrix;
