#include "NameBST.h"
#include <sstream>
#include <string>
#include <iomanip>
#include <fstream>

NameBST::NameBST() : root(nullptr)
{

}
NameBST::~NameBST()
{

}

NameBSTNode* NameBST::getRoot()
{
    return root;
}

bool NameBST::hasNodeWithExpiredDateRecursive(NameBSTNode* node, string date)
{
    if (node == nullptr) {
        return false;
    }

    if (node->getNameBST_last_date() < date) {
        return true; // 만기 날짜가 주어진 날짜보다 이전인 경우 true 반환
    }

    return hasNodeWithExpiredDateRecursive(node->getLeft(), date) ||
        hasNodeWithExpiredDateRecursive(node->getRight(), date);
}

// insert
void NameBST::insertNode(MemberQueueNode newNode)
{
    if (root == nullptr)
    {
        root = new NameBSTNode(newNode);
    }
    else
    {
        insertRecursive(root, newNode);
    }
    ExpirationDate(root, newNode);
}

void NameBST::insertRecursive(NameBSTNode* currentNode, MemberQueueNode newNode)
{

    if (newNode.getName() < currentNode->getNameBST_name())
    {
        // 왼쪽 서브트리로 이동
        if (currentNode->getLeft() == nullptr)
        {
            currentNode->setLeft(new NameBSTNode(newNode));
        }
        else
        {
            insertRecursive(currentNode->getLeft(), newNode);
        }
    }
    else
    {
        // 오른쪽 서브트리로 이동
        if (currentNode->getRight() == nullptr)
        {
            currentNode->setRight(new NameBSTNode(newNode));
        }
        else
        {
            insertRecursive(currentNode->getRight(), newNode);
        }
    }
}

// search
NameBSTNode* NameBST::searchNode(string name)
{
    NameBSTNode* currentNode = root;

    while (currentNode != nullptr)
    {
        if (currentNode->getNameBST_name() == name)
        {
            return currentNode;
        }

        if (name < currentNode->getNameBST_name())
        {
            // 왼쪽 서브트리를 탐색
            currentNode = currentNode->getLeft();
        }
        else
        {
            // 오른쪽 서브트리를 탐색
            currentNode = currentNode->getRight();
        }
    }

    return nullptr;
}

NameBSTNode* NameBST::findMin(NameBSTNode* node)
{
    while (node->getLeft() != nullptr)
    {
        node = node->getLeft();
    }
    return node;
}

//delete
void NameBST::deleteNode(string name) 
{
    // 먼저 해당 노드를 찾음
    NameBSTNode* nodeToDelete = searchNode(name);

    // 노드를 찾지 못한 경우 아무것도 하지 않음
    if (nodeToDelete == nullptr) {
        return;
    }

    // 노드를 삭제하는 데 사용할 부모 노드를 추적
    NameBSTNode* parent = nullptr;
    NameBSTNode* currentNode = root;
    while (currentNode != nullptr && currentNode != nodeToDelete) {
        parent = currentNode;
        if (name < currentNode->getNameBST_name()) {
            currentNode = currentNode->getLeft();
        }
        else {
            currentNode = currentNode->getRight();
        }
    }

    // 1. 자식이 없는 경우 또는 1개의 자식만 있는 경우
    if (nodeToDelete->getLeft() == nullptr || nodeToDelete->getRight() == nullptr) {
        NameBSTNode* child = (nodeToDelete->getLeft() != nullptr) ? nodeToDelete->getLeft() : nodeToDelete->getRight();

        if (parent == nullptr) {
            // 삭제할 노드가 루트 노드인 경우
            root = child;
        }
        else if (parent->getLeft() == nodeToDelete) {
            parent->setLeft(child);
        }
        else {
            parent->setRight(child);
        }

        delete nodeToDelete;
    }
    else {
        // 2. 두 개의 자식이 있는 경우
        // 오른쪽 서브트리에서 최솟값을 찾아서 현재 노드의 값을 업데이트
        NameBSTNode* minValueNode = findMin(nodeToDelete->getRight());
        string minName = minValueNode->getNameBST_name();
        int minAge = minValueNode->getNameBST_age();
        string minFirstDate = minValueNode->getNameBST_first_date();
        string minLastDate = minValueNode->getNameBST_last_date();

        // 오른쪽 서브트리에서 최솟값을 삭제
        deleteNode(minName);
        deleteNode(to_string(minAge));
        deleteNode(minFirstDate);
        deleteNode(minLastDate);


        // 현재 노드의 값을 최솟값으로 업데이트
        nodeToDelete->setNameBST_name(minName);
        nodeToDelete->setNameBST_age(minAge);
        nodeToDelete->setNameBST_first_date(minFirstDate);
        nodeToDelete->setNameBST_last_date(minLastDate);
    }
}

