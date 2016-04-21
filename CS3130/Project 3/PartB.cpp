//Brady Kedge
//CS3130
//Project 3 Part B

#include <iostream>
#include "binaryTree.h"
#include <stdlib.h>
#include <time.h>

using namespace std;

int main()
{
    BinarySearchTree bTree;

    //Values for T and N
    int Tvalues[3] = {5, 10, 15};
    int Nvalues [3] = {100, 500, 1000};

    int heightTotal;
    double AverageHeight;
    int arrSize;
    int randNum;

    //Random seed
    srand((unsigned int) time(NULL));


    //N
    for(int i=0; i < 3; i++)
    {
        //Testing
        //cout << "Looping through i: " << i;

        //T
        for(int j=0; j < 3; j++)
        {
            //Testing
            //cout << "Looping through j: " << j;
            heightTotal = 0;

            //Makes Tvalues[j] trees
            for(int m=0; m < Tvalues[j]; m++)
            {
                arrSize = Nvalues[i];
                int treeArray[arrSize];

                for(int h=0; h < Nvalues[i]; h++)
                {
                    randNum = rand() % 5000 + 1;
                    treeArray[h] = randNum;
                    //bTree.InsertNode(treeArray[h]);

                }

                //Inserts the values
                for(int n=0; n < Nvalues[i]; n++)
                {
                    bTree.InsertNode(treeArray[n]);

                }

                heightTotal += bTree.Height();
            }

            //Average height
            AverageHeight = heightTotal / Tvalues[j];
            //cout << AverageHeight;

            if(j == 1 && i == 2)
            {
                cout << "T = " << Tvalues[j] << endl;
                cout << "N = " << Nvalues[i] << endl;
                cout << "Average Height is: " << AverageHeight;
            }

        }
    }


    return 0;
}


//////////////////////////////
//Same functions from Part A//
/////////////////////////////

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

