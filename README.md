# Simple Shell

A learning project implementing a command-line shell in C, including command lookup through `PATH`, process creation with `fork()`, execution with `execve()`, and several built-in commands.

## Build

On Linux with GCC:

```bash
gcc -std=gnu11 -Wall -Wextra -o simple_shell ./*.c
```

## Run

```bash
./simple_shell
```

You can also pipe commands into the shell:

```bash
printf 'echo hello\n' | ./simple_shell
```

## Security hardening

The `check_path.c` command lookup previously concatenated directory and command strings into a fixed-size buffer without a length check. The proposed fix uses bounded `snprintf()` and skips candidates that do not fit.

Run the regression smoke tests on Linux:

```bash
bash tests/path_lookup_smoke.sh
```

The script builds with AddressSanitizer and exercises direct commands, normal `PATH` lookup, and an oversized `PATH` entry. **These tests have been added but have not yet been executed in CI.**

## Limitations and next steps

This is an educational shell, not a hardened replacement for a production shell. Further review should cover null pointer handling, memory allocation failures, signal handling, command parsing, and environment variable processing. In particular, the path buffer remains fixed-size; excessively long candidates are skipped rather than executed.

