//
// Created by Fitz on 2017/11/29.
//
#include <iostream>
#include <fstream>
using namespace std;

int character[257];

void statistics()  //����ͳ��Ӣ���������ַ�����Ƶ�ʵĺ���
{
    for(int i=0;i<=255;i++)
        character[i]=0;
    string filePath;
    char temp;
    cout<<"������Ҫѹ�������Ӣ�����µ�·��"<<endl;
    cin>>filePath;
    ifstream englishArticle(filePath,ios::in);
    if(!englishArticle.is_open())
    {
        cout<<"���ļ�ʧ��,��������Ч·��"<<endl;
        exit(0);
    }
    while(!englishArticle.eof())
    {
        cin>>temp;
        character[int(temp)]++;
    }
    englishArticle.close();
}

int main()
{
    statistics();
    return 0;
}
