#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 1000
#define MAX_FRIENDS 100

// Red-Black Tree Node Renkleri
#define RED 0
#define BLACK 1

// Kullanici yapisi
struct User {
    int id;
    int friendCount;
    int friends[MAX_FRIENDS];
};

// RBT icin dugum
typedef struct RBTNode {
    struct User* user;
    int color;
    struct RBTNode *left, *right, *parent;
} RBTNode;

RBTNode *root = NULL;

// Fonksiyonlarin on tanimlari
RBTNode* insertRBT(RBTNode* root, struct User* user);
void inorder(RBTNode* root);
RBTNode* createRBTNode(struct User* user);
RBTNode* rotateLeft(RBTNode* root, RBTNode* node);
RBTNode* rotateRight(RBTNode* root, RBTNode* node);
RBTNode* fixInsert(RBTNode* root, RBTNode* node);
RBTNode* searchRBT(RBTNode* root, int id);

struct User users[MAX_USERS];
int userCount = 0;

// Kullanici bul veya ekle
struct User* getUser(int id) {
    for (int i = 0; i < userCount; i++) {
        if (users[i].id == id) return &users[i];
    }
    users[userCount].id = id;
    users[userCount].friendCount = 0;
    return &users[userCount++];
}

void addFriend(int id1, int id2) {
    struct User* u1 = getUser(id1);
    struct User* u2 = getUser(id2);
    u1->friends[u1->friendCount++] = id2;
    u2->friends[u2->friendCount++] = id1;
}

void readDataset(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Dosya acilamadi!\n");
        exit(1);
    }
    char line[100];
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "USER", 4) == 0) {
            int id;
            sscanf(line, "USER %d", &id);
            struct User* u = getUser(id);
            root = insertRBT(root, u);
        } else if (strncmp(line, "FRIEND", 6) == 0) {
            int id1, id2;
            sscanf(line, "FRIEND %d %d", &id1, &id2);
            addFriend(id1, id2);
        }
    }
    fclose(file);
}

void dfs(int startId, int depth, int currentDepth, int visited[], int result[], int* count) {
    visited[startId] = 1;
    if (currentDepth == depth) {
        result[(*count)++] = startId;
        return;
    }
    struct User* u = getUser(startId);
    for (int i = 0; i < u->friendCount; i++) {
        int friendId = u->friends[i];
        if (!visited[friendId]) {
            dfs(friendId, depth, currentDepth + 1, visited, result, count);
        }
    }
}

void findFriends(int userId) {
    int visited[MAX_USERS] = {0};
    int result1[MAX_USERS], result2[MAX_USERS];
    int count1 = 0, count2 = 0;
    dfs(userId, 1, 0, visited, result1, &count1);

    for (int i = 0; i < MAX_USERS; i++) visited[i] = 0;
    dfs(userId, 2, 0, visited, result2, &count2);

    printf("Mesafe 1 arkadaslar: ");
    for (int i = 0; i < count1; i++) if (result1[i] != userId) printf("%d ", result1[i]);
    printf("\nMesafe 2 arkadaslar: ");
    for (int i = 0; i < count2; i++) {
        int id = result2[i];
        if (id != userId) {
            int skip = 0;
            for (int j = 0; j < count1; j++) if (result1[j] == id) skip = 1;
            if (!skip) printf("%d ", id);
        }
    }
    printf("\n");
    printf("Kullanici etkisi: %d\n", count1 + count2);
}

void findCommunity(int userId, int visited[], int group[], int* groupCount) {
    visited[userId] = 1;
    group[(*groupCount)++] = userId;
    struct User* u = getUser(userId);
    for (int i = 0; i < u->friendCount; i++) {
        int fid = u->friends[i];
        if (!visited[fid]) findCommunity(fid, visited, group, groupCount);
    }
}

void printCommunities() {
    int visited[MAX_USERS] = {0};
    printf("Topluluk tespitine geciliyor:\n");
    for (int i = 0; i < userCount; i++) {
        int id = users[i].id;
        if (!visited[id]) {
            int group[MAX_USERS];
            int count = 0;
            findCommunity(id, visited, group, &count);
            printf("Topluluk: ");
            for (int j = 0; j < count; j++) printf("%d ", group[j]);
            printf("\n");
        }
    }
}

void findMutualFriends(int id1, int id2) {
    struct User* u1 = getUser(id1);
    struct User* u2 = getUser(id2);
    int count = 0;
    printf("Ortak Arkadaslari Bulunan ID'ler (%d %d):\n", id1, id2);
    for (int i = 0; i < u1->friendCount; i++) {
        for (int j = 0; j < u2->friendCount; j++) {
            if (u1->friends[i] == u2->friends[j]) {
                printf("%d\n", u1->friends[i]);
                count++;
            }
        }
    }
    printf("Ortak arkadas sayisi: %d\n", count);
}

// ================== RED-BLACK TREE FONKSIYONLARI =====================
RBTNode* createRBTNode(struct User* user) {
    RBTNode* node = (RBTNode*)malloc(sizeof(RBTNode));
    node->user = user;
    node->color = RED;
    node->left = node->right = node->parent = NULL;
    return node;
}

RBTNode* rotateLeft(RBTNode* root, RBTNode* x) {
    RBTNode* y = x->right;
    x->right = y->left;
    if (y->left) y->left->parent = x;
    y->parent = x->parent;
    if (!x->parent) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
    return root;
}

RBTNode* rotateRight(RBTNode* root, RBTNode* y) {
    RBTNode* x = y->left;
    y->left = x->right;
    if (x->right) x->right->parent = y;
    x->parent = y->parent;
    if (!y->parent) root = x;
    else if (y == y->parent->right) y->parent->right = x;
    else y->parent->left = x;
    x->right = y;
    y->parent = x;
    return root;
}

RBTNode* fixInsert(RBTNode* root, RBTNode* z) {
    while (z->parent && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            RBTNode* y = z->parent->parent->right;
            if (y && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    root = rotateLeft(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                root = rotateRight(root, z->parent->parent);
            }
        } else {
            RBTNode* y = z->parent->parent->left;
            if (y && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    root = rotateRight(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                root = rotateLeft(root, z->parent->parent);
            }
        }
    }
    root->color = BLACK;
    return root;
}

RBTNode* insertRBT(RBTNode* root, struct User* user) {
    RBTNode* node = createRBTNode(user);
    RBTNode* y = NULL;
    RBTNode* x = root;
    while (x) {
        y = x;
        if (user->id < x->user->id) x = x->left;
        else x = x->right;
    }
    node->parent = y;
    if (!y) root = node;
    else if (user->id < y->user->id) y->left = node;
    else y->right = node;
    return fixInsert(root, node);
}

int main() {
    readDataset("veriseti.txt");
    int id;
    printf("Arkadaslarini analiz etmek istediginiz kullanici ID'sini girin: ");
    scanf("%d", &id);

    printf("Kullanici ID: %d\n", id);
    findFriends(id);

    int ortak_id;
    printf("Ortak arkadas analizi icin ikinci ID'yi girin: ");
    scanf("%d", &ortak_id);
    findMutualFriends(id, ortak_id);

    printCommunities();
    return 0;
}
