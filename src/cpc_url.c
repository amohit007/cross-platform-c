#include "cpc_url.h"

#ifdef CPC_PLATFORM_WINDOWS
	#include <Shlwapi.h>

	CPC_CHECK_RETURN bool cpc_url_encode(const char *restrict url, char *restrict encoded_url, size_t encoded_url_size) {
		CPC_ASSERT(url != NULL);
		CPC_ASSERT(encoded_url != NULL);
		CPC_ASSERT(!(encoded_url <= url && url < encoded_url + encoded_url_size));

		CPC_ASSERT(encoded_url_size <= MAXDWORD);
		DWORD tmp_encoded_url_size = (DWORD)encoded_url_size;
		HRESULT result = UrlEscape(url, encoded_url, &tmp_encoded_url_size, URL_ESCAPE_ASCII_URI_COMPONENT | URL_ESCAPE_PERCENT);
		return result == S_OK;
	}

	CPC_CHECK_RETURN bool cpc_url_decode(const char *encoded_url, char *url, size_t url_size) {
		CPC_ASSERT(encoded_url != NULL);
		CPC_ASSERT(url != NULL);
		CPC_ASSERT(!(url <= encoded_url && encoded_url < url + url_size));

		CPC_ASSERT(url_size <= MAXDWORD);
		DWORD tmp_url_size = (DWORD)url_size;
		HRESULT result = UrlUnescape((char *)(UINT_PTR)encoded_url, url, &tmp_url_size, 0);
		return result == S_OK;
	}
#else
	#include "cpc_char.h"

	CPC_CHECK_RETURN bool cpc_url_encode(const char *restrict url, char *restrict encoded_url, size_t encoded_url_size) {
		CPC_ASSERT(encoded_url != NULL);
		CPC_ASSERT(url != NULL);
		CPC_ASSERT(!(encoded_url <= url && url < encoded_url + encoded_url_size));

		while (*url != '\0') {
			if (cpc_is_alphanumeric(*url) | (*url == '-') | (*url == '.') | (*url == '~') | (*url == '_')) {
				if (encoded_url_size < 2) return false;
				*encoded_url = *url;
				encoded_url++;
				encoded_url_size--;
			} else {
				if (encoded_url_size < 4) return false;
				encoded_url[0] = '%';
				encoded_url[1] = cpc_to_hex((unsigned char)*url >> 4);
				encoded_url[2] = cpc_to_hex(*url & 15);
				encoded_url += 3;
				encoded_url_size -= 3;
			}
			url++;
		}
		*encoded_url = '\0';
		return true;
	}

	CPC_CHECK_RETURN bool cpc_url_decode(const char *restrict encoded_url, char *restrict url, size_t url_size) {
		CPC_ASSERT(encoded_url != NULL);
		CPC_ASSERT(url != NULL);
		CPC_ASSERT(!(url <= encoded_url && encoded_url < url + url_size));

		while (*encoded_url != '\0') {
			if (url_size < 2) return false;
			if (*encoded_url == '%') {
				if (CPC_UNLIKELY(!cpc_is_hex(encoded_url[1]) | !cpc_is_hex(encoded_url[2]))) return false;
				*url = (char)((cpc_from_hex(encoded_url[1] & 0xF) << 4) | cpc_from_hex(encoded_url[2] & 0xF));
				encoded_url += 2;
			} else if (*encoded_url == '+') { 
				*url = ' ';
			} else {
				*url = *encoded_url;
			}
			url++;
			encoded_url++;
			url_size--;
		}
		*url = '\0';
		return true;
	}
#endif
