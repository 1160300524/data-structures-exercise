//
// Created by Fitz on 2017/11/23.
//
#include <iostream>
using namespace std;

struct CellElement
{
    int pority;   //���ȼ�
    int pocessID; //���̺�
};

class heap
{
    int size;
    int Maxlength;
    CellElement *Ele;
    heap(int length)
    {
        size=0;
        const MaxLength=length;
        Maxlength=length;
        static CellElement elements[MaxLength];
        Ele=elements;
    }

    bool empty()
    {
        if(size==0)
            return true;
        return false;
    }

    bool full()
    {
        return (size==Maxlength);
    }

    void insert(int p,int ID)
    {

    }
};

int main()
{
    return 0;
}

