#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int * init_array(int n)
{
    //malloc 
    int * ages =(int *) malloc(sizeof(int)*n);
    if(!ages){
        perror("malloc error");
        return NULL;
    }
    for(int i=0;i<15;i++){
        ages[i]=i;
    }
    return ages;
}
int  average_age(int ages[],int array_size){
    //get array size
    int age_sum = 0;
    for(int i=0;i<array_size ;i++)
    {
        if(ages[i]==0) continue;
        age_sum+=ages[i];
    }
    return age_sum/array_size;
}
int get_age_notzero(int age[],int array_size)
{
    int age_sum = 0;
    for (int i = 0; i < array_size; i++)
    {
        if(age[i]>0 && age[i]<10){
            printf("age: %d",age[i]);
            age_sum++;
        }
        else if(age[i]>10 && age[i]<100)
        {
            //个位
            int b = age[i]%10;
            if(b!=0){
                printf("age: %d",age[i]);
                age_sum++;
            }
        }
    }
    return age_sum;
}

int main(){
    int * ages = init_array(15);
    printf("average %d\n",average_age(ages,15));
    printf("age not contain zero:\n");
    printf("the sum number:%d",get_age_notzero(ages,15));
    return 0;
}

