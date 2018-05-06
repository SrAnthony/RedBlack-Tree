/*
 *  ============================
 *  Anthony Nadaletti
 *  https://github.com/SrAnthony/AVL-Tree
 *  ============================
 */
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "avlTreePrinter.h"
#include "rotations.h"

avl_node* insertion_case_1(avl_node* node); // Needed for insertion_case_3

avl_node* get_tree_root(avl_node* node) {
  avl_node* root;
  for(; root->root != NULL; root = root->root);
  return root;
}

avl_node* grandf(avl_node* node) {
  if (node && node->root != NULL)
		return node->root->root;
	else
		return NULL;
}

avl_node* uncle(avl_node* node) {
  avl_node* gf = grandf(node);
	if (!gf)
		return NULL; // If not grandf, then not uncle
	if (node->root == gf->left)
		return gf->right;
	else
		return gf->left;
}

avl_node* insertion_case_5(avl_node* node) {
  printf("[INFO] Insertion Case 5\n");
  avl_node* gf = grandf(node);

  node->root->color = 0;
  gf->color = 1;

  if(node == node->root->left && node->root == gf->left) {
    return rotation_simple_right(gf);
  }
  return rotation_simple_left(gf);
}

avl_node* insertion_case_4(avl_node* node) {
  printf("[INFO] Insertion Case 4\n");
  avl_node* gf = grandf(node);

  if(node == node->root->right && node->root == gf->left) {
    return rotation_simple_left(node->root);
  }
  else if(node == node->root->left && node->root == gf->right) {
    return rotation_simple_right(node->root);
  }
  return insertion_case_5(node);
}

avl_node* insertion_case_3(avl_node* node) {
  printf("[INFO] Insertion Case 3\n");
  avl_node* unc = uncle(node), *gf;

	if (unc && unc->color == 1) {
    node->root->color = 0;
    unc->color = 0;
    gf = grandf(node);
    gf->color = 1;
		return insertion_case_1(gf);
	}
	return insertion_case_4(node);
}

avl_node* insertion_case_2(avl_node* node) {
  printf("[INFO] Insertion Case 2\n");
  if(node->root->color == 1){
    return insertion_case_3(node);
  }
  return node;
}

avl_node* insertion_case_1(avl_node* node) {
  printf("[INFO] Insertion Case 1\n");
  if(node->root == NULL){
    node->color = 0; // Black
    node->position = 3;
  }
  else return insertion_case_2(node);
  return node;
}

avl_node* create_node(){
  // Creates a new node with user input data
  avl_node *newNode = (avl_node*)calloc(1, sizeof(avl_node));
  newNode->color = 1; // Red
  printf("[USER] Type a number: ");
  scanf("%d", &newNode->data);

  printf("[INFO] Created node: %d\n", newNode->data);
  return newNode;
}

avl_node* add_node(avl_node * node, avl_node* toAdd){

		if (toAdd->data == node->data) {
				printf("[INFO] The number %d is already on the tree!\n", toAdd->data);
				return node;
		}
		else if (toAdd->data > node->data) {
				printf("[INFO] Adding: going right, %d > %d\n", toAdd->data, node->data);
				if (node->right == NULL) {
						node->right = toAdd; // If right is NULL then toAdd is added to it
						toAdd->position = 0; // Position 0 = right, 1 = left
						toAdd->root = node; // node is toAdd's father
						printf("[INFO] Added on %d's right side\n", node->data);
            insertion_case_1(toAdd);
				}
				else {
						add_node(node->right, toAdd);
				}
		}
		else { //if (toAdd->data < node->data)
				printf("[INFO] Adding: going left, %d < %d\n", toAdd->data, node->data);
				if (node->left == NULL) {
						node->left = toAdd; // If left is NULL then toAdd is added to it
						toAdd->position = 1; // Position 0 = right, 1 = left
						toAdd->root = node; // node is toAdd's father
						printf("[INFO] Added on %d's left side\n", node->data);
            insertion_case_1(toAdd);
				}
				else {
						add_node(node->left, toAdd);
				}
		}
    // Insertion cases can rotate the tree, this function has to return the tree root
		return get_tree_root(node);
}

int main(void) {
		avl_node *root = insertion_case_1(create_node());
		int option;
		do{
				printf("\n\t|------------------------------------Level------------------------------------|\n");
				printf("\t|--0--| |--1--| |--2--| |--3--| |--4--| |--5--| |--6--| |--7--| |--8--| |--9--|\n");
				print_tree(root, 0);
				printf("\n\n----------------\nChoose an option:\n");
				printf("1. Add a new node\n");
        printf("0. Exit\n");
				scanf("%d", &option);
				system("clear");
				switch (option) {
				case 1:
						root = add_node(root, create_node());
						break;
				}
		}while(option != 0);
		return 0;
}
