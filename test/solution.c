#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 255

int check(struct dirent * dirEl){
 if(!strcmp(dirEl->d_name, "..")) return 2;
 if(!strcmp(dirEl->d_name, ".")) return 2;
 if(dirEl->d_type == DT_DIR) return 0;
 if(!strcmp((dirEl->d_name + 1), ".txt")) return 1; 
 return 2;
}

int Wsearch(const char* dirPath, char* word, char** out){
 DIR* dir = opendir(dirPath);
 if(dir){
  struct dirent * dirEl = readdir(dir);

  while (dirEl){

   char* newPath = (char*)malloc(MAX_LEN*sizeof(char));
   strcpy(newPath,dirPath);
   strcat(newPath, "/");
   strcat(newPath, dirEl->d_name);

   switch(check(dirEl)){

    case 0:
     Wsearch(newPath, word, out);
     break;

    case 1:
     for(int i = 0; i < strlen(word); i++){
      if (*(dirEl->d_name) == word[i]){
       strcpy(*(out+i), newPath);
      }
     }
    break;
    }
   free(newPath);
   dirEl = readdir(dir);
   }
  }
 closedir(dir);
}


int main(){

 char* word = (char*)calloc(MAX_LEN, sizeof(char));
 char c;
 FILE* res = fopen("result.txt", "wt");
 fgets(word, MAX_LEN, stdin); 
 char** result = (char**)malloc(strlen(word)*sizeof(char*));

 for(int i = 0; i < strlen(word); i++){
  result[i] = (char*)malloc(MAX_LEN*sizeof(char));
 }

 Wsearch("./tmp", word, result);

 for(int i = 0; i < strlen(word); i++){
  printf("%s\n", result[i]);
 }

 fclose(res);
 free(word);
  for(int i = 0; i < strlen(word) - 1; i++){
  free(result[i]);
 }
 free(result);
 return 0;
}
