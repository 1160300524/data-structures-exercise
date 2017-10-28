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
    cellElement *head=NULL;
    cellElement *previous = head;
    string FilePath="",FIleName="";
    void insert(int id,string n,string b,int price,int a)
    {
        if(head==NULL){
            cellElement *p = (cellElement *)malloc(sizeof(cellElement));
            if(p==NULL){
                cout<<"�ռ䲻�㣬�޷����뵽�ռ䣡"<<endl;
                return;
            }
            head = p;
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
            while(p->next!=NULL)
            {
                if(p->price>=price)
                {
                    cellElement *temp = (cellElement *)malloc(sizeof(cellElement));
                    if(temp==NULL){
                        cout<<"�ռ䲻�㣬�޷����뵽�ռ䣡"<<endl;
                        return;
                    }
                    temp->id=id;
                    temp->next=p;
                    temp->name=n;
                    temp->brand=b;
                    temp->price=price;
                    temp->amount=a;
                    pr->next=temp;
                    return ;
                }
                pr=p;
                p=p->next;
            }
            if(p->next==NULL)
            {
                cellElement *temp = (cellElement *)malloc(sizeof(cellElement));
                if(temp==NULL){
                    cout<<"�ռ䲻�㣬�޷����뵽�ռ䣡"<<endl;
                    return;
                }
                temp->id=id;
                temp->next=p;
                temp->name=n;
                temp->brand=b;
                temp->price=price;
                temp->amount=a;
                temp->next=NULL;
                p->next=temp;
            }
        }
    }

    cellElement* loate(int id){
        if(head==NULL){
            //cout<<"���ݻ�δ¼�룬�޷���ѯ��"<<endl;
            return NULL;   //�˴�ע���������
        }
        else{
            cellElement *p = previous;
            while (p->next!=NULL){
                if(p->id==id)
                {
                    return p;
                }
                previous = p;
                p=p->next;
            }
            if(p->next==NULL){
                //cout<<"�Ҳ�������Ʒ��"<<endl;
                return NULL;
            }
        }
    }

    void Delete(int id){
        cellElement *temp = this->loate(id);
        if(temp==NULL){
            return;
        }
        else{
            cellElement *p;
            p = previous->next;
            if(p->next==NULL){
                previous->next=NULL;
            }
            else{
                previous->next=p->next;
            }
            free(p);
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
            this->insert(id,a,b,price,AddAmount);
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
        InputFile();
        ofstream DataFile;
        DataFile.open(FilePath);
        cellElement *p = head;
        cellElement *temp;
        while(p->next!=NULL){
            if(p==head){
                temp = p->next;
                p = NULL;
                p = temp;
                continue;
            }
            temp = p->next;
            DataFile<<p->id<<" "<<p->name<<" "<<p->brand<<" "<<p->price<<" "<<p->amount<<endl;
            free(p);
            p = temp;
        }
        free(p);
        return;
    }

    void display(){
        cellElement *p = head;
        if(head!=NULL)
        {
            cout<<"�üҵ��ID��\t\t�üҵ��������\t\t�üҵ��Ʒ����\t\t�üҵ�ļ۸���\t\t�üҵ�Ŀ��������\t\t";
        }
        while(p!=NULL){
            cout<<p->id<<"\t"<<p->name<<"\t"<<p->brand<<"\t"<<p->price<<"\t"<<p->amount<<endl;
            p=p->next;
        }
    }

    void ReadFromFile(){
        int price,amount,id;
        string name,brand;
        InputFile();
        ifstream DataFile;
        DataFile.open(FilePath);
        while(true){
            DataFile>>id>>name>>brand>>price>>amount;
            this->insert(id,name,brand,price,amount);
            if(DataFile.eof())
                break;
        }
    }

private:
    void InputFile()
    {
        if(FilePath==""){
            cout<<"�������ļ���·�������������ļ������ƣ�"<<endl;
            cin>>FilePath;
        }
    }
};

int InitMenu(){
    int choice=0;
    while(choice<=0||choice>=2){
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
            cellElement *p = Shop->loate(id);
            if(p==NULL){
                cout<<"��IDû����Ʒ��֮��Ӧ"<<endl;
                break;
            }
            cout<<"����Ʒ��������"<<p->name<<"\t����Ʒ��Ʒ����"<<p->brand<<"\t����Ʒ�ĵ�����"<<p->price<<"\t����Ʒ��������"<<p->amount<<endl;
            break;
        case 4:
            Shop->display();
            break;
        case 5:
            cout<<"������������޸ĵ�id"<<endl;
            cin>>id;
            cout<<"���������޸ĺ����Ϣ��"<<endl;
            cout<<"����һ������������:  ��ƷID�����ƣ�Ʒ�ƣ����ۣ������        (waring:���������˳�����룬���ܻᵼ�³�����������ݶ�ʧ)"<<endl;
            cin>>name>>brand>>price>>amount;
            Shop->modify(id,name,brand,price,amount);
            break;
        case 6:
            cout<<"����һ������������:  ��ƷID�����ƣ�Ʒ�ƣ����ۣ������        (waring:���������˳�����룬���ܻᵼ�³�����������ݶ�ʧ)"<<endl;
            cin>>id>>name>>brand>>price>>amount;
            cellElement *temp = Shop->loate(id);
            while(temp!=NULL){
                cout<<"��ID�Ѿ������ˣ�����������һ��IDֵ";
                cin>>id;
                temp = Shop->loate(id);
            }
            Shop->insert(id,name,brand,price,amount);
            cout<<"��ӳɹ�!"<<endl;
            break;
        case 7:
            Shop->empty();
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