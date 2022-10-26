#include "gib.h"


int main(void){

  GIB_TOKEN_DATA g = gib_tokens("hello.txt");

  for(int i = 0; i < g.len;i++){
    printf("%s\n",g.array[i]);
  }

  return 0;
  
}
