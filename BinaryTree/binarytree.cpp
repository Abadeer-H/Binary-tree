#include <iostream>
#include <binarytree.h>

using namespace std;

BinaryTree::BinaryTree()
{
    root = nullptr;
}

BinaryTree::BinaryTree(int a)
{
    root = new node{a};
    root->red = false;
}

BinaryTree::~BinaryTree()
{
    deleteTree(root);
    root = nullptr;
}

void BinaryTree::deleteTree(node *nod)
{
    if (nod->left != nullptr)
    {
        deleteTree(nod->left);
        nod->left = nullptr;
    }
    if (nod->right != nullptr)
    {
        deleteTree(nod->right);
        nod->right = nullptr;
    }
    if (nod->left == nullptr && nod->right == nullptr)
    {
        delete nod;
    }
}

void BinaryTree::pushBack(int a)
{
    BinaryTree::pushBack(a, root);
}

void BinaryTree::pushBack(int a, node *nod)
{
    if (nod == nullptr)
    {
        root = new node{a};
        root->red = false;
        return;
    }

    if (nod->left == nullptr && a < nod->data)
    {
        nod->left = new node{a};
        rebalance(nod->left);
    }
    else if (nod->right == nullptr && a > nod->data)
    {
        nod->right = new node{a};
        rebalance(nod->right);
    }
    else if (nod->left != nullptr && a < nod->data)
    {
        pushBack(a, nod->left);
    }
    else if (nod->right != nullptr && a > nod->data)
    {
        pushBack(a, nod->right);
    }

    if (nod->data == a)
    {
        nod->amount++;
    }
}

BinaryTree::node *BinaryTree::searchGrand(node *nod, node *current) const
{
    if (current == nullptr)
    {
        current = root;
    }

    if (current->left != nullptr && nod->data < current->data)
    {
        if (current->left->left != nullptr && nod->data < current->left->data)
        {
            if (current->left->left == nod)
            {
                return current;
            }
            else
            {
                return searchGrand(nod, current->left);
            }
        }

        if (current->left->right != nullptr && nod->data > current->left->data)
        {
            if (current->left->right == nod)
            {
                return current;
            }
            else
            {
                return searchGrand(nod, current->left);
            }
        }
    }

    if (nod->data > current->data)
    {
        if (nod->data < current->right->data)
        {
            if (current->right->left == nod)
            {
                return current;
            }
            else
            {
                return searchGrand(nod, current->right);
            }
        }

        if (nod->data > current->right->data)
        {
            if (current->right->right == nod)
            {
                return current;
            }
            else
            {
                return searchGrand(nod, current->right);
            }
        }
    }

    return nullptr;
}

void BinaryTree::rebalance(node *nod)
{
    node *grand = searchGrand(nod);

    if (nod == root || grand == nullptr)
    {
        root->red = false;
        return;
    }

    if (nod->data < grand->data && grand->right != nullptr && grand->right->red && grand->left->red)
    {

    }

    if (nod->data < grand->data && (grand->right == nullptr || !grand->right->red) && grand->left->red)
    {
        if (nod == grand->left->right)
        {
            node* cpy = grand->left;
            grand->left = nod;
            cpy->right = nod->left;
            nod->left = cpy;
            nod = nod->left;
        }
        if (nod == grand->left->left)
        {
            node *grandgrand = searchGrand(grand->left);
            node *cpy = grand->left->right;
            node *cpy2 = grand->left;
            grand->left->right = grand;
            grand->left = cpy;
            grand = cpy2;
            grand->red = grand->right->red;
            grand->right->red = !grand->red;
            if (grandgrand == nullptr)
            {
                root = grand;
            }
            else if (grand->data < grandgrand->data)
            {
                grandgrand->left = grand;
            }
            else if (grand->data > grandgrand->data)
            {
                grandgrand->right = grand;
            }
        }
        return;
    }
    if (nod->data > grand->data && (grand->left == nullptr || !grand->left->red) && grand->right->red)
    {
        if (nod == grand->right->left)
        {
            node* cpy = grand->right;
            grand->right = nod;
            cpy->left = nod->right;
            nod->right = cpy;
            nod = nod->right;
        }
        if (nod == grand->right->right)
        {
            node *grandgrand = searchGrand(grand->right);
            node *cpy = grand->right->left;
            node *cpy2 = grand->right;
            grand->right->left = grand;
            grand->right = cpy;
            grand = cpy2;
            grand->red = grand->left->red;
            grand->left->red = !grand->red;
            if (grandgrand == nullptr)
            {
                root = grand;
            }
            else if (grand->data < grandgrand->data)
            {
                grandgrand->left = grand;
            }
            else if (grand->data > grandgrand->data)
            {
                grandgrand->right = grand;
            }
        }
        return;
    }

    if ((nod->data > grand->data && grand->left->red) || (nod->data < grand->data && grand->right->red))
    {
        grand->left->red = false;
        grand->right->red = false;
        grand->red = true;
        if (grand == root)
        {
            grand->red = false;
        }
        if (grand != nullptr)
        {
            rebalance(grand);
        }
    }
}



