#ifndef _GIB_TOKKENS_H_
#define _GIB_TOKKENS_H_

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

//@TYPES
//TYPES STRUCTS


typedef struct node{

  struct node * next;
  struct node * prev;
         char *  val;

}node;

typedef struct{

  unsigned long counter;
  node head;
  node tail;
  
}List;


typedef struct{

  char        ** array;
  List            list;
  int             len;
  
}GIB_TOKEN_DATA;



//TYPES END


//@ HELPER


List parse(char * path);
void init_list(List * ll);
node * createnewnode();
void append(List * ll,char * val);
char ** arrayfy(List ll);
char * strip_space(char *word);
bool is_special_symbol(char c);
char * loadsrc(char * path);


//HELPER FUNCTONS




          //PARSE


List parse(char * path){
  
  List ll;
  
  init_list(&ll);

  char * code = loadsrc(path);

  long len = strlen(code);

  long index = 0;
  long lastindex = 0;
  long i = 0;

  while(index != len){
    if(isspace(code[index])){
      char * buffer = (char*) calloc((index - lastindex),sizeof(char));
      
      while(lastindex != index){

    	buffer[i] = code[lastindex];
	    i++;
	    lastindex++;
	
      }

      i= 0;
      char * stripped  = strip_space(buffer);
      if(stripped != NULL){
	    append(&ll,stripped);
      }
      
    }
    index++;
  }

  char * buffer = (char*) calloc((index - lastindex),sizeof(char));
  i = 0;   
  while(lastindex != index){

    buffer[i] = code[lastindex];
    i++;
    lastindex++;
  
    }
      char * stripped  = strip_space(buffer);
      if(stripped != NULL){
      append(&ll,stripped);
      }

  return ll;

}



           //INIT_LIST


void init_list(List * ll){

  ll->head.next = NULL;
  ll->head.prev = NULL;

  ll->tail.next = NULL;
  ll->tail.prev = NULL;

  ll->counter = 0;

  ll->tail.val = NULL;
  ll->head.val = NULL;
  
}


        //CREATENEWNODE

node * createnewnode(){

  node * buffernode = (node *) malloc(sizeof(node));
  buffernode->val =  NULL;
  buffernode->next = NULL;
  buffernode->prev = NULL;

  return buffernode;
  
}


          //APPEND

void append(List * ll,char * val){

  node *newnode = createnewnode();

  newnode->val = val;

  if(ll->counter == 0){

    newnode->next = &ll->tail;
    newnode->prev = &ll->head;
    ll->tail.prev = newnode;
    ll->head.next = newnode;

    ll->counter++;
    return;
  }


  ll->tail.prev->next = newnode;

  newnode->next = &ll->tail;
  newnode->prev = ll->tail.prev;

  ll->tail.prev  = newnode;
  ll->counter++;
  return;
  

}


          //ARRAYFY


char ** arrayfy(List ll){                                //please pass in the initialized and parsed List

  char **ret = calloc(ll.counter,sizeof(char*));

  node * headdotnext= ll.head.next;

  for(int i = 0; i < ll.counter ; i++){


    ret[i] = headdotnext->val;

    headdotnext = headdotnext->next;

  }

  return ret;



}



          //STRPI_SPACE

char * strip_space(char * word){

  int len = strlen(word);

  int newlen = 0;

  for(int i = 0;i < len;i++){

      newlen++;
    }

  char * retval = (char *) calloc(newlen,sizeof(char));

  int index2 = 0;
  
  for(int i = 0;i < len;i++){
    if(!isspace(word[i])){

      retval[index2] = word[i];

      index2++;
      
    }

    
  }

  if(strlen(retval) == 0){
    return NULL;
  }

  return  retval;
  
  
}

             //IS_SPECIAL_SYMBOL

bool is_special_symbol(char  c){

  if(c == '!'){
    return true;
  }
  if(c == '@'){
    return true;
  }
  if(c == '#'){
    return true;
  }
  if(c == '$'){
    return true;
  }
  if(c == '%'){
    return true;
  }
  if(c == '^'){
    return true;
  }
  if(c == '&'){
    return true;
  }
  if(c == '*'){
    return true;
  }
  if(c == '('){
    return true;
  }
  if(c == ')'){
    return true;
  }
  if(c == '-'){
    return true;
  }
  if(c == '='){
    return true;
  }
  if(c == '+'){
    return true;
  }
  if(c == '['){
    return true;
  }
  if(c == ']'){
    return true;
  }
  if(c == '{'){
    return true;
  }
  if(c == '}'){
    return true;
  }
  if(c == '|'){
    return true;
  }
  if(c == '\\'){
    return true;
  }
  if(c == ';'){
    return true;
  }
  if(c == ':'){
    return true;
  }
  if(c == '"'){
    return true;
  }
  if(c == '\''){
    return true;
  }
  if(c == ','){
    return true;
  }
  if(c == '.'){
    return true;
  }
  if(c == '<'){
    return true;
  }
  if(c == '>'){
    return true;
  }
  if(c == '/'){
    return true;
  }
  if(c == '?'){
    return true;
  }

  return false;
}




              //LOAD SRC


char * loadsrc(char * path){

  FILE * f;
  char * source;
  long numbytes;

  
  f = fopen(path,"r");
  assert(f != NULL);
  
  fseek(f, 0L, SEEK_END);
  
  numbytes  = ftell(f);

  rewind(f);
  
 
  source =(char *) calloc(numbytes,sizeof(char));
  assert(source != NULL);


 long special_symbol_counter = 0;
  
  char c;
  long index = 0;
  
  while(1){
    c = getc(f);
    if(feof(f)){
      break;
    }
    if(is_special_symbol(c)){
      special_symbol_counter++;
    }
    source[index] = c;
    index++;
  }
 
  char * retval = (char*) calloc(numbytes+(special_symbol_counter*2),sizeof(char));

  index = 0;
  int retindex = 0;

  
  while(index < numbytes){

    if(is_special_symbol((source[index]))){
	retval[retindex] = ' ';
	retval[retindex+1] = source[index];
	retval[retindex+2] = ' ';
	retindex += 2;
      }else{
	retval[retindex] = source[index];
      }

      retindex++;
      index++;
    }

  free(source);
  
  fclose(f);

  return retval;

}








//HELPER FUNCTIONS END



//@API
//API FUNCTIONS

GIB_TOKEN_DATA gib_tokens(char * path){

  GIB_TOKEN_DATA buffer;

  buffer.list = parse(path);
  buffer.array = arrayfy(buffer.list);
  buffer.len = buffer.list.counter;

  return buffer;
}






//API FUNCTIONS END

















#endif //_GIB_TOKENS_H_











