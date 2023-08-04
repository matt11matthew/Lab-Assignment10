#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{
    struct Trie* children[26];
    int count;
};
struct Trie *createTrie();
// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    if (pTrie == NULL || word == NULL) {
        return;
    }

    // Traverse the Trie using characters of the word
    struct Trie* currentNode = pTrie;
    for (int i = 0; word[i] != '\0'; i++) {
        char c = word[i];
        int index = c - 'a'; // Assuming only lowercase English letters

        // If the current character's node doesn't exist, create a new node
        if (currentNode->children[index] == NULL) {
            currentNode->children[index] = createTrie();
        }

        // Move to the next node
        currentNode = currentNode->children[index];
    }

    // Mark the end of the word in the Trie and update the count
    currentNode->count++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word) {
    struct Trie *current = pTrie;

    // Traverse the trie based on the letters of the word


    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';

        if (current->children[index] == NULL) {
            return 0;
        }
        current = current->children[index];
    }
    return current->count;
}


void deallocateNode(struct Trie *node) {
    if (node == NULL) return;
    for (int i = 0; i < 26; i++)
        deallocateNode(node->children[i]);
    free(node);
}

struct Trie *deallocateTrie(struct Trie *pTrie) {
    if (pTrie == NULL) return NULL;

    deallocateNode(pTrie);
    free(pTrie);
    pTrie = NULL; // Set the pointer to NULL after deallocation

    return pTrie;
}


// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie* trie = malloc((sizeof(struct Trie)));

    trie->count = 0;
    for (int i = 0;  i < 26; i++) {
        trie->children[i] = NULL;
    }
    return trie;
}
// Function to duplicate a string
char* duplicateString(const char* str) {
    size_t len = strlen(str);
    char* newStr = (char*)malloc((len + 1) * sizeof(char));
    if (newStr == NULL) {
        perror("Memory allocation error");
        return NULL;
    }
    strcpy(newStr, str);
    return newStr;
}
int readAllLinesFromFile(const char* filename, char* allLines[]) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening the file");
        return -1;
    }

    // Read the number of lines from the first line of the file
    int numLines;
    if (fscanf(file, "%d", &numLines) != 1) {
        perror("Error reading the number of lines");
        fclose(file);
        return -1;
    }

    // Read lines and store them in the array
    char line[256]; // Assuming lines are not longer than 100 characters
    for (int i = 0; i < numLines; i++) {
        if (fgets(line, sizeof(line), file) == NULL) {
            perror("Error reading line");
            for (int j = 0; j < i; j++) {
                free(allLines[j]);
            }
            fclose(file);
            return -1;
        }
        int lineLength = strlen(line);
        if (line[lineLength - 1] == '\n') {
            line[lineLength - 1] = '\0'; // Remove the newline character
        }
        allLines[i] = duplicateString(line); // Store the line in the array
        if (allLines[i] == NULL) {
            perror("Memory allocation error");
            for (int j = 0; j <= i; j++) {
                free(allLines[j]);
            }
            fclose(file);
            return -1;
        }
    }

    fclose(file);
    return numLines;
}
int main(void)
{
    char *inWords[256];

    //read the number of the words in the dictionary
//    int numWords = readDictionary("dictionary.txt", inWords);
    int numWords = readAllLinesFromFile("C:\\Users\\Matthew Eisenberg\\Documents\\DREnhancedMod\\Projects\\DRMod\\Lab-Assignment10\\dictionary.txt", inWords);
    for (int i=0;i<numWords;++i)
    {
        printf("%s\n",inWords[i]);
    }

    struct Trie *pTrie = createTrie();
    for (int i=0;i<numWords;i++)
    {
        insert(pTrie, inWords[i]);
    }
    // parse lineby line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i=0;i<5;i++)
    {
        printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
    }
    pTrie = deallocateTrie(pTrie);
    if (pTrie != NULL)
        printf("There is an error in this program\n");
    return 0;
}