#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "tree.h"
#include "stack.h"
#define FAILED NULL


void parseTable(int parsing_table[8][128]){

	// initialize every entry as -1
	for (int i=0; i<128; i++){
		for (int j = 0; j < 8; j++){
			parsing_table[j][i] = -1;
		}
	}

	// grammar 4, 8, 13 accept any character
	for (int i=0; i<128; i++){
		parsing_table[1][i] = 4;
		parsing_table[3][i] = 8;
		parsing_table[6][i] = 13;
	}

	// specific grammars
	for (int i=0; i<10; i++){
		char c = i +'0';
		parsing_table[0][(int)c] = 1;
		parsing_table[2][(int)c] = 5;
		parsing_table[4][(int)c] = 9;
		parsing_table[5][(int)c] = 11;
		parsing_table[6][(int)c] = 12;
		parsing_table[7][(int)c] = i+14;
	}
	parsing_table[0][(int)('(')] = 1;
	parsing_table[2][(int)('(')] = 5;
	
	parsing_table[1][(int)('+')] = 2;
	parsing_table[1][(int)('-')] = 3;

	parsing_table[3][(int)('*')] = 6;
	parsing_table[3][(int)('/')] = 7;

	parsing_table[4][(int)('(')] = 10;

}

//char* terminal[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "(", ")", "+", "-", "*", "/"}
bool isNonTerminal(char* s){
	bool b = 0;
	int len = strlen(s);
	if (len==1){
		b = (s[0] == 'E' || s[0] == 'T' || s[0] == 'F' || s[0] == 'N' || s[0] == 'D');
	} else if (len==2){
		b = ( (s[0] == 'T' && s[1] == 'T') || (s[0] == 'F' && s[1] == 'T') || (s[0] == 'N' && s[1] == 'T'));
	}
	return b;
}


int find_index(char* s){
	int len = strlen(s);
	int index = -1;
	if (len==1){
		if (s[0] == 'E'){
			index = 0;
		} else if (s[0] == 'T'){
			index = 2;
		} else if (s[0] == 'F'){
			index = 4;
		} else if (s[0] == 'N'){
			index = 5;
		} else if (s[0] == 'D'){
			index = 7;
		}
	} else if (len==2){
		if (s[0] == 'T' && s[1] == 'T'){
			index = 1;
		} else if (s[0] == 'F' && s[1] == 'T'){
			index = 3;
		} else if (s[0] == 'N' && s[1] == 'T'){
			index = 6;
		}
	}
	return index;
}

Stack add_production(int grammar){
	Stack production = new_Stack();
	switch (grammar){
		case 1:
		Stack_push(production, "TT");
		Stack_push(production, "T");
		break;

		case 2:
		Stack_push(production, "TT");
		Stack_push(production, "T");
		Stack_push(production, "+");
		break;

		case 3:
		Stack_push(production, "TT");
		Stack_push(production, "T");
		Stack_push(production, "-");
		break;

		case 5:
		Stack_push(production, "FT");
		Stack_push(production, "F");
		break;

		case 6:
		Stack_push(production, "FT");
		Stack_push(production, "F");
		Stack_push(production, "*");
		break;

		case 7:
		Stack_push(production, "FT");
		Stack_push(production, "F");
		Stack_push(production, "/");
		break;

		case 9:
		Stack_push(production, "N");
		break;

		case 10:
		Stack_push(production, ")");
		Stack_push(production, "E");
		Stack_push(production, "(");
		break;

		case 11:
		Stack_push(production, "NT");
		Stack_push(production, "D");
		break;

		case 12:
		Stack_push(production, "N");
		break;

		case 14:
		Stack_push(production, "0");
		break;
		case 15:
		Stack_push(production, "1");
		break;
		case 16:
		Stack_push(production, "2");
		break;
		case 17:
		Stack_push(production, "3");
		break;
		case 18:
		Stack_push(production, "4");
		break;
		case 19:
		Stack_push(production, "5");
		break;
		case 20:
		Stack_push(production, "6");
		break;
		case 21:
		Stack_push(production, "7");
		break;
		case 22:
		Stack_push(production, "8");
		break;
		case 23:
		Stack_push(production, "9");
		break;
	}
	return production;
}

