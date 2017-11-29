//coding=utf-8
// Created by Fitz on 2017/10/27.
//
#include <iostream>
#include <fstream>
using namespace std;
typedef struct cellElement{
    cellElement *next;
    string name;
    string brand;   //��ʾƷ��
    int id,price ,amount;
}cellElement;

class chain{

public:
    cellElement *head;
    cellElement *previous = head;
    string FilePath="";

    chain(){
        head->next=NULL;
    }

    void insert(int id,string n,string b,int price,int a)
    {
        if(head->next==NULL){
            cellElement *p = new cellElement;
            head->next = p;
            p->id=id;
            p->next=NULL;
            p->name=n;
            p->brand=b;
            p->price=price;
            p->amount=a;
            //�˴�δ�жϴ���Ĳ����Ƿ�Ϊ��
        }

        else{
            cellElement *pr=head;
            cellElement *p=pr->next;
            while(p!=NULL)
            {
                if(p->price>=price)
                {
                    cellElement *temp = new cellElement;
                    temp->id=id;
                    temp->name=n;
                    temp->brand=b;
                    temp->price=price;
                    temp->amount=a;
                    temp->next = pr->next;
                    pr->next = temp;
                    return ;
                }
                pr=p;
                p=p->next;
            }
            cellElement *temp = new cellElement;
            temp->id=id;
            temp->next=NULL;
            temp->name=n;
            temp->brand=b;
            temp->price=price;
            temp->amount=a;
            pr->next=temp;
        }
    }

    cellElement* loate(int id){
        if(head->next==NULL){
            return NULL;   //�˴�ע���������
        }
        else{
            previous = head;
            cellElement *p = previous->next;
            while (p!=NULL){
                if(p->id==id)
                {
                    return p;
                }
                previous = p;
                p=p->next;
            }
            return NULL;
        }
    }

    void Delete(int id){
        cellElement *temp = this->loate(id);
        if(temp==NULL){
            return;
        }
        else{
            cellElement *p;
            p = previous->next;//previous->next;
            if(p->next==NULL){
                previous->next=NULL;
            }
            else{
                previous->next=p->next;
            }
            delete(p);
        }
    }

    void AddAmount(int id,int AddAmount){
        cellElement *p = this->loate(id);
        if(p==NULL){
            if(AddAmount<0) {
                cout<<"����Ʒû�п���ˣ��޷������"<<endl;
                return;
            }
            string a,b;
            int price;
            cout<<"���ݿ�û�д���Ʒ���벹�����Ʒ����Ϣ"<<endl<<"���������Ʒ�����ƣ�"<<endl;
            cin>>a;
            cout<<"���������Ʒ��Ʒ�ƣ�"<<endl;
            cin>>b;
            cout<<"���������Ʒ�ļ۸�"<<endl;
            cin>>price;
            cout<<"���������Ʒ�Ŀ��������"<<endl;
            cin>>AddAmount;
            this->insert(id,a,b,price,AddAmount);
            return ;
        }
        if(p->amount+AddAmount<0){
            cout<<"��治�㣬�޷������˶�Ļ��"<<endl;
            return;
        }
        p->amount+=AddAmount;
        cout<<"���ݸ��³ɹ���"<<endl;
        return;
    }

    void modify(int id,string name,string brand,int price,int amount){
        this->Delete(id);
        this->insert(id,name,brand,price,amount);
        return;
    }

    void empty()
    {
        this->InputFile();
        ofstream DataFile;
        DataFile.open(FilePath);
        cellElement *temp=head;
        cellElement *p = head->next;
        while(p->next!=NULL){
            temp = p->next;
            DataFile<<p->id<<" "<<p->name<<" "<<p->brand<<" "<<p->price<<" "<<p->amount<<endl;
            delete(p);
            p = temp;
        }
        DataFile<<p->id<<" "<<p->name<<" "<<p->brand<<" "<<p->price<<" "<<p->amount;
        delete(p);
        return;
    }

    void display(){
        cellElement *p = head->next;
        if(head!=NULL)
        {
            cout<<"�üҵ��ID\t�üҵ������\t�üҵ��Ʒ����\t�üҵ�ļ۸���\t�üҵ�Ŀ��������\t"<<endl;
        }
        while(p!=NULL){
            cout<<p->id<<"\t\t"<<p->name<<"\t\t"<<p->brand<<"\t\t"<<p->price<<"\t\t"<<p->amount<<endl;
            p=p->next;
        }
    }

    void ReadFromFile(){
        int price,amount,id,i=0;
        string name,brand;
        InputFile();
        ifstream DataFile;
        DataFile.open(FilePath);
        while (true){
            DataFile>>id>>name>>brand>>price>>amount;
            insert(id,name,brand,price,amount);
            if(DataFile.eof()!=0)
                break;
        }
        DataFile.close();
    }

private:
    void InputFile()
    {
        if(FilePath==""){
            cout<<"�������ļ���·�����������ļ������ƣ�"<<endl;
            cin>>FilePath;
        }
    }
};

