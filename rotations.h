// When RightRight
avl_node* rotation_simple_left(avl_node *node){
		printf("[INFO] Simple rotation to the left on node %d...\n", node->data);
		avl_node* pivot = node->right;
		avl_node* rot_root = node->root;

		pivot->root = rot_root;
		node->root = pivot;
		node->right = pivot->left;
		if(node->right){
			node->right->root = node;
			node->right->position = 0;
		}
		pivot->left = node;

		pivot->position = node->position;
		node->position = 1;

		if(pivot->position == 0) // 0 is right
				rot_root->right = pivot;
		else if(pivot->position == 1) // 1 is left
				rot_root->left = pivot;
		else{ // Then position == 3, is the main root
				printf("[INFO] Hey, %d is the new root!\n", pivot->data);
				pivot->position = 3;
				node->position = 1; // Node is on left side of pivot
		}
		return node;
}
// When LeftLeft
avl_node* rotation_simple_right(avl_node *node){
		printf("[INFO] Simple rotation to the right on node %d...\n", node->data);
		avl_node* pivot = node->left;
		avl_node* rot_root = node->root; // Can be NULL if node is the root

		pivot->root = rot_root;
		node->root = pivot;
		node->left = pivot->right;
		if(node->left){
			node->left->root = node;
			node->left->position = 1;
		}
		pivot->right = node;

		pivot->position = node->position;
		node->position = 0;

		if(pivot->position == 0){ // 0 is right
				rot_root->right = pivot;
		}
		else if(pivot->position == 1){ // 1 is left
				rot_root->left = pivot;
		}
		else{ // Then position == 3, is the main root
				printf("[INFO] Hey, %d is the new root!\n", pivot->data);
				pivot->position = 3;
				node->position = 0; // Node is on right side of pivot
		}
		return node;
}
// When LeftRight
avl_node* rotation_double_right(avl_node *node){
		printf("[INFO] Double rotation to the right on node %d...\n", node->data);
		avl_node *pivot = node->left->right;
		pivot->left = node->left;
		node->left->root = pivot;

		node->left->position = pivot->position = 1;

		node->left->right = NULL;
		node->left = pivot;
		return rotation_simple_right(node);
}
// When RightLeft
avl_node* rotation_double_left(avl_node *node){
		printf("[INFO] Double rotation to the left on node %d...\n", node->data);
		avl_node *pivot = node->right->left;
		pivot->right = node->right;
		node->right->root = pivot;

		node->right->position = pivot->position = 0;

		node->right->left = NULL;
		node->right = pivot;
		return rotation_simple_left(node);
}
