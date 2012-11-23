/*
 * Copyright (c) 2012 Eric des Courtis <eric.des.courtis@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */


#include "erl_nif.h"

#ifdef _WIN32
#include <Windows.h>
#endif

static ERL_NIF_TERM dontcrash_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]);
static ERL_NIF_TERM crash_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]);
static int handle_upgrade(ErlNifEnv* env, void** priv_data, void** old_priv_data, ERL_NIF_TERM load_info);

static ErlNifFunc nif_funcs[] = {
    {"crash", 0, crash_nif},
    {"dontcrash", 0, dontcrash_nif}
};


static ERL_NIF_TERM crash_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{

    volatile int a = *((char *)NULL);

    return enif_make_atom(env, "ok");

}

static ERL_NIF_TERM dontcrash_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
#ifdef _WIN32
    (void)SetErrorMode(SEM_NOGPFAULTERRORBOX);
#endif
    return enif_make_atom(env, "ok");

}

static int handle_upgrade(ErlNifEnv* env, void** priv_data, void** old_priv_data, ERL_NIF_TERM load_info)
{
    return 0;
}


ERL_NIF_INIT(dontcrash, nif_funcs, NULL, NULL, handle_upgrade, NULL)
