//
// Created by Scottie on 3/18/2020.
//

#ifndef UNTITLED_BET_HPP
#define UNTITLED_BET_HPP


#include"bet.h"
#include<iostream>
#include <string>
#include <stack>

BET::BET()                                         //default constructor
{
    root = nullptr;
}

BET::BET(const string &postfix)                   // one parameter constructor  calls build from postfix
{
    root = nullptr;
    buildFromPostfix(postfix);
}

BET::BET(const BET &x)                               //copy constructor
{
    root = clone(x.root);
}

BET::~BET()                                      //destructor
{
    if (!empty()) {
        makeEmpty(root);
    }

}

bool BET::IsOperator(string &x)            // if the string is one of the operators return true, else return false
{
    if (x == "+" || x == "-" || x == "*" || x == "/")
        return true;
    else
        return false;

}

int BET::Precedence(string &x) {            // gives addition and subtraction less priority then multiplication and division, pretty much pemdas
    if (x == "+" || x == "-")
        return 1;
    if (x == "*" || x == "/")
        return 2;
    else
        return 3;
}

bool BET::buildFromPostfix(const string &postfix) // takes a post fix string and builds a tree
{                                                 // inspired by the geeks for geeks site on expression trees
    stack <BinaryNode*> tempstack;                //https://www.geeksforgeeks.org/expression-tree/
    if (!empty())                                   //if its not empty, make it empty
    {
        makeEmpty(root);
    }
    bool flag = true;                               // used for error checking
    string token;
    for (int i = 0; i < postfix.length(); i++)          // iterates through the given postfix string
    {

        token = postfix[i];
        if (token != " ")       // checks to see if the token is a space, if it is do nothing
        {
            if (!IsOperator(token))              //if its an operand
            {

                while (postfix[i + 1] != ' ')            // if the next data in the string is a number concatenate them
                {                                       // for operands bigger than one character

                    token += postfix[i + 1];
                    ++i;
                }

                BinaryNode *temp;
                temp = new BinaryNode(token, nullptr, nullptr);
                tempstack.push(temp);
            } else {                                  // for operators
                BinaryNode *tempL, *tempR;
                if (!tempstack.empty()) {            // if it an operator, take the top operand inn the stack and set it to the right node
                    tempR = tempstack.top();
                    tempstack.pop();
                } else {
                    flag = false;                                   // if the stack is empty an error has occured because there is an operator with out its operands
                }
                if (!tempstack.empty()) {
                    tempL = tempstack.top();          // set the next item in the stack to the right node;
                    tempstack.pop();                    // and pops the two top nodes
                } else {                            // if the stack is empty an error has occured because there is an operator with out its operands
                    flag = false;
                }
                if(!flag)
                {
                    cout<<"ERROR"<<endl;
                    return false;
                }else {
                    BinaryNode *temp1;
                    temp1 = new BinaryNode(token, tempL,tempR);        // pushes the new operaton to the top of the stack
                    tempstack.push(temp1);
                }

            }

        }
    }
    if(tempstack.size()>1)      // if the stack has more than one item return an error, because the one item on the stack should bee the root
    {                           // if there is an operand without an operator
        cout<< "ERROR"<< endl;
        return false;
    } else {
        root = tempstack.top();  // if no errors occured, build the tree
        return true;
    }
}

 const BET &BET::operator=(const BET &x)    // assignment operator
{
    root = clone(x.root);
    return *this;
}

void BET::printInfixExpression()                   //prints infix expression
{
    printInfixExpression(root);
    cout << "\n";
}

void BET::printPostfixExpression()                  //prints postfix expression
{
    printPostfixExpression(root);
    cout << "\n";

}

size_t BET::size()                                 //returns # of nodes in the tree
{
    return size(root);
}

size_t BET::leaf_nodes()                            //returns # of leaf nodes in the tree
{
    return leaf_nodes(root);
}

bool BET::empty()                                   //return true if tree is empty otherwise false
{
    if (root == nullptr)
        return true;
    else
        return false;
}

void BET::printInfixExpression(BinaryNode *n) {                         // I used help from reddit page  using a similar algorithim,
                                                                        //here is the link https://www.reddit.com/r/learnprogramming/comments/6n5gox/c_printing_appropriate_parentheses_in_binary/
     if(!empty()) {
         if (n->left == nullptr || n->right == nullptr)                  // if the node is a leaf, output the data
         {
             cout << n->data;
         } else                                                     // otherwise check precedence of left and right node
         {
             if ((Precedence(n->left->data) < Precedence(n->data))) // checking precedence of the node's data and the left child nodes data, if the precedence is less then output a open parenthesis
             {
                 cout << "( ";                                             // puts parenthesis around the tree with less precendece
                 printInfixExpression(n->left);                           // calls the print function recursively
                 cout << " )";
             } else
                 printInfixExpression(n->left);                          // calls the print function recursively

             cout << ' ' << n->data << ' ';

             if ((Precedence(n->right->data) <=Precedence(n->data)))         // same as checking precedence of left node, just for right node
             {
                 cout << "( ";                                                 // puts parenthesis around the tree with less precendece
                 printInfixExpression(n->right);                              // calls the print function recursively
                 cout << " )";
             } else
                 printInfixExpression(n->right);                          // calls the print function recursively
         }
     }
}

void BET::makeEmpty(BinaryNode *&t) {
    if (t != nullptr)      //if t is not null, then check its children and empty if they are not null recursivly untill the tree is empty
    {
        if (t->left != nullptr) {
            makeEmpty(t->left);
        }
        if (t->right != nullptr) {
            makeEmpty(t->right);
        }
        delete t; // deleted the node after recursive makeempty calls
    }

}

 BinaryNode *BET::clone(BinaryNode *t)             //clone all nodes in the subtree pointed to by t
{

    if (t == nullptr) {             // if the node is empty, return an empty node
        return nullptr;
    } else {                        // otherwise make a new node with the data at t and clone the left and right trees recursively until it hits a leaf
        BinaryNode *temp;
        temp = new BinaryNode(t->data, clone(t->left), clone(t->right));
        return temp;
    }

}

void BET::printPostfixExpression(BinaryNode *n) {
    if (n != nullptr) {                        //as long as the tree isnt empty output the data recursively
        printPostfixExpression(n->left);
        printPostfixExpression(n->right);
        cout << n->data << " ";
    }

}

size_t BET::size(BinaryNode *t) {
    size_t sizecount;
    if (t != nullptr)                      // if there is data in t then add one to the number of items
    {                                   //plus the sizes if its children recursivly
        sizecount = size(t->left) + size(t->right) + 1;
    } else {
        sizecount = 0;
    }
    return sizecount;

}

size_t BET::leaf_nodes(BinaryNode *t) {     //used help from geeks for geeks site for help, here is the link https://www.geeksforgeeks.org/write-a-c-program-to-get-count-of-leaf-nodes-in-a-binary-tree/
    size_t numofleaves = 0;               // by default, the tree has no leaves
    if (t->left == nullptr && t->right == nullptr)  // if t has no children, then it is a leaf
    {
        numofleaves = numofleaves + 1;                          // add 1 to the number of leaves
        return numofleaves;
    } else {
        numofleaves = numofleaves +leaf_nodes(t->left);         // since t is not a leave, check to see if its children are leafs,
        numofleaves = numofleaves + leaf_nodes(t->right);       // and add it to the number of leaves
        return numofleaves;
    }


}

#endif //UNTITLED_BET_HPP
