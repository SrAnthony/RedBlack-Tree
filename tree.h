/*
 *  ============================
 *  Anthony Nadaletti
 *  https://github.com/SrAnthony/RedBlack-Tree
 *  ============================
 *  Test numbers: 50, 40, 30, 45, 47, 55, 53, 56, 41, 42
 */
typedef struct avl_node {
    // position = where the node is localized
		// 0 - right, 1 - left, 3 - is root
		// Color = 0 Black, 1 Red
		int data, position, color;
		struct avl_node *right;
		struct avl_node *left;
		struct avl_node *root;
}avl_node;
