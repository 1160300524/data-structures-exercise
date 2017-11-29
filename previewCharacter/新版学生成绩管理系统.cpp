//coding=utf-8
#include <iostream>
#include <string.h>
#include <sstream>
using namespace std;

#define M 50
int college_num=20,item_num=20;
int man_item_num=20;
int item_data[M][M];
int choice;
string item_name[M];
string college_name[M];
string file_path="",file_name="";
typedef struct college_data
{
    int id;
    int score[M];
    int score_sum,item_man_sum,item_woman_sum;
}college_data;

void init_menu()
{
    cout<<"����������������ɼ�or�������ļ���ȡ���ݣ�"<<endl;
    cout<<">>>1.������������ɼ�"<<endl<<">>>2.�������ļ���ȡ����"<<endl<<"����������ѡ��(1 or 2)"<<endl;
    cin>>choice;
    while(choice<=0||choice>2)
    {
        cout<<"������Χ������"<<endl<<"����������(1 or 2)"<<endl;
        cin>>choice;
    }
    return;
}

void if_file_path()
{
    if(file_path=="")
    {
        cout<<"�������ļ��洢��λ��(��\\��β)"<<endl;
        cin>>file_path;
    }
    if(file_name=="")
    {
        cout<<"�������ļ�������"<<endl;
        cin>>file_name;
    }
}

void write_file()
{
    FILE *file;
    if_file_path();
    string temp_path;
    temp_path=file_path;
    temp_path+=file_name;
    file=fopen(temp_path.c_str(),"w");
    while(file==NULL)
    {
        cout<<"�������Ч��·��(��\\��β)"<<endl;
        cin>>file_path;
        temp_path=file_path;
        temp_path+=file_name;
        file=fopen(temp_path.c_str(),"w");
    }
    fprintf(file,"%d\n%d\n%d\n",college_num,item_num,man_item_num);
    for(int i=0;i<item_num;i++)
    {
        int temp;
        if(i<man_item_num)
            temp=3;
        else
            temp=5;
        for(int j=0;j<temp;j++)
        {
            fprintf(file,"%d ",item_data[i][j]);
        }
    }
    fprintf(file,"\n");
    for(int i=0;i<item_num;i++)
    {
        fprintf(file,"%s\n",item_name[i].c_str());
    }
    for(int i=0;i<college_num;i++)
    {
        fprintf(file, "%s\n", college_name[i].c_str());
    }
    fclose(file);
}

void read_file()
{
    FILE *file;
    string temp_path;
    if_file_path();
    temp_path=file_path;
    temp_path+=file_name;
    file=fopen(temp_path.c_str(),"r");
    while(file==NULL)
    {
        cout<<"�������Ч��·��(��\\��β)"<<endl;
        cin>>file_path;
        temp_path=file_path;
        temp_path+=file_name;
        file=fopen(temp_path.c_str(),"r");
    }
    fscanf(file,"%d\n%d\n%d\n",&college_num,&item_num,&man_item_num);
    for(int i=0;i<college_num;i++)
    {
        int temp;
        if(i<man_item_num)
            temp=3;
        else
            temp=5;
        for(int j=0;j<temp;j++)
        {
            fscanf(file,"%d",&item_data[i][j]);
        }
    }
    //fscanf(file,"\n");
    for(int i=0;i<item_num;i++)
    {
        char temp[M];
        fscanf(file,"%s",temp);
        item_name[i] = temp;
        cout<<item_name[i]<<endl;
    }
    for(int i=0;i<college_num;i++)
    {
        char temp[M];
        fscanf(file,"%s",temp);
        college_name[i] = temp;
    }
    fclose(file);
}

void menu()
{
    cout<<"##�ɼ�ϵͳ�˵�##"<<endl;
    cout<<">>>1.��ѧԺ  ����������"<<endl;
    cout<<">>>2.��ѧԺ  �����������"<<endl;
    cout<<">>>3.��ѧԺ  �ܷ��������"<<endl;
    cout<<">>>4.��ѧԺ  ���������ܷ����"<<endl;
    cout<<">>>5.��ѧԺ  Ů���������ܷ����"<<endl;
    cout<<">>>6.��ѧԺ  ��Ų�ѯĳ����Ŀ�����"<<endl;
    cout<<">>>7.����Ŀ��Ų�ѯ�гɼ���ѧԺ"<<endl;
    cout<<">>>8.�޸�ѧԺ������"<<endl;
    cout<<">>>9.�޸���Ŀ������"<<endl;
    cout<<">>>10.�˳�"<<endl;
    cin>>choice;
}

