//coding=utf-8
#include <iostream>
#include <string.h>
#include <string>
using namespace std;

#define M 20
int college_num=20,item_num=20;
int man_item_num=20;
int item_data[M][M];
char item_name[M][M];  //ѧԺ������  ����ǰһ����ʾѧԺ�ı�ţ���һ�����ַ�������

typedef struct college_data
{
    int id;
    string name;
    int score[M];
    int score_sum,item_man_sum,item_woman_sum;
}college_data;

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

    }
private:
    void print_out()
    {
        cout<<"ѧԺ���\tѧԺ����\t�ܷ�\t���������ܷ�\tŮ�������ܷ�\t����"<<endl;
        for(int i=0;i<college_num;i++)
        {
            cout<<college[i].id<<"\t"<<college[i].name<<"\t"<<college[i].score_sum<<"\t"<<college[i].item_man_sum<<"\t"<<college[i].item_woman_sum<<"\t"<<i<<endl;
        }
    }

    void swap(int i,int j)
    {
        college_data temp = college[i];
        college[i] = college[j];
        college[j] = temp;
    }
};

int main() {
    university hit;
    cout<<hit.college[9].name<<endl;
    cout<<1<<"\t";
    return 0;
}