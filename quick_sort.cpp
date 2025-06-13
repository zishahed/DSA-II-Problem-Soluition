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
#include<bits/stdc++.h>
using namespace std;
vector<pair<string, int>> patient;
int partition(int low, int high)     // Haore's Partition Technique
{
    int pivot = patient[low].second;
    int i = low - 1, j = high + 1;
    while (true)
    {
        do
            i++;
        while (patient[i].second < pivot);
        do
            j--;
        while (patient[j].second > pivot);
        if (i >= j)
            return j;
        swap(patient[i], patient[j]);
    }
}
void quickSort(int low, int high)
{
    if (low < high)
    {
        int pi = partition(low, high);
        quickSort(low, pi);
        quickSort(pi + 1, high);
    }
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
    quickSort(0, n - 1);
    printSort(n);
}
