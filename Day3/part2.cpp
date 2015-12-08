#include <iostream>
#include <iterator>
#include <numeric>
#include <unordered_set>
#include <sstream>
#include <algorithm>
#include <functional>

using namespace std;
namespace std
{
    template<>
    struct  hash<pair<int,int>>
    {
        inline size_t operator()(const pair<int,int> &p) const {
            return hash<int>()(p.first)^ hash<int>()( p.second);
        }
    };
};

void processDirection(pair<int,int> &current, char instruction)
{
    switch(instruction){
        case '<':
            current.first -= 1;
        break;
        case '>':
            current.first += 1;
        break;
        case '^':
            current.second -= 1;
        break;
        case 'v':
            current.second += 1;
        break;
        default:
            cout<<instruction<<endl;
        break;
    }
}


int main()
{
    unordered_set<pair<int,int>> homes = accumulate(
        istream_iterator<char>(cin),
        istream_iterator<char>(),
        unordered_set<pair<int,int>>(),
        [santa = make_pair(0,0),robot = make_pair(0,0),issanta = true](unordered_set<pair<int,int>> current_homes, char direction) mutable {
            if(issanta){
                processDirection(santa,direction);
                current_homes.insert(santa);
            }else{
                processDirection(robot,direction);
                current_homes.insert(robot);
            }
            issanta =  !issanta;
            return current_homes; 
        }
    );
    cout<<homes.size()<<endl;
    homes.insert(make_pair(0,0));
    cout<<homes.size()<<endl;
    return 0;
}
