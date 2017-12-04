//
// Created by Fitz on 2017/12/3.
//
#include<iostream>
#include <stack>
#include <cstdlib>
#include "Map.h"
using namespace std;
#define Max 500

Map newMap;
int year,n;
int newDevicePrice[Max];
int repareDevicePrice[Max];
stack<int> trace;

int main()
{
    int count=1,pre,w,sum,main[Max],count1=0;
    cout<<"���������"<<endl;
    cin>>year;
    cout<<"������"<<year<<"����ÿ����豸�ļ۸�"<<endl;
    for(int i=0;i<year;i++)
    {
        cin>>newDevicePrice[i];
    }
    cout<<"������"<<year<<"����ÿ��ά���豸�ļ۸�"<<endl;
    for(int i=0;i<year;i++)
    {
        cin>>repareDevicePrice[i];
    }
    n=(year*year-year+2)/2;   //�Ȳ��������
    newMap.initMap(n);
    for(int i=year-2;i>=0;i--)
    {
        pre=count;
        for(int j=0;j<i;j++)
        {
            newMap.addEdge(count,count+1,repareDevicePrice[j+1]);
            count++;
        }
        count++;
        main[count1]=count;
        count1++;
        newMap.addEdge(pre,count,newDevicePrice[year-i-1]+repareDevicePrice[0]);
    }
    count=1;
    for(int i=year-1;i>0;i--)
    {
        for(int j=0;j<i;j++)
        {
            if(main[j+year-i-1]!=n)
                newMap.addEdge(count,main[j+year-i-1],newDevicePrice[j+1]+repareDevicePrice[0]);
            else
                newMap.addEdge(count,main[j+year-i-1],repareDevicePrice[j+1]<newDevicePrice[j+1]+repareDevicePrice[0]?repareDevicePrice[j+1]:newDevicePrice[j+1]+repareDevicePrice[0]);
            count++;
        }
    }
    newMap.dijkstra();
    int i=n;
    while(newMap.p[i]!=0)
    {
        i=newMap.p[i];
        for(int j=0;j<count1;j++)
        {
            if(i==main[j])
                trace.push(j+2);
        }
    }
    trace.push(1);
    while(!trace.empty())
    {
        cout<<"����������� "<<trace.top()<<endl;
        trace.pop();
    }
    cout<<endl;
    cout<<"���ٵľ�����"<<newMap.dis[n]+newDevicePrice[0]+repareDevicePrice[0]<<endl;
    return 0;
}
//5 11 11 12 12 13 5 6 8 11 18
//6 11 11 12 12 13 10 5 6 8 11 18 20