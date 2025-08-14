#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>


void f()
{
    static int counter = 0;
    counter++;
    printf("%d\n", counter);
}

struct Pointer;

void df(int argsCnt, ...)
{
    va_list ap;
    va_start(ap, argsCnt);
    for (int i = 0; i < argsCnt; i++)
    {
        int num = va_arg(ap, int);
        printf("%d ", num);
    }
    va_end(ap);
    printf("\n");
}

void main()
{
    // int width = 5;
    // int height = 3;

    // int (*arr)[width] = malloc(width * height * sizeof(int)); // 20크기 단위 배열 포인터

    // printf("%p\n", arr);
    // printf("%p\n", arr + 1);

    // for (int i = 0; i < height; i++)
    //     for (int j = 0; j < width; j++)
    //         arr[i][j] = i;

    // for (int i = 0; i < height; i++)
    // printf("%d\n", *(*(arr + i) + 2));

    // f();
    // f();
    // f();

    df(2, 2, 3);
    df(4, 1, 2, 3, 4);
}

enum Color
{
    Red,
    Green,
    Blue
};

typedef enum _stateCode
{
    Ok = 200,
    NotFound = 404,
    ServerError = 500
} StateCode;

struct Pointer
{
    int x;
    int y;
    enum Color c;
};

typedef struct _response
{
    StateCode code;
} Response;
