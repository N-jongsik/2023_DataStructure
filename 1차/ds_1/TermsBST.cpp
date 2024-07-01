#include "TermsBST.h"
#include <sstream>
#include <iomanip>
#include <fstream>


TermsBST::TermsBST() : root(nullptr)
{
    bstMap['A'] = nullptr;
    bstMap['B'] = nullptr;
    bstMap['C'] = nullptr;
    bstMap['D'] = nullptr;
}
TermsBST::~TermsBST()
{

}


TermsBSTNode* TermsBST::getRoot()
{
    return root;
}

// insert
void TermsBST::insertNode(MemberQueueNode newNode) {
    char bstType = newNode.getType();

    if (bstMap.find(bstType) == bstMap.end()) {
        cout << "����: ��ȿ���� ���� ���Ծ�� Ÿ���Դϴ�." << endl;
        return;
    }

    if (bstMap[bstType] == nullptr) {
        bstMap[bstType] = new TermsBSTNode(newNode);
    }
    else {
        insertRecursive(bstMap[bstType], newNode);
    }
    Expiration_Date(bstMap[bstType], newNode);
}

void TermsBST::insertRecursive(TermsBSTNode* currentNode, MemberQueueNode newNode)
{
    if (newNode.getDate() < currentNode->getBST_first_date())
    {
        if (currentNode->getLeft() == nullptr)
        {
            currentNode->setLeft(new TermsBSTNode(newNode));
        }
        else
        {
            insertRecursive(currentNode->getLeft(), newNode);
        }
    }
    else
    {
        if (currentNode->getRight() == nullptr)
        {
            currentNode->setRight(new TermsBSTNode(newNode));
        }
        else
        {
            insertRecursive(currentNode->getRight(), newNode);
        }
    }
}

// print
void TermsBST::printInOrder(TermsBSTNode* currentNode, ofstream& flog)
{
    if (currentNode != nullptr) {
        // ���� ����Ʈ�� ���
        if (currentNode->getLeft() != nullptr) {
            printInOrder(currentNode->getLeft(), flog);
        }

        // ���� ��� ���
        flog << currentNode->getBST_name() << "/" << currentNode->getBST_age() << "/" << currentNode->getBST_first_date() << "/" << currentNode->getBST_last_date() << endl;
        cout << currentNode->getBST_name() << "/" << currentNode->getBST_age() << "/" << currentNode->getBST_first_date() << "/" << currentNode->getBST_last_date() << endl;
       

        // ������ ����Ʈ�� ���
        if (currentNode->getRight() != nullptr) {
            printInOrder(currentNode->getRight(), flog);
        }
    }
}


void TermsBST::print(string bstType, ofstream& flog) {
    char bstCharType = bstType[0];
    if (bstMap.find(bstCharType) == bstMap.end() || bstMap[bstCharType] == nullptr) 
    {
        flog << "===== ERROR =====" << endl;
        flog << 500 << endl;
        flog << "=================" << endl << endl;

        cout << "===== ERROR =====" << endl;
        cout << 500 << endl;
        cout << "=================" << endl << endl;
        return;
    }
    else if (bstCharType == 'A')
    {
        flog << "===== PRINT =====" << endl;
        flog << "TermsBST " << bstCharType << endl;

        cout << "===== PRINT =====" << endl;
        cout << "TermsBST " << bstCharType << endl;
    }
    else if (bstCharType == 'B')
    {
        flog << "===== PRINT =====" << endl;
        flog << "TermsBST " << bstCharType << endl;

        cout << "===== PRINT =====" << endl;
        cout << "TermsBST " << bstCharType << endl;
    }
    else if (bstCharType == 'C')
    {
        flog << "===== PRINT =====" << endl;
        flog << "TermsBST " << bstCharType << endl;

        cout << "===== PRINT =====" << endl;
        cout << "TermsBST " << bstCharType << endl;
    }
    else if (bstCharType == 'D')
    {
        flog << "===== PRINT =====" << endl;
        flog << "TermsBST " << bstCharType << endl;

        cout << "===== PRINT =====" << endl;
        cout << "TermsBST " << bstCharType << endl;
    }

    // ���� ��ȸ�� ����ϴ� ���� ����
    printInOrder(bstMap[bstCharType], flog);

    flog << "==============" << endl << endl;
    cout << "==============" << endl << endl;
}

