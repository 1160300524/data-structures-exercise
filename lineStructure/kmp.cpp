//
// Created by Fitz on 2018/1/6.
//
/*
 * reference article:https://www.cnblogs.com/yjiyjige/p/3263858.html
 */
#include<iostream>
#include <cstdlib>

using namespace std;

void get_next(string pattern, int next[]) {
    int j = 0, k = -1;
    next[0] = k;
    while (j < pattern.size()) {
        if (k == -1 || pattern[j] == pattern[k]) {
            if (pattern[++j] == pattern[++k])
                next[j] = next[k];
            else
                next[j] = k;
        } else
            k = next[k];
    }
}

int kmp_match(string str, string pattern) {
    int index = 0, j = 0;
    int *next = (int *) malloc(sizeof(int) * pattern.size());
    get_next(pattern, next);
    while (index < str.size()) {
        if (str[index] == pattern[j]) {
            index++;
            j++;
        } else {
            if (next[j] == -1) {
                index++;
                j = 0;
            } else
                j = next[j];
        }
        if (j == pattern.size())
            break;
    }
    free(next);
    if (index == str.size() && j != pattern.size())
        return -1;
    return index - j + 1;
}

int main() {
    string str;
    string pattern;
    cout << "����������" << endl;
    cin >> str;
    cout << "������Ҫƥ����ַ���" << endl;
    cin >> pattern;
    int temp;
    if ((temp = kmp_match(str, pattern)) == -1)
        cout << "�޷��ҵ�ƥ����ַ���" << endl;
    else
        cout << "ƥ�䵽���ַ����������ĵ� " << temp << " ��λ��" << endl;
    return 0;
}
/*
dcbabcdef
abcd
cbabcd
 */