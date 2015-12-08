#include <iostream>
#include <numeric>
#include <vector>
#include <functional>
#include <algorithm>
#include <iterator>
#include <regex>
#include <map>
#include <sstream>

#define HEIGHT 1000
#define WIDTH 1000

#define getPos(x,y) (x*1000+y)

using namespace std;
struct Rectangle{
    int x1;
    int y1;
    int x2;
    int y2;
};
struct line_reader: std::ctype<char> {
    line_reader(): std::ctype<char>(get_table()) {}
    static std::ctype_base::mask const* get_table() {
        static std::vector<std::ctype_base::mask> 
             rc(table_size, std::ctype_base::mask());
        rc['\n'] = std::ctype_base::space;
        return &rc[0];
    }
};

int main()
{   
    vector<int> lights(HEIGHT*WIDTH);
    
    map<string,function<void(vector<int>&,Rectangle&)>> actions= 
    {
        make_pair("turn on",function<void(vector<int>&i,Rectangle&)>([](vector<int> & vec,Rectangle& rect){
            for(int x = rect.x1;x<=rect.x2;x++){
                for(int y = rect.y1;y<=rect.y2;y++){
                    vec[getPos(x,y)]++;
                }
            }
        })),
        make_pair("turn off",function<void(vector<int>&i,Rectangle&)>([](vector<int> & vec,Rectangle& rect){
            for(int x = rect.x1;x<=rect.x2;x++){
                for(int y = rect.y1;y<=rect.y2;y++){
                    vec[getPos(x,y)] = max(vec[getPos(x,y)]-1,0);
                }
            }
        })),
        make_pair("toggle",function<void(vector<int>&i,Rectangle&)>([](vector<int> & vec,Rectangle& rect){
            for(int x = rect.x1;x<=rect.x2;x++){
                for(int y = rect.y1;y<=rect.y2;y++){
                    vec[getPos(x,y)] += 2;
                }
            }
        }))
    };
    regex command_regex("([^0-9]+) (\\d{1,3}),(\\d{1,3}) through (\\d{1,3}),(\\d{1,3})");
    cin.imbue(locale(locale(),new line_reader()));
    int rounds = accumulate(
        istream_iterator<string>(cin),
        istream_iterator<string>(),
        0,
        [&](int num,string command){
            Rectangle rect;
            smatch command_matches;
            if(regex_search(command,command_matches,command_regex)){
                stringstream(command_matches[2]) >> rect.x1; 
                stringstream(command_matches[3]) >> rect.y1; 
                stringstream(command_matches[4]) >> rect.x2; 
                stringstream(command_matches[5]) >> rect.y2; 
                actions[command_matches[1]](lights,rect);
            }
            return num +1;
        });
    int count = accumulate(lights.begin(),lights.end(),0,[](int total,int amount){ return total+amount;});
    cout<<count<<endl;
    return 0;
}
