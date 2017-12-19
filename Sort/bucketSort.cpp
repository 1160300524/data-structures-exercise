//
// Created by Fitz on 2017/12/17.
//
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include "linkList.h"

using namespace std;
#define Max 60000000   //��Ҫ������������Χ
#define bucketNum 5    //Ͱ�ĸ���
#define madix 1000      //���������л����Ĵ�С
#define MaxRandom 10000000     //���������ʱ��������Χ�Ķ���
int randomNum1[Max], randomNum2[Max], randomNum3[Max], randomNum4[Max];    //�ֱ�������������
int temp1[Max + 1];   //���ڼ�������ĸ�������
int temp2[Max + 1];   //���ڼ�������ĸ�������
linkList<int> bucket[bucketNum];   //Ͱ�ڵ�����ṹ��ʹ�÷������ linkList.h

//Ͱ����ĺ�����num����һ�����飬length��ʾ����ĳ���
void bucketSort(int num[], int length) {
    int flag;
    //��ÿ��Ͱ��ʹ�õ��ǲ�������
    for (int i = 0; i < length; i++) {
        if (bucket[num[i] >> 1].size == 0)  //���ԭ������Ϊ�գ��Ͳ���һ����Ԫ��
            bucket[num[i] >> 1].insert(0, num[i]);
        else {
            flag = 0;
            for (int j = 1; j <= bucket[num[i] >> 1].size; j++) {    //������Ŀ�ͷ�����ҵ��½ڵ���ʵĲ���λ��
                if (bucket[num[i] >> 1].inquire(j)->data1 > num[i]) {
                    bucket[num[i] >> 1].insert(j - 1, num[i]);
                    flag = 1;
                    break;
                }
            }
            if (flag == 0)
                bucket[num[i] >> 1].insert(bucket[num[i] >> 1].size, num[i]);
        }
    }
    int count = 0;
    //����Ͱ��˳�����ÿ��Ͱ����Ͱ�ڵ�����Ԫ�ظ���Ҫ��������飬ͬʱ�ͷ��ڴ�
    for (int i = 0; i < bucketNum; i++) {
        for (int j = 1; j <= bucket[i].size; j++) {
            num[count] = bucket[i].inquire(j)->data1;
            bucket[i].pop(j);    //�ͷ��ڴ棬��ֹ�ڴ�й©
            count++;
        }
    }
}

//һ�ּ��������ʡ�ڴ棬Ч�ʸߣ����ǲ������ڻ�������İ汾
void countSortEasy(int num[], int length, int maxNum) {
    memset(temp1, 0, sizeof(int) * (maxNum + 1));
    for (int i = 0; i < length; i++)
        temp1[num[i]]++;
    int c = 0;
    for (int i = 0; i <= maxNum; i++) {
        for (int j = 0; j < temp1[i]; j++) {
            num[c] = i;
            c++;
        }
    }
}

//�����ǿռ����Ľϴ�Ч����Խϵ͵İ汾�����ǿ������ڶ�ؼ��ʱȽ�
void countSortComplex(int num[], int length, int maxNum) {
    int better1, better2, better3;   //����ѭ��չ�����Ż���ʽ
    memset(temp1, 0, sizeof(int) * (maxNum + 1));
    for (int i = 0; i < length; i++)
        temp1[num[i]]++;
    int x;
    //������������ǵ�����ѭ�������ݼ����ϵͳ��ԭ����ʹ��3x1ѭ��չ���ķ�ʽ���Ż�Ч�ʣ���߲���ִ�е����������Դﵽ����Ч�ʵ�Ŀ��
    for (x = 0; x < length - 4; x += 3) {
        better1 = temp1[x] + temp1[x + 1];
        better2 = temp1[x] + (temp1[x + 1] + temp1[x + 2]);
        temp1[x + 1] = better1;
        better3 = better1 + (temp1[x + 2] + temp1[x + 3]);
        temp1[x + 2] = better2;
        temp1[x + 3] = better3;
    }
    //������������ʣ�ಿ��
    for (; x <= maxNum - 1; x++) {
        temp1[x + 1] = temp1[x] + temp1[x + 1];
    }

    //���ǲ���ѭ��չ���Ż��İ汾
//    for(int i=0;i<maxNum-1;i++)
//    {
//        temp1[i+1]=temp1[i]+temp1[i+1];
//    }

    //��λ������Ԫ��λ��
    for (int i = length - 1; i >= 0; i--) {
        temp2[temp1[num[i]] - 1] = num[i];
        temp1[num[i]]--;
    }
    //���޸ĺ��ֵ������Ҫ���������
    for (int i = 0; i < length; i++) {
        num[i] = temp2[i];
    }
}

