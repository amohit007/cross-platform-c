#ifndef CPC_CRYPTO_H
#define CPC_CRYPTO_H

#include "cpc_base.h"

#ifdef CPC_PLATFORM_WINDOWS
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
	#undef WIN32_LEAN_AND_MEAN
	#include <wincrypt.h>

	#define CPC_MD5_DIGEST_SIZE    16
	#define CPC_SHA1_DIGEST_SIZE   20
	#define CPC_SHA256_DIGEST_SIZE 32
	#define CPC_SHA512_DIGEST_SIZE 64
	
	typedef struct {
		HCRYPTPROV prov;
		HCRYPTHASH hash;
	} CPCHash;

	typedef CPCHash CPCMD5;
	typedef CPCHash CPCSHA1;
	typedef CPCHash CPCSHA256;
	typedef CPCHash CPCSHA512;
#else
	#ifdef __APPLE__
		#define COMMON_DIGEST_FOR_OPENSSL
		#include <CommonCrypto/CommonDigest.h>
		#define SHA1 CC_SHA1
	#else
		#include <openssl/md5.h>
		#include <openssl/sha1.h>
		#include <openssl/sha256.h>
		#include <openssl/sha512.h>
	#endif

	#define CPC_MD5_DIGEST_SIZE    MD5_DIGEST_LENGTH
	#define CPC_SHA1_DIGEST_SIZE   SHA1_DIGEST_LENGTH
	#define CPC_SHA256_DIGEST_SIZE SHA256_DIGEST_LENGTH
	#define CPC_SHA512_DIGEST_SIZE SHA512_DIGEST_LENGTH

	typedef MD5_CTX CPCMD5;
	typedef SHA_CTX CPCSHA1;
	typedef SHA256_CTX CPCSHA256;
	typedef SHA512_CTX CPCSHA512;
#endif

void cpc_md5_init(CPCMD5 *md5);
void cpc_md5_update(CPCMD5 *md5, const char *data, size_t data_size);
void cpc_md5_finish(CPCMD5 *md5, unsigned char *digest);

void cpc_sha1_init(CPCSHA1 *sha1);
void cpc_sha1_update(CPCSHA1 *sha1, const char *data, size_t data_size);
void cpc_sha1_finish(CPCSHA1 *sha1, unsigned char *digest);

void cpc_sha256_init(CPCSHA256 *sha256);
void cpc_sha256_update(CPCSHA256 *sha256, const char *data, size_t data_size);
void cpc_sha256_finish(CPCSHA256 *sha256, unsigned char *digest);

void cpc_sha512_init(CPCSHA512 *sha512);
void cpc_sha512_update(CPCSHA512 *sha512, const char *data, size_t data_size);
void cpc_sha512_finish(CPCSHA512 *sha512, unsigned char *digest);

#endif
