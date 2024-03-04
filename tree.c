#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct treenode {
  int value;
  struct treenode *left;
  struct treenode *right;
} treenode;

bool findnumber(treenode * root, int value){
  if(root == NULL){
    return false;
  }
  if(root->value == value){
    return true;
  }
  if(value < root->value){
    return findnumber(root->left, value);
  }
  else{
    return findnumber(root->right, value);
  }
}

int main(void) {
  treenode *root = NULL;
  insertnumber(&root, 15);
  insertnumber(&root, 11);
  insertnumber(&root, 24);
  insertnumber(&root, 5);
  insertnumber(&root, 19);
  insertnumber(&root, 16);
  
  printtree(root);

  printf("%d (%d)\n", 16, findnumber(root, 16));
  printf("%d (%d)\n", 15, findnumber(root, 15));
  printf("%d (%d)\n", 55, findnumber(root, 55));
  printf("%d (%d)\n", 166, findnumber(root, 166));
  return 0;
}
