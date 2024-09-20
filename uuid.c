#include <php.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <openssl/md5.h>
#include <openssl/sha.h>

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_generate_uuid_v1, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_generate_uuid_v2, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_generate_uuid_v3, 0, 2, IS_STRING, 0)
ZEND_ARG_TYPE_INFO(0, namespace_uuid, IS_STRING, 0)
ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_generate_uuid_v4, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_generate_uuid_v5, 0, 2, IS_STRING, 0)
ZEND_ARG_TYPE_INFO(0, namespace_uuid, IS_STRING, 0)
ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_generate_uuid_v7, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_generate_uuid_nil, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

        void random_bytes(unsigned char *buf, size_t len) {
    FILE *fp = fopen("/dev/urandom", "rb");
    if (fp) {
        fread(buf, 1, len, fp);
        fclose(fp);
    } else {
        for (size_t i = 0; i < len; i++) {
            buf[i] = rand() % 256;
        }
    }
}

void format_uuid(unsigned char uuid[16], char *uuid_str) {
    sprintf(uuid_str,
            "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
            uuid[0], uuid[1], uuid[2], uuid[3],
            uuid[4], uuid[5], uuid[6], uuid[7],
            uuid[8], uuid[9], uuid[10], uuid[11],
            uuid[12], uuid[13], uuid[14], uuid[15]
    );
}

/* UUID v1: Time-based */
PHP_FUNCTION(generate_uuid_v1) {
        char uuid_str[37];
        unsigned char uuid[16];
        uint64_t time_now;
        uint16_t clock_seq;
        uint8_t node[6] = {0x00, 0x0C, 0x29, 0x3E, 0x5C, 0x7F}; // Example MAC address

        struct timespec ts;
        clock_gettime(CLOCK_REALTIME, &ts);
        time_now = ((uint64_t)ts.tv_sec * 10000000) + ((uint64_t)ts.tv_nsec / 100);

        /* Adjust for UUID epoch difference */
        time_now += 0x01B21DD213814000ULL;

        /* Construct UUID */
        uuid[0] = (time_now >> 24) & 0xFF;
        uuid[1] = (time_now >> 16) & 0xFF;
        uuid[2] = (time_now >> 8) & 0xFF;
        uuid[3] = time_now & 0xFF;
        uuid[4] = (time_now >> 40) & 0xFF;
        uuid[5] = (time_now >> 32) & 0xFF;
        uuid[6] = ((time_now >> 56) & 0x0F) | 0x10; // Version 1
        uuid[7] = (time_now >> 48) & 0xFF;

        random_bytes((unsigned char*)&clock_seq, sizeof(clock_seq));
        clock_seq = (clock_seq & 0x3FFF) | 0x8000; // Variant

        uuid[8] = (clock_seq >> 8) & 0xFF;
        uuid[9] = clock_seq & 0xFF;

        memcpy(&uuid[10], node, 6);

        format_uuid(uuid, uuid_str);
        RETURN_STRING(uuid_str);
}

/* UUID v2: DCE Security version */
PHP_FUNCTION(generate_uuid_v2) {
        // UUID v2 is implementation-specific and not commonly used.
        RETURN_STRING("UUID v2 generation not implemented");
}

/* UUID v3: Name-based MD5 hash */
PHP_FUNCTION(generate_uuid_v3) {
        char *namespace_uuid, *name;
        size_t namespace_len, name_len;
        char uuid_str[37];
        unsigned char uuid[16];
        unsigned char hash[16];
        unsigned char namespace_bytes[16];

        if (zend_parse_parameters(ZEND_NUM_ARGS(), "ss", &namespace_uuid, &namespace_len, &name, &name_len) == FAILURE) {
            RETURN_THROWS();
        }

        /* Convert namespace UUID to bytes */
        sscanf(namespace_uuid,
        "%02hhx%02hhx%02hhx%02hhx-%02hhx%02hhx-%02hhx%02hhx-%02hhx%02hhx-%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx",
        &namespace_bytes[0], &namespace_bytes[1], &namespace_bytes[2], &namespace_bytes[3],
        &namespace_bytes[4], &namespace_bytes[5], &namespace_bytes[6], &namespace_bytes[7],
        &namespace_bytes[8], &namespace_bytes[9], &namespace_bytes[10], &namespace_bytes[11],
        &namespace_bytes[12], &namespace_bytes[13], &namespace_bytes[14], &namespace_bytes[15]);

        /* Compute MD5 hash of namespace and name */
        MD5_CTX c;
        MD5_Init(&c);
        MD5_Update(&c, namespace_bytes, 16);
        MD5_Update(&c, name, name_len);
        MD5_Final(hash, &c);

        /* Set version and variant */
        hash[6] = (hash[6] & 0x0F) | 0x30; // Version 3
        hash[8] = (hash[8] & 0x3F) | 0x80;

        format_uuid(hash, uuid_str);
        RETURN_STRING(uuid_str);
}

