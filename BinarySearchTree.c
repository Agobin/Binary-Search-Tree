
// A c program to classify words giving their frequency.
// Input should be redirected from a file though it could be done manually 
//Output of the program would be in file named Output.txt and would also be in the terminal
#include <stdio.h>
#include <stdlib.h>    
#include <string.h>
#include <ctype.h>

typedef struct treeNode TreeNode;

//Creates a tree node structure
struct treeNode{
	char word[50];
	int frequency;
    TreeNode *leftNode;
	TreeNode *rightNode;
};

int getword(char *word, int lim);
void inOrderTraversal( TreeNode *rootNode);
void addNode( TreeNode **root, char *word);

int main(void){
	
	//This declaration initialises the output file discarding all its content if it exist
	FILE *outputFilePtr = fopen("Output.txt", "w");
	TreeNode *root;
	char word[50];
	int ch;

	root = NULL;
	//Reads input and store in binary tree until end of file is read
	while( getword(word, 50) != EOF ){
		if( isalpha(word[0]))
			addNode( &root, word);
	}

	inOrderTraversal(root);

	fclose(outputFilePtr);
	return 0;
}

int getword(char *word, int lim){
	int c;
	char *w = word;

	while (isspace(c = getchar()));

	if (c != EOF)
		*w++ = c;
	if (!isalpha(c)) {
		*w = '\0';
		return c;
	}
	for ( ; --lim > 0; w++)
		if (!isalnum(*w = getchar())) {
			ungetc(*w, stdin);
			break;
		}
	*w = '\0';
	return word[0];
}

//This function traverses the tree inorderly and prints the tree to a file and also to the screen
void inOrderTraversal( TreeNode *rootNode){
	if( rootNode != NULL){
		FILE *outputFilePtr;
		outputFilePtr = fopen("Output.txt","a");

		inOrderTraversal(rootNode->leftNode);
		fprintf(outputFilePtr,"\t%-17s\t%-4d\n", rootNode->word, rootNode->frequency );
		printf("\n%-17s", rootNode->word );
		inOrderTraversal( rootNode->rightNode);
		fclose(outputFilePtr);
	}
}

//This function adds nodes to the tree
void addNode( TreeNode **root, char *word){

	if( *root == NULL){
		*root = malloc( sizeof(TreeNode));
		int i = 0;
		//Transfers word to (*root)->word
		for( i = 0; word[i] != '\0'; i++)
			(*root)->word[i] = word[i];
		
		(*root)->frequency = 1;
		(*root)->leftNode = (*root)->rightNode = NULL;
	}
	else if( strcmp((*root)->word, word) > 0)
		addNode( &(*root)->leftNode, word);
	else if( strcmp( (*root)->word, word) < 0)
		addNode( &(*root)->rightNode, word);
	else
		(*root)->frequency++;
}