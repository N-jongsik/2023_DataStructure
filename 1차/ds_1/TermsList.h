#pragma once
#include "TermsListNode.h"
#include "MemberQueue.h"

class TermsLIST
{
private:
    TermsListNode* head;

public:
    // 持失切
    TermsLIST();

    // 社瑚切
    ~TermsLIST();

    TermsListNode* getHead();

    void insertNode(MemberQueueNode newNode);

    TermsListNode* searchNode(MemberQueueNode newNode);

    void deleteNode(MemberQueueNode newNode);


};
