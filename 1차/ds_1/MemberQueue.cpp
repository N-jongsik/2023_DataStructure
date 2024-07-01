#include "MemberQueue.h"
#include <iostream>
#include <stdexcept>

using namespace std;

MemberQueue::MemberQueue()
{
    capacity = 100;
    size = 0;
    frontIdx = 0;
    rearIdx = 0;
    data = new MemberQueueNode[capacity];
}

MemberQueue::~MemberQueue()
{
    delete[] data;
}

bool MemberQueue::empty()
{
    return size == 0;
}

bool MemberQueue::full()
{
    return size == capacity;
}

void MemberQueue::push(const string& name, int age, const string& date, char type)
{

    if (!full())
    {
        MemberQueueNode node{ name, age, date, type };
        data[rearIdx] = node;
        rearIdx = (rearIdx + 1) % capacity; // 원형 큐
        size++;
    }
    else
    {
        cout << "error" << endl;
    }
}


MemberQueueNode MemberQueue::pop()
{
    if (!empty())
    {
        MemberQueueNode temp = data[frontIdx];
        frontIdx = (frontIdx + 1) % capacity; // 원형 큐
        size--;
        return temp;
    }
    else
    {
        cout << "error" << endl;
    }
}

MemberQueueNode MemberQueue::front()
{
    if (!empty())
    {
        return data[frontIdx];
    }
    else
    {
        cout << "error" << endl;
    }
}

