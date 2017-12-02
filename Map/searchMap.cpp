//
// Created by Fitz on 2017/12/2.
//
#include <iostream>
#include <fstream>
#include <stack>
#include<queue>
#include <cstdlib>
using namespace std;
#define maxNum 30

class map{
public:
    int pointNum,edgeNum;
    int point[maxNum],edge[maxNum][maxNum];
    void initMap(int p,int e)
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
    if(!fileReader.is_open())
    {
        cout<<"�Ҳ������ļ�����������Ч���ļ�·��"<<endl;
        exit(0);
    }
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
        if(!visited[i]&&newMap.edge[currentPoint][i])
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

void DFSNotRecursive()
{
    count=0;
    int index,flag;
    stack<int> trace;
    for(int i=0;i<newMap.pointNum;i++)
    {
        visited[i]=false;
        dfsCode[i]=-1;
    }
    for(int i=0;i<newMap.pointNum;i++)
    {
        index=i;
        while(!visited[index])
        {
            visited[index]=true;
            dfsCode[count]=index;
            trace.push(index);
            count++;
            do
            {
                flag=0;
                for(int j=0;j<newMap.pointNum;j++)
                {
                    if(!visited[j]&&newMap.edge[index][j])
                    {
                        index=j;
                        flag=1;
                        break;
                    }
                }
                if(flag==0)
                {
                    trace.pop();
                    if(trace.empty())
                    {
                        flag=1;
                        break;
                    }
                    else
                    {
                        index=trace.top();
                    }
                }
            }while(flag==0);
        }
    }
}

void BFS()
{
    queue<int> point;
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
            visited[i]=true;
            dfsCode[count]=i;
            count++;
            point.push(i);
            while(!point.empty())
            {
                for(int j=0;j<newMap.pointNum;j++)
                {
                    if(!visited[j]&&newMap.edge[point.front()][j])
                    {
                        point.push(j);
                        visited[j]=true;
                        dfsCode[count]=j;
                        //cout<<j<<endl;
                        count++;
                    }
                }
                point.pop();
            }
        }
    }
}

int main()
{
    readFile();
    //DFSRecursiveMain();
    //DFSNotRecursive();
    BFS();
    for(int i=0;i<newMap.pointNum;i++)
        cout<<dfsCode[i]<<endl;
    return 0;
}