int InitMenu(){
    int choice=0;
    while(choice<=0||choice>=3){
        cout<<"######��ӭ�����ҵ����ϵͳ######"<<endl;
        cout<<"��ѡ��ϵͳ��������ʽ��"<<endl;
        cout<<">>>1.�Լ�¼�����ݣ����浵"<<endl;
        cout<<">>>2.�����е��ļ���ȡ����"<<endl;
        cout<<"���������ѡ��(1 �� 2)"<<endl;
        cin>>choice;
    }
    return choice;
}

void menu(int *choice){
    cout<<"######�˵�######"<<endl;
    cout<<">>>1.����"<<endl;
    cout<<">>>2.ȡ��"<<endl;
    cout<<">>>3.��ѯĳ����Ʒ����Ϣ"<<endl;
    cout<<">>>4.���������Ʒ����Ϣ"<<endl;
    cout<<">>>5.�޸�ĳ����Ʒ����Ϣ"<<endl;
    cout<<">>>6.����ĳ����Ʒ����Ϣ"<<endl;
    cout<<">>>7.����Ӫҵ�����ݽ����浽ָ���ļ���"<<endl;
    cin>>*choice;
}

void solveChoice(int *choice,chain *Shop){
    int id,price,amount,Add;
    string name,brand;
    cellElement *p=NULL;
    switch(*choice){
        case 1:
            cout<<"������������ļҵ�ID��"<<endl;
            cin>>id;
            cout<<"�����������������"<<endl;
            cin>>Add;
            Shop->AddAmount(id,Add);
            break;
        case 2:
            cout<<"��������ȡ���ļҵ�ID��"<<endl;
            cin>>id;
            cout<<"��������ȡ����������"<<endl;
            cin>>Add;
            Shop->AddAmount(id,-Add);
            break;
        case 3:
            cout<<"�����������ѯ�ļҵ�ID��"<<endl;
            cin>>id;
            p= Shop->loate(id);
            if(p==NULL){
                cout<<"��IDû����Ʒ��֮��Ӧ"<<endl;
                break;
            }
            cout<<"����Ʒ��������\t"<<p->name<<"\t����Ʒ��Ʒ����\t"<<p->brand<<"\t����Ʒ�ĵ�����\t"<<p->price<<"\t����Ʒ��������\t"<<p->amount<<endl;
            break;
        case 4:
            Shop->display();
            break;
        case 5:
            cout<<"������������޸ĵ�id"<<endl;
            cin>>id;
            cout<<"���������޸ĺ����Ϣ��"<<endl;
            cout<<"����һ������������: ���ƣ�Ʒ�ƣ����ۣ������        (waring:���������˳�����룬���ܻᵼ�³�����������ݶ�ʧ)"<<endl;
            cin>>name>>brand>>price>>amount;
            Shop->modify(id,name,brand,price,amount);
            break;
        case 6:
            cout<<"����һ������������:  ��ƷID�����ƣ�Ʒ�ƣ����ۣ������        (waring:���������˳�����룬���ܻᵼ�³�����������ݶ�ʧ)"<<endl;
            cin>>id>>name>>brand>>price>>amount;
            p = Shop->loate(id);
            cout<<1<<endl;
            while(p!=NULL){
                cout<<"��ID�Ѿ������ˣ�����������һ��IDֵ";
                cin>>id;
                p = Shop->loate(id);
            }
            cout<<1<<endl;
            Shop->insert(id,name,brand,price,amount);
            cout<<"��ӳɹ�!"<<endl;
            break;
        case 7:
            Shop->empty();
            *choice = 0;
            break;
        default:
            *choice=1;
    }
    return;
}

int main()
{
    chain Shop;
    int InitChoice;
    char flag;
    InitChoice = InitMenu();
    if(InitChoice==1)
    {
        string name,brand;
        int price,amount,id=0;
        flag='y';
        while(flag=='y'||flag=='Y'){
            cout<<"����һ������������:  ��Ʒ���ƣ�Ʒ�ƣ����ۣ������        (waring:���������˳�����룬���ܻᵼ�³�����������ݶ�ʧ)"<<endl;
            cin>>name>>brand>>price>>amount;
            Shop.insert(id,name,brand,price,amount);
            id++;
            cout<<"���Ƿ���������룿����y(Y)��n(N)"<<endl;
            cin>>flag;
        }
    }
    else{
        Shop.ReadFromFile();
    }
    int choice=1;
    while(choice!=0){
        menu(&choice);
        solveChoice(&choice,&Shop);
    }
    cout<<"ϵͳ��ȫ�رգ���ӭ���ٴ�ʹ��~"<<endl;
    return 0;
}