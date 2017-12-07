//
// Created by Fitz on 2017/12/7.
//
#include <iostream>
#include <fstream>
#include "Map.h"
using namespace std;
#define Max 100
MapVertex newMap;

int point[Max];
int ve[Max];

int main()
{
    ifstream file;
    file.open("data.dat");  //���Ǵ�¼�����ݵ��ļ�
    if(!file.is_open())
    {
        cout<<"�ļ���ʧ�ܣ�������ѡ���ļ�"<<endl;
        exit(0);
    }
    cout<<"�����빤�������"<<endl;
    int n,a,b,c;
    file>>n;
    newMap.initMap(n);
    cout<<"������ÿ������ı�ţ���ǰ����ı�ţ��͸ù��������ʱ��"<<endl;
    while(!file.eof())
    {
        file>>a>>b>>c;
        if(a!=-1)
        {
            newMap.addEdgeTableIn(b,a,c);
            newMap.addEdgeTableOut(b,a,c);
        }
        point[b]=c;
    }
    for(int i=1;i<=n;i++)
    {
        ve[i]=0;
    }
    for(int i=1;i<=n;i++)
    {
        a=newMap.topoSort();
        for(int j=1;j<=newMap.edgeNodeOut[a].size;j++)
        {
            if(ve[newMap.edgeNodeOut[a].inquire(j)->data1]<ve[i]+point[a])
                ve[newMap.edgeNodeOut[a].inquire(j)->data1]=ve[i]+point[a];
        }
    }
    for(int i=1;i<=n;i++)
    {
        cout<<(char)(i+'A'-1)<<"���������ڵ�"<<ve[i]<<"�쿪ʼ"<<endl;
    }
    for(int i=1;i<=n;i++)
    {
        cout<<"���"<<(char)(i+'A'-1)<<"������Ҫ���������Ϊ"<<ve[i]+point[i]<<endl;
    }
    return 0;
}
