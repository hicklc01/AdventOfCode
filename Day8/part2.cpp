#include <iostream>
#include <numeric>
#include <vector>
#include <functional>
#include <algorithm>
#include <iterator>
#include <regex>
#include <map>
#include <sstream>

using namespace std;

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
    cin.imbue(locale(locale(),new line_reader()));
    int count = accumulate(
        istream_iterator<string>(cin),
        istream_iterator<string>(),
        0,
        [&](int count,string line){
            int i =0;
            for(string::iterator it=line.begin();it!=line.end();it++)
            {
                switch(*it){
                    case '"':
                    case '\\':
                        i++;           
                }
                i++;
            }
            return count+((i+2)-line.length());
        });
    cout<<count<<endl; 
    return 0;
}
