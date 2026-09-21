#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <limits.h>
#include <float.h>
#include <time.h>

#define NUM_CHARS 256

typedef struct trienode // BASIC DEFINITIONS via STRUCT
{
    struct trienode *children[NUM_CHARS];
    bool terminal;
} trienode;

trienode *createnode()
{ // FUNCTION TO CREATE A NODE IN OUR TRIE
    trienode *newnode = malloc(sizeof *newnode);
    for (int i = 0; i < NUM_CHARS; i++)
    {
        newnode->children[i] = NULL;
    }
    newnode->terminal = false;
    return newnode;
}

bool trieinsert(trienode **root, char *signedtext)
{ // INSERTING A TEXT IN OUR TRIE
    if (*root == NULL)
    {
        *root = createnode();
    }

    unsigned char *text = (unsigned char *)signedtext;
    trienode *tmp = *root;
    int length = strlen(signedtext);

    for (int i = 0; i < length; i++)
    {
        if (tmp->children[text[i]] == NULL)
        {
            // create a new node
            tmp->children[text[i]] = createnode();
        }
        tmp = tmp->children[text[i]];
    }
    if (tmp->terminal)
    {
        return false;
    }
    else
    {
        tmp->terminal = true;
        return true;
    }
}

void printtrie_rec(trienode *node, unsigned char *prefix, int length){ // MAIN FUNCITON TO PRINT THE TRIE 
    unsigned char newprefix[length+2];
    memcpy(newprefix, prefix, length);
    newprefix[length + 1] = 0;
    if(node->terminal){
        printf("WORD: %s \n", prefix);
    }

    for (int i = 0; i < NUM_CHARS; i++)
    {
        if(node->children[i] != NULL){
            newprefix[length] = i;
            printtrie_rec(node->children[i], newprefix, length+1);
        }
    }
    
}

bool searchtrie(trienode *root, char *signedtext){ // BASIC FUNCTION TO SEARCH A TEXT 
    unsigned char *text = (unsigned char *)signedtext;
    int length = strlen(signedtext);
    trienode *tmp = root;

    for (int i = 0; i < length; i++)
    {
        if(tmp->children[text[i]] == NULL){
            return false;
        }

        tmp= tmp->children[text[i]];
    }
    return tmp->terminal;
}




void printtrie(trienode *root){
    if(root == NULL){
        printf("TRIE EMPTY");
        return;
    }
    printtrie_rec(root, NULL, 0);

}


bool node_has_children(trienode *node){
    if(node == NULL) return false;
    for(int i = 0; i< NUM_CHARS; i++){
        if(node->children[i] != NULL){
            // if atleast one child is there..!
            return true; 
        }
    }
    return false;
} 


trienode * deletestr_rec(trienode *node, unsigned char *text, bool *deleted){  // MAIN FUNCTION TO DELETE A GIVEN TEXT UISING RECURSIVE CALLS
    if(node == NULL) return node;

    if(*text == '\0'){
        if(node->terminal){
            node->terminal = false;
            *deleted = true;

        if(node_has_children(node) == false){
            free(node);
            node = NULL;
        }
      }
      return node;
    }

    node->children[text[0]] = deletestr_rec(node->children[text[0]], text+1, deleted);

    if(*deleted && node_has_children(node) == false && node->terminal == false){
        free(node);
        node=NULL;
    }
    return node;
}

bool deletestr(trienode **root, char *signedtext){ // DELETE A TEXT BASIC COVER
    unsigned char *text = signedtext;
    bool result = false;

    if(*root == NULL) return false;
    *root = deletestr_rec(*root, text, &result);
    return result;
}

int main()
{

    trienode *root = NULL;
    trieinsert(&root, "HUEHUE");
    trieinsert(&root, "SHEWELE");
    trieinsert(&root, "SANJU");
    trieinsert(&root, "HOWWARE");
    trieinsert(&root, "ASMIT");
    printtrie(root);
    printf("%d \n",searchtrie(root, "HUEHUE"));
    printf("%d \n",searchtrie(root, "ASMIT"));

    
    deletestr(&root, "ASMIT");
    printtrie(root);
    return 0;
}
