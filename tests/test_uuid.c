#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../uuid.h"

int is_valid_uuid(const char* uuid, int expected_version) {
    if (strlen(uuid) != 36) {
        return 0;
    }

    for (int i = 0; i < 36; i++) {
        if (i == 8 || i == 13 || i == 18 || i == 23) {
            if (uuid[i] != '-') {
                return 0;
            }
        } else {
            if (!isxdigit(uuid[i])) {
                return 0;
            }
        }
    }

    if (expected_version > 0) {
        char version_char = uuid[14];
        if (version_char != (expected_version + '0')) {
            return 0;
        }
    }

    char variant_char = uuid[19];
    if (!(variant_char == '8' || variant_char == '9' || variant_char == 'a' || variant_char == 'A' ||
          variant_char == 'b' || variant_char == 'B')) {
        return 0;
    }

    return 1;
}

void test_generate_uuid_v1() {
    char* uuid = generate_uuid_v1();
    if (is_valid_uuid(uuid, 1)) {
        printf("generate_uuid_v1: PASS\n");
    } else {
        printf("generate_uuid_v1: FAIL (Output: %s)\n", uuid);
    }
    free(uuid);
}

void test_generate_uuid_v2() {
    char* uuid = generate_uuid_v2();
    if (strcmp(uuid, "UUID v2 generation not implemented") == 0) {
        printf("generate_uuid_v2: PASS\n");
    } else {
        printf("generate_uuid_v2: FAIL (Output: %s)\n", uuid);
    }
    free(uuid);
}

void test_generate_uuid_v3() {
    const char* namespace_uuid = "6ba7b810-9dad-11d1-80b4-00c04fd430c8";
    const char* name = "example";
    char* uuid = generate_uuid_v3(namespace_uuid, name);
    if (is_valid_uuid(uuid, 3)) {
        printf("generate_uuid_v3: PASS\n");
    } else {
        printf("generate_uuid_v3: FAIL (Output: %s)\n", uuid);
    }
    free(uuid);
}

void test_generate_uuid_v4() {
    char* uuid = generate_uuid_v4();
    if (is_valid_uuid(uuid, 4)) {
        printf("generate_uuid_v4: PASS\n");
    } else {
        printf("generate_uuid_v4: FAIL (Output: %s)\n", uuid);
    }
    free(uuid);
}

void test_generate_uuid_v5() {
    const char* namespace_uuid = "6ba7b810-9dad-11d1-80b4-00c04fd430c8";
    const char* name = "example";
    char* uuid = generate_uuid_v5(namespace_uuid, name);
    if (is_valid_uuid(uuid, 5)) {
        printf("generate_uuid_v5: PASS\n");
    } else {
        printf("generate_uuid_v5: FAIL (Output: %s)\n", uuid);
    }
    free(uuid);
}

void test_generate_uuid_v7() {
    char* uuid = generate_uuid_v7();
    if (is_valid_uuid(uuid, 7)) {
        printf("generate_uuid_v7: PASS\n");
    } else {
        printf("generate_uuid_v7: FAIL (Output: %s)\n", uuid);
    }
    free(uuid);
}

void test_generate_uuid_nil() {
    char* uuid = generate_uuid_nil();
    if (strcmp(uuid, "00000000-0000-0000-0000-000000000000") == 0) {
        printf("generate_uuid_nil: PASS\n");
    } else {
        printf("generate_uuid_nil: FAIL (Output: %s)\n", uuid);
    }
    free(uuid);
}

int main() {
    printf("Running UUID Generation Tests...\n\n");

    test_generate_uuid_v1();
    test_generate_uuid_v2();
    test_generate_uuid_v3();
    test_generate_uuid_v4();
    test_generate_uuid_v5();
    test_generate_uuid_v7();
    test_generate_uuid_nil();

    printf("\nAll tests completed.\n");
    return 0;
}
