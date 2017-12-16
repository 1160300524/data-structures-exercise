//
// Created by Fitz on 2017/12/16.
//
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#define Num 10000000
#define Max 10000
#define Min 1
int randomNum1[Num],randomNum2[Num],temp;
using namespace std;
int findKey(int* num,int a,int b)
{
    int mid;
    mid=(a+b)>>1;
    if(num[mid]>num[b])
        swap(num[mid],num[b]);
    if(num[a]>num[mid])
        swap(num[a],num[mid]);
    return a;
}

void quickSort(int *num,int left,int right)
{
    int i,j,t,temp;
    if(left>right)
        return;
    int pivot=findKey(num,left,right);
    temp=num[left]; //temp�д�ľ��ǻ�׼��
    i=left;
    j=right;
    while(i!=j)
    {
        //˳�����Ҫ��Ҫ�ȴ��ұ߿�ʼ��
        while(num[j]>=temp && i<j)
            j--;
        //�����ұߵ�
        while(num[i]<=temp && i<j)
            i++;
        //�����������������е�λ��
        if(i<j)
        {
            t=num[i];
            num[i]=num[j];
            num[j]=t;
        }
    }
    //���ս���׼����λ
    num[left]=num[i];
    num[i]=temp;


    quickSort(num,left,i-1);
    quickSort(num,i+1,right);
}

int main()
{
    for(int i=0;i<Num;i++)
    {
        temp=Min+rand()%Max;
        randomNum1[i]=temp;
        randomNum2[i]=temp;
//        cout<<randomNum[i]<<"\t";
    }
    cout<<endl;
    double time;
    time=clock();
//    sort(randomNum1,&randomNum1[Num],greater<int>());  //�Ӵ�С����
    sort(randomNum1,&randomNum1[Num]);   //��С��������
    time=clock()-time;
    cout<<"��������������ݹ�ģ��"<<Num<<endl<<"STL���ŵ���ʱΪ��\t";
    cout<<time<<endl;
    time=clock();
    quickSort(randomNum2,0,Num-1);  //�Լ��Ŀ��ź���
    time=clock()-time;
    cout<<"��������������ݹ�ģ��"<<Num<<endl<<"�Լ��Ŀ��ŵ���ʱΪ��\t";
    cout<<time<<endl;
    for(int i=0;i<Num;i++)
    {
//        cout<<randomNum2[i]<<"\t";
        if(randomNum1[i]!=randomNum2[i])
        {
            cout<<i<<endl;
            cout<<randomNum1[i]<<"  "<<randomNum2[i]<<endl;
        }
    }
    return 0;
}
