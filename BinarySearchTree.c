#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct treeNode TreeNode;

struct treeNode{
	char word[100];
	int frequency;
    TreeNode *leftNode;
	TreeNode *rightNode;
};

void addNode( TreeNode **root, char *word){

	if( *root == NULL){
		*root = malloc( sizeof(TreeNode));
		int i = 0;

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
void inOrderTraversal( TreeNode *rootNode){
	if( rootNode != NULL){
		inOrderTraversal(rootNode->leftNode);
		printf("\t%-17s\t%-4d\n", rootNode->word, rootNode->frequency );
		inOrderTraversal( rootNode->rightNode);
	}
}

int main(void){
	
	TreeNode *root;
	char word[50];
	int ch;

	root = NULL;
	//Reads input and store in binary tree until end of file is read
	while( ( ch = getchar()) != EOF ){
		ungetc(ch, stdin);
		scanf("%s",word);
		addNode( &root, word);
	}
	printf("\tWord  \t\t Frequency\n");
	printf("\n\n");
	inOrderTraversal(root);

	
	return 0;
}