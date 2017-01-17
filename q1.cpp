#include<stdio.h>
#include<string.h>
#include<stdlib.h>
using namespace std;
char buf[25];
int row=1, col=1;
struct trienode {
    struct trienode* children[128];
    bool isEnd;
};

typedef struct trienode trienode;

trienode* getnode() {
    trienode* root = NULL;
    root = (trienode*) malloc(sizeof(trienode));
    for(int i = 0; i<128; i++) {
        root->children[i] = NULL;
    }
    root->isEnd = false;
    return root;
}

void insert(trienode* root, char* word) {
    for(int i = 0; word[i]; i++) {
        int index = (int)word[i];
        if(!root->children[index])
            root->children[index] = getnode();
        root = root->children[index];
    }
    root->isEnd = true;
}

bool search(trienode* root, char* word) {
    for(int i = 0; word[i]; i++) {
        int index = (int)word[i];
        if(!(root->children[index])) return false;
        root = root->children[index];
    }
    return (root && root->isEnd);
}

bool check_sep(char c) {
    return (c=='\n' || c=='\t' || c=='#' || c=='(' || c==')' || c==' ' || c=='*' || c==',' || c=='=' || c=='-' || c=='>' || c=='<' || c=='/' || c=='+' || c=='|' || c=='{' || c=='}' || c=='[' || c==']' || c=='?' || c==';' || c==EOF);
    
}

void readtokens(FILE* fp) {
    if(feof(fp)) {
        buf[0]='\0';
        return;
    }
    char c = fgetc(fp);
    col++;
    int i = 0;
    if(c=='\n') {
        row++;
        col = 1;
    }
    while(!check_sep(c)) {
        buf[i++] = c;
        c = fgetc(fp);
        col++;
    }
    buf[i] = '\0';
}
int main() {
    FILE* fp = fopen("keywords","r");
    char fi[25], tok[100];
    trienode* root = getnode();
    while(fscanf(fp, "%s", fi)==1)
        insert(root, fi);
    fclose(fp);
    printf("enter file name: ");
    scanf("%s", fi);
    fp = fopen(fi, "r");
    printf("reserved keywords: \n");
    while(!feof(fp)) {
        readtokens(fp);
        int len = strlen(buf);
        if(len>0) {
//            printf("%s", buf);
            if(search(root, buf)) printf("\'%s\' found at row - %d, col - %d\n", buf,row, col-len-1);
//            putchar('\n');
        }
    }
    return 0;
}
