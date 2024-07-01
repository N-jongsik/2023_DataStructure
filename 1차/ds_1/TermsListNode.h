#pragma once
#include "MemberQueue.h"
#include "TermsBST.h"

class TermsListNode
{
private:
    TermsListNode* next;
    char pop_type;
    int count;
    TermsBST* bstPointer;

public:
    TermsListNode(MemberQueueNode newNode) : next(nullptr), pop_type(newNode.getType()), count(1), bstPointer(nullptr) {}
    ~TermsListNode() {}

    TermsListNode* getNext() { return next; }

    void setNext(TermsListNode* next) { this->next = next; }

    char getData() {
        return pop_type;
    }

    int getMemberCount();
    void incrementMemberCount();
    void decrementMemberCount();

    // �� �޼��带 ���� TermsBST ��ü�� ���� �����͸� �����մϴ�.
    void setBSTPointer(TermsBST* bst) {
        bstPointer = bst;
    }

    // �� �޼��带 ���� TermsBST ��ü�� ���� �����͸� �����ɴϴ�.
    TermsBST* getBSTPointer() {
        return bstPointer;
    }
};

