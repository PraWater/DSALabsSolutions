#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>

// trie node
struct TrieNode
{
	int noOfChildren;
	struct TrieNode **children;
	char *chars;
// isEndOfWord is true if the node represents
// end of a word
	bool isEndOfWord;
// void* data;
//instead of checking for the presence or absence of a string, if we wish to assign some value with the key as a pair, then this could be uncommented
};

// Returns new trie node (initialized to NULLs)
struct TrieNode *getNode(void)
{
	struct TrieNode *pNode = NULL;pNode = (struct TrieNode *)malloc(sizeof(struct TrieNode));
	if (pNode)
	{
		int i;
		pNode->isEndOfWord = false;
		pNode->noOfChildren = 0;
		pNode->children = NULL;
		pNode->chars = NULL;
	}
	return pNode;
}

// If not present, inserts key into trie
// If the key is prefix of trie node, just marks leaf node
void insert(struct TrieNode *root, const char *key)
{
	int level;
	int length = strlen(key);
	struct TrieNode *pCrawl = root;
	for (level = 0; level < length; level++)
	{
		bool check = false;
		for (int i = 0; i < pCrawl->noOfChildren; ++i) {
			if (pCrawl->chars[i] == key[level]) {
				pCrawl = pCrawl->children[i];
				check = true;
				break;
			}
		}
		if (check) continue;
		if (pCrawl->noOfChildren == 0) {
			pCrawl->children = (struct TrieNode**) malloc(sizeof(struct TrieNode*));
			pCrawl->children[0] = getNode();
			pCrawl->chars = (char*) malloc(1);
		}
		else {
			pCrawl->children = realloc(pCrawl->children, (pCrawl->noOfChildren+1)* sizeof(struct TrieNode*));
			pCrawl->children[pCrawl->noOfChildren] = getNode();
			pCrawl->chars = realloc(pCrawl->chars, pCrawl->noOfChildren + 1);
		}
		pCrawl->chars[pCrawl->noOfChildren] = key[level];
		pCrawl = pCrawl->children[(pCrawl->noOfChildren)++];
	}
// mark last node as leaf
	pCrawl->isEndOfWord = true;
}

// Returns true if key presents in trie, else false
bool search(struct TrieNode *root, const char *key)
{
	int level;
	int length = strlen(key);
	int index;
	struct TrieNode *pCrawl = root;
	for (level = 0; level < length; level++)
	{
		bool check = false;
		for (int i = 0; i < pCrawl->noOfChildren; ++i) {
			if (pCrawl->chars[i] == key[level]) {
				pCrawl = pCrawl->children[i];
				check = true;
				break;
			}
		}
		if (!check) return false;
	}
	return (pCrawl->isEndOfWord);
}

bool delete(struct TrieNode *root, const char *key, int level)
{
	int length = strlen(key);
	if (level == length) {
		root->isEndOfWord = false;
		if (root->noOfChildren == 0) {
			free(root);
			return true;
		}
		else return false;
	}
	int index;
	for (index = 0; index < root->noOfChildren; index++) 
		if (root->chars[index] == key[level]) break;
	if (delete(root->children[index], key, level+1)) --(root->noOfChildren);
	if (root->noOfChildren == 0) {
		free(root->chars);
		free(root);
		return true;
	}
	return false;
}

void freeTrieRecursive(struct TrieNode *root)
{
	if (!root) return;
	if (root->noOfChildren == 0) {
		free(root);
		return;
	}
	for (int i = 0; i < root->noOfChildren; ++i) {
		freeTrieRecursive(root->children[i]);
	}
	free(root->chars);
	free(root);
}

// Driver
int main()
{
// Input keys (use only 'a' through 'z' and lower case)
	char keys[][8] = {"the", "a", "there", "answer", "any", "by", "bye", "their"};
	char output[][32] = {"Not present in trie", "Present in trie"};
	struct TrieNode *root = getNode();
// Construct trie
	int i;
	for (i = 0; i < sizeof(keys)/sizeof(keys[0]); i++)
		insert(root, keys[i]);
// Search for different keys
	printf("%s --- %s\n", "the", output[search(root, "the")] );
	printf("%s --- %s\n", "these", output[search(root, "these")] );
	printf("%s --- %s\n", "their", output[search(root, "their")] );
	printf("%s --- %s\n", "thaw", output[search(root, "thaw")] );
	delete(root, "the", 0);
	printf("%s --- %s\n", "the", output[search(root, "the")] );
	printf("%s --- %s\n", "there", output[search(root, "there")] );
	freeTrieRecursive(root);
	return 0;
}
