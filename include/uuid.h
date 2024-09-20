#ifndef UUID_H
#define UUID_H

char* generate_uuid_v1();
char* generate_uuid_v2();
char* generate_uuid_v3(const char* namespace_uuid, const char* name);
char* generate_uuid_v4();
char* generate_uuid_v5(const char* namespace_uuid, const char* name);
char* generate_uuid_v7();
char* generate_uuid_nil();

#endif // UUID_H