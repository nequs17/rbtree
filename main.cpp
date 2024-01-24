#include "Header.h"


struct rbtree rb_null = { RB_NULL, RB_NULL, RB_NULL, BLACK , 0, nullptr }; // null node


struct rbtree* rbtree_create(int key,char* word)
{
    struct rbtree* node = (rbtree*)malloc(sizeof(rbtree));
    node->color = RED;
    node->key = key;
    node->value = word;

    node->parent = RB_NULL;
    node->left = RB_NULL;
    node->right = RB_NULL;

    return node;
}
/*
void rbtree_add(struct rbtree** root, int key, char* value)
{
    struct rbtree* current = *root;
    struct rbtree* parent = RB_NULL;

    while (current != RB_NULL)
    {
        if (strcmp(value, current->value) < 0)
        {
            current = current->left;
        }
        else if (strcmp(value, current->value) > 0)
        {
            current = current->right;
        }
        else
        {
            current->key = key;
            return;
        }
    }

    struct rbtree* node = rbtree_create(key, value);

    node->parent = parent;

    if (parent == RB_NULL)
    {
        *root = node;
    }
    else if (strcmp(value, parent->value) < 0)
        {
            parent->left = node;
        }
        else
        {
            parent->right = node;
        }
    rbtree_fix(&*root,node);
}
*/

void rbtree_add(struct rbtree** root, int key, char* value)
{
    struct rbtree* current = *root;
    struct rbtree* parent = RB_NULL;

    while (current != RB_NULL)
    {
        if (current->key < key)
        {
            current = current->left;
        }                                           //
        else if (current->key > key) //current->key > key
        {
            current = current->right;
        }
        else
        {
            current->key = key;
            return;
        }
    }

    struct rbtree* node = rbtree_create(key, value);

    node->parent = parent;

    if (parent == RB_NULL)
    {
        *root = node;
    }
    else if (current->key < key)
    {
        parent->left = node;
    }
    else
    {
        parent->right = node;
    }
    rbtree_fix(&*root, node);
}

void rbtree_fix(struct rbtree** root, struct rbtree* current)
{
    while (current->parent->color == RED && current != *root)
    {
        if (current->parent == current->parent->parent->left)
        {
            struct rbtree* uncle = current->parent->parent->right;
            if (uncle->color == RED)
            {
                current->parent->color = BLACK;
                uncle->color = BLACK;
                current->parent->parent->color = RED;
                current = current->parent->parent;
            }
            else if (current = current->parent->right)
            {
                current = current->parent;
                rbtree_left_rotate(root,current);
            }
            current->parent->color = BLACK;
            current->parent->parent->color = RED;
            rbtree_right_rotate(root, current->parent->parent);
        }
        else
        {
            struct rbtree* uncle = current->parent->parent->left;
            if (uncle->color == RED)
            {
                current->parent->color = BLACK;
                uncle->color = BLACK;
                current->parent->parent->color = RED;
                current = current->parent->parent;
            }
            else if(current = current->parent->left)
            {
                current = current->parent;
                rbtree_right_rotate(root, current);
            }
            current->parent->color = BLACK;
            if (current->parent->parent != RB_NULL)
            {
                current->parent->parent->color = RED;
                rbtree_left_rotate(root, current);
            }
        }
    }
    
}

void rbtree_left_rotate(struct rbtree** root, struct rbtree* current)
{
    struct rbtree* y = current->right;

    current->right = y->left;

    if (y->left != RB_NULL)
    {
        y->left->parent = current;
    }

    y->parent = current->parent;

    if (current->parent == RB_NULL)
    {
        *root = y;
    }
    else if (current == current->parent->left)
    {
        current->parent->left = y;
    }
    else
    {
        current->parent->right = y;
    }
    y->left = current;
    current->parent = y;

}

void rbtree_right_rotate(struct rbtree** root, struct rbtree* current)
{
    struct rbtree* y = current->left;

    current->left = y->right;

    if (y->right != RB_NULL)
    {
        y->right->parent = current;
    }

    y->parent = current->parent;

    if (current->parent == RB_NULL)
    {
        *root = y;
    }
    else if (current == current->parent->left)
    {
        current->parent->left = y;
    }
    else
    {
        current->parent->right = y;
    }
    y->right = current;
    current->parent = y;
    
}