class university
{
public:
    college_data college[M];
    university()
    {
        for(int i=0;i<college_num;i++)
        {
            college[i].id=i;
            memset(college[i].score,0, sizeof(college[i].score));
        }
        for(int i=0;i<item_num;i++)
        {
            if(i<man_item_num)
            {
                for(int j=0;j<3;j++)
                {
                    switch (j)
                    {
                        case 0:
                            college[item_data[i][j]].score[i]=5;
                            break;
                        case 1:
                            college[item_data[i][j]].score[i]=3;
                            break;
                        case 2:
                            college[item_data[i][j]].score[i]=2;
                            break;
                        default:;
                    }
                }
            }
            else
            {
                for(int j=0;j<5;j++)
                {
                    switch (j)
                    {
                        case 0:
                            college[item_data[i][j]].score[i]=7;
                            break;
                        case 1:
                            college[item_data[i][j]].score[i]=5;
                            break;
                        case 2:
                            college[item_data[i][j]].score[i]=3;
                            break;
                        case 3:
                            college[item_data[i][j]].score[i]=2;
                            break;
                        case 4:
                            college[item_data[i][j]].score[i]=1;
                            break;
                        default:;
                    }
                }
            }
        }
        for(int i=0;i<college_num;i++)
        {
            college[i].score_sum=0;
            college[i].item_man_sum=0;
            college[i].item_woman_sum=0;
            for(int j=0;j<item_num;j++)
            {
                college[i].score_sum+=college[i].score[j];
                if(j<man_item_num)
                    college[i].item_man_sum+=college[i].score[j];
                else
                    college[i].item_woman_sum+=college[i].score[j];
            }
        }
    }

    void sort_by_sum()
    {
        for(int i=0;i<college_num;i++)
        {
            int j=i;
            int max_num = college[i].score_sum;
            for(int k=i+1;k<college_num;k++)
            {
                if(max_num<college[k].score_sum)
                {
                    max_num = college[k].score_sum;
                    j=k;
                }
            }
            if(j!=i)
            {
                swap(i,j);
            }
        }
        print_out();
    }

    void sort_by_man_sum()
    {
        for(int i=0;i<college_num;i++)
        {
            int j=i;
            int max_num = college[i].item_man_sum;
            for(int k=i+1;k<college_num;k++)
            {
                if(max_num<college[k].item_man_sum)
                {
                    max_num = college[k].item_man_sum;
                    j=k;
                }
            }
            if(j!=i)
            {
                swap(i,j);
            }
        }
        print_out();
    }

    void sort_by_woman_sum()
    {
        for(int i=0;i<college_num;i++)
        {
            int j=i;
            int max_num = college[i].item_woman_sum;
            for(int k=i+1;k<college_num;k++)
            {
                if(max_num<college[k].item_woman_sum)
                {
                    max_num = college[k].item_woman_sum;
                    j=k;
                }
            }
            if(j!=i)
            {
                swap(i,j);
            }
        }
        print_out();
    }

    void sort_by_id()
    {
        for(int i=0;i<college_num;i++)
        {
            int j=i;
            int min_num = college[i].id;
            for(int k=i+1;k<college_num;k++)
            {
                if(min_num>college[k].id)
                {
                    min_num = college[k].id;
                    j=k;
                }
            }
            if(j!=i)
            {
                swap(i,j);
            }
        }
        print_out();
    }

    void sort_by_name()
    {
        for(int i=0;i<college_num;i++)
        {
            int j=i;
            string min_name = college_name[college[i].id];
            for(int k=i+1;k<college_num;k++)
            {
                if(min_name>college_name[college[k].id])
                {
                    min_name = college_name[college[k].id];
                    j=k;
                }
            }
            if(j!=i)
            {
                swap(i,j);
            }
        }
        print_out();
    }

    void search_by_id(int search_id,int search_item_id)
    {
        if(search_id>=college_num||search_id<0||search_item_id<0||search_item_id>=item_num)
        {
            cout<<"���ʵ����ݳ�����Χ"<<endl;
            return;
        }
        for(int i=0;i<college_num;i++)
        {
            if(college[i].id==search_id)
                cout<<"��Ҫ�ҵ�ѧԺ��\t"<<college_name[college[i].id]<<endl<<"��Ҫ�ҵ���Ŀ��\t"<<item_name[search_item_id]<<endl<<"�÷�Ϊ:\t"<<college[i].score[search_item_id]<<endl;
        }
    }