NameBSTNode* deleteMin(NameBSTNode* root) {
    if (root == nullptr) {
        return nullptr;
    }
    if (root->getLeft() == nullptr) {
        NameBSTNode* temp = root->getRight();
        delete root;
        return temp;
    }
    root->setLeft(deleteMin(root->getLeft()));
    return root;
}

void NameBST::deleteNode_date(string date)
{
    root = deleteNode_date_recursive(root, date);
}

NameBSTNode* NameBST::deleteNode_date_recursive(NameBSTNode* root, string date)
{
    if (root == nullptr) {
        return nullptr;
    }

    // 왼쪽 서브트리 삭제 시도
    root->left = deleteNode_date_recursive(root->left, date);

    // 오른쪽 서브트리 삭제 시도
    root->right = deleteNode_date_recursive(root->right, date);

    // 만기 날짜와 비교하여 삭제 여부 결정
    if (root->getNameBST_last_date() < date) 
    {
        // Case 1: 자식 노드가 하나 이거나 없을 경우
        if (root->getLeft() == nullptr) {
            NameBSTNode* temp = root->getRight();
            delete root;
            return temp;
        }
        else if (root->getRight() == nullptr) {
            NameBSTNode* temp = root->getLeft();
            delete root;
            return temp;
        }

        // Case 2: 양쪽 자식 노드가 모두 존재할 경우
        NameBSTNode* minRightSubtree = findMin(root->getRight()); // 오른쪽 서브트리에서 최솟값 찾기

        // 오른쪽 서브트리에서 찾은 최솟값으로 현재 노드의 값을 대체
        
        root->setNameBST_name(minRightSubtree->getNameBST_name());
        root->setNameBST_age(minRightSubtree->getNameBST_age());
        root->setNameBST_first_date(minRightSubtree->getNameBST_first_date());
        root->setNameBST_last_date(minRightSubtree->getNameBST_last_date());
        root->setNameBST_type(minRightSubtree->getNameBST_type());

        // 오른쪽 서브트리에서 최솟값을 삭제
        root->setRight(deleteMin(root->getRight()));
    }

    return root;
}

// print
void printInOrder(NameBSTNode* currentNode, ofstream& flog)
{
    if (currentNode != nullptr)
    {
        printInOrder(currentNode->getLeft(), flog);
        // 노드의 데이터를 출력
        flog << currentNode->getNameBST_name() << "/" << currentNode->getNameBST_age() << "/" << currentNode->getNameBST_first_date() << "/" << currentNode->getNameBST_last_date() << endl;
        cout << currentNode->getNameBST_name() << "/" << currentNode->getNameBST_age() << "/" << currentNode->getNameBST_first_date() << "/" << currentNode->getNameBST_last_date() << endl;
        
        
        printInOrder(currentNode->getRight(),flog);
    }
}
void NameBST::print(ofstream& flog)
{
    printInOrder(root,flog);
}

void NameBST::ExpirationDate(NameBSTNode* currentNode, MemberQueueNode newNode)
{
    if (currentNode != nullptr)
    {
        int year, month, day;
        char dash1, dash2;
        istringstream(currentNode->getNameBST_first_date()) >> year >> dash1 >> month >> dash2 >> day;

        if (newNode.getName() == currentNode->getNameBST_name())
        {
            if (currentNode->getNameBST_type() == 'A')
            {
                month += 6;

                if (month > 12) {
                    year += month / 12;
                    month %= 12;
                }
            }
            else if (currentNode->getNameBST_type() == 'B')
            {
                year++;
            }
            else if (currentNode->getNameBST_type() == 'C')
            {
                year += 2;
            }
            else if (currentNode->getNameBST_type() == 'D')
            {
                year += 3;
            }

            std::tm expirationTime = { 0 };
            expirationTime.tm_year = year - 1900; // tm_year는 1900년부터의 연수
            expirationTime.tm_mon = month - 1;    // tm_mon은 0부터 시작하는 월
            expirationTime.tm_mday = day;

            std::ostringstream formattedDate;
            formattedDate << std::put_time(&expirationTime, "%Y-%m-%d"); // "YYYY-MM-DD" 형식으로 포맷
            std::string newDate = formattedDate.str();

            // 현재 노드의 마지막 날짜 설정
            currentNode->setNameBST_last_date(newDate);
        }

        // 왼쪽 서브트리와 오른쪽 서브트리에 대해서도 만료 날짜 계산
        ExpirationDate(currentNode->getLeft(), newNode);
        ExpirationDate(currentNode->getRight(), newNode);
    }
}
