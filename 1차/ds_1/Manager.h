#pragma once
#include "MemberQueue.h"
#include "TermsList.h"
#include "TermsBST.h"
#include "NameBST.h"
#include <fstream>
using namespace std;

class Manager
{
private:

	ifstream	fcmd;
	ofstream	flog;
	MemberQueue Member_Queue;
	TermsLIST Terms_List;
	TermsBST Terms_BST;
	NameBST Name_BST;

public:
	Manager();
	~Manager();

	void run(const char* command);

	void PrintSuccess(const char* cmd);
	void PrintErrorCode(int num);

	// LOAD
	void LOAD();
	// ADD
	void ADD(const string& name, int age, const string& date, char type);
	// QPOP
	void QPOP();
	// SEARCH
	void SEARCH(string name);
	// PRINT
	void PRINT(string data);
	// DELETE
	void DELETE(string name);
	void DELETE_BY_DATE(string date);
	//void DELETE(string arg);
	//EXIT
	void EXIT();
};