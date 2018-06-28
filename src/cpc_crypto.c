#include "cpc_crypto.h"

#ifdef CPC_PLATFORM_WINDOWS
	#include <wincrypt.h>

	CPC_ALWAYS_INLINE static void cpc_hash_init(CPCHash *hash, DWORD prov_type, ALG_ID algo) {
		CPC_ASSERT(hash != NULL);
		
		BOOL result = CryptAcquireContext(&hash->prov, NULL, NULL, prov_type, 0);
		CPC_ASSERT(result);
		
		result = CryptCreateHash(hash->prov, algo, 0, 0, &hash->hash);
		CPC_ASSERT(result);
	}
	
	CPC_ALWAYS_INLINE static void cpc_hash_update(CPCHash *hash, const void *data, size_t data_size) {
		CPC_ASSERT(hash != NULL);
		CPC_ASSERT(data != NULL || data_size == 0);
		
		CPC_ASSERT(data_size <= MAXDWORD);
		BOOL result = CryptHashData(hash->hash, data, (DWORD)data_size, 0);
		CPC_ASSERT(result);
	}

	CPC_ALWAYS_INLINE static void cpc_hash_finish(CPCHash *hash, unsigned char *digest, size_t digest_size) {
		CPC_ASSERT(hash != NULL);
		CPC_ASSERT(digest != NULL);
		
		CPC_ASSERT(digest_size <= MAXDWORD);
		DWORD tmp_digest_size = (DWORD)digest_size;
		BOOL result = CryptGetHashParam(hash->hash, HP_HASHVAL, digest, &tmp_digest_size, 0);
		CPC_ASSERT(result);
		
		result = CryptDestroyHash(hash->hash);
		CPC_ASSERT(result);

		result = CryptReleaseContext(hash->prov, 0);
		CPC_ASSERT(result);
	}

	void cpc_md5_init(CPCMD5 *md5) {
		CPC_ASSERT(md5 != NULL);
		cpc_hash_init(md5, PROV_RSA_FULL, CALG_MD5);
	}

	void cpc_md5_update(CPCMD5 *md5, const char *data, size_t data_size) {
		CPC_ASSERT(md5 != NULL);
		CPC_ASSERT(data != NULL || data_size == 0);
		cpc_hash_update(md5, data, data_size);
	}

	void cpc_md5_finish(CPCMD5 *md5, unsigned char *digest) {
		CPC_ASSERT(md5 != NULL);
		CPC_ASSERT(digest != NULL);
		cpc_hash_finish(md5, digest, CPC_MD5_DIGEST_SIZE);
	}

	void cpc_sha1_init(CPCSHA1 *sha1) {
		CPC_ASSERT(sha1 != NULL);
		cpc_hash_init(sha1, PROV_RSA_AES, CALG_SHA1);
	}

	void cpc_sha1_update(CPCSHA1 *sha1, const char *data, size_t data_size) {
		CPC_ASSERT(sha1 != NULL);
		CPC_ASSERT(data != NULL || data_size == 0);
		cpc_hash_update(sha1, data, data_size);
	}

	void cpc_sha1_finish(CPCSHA1 *sha1, unsigned char *digest) {
		CPC_ASSERT(sha1 != NULL);
		CPC_ASSERT(digest != NULL);
		cpc_hash_finish(sha1, digest, CPC_SHA1_DIGEST_SIZE);
	}

	void cpc_sha256_init(CPCSHA256 *sha256) {
		CPC_ASSERT(sha256 != NULL);
		cpc_hash_init(sha256, PROV_RSA_AES, CALG_SHA_256);
	}

	void cpc_sha256_update(CPCSHA256 *sha256, const char *data, size_t data_size) {
		CPC_ASSERT(sha256 != NULL);
		CPC_ASSERT(data != NULL || data_size == 0);
		cpc_hash_update(sha256, data, data_size);
	}

	void cpc_sha256_finish(CPCSHA256 *sha256, unsigned char *digest) {
		CPC_ASSERT(sha256 != NULL);
		CPC_ASSERT(digest != NULL);
		cpc_hash_finish(sha256, digest, CPC_SHA256_DIGEST_SIZE);
	}

	void cpc_sha512_init(CPCSHA512 *sha512) {
		CPC_ASSERT(sha512);
		cpc_hash_init(sha512, PROV_RSA_AES, CALG_SHA1);
	}

	void cpc_sha512_update(CPCSHA512 *sha512, const char *data, size_t data_size) {
		CPC_ASSERT(sha512);
		CPC_ASSERT(data != NULL || data_size == 0);
		cpc_hash_update(sha512, data, data_size);
	}

	void cpc_sha512_finish(CPCSHA512 *sha512, unsigned char *digest) {
		CPC_ASSERT(sha512);
		CPC_ASSERT(digest != NULL);
		cpc_hash_finish(sha512, digest, CPC_SHA512_DIGEST_SIZE);
	}
