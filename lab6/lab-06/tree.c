/*
*	Created by Nan Mihai on 05.05.2021
*	Copyright (c) 2020 Nan Mihai. All rights reserved.
*	Laborator 6 - Structuri de date
*	Grupa 314CD
*	Facultatea de Automatica si Calculatoare
*	Anul Universitar 2020-2021, Seria CD
*/
#include "tree.h"

/*
*	Funcție care creează un arbore cu un singur nod
*/
Tree createTree(Tree parent, Item value) {
	Tree root = malloc(sizeof(TreeNode));
	root->parent = parent;
	root->value = value;
	root->left = NULL;
	root->right = NULL;
	return root;
}

/*
*	Funcție care inițializează un nod de arbore
*		- îi alocă memorie
*		- îi setează câmpul valoare
*		- setează left și right să pointeze către NULL
*/
void init(Tree *root, Tree parent, Item value) {
	// TODO 0
	*root = createTree(parent, value);
}

/*
*	Funcție care inserează o valoare într-un arbore binar, respectând
* proprietățile unui arbore binar de căutare
*/
Tree insert(Tree root, Item value) {
	// TODO 1
	if (root == NULL) {
		return createTree(root, value);
	}
	if (root->value == value) {
		return root;
	}
	if (root->value > value) {
		if (root->left == NULL) {
			init(&root->left, root, value);
			return root;
		}
		root->left = insert(root->left, value);
		return root;
	}
	if (root->value < value) {
		if (root->right == NULL) {
			init(&root->right, root, value);
			return root;
		}
		root->right = insert(root->right, value);
		return root;
	}
	return NULL;
}


/*
*	Funcție care verifică dacă un arbore este vid sau nu
*		- întoarce 1 dacă arborele este vid
*		- întoarce 0 dacă arborele nu este vid
*/
int isEmpty(Tree root) {
	// TODO 2
	if (root == NULL) {
		return 1;
	}
	return 0;
}

/*
*	Funcție care verifică dacă o valoare există sau nu în arbore
*		- 1 dacă value există în arbore
*		- 0 dacă value nu există în arbore
*/
int contains(Tree tree, Item value) {
	// TODO 3
	if (isEmpty(tree)) {
		return 0;
	}
	if (tree->value == value) {
		return 1;
	}
	if (tree->value > value) {
		return contains(tree->left, value);
	} else {
		return contains(tree->right, value);
	}
}

/*
*	Funcție care determină elementul minim dintr-un arbore binar de căutare
*		- NULL pentru arbore vid
*/
Tree minimum(Tree tree) {
	// TODO 4.1
	if (isEmpty(tree)) {
		return NULL;
	}
	if (tree->left == NULL) {
		return tree;
	}
	return minimum(tree->left);
}

/*
*	Funcție care determină elementul maxim dintr-un arbore binar de căutare
*		- NULL pentru arbore vid
*/
Tree maximum(Tree tree) {
	// TODO 4.2
	if (isEmpty(tree)) {
		return NULL;
	}
	if (tree->right == NULL) {
		return tree;
	}
	return maximum(tree->right);
}

/*
*	Funcție care determină succesorul în inordine pentru nodul care conține
* valoarea value.
*/
Tree successor(Tree root, Item value) {
	// TODO 5
	if (isEmpty(root)) {
		return NULL;
	}
	if (root->value == value) {
		if (root->right != NULL) {
			return minimum(root->right);
		}
		while (root->parent != NULL && root->parent->value < value) {
			root = root->parent;
		}
		return root->parent;
	}
	if (root->value > value) {
		return successor(root->left, value);
	} else {
		return successor(root->right, value);
	}
}

/*
*	Funcție care determină predecesorul în inordine pentru nodul care conține
* valoarea value.
*/
Tree predecessor(Tree root, Item value) {
	// TODO 6
	if (isEmpty(root)) {
		return NULL;
	}
	if (root->value == value) {
		if (root->left != NULL) {
			return maximum(root->left);
		}
		while (root->parent != NULL && root->parent->value > value) {
			root = root->parent;
		}
		return root->parent;
	}
	if (root->value > value) {
		return predecessor(root->left, value);
	} else {
		return predecessor(root->right, value);
	}
}

/*
*	Funcție care dealocă întreaga memorie alocată pentru un arbore binar
*		- root va pointa către NULL după ce se va apela funcția
*/
void destroyTree(Tree *root) {
	// TODO
	if (*root == NULL) {
		return;
	}
	if ((*root)->left != NULL) {
		destroyTree(&(*root)->left);
	}
	if ((*root)->right != NULL) {
		destroyTree(&(*root)->right);
	}
	if ((*root)->left == NULL && (*root)->right == NULL) {
		free((*root));
	}
}

/*
*	Funcție care șterge un nod cu o anumită valoare din arbore
*/
Tree delete(Tree root, Item value) {
	// TODO 7
	Tree tmp;
	if (root == NULL) {
		printf("Nodul nu a fost gasit");
		return root;
	}
	if (root->value > value) {
		root->left = delete(root->left, value);
	} else if (root->value < value) {
		root->right = delete(root->right, value);
	} else {
		if (root->left != NULL && root->right != NULL) {
			tmp = minimum(root->right);
			root->value = tmp->value;
			root->right = delete(root->right, tmp->value);
		} else {
			tmp = root;
			if (root->left != NULL) {
				root = root->left;
			} else {
				root = root->right;
			}
			free(tmp);
		}
	}
	return root;
}

/*
*	Funcție care determină cel mai apropiat strămoș comun pentru
* două noduri având cheile value1 și value2
*/
Tree lowestCommonAncestor(Tree root, Item value1, Item value2) {
	// TODO 8
	if (isEmpty(root)) {
		return NULL;
	}
	if (value2 < value1) {
		Item aux = value2;
		value2 = value1;
		value1 = aux;
	}
	if (root->value < value1) {
		return lowestCommonAncestor(root->right, value1, value2);
	}
	return root;
}
