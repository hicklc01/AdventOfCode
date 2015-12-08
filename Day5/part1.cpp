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
        /*has three vowels */
        [](string s){
            bool is_good = count_if(s.begin(),s.end(),
                    [](char c){
                       string vowels = "aeiou";
                       return vowels.find(c)!=string::npos;
                    })>=3;
            return is_good;

            },
        /*double letter (.)/1 */
        [](string s){
                smatch double_matches;
                regex_search(s,double_matches,regex("(\\w)\\1"));
                bool is_good = double_matches.size()>0;
                return is_good;
            },
        /*No {ab,cd,pg,xy} */
        [](string s){ 
                vector<regex> bad_pairs{
                    regex("ab"),
                    regex("cd"),
                    regex("pq"),
                    regex("xy")
                };
                
                bool is_good = accumulate(bad_pairs.begin(),bad_pairs.end(),true,
                    [&](bool good,regex banned_regex){
                        smatch banned_matches;
                        regex_search(s,banned_matches,banned_regex);
                        return good && banned_matches.size()==0;   
                    });
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
