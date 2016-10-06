#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include "hash.h"
#include "unixtimer.h"

#define NUMSIZES 3
#define TOPWORDS 5

int main(int argc, char* argv[])
{
	int i, j, htSize[NUMSIZES] = {53, 1543, 98317};
        char word[1024];
	char* ptr;

	if(argc < 2) {
		fprintf(stderr, "Use: %s <filename>\n", argv[0]);
		return -1;
	}

	for(i=0; i<NUMSIZES; i++) {

	        FILE* theFile = fopen(argv[1],"r");
		if(theFile==NULL) {
			fprintf(stderr, "Error opening %s, errno %d\n", argv[0], errno);
			return -2;
		}

		start_timer();
        	Hashtable*  t = htCreate(htSize[i]);

	        while(!feof(theFile)) {
	                fscanf(theFile,"%s",word);
			for(ptr = word; *ptr; ptr++)
				*ptr = tolower(*ptr);    // convert leters to lowercase
			// increment the value associated with key 'word' by one
                	htPut(t, word, 1+htGet(t,word) );
		}

		for(j=0; j<TOPWORDS; j++) {
			char* frequent = htMaxValKey(t);
			printf("'%s' appears %d times\n", frequent, htGet(t,frequent));
			htRemove(t, frequent);

		}

		htDestroy(t);

		printf("CPU time for table size %d is %.3f seconds\n", htSize[i], cpu_seconds() );

		fclose(theFile);
        }

	return 0;
}
