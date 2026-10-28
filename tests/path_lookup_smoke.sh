#!/usr/bin/env bash
# Regression smoke tests for command lookup, including oversized PATH entries.
set -euo pipefail
cd "$(dirname "$0")/.."
workdir="$(mktemp -d)"
trap 'rm -rf "$workdir"' EXIT

# Build with AddressSanitizer to catch memory errors during these tests.
gcc -std=gnu11 -g -O1 -fsanitize=address -fno-omit-frame-pointer \
  -o "$workdir/simple_shell" ./*.c

printf '/bin/echo lookup-ok\n' | "$workdir/simple_shell" >"$workdir/direct.out"
grep -q '^lookup-ok$' "$workdir/direct.out"

printf 'echo lookup-ok\n' | PATH=/bin "$workdir/simple_shell" >"$workdir/path.out"
grep -q '^lookup-ok$' "$workdir/path.out"

# A PATH directory longer than the old 256-byte static buffer must not
# overwrite memory. A valid later PATH directory should still be searched.
long_dir="$(printf 'x%.0s' {1..400})"
printf 'echo lookup-ok\n' | PATH="$long_dir:/bin" \
  "$workdir/simple_shell" >"$workdir/long-path.out"
grep -q '^lookup-ok$' "$workdir/long-path.out"

echo "PASS: path lookup smoke tests"
