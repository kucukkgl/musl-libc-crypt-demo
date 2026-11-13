# musl crypt() Password Length Test

A simple test program for evaluating how the musl libc implementation of `crypt()` behaves when given increasingly long passwords.

The purpose of this test is to determine whether musl's `crypt()` implementation returns an error value (typically beginning with `*`) when processing passwords beyond a certain length, such as 256 bytes.

## Test Environment

- Ubuntu VM
- musl libc built from source
- musl installed under `/usr/local/musl`

## Building musl

Clone musl:

```bash
git clone https://git.musl-libc.org/git/musl
cd musl
```

Build and install:

```bash
./configure
make
sudo make install
```

After installation, the musl compiler wrapper should be available at:

```text
/usr/local/musl/bin/musl-gcc
```

## Compile the Test

```bash
/usr/local/musl/bin/musl-gcc -static test.c -o test
```

## Run

```bash
./test
```

## What the Test Does

The program:

1. Creates passwords consisting entirely of the character `A`.
2. Tests password lengths from 1 to 4095 bytes.
3. Uses the SHA-512 crypt format (`$6$salt$`).
4. Calls musl's `crypt()` function for each password length.
5. Checks whether:
   - `crypt()` returns `NULL`, or
   - the returned string begins with `*`, which historically indicates an error condition.
6. Stops when the first failure is detected.

## Example Output

Successful test:

```text
No failure up to 4095 bytes
```

Failure example:

```text
FAILED at len=257: *0
```

## Why Use `$6$salt$`?

The prefix selects the hashing algorithm:

| Prefix | Algorithm |
|----------|----------|
| `$1$` | MD5 |
| `$5$` | SHA-256 |
| `$6$` | SHA-512 |

This test uses SHA-512 (`$6$`).

## Verify the Binary

```bash
file test
```

Expected output:

```text
test: ELF 64-bit LSB executable, x86-64, statically linked
```

This ensures the executable is using the locally built musl implementation rather than the host system's glibc or libxcrypt libraries.

## Repository Structure

```text
.
├── README.md
└── test.c
```

## License

This repository is provided for testing and research purposes.
