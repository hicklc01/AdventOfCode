#include <iostream>
#include <numeric>
#include <vector>
#include <functional>
#include <algorithm>
#include <iterator>
#include <regex>

using namespace std;

int main()
{
    vector<function<bool (string)>> check_list{
        /*double letter seperated but not overlapped */
        [](string s){
                smatch double_matches;
                regex_search(s,double_matches,regex("(\\w\\w).*\\1"));
                bool is_good = double_matches.size()>0;
                return is_good;
            },
        /*repeated letter with one inbetween */
        [](string s){
                smatch double_matches;
                regex_search(s,double_matches,regex("(\\w).\\1"));
                bool is_good = double_matches.size()>0;
                return is_good;
            }
    };

    int nice_count = accumulate(
       istream_iterator<string>(cin),
       istream_iterator<string>(),
       0,
       [&](int count,string current){
            bool is_nice = accumulate(
                check_list.begin(),
                check_list.end(),
                true,
                [&](bool nice,function<bool (string)> criteria){
                   return nice && criteria(current);
                }
            );
            return is_nice?count+1:count;
       }
    );
    cout<<nice_count<<endl;
    return 0;
}
