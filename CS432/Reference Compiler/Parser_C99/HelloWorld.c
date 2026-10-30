#include <stdio.h>
void printf(const char *str){}
int sum(int a, int b){
    return a+b;
}
int main(void) {
    int x;
    double y;
    char z;
    x=0;
    y=0.0;
    z='a';
    if(x>0);
    x=++y;
    for(x=0;x<10;x++){
        printf(x);
    }
    printf("Hello, World!\n");
    return 0;
}