// ��¥�� ����Ͽ� ��带 �˻��ϰ� ��¥�� ��ȯ�ϴ� �Լ�
string TermsBST::searchNode(TermsBSTNode* currentNode, string name)
{
    if (currentNode == nullptr) {
        return ""; // ��带 ã�� ���� ��� �� ���ڿ� ��ȯ
    }

    if (currentNode->getBST_name() == name)
    {
        return currentNode->getBST_first_date();
    }
    // ���� ����Ʈ������ ã��
    string leftResult = searchNode(currentNode->getLeft(), name);

    // ������ ����Ʈ������ ã��
    string rightResult = searchNode(currentNode->getRight(), name);

    // ���� ����Ʈ������ ã�� ��� �� �ϳ��� ã�Ҵٸ� �ش� ��� ��ȯ
    if (leftResult != "") {
        return leftResult;
    }
    else {
        return rightResult;
    }
}

// delete
void TermsBST::deleteNode(string name) {
    char bstType = ' ';  // �ʱⰪ ����
    for (const auto& pair : bstMap) {
        char type = pair.first;
        TermsBSTNode* rootNode = pair.second;
        string date = searchNode(rootNode, name);
        if (!date.empty()) {
            bstType = type;
            bstMap[bstType] = deleteRecursive(bstMap[bstType], date);
            break;
        }
    }
    if (bstType == ' ') {
        std::cout << "����: ������ �̸��� ã�� �� �����ϴ�." << std::endl;
        return;
    }
}
 
TermsBSTNode* TermsBST::deleteRecursive(TermsBSTNode* currentNode, string date) {
    if (currentNode == nullptr) {
        return currentNode; // ��带 ã�� ���� ���, �ƹ��͵� �������� �ʰ� ��ȯ�մϴ�.
    }

    if (date < currentNode->getBST_first_date()) {
        // ���� ���� Ʈ������ ���� �۾� ����
        currentNode->setLeft(deleteRecursive(currentNode->getLeft(), date));
    }
    else if (date > currentNode->getBST_first_date()) {
        // ������ ���� Ʈ������ ���� �۾� ����
        currentNode->setRight(deleteRecursive(currentNode->getRight(), date));
    }
    else {
        // ������ ��带 ã�� ���
        if (currentNode->getLeft() == nullptr) {
            // ���� �ڽ��� ���ų� �ڽ� �� ���ʸ� ���� ���
            TermsBSTNode* temp = currentNode->getRight();
            delete currentNode;
            return temp;
        }
        else if (currentNode->getRight() == nullptr) {
            // ������ �ڽĸ� ���� ���
            TermsBSTNode* temp = currentNode->getLeft();
            delete currentNode;
            return temp;
        }

        // ���� �ڽ� ��尡 ��� �ִ� ���
        // ������ ���� Ʈ������ ���� ���� ��带 ã�Ƽ� ���� ���� ��ü�մϴ�.
        TermsBSTNode* temp = findMin(currentNode->getRight());
        currentNode->setBST_name(temp->getBST_name());
        currentNode->setBST_age(temp->getBST_age());
        currentNode->setBST_first_date(temp->getBST_first_date());
        currentNode->setBST_last_date(temp->getBST_last_date());

        // ������ ���� Ʈ������ ���� ���� ��带 �����մϴ�.
        currentNode->setRight(deleteRecursive(currentNode->getRight(), temp->getBST_name()));
    }

    return currentNode;
}

TermsBSTNode* TermsBST::findMin(TermsBSTNode* node)
{
    // ���� ���� ���� ���� ���ʿ� ��ġ�� ����Դϴ�.
    while (node->getLeft() != nullptr) {
        node = node->getLeft();
    }
    return node;
}

TermsBSTNode* deleteMin(TermsBSTNode* root) 
{
    if (root == nullptr) {
        return nullptr;
    }
    if (root->getLeft() == nullptr) {
        TermsBSTNode* temp = root->getRight();
        delete root;
        return temp;
    }
    root->setLeft(deleteMin(root->getLeft()));
    return root;
}

