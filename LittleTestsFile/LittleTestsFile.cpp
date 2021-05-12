#include <iostream>
#include <cstring>
#include <vector>

using namespace std;




void main(){
    vector<int> a;

    a.push_back(1);
    a.push_back(2);

    for (auto i = a.begin(); i != a.end(); ++i)
    {
        cout << (*i) << '\t';
    }
    cout << endl;

    a.pop_back();

    for (auto i = a.begin(); i != a.end(); ++i)
    {
        cout << (*i) << '\t';
    }
    cout << endl;
 
}