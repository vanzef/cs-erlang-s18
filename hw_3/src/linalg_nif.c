#include "linalg_nif.h"

void
nif_destructor(ErlNifEnv *env,
               void *res)
{
  la_destructor((la_matrix *) res);
}
  
int
load(ErlNifEnv* env,
     void** priv_data,
     ERL_NIF_TERM load_info)
{
  int flags = ERL_NIF_RT_CREATE | ERL_NIF_RT_TAKEOVER;
  MATRIX_TYPE = enif_open_resource_type(env, NULL, "matrix",
                                        nif_destructor, flags, NULL);
  return 0;                     /* WHAA?? */
}


static ERL_NIF_TERM
nif_la_matrix_new(ErlNifEnv *env,
                  int argc,
                  const ERL_NIF_TERM argv[])
{
  uint rows, columns;
  enif_get_uint(env, argv[0], &rows);
  enif_get_uint(env, argv[1], &columns);

  // some strange mem biz here (つ˵•́ω•̀˵)つ━☆ﾟ.*･｡ﾟ҉̛༽̨҉҉ﾉ
  la_matrix **mat_p = enif_alloc_resource(MATRIX_TYPE, sizeof(la_matrix *));
  
  la_result result = la_matrix_new(mat_p, rows, columns);
  if (result != ok) {
    enif_release_resource(mat_p); /* (★━━━…‥*：･o(ﾟﾛﾟヽ) */
    return enif_make_atom(env, "err");
  }

  ERL_NIF_TERM term = enif_make_resource(env, mat_p);
  enif_release_resource(mat_p);

  return term;
  /* return enif_make_int(env, 1); */
}
