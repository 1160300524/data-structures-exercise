/*
 *
 */
#include <iostream>
#include <stack>
#include <cstdlib>
#include "Map.h"
using namespace std;

Map newMap;
int index[11]={0,0,1,2,4,5,10,11,13,14,15};
void establish()
{
    newMap.initMap(10);
    newMap.addEdge2(1,6,1);
    newMap.addEdge2(2,7,1);
    newMap.addEdge2(2,8,1);
    newMap.addEdge2(3,6,1);
    newMap.addEdge2(3,7,1);
    newMap.addEdge2(3,9,1);
    newMap.addEdge2(4,8,1);
    newMap.addEdge2(4,9,1);
    newMap.addEdge2(5,8,1);
    newMap.addEdge2(5,10,1);
}

void coutRoad(int a,int b)
{
    if(((b&0x8)>>3))
        cout<<"ũ��ȥ�԰���";
    else
        cout<<"ũ��Ӷ԰���������";
    switch(((a^b)&7))
    {
        case 0:
            cout<<"û�д�����"<<endl;
            break;
        case 1:
            cout<<"���Űײ�"<<endl;
            break;
        case 2:
            cout<<"������"<<endl;
            break;
        case 4:
            cout<<"������"<<endl;
            break;
        default:
            cout<<"error"<<endl;
    }
}

int main()
{
    stack<int> trace;
    establish();
    newMap.dijkstra();
    int i=10,temp;
    trace.push(10);
    while(newMap.p[i])
    {
        i=newMap.p[i];
        trace.push(i);
    }
    cout<<endl;
    while(!trace.empty())
    {
        temp=trace.top();
        trace.pop();
        if(!trace.empty())
        {
            coutRoad(index[temp],index[trace.top()]);
        }
    }
    return 0;
}
