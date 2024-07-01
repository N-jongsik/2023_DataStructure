#include "Manager.h"
#include <sstream>
#include <fstream>

Manager::Manager()
{

}
Manager::~Manager()
{

}

void Manager::run(const char* command)
{
    // Open command & log file
    fcmd.open(command);
    flog.open("log.txt");
    if (!fcmd)
    {
        flog << "Fail to open command file" << endl;
        exit(-1);
    }

    // Run command
    string line;
    while (getline(fcmd, line))
    {
        stringstream ss(line);
        string command;
        ss >> command;

        if (command == "LOAD")
        {
            LOAD();
        }
        else if (command == "ADD")
        {
            string name;
            int age;
            string date;
            char type;

            // 인자를 읽어옴
            ss >> name >> age >> date >> type;
            ADD(name, age, date, type);
        }
        else if (command == "QPOP")
        {
            QPOP();
        }
        else if (command == "SEARCH")
        {
            string name;
            ss >> name;
            SEARCH(name);
        }
        else if (command == "PRINT")
        {
            string data;
            ss >> data;
            PRINT(data);
        }
        else if (command == "DELETE")
        {
            string deleteType;
            ss >> deleteType;

            if (deleteType == "NAME")
            {
                string name_Delete;
                ss >> name_Delete;
                DELETE(name_Delete);
            }
            else if (deleteType == "DATE")
            {
                string date_Delete;
                ss >> date_Delete;
                DELETE_BY_DATE(date_Delete);
            }
        }
        else if (command == "EXIT")
        {
            EXIT();
        }
        else
        {
            PrintErrorCode(1000);
        }
    }
    fcmd.close();
    flog.close();
    return;
}

void Manager::PrintSuccess(const char* cmd)
{
    flog << "===== " << cmd << " =====" << endl;
    flog << "Success" << endl;
    flog << "===============" << endl << endl;

    cout << "===== " << cmd << " =====" << endl;
    cout << "Success" << endl;
    cout << "===============" << endl << endl;
}
void Manager::PrintErrorCode(int num)
{
    flog << "===== ERROR =====" << endl;
    flog << num << endl;
    flog << "===============" << endl << endl;

    cout << "===== ERROR =====" << endl;
    cout << num << endl;
    cout << "===============" << endl << endl;
}

// LOAD
void Manager::LOAD()
{
    if (Member_Queue.empty()) // Member_Queue 자료구조에 데이터가 없을 때만 실행
    {
        ifstream inputFile("data.txt");
        if (inputFile.is_open())
        {
            flog << "===== LOAD =====" << endl;
            cout << "===== LOAD =====" << endl;
            string line;
            while (getline(inputFile, line))
            {
                // 데이터 파싱
                stringstream ss(line);
                string name;
                int age;
                string date;
                char type;
                ss >> name >> age >> date >> type;

                // 데이터를 Member_Queue에 추가
                Member_Queue.push(name, age, date, type);

                flog << name << "/" << age << "/" << date << "/" << type << endl;
                cout << name << "/" << age << "/" << date << "/" << type << endl;
            }

            inputFile.close();

            flog << "================" << endl << endl;
            cout << "================" << endl << endl;
        }
        else
        {
            // 파일 열기 실패 시 에러 로그 출력
            PrintErrorCode(100);
        }
    }
    else
    {
        // 이미 데이터가 있는 경우 에러 로그 출력
        PrintErrorCode(100);
    }
}

// ADD
void Manager::ADD(const string& name, int age, const string& date, char type)
{
    if (!name.empty() && age > 0 && !date.empty() && (type == 'A' || type == 'B' || type == 'C' || type == 'D'))
    {
        if (!Member_Queue.full())
        {
            // 데이터를 Member_Queue에 추가
            Member_Queue.push(name, age, date, type);

            // 성공적으로 데이터를 추가한 경우 출력
            flog << "===== ADD =====" << endl;
            flog << name << "/" << age << "/" << date << "/" << type << endl;
            flog << "===============" << endl << endl;

            cout << "===== ADD =====" << endl;
            cout << name << "/" << age << "/" << date << "/" << type << endl;
            cout << "===============" << endl << endl;
        }
        else
        {
            PrintErrorCode(200);
        }
    }
    else
    {
        PrintErrorCode(200); // 입력값이 유효하지 않음을 나타내는 적절한 에러 코드를 선택하세요.
    }
}


