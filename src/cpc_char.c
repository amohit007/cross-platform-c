#include "cpc_char.h"

CPC_PURE bool cpc_is_whitespace(char c) {
	return (c == ' ') | (c == '\t') | (c == '\n') | (c == '\v') | (c == '\f') | (c == '\r');
}

CPC_PURE bool cpc_is_lowercase(char c) {
	return ('a' <= c) & (c <= 'z');
}

CPC_PURE bool cpc_is_uppercase(char c) {
	return ('A' <= c) & (c <= 'Z');
}

CPC_PURE bool cpc_is_alpha(char c) {
	return cpc_is_lowercase(c) | cpc_is_uppercase(c);
}

CPC_PURE bool cpc_is_numeric(char c) {
	return ('0' <= c) & (c <= '9');
}

CPC_PURE bool cpc_is_alphanumeric(char c) {
	return cpc_is_alpha(c) | cpc_is_numeric(c);
}

CPC_PURE char cpc_to_lowercase(char c) {
	return c + cpc_is_uppercase(c) * ('a' - 'A');
}

CPC_PURE char cpc_to_uppercase(char c) {
	return c - cpc_is_lowercase(c) * ('a' - 'A');
}

CPC_PURE bool cpc_is_hex(char c) {
	return cpc_is_numeric(c) | (('A' <= c) & (c <= 'F')) | (('a' <= c) & (c <= 'f'));
}

CPC_PURE unsigned char cpc_from_hex(char c) {
	CPC_ASSERT(cpc_is_hex(c));
	return (unsigned char)c - '0' - ((c >= 'A') * ('A' - '0')) - ((c >= 'a') * ('a' - 'A'));
}

CPC_PURE char cpc_to_hex(unsigned char n) {
	CPC_ASSERT(n < 16);
	return CPC_HEX_CHARS[n];
}
