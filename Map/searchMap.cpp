//
// Created by Fitz on 2017/12/2.
//
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;
#define maxNum 30

class map{
public:
    int pointNum,edgeNum;
    int point[maxNum],edge[maxNum][maxNum];
    initMap(int p,int e)
    {
        pointNum=p;
        edgeNum=e;
        for(int i=0;i<p;i++)
        {
            for(int j=0;j<p;j++)
            {
                edge[i][j]=0;
            }
        }
    }

    map() = default;

    void addEdge(int a,int b,int weight)
    {
        edge[a][b]=weight;
        edge[b][a]=weight;
    }

};

//ʵ��һ��ͼ�Ķ���
map newMap;
bool visited[maxNum];
int dfsCode[maxNum];
int count=0;
//ͨ���ļ�����ͼ����Ϣ������ͼ
void readFile()
{
    ifstream fileReader;
    string filePath;
    int p,e,a,b,w;
    cout<<"������洢ͼ��Ϣ���ļ�λ��"<<endl<<"tips:��ʽ������������ߵĸ�����������1��������2���ߵ�Ȩ��"<<endl;
    cin>>filePath;
    fileReader.open(filePath.c_str());
    fileReader>>p>>e;
    newMap.initMap(p,e);
    for(int i=0;i<e;i++)
    {
        fileReader>>a>>b>>w;
        newMap.addEdge(a,b,w);
    }
    fileReader.close();
}

void DFSRecursive(int currentPoint)
{
    visited[currentPoint]=true;
    for(int i=0;i<newMap.pointNum;i++)
    {
        if(newMap.edge[currentPoint][i])
        {
            dfsCode[count]=i;
            count++;
            DFSRecursive(i);
        }
    }
}

void DFSRecursiveMain()
{
    count=0;
    for(int i=0;i<newMap.pointNum;i++)
    {
        visited[i]=false;
        dfsCode[i]=-1;
    }
    for(int i=0;i<newMap.pointNum;i++)
    {
        if(!visited[i])
        {
            dfsCode[count]=i;
            count++;
            DFSRecursive(i);
        }
    }
}

int main()
{
    readFile();
    DFSRecursiveMain();
    for(int i=0;i<newMap.pointNum;i++)
        cout<<dfsCode[i]<<endl;
    return 0;
}