// QPOP
void Manager::QPOP()
{
    if (!Member_Queue.empty()) // Member_Queue 자료구조에 데이터가 있을 때만 실행
    {
        while (!Member_Queue.empty())
        {
            MemberQueueNode member = Member_Queue.pop();

            // Terms_List에 추가
            Terms_List.insertNode(member);

            // Terms_BST에 추가
            Terms_BST.insertNode(member);

            // Name_BST에 추가
            Name_BST.insertNode(member);
        }

        // 성공적으로 데이터를 POP하여 자료구조를 구축한 경우 출력
        PrintSuccess("QPOP");
    }
    else
    {
        // Member_Queue에 데이터가 없는 경우 에러 로그 출력
        PrintErrorCode(300);
    }
}

//SEARCH
void Manager::SEARCH(string name)
{
    NameBSTNode* result = Name_BST.searchNode(name); // Name_BST에서 이름으로 노드 검색

    if (result != nullptr)
    {
        // 검색 결과를 로그와 표준 출력에 출력
        flog << "===== SEARCH =====" << endl;
        flog << result->getNameBST_name() << "/" << result->getNameBST_age() << "/" << result->getNameBST_first_date() << "/" << result->getNameBST_last_date() << endl;
        flog << "===============" << endl << endl;

        cout << "===== SEARCH =====" << endl;
        cout << result->getNameBST_name() << "/" << result->getNameBST_age() << "/" << result->getNameBST_first_date() << "/" << result->getNameBST_last_date() << endl;
        cout << "===============" << endl << endl;
    }
    else
    {
        // 검색 결과가 없는 경우 에러 로그 출력
        PrintErrorCode(400);
    }
}

// PRINT
void Manager::PRINT(string data)
{
    if (data == "NAME")
    {
        flog << "===== PRINT =====" << endl;
        cout << "===== PRINT =====" << endl;

        flog << "Name_BST" << endl;
        cout << "Name_BST" << endl;
        Name_BST.print(flog);
        flog << "===============" << endl << endl;
        cout << "===============" << endl << endl;
    }

    else if (data == "A" || data == "B" || data == "C" || data == "D") 
    {
        if (data == "A") {
            Terms_BST.print("A", flog);
        }
        else if (data == "B") {
            Terms_BST.print("B", flog);
        }
        else if (data == "C") {
            Terms_BST.print("C", flog);
        }
        else if (data == "D") {
            Terms_BST.print("D", flog);
        }
    }

    else
    {
        PrintErrorCode(500);
    }
}


//DELETES
void Manager::DELETE(string name)
{
    NameBSTNode* result = Name_BST.searchNode(name);

    if (result != nullptr)
    {
        // Name_BST에서 해당 회원의 노드를 삭제
        Name_BST.deleteNode(name);

        // 삭제한 회원 정보를 기반으로 Terms_BST에서도 삭제 수행
        Terms_BST.deleteNode(name);

        // 삭제한 회원 정보를 기반으로 Terms_List에서도 삭제 수행
        //Terms_List.deleteNode();

        // 삭제 성공 메시지 출력
        PrintSuccess("DELETE");
    }
    else
    {
        // 삭제하고자 하는 회원 정보가 존재하지 않는 경우 에러 코드 출력
        PrintErrorCode(600);
    }
}

void Manager::DELETE_BY_DATE(string date)
{
    if (!Name_BST.hasNodeWithExpiredDateRecursive(Name_BST.getRoot(),date)) {
        // 주어진 날짜보다 만기 날짜가 이전인 노드가 없는 경우 에러 코드 출력
        PrintErrorCode(600);
        return;
    }

    // 만기 날짜가 주어진 날짜보다 이전인 노드가 있는 경우에만 삭제 작업 수행
    Name_BST.deleteNode_date(date);

    // 삭제한 회원 정보를 기반으로 Terms_BST에서도 삭제 수행
    Terms_BST.deleteNodesByDateAndTypeAll(date);

    // 삭제한 회원 정보를 기반으로 Terms_List에서도 삭제 수행
    //Terms_List.deleteNode(result->getTermBST());

    PrintSuccess("DELETE");
}

//EXIT
void Manager::EXIT()
{
    // 프로그램 종료 전에 필요한 정리 작업을 수행

    // Member_Queue, Terms_List, Terms_BST, Name_BST 등의 자료구조의 메모리를 해제

    // 로그와 화면에 종료 메시지 출력
    flog << "===== EXIT =====" << endl;
    flog << "Success" << endl;
    flog << "===============" << endl << endl;

    cout << "===== EXIT =====" << endl;
    cout << "Success" << endl;
    cout << "===============" << endl << endl;

    // 모든 작업이 완료되면 프로그램 종료
    exit(0);
}