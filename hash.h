typedef struct HTNodeStruct {
	struct HTNodeStruct* _next;
	char*                 _key;
	int                 _value;
} HTNode;

typedef struct HashtableStruct {
	int       _sz;
	HTNode** _tab;
} Hashtable;

Hashtable* htCreate(int mxs);
void htDestroy(Hashtable* t);

int htGet(Hashtable* t, char* key);
void htPut(Hashtable* t, char* key, int value);
void htRemove(Hashtable* t, char* key);

char* htMaxValKey(Hashtable* t);
