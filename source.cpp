#include "Header.h"


int main()
{

    ifstream file("words.txt");


    char str[100];

    char* temp_word;

    struct rbtree* root = RB_NULL;

    ////delete////
    cout << "First exp: 'Delete element'" << endl;
    char* _delete = nullptr;

    for (int i = 0; i < 10; i++)
    {

        file.getline(str, 100);

        temp_word = new char[strlen(str) + 1];

        strcpy(temp_word, str);

        rbtree_add(&root, i, temp_word);

        //cout << temp_word << endl;

        if (i == 0)
        {
            _delete = temp_word;
        }

        delete temp_word;
    }

    if (root != RB_NULL || !root)
    {
        rbtree_delete(&root, _delete);
        rbtree_free(&root);
    }
    cout << "element is free" << endl;
    cout << "Exp end" << endl;
    //////////////
    ////lookup////

    ofstream out("lookup.txt");
    out.precision(8);

    cout << "Second exp: 'LookUp element'" << endl;

    root = RB_NULL;

    char** dictionary = (char**)malloc(sizeof(char*) * 50000);

    for (int i = 0; i < 50000; i++)
    {
        file.getline(str, 100);

        temp_word = new char[strlen(str) + 1];

        strcpy(temp_word, str);

        rbtree_add(&root, i, temp_word);

        dictionary[i] = temp_word;


        //cout << dictionary[i] << endl;

        delete temp_word;
    }
    cout << "dictionart is full" << endl;
    for (int i = 0; i < 50000; i = i + 1000)
    {
        auto begin = chrono::steady_clock::now();
        struct rbtree* find = rbtree_lookup(root, dictionary[i]);
        auto end_t = std::chrono::steady_clock::now();
        auto elapsed_us = chrono::duration_cast<chrono::nanoseconds>(end_t - begin);
        out << fixed << i << " " << elapsed_us.count() / 1000000000.0 << '\t' << endl;

    }
    
    delete dictionary;
    out.close();
    file.close();
    cout << "second exp end" << endl;

    rbtree_free(&root);

    cout << "tree is free" << endl;
}
/*


Описать случаи, нарушающие красно-чёрные свойства (при добавлении и удалении узлов):

    Если узел красный, то оба его потомка черные.
    ---Нарушение свойства возможно, если узел имеет красного потомка.

    Для каждого узла все простые пути от него до листьев содержат одинаковое количество черных узлов.
    ---Нарушение свойства возможно, если простые пути от родительского узла до листьев не содержат одинаковое количество черных узлов.

    Если узел черный, то все его потомки должны быть красными или NIL-узлами
    ---Нарушение свойства возможно, если удаленный узел имел черного потомка, который не имеет красного брата.

    
    
*/