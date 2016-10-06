#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "hash.h"

int hashCode(char* str)
{
	assert(str);
	/* Compute a polynomial hash code for the given string  */

	int i, hash=0, b = 39;

	for(i=0; i<strlen(str); i++)
	{
		hash += (int)str[i]*(int)pow(b, i);
	}

	return hash;
}

Hashtable* htCreate(int mxs)
{
	assert(mxs > 0);
	/* Implement a function that initializes a chaining-based hashtable
	   with mxs lists for storing string keys and int values */

	Hashtable* t = (Hashtable*)malloc(sizeof(Hashtable));
	t->_sz = mxs;
	t->_tab = (HTNode**)malloc(sizeof(HTNode*)*t->_sz);
	int i;
	for(i=0; i<t->_sz; i++)
		t->_tab[i] = NULL;
	return t;
}

void htDestroy(Hashtable* t)
{
	assert(t);
	/* Deallocate all the memory needed for t and its
	   auxiliary structures */

	int i;
	HTNode *ht, *temp;

	for(i=0; i<t->_sz; i++)
	{
		ht = t->_tab[i];
		while(ht)
		{	
			temp = ht;
			ht = ht->_next;
			free(temp->_key);
			free(temp);
		}
		free(ht);
		
	}

	//free(t->_tab);
	//free(t);
}

HTNode* findInList(Hashtable* t, int k, char* key)
{
		assert(t && key && k>=0 && k < t->_sz);
        /* Return a pointer to the node containing 'key' in the k-th
           list of hashtable t, and  NULL otherwise */
	
	HTNode* htnode = t->_tab[k];

	while(htnode)
	{
		if(strcmp(htnode->_key,key)==0) return htnode;
		htnode = htnode->_next;
	}
	return NULL;
}

int htGet(Hashtable* t, char* key)
{
	assert(t && key);
	/* Return the value associated with given key in t. If there is no
	   such value (key does not appear in t) then return 0 */
	int k = abs(hashCode(key)) % t->_sz;

	HTNode* found = findInList(t,k,key);
	if (found)
		return found->_value;
	else return 0;

}

void htPut(Hashtable* t, char* key, int value)
{
	assert(t && key && value>0);
	/* Add the key/value pair to the hashtable t if not already in,
	   otherwise update the value associated with key k */
	int k = abs(hashCode(key)) % t->_sz;
	//HTNode* found = (HTNode*)malloc(sizeof(HTNode));

	HTNode* found = findInList(t,k,key);
	if (found == NULL) {
		HTNode* new = (HTNode*)malloc(sizeof(HTNode));
		new->_key = strdup(key);
		new->_value = value;
		new->_next = t->_tab[k];
		t->_tab[k] = new;
	}
	else {
		found->_value = value;
	}

}


void htRemove(Hashtable* t, char* key)
{
	assert(t && key);
	/* Remove the pair identified by the given key from hashtable t */

	int k = abs(hashCode(key)) % t->_sz;

	HTNode* last = NULL;
	HTNode* cur = t->_tab[k];
	while (cur) {
		if (strcmp(cur->_key,key) == 0) {
			if (last)
				last->_next = cur->_next;
			else t->_tab[k] = cur->_next;
			free(cur->_key);
			free(cur);
			return;
		}
		last = cur;
		cur = cur->_next;
	}
}

char* htMaxValKey(Hashtable* t)
{
	assert(t);
	/* return a key with maximum value in the hash table t */
	
	HTNode* cur = t->_tab[0]; 
	HTNode* max = cur;
	char* key = max->_key;
	int i;

	for(i=0; i<t->_sz; i++)
	{
		cur = t->_tab[i];
		while(cur != NULL)
		{
			if(cur->_value > max->_value){ max = cur;}
			cur = cur->_next;
		}
		
	}

	key = max->_key;
	free(cur);
	free(max);

	return key;

}

