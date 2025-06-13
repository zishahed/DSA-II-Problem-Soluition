/*
Suppose in a hospital, you are given the name of patients and their
serverity level, you have to print sort their name according to their
severity level.
10
Ajwad 14
Asif 86
Adeeb 30
Abrar 100
Abid 148
Shahed 28
Spondon 24
Nusair 52
Shazzad 126
Shifat 108
*/

#include <bits/stdc++.h>
using namespace std;
vector<pair<string, int>> patient;
void merge(int left, int mid, int right)
{
    int n1 = mid - left + 1, n2 = right - mid;
    vector<pair<string, int>> L(n1), R(n2);
    for (int i = 0; i < n1; i++)
        L[i] = patient[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = patient[mid + 1 + i];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (L[i].second <= R[j].second)
            patient[k++] = L[i++];
        else
            patient[k++] = R[j++];
    }
    while (i < n1)
        patient[k++] = L[i++];
    while (j < n2)
        patient[k++] = R[j++];
}
void mergeSort(int left, int right)
{
    if (left >= right)
        return;
    int mid = left + (right - left) / 2;
    mergeSort(left, mid);
    mergeSort(mid + 1, right);
    merge(left, mid, right);
}
void printSort(int n)
{
    cout << "Name \t Severity Level\n";
    for (int i = 0; i < n; i++)
        cout << patient[i].first << "\t\t  " << patient[i].second << '\n';
}
int main()
{
    int n;
    cin >> n;
    patient.resize(n);
    for (int i = 0; i < n; i++)
    {
        string s;
        int lvl;
        cin >> s >> lvl;
        patient[i] = {s, lvl};
    }
    mergeSort(0, n - 1);
    printSort(n);
}