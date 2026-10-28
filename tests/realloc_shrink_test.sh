#!/usr/bin/env bash
# Focused regression test for shrinking allocations.
set -euo pipefail
cd "$(dirname "$0")/.."
tmp="$(mktemp -d)"
trap 'rm -rf "$tmp"' EXIT
cat > "$tmp/realloc_test.c" <<'EOF'
#include "main.h"
#include <assert.h>
#include <string.h>

int main(void)
{
    char *p = malloc(16);
    char *q;
    assert(p != NULL);
    memcpy(p, "abcdefghijklmnop", 16);
    q = _realloc(p, 16, 4);
    assert(q != NULL);
    assert(memcmp(q, "abcd", 4) == 0);
    free(q);
    return 0;
}
EOF
gcc -std=gnu11 -g -O1 -fsanitize=address -fno-omit-frame-pointer \
  -I. "$tmp/realloc_test.c" mem_mngmnt_realloc.c -o "$tmp/realloc_test"
"$tmp/realloc_test"
echo "PASS: shrinking reallocation copies only destination capacity"
