
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "tree.h"
#include "stack.h"
#include "table_driven_parsing.h"

bool isWellformed(char* in, int len){
	for (int i = 0; i<len; i++){
		if ( !(isDigit(in[i]) || isOperator(in[i])) ){
			printf("Expression malformed. Character \"%c\" is not expected in a well-formed arithmetic expression.\n", in[i]);
			return 0;
		}
	}
	return 1;
}

int main(int argc, char** argv) {

	FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    if (argc==2){
    	char * filename = argv[1];
    	fp = fopen(filename, "r");
    	printf("\nCSC173 Project 2 by Tianyi Ma\n\nStart reading from file \"%s\"\n\n", filename);

    	while ((read = getline(&line, &len, fp)) != -1) {

    		// if the line includes "\n", strip it and return the proper expression
    		char *newline;
    		bool isFree = 1;
    		if (line[read-1]==10){
    			newline = (char *) calloc(read,sizeof(char));
				strncpy(newline, line, read-1);
				read--;
				isFree=0;
    		} else {
    			newline = line;
    		}

    		// if the line is a well-formed expression
    		if (isWellformed(newline, read)){
    			printf("Parsing %s...\n", newline);
    			TREE parseTree1;
				TREE parseTree2;
				//int nextTerminal = 0;

				//parseTree1 = E(newline, nextTerminal);
				parseTree1 = E(newline);
				set_next_Terminal();
				if (Tree_get_wellFormed()){
					printf("Parse tree using [recursive-descent parser]:\n");
					printTree(parseTree1, 0);

					parseTree2 = parse(newline);
					printf("Parse tree using [table-driven parser]:\n");
					printTree(parseTree2, 0);

					int eva = evaluate(parseTree1);
					printf("Evaluating expression...\n");
					printf("%s = %d\n\n", newline, eva);
                    Tree_free(parseTree2);
				}
				Tree_set_wellFormed(1);
                Tree_free(parseTree1);
    		}

    		if (!isFree)
        		free(newline);
        }
        printf("End of parsing. \n\n");
        fclose(fp);

    	if (line)
        	free(line);
    }
}
