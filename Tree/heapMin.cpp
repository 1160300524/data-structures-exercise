//
// Created by Fitz on 2017/11/30.
//
#include <iostream>
#include <fstream>
using namespace std;

struct CellElement
{
    int pority;   //���ȼ�
    int pocessID; //���̺�
};

class heapmin
{
public:
    int size;
    int Maxlength;
    CellElement *Elements;
    heapmin(int length)
    {
        size=0;
        Maxlength=length;
        Elements=new CellElement[Maxlength];
    }

    bool empty()
    {
        if(size==0)
            return true;
        return false;
    }

    bool full()
    {
        return (size==Maxlength-1);
    }

    bool insert(int p,int ID)
    {
        int i=size+1;
        if(!full())
        {
            size++;
            while(i!=1&&p<=Elements[i/2].pority)
            {
                if(p<Elements[i/2].pority||(p==Elements[i/2].pority&&ID<Elements[i/2].pocessID))
                {
                    Elements[i].pority=Elements[i/2].pority;
                    Elements[i].pocessID=Elements[i/2].pocessID;
                    i=i/2;
                }
                else
                    break;
            }
            Elements[i].pocessID=ID;
            Elements[i].pority=p;
            return true;
        }
        return false;
    }

    CellElement top()
    {
        return Elements[1];
    }

    bool DeleteMin() {
        int parent = 1, child = 2;
        CellElement temp;
        if (!empty()) {
            temp = Elements[size];
            size--;
            while (child <= size) {
                if (child < size && Elements[child].pority > Elements[child + 1].pority)
                    child++;
                else if(child < size && Elements[child].pority == Elements[child + 1].pority&&Elements[child].pocessID>Elements[child + 1].pocessID)
                    child++;
                if (temp.pority < Elements[child].pority)
                    break;
                if(temp.pority==Elements[child].pority&&temp.pocessID<Elements[child].pocessID)
                    break;
                Elements[parent] = Elements[child];
                parent = child;
                child *= 2;
            }
            Elements[parent] = temp;
            return true;
        }
        return false;
    }
};

int main()
{
    heapmin temp(100);
    heapmin system(100);
    fstream ReadFile;
    string filepath;
    int a=0,b=0,count=0;
    cout<<">>>�����������Ϣ�ļ�task.dat����Ч·��"<<endl;
    cin>>filepath;
    ReadFile.open(filepath.c_str(),ios::in);
    if (!ReadFile.is_open())
    {
        cout << "Error opening file"<<endl;
        exit (1);
    }
    cout<<"��ʼ��ȡ�ļ�����"<<endl;
    while(!ReadFile.eof())
    {
        ReadFile>>a>>b;
        count++;
        system.insert(b,a);  //�Ƚ��̺ź����ȼ�
    }
    ReadFile.close();
    cout<<"��ȡ�ļ����"<<endl;
    a=system.size;
    cout<<"��ʼ������̵�ִ��˳��:"<<endl;
    for(int i=1;i<=a;i++)
    {
        cout<<system.top().pocessID<<"\t"<<system.top().pority<<endl;
        system.DeleteMin();
    }
    return 0;
}

//C:\Users\29488\Desktop\task.dat