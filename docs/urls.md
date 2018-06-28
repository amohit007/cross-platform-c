[Home](https://milesbarr.github.io/cross-platform-c/)

# URLs

## Usage

Encode a URL.

```c
char encoded_url[256];
bool ok = cpc_url_encode("http://example.com", encoded_url, sizeof(encoded_url));
```

Decode a URL.

```c
char url[256];
bool ok = cpc_url_decode("http://example.com", url, sizeof(url));
```
