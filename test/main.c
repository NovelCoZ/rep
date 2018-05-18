#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <ctype.h>

#define MAX_DEPTH 5

char* newDirName(int seed){
	char* name = (char*)calloc(10, sizeof(char));
	int a = rand() % 9 + 1;
	*name = 'A' + seed % 26;
	for(int i = 1; i < a - 1; i++){
		*(name + i) = 'a' + rand() % 26;
	}
	int dv = seed / 26;
	*(name + a) = 'a' + dv + (seed % (26 - dv));
return name;
}

char* newFileName(int seed, int key){
	char* name = (char*)calloc(9, sizeof(char));
	if(key == 1){
		*name = 'a' + seed % 26;
		if(seed > 25) *name = 'A' + seed % 26;
		strcat(name, ".txt");
	} else{
	int len = rand() % 2 + 2;
	for(int i = 0; i < len; i++){
		int dv = i * seed / 26;
		*(name+i) = 'a' + dv + seed % (26 - dv);
	}
	strcat(name, ".txt");
	}

return name;
}

void makeTestField(char* path, int depth, int* seed, int *done){
	if (depth == MAX_DEPTH) return;
	if(*done == 52) return;
	depth++;
	(*seed) = *seed + 1;
	int fnum = rand() % 4;
	int lfnum = rand() % 2;
	for(int i = 0; i < fnum; i++){
	char* filePath = (char*)calloc(255, sizeof(char));
	strcpy(filePath, path);
	strcat(filePath, "/");
	strcat(filePath, newFileName(*seed, 0));
	FILE* file = fopen(filePath, "wt");
	fclose(file);
	free(filePath);
	}
	for(int i = 0; i < lfnum; i++){
	if(*done == 52) continue;
	char* filePath = (char*)calloc(255, sizeof(char));
        strcpy(filePath, path);
        strcat(filePath, "/");
        strcat(filePath, newFileName(*done, 1));
        FILE* file = fopen(filePath, "wt");
        fclose(file);
	(*done) = *done + 1;
	free(filePath);
	}
	if(depth == MAX_DEPTH - 1) return;
	int dnum = rand() % 4 + 1;
	for(int i = 0; i < dnum; i++){
	char* dirPath = (char*) calloc(255, sizeof(char));
	strcpy(dirPath, path);
        strcat(dirPath, newDirName(*seed));
	strcat(dirPath, "/");
	mkdir(dirPath, 0777);
	makeTestField(dirPath, depth, seed, done);
	free(dirPath);
	}
}

int main(){
int* seed = (int*)calloc(1, sizeof(int));
int* done = (int*)calloc(1, sizeof(int));
srand(time(NULL));
while(*done != 52)
makeTestField("./tmp/", 0, seed, done);
return 0;
}
