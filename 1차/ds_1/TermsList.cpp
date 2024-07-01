#include "TermsList.h"
#include <iostream>
#include <string>
#include "MemberQueue.h"
using namespace std;

TermsLIST::TermsLIST() : head(nullptr)
{

}

TermsLIST::~TermsLIST()
{

}

TermsListNode* TermsLIST::getHead()
{
        return head;
}


void TermsLIST::insertNode(MemberQueueNode newNode)
{
    TermsListNode* existingNode = searchNode(newNode);

    if (existingNode == nullptr)
    {
        // 리스트에 존재하지 않는 경우, 새 노드를 생성하여 리스트에 추가
        if (head == nullptr)
        {
            head = new TermsListNode(newNode);
        }
        else
        {
            TermsListNode* currentNode = head;
            while (currentNode->getNext() != nullptr)
            {
                currentNode = currentNode->getNext();
            }
            currentNode->setNext(new TermsListNode(newNode));
        }
    }
    else
    {
        // 리스트에 이미 존재하는 경우, 해당 노드의 회원 수를 증가시킴
        existingNode->incrementMemberCount();
    }
}

TermsListNode* TermsLIST::searchNode(MemberQueueNode newNode)
{
    TermsListNode* currentNode = head;

    while (currentNode != nullptr)
    {
        if (currentNode->getData() == newNode.getType())
        {
            return currentNode; // 주어진 데이터를 가진 노드를 찾았습니다.
        }

        currentNode = currentNode->getNext();
    }

    // 주어진 데이터를 가진 노드를 찾지 못했습니다.
    return nullptr;
}

void TermsLIST::deleteNode(MemberQueueNode newNode)
{
    if (head == nullptr)
    {
        cout << "error 리스트 비어있음" << endl;
        return;
    }

    TermsListNode* currentNode = head;
    TermsListNode* prevNode = nullptr;

    while (currentNode != nullptr)
    {
        if (currentNode->getData() == newNode.getType())
        {
            // 해당 노드를 찾았으면 회원 수를 감소시킴
            currentNode->decrementMemberCount();

            // 만약 회원 수가 0이 되면 노드 삭제
            if (currentNode->getMemberCount() == 0)
            {
                if (prevNode == nullptr)
                {
                    // 삭제할 노드가 헤드인 경우
                    head = currentNode->getNext();
                    delete currentNode;
                }
                else
                {
                    prevNode->setNext(currentNode->getNext());
                    delete currentNode;
                }
            }
            return;
        }

        prevNode = currentNode;
        currentNode = currentNode->getNext();
    }

    // 주어진 데이터를 가진 노드를 찾지 못했습니다.
    cout << "error 해당 가입약관 노드를 찾을 수 없음" << endl;
}
int TermsListNode::getMemberCount()
{
    return count;
}

void TermsListNode::incrementMemberCount()
{
    count++;
}

void TermsListNode::decrementMemberCount()
{
    if (count > 0)
    {
        count--;
    }
}