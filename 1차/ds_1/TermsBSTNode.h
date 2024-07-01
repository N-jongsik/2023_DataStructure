#pragma once
#include "MemberQueueNode.h"
#include <iostream>
#include <string>
using namespace std;

class TermsBSTNode
{
private:

	TermsBSTNode* left;
	TermsBSTNode* right;

public:
	string bst_name;
	int bst_age;
	string bst_first_date;
	string bst_last_date;
	char bst_type;

	TermsBSTNode(MemberQueueNode newBSTNode) : left(nullptr), right(nullptr), bst_name(newBSTNode.getName()), bst_age(newBSTNode.getAge()), bst_first_date(newBSTNode.getDate()), bst_last_date(""), bst_type(newBSTNode.getType()) {}
	~TermsBSTNode() {}

	TermsBSTNode* getLeft() { return left; }
	TermsBSTNode* getRight() { return right; }

	void setLeft(TermsBSTNode* left) { this->left = left; }
	void setRight(TermsBSTNode* right) { this->right = right; }

	char getBSTType() {
		return bst_type;
	}

	string getBST_first_date()
	{
		return bst_first_date;
	}

	string getBST_last_date()
	{
		return bst_last_date;
	}

	string getBST_name()
	{
		return bst_name;
	}

	int getBST_age()
	{
		return bst_age;
	}

	void setBST_name(string bst_name) { this->bst_name = bst_name; }
	void setBST_age(int bst_age) { this->bst_age = bst_age; }
	void setBST_first_date(string newDate) { bst_first_date = newDate; }
	void setBST_last_date(string newDate) { bst_last_date = newDate; }

	void copyDataFrom(const TermsBSTNode* otherNode) {
		// 데이터 멤버를 복사합니다.
		this->bst_name = otherNode->bst_name;
		this->bst_age = otherNode->bst_age;
		this->bst_first_date = otherNode->bst_first_date;
		this->bst_last_date = otherNode->bst_last_date;
	}
};