//���������ʵ��  ���ڲ�ʹ���˼�������ĸ��Ӱ汾
void madixSort(int num[], int length, int max) {
//    ԭ������Ѱ�Ҵ�����������ֵ
//    int max=num[0];
//    for(int i=0;i<length-1;i++)
//    {
//        if(max<num[i+1])
//            max=num[i+1];
//    }
    int temp = 1;
    int stash;   //����洢һ������ֵ�����Ż�Ч��
    memset(temp1, 0, sizeof(int) * (max + 1));
    //ѭ�������ΰ��ո�λ��ʮλ��������
    while (max / temp) {
        //�������Ķ��Ǽ������������
        //����ĳλ,  �ݴ��������Ǹ�λ���ֵĴ���
        for (int i = 0; i < length; i++)
            temp1[(num[i] / temp) % madix]++;
        //�ݴ�����temp1  �д洢С���±�ֵ�ĳ��ִ���
        for (int i = 0; i < madix; i++) {
            temp1[i + 1] = temp1[i] + temp1[i + 1];
        }
        //��λ����ĳλ�����ؼ��ִ洢��λ�ã��ݴ��� temp2��
        for (int i = length - 1; i >= 0; i--) {
            stash = (num[i] / temp) % madix;   //�洢����num[i]��ĳλ��ֵ
            temp2[temp1[stash] - 1] = num[i];
            temp1[stash]--;
        }
        memset(temp1, 0, sizeof(int) * (max + 1));//��ʼ���������´�ѭ������Bug
        //��temp2�����ݸ��Ƶ�num������
        for (int i = 0; i < length; i++) {
            num[i] = temp2[i];
        }
        temp *= madix;
    }
}

int main() {
    int temp;
    for (int i = 0; i < Max; i++) {
//        temp = rand() % MaxRandom;
        temp=Max-i;
        randomNum1[i] = temp;
        randomNum2[i] = temp;
        randomNum3[i] = temp;
        randomNum4[i] = temp;
    }
    double time;
    time = clock();
//    sort(randomNum1,&randomNum1[Num],greater<int>());  //�Ӵ�С����
//    qsort(randomNum1,Max, sizeof(int),cmp);   //��С��������
    sort(randomNum1, &randomNum1[Max]);
    time = clock() - time;
    cout << "��������������ݹ�ģ��" << Max << endl << "STL���ŵ���ʱΪ��\t";
    cout << time / 1000 << "s" << endl;
    time = clock();
    countSortComplex(randomNum2, Max, Max);
    time = clock() - time;
    cout << "�������򣨿����ڻ������򣬶�ռ�ڴ�汾�������ݹ�ģ��" << Max << endl << "��ʱΪ��\t";
    cout << time / 1000 << "s" << endl;
    time = clock();
    countSortEasy(randomNum3, Max, Max);
    time = clock() - time;
    cout << "��������(ʡ�ڴ�汾)�����ݹ�ģ��" << Max << endl << "��ʱΪ��\t";
    cout << time / 1000 << "s" << endl;
    time = clock();
    madixSort(randomNum4, Max, Max);
    time = clock() - time;
    cout << "������������ݹ�ģ��" << Max << endl << "��ʱΪ��\t";
    cout << time / 1000 << "s" << endl;
    for (int i = 0; i < Max; i++) {
        if (randomNum1[i] != randomNum2[i]) {
            cout << i << endl;
            cout << randomNum1[i] << "  " << randomNum2[i] << endl;
        }
        if (randomNum1[i] != randomNum3[i]) {
            cout << i << endl;
            cout << randomNum1[i] << "  " << randomNum2[i] << endl;
        }
        if (randomNum1[i] != randomNum4[i]) {
            cout << i << endl;
            cout << randomNum1[i] << "  " << randomNum2[i] << endl;
        }
    }
    return 0;
}
