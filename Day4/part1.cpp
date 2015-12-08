#include <openssl/md5.h>
#include <iostream>
#include <algorithm>

using namespace std;

string calculatemd5(string &msg)
{
    string result;
    const char* test = msg.c_str();
    int i;

    MD5_CTX md5;

    MD5_Init (&md5);
    MD5_Update (&md5, (const unsigned char *) test, msg.length());
    unsigned char buffer_md5[16];
    MD5_Final ( buffer_md5, &md5);
    char buf[32];
    for (i=0;i<16;i++){
        sprintf(buf, "%02x", buffer_md5[i]);
        result.append( buf );
    }
    return result;
}

int main()
{
    string secret_key;
    cin >> secret_key;
    bool found = false;
    int number =0;
    string test;
    string output;
    while(!found)
    {
        test = secret_key+to_string(number);
        output = calculatemd5(test);
        if(output.compare(0,5, "00000")==0){ found = true;}
        else number++;
    }
    cout<<test<<endl;

    return 0;
}
