//coding=utf-8
#include <iostream>
#include <string.h>
using namespace std;

#define M 20
int college_num=20,item_num=20;
int man_item_num=20;
int item_data[M][M];
int choice;
string item_name[M];
string college_name[M];
string file_path=NULL,file_name=NULL;
typedef struct college_data
{
    int id;
    string name;
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
    if(file_path==NULL)
    {
        cout<<"�������ļ��洢��λ��"<<endl;
        cin>>file_path;
    }
    if(file_name==NULL)
    {
        cout<<"�������ļ�������"<<endl;
        cin>>file_name;
    }
}

void write_file()
{
    FILE *file;
    string temp_path;
    if_file_path();
    temp_path=file_path;
    temp_path+=file_name;
    file=fopen(temp_path,'w');
    while(file==NULL)
    {
        cout<<"�������Ч��·��"<<endl;
        cin>>file_path;
        temp_path=file_path;
        temp_path+=file_name;
        file=fopen(temp_path,'w');
    }
    fprintf(file,"%d%d%d",college_num,item_num,man_item_num);
    for(int i=0;i<item_num;i++)
    {
        int temp;
        if(i<man_item_num)
            temp=3;
        else
            temp=5;
        for(int j=0;j<temp;j++)
        {
            fprintf(file,"%d",item_data[i][j]);
        }
    }
    for(int i=0;i<item_num;i++)
    {
        fprintf(file,"%s",item_name[i]);
    }
    for(int i=0;i<college_num;i++)
    {
        fprintf(file, "%s", college_name[i]);
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
    file=fopen(temp_path,'w');
    while(file==NULL)
    {
        cout<<"�������Ч��·��"<<endl;
        cin>>file_path;
        temp_path=file_path;
        temp_path+=file_name;
        file=fopen(temp_path,'w');
    }
    fscanf(file,"%d%d%d",&college_num,&item_num,&man_item_num);
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
    for(int i=0;i<item_num;i++)
    {
        fscanf(file,"%s",&item_name[i]);
    }
    for(int i=0;i<college_num;i++)
    {
        fscanf(file, "%s", &college_name[i]);
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
            college[i].name="ѧԺ";
            college[i].name+=(char)(i+'0');
            college_name[i]=college[i].name;
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
                        case 2:
                            college[item_data[i][j]].score[i]=2;
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
                        case 2:
                            college[item_data[i][j]].score[i]=3;
                        case 3:
                            college[item_data[i][j]].score[i]=2;
                        case 4:
                            college[item_data[i][j]].score[i]=1;
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
            int max_num = college[i].id;
            for(int k=i+1;k<college_num;k++)
            {
                if(max_num<college[k].id)
                {
                    max_num = college[k].id;
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
            string min_name = college[i].name;
            for(int k=i+1;k<college_num;k++)
            {
                if(min_name>college[k].name)
                {
                    min_name = college[k].name;
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
                cout<<"��Ҫ�ҵ�ѧԺ��\t"<<college[i].name<<endl<<"��Ҫ�ҵ���Ŀ��\t"<<item_name[search_item_id]<<endl<<"�÷�Ϊ:\t"<<college[i].score[search_item_id]<<endl;
        }
    }

    void search_by_item(int search_item_id)
    {
        if(search_item_id<0||search_item_id>=item_num)
        {
            cout<<"���ʵ����ݳ�����Χ"<<endl;
            return;
        }
        cout<<"��Ҫ�ҵ���Ŀ"<<item_name[search_item_id]<<"����������"<<endl;
        if(search_item_id<man_item_num)
        {
            for(int i=0;i<3;i++)
            {
                cout<<"����"<<i<<"\t"<<college_name[item_data[search_item_id][i]]<<endl;
            }
        }
        else
        {
            for(int i=0;i<5;i++)
            {
                cout<<"����"<<i<<"\t"<<college_name[item_data[search_item_id][i]]<<endl;
            }
        }
    }

    void print_out()
    {
        cout<<"ѧԺ���\tѧԺ����\t�ܷ�\t���������ܷ�\tŮ�������ܷ�\t����"<<endl;
        for(int i=0;i<college_num;i++)
        {
            cout<<college[i].id<<"\t"<<college[i].name<<"\t"<<college[i].score_sum<<"\t"<<college[i].item_man_sum<<"\t"<<college[i].item_woman_sum<<"\t"<<i<<endl;
        }
    }
private:
    void swap(int i,int j)
    {
        college_data temp = college[i];
        college[i] = college[j];
        college[j] = temp;
    }
};

int main() {
    choice = 0;
    init_menu();
    if(choice==1)
    {
        do
        {
            cout<<"������ѧԺ��������(�������20)"<<endl;
            cin>>college_num;
        }while(college_num>20||college_num<=0);
        do
        {
            cout<<"��������Ŀ��������(�������40)"<<endl;
            cin>>item_num;
        }while(item_num>40||item_num<=0);
        do
        {
            cout<<"������������Ŀ��������(�������40)"<<endl;
            cin>>man_item_num;
        }while(man_item_num>20||man_item_num<=0);
        cout<<"��ʼ����"<<item_num<<"����Ŀ�ĳɼ���"<<endl;
        for(int i=0;i<item_num;i++)
        {
            if(i<man_item_num)
            {
                cout<<">>>�������"<<i+1<<"����Ŀ��ǰ3��ѧԺ��ţ�"<<endl;
                for(int j=0;j<3;j++)
                {
                    cin>>item_data[i][j];
                }
            }
            else
            {
                cout<<">>>�������"<<i+1<<"����Ŀ��ǰ5��ѧԺ��ţ�"<<endl;
                for(int j=0;j<5;j++)
                {
                    cin>>item_data[i][j];
                }
            }
        }

    }
    else
        read_file();

    university hit;
    return 0;
}
