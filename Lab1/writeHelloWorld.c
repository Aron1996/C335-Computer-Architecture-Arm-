#include<stdio.h>
#include <string.h> 
int main(void){ 
  while(1){
    FILE *fp;
    printf("Hello World\n"); 
    fp = fopen("HelloWorld.txt", "w");
    fprintf(fp, "Hello World");
    fclose(fp);
    sleep(3);
  }
}
