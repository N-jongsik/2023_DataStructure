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
        return true; // ���� ��¥�� �־��� ��¥���� ������ ��� true ��ȯ
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
        // ���� ����Ʈ���� �̵�
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
        // ������ ����Ʈ���� �̵�
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
            // ���� ����Ʈ���� Ž��
            currentNode = currentNode->getLeft();
        }
        else
        {
            // ������ ����Ʈ���� Ž��
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
    // ���� �ش� ��带 ã��
    NameBSTNode* nodeToDelete = searchNode(name);

    // ��带 ã�� ���� ��� �ƹ��͵� ���� ����
    if (nodeToDelete == nullptr) {
        return;
    }

    // ��带 �����ϴ� �� ����� �θ� ��带 ����
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

    // 1. �ڽ��� ���� ��� �Ǵ� 1���� �ڽĸ� �ִ� ���
    if (nodeToDelete->getLeft() == nullptr || nodeToDelete->getRight() == nullptr) {
        NameBSTNode* child = (nodeToDelete->getLeft() != nullptr) ? nodeToDelete->getLeft() : nodeToDelete->getRight();

        if (parent == nullptr) {
            // ������ ��尡 ��Ʈ ����� ���
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
        // 2. �� ���� �ڽ��� �ִ� ���
        // ������ ����Ʈ������ �ּڰ��� ã�Ƽ� ���� ����� ���� ������Ʈ
        NameBSTNode* minValueNode = findMin(nodeToDelete->getRight());
        string minName = minValueNode->getNameBST_name();
        int minAge = minValueNode->getNameBST_age();
        string minFirstDate = minValueNode->getNameBST_first_date();
        string minLastDate = minValueNode->getNameBST_last_date();

        // ������ ����Ʈ������ �ּڰ��� ����
        deleteNode(minName);
        deleteNode(to_string(minAge));
        deleteNode(minFirstDate);
        deleteNode(minLastDate);


        // ���� ����� ���� �ּڰ����� ������Ʈ
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

    // ���� ����Ʈ�� ���� �õ�
    root->left = deleteNode_date_recursive(root->left, date);

    // ������ ����Ʈ�� ���� �õ�
    root->right = deleteNode_date_recursive(root->right, date);

    // ���� ��¥�� ���Ͽ� ���� ���� ����
    if (root->getNameBST_last_date() < date) 
    {
        // Case 1: �ڽ� ��尡 �ϳ� �̰ų� ���� ���
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

        // Case 2: ���� �ڽ� ��尡 ��� ������ ���
        NameBSTNode* minRightSubtree = findMin(root->getRight()); // ������ ����Ʈ������ �ּڰ� ã��

        // ������ ����Ʈ������ ã�� �ּڰ����� ���� ����� ���� ��ü
        
        root->setNameBST_name(minRightSubtree->getNameBST_name());
        root->setNameBST_age(minRightSubtree->getNameBST_age());
        root->setNameBST_first_date(minRightSubtree->getNameBST_first_date());
        root->setNameBST_last_date(minRightSubtree->getNameBST_last_date());
        root->setNameBST_type(minRightSubtree->getNameBST_type());

        // ������ ����Ʈ������ �ּڰ��� ����
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
        // ����� �����͸� ���
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
            expirationTime.tm_year = year - 1900; // tm_year�� 1900������� ����
            expirationTime.tm_mon = month - 1;    // tm_mon�� 0���� �����ϴ� ��
            expirationTime.tm_mday = day;

            std::ostringstream formattedDate;
            formattedDate << std::put_time(&expirationTime, "%Y-%m-%d"); // "YYYY-MM-DD" �������� ����
            std::string newDate = formattedDate.str();

            // ���� ����� ������ ��¥ ����
            currentNode->setNameBST_last_date(newDate);
        }

        // ���� ����Ʈ���� ������ ����Ʈ���� ���ؼ��� ���� ��¥ ���
        ExpirationDate(currentNode->getLeft(), newNode);
        ExpirationDate(currentNode->getRight(), newNode);
    }
}
