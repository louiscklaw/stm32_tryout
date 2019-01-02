
/* gcc test.c  -o test.out */

#include <stdio.h>

const char *HELLOWORLD = "helloconstant";

char test_stack[100];
int test_stack_top=-1;
int test_stack_max=100;


void print_char_inside_func(char * pc)
{
  printf("%c", *pc);
}

int main()
{
    char c='a';
    char* pc  =&c;

    print_char_inside_func(pc);

    return 0;
}
