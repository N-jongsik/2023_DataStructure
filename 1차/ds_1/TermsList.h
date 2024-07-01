#pragma once
#include "TermsListNode.h"
#include "MemberQueue.h"

class TermsLIST
{
private:
    TermsListNode* head;

public:
    // ������
    TermsLIST();

    // �Ҹ���
    ~TermsLIST();

    TermsListNode* getHead();

    void insertNode(MemberQueueNode newNode);

    TermsListNode* searchNode(MemberQueueNode newNode);

    void deleteNode(MemberQueueNode newNode);


};
