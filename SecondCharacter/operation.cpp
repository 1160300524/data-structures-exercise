//
// Created by Fitz on 2017/10/31.
//

#include <iostream>
#include <math.h>
using namespace std;

string operation = "+-*/()";

typedef union charOrInt{
    int num;
    char op;
}charOrInt;


typedef struct cellElement{
    cellElement *next;
    charOrInt data;
    bool ifINT;
}cellElement;

//������ǻ�������ָ�빹�ɵ�ջ�ṹ
class stack
{
public:
    cellElement *head=new cellElement;
    int length=0;

    stack(){
        length=0;
        head->next=NULL;
    }

    void push(charOrInt temp,bool ifINT)
    {
        cellElement *cell = new cellElement;
        if(length==0)
        {
            head->next=cell;
            cell->next=NULL;
        }
        else{
            cell->next=head->next;
            head->next=cell;
        }
        cell->data = temp;
        cell->ifINT=ifINT;
        length++;
        return;
    }

    charOrInt pop() //�ڵ���pop()ǰҪ�ж��Ƿ�Ϊ��
    {
        charOrInt x;
        cellElement *temp = head->next;
        head->next = temp->next;
        x = temp->data;
        delete(temp);
        length--;
        return x;
    }

    bool Empty()
    {
        if(head->next==NULL)
            return true;
        else
            return false;
    }

    cellElement * top()
    {
        if(Empty())
            return NULL;
        else
            return (head->next);
    }

};

//����������ڽ���׺����ʽת��Ϊ��׺����ʽ
class mid2tail:stack
{
public:
    stack max;
    stack OpChar;

    void push(char temp)
    {
        charOrInt x;
        x.op = temp;
        OpChar.push(x, false);
        if(max.Empty())
            max.push(x,false);
        else if(operation.find((*max.top()).data.op)/2<operation.find(x.op)/2)
            max.push(x,false);
        else;
    }

    char pop()
    {
        char x;
        charOrInt temp;
        temp=OpChar.pop();
        x=temp.op;
        if(operation.find((*max.top()).data.op)/2==operation.find(temp.op)/2)
            max.pop();
        return x;
    }
};



string Input;
stack transition;
charOrInt tran;
stack tail1,tail2;
mid2tail str;

//�����������������׺����ʽת��Ϊ��׺����ʽ
void mid2post()
{
    int sum;
    for(int i=0;i<=Input.length();i++)
    {
        if(Input[i]>='0'&&Input[i]<='9'&&i!=Input.length())
        {
            tran.num=int(Input[i]-'0');
            transition.push(tran,true);
        }
        else
        {
            if(!transition.Empty())
            {
                sum=0;
                int temp1 = transition.length;
                for(int j=1;j<=temp1;j++)
                {
                    sum+=transition.pop().num* (int)pow(10,j-1);
                }
                tran.num=sum;
                tail1.push(tran,true);
            }
            if((str.max.Empty()||(operation.find(Input[i])/2>operation.find(str.max.top()->data.op)/2))&&i!=Input.length())
            {
                str.push(Input[i]);
            }
            else{
                if(i==Input.length())
                {
                    int temp2=str.OpChar.length;
                    for(int i=0;i<temp2;i++)
                    {
                        tran.op=str.pop();
                        tail1.push(tran,false);
                    }
                    continue;
                }
                while(!str.OpChar.Empty()&&operation.find(Input[i])/2<=operation.find(str.max.top()->data.op)/2)
                {
                    tran.op=str.pop();
                    tail1.push(tran,false);
                }
                str.push(Input[i]);
            }
        }
    }
}

int main()
{
    cin>>Input;
    mid2post();
    int temp = tail1.length;
    for(int i=0;i<temp;i++)  //��tail1�ĵ���ת��Ϊ����
        tail2.push(tail1.pop(),tail1.top()->ifINT);

    for(int i=0;i<temp;i++)  //just for test
    {
        if(tail2.top()->ifINT)
            cout<<tail2.pop().num<<" ";
        else
            cout<<tail2.pop().op<<" ";
    }
    return 0;
}