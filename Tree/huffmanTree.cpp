//
// Created by Fitz on 2017/11/29.

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cstdio>

using namespace std;
//����ȷ�����齨��ʱ�����С
#define codeNum 256
#define nullptr NULL
//����������ڴ��ļ���ȡ��Ϣ��flag=1������ȡһ��δѹ���ļ���flag=2������ȡһ���Ѿ�ѹ�������ļ������ڽ�ѹ
void getContent(int flag,char* path);
//�����������ͳ��������ÿ���ַ��ĳ���Ƶ��
void statistics();
//����������ڽ�ѹ�����߽�ѹ�������д���ļ�
void writeCode(int flag,char* path);
//�����洢�������µ��ַ�Ƶ���������Ӧ��ascii����Ϊ������±�
int character[codeNum+1];
//�����洢���ļ�����Ķ����Ƶı���
string Article;
//�����洢���ļ�����Ķ����Ƶı���
string binary;
//����ṹ�߱�ʾһ������������һ���ڵ�
struct CellElement
{
    int pority;   //����ڵ��Ȩ��
    int pocessID; //�����ID
};
//������ʾС���ѵ�һ���ڵ�
class cellElement
{
public:
    int weight,lchild,rchild;
    cellElement()
    {
        weight=0;
        lchild=-1;
        rchild=-1;
    }
};

class heapmin
{
public:
    int size;
    int Maxlength;
    CellElement *Elements;
    heapmin(int length)
    {
        size=0;
        Maxlength=length;
        Elements=new CellElement[Maxlength];
    }

    bool empty()
    {
        if(size==0)
            return true;
        return false;
    }

    bool full()
    {
        return (size==Maxlength-1);
    }

    bool insert(int p,int ID)
    {
        int i=size+1;
        if(!full())
        {
            size++;
            while(i!=1&&p<=Elements[i/2].pority)
            {
                if(p<Elements[i/2].pority||(p==Elements[i/2].pority&&ID<Elements[i/2].pocessID))
                {
                    Elements[i].pority=Elements[i/2].pority;
                    Elements[i].pocessID=Elements[i/2].pocessID;
                    i=i/2;
                }
                else
                    break;
            }
            Elements[i].pocessID=ID;
            Elements[i].pority=p;
            return true;
        }
        return false;
    }

    CellElement top()
    {
        return Elements[1];
    }

    bool DeleteMin() {
        int parent = 1, child = 2;
        CellElement temp;
        if (!empty()) {
            temp = Elements[size];
            size--;
            while (child <= size) {
                if (child < size && Elements[child].pority > Elements[child + 1].pority)
                    child++;
                else if(child < size && Elements[child].pority == Elements[child + 1].pority&&Elements[child].pocessID>Elements[child + 1].pocessID)
                    child++;
                if (temp.pority < Elements[child].pority)
                    break;
                if(temp.pority==Elements[child].pority&&temp.pocessID<Elements[child].pocessID)
                    break;
                Elements[parent] = Elements[child];
                parent = child;
                child *= 2;
            }
            Elements[parent] = temp;
            return true;
        }
        return false;
    }
};
//������һ����codeNum+1��С��С���ѣ�����ɭ��Ȩ�صıȽϴ�С
heapmin sortedNum(codeNum+1);

class huffmanTree
{
public:
    int * frequency;
    string codeRule[codeNum+1],temp,encodeResult,decodeResult,encodeBinary,input;
    cellElement HT[2*codeNum-1];
    huffmanTree(int *temp)
    {
        frequency=temp;
    }
    //�ú������ݴ�����ַ�����Ƶ�ʣ�������������
    void establishTree()
    {
        for(int i=0;i<2*codeNum-1;i++)
        {
            HT[i].weight=0;
            HT[i].lchild=-1;
            HT[i].rchild=-1;
        }
        while(!sortedNum.empty())
            sortedNum.DeleteMin();
        for(int i=0;i<codeNum;i++)
        {
            HT[i].weight=frequency[i];
            sortedNum.insert(frequency[i],i);
        }
        int sum;
        for(int i=codeNum;i<2*codeNum-1;i++)
        {
            sum=0;
            HT[i].lchild=sortedNum.top().pocessID;
            sum+=sortedNum.top().pority;
            sortedNum.DeleteMin();
            HT[i].rchild=sortedNum.top().pocessID;
            sum+=sortedNum.top().pority;
            sortedNum.DeleteMin();
            HT[i].weight=sum;
            sortedNum.insert(HT[i].weight,i);
        }
    }

