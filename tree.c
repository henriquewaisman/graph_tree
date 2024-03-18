#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define a árvore binária com data e filhos da esq e dir
typedef struct treenode {
  int value;
  struct treenode *left;
  struct treenode *right;
} treenode;

//cria o nó e seta seus filhos como nulo, recebe o data
treenode *createnode(int value) {
  treenode *result = malloc(sizeof(treenode));
  if (result != NULL) {
    result->left = NULL;
    result->right = NULL;
    result->value = value;
  }
  return result;
}

//função de identação
void printtabs(int numtabs) {
  for (int i = 0; i < numtabs; i++) {
    printf("\t");
  }
}

//printa a árvore em pré ordem: raíz, esq, dir; recursão
void printtree_rec(treenode *root, int level) {
  if (root == NULL) {
    printtabs(level);
    printf("--<empty>--\n");
    return;
  }
  printtabs(level);
  printf("value = %d\n", root->value);
  printtabs(level);
  printf("left\n");
  printtree_rec(root->left, level + 1);
  printtabs(level);
  printf("right\n");
  printtree_rec(root->right, level +1);
  printtabs(level);
  printf("done\n");
}

//printa a árvore por níveis
void printtree(treenode* root){
  printtree_rec(root, 0);
}

//insere um número e retorna se foi inserido ou não (ABB)
bool insertnumber(treenode **rootptr, int value){
  treenode *root = *rootptr;
  if (root == NULL) {
    (*rootptr) = createnode(value);
    return true;
  }
  if (value == root->value) {
    return false;
  }
  if (value < root->value) {
    return insertnumber(&(root->left), value);
  } else {
    return insertnumber(&(root->right), value);
  }
}

// Busca um número específico, retorna true caso o número esteja na árvore, e false caso não esteja
bool findnumber(treenode * root, int value){
  if(root == NULL){
    return false;                                             // Caso percorra a árvore toda e não ache o número buscado, retorne 0
  }             
    if(root->value == value){             
      return true;                                            // Caso ache o número, retorna 1
    }             
  if(value < root->value){              
    return findnumber(root->left, value);                     // Caso o número buscado seja menor que o nó atual, caminha iterativamente para a esquerda
  }             
  else{             
    return findnumber(root->right, value);                    // Caso o número buscado seja maior que o nó atual, caminha iterativamente para a direita
  }
}

// TODO: Conta os nós da árvore
int numOfNodes(struct treenode* root){
    if(root == NULL){                                         // Trata nós nulos
      return 0;
    }
    int leftNodes = numOfNodes(root->left);                   // Guarda uma iteração para os nós da esquerda dentro de uma variável inteira.
    int rightNodes = numOfNodes(root->right);                 // Guarda uma iteração para os nós da direita dentro de uma variável inteira.
    return (rightNodes+leftNodes)+1;                          // Retorna o número de iterações guardadas nas variárveis leftNodes e rightNodes e soma 1 do nó raíz
}

// TODO: Conta os nós não folhas da árvore
int NonLeaf(treenode *root) {
    if (root == NULL){
      return 0;                                               // Trata nós nulos
    } 
    else if (root->left == NULL && root->right == NULL){
      return 0;                                               // Trata nós folhas
    }
    else{
      return 1 + NonLeaf(root->left) + NonLeaf(root->right);  //  Soma nós não folhas iterativamente e soma 1 da raíz
    }
}

// TODO: Exluir um número mantendo a ordem
// Acha o menor número
treenode *findMinNode(treenode *node) {
    while (node->left != NULL)
        node = node->left;
    return node;
}

// Remoção do nó
treenode *removeNode(treenode *root, int node) {
    if (root == NULL){
        return root;                                          // Trata nós nulos
    }
    if(node < root->value){                                   // Caso o número buscado seja menor que o nó atual, caminha iterativamente para a esquerda
      root->left = removeNode(root->left, node);
    }
    else if(node > root->value){
        root->right = removeNode(root->right, node);          // Caso o número buscado seja maior que o nó atual, caminha iterativamente para a direita
    }
    else{                                                     // Número buscado == Nó atual
        if(root->left == NULL){                               // Caso não tenha filho à esquerda
            treenode *temp = root->right;                     // Guarda o filho direito numa variável temporária
            free(root);                                       // Desaloca o nó da memória
            return temp;                                      // Retorna o novo valor guardado na variável temporária
        }
        else if(root->right == NULL){                         // Caso não tenha filho à direita
            treenode *temp = root->left;                      // Guarda o filho esquerdo numa variável temporária
            free(root);                                       // Desaloca o nó da memória
            return temp;                                      // Retorna o novo valor guardado na variável temporária
        }
        treenode *temp = findMinNode(root->right);            // Caso o nó tenha ambos os filhos, procura o menor valor da subávore da direita e guarda numa variável temporária
        root->value = temp->value;                            // Seta o novo valor do nó como a variável temporária 
        root->right = removeNode(root->right, temp->value);   // Finalmente, remove o nó trocado
    }
    return root;                                              // Retorna o nó trocado
}

int main(void) {
  //Construindo  a árvore
  treenode *root = createnode(15);
  insertnumber(&root, 11);
  insertnumber(&root, 24);
  insertnumber(&root, 5);
  insertnumber(&root, 19);
  insertnumber(&root, 16);
  //Usando a função
  printf("A árvore possui um total de %i nós\n", numOfNodes(root));
  printf("A árvore possui um total de %i nós não folhas\n", NonLeaf(root));
  
  printf("%d (%d)\n", 16, findnumber(root, 16));  // Buscando um número presente na árvore
  printf("%d (%d)\n", 55, findnumber(root, 55));  // Buscando um número não presente na árvore
  
  printtree(root);
  removeNode(root, 19); // Remove o 19
  printf("\nRemovendo 19\n\n");
  printtree(root);
  
  return 0;
}