TREE makeNode(int grammar){
	TREE node = NULL;
	switch (grammar){
	case 1:
	  node = makeNode2("E", makeNode0("T"), makeNode0("TT"));
		break;

		case 2:
		node = makeNode3("TT", makeNode0("+"), makeNode0("T"), makeNode0("TT"));
		break;

		case 3:
		node = makeNode3("TT", makeNode0("-"), makeNode0("T"), makeNode0("TT"));
		break;

		case 4:
		node = makeNode1("TT", makeNode0("e"));
		break;

		case 5:
		node = makeNode2("T", makeNode0("F"), makeNode0("FT"));
		break;

		case 6:
		node = makeNode3("FT", makeNode0("*"), makeNode0("F"), makeNode0("FT"));
		break;

		case 7:
		node = makeNode3("FT", makeNode0("/"), makeNode0("F"), makeNode0("FT"));
		break;

		case 8:
		node = makeNode1("FT", makeNode0("e"));
		break;

		case 9:
		node = makeNode1("F", makeNode0("N"));
		break;

		case 10:
		node = makeNode3("F", makeNode0("("), makeNode0("E"), makeNode0(")"));
		break;

		case 11:
		node = makeNode2("N", makeNode0("D"), makeNode0("NT"));
		break;

		case 12:
		node = makeNode1("NT", makeNode0("N"));
		break;

		case 13:
		node = makeNode1("NT", makeNode0("e"));
		break;

		case 14:
		node = makeNode1("D", makeNode0("0"));
		break;
		case 15:
		node = makeNode1("D", makeNode0("1"));
		break;
		case 16:
		node = makeNode1("D", makeNode0("2"));
		break;
		case 17:
		node = makeNode1("D", makeNode0("3"));
		break;
		case 18:
		node = makeNode1("D", makeNode0("4"));
		break;
		case 19:
		node = makeNode1("D", makeNode0("5"));
		break;
		case 20:
		node = makeNode1("D", makeNode0("6"));
		break;
		case 21:
		node = makeNode1("D", makeNode0("7"));
		break;
		case 22:
		node = makeNode1("D", makeNode0("8"));
		break;
		case 23:
		node = makeNode1("D", makeNode0("9"));
		break;

	}
	return node;
}

TREE parse(char*in){
	Stack goal = new_Stack();
	TREE parseTree = NULL;
	int parsing_table[8][128];
	int len = strlen(in);
	int nextTerminal = 0;

	parseTable(parsing_table);
	Stack_push(goal, "E");
	parseTree = makeNode0("E");

	while (!Stack_isEmpty(goal)){

		char currIn = in[nextTerminal];
		char* currState = Stack_pop(goal);
		int state_index = -1;

		if (isNonTerminal(currState)){ // if the top of the stack is not a terminal
			state_index = find_index(currState);
			int grammar = parsing_table[state_index][(int)currIn];
			if (grammar != -1){

				Stack production = add_production(grammar); // match production and add it to the stack
				StackIterator iterator = Stack_iterator(production);
				while (StackIterator_hasNext(iterator)){
					char* next = StackIterator_next(iterator);
					Stack_prepend(goal, next);
				}
				free(iterator);
				Stack_free(production, 0);
				TREE nN = makeNode(grammar);

				addNode(parseTree, nN); // add the production to the tree
				set_find();
				Tree_free(nN);
			}

		} else { // if the top of the stack is a terminal
			char currTerminal = currState[0];
			if (currIn == currTerminal){
				nextTerminal++;
			} else {
				printf("Error: malformed expression\n");
				return FAILED;
			}
		}

		if (nextTerminal > len){
			printf("malformed expression\n");
			return FAILED;
		}
	}
	Stack_free(goal, 0);
	return parseTree;
}









