/*
 *  ============================
 *  Daniweb.com | Developed by Narue
 *  https://www.daniweb.com/programming/software-development/threads/146112/printing-a-binary-tree
 *  ============================
 */
 // #include <stdio.h>
 // #include "tree.h"

void padding(int n){
  for (int i = 0; i < n; i++ )
    printf("\t");
}
void print_node(avl_node *node, int level) {
  int color = node->color == 1 ? 31 : 0; // 31 is the red code, 0 is reset (terminal default)

  printf("(\e[%dm\e[1m%03d\e[0m)", color, node->data);

  int dash = 84 - (level * 8); // 80 is the total available space, level * 8 is the tab size
  char str[12];
  sprintf(str, "%d", node->data); // Int converted into string
  for(int i=0; str[i] != '\0'; i++) dash--; // For each caracter on string remove 1 from dash

  for(int i=0; i < dash; i++) printf("-");
  puts("");
}
void print_tree (avl_node *root, int level){

  if ( root == NULL ) {
    padding(level + 1);
    puts("~"); // Black ~
  }
  else {
    print_tree (root->right, level + 1);

    padding (level+1);
    print_node(root, level+1);

    print_tree(root->left, level + 1);
  }
}
