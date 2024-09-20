PHP_ARG_ENABLE(uuid, whether to enable UUID support,
[  --enable-uuid   Enable UUID support])

if test "$PHP_UUID" != "no"; then
    PHP_NEW_EXTENSION(uuid, uuid.c, $ext_shared)
fi
