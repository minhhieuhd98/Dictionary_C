#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libbtr/inc/btree.h"

#define KEY_LEN 50
#define MEAN_LEN 1000

char* split(char* str) {
	char* result; result = (char*)malloc(sizeof(char)*MEAN_LEN);
	int i = 0;
	for(int j = 0; j < strlen(str); j++, i++){
		if(str[j] == '\\' && str[j+1] == 'n') {
			result[i] = '\n';
			++j; 
		} else 
			result[i] = str[j];
	}
	result[i] = '\0';
	return result;
}

int main(int argc, const char* argv[]) {
	FILE* fpt;
	if((fpt = fopen("AnhViet.txt", "r")) == NULL) {
		printf("Can't open %s file\n", "AnhViet.txt");
		exit(EXIT_FAILURE);
	}else {
		BTA* BtreeData; 
		BtreeData = btcrt("AnhViet.dat", 0, 0);
		
		char key[KEY_LEN], mean_word[MEAN_LEN];
		
		char* mean = (char*)malloc(sizeof(char)*MEAN_LEN);
		
		while(fscanf(fpt, "%[^\t]", key)) {
			fgets(mean_word, MEAN_LEN, fpt);
			mean = split(mean_word);
			btins(BtreeData, key, mean, strlen(mean));
		}
		free(mean);
		btcls(BtreeData);
		fclose(fpt);
	}
}