struct rbtree* rbtree_lookup(struct rbtree* tree, char* key)
{
    while (tree != RB_NULL)
    {
        if (strcmp(key, tree->value) == 0)
            return tree;
        else if (strcmp(tree->value, key) > 0)
            tree = tree->left;
        else
            tree = tree->right;
    }
    return tree;
}

struct rbtree* rbtree_lookup_key(struct rbtree* tree, int key)
{
    while (tree != RB_NULL)
    {
        if (tree->key == key)
            return tree;
        else if (key > tree->key)
            tree = tree->right;
        else
            tree = tree->left;
    }
    return tree;
}

void rbtree_delete_fix(struct rbtree** root, struct rbtree* x)
{
    while (x != *root && x->color == BLACK)
    {
        if (x == x->parent->left)
        {
            struct rbtree* w = x->parent->right;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                rbtree_left_rotate(root, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->right->color == BLACK)
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    rbtree_right_rotate(root, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                rbtree_left_rotate(root, x->parent);
                x = *root;
            }
        }
        else
        {
            struct rbtree* w = x->parent->left;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                rbtree_right_rotate(root, x->parent);
                w = x->parent->left;
            }
            if (w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    rbtree_left_rotate(root, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rbtree_right_rotate(root, x->parent);
                x = *root;
            }
        }
    }
    x->color = BLACK;
}

void rbtree_delete(struct rbtree** root, char* key)
{
    struct rbtree* z;
    if (!(z = rbtree_lookup(*root, key)))
    {
        return;
    }
    if (z == *root && z->left == RB_NULL && z->right == RB_NULL) // проверка на корень дерева
    {
        delete z;
        *root = RB_NULL;
        return;
    }
    struct rbtree* x = RB_NULL;
    struct rbtree* y = z;
    char ycolor = y->color;

    if (z->left == RB_NULL && z->right == RB_NULL) // проверка на лист
    {
        //x = RB_NULL;
        rbtree_transplant(&*root, z, RB_NULL);
    }
    else if (z->left == RB_NULL)
    {
        x = z->right;
        rbtree_transplant(&*root, z, z->right);
    }
    else if (z->right == RB_NULL)
    {
        x = z->left;
        rbtree_transplant(&*root, z, z->left);
    }
    else
    {
        y = rbtree_max(z->left);
        ycolor = y->color;
        x = y->left;

        if (y->parent != z)
        {
            rbtree_transplant(&*root, y, y->left);
            y->left = z->left;
            y->left->parent = y;
        }
        else
        {
            x->parent = y;
        }
        rbtree_transplant(&*root, z, y);
        y->right = z->right;
        y->right->parent = y;
        y->color = z->color;
    }

    z = RB_NULL;
    //z = RB_NULL;

    if (ycolor == 'B')
    {
        rbtree_delete_fix(&*root, x);
    }

    return;
}

void rbtree_transplant(struct rbtree** root, struct rbtree* u, struct rbtree* v)
{
    if (u->parent == RB_NULL)
        *root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    v->parent = u->parent;
}

struct rbtree* rbtree_min(struct rbtree* tree)
{
    if (tree == RB_NULL)
    {
        return RB_NULL;
    }
    while (tree->left != RB_NULL)
    {
        tree = tree->left;
    }
    return tree;
}

struct rbtree* rbtree_max(struct rbtree* tree)
{
    if (tree == RB_NULL)
    {
        return RB_NULL;
    }
    while (tree->right != RB_NULL)
    {
        tree = tree->right;
    }
    return tree;
}

void rbtree_free(struct rbtree** tree)
{
    if (tree == nullptr)
    {
        return;
    }
    stack<struct rbtree*> array_delete;
    struct rbtree* current = *tree;
    while (current != RB_NULL || !array_delete.empty())
    {
        while (current != RB_NULL)
        {
            array_delete.push(current);
            current = current->left;
        }
        current = array_delete.top();
        array_delete.pop();
        struct rbtree* temp = current;
        current = current->right;
        delete temp;
    }
    *tree = nullptr;
}

