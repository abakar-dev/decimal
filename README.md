# s21_decimal

![C Language](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![School21](https://img.shields.io/badge/School21-000000?style=for-the-badge)
![Decimal](https://img.shields.io/badge/decimal-arithmetic-blue?style=for-the-badge)
![Precision](https://img.shields.io/badge/precision-financial-green?style=for-the-badge)
![CI](https://github.com/abakar-dev/s21-decimal/workflows/CI/badge.svg)
![Tests](https://img.shields.io/badge/tests-80%25%20coverage-green?style=for-the-badge)
![License](https://img.shields.io/badge/license-MIT-blue?style=for-the-badge)
![Platform](https://img.shields.io/badge/platform-Linux%20%7C%20macOS-lightgrey?style=for-the-badge)
![Version](https://img.shields.io/badge/version-v1.0.0-orange?style=for-the-badge)
![128-bit](https://img.shields.io/badge/128--bit-data%20type-purple?style=for-the-badge)

High-precision decimal arithmetic library for exact financial calculations in C.

## Description

Custom implementation of `decimal` data type for financial computations with out floating-point errors. Provides 128-bit decimal arithmetic with exact precision. Developed as part of **School 21** programming curriculum.

## Features

- **128-bit decimal representation**: 96-bit integer + scaling factor
- **Exact arithmetic**: addition, subtraction, multiplication, division
- **Full comparison operators**: <, >, <=, >=, ==, !=
- **Type conversions**: decimal <--> int <--> float
- **Mathematical functions**: floor, round, truncate, negate
- **Banker's rounding**: financial standard compliance
- **Range**: -(+)79,228,162,514,264,337,593,543,950,335
- **Memory safe**: no memory leaks

## Project Structure

```src/
- s21_decimal.h          # The main header file
- arithmetic.c           # +, -, *, / operations
- comparison.c           # Comparison operators
- convertors.c           # Type conversions
- otherFun.c             # Additional functions
- additionalFunc.c       # Helper functions
- checker.c              # Validation functions
- getAndSet.c            # Bit manipulation
- Makefile               # Build configuration
- tests/                 # Unit tests
       - main.c              # The main test file/ running tests
       - s21_decimal_test.h  # Test header file
       - other_test.c        # Other function tests
       - Makefile            # Tests build file
       - arithmetic/         # Arithmetic tests
```

## Build and Usage

### Compile library

```bash
cd src
make s21_decimal.a
```

### Run tests

```bash
cd src
make test
```

### Generate coverage report

```bash
cd src
make gcov_report
```

## Functions

### Arithmetic Operations

- `s21_add` - addition
- `s21_sub` - subtraction
- `s21_mul` - multiplication
- `s21_div` - division

### Comparison Operators

- `s21_is_less`, `s21_is_greater`, `s21_is_equal`, `s21_is_not_equal`
- `s21_is_less_or_equal`, `s21_is_greater_or_equal`

### Convertors

- `s21_from_int_to_decimal`, `s21_from_float_to_decimal`
- `s21_from_decimal_to_int`, `s21_from_decimal_to_float`

### Other Functions

- `s21_floor`, `s21_round`, `s21_truncate`, `s21_negate`

## Testing

Comprehensive unit test coverage using Check library. Tests cover:

- All arithmetic operations with edge cases
- Type conversion accuracy
- Comparison operators
- Special values and error conditions

### Test Structure

```tests/
- main.c                # The main test file
- Makefile              # Tests build file
- other_test.c          # Other functions tests
- s21_decimal_test.h    # The main test header file
- arithmetic/           # Arithmetic tests
     - add_test.c       # Addition tests
     - sub_test.c       # Subtraction tests
     - mul_test.c       # Multiplication tests
     - div_test.c       # Division tests
```

## Code Requirements

- Language standard: **C11**
- Compiler: **gcc**
- Code style: **Google C Style**
- Principles: **Structured programming**
- Test coverage: **> or = 80% per function**

## Project Information

- **Educational institution**: School 21
- **Track**: C Programming
- **Project**: s21_decimal (High-precision decimal arithmetic)
- **Author**: cadwynga

## License

MIT License - see [LICENSE] (LICENSE) file for details.

---

*Educational project developed for learning purposes.*
