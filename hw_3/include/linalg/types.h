#pragma once

typedef unsigned int uint;
typedef unsigned long int ulint;

typedef enum la_result {
  null_ptr,
  mat_size_err,
  mem_err,
  ok,
} la_result;

typedef struct la_matrix {
  uint columns, rows;
  double *data;
} la_matrix;

