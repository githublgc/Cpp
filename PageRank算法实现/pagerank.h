#include<iostream>
#include<fstream>
#include<list>//链表
#include<algorithm>
using namespace std;

int count1 = 0;//记录节点总数

int count2 = 0;//记录有效节点数（有出度或入度）
bool* valid;//标记有入度的节点
bool* valid1;//判断有出度的节点
bool* blackhole;//标记仅有入度无出度的黑洞节点
int* counttoNode;//各节点指向节点的个数

int count3 = 0;//记录分块数目
int blocksize = 2000;//每块的大小

//β为PageRank遵循原连接关系的参数，1 - β概率进行N个样本上随机散落
//double beta = 0.85;//一般0.8-0.9，常用值0.85
double beta = 0.85;
//double sigma = 0.0000000000001;//判断是否收敛的阈值
double sigma = 0.000001;



double* Wtn;//在t=n时刻时的节点权重
double* Wtn1;//经过迭代后t=n+1时的更新权重

int m=30;//设为数据集中第一个tonode的ID

void countallnode()
{
	//通过保存最大NodeID来获取总数
	ifstream in("data.txt");
	int fromNode, toNode;
	while (!in.eof())
	{
		in >> fromNode >> toNode;
		if (fromNode > count1)
		{
			count1 = fromNode;
		}
		if (toNode > count1)
		{
			count1 = toNode;
		}
	}
	cout << "节点总数为：" << count1 << endl;
	cout << endl;
	
}

//将原文件分块保存
void blockSaving()
{
	count3 = count1 / blocksize + 1;
	cout << "每块大小为"<< blocksize <<"数据共可分为" << count3 << "块" << endl;
	cout << "开始分块" << endl;
	ofstream* out = new ofstream[count3];
	char buf[100];
	for (int i = 0; i < count3; i++)
	{
		sprintf_s(buf, "block%d.txt", i);
		out[i].open(buf);
	}
	ifstream in("data.txt");
	int fromNode, toNode;
	int current = -1;//头节点，放在第一个节点之前
	int count6 = 0;//记录当前记录了多少条，判断是否要换到下一个块记录数据
	list<int> LinkList;
	while (!in.eof())
	{
		in >> fromNode >> toNode;
		if (current != fromNode)
			//读取当前节点完成，先将原节点写入磁盘 
		{
			int t;
			while (!LinkList.empty())
			{
				t = LinkList.front();
				out[current / blocksize] << current << " " << counttoNode[current - 1] << " " << t << endl;
				LinkList.pop_front();
			}
			current = fromNode;
			count6 = 0;
		}
		 
		count6++;
		LinkList.push_back(toNode);//数据写入链表尾部
	}
	cout << "完成分块" << endl;
	cout << endl;
	
}

bool Isend()
{
	double New = 0.0, Old = 0.0;
	bool flag = false;//标志位，标记是否可以结束迭代
	for (int i = 0; i < count1; i++)
	{
		Old =Old+Wtn1 [i];
	}
	for (int i = 0; i < count1; i++)
	{
		if (valid[i]==false&&valid1[i]==false)
		{
			Wtn1[i] = 0;//无效节点更新后的权重还设为0
			continue;
		}
		else
		{
			Wtn1[i] += (1 - Old) / count2;
			if (Wtn[i] - Wtn1[i] > sigma || Wtn1[i] - Wtn[i] > sigma)//迭代前后和阈值sigma对比
			{
				flag = true;//差值较大，设置标志位，再次循环
			}
			Wtn[i] = Wtn1[i];//将上一轮迭代数据更新
			Wtn1[i] = 0;
			New =New+ Wtn1[i];
		}
	}
	
	return flag;
}

//构造分数列表，sort实现排名，取前100个输出
struct ScoreList
{
	int NodeId;
	double Score;
};
bool Compare(ScoreList r1, ScoreList r2)//添加比较函数实现sort降序
{
	return r1.Score > r2.Score;
}

ScoreList* L;//构建分数排名列表
void topRankCount()
{
	L = new ScoreList[count1];
	for (int i = 0; i < count1; i++)
	{
		L[i].NodeId = i;
		L[i].Score = Wtn[i];
	}
	sort(L, L + count1, Compare);//降序
	//sort(p, p + count1);升序排列
	cout << "节点排列完成" << endl;
	cout << endl;

}

