//
// Created by Fitz on 2017/12/16.
//
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#define Num 100000000
#define Max 30000000
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
    if(num[mid]>num[b])
        swap(num[mid],num[b]);
    return mid;
}

void insertSort(int num[],int left,int right)
{
    int j,temp,k;
    for(int i=left+1;i<=right;i++)
    {
        temp=num[i];
        j=i;
        while(temp<=num[j]&&j>left)
        {
            j--;
        }
        k=i;
        while(k!=j+1)
        {
            num[k]=num[k-1];
            k--;
        }
        if(temp<num[j])
        {
            num[j+1]=num[j];
            num[j]=temp;
        }
        else
            num[j+1]=temp;
    }
}


void quickSort(int *num,int left,int right)
{
    int i,j,t,temp,l,r,lLen=0,rLen=0;
    if(left>=right)
        return;
    if(right-left<16)    // ���������Ĵ�СС��16ʱ�����ò��������Ч�ʸ���  ������β��ԣ����ֲ�����16ʱ��ʱ����
    {
        insertSort(num,left,right);
        return ;
    }
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
                if(pivot==r)
                    pivot=j;
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
                if(pivot==l)
                    pivot=i;
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
//        ���ս���׼����λ
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
    if(lLen>0)
        l--;
    int a=lLen;
    while(a>0)
    {
        swap(num[l],num[i-x]);
        x++;
        l--;
        a--;
    }
    a=rLen;
    x=1;
    if(rLen>0)
        r++;
    while(a>0)
    {
        swap(num[r],num[i+x]);
        x++;
        r++;
        a--;
    }
    quickSort(num,i+1+rLen,right);
    quickSort(num,left,i-1-lLen);
}

int cmp( const void *a , const void *b)
{
    return *(int *)a - *(int *)b;
}

int main()
{
    for(int i=0;i<Num;i++)
    {
//        temp=Min+rand()%Max;
        temp=Max-i;
        randomNum1[i]=temp;
        randomNum2[i]=temp;
    }
    cout<<endl;
    double time;
    time=clock();
//    sort(randomNum1,&randomNum1[Num],greater<int>());  //�Ӵ�С����
    qsort(randomNum1,Num, sizeof(int),cmp);   //��С��������
//    sort(randomNum1,&randomNum1[Num]);
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
        if(randomNum1[i]!=randomNum2[i])
        {
            cout<<i<<endl;
            cout<<randomNum1[i]<<"  "<<randomNum2[i]<<endl;
        }
    }
    return 0;
}
