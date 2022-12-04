//
// Created by Scottie on 3/18/2020.
//

#ifndef UNTITLED_BET_H
#define UNTITLED_BET_H
#include <string>


using namespace std;
struct BinaryNode{
    string data;
    BinaryNode *left;
    BinaryNode *right;
    BinaryNode() //defaut constructor
    {
        data=nullptr;
        left=nullptr;
        right=nullptr;
    }
    BinaryNode(const string & d,BinaryNode *L,BinaryNode * R)
    {
        left=L;
        right=R;
        data=d;
    }
};
class BET{

private:


    void printInfixExpression(BinaryNode *n);
    void makeEmpty(BinaryNode* &t);
     BinaryNode * clone(BinaryNode *t);              //clone all nodes in the subtree pointed to by t
    void printPostfixExpression(BinaryNode *n);
    size_t size(BinaryNode *t) ;
    size_t leaf_nodes(BinaryNode *t);
    BinaryNode *root;
    bool IsOperator(string & x);                    // boolean to check if the tolken is an operator or not
    int Precedence(string & x);

public:
    BET();                                          //default constructor
    BET(const string & postfix);                    // one parameter constructor
    BET(const BET&);                                //copy constructor
    ~BET();                                         //destructor
    bool buildFromPostfix(const string& postfix);   //
    const BET & operator=(const BET &);             // assignment operator
    void printInfixExpression();                    //prints infix expression
    void printPostfixExpression();                  //prints postfix expression
    size_t size();                                  //returns # of nodes in the tree
    size_t leaf_nodes();                            //returns # of leaf nodes in the tree
    bool empty();                                   //return true if tree is empty


};
































#endif //UNTITLED_BET_H
