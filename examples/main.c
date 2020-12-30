#include <stdio.h>
#include "array.h"
#include "array_io.h"

int callback_int(uint32_t idx, int *v, void *userdata)
{
    return printf("%u : %d\n", idx, *v);
}

int callbacks_int(char *buffer, size_t n, uint32_t idx, int *v, void *userdata)
{
    return snprintf(buffer, n, "%u => %d ", idx, *v);
}

int main()
{
    char buffer[256] = {0};
    Array(int) myintarray = 0;

    // You can only add element inside the array using a variable
    // Array_push(myintarray, 10) is invalid and will not compile
    int value = 10;
    Array_push(myintarray, value);
    for (int i = 0; i < 100; ++i) {
        Array_push(myintarray, i);
    }
    Array_toString(myintarray, callbacks_int, buffer, 255, 0);
    printf("%s\n", buffer);
    Array_free(myintarray);
    return 0;
}