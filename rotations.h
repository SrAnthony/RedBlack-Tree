int calc_bf(avl_node* node) {
	return node->l_height - node->r_height;
}

avl_node* calc_height(avl_node* node) {
		// TODO: it should run only on the side where the tree was rebalanced or added a new node
		if(node){
				calc_height(node->left);
				calc_height(node->right);

				avl_node* right = node->right;
				avl_node* left = node->left;

				// Increments the height of the node
				if(node->right)
						node->r_height = calc_bf(right) > 0 ? right->l_height+1 : right->r_height+1;

				if(node->left)
						node->l_height = calc_bf(left) > 0 ? left->l_height+1 : left->r_height+1;
		}
		return node;
}

avl_node* calc_height_root(avl_node* node) {
	printf("[INFO] Recalculating the height on all nodes, based on %d\n", node->data);
	avl_node* root = node;
	for(; root->root != NULL; root = root->root); // Iterates to the tree's root
	return calc_height(root);
}

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
		// To fix the height
		node->r_height = 0;

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
				printf("[INFO] Recalculating height on all nodes after simple left rotating on root\n");
				return calc_height(pivot);
		}
		return calc_height_root(node);
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
		// To fix the height
		node->l_height = 0;

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
				printf("[INFO] Recalculating height on all nodes after simple right rotating on root\n");
				return calc_height(pivot);
		}
		return calc_height_root(node);
}
// When LeftRight
avl_node* rotation_double_right(avl_node *node){
		printf("[INFO] Double rotation to the right on node %d...\n", node->data);
		avl_node *pivot = node->left->right;
		pivot->l_height = 1;
		node->left->r_height = 0;
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
		pivot->r_height = 1;
		node->right->l_height = 0;
		pivot->right = node->right;
		node->right->root = pivot;

		node->right->position = pivot->position = 0;

		node->right->left = NULL;
		node->right = pivot;
		return rotation_simple_left(node);
}
