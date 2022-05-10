#include"pagerank.h"
using namespace std;

int a[100000];
int countl = 0;
//读取原数据，统计总节点数
void countal1node()
{
	ifstream in("data.txt");
	int fromNode, toNode;
	while (!in.eof())
	{
		a[0] = 0;
		for (int j = 0; j < count1; j++)
		{
			if (fromNode != a[j])
			{
				count1++;
				fromNode = a[count1];
			}
			if (toNode != a[j])
			{
				count1++;
				toNode = a[count1];
			}
		}
	}
}

int main()
{
	countallnode();//读取原数据，统计总节点数
	cout << "数据预处理" << endl;//统计每个节点的出度和是否有效 
	cout << "将孤立点权重设为0,统计有效节点" << endl;
		Wtn = new double[count1];
		Wtn1 = new double[count1];
		counttoNode = new int[count1];
		valid = new bool[count1];
		valid1 = new bool[count1];
		blackhole= new bool[count1];
		//初始化 出度数组和有效位数组 

		//将没有任何边的孤立点直接移除，设定权重为0
		//因为这些孤立点对PageRank的迭代过程不起任何作用
		for (int i = 0; i < count1; i++)
		{
			counttoNode[i] = 0;
			valid[i] = false;//预设各节点均为无入度的
			valid1[i] = false;//预设各节点均为无出度的
			blackhole[i] = false;//预设各节点均不是黑洞的
		}
		ifstream in("data.txt");
		int fromNode, toNode;
		//读取原文件，检测节点的有效性和出度 
		while (!in.eof())
		{
			in >> fromNode >> toNode;
			valid[fromNode - 1] = true;
			valid1[toNode - 1] = true;
			//valid[toNode - 1] = true;
			counttoNode[fromNode - 1]++;
		}

		int count5 = 0;
		//统计有效节点数量 
		for (int i = 0; i < count1; i++)
		{
			if (valid[i]||valid1[i])
			{
				
				count2++;
			}

			if (valid[i] && (valid1[i] == false))
			{
				count5++;//统计黑洞数量
				blackhole[i] = true;
			}
		}

		cout << "有出度/入度节点有" <<count2<<"个" << endl;
		cout << "其中有黑洞" << count5 << "个" << endl;
		cout << endl;
		

		for (int i = 0; i < count1; i++)
		{
			if (valid[i]||valid1[i])
			{
				Wtn[i] = 1 / count2;//初始时有效节点平分归一化的权重
			}
			else
			{
				Wtn[i] = 0;//无效节点权重为0
			}
			Wtn1[i] = 0;//等待更新权重的初始化
		}
		cout << "统计有效节点完成" << endl;
		cout << endl;

	
	blockSaving();

	cout << "开始迭代" << endl;
	bool flag = true;//迭代标志
	int count4 = 0;//迭代次数
	while (flag)//没有结束前反复迭代接近阈值
	{
		count4++;
		
		for (int i = 0; i < count3; i++)
		{
			char s[100];
			sprintf_s(s, "block%d.txt", i);
			ifstream in(s);
			int fromNode, votes, toNode;//从某节点投了n票给另一个节点
			int temp=0;
			//注意，数据中多条toNode重复，fromnode可以直接累加和，但随机游走只做一次。
			while (!in.eof())
			{
				in >> fromNode >> votes >> toNode;
				//以beta概率时，按照原来网络中的结构进行
				Wtn1[toNode - 1] = Wtn1[toNode - 1] + Wtn[fromNode - 1] / votes * beta;
				if(m!=toNode)//当数据集中来到新的toNode时，进行一次随机游走
				{
					//1.直接以1-beta的概率，在全体数据集上进行随机游走，解决蜘蛛网陷阱
					//Wtn1[toNode - 1] = Wtn1[toNode - 1] + (1 - beta) / count1;
					//2.改为以1-sblackhole概率,在解决蜘蛛网陷阱的基础上解决黑洞，sblackhole=rold/di
					//int s= Wtn1[toNode - 1] = Wtn1[toNode - 1] + Wtn[fromNode - 1] / votes * beta;
					// //r=r+(1-r)/N,r=0时代表黑洞
					/*Wtn1[toNode - 1] = Wtn1[toNode - 1] + (1 - Wtn1[toNode - 1]) / count1;*/
					//3.对非黑洞部分1-beta，对黑洞部分1/N
					if(blackhole[toNode-1]==false)
						Wtn1[toNode - 1] = Wtn1[toNode - 1] + (1 - beta) / count1;
					else
					{
						//Wtn1[toNode - 1] = Wtn1[toNode - 1] + (1 - Wtn1[toNode - 1]) / count1;
						Wtn1[toNode - 1] = 1 / count1;
					}
					
					m = toNode;//更新临时值m
				}
			}
		}
		flag = Isend();//用来判断是否可结束迭代
		
	}
	cout << "经过了" << count4 << "次迭代后收敛至设定阈值" <<sigma<< endl;
	cout << endl;

	topRankCount();
	cout << "将Top 100 NodeID以[NodeID] [Score]的形式保存到result.txt" << endl;
	ofstream out("result.txt");
	for (int i = 0; i < 100; i++)
	{
		out << L[i].NodeId + 1 << " " << L[i].Score << endl;
	}
	system("pause");
	return 0;
	
}