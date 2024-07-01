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

            // ���ڸ� �о��
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
    if (Member_Queue.empty()) // Member_Queue �ڷᱸ���� �����Ͱ� ���� ���� ����
    {
        ifstream inputFile("data.txt");
        if (inputFile.is_open())
        {
            flog << "===== LOAD =====" << endl;
            cout << "===== LOAD =====" << endl;
            string line;
            while (getline(inputFile, line))
            {
                // ������ �Ľ�
                stringstream ss(line);
                string name;
                int age;
                string date;
                char type;
                ss >> name >> age >> date >> type;

                // �����͸� Member_Queue�� �߰�
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
            // ���� ���� ���� �� ���� �α� ���
            PrintErrorCode(100);
        }
    }
    else
    {
        // �̹� �����Ͱ� �ִ� ��� ���� �α� ���
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
            // �����͸� Member_Queue�� �߰�
            Member_Queue.push(name, age, date, type);

            // ���������� �����͸� �߰��� ��� ���
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
        PrintErrorCode(200); // �Է°��� ��ȿ���� ������ ��Ÿ���� ������ ���� �ڵ带 �����ϼ���.
    }
}


// QPOP
void Manager::QPOP()
{
    if (!Member_Queue.empty()) // Member_Queue �ڷᱸ���� �����Ͱ� ���� ���� ����
    {
        while (!Member_Queue.empty())
        {
            MemberQueueNode member = Member_Queue.pop();

            // Terms_List�� �߰�
            Terms_List.insertNode(member);

            // Terms_BST�� �߰�
            Terms_BST.insertNode(member);

            // Name_BST�� �߰�
            Name_BST.insertNode(member);
        }

        // ���������� �����͸� POP�Ͽ� �ڷᱸ���� ������ ��� ���
        PrintSuccess("QPOP");
    }
    else
    {
        // Member_Queue�� �����Ͱ� ���� ��� ���� �α� ���
        PrintErrorCode(300);
    }
}

//SEARCH
void Manager::SEARCH(string name)
{
    NameBSTNode* result = Name_BST.searchNode(name); // Name_BST���� �̸����� ��� �˻�

    if (result != nullptr)
    {
        // �˻� ����� �α׿� ǥ�� ��¿� ���
        flog << "===== SEARCH =====" << endl;
        flog << result->getNameBST_name() << "/" << result->getNameBST_age() << "/" << result->getNameBST_first_date() << "/" << result->getNameBST_last_date() << endl;
        flog << "===============" << endl << endl;

        cout << "===== SEARCH =====" << endl;
        cout << result->getNameBST_name() << "/" << result->getNameBST_age() << "/" << result->getNameBST_first_date() << "/" << result->getNameBST_last_date() << endl;
        cout << "===============" << endl << endl;
    }
    else
    {
        // �˻� ����� ���� ��� ���� �α� ���
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
        // Name_BST���� �ش� ȸ���� ��带 ����
        Name_BST.deleteNode(name);

        // ������ ȸ�� ������ ������� Terms_BST������ ���� ����
        Terms_BST.deleteNode(name);

        // ������ ȸ�� ������ ������� Terms_List������ ���� ����
        //Terms_List.deleteNode();

        // ���� ���� �޽��� ���
        PrintSuccess("DELETE");
    }
    else
    {
        // �����ϰ��� �ϴ� ȸ�� ������ �������� �ʴ� ��� ���� �ڵ� ���
        PrintErrorCode(600);
    }
}

void Manager::DELETE_BY_DATE(string date)
{
    if (!Name_BST.hasNodeWithExpiredDateRecursive(Name_BST.getRoot(),date)) {
        // �־��� ��¥���� ���� ��¥�� ������ ��尡 ���� ��� ���� �ڵ� ���
        PrintErrorCode(600);
        return;
    }

    // ���� ��¥�� �־��� ��¥���� ������ ��尡 �ִ� ��쿡�� ���� �۾� ����
    Name_BST.deleteNode_date(date);

    // ������ ȸ�� ������ ������� Terms_BST������ ���� ����
    Terms_BST.deleteNodesByDateAndTypeAll(date);

    // ������ ȸ�� ������ ������� Terms_List������ ���� ����
    //Terms_List.deleteNode(result->getTermBST());

    PrintSuccess("DELETE");
}

//EXIT
void Manager::EXIT()
{
    // ���α׷� ���� ���� �ʿ��� ���� �۾��� ����

    // Member_Queue, Terms_List, Terms_BST, Name_BST ���� �ڷᱸ���� �޸𸮸� ����

    // �α׿� ȭ�鿡 ���� �޽��� ���
    flog << "===== EXIT =====" << endl;
    flog << "Success" << endl;
    flog << "===============" << endl << endl;

    cout << "===== EXIT =====" << endl;
    cout << "Success" << endl;
    cout << "===============" << endl << endl;

    // ��� �۾��� �Ϸ�Ǹ� ���α׷� ����
    exit(0);
}