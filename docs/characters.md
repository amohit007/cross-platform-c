[Home](https://milesbarr.github.io/cross-platform-c/)

# Characters

These functions are similar to those in the C standard library, however they offer a consistent interface and can be inlined by the compiler.

## Usage

Character sets:

```c
CPC_WHITESPACE_CHARS
CPC_LOWERCASE_CHARS
CPC_UPPERCASE_CHARS
CPC_ALPHA_CHARS
CPC_NUMERIC_CHARS
CPC_ALPHANUMERIC_CHARS
CPC_HEX_CHARS
```

Check if a character is whitespace.

```c
bool is_whitespace = cpc_is_whitespace(c);
```

Check if a character is lowercase.

```c
bool is_lowercase = cpc_is_lowercase(c);
```

Check if a character is uppercase.

```c
bool is_uppercase = cpc_is_uppercase(c);
```

Check if a character is a letter.

```c
bool is_alpha = cpc_is_alpha(c);
```

Check if a character is numeric.

```c
bool is_numeric = cpc_is_numeric(c);
```

Check if a character is alphanumeric.

```c
bool is_alphanumeric = cpc_is_alphanumeric(c);
```

Convert a character to lowercase.

```c
char lowercase_char = cpc_to_lowercase(c);
```

Convert a character to uppercase.

```c
char uppercase_char = cpc_to_uppercase(c);
```

Check if a character is hex.

```c
bool is_hex = cpc_is_hex(c);
```

Convert a hex character to a number.

```c
unsigned char n = cpc_from_hex(c);
```

Convert a number to a hex character.

```c
char hex_char = cpc_to_hex(n);
```
