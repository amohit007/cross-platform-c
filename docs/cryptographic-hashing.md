[Home](https://milesbarr.github.io/cross-platform-c/)

# Cryptographic Hashing

The library supports MD5, SHA-1, SHA-256, and SHA-512.

## Usage

The following examples use MD5, but the other hash functions are identical in their usage.

Initialize a hash.

```c
CPCMD5 md5;
cpc_md5_init(&md5);
```

Update a hash with data.

```c
char data[] = "Hello, World!";
cpc_md5_update(&md5, data, sizeof(data));
```

Finish a hash.

```c
unsigned char digest[CPC_MD5_DIGEST_SIZE];
cpc_md5_finish(&md5, digest);
```
