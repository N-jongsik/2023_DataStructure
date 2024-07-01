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
        cout << "에러: 유효하지 않은 가입약관 타입입니다." << endl;
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
        // 왼쪽 서브트리 출력
        if (currentNode->getLeft() != nullptr) {
            printInOrder(currentNode->getLeft(), flog);
        }

        // 현재 노드 출력
        flog << currentNode->getBST_name() << "/" << currentNode->getBST_age() << "/" << currentNode->getBST_first_date() << "/" << currentNode->getBST_last_date() << endl;
        cout << currentNode->getBST_name() << "/" << currentNode->getBST_age() << "/" << currentNode->getBST_first_date() << "/" << currentNode->getBST_last_date() << endl;
       

        // 오른쪽 서브트리 출력
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

    // 중위 순회로 출력하는 로직 구현
    printInOrder(bstMap[bstCharType], flog);

    flog << "==============" << endl << endl;
    cout << "==============" << endl << endl;
}

// 날짜를 사용하여 노드를 검색하고 날짜를 반환하는 함수
string TermsBST::searchNode(TermsBSTNode* currentNode, string name)
{
    if (currentNode == nullptr) {
        return ""; // 노드를 찾지 못한 경우 빈 문자열 반환
    }

    if (currentNode->getBST_name() == name)
    {
        return currentNode->getBST_first_date();
    }
    // 왼쪽 서브트리에서 찾기
    string leftResult = searchNode(currentNode->getLeft(), name);

    // 오른쪽 서브트리에서 찾기
    string rightResult = searchNode(currentNode->getRight(), name);

    // 양쪽 서브트리에서 찾은 결과 중 하나라도 찾았다면 해당 결과 반환
    if (leftResult != "") {
        return leftResult;
    }
    else {
        return rightResult;
    }
}

// delete
void TermsBST::deleteNode(string name) {
    char bstType = ' ';  // 초기값 설정
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
        std::cout << "에러: 삭제할 이름을 찾을 수 없습니다." << std::endl;
        return;
    }
}
 
TermsBSTNode* TermsBST::deleteRecursive(TermsBSTNode* currentNode, string date) {
    if (currentNode == nullptr) {
        return currentNode; // 노드를 찾지 못한 경우, 아무것도 변경하지 않고 반환합니다.
    }

    if (date < currentNode->getBST_first_date()) {
        // 왼쪽 서브 트리에서 삭제 작업 수행
        currentNode->setLeft(deleteRecursive(currentNode->getLeft(), date));
    }
    else if (date > currentNode->getBST_first_date()) {
        // 오른쪽 서브 트리에서 삭제 작업 수행
        currentNode->setRight(deleteRecursive(currentNode->getRight(), date));
    }
    else {
        // 삭제할 노드를 찾은 경우
        if (currentNode->getLeft() == nullptr) {
            // 왼쪽 자식이 없거나 자식 중 한쪽만 있을 경우
            TermsBSTNode* temp = currentNode->getRight();
            delete currentNode;
            return temp;
        }
        else if (currentNode->getRight() == nullptr) {
            // 오른쪽 자식만 있을 경우
            TermsBSTNode* temp = currentNode->getLeft();
            delete currentNode;
            return temp;
        }

        // 양쪽 자식 노드가 모두 있는 경우
        // 오른쪽 서브 트리에서 가장 작은 노드를 찾아서 현재 노드와 교체합니다.
        TermsBSTNode* temp = findMin(currentNode->getRight());
        currentNode->setBST_name(temp->getBST_name());
        currentNode->setBST_age(temp->getBST_age());
        currentNode->setBST_first_date(temp->getBST_first_date());
        currentNode->setBST_last_date(temp->getBST_last_date());

        // 오른쪽 서브 트리에서 가장 작은 노드를 삭제합니다.
        currentNode->setRight(deleteRecursive(currentNode->getRight(), temp->getBST_name()));
    }

    return currentNode;
}

TermsBSTNode* TermsBST::findMin(TermsBSTNode* node)
{
    // 가장 작은 값은 가장 왼쪽에 위치한 노드입니다.
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

    // 왼쪽 서브트리를 재귀적으로 삭제
    root->setLeft(deleteNodesByDateAndTypeRecursive(root->getLeft(), date));

    // 오른쪽 서브트리를 재귀적으로 삭제
    root->setRight(deleteNodesByDateAndTypeRecursive(root->getRight(), date));

    // 노드의 타입과 만료 날짜를 확인하여 date보다 작으면 삭제
    if (root->getBST_last_date() < date) {
        // 자식 노드가 하나 이거나 없을 경우
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

        // Case 2: 양쪽 자식 노드가 모두 존재할 경우
        TermsBSTNode* minRightSubtree = findMin(root->getRight()); // 오른쪽 서브트리에서 최솟값 찾기

        // 오른쪽 서브트리에서 찾은 최솟값으로 현재 노드의 값을 대체
        root->setBST_last_date(minRightSubtree->getBST_last_date());
        

        // 오른쪽 서브트리에서 최솟값을 삭제
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
            expirationTime.tm_year = year - 1900; // tm_year는 1900년부터의 연수
            expirationTime.tm_mon = month - 1;    // tm_mon은 0부터 시작하는 월
            expirationTime.tm_mday = day;

            std::ostringstream formattedDate;
            formattedDate << std::put_time(&expirationTime, "%Y-%m-%d"); // "YYYY-MM-DD" 형식으로 포맷
            std::string newDate = formattedDate.str();

            // 현재 노드의 마지막 날짜 설정
            currentNode->setBST_last_date(newDate);
            return newDate;
        }

        // 왼쪽 서브트리와 오른쪽 서브트리에 대해서도 만료 날짜 계산
        string leftExpiration = ExpirationDate(currentNode->getLeft(), newNode);
        string rightExpiration = ExpirationDate(currentNode->getRight(), newNode);

        // 왼쪽과 오른쪽 서브트리 중에서 더 늦은 만기날짜를 반환
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
            expirationTime.tm_year = year - 1900; // tm_year는 1900년부터의 연수
            expirationTime.tm_mon = month - 1;    // tm_mon은 0부터 시작하는 월
            expirationTime.tm_mday = day;

            std::ostringstream formattedDate;
            formattedDate << std::put_time(&expirationTime, "%Y-%m-%d"); // "YYYY-MM-DD" 형식으로 포맷
            std::string newDate = formattedDate.str();

            // 현재 노드의 마지막 날짜 설정
            currentNode->setBST_last_date(newDate);
        }

        // 왼쪽 서브트리와 오른쪽 서브트리에 대해서도 만료 날짜 계산
        ExpirationDate(currentNode->getLeft(), newNode);
        ExpirationDate(currentNode->getRight(), newNode);
    }
}