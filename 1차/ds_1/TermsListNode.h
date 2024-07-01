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

    // 이 메서드를 통해 TermsBST 객체에 대한 포인터를 설정합니다.
    void setBSTPointer(TermsBST* bst) {
        bstPointer = bst;
    }

    // 이 메서드를 통해 TermsBST 객체에 대한 포인터를 가져옵니다.
    TermsBST* getBSTPointer() {
        return bstPointer;
    }
};

