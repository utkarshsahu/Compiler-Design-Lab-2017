#include<stdio.h>
#include<stdlib.h>
using namespace std;

struct trienode {
    struct trienode* children[26];
    bool isEnd;
};

typedef struct trienode trienode;

trienode* getnode() {
    trienode* root = NULL;
    root = (trienode*) malloc(sizeof(trienode));
    for(int i = 0; i<26; i++) {
        root->children[i] = NULL;
    }
    root->isEnd = false;
    return root;
}

void insert(trienode* root, char* word) {
    for(int i = 0; word[i]; i++) {
        int index = (int)(word[i]-'a');
        if(!root->children[index])
            root->children[index] = getnode();
        root = root->children[index];
    }
    root->isEnd = true;
}

bool search(trienode* root, char* word) {
    for(int i = 0; word[i]; i++) {
        int index = (int)(word[i]-'a');
        if(!(root->children[index])) return false;
        root = root->children[index];
    }
    return (root && root->isEnd);
}

int main() {
    FILE* fp = fopen("keywords","r");
    char buf[25], tok[100];
    trienode* root = getnode();
    while(fscanf(fp, "%s", buf)==1)
        insert(root, buf);
    fclose(fp);
    printf("enter file name: ");
    scanf("%s", buf);
    fp = fopen(buf, "r");
    printf("reserved keywords: \n");
    while(fscanf(fp, "%s", tok)==1) {
        printf("%s\n",tok);
        if(search(root, tok)) printf("%s\n", tok);
        else printf("no %s\n", tok);
    }
    return 0;
}
