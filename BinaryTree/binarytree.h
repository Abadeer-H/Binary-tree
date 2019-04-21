#ifndef BINARYTREE_H
#define BINARYTREE_H

class BinaryTree
{
private:
    struct node
    {
        int data;
        node *left = nullptr;
        node *right = nullptr;
        unsigned int amount = 1;
        bool red = true;
        node(int a): data(a) {}
    };
    node *root;

    void deleteTree(node*);
    node *search(int a, node *nod) const;
    void pushBack(int a, node *nod);

public:
    BinaryTree();
    BinaryTree(int a);
    ~BinaryTree();
    void pushBack(int a);
    node *searchGrand(node *nod, node *current = nullptr) const;
    void rebalance(node *nod);
    node *search(int a) const;
    void show(node *) const;
    void deleteNode(int a);
//    void printTree(node*, int) const;
//    void printTree() const;
};

#endif // BINARYTREE_H
