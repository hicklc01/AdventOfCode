#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    string directions;
    cin >> directions;
    int ups = count(directions.begin(),directions.end(),'(');
    int downs = count(directions.begin(),directions.end(),')');
    cout<<ups-downs<<endl;
}
