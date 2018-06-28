[Home](https://milesbarr.github.io/cross-platform-c/)

# Math

## Usage

Check if an integer is a power of two.

```c
bool power_of_two = CPC_IS_POWER_OF_TWO(x);
```

Set a bit in an integer.

```c
unsigned int x = 0;
x = CPC_SET_BIT(x, 0);
```

Unset a bit in an integer.

```c
unsigned int x = 1;
x = CPC_UNSET_BIT(x, 0);
```

Toggle a bit in an integer.

```c
unsigned int x = 0;
x = CPC_TOGGLE_BIT(x, 0);
```

Check if an integer is even.

```c
bool even = CPC_IS_EVEN(0);
```

Check if an integer is odd.

```c
bool odd = CPC_IS_ODD(0);
```

Take the absolute value of an integer.

```c
int x = -1;
x = CPC_ABS(x);
```

Check if two integers have the same sign.

```c
bool same_sign = CPC_IS_SAME_SIGN(-1, 1);
```

Take the inverse square root of a number.

```c
float x = cpc_inv_sqrt(x);
```

Raise a number to a power.

```c
float x = cpc_pow(base, exp);
```
