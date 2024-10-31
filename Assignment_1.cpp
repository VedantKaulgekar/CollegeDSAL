#include <iostream>
using namespace std;
struct Student
{
    int Roll_No;
    string First_Name;
    string Last_Name;
    float SGPA;
};

// quick sort

int partition(Student s[], int low, int high)
{
    Student pivot = s[high];
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (s[j].SGPA < pivot.SGPA)
        {
            i++;
            Student temp1 = s[i];
            s[i] = s[j];
            s[j] = temp1;
        }
    }
    Student temp2 = s[i + 1];
    s[i + 1] = s[high];
    s[high] = temp2;
    return i + 1;
}

void quicksort(Student s[], int low, int high)
{
    if (low < high)
    {
        int pivot_index = partition(s, low, high);
        quicksort(s, low, pivot_index - 1);
        quicksort(s, pivot_index + 1, high);
    }
}

void quicksort(Student s[], int low, int high);
int partition(Student s[], int low, int high);

int main()
{
    cout << "enter number of entries to accept :";
    int n;
    cin >> n;
    Student s[n];
    // input
    for (int i = 0; i < n; i++)
    {
        cout << "Enter Roll No of Student: ";
        cin >> s[i].Roll_No;
        cout << "Enter Name of Student: ";
        cin >> s[i].First_Name >> s[i].Last_Name;
        cout << "Enter SGPA of Student: ";
        cin >> s[i].SGPA;
        cout << endl;
    }
    // bubble sort
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (s[j].Roll_No > s[j + 1].Roll_No)
            {
                Student temp = s[j];
                s[j] = s[j + 1];
                s[j + 1] = temp;
            }
        }
    }
    // output bubble
    cout << endl
         << "Roll Number-wise order" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "Student " << i + 1 << " details:" << endl
             << s[i].Roll_No << ") " << s[i].First_Name << " " << s[i].Last_Name << " " << s[i].SGPA << endl;
    }
    // insertion sort
    for (int i = 1; i < n; i++)
    {
        Student tosort = s[i];
        int j = i - 1;
        while (j >= 0 && s[j].First_Name > tosort.First_Name)
        {
            s[j + 1] = s[j];
            j = j - 1;
        }
        s[j + 1] = tosort;
    }

    // output insertion
    cout << endl
         << "Alphabetical order" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "Student " << i + 1 << " details:" << endl
             << s[i].Roll_No << ") " << s[i].First_Name << " " << s[i].Last_Name << " " << s[i].SGPA << endl;
    }
    quicksort(s, 0, n - 1);
    // output quicksort
    cout << endl
         << "SGPA order" << endl;
    for (int i = n - 1; i >= 0; i--)
    {
        cout << "Student details:" << endl
             << s[i].Roll_No << ") " << s[i].First_Name << " " << s[i].Last_Name << " " << s[i].SGPA << endl;
    }
    // linear search
    cout << endl
         << "enter SGPA to search (Linear)" << endl;
    float searchl;
    int num = 0;
    cin >> searchl;
    for (int i = 0; i < n; i++)
    {
        if (s[i].SGPA == searchl)
        {
            cout << endl
                 << "Student " << "Roll No: " << s[i].Roll_No << ") " << s[i].First_Name << " " << s[i].Last_Name << " " << s[i].SGPA << endl;
            num++;
        }
    }
    if (num == 0)
    {
        cout << "No Students with given SGPA found";
    }
    // binary search
    cout << endl
         << "enter SGPA to search (Binary)" << endl;
    float searchb;
    int numb = 0;
    int high = n;
    int low = 0;
    int mid = (high + low) / 2;
    cin >> searchb;
    int found = 0;
    while (low <= high)
    {
        int mid = (high + low) / 2;
        if (s[mid].SGPA == searchb)
        {
            cout << endl
                 << "Student " << "Roll No: " << s[mid].Roll_No << ") " << s[mid].First_Name << " " << s[mid].Last_Name << " " << s[mid].SGPA << endl;
            found++;
            break;
        }
        else if (s[mid].SGPA < searchb)
        {
            low = mid + 1;
        }
        else
            high = mid - 1;
    }
    if (found == 0)
    {
        cout << endl
             << "no Students with given SGPA found" << endl;
    }
}
