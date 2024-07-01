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
        // ����Ʈ�� �������� �ʴ� ���, �� ��带 �����Ͽ� ����Ʈ�� �߰�
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
        // ����Ʈ�� �̹� �����ϴ� ���, �ش� ����� ȸ�� ���� ������Ŵ
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
            return currentNode; // �־��� �����͸� ���� ��带 ã�ҽ��ϴ�.
        }

        currentNode = currentNode->getNext();
    }

    // �־��� �����͸� ���� ��带 ã�� ���߽��ϴ�.
    return nullptr;
}

void TermsLIST::deleteNode(MemberQueueNode newNode)
{
    if (head == nullptr)
    {
        cout << "error ����Ʈ �������" << endl;
        return;
    }

    TermsListNode* currentNode = head;
    TermsListNode* prevNode = nullptr;

    while (currentNode != nullptr)
    {
        if (currentNode->getData() == newNode.getType())
        {
            // �ش� ��带 ã������ ȸ�� ���� ���ҽ�Ŵ
            currentNode->decrementMemberCount();

            // ���� ȸ�� ���� 0�� �Ǹ� ��� ����
            if (currentNode->getMemberCount() == 0)
            {
                if (prevNode == nullptr)
                {
                    // ������ ��尡 ����� ���
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

    // �־��� �����͸� ���� ��带 ã�� ���߽��ϴ�.
    cout << "error �ش� ���Ծ�� ��带 ã�� �� ����" << endl;
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