    //ͨ���������������õ���Ӧ�ı������
    void getCodeRule(int index)
    {
        if(index!=-1)
        {
            if(HT[index].lchild==-1&&HT[index].rchild==-1)
                codeRule[index]=temp;
            temp+='0';
            getCodeRule(HT[index].lchild);
            temp+='1';
            getCodeRule(HT[index].rchild);
            if(!temp.empty())
                temp.erase(temp.size()-1);
        }
        else
        {
            temp.erase(temp.size()-1);
        }
    }

    //�ú���ͨ�������洢ԭ�������ݵ��ַ���������Ӧ��ascii���滻Ϊ�Ѿ��õ��Ķ�Ӧ01���룬�������Ա����encodeResul��
    void encode()
    {
        encodeResult="";
        for(int i=0;i<Article.size();i++)
        {
            encodeResult+=codeRule[(unsigned char)(Article[i])];
        }
    }

    //�ú����ǽ�encode()�����õ���encodeResultͨ��λ���㣬ÿ8λ01�����Ϊһ���ֽڵĴ�С���ﵽѹ����Ŀ��
    void encodeBinaryAction()
    {
        encodeBinary="";
        char oneByte;
        int mod=8-(int)encodeResult.size()%8,temp,quotient=(int)encodeResult.size()/8;
        for(int i=0;i<((int)encodeResult.size()-8);i+=8)
        {
            oneByte=char(0xff);
            for(int j=7;j>=0;j--)
            {
                if(encodeResult[i-j+7]=='0') //i+7-j��ʾ���α��� i+0,i+1,i+2,����i+7��Ԫ��
                    temp=0;
                else
                    temp=1;
                temp=(temp<<j)|(~(1<<j));
                oneByte=char(oneByte&temp);
            }
            encodeBinary+=oneByte;
        }
        oneByte=char(0xff);
        int k=7;
        for(int i=quotient*8;i<encodeResult.size();i++)
        {
            if(encodeResult[i]=='0')
                temp=0;
            else
                temp=1;
            temp=(temp<<k)|(~(1<<k));
            oneByte=char(oneByte&temp);
            k--;
        }
        for(int j=mod-1;j>=0;j--)
        {
            temp=0;
            temp=(temp<<j)|(~(1<<j));
            oneByte=char(oneByte&temp);
        }
        encodeBinary+=oneByte;
        encodeBinary+=(char)mod;
    }

    //�ú���ͨ����01�ַ������Ѿ������Ĺ����������õ�������ԭ�ļ�����
    void decode()
    {
        decodeResult="";
        int index=2*codeNum-2;
        for(int i=0;i<input.size();i++)
        {
            if(input[i]=='0')
            {
                if(HT[index].lchild!=-1)
                {
                    index=HT[index].lchild;
                }
                if(HT[index].lchild==-1&&HT[index].rchild==-1)
                {
                    decodeResult+=char(index);
                    index=2*codeNum-2;
                }
            }
            else
            {
                if(HT[index].rchild!=-1)
                    index=HT[index].rchild;
                    if(HT[index].lchild==-1&&HT[index].rchild==-1)
                    {
                        decodeResult+=char(index);
                        index=2*codeNum-2;
                    }
            }
        }
    }

    //�ú���ͨ���Եõ���ѹ��������ݽ��л�ԭ����ÿһλ��01��Ϣ���һ��01�ַ������뵽decodeResult��
    void decodeBinary()
    {
        input="";
        char onebyte;
        int temp;
        for(int i=0;i<binary.size()-1;i++)
        {
            onebyte=binary[i];
            for(int j=7;j>=0;j--)
            {
                temp=((1<<j)&onebyte)>>j;
                if(temp==1)
                    input+='1';
                else if(temp==0)
                    input+='0';
            }
        }
        temp=binary[binary.size()-1];
        for(int i=0;i<temp;i++)
            input.erase(input.size()-1);
    }

};

void getContent(int flag,char* path)  //����ͳ��Ӣ���������ַ�����Ƶ�ʵĺ���
{
    string filePath;
    Article="";
    binary="";
    ifstream englishArticle;
    if(flag==1)
    {
        cout<<"������Ҫѹ��������ļ���·��"<<endl<<">>>";
        cin>>filePath;
        englishArticle.open(filePath.c_str(),ios::binary);
    }
    else if(flag==2)
    {
        cout<<"������Ҫ��ѹ���ļ�·��"<<endl<<">>>";
        cin>>filePath;
        englishArticle.open(filePath.c_str(),ios::binary);
    }
    else
        englishArticle.open(path,ios::binary);
    if(!englishArticle.is_open())
    {
        cout<<"���ļ�ʧ��,��������Ч·��"<<endl;
        exit(0);
    }
    if(flag==1||flag==3)
    {
        stringstream article;
        article<<englishArticle.rdbuf();  //�˴��пӣ�<<�ķ�����
        string test(article.str());
        Article=test;
    }
    else
    {
        int count;
        unsigned char temp;
        englishArticle.read((char*)&count, sizeof(int));
        for(int i=0;i<codeNum;i++)
            character[i]=0;
        for(int i=0;i<count;i++)
        {
            englishArticle.read((char*)&temp, sizeof(char));
            englishArticle.read((char*)&character[(int)temp], sizeof(int));
        }
        englishArticle.close();
        if(flag==2)
        {
            englishArticle.open(filePath.c_str(),ios::binary);
        }
        else
            englishArticle.open(path,ios::binary);
        stringstream article;
        article<<englishArticle.rdbuf();  //�˴��пӣ�<<�ķ�����
        string test(article.str());
        binary=test.substr(5*(count+1)-1);
    }
    englishArticle.close();
}

