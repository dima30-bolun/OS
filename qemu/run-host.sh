#!/usr/bin/env sh
set -eu
make
exec ./out/bolun-host
