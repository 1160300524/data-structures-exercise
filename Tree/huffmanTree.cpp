//
// Created by Fitz on 2017/11/29.
//
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
#define codeNum 256
void getContent();
void statistics();
int character[codeNum+1];
string Article;
string binary;

struct CellElement
{
    int pority;   //����ڵ��Ȩ��
    int pocessID; //�����ID
};

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

heapmin sortedNum(codeNum+1);

class huffmanTree
{
public:
    int * frequency,root;
    string codeRule[codeNum+1],temp,encodeResult,decodeResult,encodeBinary;
    cellElement HT[2*codeNum-1];
    huffmanTree(int *temp)
    {
        frequency=temp;
    }

    void establishTree()
    {
        //��ʼ��С����
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
        root=sortedNum.top().pocessID;
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
            if(temp.size()!=0)
                temp.erase(temp.size()-1);
        }
        else
        {
            temp.erase(temp.size()-1);
        }
    }

    void encode()
    {
        for(int i=0;i<Article.size();i++)
        {
            encodeResult+=codeRule[(unsigned char)(Article[i])];
        }
        cout<<"test"<<endl;
    }

    void encodeBinaryAction()
    {
        char oneByte;
        int mod=(int)encodeResult.size()%8,temp,quotient=(int)encodeResult.size()/8;
        for(int i=0;i<encodeResult.size();i+=8)
        {
            oneByte=0xff;
            for(int j=7;j>=0;j--)
            {
                if(encodeResult[i]=='0')
                    temp=0;
                else
                    temp=1;
                temp=temp<<j|((unsigned(1))>>(8-j));
                oneByte=oneByte&temp;
            }
            encodeBinary+=oneByte;
        }
        oneByte=char(0xff);
        for(int i=quotient*8;i<encodeResult.size();i++)
        {
            for(int j=7;j>=0;j--)
            {
                if(j>=mod)
                {
                    if(encodeResult[i]=='0')
                        temp=0;
                    else
                        temp=1;
                }
                else
                    temp=0;
                temp=temp<<j|((unsigned(1))>>(8-j));
                oneByte=char(oneByte&temp);
            }
        }
        encodeBinary+=oneByte;
        encodeBinary+=(char)mod;
    }

    void decode(string input)
    {
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

    void decodeBinary()
    {

    }

};

void getContent(int flag)  //����ͳ��Ӣ���������ַ�����Ƶ�ʵĺ���
{
    string filePath;
    if(flag==1)
        cout<<"������Ҫѹ��������ļ���·��"<<endl;
    else
        cout<<"������Ҫ��ѹ���ļ�·��"<<endl;
    cin>>filePath;
    ifstream englishArticle(filePath,ios::binary);
    if(!englishArticle.is_open())
    {
        cout<<"���ļ�ʧ��,��������Ч·��"<<endl;
        exit(0);
    }
    if(flag==1)
    {
        stringstream article;
        article<<englishArticle.rdbuf();  //�˴��пӣ�<<�ķ�����
        string test(article.str());
        Article=test;
    }
    else
    {
        int count;
        unsigned temp;
        englishArticle>>count;
        for(int i=0;i<count;i++)
        {
            englishArticle>>temp;
            englishArticle>>character[temp];
        }
        englishArticle>>binary;
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

huffmanTree hft(character);

void writeCode(int flag)
{
    string path;
    if(flag==1)
        path="file.zip";
    else
        path="decode.txt";
    ofstream outCode;
    outCode.open(path,ios::binary);
    if(!outCode.is_open())
    {
        cout<<"����ļ��޷���"<<endl;
        exit(0);
    }
    if(flag==1)
    {
        int count=0;
        for(int i=0;i<codeNum;i++)
        {
            if(character[i]!=0)
                count++;
        }
        outCode<<count;
        for(int i=0;i<codeNum;i++)
        {
            if(character[i]!=0)
            {
                outCode<<char(i)<<character[i];
            }
        }
        outCode<<hft.encodeBinary;
        cout<<"��ѹ���ļ�����Ϊ����Ϊ  "+path+"  ���ļ�"<<endl;
    }
    else if(flag==2)
    {
        outCode<<hft.decodeResult;
        cout<<"��ѹ����ļ�����Ϊ����Ϊ  "+path+"  ���ļ�"<<endl;
    }
    outCode.close();
}

int main()
{
    getContent(1);
    hft.decode(Article);
    writeCode(2);
    a:cout<<">>>��Ҫѹ���ļ����ǽ�ѹ�ļ���(����1 �� 2)"<<endl<<">>>1��ѹ���ļ�"<<endl<<">>>2����ѹ�ļ�"<<endl;
    int choice;
    cin>>choice;
    switch (choice)
    {
        case 1:
            getContent(1);
            statistics();
            hft.establishTree();
            hft.getCodeRule(2*codeNum-2);
            hft.encode();
            hft.encodeBinaryAction();
            writeCode(1);
            break;
        case 2:
            getContent(2);
            break;
        default:goto a;
    }

    return 0;
}
