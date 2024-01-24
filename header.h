#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <inttypes.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <chrono>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <fstream>
#include <string>
#include <time.h>
#include <random>
#include <stack>

using namespace std;

void rbtree_free(struct rbtree** root);

enum color {
    RED,        // 0
    BLACK,      // 1
};

struct rbtree {
    struct rbtree* parent;
    struct rbtree* right;
    struct rbtree* left;

    color color;
    int key;
    char* value;
};

#define RB_NULL &rb_null
extern struct rbtree rb_null;

void rbtree_fix(struct rbtree** root, struct rbtree* current);
void rbtree_delete_fix(struct rbtree** root, struct rbtree* x);
void rbtree_add(struct rbtree** root, int key, char* value);


struct rbtree* rbtree_create(int key, char* word);
struct rbtree* rbtree_lookup(struct rbtree* tree, char* key);
struct rbtree* rbtree_lookup_key(struct rbtree* tree, int key);

void rbtree_delete(struct rbtree** root, char* key);
struct rbtree* rbtree_min(struct rbtree* root);
struct rbtree* rbtree_max(struct rbtree* root);
void rbtree_transplant(struct rbtree** root, struct rbtree* u, struct rbtree* v);


void rbtree_right_rotate(struct rbtree** root, struct rbtree* current);
void rbtree_left_rotate(struct rbtree** root, struct rbtree* current);




