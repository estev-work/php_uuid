#ifndef UUID_H
#define UUID_H

/**
 * Generate UUID version 1 (time-based).
 *
 * @return char* - Pointer to the string representation of UUID v1.
 */
char* generate_uuid_v1();

/**
 * Generate UUID version 2 (DCE Security-based).
 *
 * @param domain - Domain for the UUID (0 = PERSON, 1 = GROUP, 2 = ORG).
 * @param local_id - Local identifier (e.g., UID or GID).
 * @return char* - Pointer to the string representation of UUID v2.
 */
char* generate_uuid_v2(int domain, uint32_t local_id);

/**
 * Generate UUID version 3 (namespace-based, MD5 hash).
 *
 * @param namespace_uuid - Namespace UUID as a string.
 * @param name - Name for which UUID will be generated.
 * @return char* - Pointer to the string representation of UUID v3.
 */
char* generate_uuid_v3(const char* namespace_uuid, const char* name);

/**
 * Generate UUID version 4 (random-based).
 *
 * @return char* - Pointer to the string representation of UUID v4.
 */
char* generate_uuid_v4();

/**
 * Generate UUID version 5 (namespace-based, SHA-1 hash).
 *
 * @param namespace_uuid - Namespace UUID as a string.
 * @param name - Name for which UUID will be generated.
 * @return char* - Pointer to the string representation of UUID v5.
 */
char* generate_uuid_v5(const char* namespace_uuid, const char* name);

/**
 * Generate UUID version 7 (time-ordered).
 *
 * @return char* - Pointer to the string representation of UUID v7.
 */
char* generate_uuid_v7();

/**
 * Generate Nil UUID (all zeros).
 *
 * @return char* - Pointer to the string representation of Nil UUID.
 */
char* generate_uuid_nil();

#endif // UUID_H
