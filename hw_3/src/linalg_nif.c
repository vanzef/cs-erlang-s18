#include "linalg_nif.h"

static ERL_NIF_TERM
hello(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]){
  return enif_make_int(env, 1);
}
