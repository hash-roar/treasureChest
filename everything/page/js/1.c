#include<stdio.h>
#include<string.h>

void swap_var(int * a,int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main()
{
   // for test 
   int a,b;
   scanf("%d %d",&a,&b);
   swap_var(&a,&b);
   printf("after swap  a:%d,b:%d",a,b);

}