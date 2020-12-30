#pragma once

typedef int (*Array_print_callback)(int idx, void *data, void *userdata);
typedef int (*Array_toString_callback)(char *buffer, size_t n, uint32_t idx, int *v, void *userdata);

#define Array_print(a, callback, userdata)                          \
    for (uint32_t __aite = 0; __aite < ArraySize(a); ++__aite) {    \
        callback(__aite, &(a)[__aite], userdata);                   \
    }

#define Array_toString(a, callback, buffer, n, userdata)                                        \
    for (uint32_t __aite = 0, offset = 0; __aite < ArraySize(a); ++__aite) {                    \
        if (n - offset <= n)                                                                    \
            offset += callback(buffer + offset, n - offset, __aite, &(a)[__aite], userdata);    \
    }
