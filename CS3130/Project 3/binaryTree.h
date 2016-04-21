//Brady Kedge
//CS3130
//Project 3

#ifndef ALGOPROJECT3_BINARYTREE_H
#define ALGOPROJECT3_BINARYTREE_H

class BinarySearchTree
{
private:

    //Node structure
    struct Node
    {
        int val;
        Node *left;
        Node *right;
    };

    //Points to root
    Node *root;

    void Insert(Node *&, Node *&);
    void DeleteNode(int, Node *&);
    void MakeDelete(Node *&);
    void InOrder(Node *) const;
    void PreOrder(Node *) const;
    void PostOrder(Node *) const;
    int Height(Node *) const;


public:
    //Constructor
    BinarySearchTree()
    {
        root = NULL;
    }


    void InsertNode(int);
    bool SearchNode(int);
    void Remove(int);

    int Height() const
    {
        Height(root);
    }


    void InOrder() const
    {
        InOrder(root);
    }

    void PreOrder() const
    {
        PreOrder(root);
    }

    void PostOrder() const
    {
        PostOrder(root);
    }
};

#endif //ALGOPROJECT3_BINARYTREE_H
