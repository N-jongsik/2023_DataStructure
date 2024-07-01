#pragma once
#include "TermsBSTNode.h"
#include <string>
#include <unordered_map>
using namespace std;

class TermsBST
{
private:
	TermsBSTNode* root;
	std::unordered_map<char, TermsBSTNode*> bstMap;

public:
	TermsBST();
	~TermsBST();

	TermsBSTNode* getRoot();

	//search
	string searchNode(TermsBSTNode* currentNode, string name);
	
	// insert
	void insertNode(MemberQueueNode newNode);
	void insertRecursive(TermsBSTNode* currentNode, MemberQueueNode newNode);

	// print
	void printInOrder(TermsBSTNode* currentNode, ofstream& flog);
	void print(string bstType, ofstream& flog);

	// delete name
	void deleteNode(string name);
	TermsBSTNode* findMin(TermsBSTNode* node);
	TermsBSTNode* deleteRecursive(TermsBSTNode* currentNode, string name);

	// delete date
	void deleteNodesByDateAndTypeAll(string date);
	TermsBSTNode* deleteNodesByDateAndTypeRecursive(TermsBSTNode* root, string date);

	// calculate expiration date
	string ExpirationDate(TermsBSTNode* currentNode, MemberQueueNode newNode);
	void Expiration_Date(TermsBSTNode* currentNode, MemberQueueNode newNode);
};