#else
	void cpc_md5_init(CPCMD5 *md5) {
		CPC_ASSERT(ms5);
		int result = MD5_Init(md5);
		CPC_ASSERT(result == 1);
	}

	void cpc_md5_update(CPCMD5 *md5, const char *data, size_t data_size) {
		CPC_ASSERT(md5 != NULL);
		CPC_ASSERT(data != NULL || data_size == 0);
		int result = MD5_Update(md5, data, data_size);
		CPC_ASSERT(result == 1);
	}

	void cpc_md5_finish(CPCMD5 *md5, unsigned char *digest) {
		CPC_ASSERT(md5 != NULL);
		CPC_ASSERT(digest != NULL);
		int result = MD5_Final(digest, md5);
		CPC_ASSERT(result == 1);
	}

	void cpc_sha1_init(CPCSHA1 *sha1) {
		CPC_ASSERT(sha1 != NULL);
		int result = SHA1_Init(sha1);
		CPC_ASSERT(result == 1);
	}

	void cpc_sha1_update(CPCSHA1 *sha1, const char *data, size_t data_size) {
		CPC_ASSERT(sha1 != NULL);
		CPC_ASSERT(data != NULL || data_size == 0);
		int result = SHA1_Update(sha1, data, data_size);
		CPC_ASSERT(result == 1);
	}

	void cpc_sha1_finish(CPCSHA1 *sha1, unsigned char *digest) {
		CPC_ASSERT(sha1 != NULL);
		CPC_ASSERT(digest != NULL);
		int result = SHA1_Final(digest, sha1);
		CPC_ASSERT(result == 1);
	}

	void cpc_sha256_init(CPCSHA256 *sha256) {
		CPC_ASSERT(sha256 != NULL);
		int result = SHA256_Init(sha256);
		CPC_ASSERT(result == 1);
	}

	void cpc_sha256_update(CPCSHA256 *sha256, const char *data, size_t data_size) {
		CPC_ASSERT(sha256 != NULL);
		CPC_ASSERT(data != NULL || data_size == 0);
		int result = SHA256_Update(sha256, data, data_size);
		CPC_ASSERT(result == 1);
	}

	void cpc_sha256_finish(CPCSHA256 *sha256, unsigned char *digest) {
		CPC_ASSERT(sha256 != NULL);
		CPC_ASSERT(digest != NULL);
		int result = SHA256_Final(digest, sha256);
		CPC_ASSERT(result == 1);
	}

	void cpc_sha512_init(CPCSHA256 *sha512) {
		CPC_ASSERT(sha512);
		int result = SHA512_Init(sha512);
		CPC_ASSERT(result == 1);
	}

	void cpc_sha512_update(CPCSHA512 *sha512, const char *data, size_t data_size) {
		CPC_ASSERT(sha512);
		CPC_ASSERT(data != NULL || data_size == 0);
		int result = SHA512_Update(sha512, data, data_size);
		CPC_ASSERT(result == 1);
	}

	void cpc_sha512_finish(CPCSHA512 *sha512, unsigned char *digest) {
		CPC_ASSERT(sha512);
		int result = SHA512_Final(digest, sha512);
		CPC_ASSERT(result == 1);
	}
#endif
