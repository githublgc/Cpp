
#include <iostream>
#include <string>
using namespace std;

int main()
{
    string s1, s2, s3;//输入字符串
    cout << "请输入密钥s1以构建置换表" << endl;
    cout << "要求：1.填满26位.2.大写字母.3.按字母表顺序给出对应关系" << endl;
    getline(cin,s1);
    cout << "置换表为：" << endl;
    for (int i = 0; i < 26; i++)
    {
        cout << (char)('A' + i) << " ";
    }
    cout << endl;
    for (int i = 0; i < s1.length(); i++)
    {
        if (s1[i] >= 65 && s1[i] <= 90)
            cout << s1[i] << " ";
        else
            continue;
    }

    cout << endl;

    cout << "输入明文，进行加密后得密文" << endl;
    getline(cin,s2);
    int count1 = s2.length();
    int* a;
    a = new int[count1];
    int t;
    for (int i = 0; i < count1; i++)//字母转换成坐标关系。
    {
        if (s2[i] >= 97 && s2[i] <= 122)
            s2[i] = s2[i] - 97 + 65;//如果输入小写时转换为大写字母进行加密。
        if (s2[i] >= 65 && s2[i] <= 90)
        {
            t = s2[i] - 65;
            a[i] = s1[t];
        }
        else
            a[i] = s2[i];
    }
    for (int i = 0; i < count1; i++)
        cout << char(a[i]);

    cout << endl;

    cout << "输入密文，进行解密后得明文" << endl;
    getline(cin,s3);
    int count2 = s3.length();
    int* b;
    b = new int[count2];
    //对应的密文不是连续关系，考虑逐个做减法（密-明）来记录明密文之间的关系
    //密-（密-明）=明
    // 不可行！注意s3,s1对应关系不一致！
    int *p=new int [count2];//偏移数表
    //for (int i = 0; i < 26; i++)
    //{
    //    p[i] = s1[i] - ('A' + i);
    //}

    //输入密文-》对应到s1[i]->i->明文i+65
    for (int i = 0; i < count2; i++)//字母转换成坐标关系。
    {
        for (int j = 0; j < 26; j++)//s3中各位对应的是密文中的第几个
        {
            if (s3[i] >= 97 && s3[i] <= 122)
                s3[i] = s3[i] - 97 + 65;//如果输入小写时转换为大写字母进行加密。
            if (s3[i] >= 65 && s3[i] <= 90)
            {
                if (s3[i] == s1[j])//!!双等号！
                    p[i] = j;
            }
            else
                p[i] = s3[i];
        }
        
    }

    /*for (int i = 0; i < count2; i++)
        cout << p[i] << "";
    cout << endl;*/

    for (int i = 0; i < count2; i++)//第几个密文，下标加上65便是明文
    {
        if (s3[i] >= 65 && s3[i] <= 90)
            b[i] = p[i] + 65;
        else
            b[i] = p[i];
    }
    for (int i = 0; i < count2; i++)
        cout << char(b[i]);


    
    
}

