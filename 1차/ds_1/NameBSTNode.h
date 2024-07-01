#pragma once
#include "MemberQueue.h"
#include <string>

class NameBSTNode
{
private:
	
	


public:
	NameBSTNode* left;
	NameBSTNode* right;

	string NameBST_name;
	int NameBST_age;
	string NameBST_first_date;
	string NameBST_last_date;
	char NameBST_type;

	NameBSTNode(MemberQueueNode newNode) : left(nullptr), right(nullptr), NameBST_name(newNode.getName()), NameBST_age(newNode.getAge()), NameBST_first_date(newNode.getDate()), NameBST_last_date(""), NameBST_type(newNode.getType()) {}
	~NameBSTNode() {}

	NameBSTNode* getLeft() { return left; }
	NameBSTNode* getRight() { return right; }

	void setLeft(NameBSTNode* left) { this->left = left; }
	void setRight(NameBSTNode* right) { this->right = right; }

	string getNameBST_name()
	{
		return NameBST_name;
	}

	int getNameBST_age()
	{
		return NameBST_age;
	}

	string getNameBST_first_date()
	{
		return NameBST_first_date;
	}

	string getNameBST_last_date()
	{
		return NameBST_last_date;
	}

	char getNameBST_type()
	{
		return NameBST_type;
	}

	void setNameBST_name(string NameBST_name) { this->NameBST_name = NameBST_name; }
	void setNameBST_age(int NameBST_age) { this->NameBST_age = NameBST_age; }
	void setNameBST_first_date(string NameBST_first_Date) { this->NameBST_first_date = NameBST_first_Date; }
	void setNameBST_last_date(string NameBST_last_date) { this->NameBST_last_date = NameBST_last_date; }
	void setNameBST_type(char NameBST_type) { this->NameBST_type = NameBST_type; }

};