/* UUID v4: Random */
PHP_FUNCTION(generate_uuid_v4) {
        char uuid_str[37];
        unsigned char uuid[16];

        random_bytes(uuid, 16);

        /* Set version and variant */
        uuid[6] = (uuid[6] & 0x0F) | 0x40; // Version 4
        uuid[8] = (uuid[8] & 0x3F) | 0x80;

        format_uuid(uuid, uuid_str);
        RETURN_STRING(uuid_str);
}

/* UUID v5: Name-based SHA-1 hash */
PHP_FUNCTION(generate_uuid_v5) {
        char *namespace_uuid, *name;
        size_t namespace_len, name_len;
        char uuid_str[37];
        unsigned char uuid[16];
        unsigned char hash[20];
        unsigned char namespace_bytes[16];

        if (zend_parse_parameters(ZEND_NUM_ARGS(), "ss", &namespace_uuid, &namespace_len, &name, &name_len) == FAILURE) {
            RETURN_THROWS();
        }

        /* Convert namespace UUID to bytes */
        sscanf(namespace_uuid,
        "%02hhx%02hhx%02hhx%02hhx-%02hhx%02hhx-%02hhx%02hhx-%02hhx%02hhx-%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx",
        &namespace_bytes[0], &namespace_bytes[1], &namespace_bytes[2], &namespace_bytes[3],
        &namespace_bytes[4], &namespace_bytes[5], &namespace_bytes[6], &namespace_bytes[7],
        &namespace_bytes[8], &namespace_bytes[9], &namespace_bytes[10], &namespace_bytes[11],
        &namespace_bytes[12], &namespace_bytes[13], &namespace_bytes[14], &namespace_bytes[15]);

        /* Compute SHA1 hash of namespace and name */
        SHA_CTX c;
        SHA1_Init(&c);
        SHA1_Update(&c, namespace_bytes, 16);
        SHA1_Update(&c, name, name_len);
        SHA1_Final(hash, &c);

        /* Use the first 16 bytes */
        memcpy(uuid, hash, 16);

        /* Set version and variant */
        uuid[6] = (uuid[6] & 0x0F) | 0x50; // Version 5
        uuid[8] = (uuid[8] & 0x3F) | 0x80;

        format_uuid(uuid, uuid_str);
        RETURN_STRING(uuid_str);
}

/* UUID v7: Time-ordered */
PHP_FUNCTION(generate_uuid_v7) {
        char uuid_str[37];
        unsigned char uuid[16];
        uint64_t timestamp;

        struct timespec ts;
        clock_gettime(CLOCK_REALTIME, &ts);
        timestamp = (uint64_t)ts.tv_sec * 1000 + ts.tv_nsec / 1000000;

        uuid[0] = (timestamp >> 40) & 0xFF;
        uuid[1] = (timestamp >> 32) & 0xFF;
        uuid[2] = (timestamp >> 24) & 0xFF;
        uuid[3] = (timestamp >> 16) & 0xFF;
        uuid[4] = (timestamp >> 8) & 0xFF;
        uuid[5] = timestamp & 0xFF;

        uuid[6] = 0x70 | ((timestamp >> 12) & 0x0F);
        uuid[7] = 0x80 | ((timestamp >> 4) & 0x3F);

        random_bytes(&uuid[8], 8);

        format_uuid(uuid, uuid_str);
        RETURN_STRING(uuid_str);
}

/* Nil UUID */
PHP_FUNCTION(generate_uuid_nil) {
        RETURN_STRING("00000000-0000-0000-0000-000000000000");
}

const zend_function_entry uuid_functions[] = {
        PHP_FE(generate_uuid_v1, arginfo_generate_uuid_v1)
        PHP_FE(generate_uuid_v2, arginfo_generate_uuid_v2)
        PHP_FE(generate_uuid_v3, arginfo_generate_uuid_v3)
        PHP_FE(generate_uuid_v4, arginfo_generate_uuid_v4)
        PHP_FE(generate_uuid_v5, arginfo_generate_uuid_v5)
        PHP_FE(generate_uuid_v7, arginfo_generate_uuid_v7)
        PHP_FE(generate_uuid_nil, arginfo_generate_uuid_nil)
        PHP_FE_END
};

zend_module_entry uuid_module_entry = {
        STANDARD_MODULE_HEADER,
        "uuid",
        uuid_functions,
        NULL, NULL, NULL, NULL, NULL,
        NO_VERSION_YET, STANDARD_MODULE_PROPERTIES
};

ZEND_GET_MODULE(uuid)
