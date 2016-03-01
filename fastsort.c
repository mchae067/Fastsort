/* 
 * fastsort.c
 * Mark Chae
 * chae@cs.wisc.edu
 * 
 * 
 * bugs: Program compiles, but does not print the sorted list.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Made global for qsort()
int sortIndex = 1;

int sort(void const *a, void const *b) {
    if (sortIndex!=0) {
        int i,j;
        char *splitTemp = (char *)malloc(128 * sizeof(char));

        char *atemp = strdup(*(char* const*) a);
        char *asplit = strtok(atemp, " ");
        for (i=1; i<sortIndex; i++) {
            splitTemp = strtok(NULL, " ");
            asplit = splitTemp;
        }
        char *btemp = strdup(*(char* const*) b);
        char *bsplit = strtok(btemp, " ");
        for (j=1; j<sortIndex; j++) {
            splitTemp = strtok(NULL, " ");
            bsplit = splitTemp;
        }
        return strcmp(asplit , bsplit);
    }
  return strcmp(*(char* const*) a, *(char* const*) b);
}

int main(int argc, char* argv[]) {
    //check for proper args
    char *filename = NULL;
    
    // ./fastsort -3 file.txt
    if(argc == 3) {
        if (atoi(argv[1]) == 0) {
            fprintf(stderr, "Error: Bad command line parameters\n");
            exit(1);
        }
        sortIndex = atoi(argv[1]);
        filename = argv[2];
    }
    // ./fastsort file.txt
    else if (argc == 2){
        filename = argv[1];
    }
    else if (argc > 3) {
        fprintf(stderr, "Error: Bad command line parameters\n");
        exit(1);
    }
    else if (argc <= 1) {
        fprintf(stderr, "Error: Bad command line parameters\n");
        exit(1);
    }
    
    //Open and read file
    FILE *fp;
    fp = fopen(filename,"r");
    if(fp == NULL)
    {
      fprintf(stderr, "Error: Cannot open file %s\n", filename);
      exit(1);
    }
    
    //Determine number of lines in file
    //Read in rows line-by-line, and check length
    int c;
    unsigned long int numRows = 0;
    while((c=fgetc(fp))!=EOF )
    {
        if(c == '\n')
            numRows++;
    }
    //Allocate data to memory
    //128 chars max per line
    char *rows[128];
    char *rowElements = "not NULL";
    int i=0;
    while (rowElements!=NULL) {
        rows[i] = (char *)malloc(sizeof(char) * 128);
        if (rows[i] == NULL) {
            printf(stderr, "malloc failed\n");
            exit(1);
        }
        rowElements = fgets(rows[i], 128, fp);
        if(rows[i][strlen(rows[i])] != '\n') {
            printf(stderr,"Line too long");
            exit(1);
        }
        i++;
    }
    
    //Call sort and print the result
    qsort(&rows[0], i, sizeof(char *), sort);
    for(i = 0; rows[i]!=NULL; i++) {
        printf("%s\n", (char *)rows[i]);
    }
    
    fclose(fp);
    return 0;
}

