#include "HashUtils.h"
#include <cassert>
#include <vector>
#include <cstring>
#include <stdexcept>
#ifdef _WIN32
#include <Windows.h>
#include <Wincrypt.h>
#elif defined(__APPLE__)
#define COMMON_DIGEST_FOR_OPENSSL
#include <CommonCrypto/CommonDigest.h>
#include <CommonCrypto/CommonHMAC.h>
#elif defined(HAS_OPENSSL)
#include <openssl/sha.h>
#include <openssl/hmac.h>
#endif

std::array<uint8, 0x20> Framework::HashUtils::ComputeSha256(const void* data, size_t dataSize)
{
	std::array<uint8, 0x20> result;
#if defined(_WIN32)
	BOOL succeeded = FALSE;

	HCRYPTPROV context = NULL;
	succeeded = CryptAcquireContext(&context, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT);
	assert(succeeded);

	{
		HCRYPTHASH hash = NULL;
		succeeded = CryptCreateHash(context, CALG_SHA_256, 0, 0, &hash);
		assert(succeeded);

		succeeded = CryptHashData(hash, reinterpret_cast<const BYTE*>(data), dataSize, 0);
		assert(succeeded);

		DWORD hashSize = 0;
		DWORD hashSizeLength = sizeof(hashSize);
		succeeded = CryptGetHashParam(hash, HP_HASHSIZE, reinterpret_cast<BYTE*>(&hashSize), &hashSizeLength, 0);
		assert(succeeded);
		
		assert(hashSize == 0x20);

		succeeded = CryptGetHashParam(hash, HP_HASHVAL, reinterpret_cast<BYTE*>(result.data()), &hashSize, 0);
		assert(succeeded);

		succeeded = CryptDestroyHash(hash);
		assert(succeeded);
	}

	succeeded = CryptReleaseContext(context, 0);
	assert(succeeded);
#elif defined(HAS_OPENSSL) || defined(__APPLE__)
	SHA256_CTX c;
	SHA256_Init(&c);
	SHA256_Update(&c, data, dataSize);
	SHA256_Final(result.data(), &c);
#else
	throw std::runtime_error("Not supported");
#endif
	return result;
}

std::array<uint8, 0x20> Framework::HashUtils::ComputeHmacSha256(const void* key, size_t keySize, const void* data, size_t dataSize)
{
	std::array<uint8, 0x20> result;
#if defined(_WIN32)
	BOOL succeeded = FALSE;

	HCRYPTPROV context = NULL;
	succeeded = CryptAcquireContext(&context, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT);
	assert(succeeded);

	HCRYPTKEY cryptKey = NULL;

	{
		struct KEYSTRUCT
		{
			PUBLICKEYSTRUC header;
			DWORD keySize;
		};

		std::vector<uint8> keyBlob;
		keyBlob.resize(sizeof(KEYSTRUCT) + keySize);
		auto kb = reinterpret_cast<KEYSTRUCT*>(keyBlob.data());
		kb->header.bType = PLAINTEXTKEYBLOB;
		kb->header.bVersion = CUR_BLOB_VERSION;
		kb->header.reserved = 0;
		kb->header.aiKeyAlg = CALG_RC2;
		kb->keySize = keySize;
		memcpy(kb + 1, key, keySize);

		succeeded = CryptImportKey(context, reinterpret_cast<const BYTE*>(keyBlob.data()), keyBlob.size(), 0, CRYPT_IPSEC_HMAC_KEY, &cryptKey);
		assert(succeeded);
	}

	{
		HCRYPTHASH hash = NULL;
		succeeded = CryptCreateHash(context, CALG_HMAC, cryptKey, 0, &hash);
		assert(succeeded);

		HMAC_INFO hmacInfo = {};
		hmacInfo.HashAlgid = CALG_SHA_256;
		succeeded = CryptSetHashParam(hash, HP_HMAC_INFO, reinterpret_cast<const BYTE*>(&hmacInfo), 0);
		assert(succeeded);

		succeeded = CryptHashData(hash, reinterpret_cast<const BYTE*>(data), dataSize, 0);
		assert(succeeded);

		DWORD hashSize = 0;
		DWORD hashSizeLength = sizeof(hashSize);
		succeeded = CryptGetHashParam(hash, HP_HASHSIZE, reinterpret_cast<BYTE*>(&hashSize), &hashSizeLength, 0);
		assert(succeeded);
		
		assert(hashSize == 0x20);

		succeeded = CryptGetHashParam(hash, HP_HASHVAL, reinterpret_cast<BYTE*>(result.data()), &hashSize, 0);
		assert(succeeded);

		succeeded = CryptDestroyHash(hash);
		assert(succeeded);
	}

	succeeded = CryptDestroyKey(cryptKey);
	assert(succeeded);

	succeeded = CryptReleaseContext(context, 0);
	assert(succeeded);
#elif defined(__APPLE__)
	static_assert(CC_SHA256_DIGEST_LENGTH == 0x20, "Expecting a 32-byte size array.");
	CCHmac(kCCHmacAlgSHA256, key, keySize, reinterpret_cast<const unsigned char*>(data), dataSize, result.data());
#elif defined(HAS_OPENSSL)
	uint8 interResult[EVP_MAX_MD_SIZE];
	unsigned int resultSize = 0;
	HMAC(EVP_sha256(), key, keySize, reinterpret_cast<const unsigned char*>(data), dataSize, interResult, &resultSize);
	if(resultSize != 0x20)
	{
		throw std::runtime_error("Invalid result size");
	}
	memcpy(result.data(), interResult, 0x20);
#else
	throw std::runtime_error("Not supported");
#endif
	return result;
}
