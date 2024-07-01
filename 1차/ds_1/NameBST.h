#pragma once
#include "NameBSTNode.h"

class NameBST
{
private:
	NameBSTNode* root;

public:

	NameBST();
	~NameBST();

	NameBSTNode* getRoot();

	bool hasNodeWithExpiredDateRecursive(NameBSTNode* node, string date);

	// insert
	void insertNode(MemberQueueNode newNode);
	void insertRecursive(NameBSTNode* currentNode, MemberQueueNode newNode);

	// search name
	NameBSTNode* searchNode(string name);

	// delete name
	void deleteNode(string name);
	NameBSTNode* findMin(NameBSTNode* node);

	// delete date
	void deleteNode_date(string date);
	NameBSTNode* deleteNode_date_recursive(NameBSTNode* root, string date);

	// print
	void print(ofstream& flog);

	// calculate expiration date 
	void ExpirationDate(NameBSTNode* currentNode, MemberQueueNode newNode);
};