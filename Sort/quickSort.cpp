//
// Created by Fitz on 2017/12/16.
//
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#define Num 10
#define Max 10
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
    return mid;
}

void quickSort(int *num,int left,int right)
{
    int i,j,t,temp,l,r,lLen=0,rLen=0;
    if(left>=right)
        return;
    int pivot=findKey(num,left,right);
    temp=num[pivot]; //temp�д�ľ��ǻ�׼��
    i=left;
    j=right;
    l=left;
    r=right;
    while(i<j)
    {
        //˳�����Ҫ��Ҫ�ȴ��ұ߿�ʼ��
        while(num[j]>=temp && i<j)
        {
            if(num[j]==temp&&j!=pivot)
            {
                swap(num[j],num[r]);
                r--;
                rLen++;
            }
            j--;
        }
        //������ߵ�
        while(num[i]<=temp && i<j)
        {
            if(num[i]==temp&&i!=pivot)
            {
                swap(num[i],num[l]);
                l++;
                lLen++;
            }
            i++;
        }
        //�����������������е�λ��
        if(i<j)
        {
            t=num[i];
            num[i]=num[j];
            num[j]=t;
        }
    }
    //    ���ս���׼����λ
    if(pivot<=i||num[i]>num[pivot])
    {
        num[pivot]=num[i];
        num[i]=temp;
    }
    else if(i+1<=right)
    {
        num[pivot]=num[i+1];
        num[i+1]=temp;
        i++;
    }
    else
    {
        num[pivot]=num[i+1];
        num[i+1]=temp;
    }
    int x=1;
    if(l!=left&&l!=i)
        l--;
    while(l!=left)
    {
        swap(num[l],num[i-x]);
        x++;
        l--;
    }
    if(num[l]==temp&&l!=i)
    swap(num[l],num[i-x]);
    x=1;
    if(r!=right&&r!=i)
        r++;
    while(r!=right)
    {
        swap(num[r],num[i+x]);
        x++;
        r++;
    }
    if(num[r]==temp&&r!=i)
        swap(num[r],num[i+x]);
    quickSort(num,left,i-1-lLen);
    quickSort(num,i+1+rLen,right);
}

int main()
{
    for(int i=0;i<Num;i++)
    {
        temp=Min+rand()%Max;
//        temp=i;
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
