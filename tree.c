#include <stdlib.h>
#include <stdio.h>

/*
 *  General-purpose tree traversal function. Written by Kjell Post ca '88
 *  =====================================================================
 *  Using one extra bit per tree-node, the function traverse(p, order, F)
 *  takes (1) a tree node p; (2) a traverse argument order and a function 
 *  pointer F and applies F() on each node in PREORDER/INORDER/POSTORDER,
 *  depending on the order argument. An example is shown in main() below. 
 *
 */

typedef enum { PREORDER, INORDER, POSTORDER } traverse_order;
typedef enum { LEFT=0, RIGHT=1 } traverse_origin;

typedef struct node *TREE;

struct node {
  char data;
  TREE left, right;
  traverse_origin back: 1;	/* 1 bit is enough */
};

TREE mknode(char c, TREE left, TREE right) {
  TREE p = (TREE) malloc(sizeof(struct node));
  p->data = c;
  p->left = left;
  p->right = right;
  return p;
}

TREE mkleaf(char c) {
  return  mknode(c, 0, 0);
}

void traverse(TREE p, traverse_order order, void (*F)()) {
  TREE current, previous, source, temp;
  source = mkleaf('?');
  source->back = RIGHT;
  source->right = source;
  current = p;
  previous = source;
  for (;;) {
    while (current) {		/* advance left */
      if (order == PREORDER)
	F(current);
      temp = current->left;
      current->left = previous;
      current->back = LEFT;
      previous = current;
      current = temp;
    }
    while (previous->back == RIGHT) { /* retreat */
      temp = previous;
      previous = previous->right;
      temp->right = current;
      current = temp;
      if (current == previous)	/* done */
        return;
      if (order == POSTORDER)
        F(current);
    }
    temp = previous;
    previous = previous->left;
    temp->left = current;
    current = temp;
    if (order == INORDER)
      F(current);
    temp = current->right;	/* advance right */
    current->right = previous;
    current->back = RIGHT;
    previous = current;
    current = temp;
  }
}

void process(TREE p) {
  printf("%c ", p->data);
}

int main() {
  // 9-4*2
  TREE p = mknode('-', mkleaf('9'), mknode('*', mkleaf('4'), mkleaf('2')));
  printf("INORDER:   "); traverse(p, INORDER, process);   printf("\n");
  printf("PREORDER:  "); traverse(p, PREORDER, process);  printf("\n");
  printf("POSTORDER: "); traverse(p, POSTORDER, process); printf("\n");
}
