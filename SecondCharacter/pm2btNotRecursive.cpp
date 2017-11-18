//
// Created by Fitz on 2017/11/16.
//

#include <iostream>
#include<stack>
using namespace std;

struct cellElement{
    char data;
    int lchild,rchild;
};

class BinaryTree
{
public:
    string pre,mid;
    int head;
    int length;
    cellElement tree[100];
    BinaryTree(string a,string b)
    {
        pre=a;
        mid=b;
        if(a.length()!=b.length())
        {
            cout<<"������ַ�����һ���������Ϸ�"<<endl;
            exit(0);
        }
        length=a.length();
        for(int i=0;i<length;i++)
        {
            tree[i].data=mid[i];
            tree[i].lchild=-1;
            tree[i].rchild=-1;
        }
        create();
    }
    void create()
    {
        int j,temp;
        stack<int> cell; //������¼���������Ľڵ�
        for(int i=0;i<length;i++)
        {
            j=mid.find(pre[i]);
            if(cell.empty())
            {
                head=j;
                cell.push(j);
            }
            else
            {
                if(j<cell.top())
                {
                    tree[cell.top()].lchild=j;
                    cell.push(j);
                }
                else
                {
                    while(!cell.empty()&&j>cell.top())
                    {
                        temp=cell.top();
                        cell.pop();
                    }
                    tree[temp].rchild=j;
                    cell.push(j);
                }
            }
        }
    }

    void LayoutBehind(int index)
    {
        if(index!=-1)
        {
            LayoutBehind(tree[index].lchild);
            LayoutBehind(tree[index].rchild);
            cout<<tree[index].data<<endl;
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
    bt.LayoutBehind(bt.head);
    return 0;
}
/*
abdhiecfjg
hdibeafjcg
hidbeafjcg
 */