BinaryTree::node *BinaryTree::search(int a) const
{
    return search(a, root);
}

BinaryTree::node *BinaryTree::search(int a, node *nod) const
{
    if (a == nod->data)
    {
        return nod;
    }

    if (a < nod->data)
    {
        if (nod->left != nullptr)
        {
            return search(a, nod->left);
        }
        else
        {
            return nullptr;
        }
    }
    if (a > nod->data)
    {
        if (nod->right != nullptr)
        {
            return search(a, nod->right);
        }
        else
        {
            return nullptr;
        }
    }
}

void BinaryTree::show(node *nod) const
{
    cout << nod->data;
}

void BinaryTree::deleteNode(int a)
{
    node *nod = search(a);
    if (nod == nullptr)
    {
        cout << "Not found!";
        return;
    }

    node *grand = searchGrand(nod);
    node *parent;

    if (grand != nullptr)
    {
        if (a < grand->data)
        {
            parent = grand->left;
        }
        if (a > grand->data)
        {
            parent = grand->left;
        }
    }
    else
    {
        parent = root;
    }


    if (nod->left == nullptr && nod->right == nullptr && nod->red)
    {
        if (a < parent->data)
        {
            parent->left = nullptr;
        }
        if (a > parent->data)
        {
            parent->right = nullptr;
        }
        delete nod;
        return;
    }


    if (nod->left != nullptr && nod->right == nullptr)
    {
        if (nod->red)
        {
            if (a < parent->data)
            {
                parent->left = nod->left;
            }
            if (a > parent->data)
            {
                parent->right = nod->left;
            }
            delete nod;
            return;
        }
        else
        {
            if (nod->left->red)
            {
                nod->left->red = false;
                if (nod == root)
                {
                    root = nod->left;
                    delete nod;
                    return;
                }

                if (a < parent->data)
                {
                    parent->left = nod->left;
                }
                if (a > parent->data)
                {
                    parent->right = nod->left;
                }
                delete nod;
                return;
            }
        }
    }

    if (nod->left == nullptr && nod->right != nullptr)
    {
        if (nod->red)
        {
            if (a < parent->data)
            {
                parent->left = nod->right;
            }
            if (a > parent->data)
            {
                parent->right = nod->right;
            }
            delete nod;
            return;
        }
    }
    else
    {
        if (nod->right->red)
        {
            nod->right->red = false;

            if (nod == root)
            {
                root = nod->right;
                delete nod;
                return;
            }

            if (a < parent->data)
            {
                parent->left = nod->right;
            }
            if (a > parent->data)
            {
                parent->right = nod->right;
            }
            delete nod;
            return;
        }
    }
}

//void BinaryTree::printTree(node *nod, int space) const
//{
//    if (nod == nullptr)
//    {
//        return;
//    }
//    space += 10;
//    printTree(nod->right, space);
//    printf("\n");
//    for (int i = 10; i < space; i++)
//        printf(" ");
//    printf("%d\n", nod->data);
//    printTree(nod->left, space);
//}

//void BinaryTree::printTree() const
//{
//    printTree(root, 10);
//}
