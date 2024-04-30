#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>
#define ALPHABET_SIZE 52 //you can instead reduce the alphabet size and create your own mapping of character to index in array
int CHAR_TO_INDEX(char c)
{
	int a = (int)c;
	if (a <= 90) {
		return a-65;
	}
	return a-97;
//custom mapping if alphabet size reduced
}
// trie node
struct TrieNode
{
	int noOfChildren;
	struct TrieNode *children[ALPHABET_SIZE];
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
		for (i = 0; i < ALPHABET_SIZE; i++)
		pNode->children[i] = NULL;
	}
	return pNode;
}

// If not present, inserts key into trie
// If the key is prefix of trie node, just marks leaf node
void insert(struct TrieNode *root, const char *key)
{
	int level;
	int length = strlen(key);
	int index;
	struct TrieNode *pCrawl = root;
	for (level = 0; level < length; level++)
	{
		index = CHAR_TO_INDEX(key[level]);
		if (!pCrawl->children[index])
		{
			pCrawl->children[index] = getNode();
			++(pCrawl->noOfChildren);
		}
		pCrawl = pCrawl->children[index];
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
		index = CHAR_TO_INDEX(key[level]);
		if (!pCrawl->children[index])
			return false;
		pCrawl = pCrawl->children[index];
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
		return false;
	}
	int index = CHAR_TO_INDEX(key[level]);
	if (delete(root->children[index], key, level+1)) --(root->noOfChildren);
	if (root->noOfChildren == 0) {
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
	for (int i = 0; i < ALPHABET_SIZE; ++i) {
		if (root->children[i]) freeTrieRecursive(root->children[i]);
	}
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
