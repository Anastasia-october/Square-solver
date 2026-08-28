#include <stdio.h>
#include <string.h>

int main(void)
{
    const char* str = "ref";
    printf("%d\n", strcmp(str, "ref"));
}
