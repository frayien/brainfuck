#include <cstdio>
#include <iostream>
int main() {char buffer[30000] = {0};char *ptr = buffer;ptr++;--(*ptr);--(*ptr);--(*ptr);--(*ptr);--(*ptr);--(*ptr);--(*ptr);--(*ptr);--(*ptr);--(*ptr);while(*ptr){++(*ptr);++(*ptr);++(*ptr);++(*ptr);++(*ptr);++(*ptr);++(*ptr);++(*ptr);++(*ptr);++(*ptr);ptr++;*ptr=getchar();--(*ptr);--(*ptr);--(*ptr);--(*ptr);--(*ptr);--(*ptr);--(*ptr);--(*ptr);--(*ptr);--(*ptr);}++(*ptr);++(*ptr);++(*ptr);++(*ptr);++(*ptr);++(*ptr);++(*ptr);++(*ptr);++(*ptr);++(*ptr);while(*ptr){ptr--;}ptr++;while(*ptr){putchar(*ptr);ptr++;}return 0;}