#pragma once
#include "MemberQueueNode.h"
#include <string>

class MemberQueue
{
private:
	int size;
	int capacity;
	MemberQueueNode* data;
	int frontIdx;
	int rearIdx;

public:
	MemberQueue();
	~MemberQueue();

	bool empty();
	bool full();
	void push(const string& name, int age, const string& date, char type);
	MemberQueueNode pop();
	MemberQueueNode front();
};

