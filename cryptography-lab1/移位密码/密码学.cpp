

#include <iostream>
#include <string>
using namespace std;

int main()
{
    cout << "请输入明/密文" << endl;
    string s;//输入字符串
    getline(cin, s);
    cout << "输入E加密，输入D解密" << endl;
    char c;
    cin >> c;
    cout << "请输入移位个数" << endl;
    int a;
    cin >> a;
    
    


    if (c == 'E')
    {

        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] >= 65 && s[i] <= 90)//大写字母
            {
                int t = s[i] + a - 65;
                t = t % 26;
                s[i] = (char)(t + 65);
                continue;
            }

            if (s[i] >= 97 && s[i] <= 122)//小写字母
            {
                int t = s[i] + a - 97;
                t = t % 26;
                s[i] = (char)(t + 97);
                continue;
            }

        }
        cout << s;


    }

    if (c == 'D')
    {

        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] >= 65 && s[i] <= 90)//大写字母
            {
                //int t = s[i] - a - 65;注意，这里不取模时就不用先减再加了！
                a = a % 26;//对移位数字取模
                int t = s[i] - a;
                if (t < 65)
                    t = t + 26;//越减越小，要按26加
                //s[i] = (char)(t + 65);
                s[i] = (char)(t);

                continue;
            }

            if (s[i] >= 97 && s[i] <= 122)//小写字母
            {
                a = a % 26;
                int t = s[i] - a;
                if (t < 97)
                    t = t + 26;
                s[i] = (char)(t);
                continue;
            }

        }
        cout << s;
    }

}