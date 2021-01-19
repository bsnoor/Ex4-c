#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LettersCount ((int)26) 
#define CharA(c) ((int)c - (int)'a')
#define WORD 30

typedef struct node
{
    char letter;
    int endWord;
    int alreadyPrinted;
    char string[WORD];
    long unsigned int count;
    struct node* children[LettersCount];
} node;

// Returns new trie node (initialized to NULLs)
struct node* getNode(void)
{
    struct node* newNode = NULL;

    newNode = (struct node*)malloc(sizeof(struct node));

    if (newNode)
    {
        int i;

        newNode->endWord = 0;
        newNode->alreadyPrinted = 0;
        newNode->count = 0;
        for (i = 0; i < LettersCount; i++)
            newNode->children[i] = NULL;
    }
    return newNode;
}

void insert(struct node* root, const char* word)
{
    int i;
    int length = strlen(word);
    int index;
    char c;
    char temp[WORD];

    struct node* pCrawl = root;

    for (i = 0; i < length; i++)
    {
        c = tolower(word[i]);
        index = CharA(c);
        //check if is already exist
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();
        *temp = pCrawl->string;
        pCrawl = pCrawl->children[index];

        //insert letter into child
        pCrawl->letter = c;
        //update string
        *pCrawl->string = temp + *pCrawl->string;
    }
    pCrawl->endWord = 1;
    pCrawl->count++;
}

/*
// Returns true if key presents in trie, else false
bool search(struct node* root, const char* key)
{
    int level;
    int length = strlen(key);
    int index;
    struct node* pCrawl = root;

    for (level = 0; level < length; level++)
    {
        index = CHAR_TO_ARRAY(key[level]);

        if (!pCrawl->children[index])
            return false;

        pCrawl = pCrawl->children[index];
    }

    return (pCrawl != NULL && pCrawl->endWord);
}
*/

// Returns many times the word "Key" shows in the tree
int searchCounter(struct node* root, const char* key)
{
    int level;
    int length = strlen(key);
    int index;
    int printedCounter;
    struct node* pCrawl = root;

    for (level = 0; level < length; level++)
    {
        index = CharA(key[level]);

        if (!pCrawl->children[index])
            return false;

        pCrawl = pCrawl->children[index];
    }
    if (!pCrawl->alreadyPrinted) {
        pCrawl->alreadyPrinted = 1;
        printedCounter = pCrawl->count;
        pCrawl->count = -1;
        return (printedCounter);
    }
    return (pCrawl->count);
}

// Sorts an array of strings where length of every
// string should be smaller than MAX_LEN
void selectionSort(char arr[][WORD], int n)
{
    int i, j, min_idx;

    // One by one move boundary of unsorted subarray
    char minStr[WORD];
    for (i = 0; i < n - 1; i++)
    {
        // Find the minimum element in unsorted array
        int min_idx = i;
        strcpy(minStr, arr[i]);
        for (j = i + 1; j < n; j++)
        {
            // If min is greater than arr[j]
            if (strcmp(minStr, arr[j]) > 0)
            {
                // Make arr[j] as minStr and update min_idx
                strcpy(minStr, arr[j]);
                min_idx = j;
            }
        }

        // Swap the found minimum element with the first element
        if (min_idx != i)
        {
            char temp[WORD];
            strcpy(temp, arr[i]); //swap item[pos] and item[i]
            strcpy(arr[i], arr[min_idx]);
            strcpy(arr[min_idx], temp);
        }
    }
}

int main(int argc, char* argv[])
{
    struct node* root = getNode();
    char str1[WORD];
    char newString[10][WORD];
    int i, j, ctr, count;

    fgets(str1, sizeof str1, stdin);

    j = 0; ctr = 0;
    for (i = 0; i <= (strlen(str1)); i++)
    {
        // if space or NULL found, assign NULL into newString[ctr]
        if (str1[i] == ' ' || str1[i] == '\0')
        {
            newString[ctr][j] = '\0';
            ctr++;  //for next word
            j = 0;    //for next word, init index to 0
        }
        else
        {
            newString[ctr][j] = str1[i];
            j++;
        }
    }
    for (i = 0; i < ctr; i++) {
        insert(root, newString[i]);
    }
    selectionSort(newString, ctr);

    if (argc == 2) {
        int check = strcmp(argv[1], "r");
        if (argc == 2 && check == 0) {
            for (i = 0; i < ctr; i++) {
                count = searchCounter(root, newString[i]);
                if (count != -1)
                    printf("%s %d\n", newString[i], count);
            }
        }
    }
    else {
        for (i = ctr - 1; i >= 0; i--) {
            count = searchCounter(root, newString[i]);
            if (count != -1)
                printf("%s %d\n", newString[i], count);
        }
    }
}