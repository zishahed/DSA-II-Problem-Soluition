#include <bits/stdc++.h>
using namespace std;
vector<pair<int, string>> patient;

void mergeing(int left, int mid, int right)
{
    int n1 = mid - left + 1, n2 = right - mid;
    vector<pair<int, string>> L(n1), R(n2);
    for (int i = 0; i < n1; i++)
        L[i] = patient[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = patient[mid + 1 + i];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (L[i].first < R[j].first)
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
    mergeing(left, mid, right);
}

void print(){
    cout << "\nThe Patient infos are given below: \n";
    cout << "Serial No. \t Name";
    for(auto &p: patient)
        cout << p.first << '\t' << p.second;
    cout << '\n';
}

int main()
{
    int n;
    cout << "Enter the number of Patients: ";
    cin >> n;
    patient.resize(n);
    cout << "Enter the info of patients: \n";
    for (int i = 0; i < n; i++)
    {
        int serial;
        string name;
        //cout << "Enter the serial no. and Patient's name: ";
        cin >> name >> serial;
        patient[i] = make_pair(serial, name);
    }
    mergeSort(0, n - 1);
    print();
}