void TermsBST::deleteNodesByDateAndTypeAll(string date) 
{
    for (char type : {'A', 'B', 'C', 'D'}) {
        if (bstMap.find(type) != bstMap.end()) {
            bstMap[type] = deleteNodesByDateAndTypeRecursive(bstMap[type], date);
        }
    }
}

TermsBSTNode* TermsBST::deleteNodesByDateAndTypeRecursive(TermsBSTNode* root, string date)
{
    if (root == nullptr) {
        return nullptr;
    }

    // ���� ����Ʈ���� ��������� ����
    root->setLeft(deleteNodesByDateAndTypeRecursive(root->getLeft(), date));

    // ������ ����Ʈ���� ��������� ����
    root->setRight(deleteNodesByDateAndTypeRecursive(root->getRight(), date));

    // ����� Ÿ�԰� ���� ��¥�� Ȯ���Ͽ� date���� ������ ����
    if (root->getBST_last_date() < date) {
        // �ڽ� ��尡 �ϳ� �̰ų� ���� ���
        if (root->getLeft() == nullptr) {
            TermsBSTNode* temp = root->getRight();
            delete root;
            return temp;
        }
        else if (root->getRight() == nullptr) {
            TermsBSTNode* temp = root->getLeft();
            delete root;
            return temp;
        }

        // Case 2: ���� �ڽ� ��尡 ��� ������ ���
        TermsBSTNode* minRightSubtree = findMin(root->getRight()); // ������ ����Ʈ������ �ּڰ� ã��

        // ������ ����Ʈ������ ã�� �ּڰ����� ���� ����� ���� ��ü
        root->setBST_last_date(minRightSubtree->getBST_last_date());
        

        // ������ ����Ʈ������ �ּڰ��� ����
        root->setRight(deleteMin(root->getRight()));
    }

    return root;
}


string TermsBST::ExpirationDate(TermsBSTNode* currentNode, MemberQueueNode newNode)
{
    if (currentNode != nullptr)
    {
        int year, month, day;
        char dash1, dash2;
        istringstream(currentNode->getBST_first_date()) >> year >> dash1 >> month >> dash2 >> day;

        if (newNode.getName() == currentNode->getBST_name())
        {
            if (currentNode->getBSTType() == 'A')
            {
                month += 6;

                if (month > 12) {
                    year += month / 12;
                    month %= 12;
                }
            }
            else if (currentNode->getBSTType() == 'B')
            {
                year++;
            }
            else if (currentNode->getBSTType() == 'C')
            {
                year += 2;
            }
            else if (currentNode->getBSTType() == 'D')
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
            currentNode->setBST_last_date(newDate);
            return newDate;
        }

        // ���� ����Ʈ���� ������ ����Ʈ���� ���ؼ��� ���� ��¥ ���
        string leftExpiration = ExpirationDate(currentNode->getLeft(), newNode);
        string rightExpiration = ExpirationDate(currentNode->getRight(), newNode);

        // ���ʰ� ������ ����Ʈ�� �߿��� �� ���� ���⳯¥�� ��ȯ
        if (leftExpiration > rightExpiration) {
            return leftExpiration;
        }
        else {
            return rightExpiration;
        }
    }

    return "";
}
void TermsBST::Expiration_Date(TermsBSTNode* currentNode, MemberQueueNode newNode)
{
    if (currentNode != nullptr)
    {
        int year, month, day;
        char dash1, dash2;
        istringstream(currentNode->getBST_first_date()) >> year >> dash1 >> month >> dash2 >> day;

        if (newNode.getName() == currentNode->getBST_name())
        {
            if (currentNode->getBSTType() == 'A')
            {
                month += 6;

                if (month > 12) {
                    year += month / 12;
                    month %= 12;
                }
            }
            else if (currentNode->getBSTType() == 'B')
            {
                year++;
            }
            else if (currentNode->getBSTType() == 'C')
            {
                year += 2;
            }
            else if (currentNode->getBSTType() == 'D')
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
            currentNode->setBST_last_date(newDate);
        }

        // ���� ����Ʈ���� ������ ����Ʈ���� ���ؼ��� ���� ��¥ ���
        ExpirationDate(currentNode->getLeft(), newNode);
        ExpirationDate(currentNode->getRight(), newNode);
    }
}