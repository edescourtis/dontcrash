-module(dontcrash).

-on_load(load_nif/0).

-export([dontcrash/0, crash/0]).

%% -------------------------------------------------------------------------
%% API
%% -------------------------------------------------------------------------
-spec dontcrash() -> ok.
dontcrash() ->
    erlang:nif_error(not_loaded).

-spec crash() -> ok.
crash() ->
    erlang:nif_error(not_loaded).

%% -------------------------------------------------------------------------
%% on_load callback
%% -------------------------------------------------------------------------

load_nif() ->
    erlang:load_nif(filename:join(code:priv_dir(dontcrash), "dontcrash"), 0).
