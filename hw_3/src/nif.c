#include "nif.h"
#include <stdio.h>

int
load(ErlNifEnv *env,
     void **priv_data,
     ERL_NIF_TERM load_info)
{
  int flags = ERL_NIF_RT_CREATE | ERL_NIF_RT_TAKEOVER;
  if ((LA_MATRIX_TYPE = enif_open_resource_type(env,
                                                NULL,
                                                "matrix",
                                                nif_matrix_destructor,
                                                flags,
                                                NULL))
      == NULL)
    return 1;
  return 0;
}
