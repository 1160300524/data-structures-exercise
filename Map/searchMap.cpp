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
    map(int p,int e)
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

    map(){}

    void addEdge(int a,int b,int weight)
    {
        edge[a][b]=weight;
        edge[b][a]=weight;
    }

};

//ʵ��һ��ͼ�Ķ���
map newMap;
int visited[maxNum];

//ͨ���ļ�����ͼ����Ϣ������ͼ
void readFile()
{
    ifstream fileReader;
    string filePath;
    int p,e,a,b,w;
    cout<<"������洢ͼ��Ϣ���ļ�λ��"<<"tips:��ʽ������������ߵĸ�����������1��������2���ߵ�Ȩ��"endl;
    cin>>filePath;
    fileReader.open(filePath.c_str());
    fileReader>>p>>e;
    newMap.map(p,e);
    for(int i=0;i<e;i++)
    {
        fileReader>>a>>b>>w;
        newMap.addEdge(a,b,w);
    }
    fileReader.close();
}

void deepSearchRecursive()
{

}

int main()
{
    readFile();
    return 0;
}