    void search_by_item(int search_item_id)
    {
        if(search_item_id<0||search_item_id>=item_num)
        {
            cout<<"���ʵ����ݳ�����Χ"<<endl;
            return;
        }
        cout<<"��Ҫ�ҵ�  "<<item_name[search_item_id]<<"  ����������"<<endl;
        if(search_item_id<man_item_num)
        {
            for(int i=0;i<3;i++)
            {
                cout<<"����"<<i+1<<"\t"<<college_name[item_data[search_item_id][i]]<<endl;
            }
        }
        else
        {
            for(int i=0;i<5;i++)
            {
                cout<<"����"<<i+1<<"\t"<<college_name[item_data[search_item_id][i]]<<endl;
            }
        }
    }

private:
    void swap(int i,int j)
    {
        college_data temp = college[i];
        college[i] = college[j];
        college[j] = temp;
    }
    void print_out()
    {
        cout<<"ѧԺ���\tѧԺ����\t�ܷ�\t���������ܷ�\tŮ�������ܷ�\t����"<<endl;
        for(int i=0;i<college_num;i++)
        {
            cout<<college[i].id<<"\t\t"<<college_name[college[i].id]<<"\t\t"<<college[i].score_sum<<"\t\t"<<college[i].item_man_sum<<"\t\t"<<college[i].item_woman_sum<<"\t"<<i+1<<endl;
        }
    }
};

//int main() {
//    int search_id,search_item;
//    string modify_name;
//    choice = 0;
//    init_menu();
//    if(choice==1)
//    {
//        do
//        {
//            cout<<"������ѧԺ��������(�������20)"<<endl;
//            cin>>college_num;
//        }while(college_num>20||college_num<=0);
//        do
//        {
//            cout<<"��������Ŀ��������(�������40)"<<endl;
//            cin>>item_num;
//        }while(item_num>40||item_num<=0);
//        do
//        {
//            cout<<"������������Ŀ��������(�������40)"<<endl;
//            cin>>man_item_num;
//        }while(man_item_num>20||man_item_num<=0);
//        cout<<"��ʼ����"<<item_num<<"����Ŀ�ĳɼ���"<<endl;
//        for(int i=0;i<item_num;i++)
//        {
//            if(i<man_item_num)
//            {
//                cout<<">>>�������"<<i+1<<"����Ŀ��ǰ3��ѧԺ��ţ�"<<endl;
//                for(int j=0;j<3;j++)
//                {
//                    cin>>item_data[i][j];
//                }
//            }
//            else
//            {
//                cout<<">>>�������"<<i+1<<"����Ŀ��ǰ5��ѧԺ��ţ�"<<endl;
//                for(int j=0;j<5;j++)
//                {
//                    cin>>item_data[i][j];
//                }
//            }
//        }
//        for(int i=0;i<college_num;i++)
//        {
//            college_name[i] = "ѧԺ";
//            stringstream stream;
//            stream<<i;
//            stream>>modify_name;
//            college_name[i]+=(char)(i+1+'0');
//        }
//        for(int i=0;i<item_num;i++)
//        {
//            item_name[i] = "��Ŀ";
//            stringstream stream;
//            stream<<i;
//            stream>>modify_name;
//            item_name[i] += modify_name;
//        }
//        write_file();
//    }
//    else
//        read_file();
//    choice=0;
//    university hit;
//    while(true)
//    {
//        choice=0;
//        menu();
//        switch (choice)
//        {
//            case 1:
//                hit.sort_by_id();
//                break;
//            case 2:
//                hit.sort_by_name();
//                break;
//            case 3:
//                hit.sort_by_sum();
//                break;
//            case 4:
//                hit.sort_by_man_sum();
//                break;
//            case 5:
//                hit.sort_by_woman_sum();
//                break;
//            case 6:
//                cout<<"��������Ҫ��ѯ��ѧԺ���"<<endl;
//                cin>>search_id;
//                cout<<"��������Ҫ��ѯ����Ŀ���"<<endl;
//                cin>>search_item;
//                hit.search_by_id(search_id,search_item);
//                break;
//            case 7:
//                cout<<"��������Ҫ��ѯ����Ŀ���"<<endl;
//                cin>>search_item;
//                hit.search_by_item(search_item);
//                break;
//            case 8:
//                cout<<"�����������޸ĵ�ѧԺ���"<<endl;
//                cin>>search_id;
//                cout<<"����������ĳɵ�ѧԺ����"<<endl;
//                cin>>modify_name;
//                college_name[search_id]=modify_name;
//                break;
//            case 9:
//                cout<<"�����������޸ĵ���Ŀ���"<<endl;
//                cin>>search_item;
//                cout<<"�����������޸ĳɵ���Ŀ����"<<endl;
//                cin>>modify_name;
//                item_name[search_item]=modify_name;
//                break;
//            case 10:
//                write_file();
//                exit(0);
//            default:
//                cout<<"���벻��ѡ�Χ������������"<<endl;
//        }
//    }
//}

/*C:\Users\29488\Desktop\
5
5
3
2 1 3
4 1 0
1 3 2
4 3 2 1 0
0 1 2 3 4
*/