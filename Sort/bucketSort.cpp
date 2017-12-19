//
// Created by Fitz on 2017/12/17.
//
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include "linkList.h"
using namespace std;
#define Max 10000
#define Size 50
int num[Max];
int temp1[Max+1];
int temp2[Max+1];
linkList<int> bucket[Size];
//int count[10];
//int tmp[10];
void bucketSort(int num[],int length)
{
    int flag;
    for(int i=0;i<length;i++)
    {
        if(bucket[num[i]>>1].size==0)
            bucket[num[i]>>1].insert(0,num[i]);
        else
        {
            flag=0;
            for(int j=1;j<=bucket[num[i]>>1].size;j++)
            {
                if(bucket[num[i]>>1].inquire(j)->data1>num[i])
                {
                    bucket[num[i]>>1].insert(j-1,num[i]);
                    flag=1;
                    break;
                }
            }
            if(flag==0)
                bucket[num[i]>>1].insert(bucket[num[i]>>1].size,num[i]);
        }
    }
    int count=0;
    for(int i=0;i<Size;i++)
    {
        for(int j=1;j<=bucket[i].size;j++)
        {
            num[count]=bucket[i].inquire(j)->data1;
            bucket[i].pop(j);    //�ͷ��ڴ棬��ֹ�ڴ�й©
            count++;
        }
    }
}

void CountingSort(int *A,int *B,int *Order,int N,int K)
{
    int *C=new int[K+1];
    int i;
    memset(C,0,sizeof(int)*(K+1));
    for (i=1;i<=N;i++) //��A�е�ÿ��Ԫ�ط���
        C[A[i]]++;
    for (i=2;i<=K;i++) //ͳ�Ʋ�����i��Ԫ�صĸ���
        C[i]+=C[i-1];
    for (i=N;i>=1;i--)
    {
        B[C[A[i]]]=A[i]; //����ͳ�Ƶ�λ�ã���ֵ�����B�У���˳�������Order��
        Order[C[A[i]]]=i;
        C[A[i]]--;
    }
}

void countSortEasy(int num[],int length,int maxNum)
{
    memset(temp1,0, sizeof(int)*(maxNum+1));
    for(int i=0;i<length;i++)
        temp1[num[i]]++;
    int c=0;
    for(int i=0;i<=maxNum;i++)
    {
        for(int j=0;j<temp1[i];j++)
        {
            num[c]=i;
            c++;
        }
    }
}

void countSortComplex(int num[],int length,int maxNum)
{
    memset(temp1,0, sizeof(int)*(maxNum+1));
    for(int i=0;i<length;i++)
        temp1[num[i]]++;
    for(int i=0;i<maxNum;i++)
    {
        temp1[i+1]=temp1[i]+temp1[i+1];
    }
    for(int i=length-1;i>=0;i--)
    {
        temp2[temp1[num[i]]-1]=num[i];
        temp1[num[i]]--;
    }
    for(int i=0;i<length;i++)
    {
        num[i]=temp2[i];
    }
}

//int maxbit(int data[],int n)
//{
//    int d=1;
//    for(int i=0;i<n;i++)
//    {
//        int c=1;
//        int p=data[i];
//        while(p/10)
//        {
//            p=p/10;
//            c++;
//        }
//        if(c>d)
//            d=c;
//    }
//    return d;
//}
//
//void RadixSort(int data[],int n)
//{
//    int d=maxbit(data,n);
//    int r=1;
//    int rad[n];
//    int c[10],count1;
//    memset(c,0, sizeof(int)*10);
//    for(int i=0;i<d;i++)
//    {
//
//        for(int i=0;i<10;i++)//װͰ֮ǰҪ����Ͱ
//            count[i]=0;
//        for(i=0;i<n;i++) //��¼ÿ��Ͱ�ļ�¼��
//        {
//            int k=data[i]/r;
//            int q=k%10;
//            count[q]++;
//        }
//        for(i=1;i<10;i++)//����λ��
//        {
//            count[i]+=count[i-1];
//        }
//        for(int j=n-1;j>=0;j--)
//        {
//            int p=data[j]/r;
//            int s=p%10;
//            tmp[count[s]-1]=data[j];
//            count[s]--;
//        }
////        countSort(tmp,10,100);
//        for(int k=0;k<n;k++)
//        {
//            num[i]=tmp[i];
//            c[i]++;
//        }
//        r=r*10;
//    }
////    r=0;
////    count1=0;
////    for(int i=0;i<10;i++)
////    {
////        for(int j=i;j<c[i];j++)
////        {
////            num[r]=rad[count1+j];
////            r++;
////        }
////        count1+=c[i];
////    }
//
//}

int main()
{
    for(int i=0;i<Max;i++)
    {
        num[i]=Max-i;
    }
    double time;
    time=clock();
//    bucketSort(num,Max);
    time=clock()-time;
    cout<<"��������������ݹ�ģ��"<<Max<<endl<<"��ʱΪ��\t";
    cout<<time<<endl;
    time=clock();
    countSortComplex(num,Max,Max);
    time=clock()-time;
    cout<<"��������������ݹ�ģ��"<<Max<<endl<<"��ʱΪ��\t";
    cout<<time<<endl;
//    RadixSort(num,Max);
    for(int i=0;i<Max;i++)
        cout<<num[i]<<" ";
    cout<<endl;
    return 0;
}
