//
//  tree.c
//  tree
//
//  Created by William McCarthy on 134//20.
//  Copyright © 2020 William McCarthy. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

#include "tree.h"
#include "utils.h"


//-------------------------------------------------
tnode* tnode_create(const char* word) {
  tnode* p = (tnode*)malloc(sizeof(tnode));
  p->word = strdup(word);    // copy of word allocated on heap
  p->count = 1;
  p->left = NULL;
  p->right = NULL;
  
  return p;
}

void tnode_delete(tnode* p) {
    free((void*)p->word);
    free(p);
}

tree* tree_create(void) {
  tree* p = (tree*)malloc(sizeof(tree));
  p->root = NULL;
  p->size = 0;
  
  return p;
}

static void tree_deletenodes(tree* t, tnode* p) {
  if (p == NULL) { return; }
  
  tree_deletenodes(t, p->left);
  tree_deletenodes(t, p->right);
  tnode_delete(p);
  t->size--;
}

void tree_clear(tree* t) {
  tree_delete(t);
  t->root = NULL;
  t->size = 0;
}

void tree_delete(tree* t) { tree_deletenodes(t, t->root); }

bool tree_empty(tree* t) { return t->size == 0; }
size_t tree_size(tree* t) { return t->size; }

static tnode* tree_addnode(tree* t, tnode** p, const char* word) {
  int compare;
  
  if (*p == NULL) {
    *p = tnode_create(word);
  } else if ((compare = strcmp(word, (*p)->word)) == 0) {
    (*p)->count++;
  } else if (compare < 0) { tree_addnode(t, &(*p)->left, word);
  } else {
    tree_addnode(t, &(*p)->right, word);
  }

  return *p;
}

tnode* tree_add(tree* t, const char* word) {
  tnode* p = tree_addnode(t, &(t->root), word);
  t->size++;

  return p;
}

static void tree_printme(tree* t, tnode* p) {
  printf("%s", p->word);
  if (p->count > 1) { printf(" -- %d", p->count); }
  printf("\n");
}

static void tree_printnodes(tree* t, tnode* p) {
  if (p == NULL) { return; }
  
  tree_printnodes(t, p->left);
  tree_printme(t, p);
  tree_printnodes(t, p->right);
}

static void tree_printnodes_preorder(tree* t, tnode* p) {
  if (p == NULL) { return; }
  
  tree_printme(t, p);
  tree_printnodes(t, p->left);
  tree_printnodes(t, p->right);
}

static void tree_printnodes_postorder(tree* t, tnode* p) {
    if (p == NULL) { return; }

    tree_printnodes(t, p->left);
    tree_printnodes(t, p->right);
    tree_printme(t, p);
}

static void tree_printnodes_levelorder(tree* t, tnode* p) {
    if (p == NULL) { return; }

    if (t->size == 1) { tree_printme(t,p); }
    else { tree_printnodes(t, p->left); tree_printnodes(t, p->right); }

}

void tree_print(tree* t) {    // INORDER-printing
  tree_printnodes(t, t->root);
  printf("\n");
}

void tree_print_preorder(tree* t) {
  tree_printnodes_preorder(t, t->root);
  printf("\n");
}

void tree_print_postorder(tree* t){
    tree_printnodes_postorder(t, t->root);
    printf("\n");
}

void tree_print_levelorder(tree* t) {
    tree_printnodes_levelorder(t, t->root);
    printf("\n");
}


void tree_test(const char* words[], char flag) {
  tree* t = tree_create();
  int i = 0;
  
  while(words[i] != NULL){
	  printf("%s", words[i]);
	  tree_add(t, words[i++]);
	  }
  
  
  tree_add(t, "now");
  tree_add(t, "is");
  tree_add(t, "the");
  tree_add(t, "time");
  tree_add(t, "for");
  tree_add(t, "all");
  tree_add(t, "good");
  tree_add(t, "men");
  tree_add(t, "and");
  tree_add(t, "women");
  tree_add(t, "to");
  tree_add(t, "come");
  tree_add(t, "to");
  tree_add(t, "the");
  tree_add(t, "aid");
  tree_add(t, "of");
  tree_add(t, "their");
  tree_add(t, "country");
  switch(flag) { //The second command to tell which order to order the words in.
		case 'i':
		printf("Running case inorder\n");
		tree_print(t);
		break;
		case 'p':
		printf("Running case postorder\n");
		tree_print_postorder(t);
		break;
		case 'r':
		printf("Running case preorder\n");
		tree_print_preorder(t);
		break;
		case 'l':
		printf("Running case level order\n");
		tree_print_levelorder(t);
		break;
		defualt: 
		printf("No such command exist");
	}

  printf("is my tree empty? %s\n", yesorno(tree_empty(t)));
  printf("size of tree: %zu\n\n", tree_size(t));
  
  tree_clear(t);
  printf("is my tree empty now? %s\n", yesorno(tree_empty(t)));
  printf("size of tree: %zu\n\n", tree_size(t));
}

void getFile(const char* filename, FILE* fin){

}

char processChoice(const char* choice){
	return choice[1];
	}

bool iscommand(const char* choice){
	return choice[0] == '-';
	}

int main(int argc, const char* argv[]) {
	int i = 1, j = 0, k=0;
	int c, d;
    const char* words[BUFSIZ];
    bool checkedFile = false;
    char fileWord[BUFSIZ];
    //memset(fileWord, 0, BUFSIZ);
	
	switch(processChoice(argv[i])) { //Allows for command line input. To modes: -f for file reading, followed by filename, and -c for console, followed by the words being added.
		case 'f':
		checkedFile = true;
		FILE* fin;
		const char* filename = argv[++i];
		printf("Opening %s...\n", filename);
		fin = fopen(filename, "r");
	    while ((d = fgetc(fin)) != EOF) {
			if(d == ' ' || d == '\n') {
				words[j++] = fileWord;
				k = 0;
				}
			else {
				fileWord[k++] = d;
				
				}
			
		}
		
		fclose(fin);
		c = processChoice(argv[++i]);
		break;
			
		case 'c':
		printf("Running case -c\n");
		
		while(!iscommand(argv[i + 1])){
			words[j++] = argv[++i];
			}
			words[j] = NULL;
		c = processChoice(argv[++i]);
		break;
	}
	
	
	
  tree_test(words, c);
  
  return 0;
}