void statistics()
{
    for(int i=0;i<codeNum;i++)
    {
        character[i]=0;
    }
    for(int i=0;i<Article.size();i++)
    {
        character[(unsigned char)(Article[i])]++;
    }
}
//������һ�ù�������
huffmanTree hft(character);

void writeCode(int flag,char* path)
{
    string filePath;
    ofstream outCode;
    if(flag==1)
    {
        cout<<"������ѹ�����ļ��ı���·��"<<endl<<">>>";
        cin>>filePath;
        outCode.open(filePath.c_str(),ios_base::binary);
    }
    else if(flag==2)
    {
        cout<<"�������ѹ���ļ��ı���·��"<<endl<<">>>";
        cin>>filePath;
        outCode.open(filePath.c_str(),ios_base::binary);
    }
    else
        outCode.open(path,ios_base::binary);
    if(!outCode.is_open())
    {
        cout<<"����ļ��޷���"<<endl;
        exit(0);
    }
    if(flag==1||flag==3)
    {
        int count=0;
        for(int i=0;i<codeNum;i++)
        {
            if(character[i]!=0)
                count++;
        }
        outCode.write((char*)&count,sizeof(int));
        for(int i=0;i<codeNum;i++)
        {
            if(character[i]!=0)
            {
                outCode.write((char*)&i,sizeof(char));
                outCode.write((char*)&character[i], sizeof(int));
            }
        }
        outCode<<hft.encodeBinary;
        if(flag<3)
            cout<<"��ѹ���ļ�����Ϊ  ����Ϊ  "+filePath+"  ���ļ�"<<endl;
        else
            cout<<"��ѹ���ļ�����Ϊ  ����Ϊ  "<<path<<"  ���ļ�"<<endl;
    }
    else
    {
        outCode<<hft.decodeResult;
        if(flag<3)
            cout<<"��ѹ����ļ�����Ϊ  ����Ϊ  "+filePath+"  ���ļ�"<<endl;
        else
            cout<<"��ѹ����ļ�����Ϊ  ����Ϊ  "<<path<<"  ���ļ�"<<endl;
    }
    outCode.close();
}

void communicate()   //���û������Ľ���
{
    a:cout<<"��Ҫѹ���ļ����ǽ�ѹ�ļ���(����1 �� 2)"<<endl<<"tips:��������������ַ������Խ�������"<<endl<<"1��ѹ���ļ�"<<endl<<"2����ѹ�ļ�"<<endl<<">>>";
    int choice;
    cin>>choice;
    switch (choice)
    {
        case 1:
            getContent(1, nullptr);
            statistics();
            hft.establishTree();
            hft.getCodeRule(2*codeNum-2);
            hft.encode();
            hft.encodeBinaryAction();
            writeCode(1, nullptr);
            break;
        case 2:
            getContent(2, nullptr);
            hft.establishTree();
            hft.decodeBinary();
            hft.decode();
            writeCode(2, nullptr);
            break;
        default:
            cout<<"���������˳�"<<endl;
            exit(0);
    }
    goto a;
}

int main(int argc,char *argv[])
{
    if(argc==1)
        communicate();
    else if(argc==4)
    {
        if(argv[1][0]=='-'&&!argv[1][2])
        {
            if(argv[1][1]=='c')
            {
                getContent(3,argv[2]);
                statistics();
                hft.establishTree();
                hft.getCodeRule(2*codeNum-2);
                hft.encode();
                hft.encodeBinaryAction();
                writeCode(3,argv[3]);
                exit(0);
            }
            else if(argv[1][1]=='d')
            {
                getContent(4,argv[2]);
                hft.establishTree();
                hft.decodeBinary();
                hft.decode();
                writeCode(4,argv[3]);
                exit(0);
            }
        }
    }
    cout<<"usage:-c <input file path> <ouput file path>"<<endl<<"tips:this is to encode your file"<<endl;
    cout<<"usage:-d <input file path> <output file path>"<<endl<<"tips:this is to decode yout file"<<endl;
    return 0;
}