

#include <iostream>
#include <string>
using namespace std;

int main()
{
    string s;//输入字符串
    cout << "请输入密文" << endl;

    getline(cin, s);


    for (int a = 0; a < 26; a++)


    {
        cout << "移位位数为：" << a << "时" << endl;
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] >= 65 && s[i] <= 90)//大写字母
            {

                int t = s[i] - a;
                if (t < 65)
                    t = t + 26;//越减越小，要按26加

                s[i] = (char)(t);

                continue;
            }

            if (s[i] >= 97 && s[i] <= 122)//小写字母
            {

                int t = s[i] - a;
                if (t < 97)
                    t = t + 26;
                s[i] = (char)(t);
                continue;
            }

        }
        cout << s << endl;



    }
}

