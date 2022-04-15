#ifndef DRAWTREE_HH
#define DRAWTREE_HH

#include <ostream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <algorithm>

namespace
{
#define lChild _lchild  //使用前将 l_child_ 更换为 自己树节点的左孩子的名字
#define rChild _rchild //使用前将 r_child_ 更换为 自己树节点的右孩子的名字
#define data   _key     //使用前将 data_ 更换为 自己树节点的数据的变量名
#define MAXN (1000)      //这棵树的节点上限
#define PERID (2)        //打印两个节点的横坐标间隔
    unsigned int SUM;  //统计当前遍历到第几个节点

#ifdef _WIN32
    void clear() { system("cls"); }
#elif __linux__
    void clear() { system("clear"); }
#endif

    // 将光标移动到 (X,Y)
    std::string AXIS(int X, int Y) {
        std::stringstream ss;
        ss << "\033[" << Y << ";" << X << "H";
        return ss.str();
    }

    struct DrawNode {
        int x, y, dataSize;
    }axisArray[MAXN];

    


    //计算节点数据输出的长度
    template <typename TreePtr>
    int dataSize(TreePtr const& root) {
        std::stringstream ss;
        ss << (root->data);
        return (ss.str()).length();
    }

    //中序遍历, 从左往右画节点(不连线)
    //横坐标通过全局变量SUM和上一个节点数据的输出长度算出
    //纵坐标通过递归深度判断
    //PERID 是两个节点间隔长度
    template <typename TreePtr>
    void buildDrawTree(TreePtr const& root, int deep) {
        if (!root) return;  //判断空节点,如果你的节点判空和我不一样,这里也要改, 比如我之前的判断空节点是(root->height_== -1).

        if (root->lChild)  buildDrawTree(root->lChild, deep + 1);

        axisArray[SUM] = (struct DrawNode){ axisArray[SUM - 1].x + axisArray[SUM - 1].dataSize + PERID, deep, dataSize(root) };
        std::cout << AXIS(axisArray[SUM].x, axisArray[SUM].y) << root->data;
        ++SUM;

        if (root->rChild)  buildDrawTree(root->rChild, deep + 1);

    }

    template <typename TreePtr>
    void Draw(TreePtr const& t) {  //画树函数
        clear();  //清屏
        SUM = 1;
        int maxy = 0;

        buildDrawTree<TreePtr>(t, 2);   //每个结点画出来

        //画节点间连线,因为画的节点不会太多,所以就写了n^2的算法,比较好实现
        //每个节点只有一个父节点,所以画出每个节点和自己父节点的连线即可
        for (int i = 1; i < SUM; i++) {
            //x,y是子节点的坐标,p是父节点的axisArray数组的下标, px,py是父节点的坐标;
            int x = axisArray[i].x, y = axisArray[i].y, p = 0, px = 0, py = y - 1;

            if (y == 1) continue; // 根结点没有父节点,跳过

            for (int j = 1; j < SUM; j++) {  //循环找父节点
                if (i == j) continue;
                if ((!p || abs(axisArray[j].x - x) < abs(px - x)) && axisArray[j].y + 1 == y)
                    p = j, px = axisArray[j].x;
            }

            int s = (2 * x + axisArray[i].dataSize) >> 1;
            std::cout << AXIS(s, py) << '+';
            if (s < px)
                for (int i = s + 1; i < px; i++) std::cout << AXIS(i, py) << '-';
            else
                for (int i = px + axisArray[p].dataSize; i < s; i++) std::cout << AXIS(i, py) << '-';
            maxy = std::max(maxy, y);
        }
        std::cout << AXIS(1, maxy + 1);  //打印完把光标移到最下边.
        // getchar();
    }
} // namespace
#endif

