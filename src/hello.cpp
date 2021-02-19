#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    vector<string> msg {"Hello", "C++17", "World", "from", "VS Code", "and the C++ extension!"};
    
    for (const string& word : msg)
    {
        cout << word << " ";
    }
    cout << endl;

    int a{10};
    int *a_ptr = &a;

    cout<< a << "\n";
    cout<< a_ptr << "\n";
    cout<< *a_ptr << "\n";


}