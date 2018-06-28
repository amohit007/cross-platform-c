#ifndef CPC_CHAR_H
#define CPC_CHAR_H

#include "cpc_bool.h"
#include "cpc_base.h"

#define CPC_WHITESPACE_CHARS   " \t\n\v\f\r"
#define CPC_LOWERCASE_CHARS    "abcdefghijklmnopqrstuvwxyz"
#define CPC_UPPERCASE_CHARS    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define CPC_ALPHA_CHARS        CPC_LOWERCASE_CHARS CPC_UPPERCASE_CHARS
#define CPC_NUMERIC_CHARS      "0123456789"
#define CPC_ALPHANUMERIC_CHARS CPC_ALPHA_CHARS CPC_NUMERIC_CHARS
#define CPC_HEX_CHARS          "0123456789ABCDEF"

CPC_PURE bool cpc_is_whitespace(char c);
CPC_PURE bool cpc_is_lowercase(char c);
CPC_PURE bool cpc_is_uppercase(char c);
CPC_PURE bool cpc_is_alpha(char c);
CPC_PURE bool cpc_is_numeric(char c);
CPC_PURE bool cpc_is_alphanumeric(char c);
CPC_PURE char cpc_to_lowercase(char c);
CPC_PURE char cpc_to_uppercase(char c);
CPC_PURE bool cpc_is_hex(char c);
CPC_PURE unsigned char cpc_from_hex(char c);
CPC_PURE char cpc_to_hex(unsigned char n);

#endif
