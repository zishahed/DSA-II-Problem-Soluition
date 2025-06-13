#include <bits/stdc++.h>
using namespace std;
typedef tuple<int, string, double> t_isd;
vector<t_isd> employee;

void merge(int left, int mid, int right)
{
    int n1 = mid - left + 1, n2 = right - mid;
    vector<t_isd> L(n1), R(n2);
    for (int i = 0; i < n1; ++i)
        L[i] = employee[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = employee[mid + 1 + j];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (get<0>(L[i]) <= get<0>(R[j]))
            employee[k++] = L[i++];
        else
            employee[k++] = R[j++];
    }
    while (i < n1)
        employee[k++] = L[i++];
    while (j < n2)
        employee[k++] = R[j++];
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

t_isd binarySearch(int low, int high, int find)
{
    if (high >= low)
    {
        int mid = low + (high - low) / 2;
        if (get<0>(employee[mid]) == find)
            return employee[mid];
        else if (get<0>(employee[mid]) > find)
            return binarySearch(low, mid - 1, find);
        else
            return binarySearch(mid + 1, high, find);
    }
    return make_tuple(-1, "", -1.0);
}

void print()
{
    cout << "The Employee Information is given below: \n";
    for (auto &e : employee)
        cout << "ID: " << get<0>(e) << ", Name: " << get<1>(e) << ", Salary: " << get<2>(e) << "\n";
}
int main()
{
    int n;
    cout << "Enter the number of employee: ";
    cin >> n;
    employee.resize(n);
    for (int i = 0; i < n; i++)
    {
        cout << "Information of employee no. " << i + 1 << ": ";
        cout << endl;
        int id;
        cout << "Enter the ID: ";
        cin >> id;
        string name;
        cout << "Enter the name: ";
        cin >> name;
        double salary;
        cout << "Enter the salary: ";
        cin >> salary;
        cout << endl;
        employee[i] = make_tuple(id, name, salary);
    }
    mergeSort(0, n - 1);
    print();
    int find;
    cout << "\nWhich employee do you want to find? : ";
    cin >> find;
    t_isd found = binarySearch(0, n - 1, find);
    if (get<0>(found) == -1)
        cout << "\nEmployee not found\n";
    else
    {
        cout << "\nFound the employee. Info is: \n";
        cout << "ID: " << get<0>(found) << ", Name: " << get<1>(found) << ", Salary: " << get<2>(found) << "\n";
    }
}