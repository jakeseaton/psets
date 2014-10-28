/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/
#include <stdbool.h>
#include <ctype.h>
#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// maximum size of the hashtable
#define HASHSIZE 2886

// declare node
typedef struct node
{
    char nodeword[LENGTH];
    struct node* next;
} node;

// initialize hashtable
node* ht[HASHSIZE];  

// global dictionary size variable
int dicsize = 0;

// hash function
int hash(const char* s)
{
    // initialize return value
    int hashed = 0;
    
    // hash function
    if (!isalpha(s[1]))
    {   
        hashed += 100 * (tolower(s[0]) - 'a');
    }
    else if (!isalpha(s[2]))
    {
        hashed += (100 * (tolower(s[0]) - 'a'));
        hashed += (10 * (tolower(s[1]) - 'a'));
    }
    else
    {
        hashed += (100 * (tolower(s[0]) - 'a'));
        hashed += (10 * (tolower(s[1]) - 'a'));
        hashed += (tolower(s[2]) - 'a');
    }
    return (hashed) ;
    // this should be % HASHSIZE but it is unnecessary
} 

// Helper Function: linear search a linked list
bool search(node* list, const char* s)
{   
    while(list != NULL)
    {
        if (strcasecmp(list->nodeword, s) == 0)
        {
            return true;
        }
        list = list->next;
    }
    return false;
}

// Helper Function: free a linked list
void free_list(node* head)
{
    if (head == NULL)
    {
        free(head);
        return;
    }
    else
    {
        node* cursor = head->next;
        free(head);
        free_list(cursor);
    }
}    

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* checkword)
{   
    // search for the word and return
    if (search(ht[hash(checkword)], checkword) == true)
    {
        return true;
    }      
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{       
    // open dictionary
    FILE* file = fopen(dictionary, "r");
    
    // check for null
    if (file == NULL)
    {
        printf("Could not open\n");
        return false;
    }
        
    // initialize a temporary node
    node* temp_node = malloc(sizeof(node));
    
    // check for null
    if (temp_node == NULL)
    {
        return false;
    }
    
    // read words into the temporary node, until the end of file
    while (fscanf(file, "%45s", temp_node->nodeword) == 1)
    {
        // hash the word
        int value = hash(temp_node->nodeword);
        
        // initialize a new node to be added to the linked list
        node* newnode = malloc(sizeof(node));
        
        // check for NULL
        if (newnode == NULL)
        {
            return false;
        }
        
        // copy the word into the new node
        strcpy(newnode->nodeword, temp_node->nodeword);
        
        // new node points to the start of the linked list
        newnode->next = ht[value];
        
        // the head points to the new node, making it the start
        ht[value] = newnode;

        // increment counter
        dicsize++;
    }
    
    // complete
    free(temp_node);
    fclose(file);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return dicsize;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // iterate through hash table
    for(int i = 0; i < HASHSIZE; i++)
    {
        // free each linked list
        free_list(ht[i]);
    }
    return true;
}
