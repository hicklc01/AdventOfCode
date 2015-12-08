#include <iostream>
#include <numeric>

using namespace std;

int main()
{
    string directions;
    cin >> directions;
    int floor,index = 0;
    for(auto c:directions){
        index++;
        c=='('?floor++:floor--;
        if(floor==-1)break;
    }
    cout<<index<<endl;
}
