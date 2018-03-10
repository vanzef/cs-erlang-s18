#include "linalg_nif.h"

void dosmth() {
  printf("DO SMTHNG!\n");
}

static ERL_NIF_TERM
hello(ErlNifEnv *env,
      int argc,
      const ERL_NIF_TERM argv[])
{
  return enif_make_int(env, 1);
}
