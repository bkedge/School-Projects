#include <iostream>
#include "binaryTree.h"

//Brady Kedge
//CS3130
//Project 3

using namespace std;

int main() {

    //Testing
    //cout << "Hello, World!" << endl;

    BinarySearchTree myTree;

    //Initialize array
    int arr[10] = {30, 10, 45, 38, 20, 50, 25, 33, 8, 12};

    //Fill tree with array values
    for(int i = 0; i < 10; i++)
    {
        myTree.InsertNode(arr[i]);
    }

    string input;
    int KeyInput;

    //Testing
    cout << "Tree was made" << endl;

    //MENU//
    do{
        cout << endl;
        cout << "MENU\n";
        cout << "----\n";
        cout << "1. SEARCH\n";
        cout << "2. DELETE\n";
        cout << "3. HEIGHT\n";
        cout << "4. IN-ORDER\n";
        cout << "5. POST-ORDER\n";
        cout << "6. PRE-ORDER\n";
        cout << "7. QUIT\n";

        cout << "Input: ";
        cin >> input;
        cout << endl;

        if(input == "SEARCH")
        {
            cout << "Enter value to search for: ";
            cin >> KeyInput;
            myTree.SearchNode(KeyInput);
        }
        else if(input == "DELETE")
        {
            cout << "Enter value to delete: ";
            cin >> KeyInput;
            bool InTree = myTree.SearchNode(KeyInput);
            if(!InTree)
            {
                cout << "Cannot delete, please try again\n";
            }
            else
            {
                myTree.Remove(KeyInput);
                cout << "Value " << KeyInput <<" was deleted\n";
            }

        }
        else if(input == "HEIGHT")
        {
            cout << "Height of tree is: " << myTree.Height() << endl;
        }
        else if(input == "IN-ORDER")
        {
            //In order
            cout << "In order traversal is: ";
            myTree.InOrder();
            cout << endl;
        }
        else if(input == "POST-ORDER")
        {
            //Post order
            cout << "Post order traversal is: ";
            myTree.PostOrder();
            cout << endl;
        }
        else if(input == "PRE-ORDER")
        {
            //Pre order
            cout << "Pre order traversal is: ";
            myTree.PreOrder();
            cout << endl;
        }


    }while(input != "QUIT");






    return 0;
}

void BinarySearchTree::Insert(Node *&nodePtr, Node *&newNode)
{
    if (nodePtr == NULL) // No node, make one
    {
        nodePtr = newNode;
    }
    else if(newNode->val < nodePtr->val) //New node is less than key
    {
        //Go left
        Insert(nodePtr->left, newNode);
    }
    else //New node is greater than key
    {
        //Go right
        Insert(nodePtr->right, newNode);
    }
}

void BinarySearchTree::InsertNode(int key)
{
    //Setup the new node
    Node *newNode;
    newNode = new Node;
    newNode->val = key;
    newNode->left = newNode->right = NULL;

    //Call insert
    Insert(root, newNode);
}

bool BinarySearchTree::SearchNode(int key)
{
    Node *nodePtr = root;
    cout << "Searching for " << key << endl;

    while(nodePtr)
    {
        //Return true when found
        if(nodePtr->val == key)
        {
            cout << "Matched key, returning true\n";
            return true;
        }
        else if(key < nodePtr->val)
        {
            cout << key << " < " << nodePtr->val << " going left\n";
            nodePtr = nodePtr->left;
        } //Key is less than current val, go left

        else
        {
            cout << key << " > " << nodePtr->val << " going right\n";
            nodePtr = nodePtr->right;
        }//Key is greater than current val, go right

    }

    cout << "Value is not in tree\n";
    return false;
}

void BinarySearchTree::Remove(int key)
{
    DeleteNode(key, root);
}


void BinarySearchTree::DeleteNode(int key, Node *&nodePtr)
{
    if(key < nodePtr->val)
        DeleteNode(key, nodePtr->left);
    else if(key > nodePtr->val)
        DeleteNode(key, nodePtr->right);
    else
        MakeDelete(nodePtr);
}

void BinarySearchTree::InOrder(Node *nodePtr) const
{
    if(nodePtr)
    {
        //Left->Root->Right
        InOrder(nodePtr->left);
        cout << nodePtr->val << " ";
        InOrder(nodePtr->right);

    }
}

void BinarySearchTree::PostOrder(Node *nodePtr) const
{
    if(nodePtr)
    {
        //Left->Right->Root
        PostOrder(nodePtr->left);
        PostOrder(nodePtr->right);
        cout << nodePtr->val << " ";
    }
}

void BinarySearchTree::PreOrder(Node *nodePtr) const
{
    if(nodePtr)
    {
        //Root->Left-Right
        cout << nodePtr->val << " ";
        PreOrder(nodePtr->left);
        PreOrder(nodePtr->right);
    }
}

void BinarySearchTree::MakeDelete(Node *&nodePtr)
{
    //Temp pointer
    Node *tempPtr;

    if(nodePtr == NULL)
        //CANT RETURN EMPTY NODES!!!!
        cout << "Empty Node" << endl;
    else if(nodePtr->right == NULL)
    {
        tempPtr = nodePtr;
        //Attach left child
        nodePtr = nodePtr->left;
        delete tempPtr;
    }
    else if(nodePtr->left == NULL)
    {
        tempPtr = nodePtr;
        //Same as before just attach right child
        nodePtr = nodePtr->right;
        delete tempPtr;
    }
    else  //Two children
    {
        tempPtr = nodePtr -> right;

        //Go far left
        while(tempPtr->left)
        {
            tempPtr = tempPtr->left;
        }

        tempPtr->left = nodePtr->left;
        tempPtr = nodePtr;
        nodePtr = nodePtr->right;
        delete tempPtr;
    }

}



int BinarySearchTree::Height(Node *nodePtr) const
{
    if(nodePtr == NULL)
        return -1;
    else
    {
        int left = Height(nodePtr->left);
        int right = Height(nodePtr->right);

        return 1 + max(left,right);
    }
}

