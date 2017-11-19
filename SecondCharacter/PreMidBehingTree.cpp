//
// Created by Fitz on 2017/11/18.
//
#include <iostream>
#include <stack>
#include <queue>
using namespace std;

struct cellElement{
    char data;
    cellElement *lchild,*rchild;
};

class BinaryTree
{
public:
    string pre,mid;
    cellElement *root;
    int length;
    BinaryTree(string a,string b)
    {
        pre=a;
        mid=b;
        if(a.length()!=b.length())
        {
            cout<<"error:  ������ַ�����һ���������Ϸ�"<<endl;
            exit(0);
        }
        for(int i=0;i<length;i++)
        {
            if(mid.find(pre[i])==-1||pre.find(mid[i]))
            {
                cout<<"error:  ����������޷�����������"<<endl;
                exit(0);
            }
        }
        length=a.length();
        root=create(mid[0],mid[length-1]);
    }
    cellElement * create(char a,char b)
    {
        static int i=0;
        int temp;
        cellElement *root=new cellElement;

        temp=mid.find((char)pre[i]);
        root->data=pre[i];
        if(a==b)
        {
            root->rchild=nullptr;
            root->lchild=nullptr;
            return root;
        }
        if(temp-1>=mid.find(a))
        {
            i++;
            root->lchild=create(a,mid[temp-1]);
        }
        else
        {
            root->lchild=nullptr;
        }
        if(temp+1<=mid.find(b))
        {
            i++;
            root->rchild=create(mid[temp+1],b);
        }
        else
        {
            root->rchild=nullptr;
        }
        return root;
    }
//ǰ������ݹ�
    void PreviousRecursive(cellElement *root)
    {
        if(root!=nullptr)
        {
            cout<<root->data<<" ";
            PreviousRecursive(root->lchild);
            PreviousRecursive(root->rchild);
        }
    }
//ǰ������ǵݹ�
    void PreviousNotRecursive(cellElement *root)
    {
        stack<cellElement*> trace;
        while(!trace.empty()||root)
        {
            if(root)
            {
                cout<<root->data<<" ";
                trace.push(root);
                root=root->lchild;
            }
            else
            {
                root=trace.top();
                trace.pop();
                root=root->rchild;
            }
        }
    }
//��������ݹ�
    void MidNotRecursive(cellElement *root)
    {
        stack<cellElement *> trace;
        while(root||!trace.empty())
        {
            if(root)
            {
                trace.push(root);
                root=root->lchild;
            }
            else
            {
                root=trace.top();
                cout<<root->data<<" ";
                trace.pop();
                root=root->rchild;
            }
        }
    }
//��������ǵݹ�
    void MidRecursive(cellElement *root)
    {
        if(root!=nullptr)
        {
            MidRecursive(root->lchild);
            cout<<root->data<<" ";
            MidRecursive(root->rchild);
        }
    }
//��������ݹ�
    void BehindNotRecursive(cellElement *root)
    {
        stack<cellElement*> trace;
        int flag;
        cellElement *LastVisted;
        do
        {
            while(root)
            {
                trace.push(root);
                root=root->lchild;
            }
            flag=1;      //��ʾ����Ը��ڵ��������ڵ��Ѿ���ջ�����ʹ���
            LastVisted= nullptr;
            while(flag==1&&!trace.empty())
            {
                root=trace.top();
                if(LastVisted==root->rchild)
                {
                    cout<<root->data<<" ";
                    trace.pop();
                    LastVisted=root;
                }
                else
                {
                    root=root->rchild;
                    flag=0;
                }
            }
        }while(!trace.empty());
    }
//��������ǵݹ�
    void BehindRecursive(cellElement *root)
    {
        if(root!=nullptr)
        {
            BehindRecursive(root->lchild);
            BehindRecursive(root->rchild);
            cout<<root->data<<" ";
        }
    }
//�������
    void FloorOrder(cellElement *root)
    {
        queue<cellElement*> floor;
        int len=0,newlen=0,count=0;
        while(count<length)
        {
            if(len==0&&newlen!=0)
            {
                len=newlen;
                newlen=0;
            }
            else if(newlen==0)
            {
                floor.push(root);
                len++;
            }
            while(len!=0)
            {
                if(floor.front()->lchild)
                {
                    floor.push(floor.front()->lchild);
                    newlen++;
                }
                if(floor.front()->rchild)
                {
                    floor.push(floor.front()->rchild);
                    newlen++;
                }
                root=floor.front();
                cout<<floor.front()->data<<" ";
                count++;
                floor.pop();
                len--;
            }
        }
    }
};

int main()
{
    string pre,mid;
    cout<<">>>������һ��ǰ������Ķ������ַ���"<<endl;
    cin>>pre;
    cout<<">>>������һ����������Ķ������ַ���"<<endl;
    cin>>mid;
    BinaryTree bt(pre,mid);
    cout<<"ǰ������˶�������  �ݹ�  ����ǣ�"<<endl;
    bt.PreviousRecursive(bt.root);
    cout<<endl;
    cout<<"ǰ������˶�������  �ǵݹ�  ����ǣ�"<<endl;
    bt.PreviousNotRecursive(bt.root);
    cout<<endl;
    cout<<"��������˶�������  �ݹ�  ����ǣ�"<<endl;
    bt.MidRecursive(bt.root);
    cout<<endl;
    cout<<"��������˶�������  �ǵݹ�  ����ǣ�"<<endl;
    bt.MidNotRecursive(bt.root);
    cout<<endl;
    cout<<"��������˶�������  �ݹ�  ����ǣ�"<<endl;
    bt.BehindRecursive(bt.root);
    cout<<endl;
    cout<<"��������˶�������  �ǵݹ�  ����ǣ�"<<endl;
    bt.BehindNotRecursive(bt.root);
    cout<<endl;
    cout<<"��������˶������Ľ���ǣ�"<<endl;
    bt.FloorOrder(bt.root);
    cout<<endl;
    return 0;
}

/*
abdhiecfjg
hdibeafjcg

abdhiejkcflmgno
hdibjekalfmcngo

abcdfgehi
bafdgchei

 */