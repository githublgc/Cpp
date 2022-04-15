#include <iostream>
#include "BSTree.h"
#include<string>
using namespace std;


int main()
{
    BSTree<int> s;
   

    int a[8] = {7,6,8,4,3,5,1,2};
   
    cout << "逐点插入" << endl;
    for (int i = 0; i < 8; i++)
    {
        cout << a[i] << endl;
        s.insert(a[i]);
    }
    cin.clear();

    cout << "打印二叉查找树" << endl;
    cout << a[0];
    s.print();
    cout << endl;
    
    


    cout << "后序遍历二叉查找树:" << endl;
    s.postOrder();
    cout << endl;//

   
    //将后序遍历的各个节点放到数组里
   
        int temp;
        cout << "输入想要查看的节点" << endl;
        cin>>temp;//要找到的元素
        for(int i=0;i<7;i++)
        {
        if(x[i]==temp)
            cout<<"后序遍历的后继节点为"<<x[i+1]<<endl;
        }
 
    //元素替换
    BSTree<int> s1;

    int b[8];
    for (int i = 0; i < 8; i++)
    {
        b[i] = 0;
    }

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (a[i] >= a[j])
                b[i] = b[i] + a[j];
        }
    }

    for (int i = 0; i < 8; i++)
    {
        cout << b[i] << endl;
        s1.insert(b[i]);

    }

    cout << "替换为节点之和的二叉查找树" << endl;
    cout << b[0];
    s1.print();
    cout << endl;


    system("pause");

    return 0;
}