/**********************************************
# Project Name : Key_Tasks
# File Name    : Key_Tasks.cpp
# File Function: solve the problem
# Author       : YunPeng Xu(徐云鹏)
# Update Date  : 2024/10/16
**********************************************/

#include<iostream>
#include<climits>
#include"MyDataStructure.h"

using std::cin;
using std::cout;
using std::cerr;
using std::endl;

//the max number of nodes
const int KMaxNodeNum = 100;

inline int Max(int a, int b){ return a > b ? a : b; }
inline int Min(int a, int b){ return a < b ? a : b; }

/*
* Function Name   : InputInt
* Function        : input a int in the range of [1, limit] and check the validation
* Input Parameters: int& - input
                    const int - limit
                    const char* - prompt
*/
void InputInt(int& input, const int limit, const char* prompt)
{
    cout << endl << ">>> 请输入" << prompt << "，范围[1, " << limit << "]:" << endl;
    while(true)
    {
        cin >> input;
        if(input < 1 || input > limit || cin.fail())
        {
            cerr << endl << ">>> 非法输入，请重新输入！" << endl;
            cin.clear();
            cin.ignore(1024, '\n');
        }
        else
            break;
    }
}

/*
Function Name   : Initialize
Function        : initialize the data
Input Parameters: int& - node_num
                  int& - task_num
                  int**& - cost
                  int*& - indegree
                  int*& - topology_sort
                  int*& - node_min_time
                  int*& - node_max_time
*/
void Initialize(int& node_num, int& task_num, int**& cost, int*& indegree, int*& topology_sort, int*& node_min_time, int*& node_max_time)
{
    InputInt(node_num, KMaxNodeNum, "任务交接点的数量");
    InputInt(task_num, KMaxNodeNum * (KMaxNodeNum - 1) / 2, "子任务的数量");

    cost = new int*[node_num + 1]();
    for(int i = 1; i <= node_num; i++)
        cost[i] = new int[node_num + 1]();
    indegree = new int[node_num + 1]();
    topology_sort = new int[node_num + 1]();
    node_min_time = new int[node_num + 1]();
    node_max_time = new int[node_num + 1]();
    for(int i = 1; i <= node_num; i++)
    {
        node_min_time[i] = -1;
        node_max_time[i] = INT_MAX;
    }

    cout << endl << ">>> 请输入每个任务的起始点、终点和耗时：" << endl;
    for(int i = 1; i <= task_num; i++)
    {
        int start_node, end_node, task_cost;
        cin >> start_node >> end_node >> task_cost;
        cost[start_node][end_node] = task_cost;
        indegree[end_node]++;
    }
}

/*
* Function Name   : TopologySort
* Function        : sort the nodes by topology
* Input Parameters: int - node_num
                    int* - indegree
                    int** - cost
                    int* - topology_sort
*/
void TopologySort(int node_num, int* indegree, int** cost, int* topology_sort)
{
    int*temp = new int[node_num + 1]();
    for(int i = 1; i <= node_num; i++)
        temp[i] = indegree[i];

    my::queue<int> q;
    for(int i = 1; i <= node_num; i++)
        if(temp[i] == 0)
            q.push(i);
    
    int index = 0;
    while(!q.empty())
    {
        int current = q.front();
        q.pop();
        topology_sort[++index] = current;
        for(int i = 1; i <= node_num; i++)
        {
            if(cost[current][i] != 0)
            {
                temp[i]--;
                if(temp[i] == 0)
                    q.push(i);
            }
        }
    }

    if(index != node_num)
    {
        cout << endl << ">>> 无法完成所有任务！" << endl;
        cout << 0 << endl;
        exit(0);
    }
}

/*
* Function Name   : CalculateMinTime
* Function        : calculate the min time of each node
* Input Parameters: int - node_num
                    int* - topology_sort
                    int** - cost
                    int* - node_min_time
*/
void CalculateMinTime(int node_num, int* topology_sort, int** cost, int* node_min_time)
{
    node_min_time[topology_sort[1]] = 0;

    //依次按拓扑排序的正顺计算每个点的最早完成时间
    for(int i = 1; i <= node_num; i++)
    {
        //对当前点，遍历所有可能的后置点（经过了拓扑排序，所以后置点一定在当前点的后面）
        for(int j = i + 1; j <= node_num; j++)
        {
            //如果当前点到后置点有路径
            if(cost[topology_sort[i]][topology_sort[j]] != 0)
            {
                //后置点的最早完成时间 = max(其前置点的最早完成时间+前置点到后置点的耗时) for 前置点 in 所有前置点
                //取max是因为所有前置点都要完成后才能进行后置点
                node_min_time[topology_sort[j]] = Max(node_min_time[topology_sort[j]], node_min_time[topology_sort[i]] + cost[topology_sort[i]][topology_sort[j]]);
            }
        }
    }
}

/*
* Function Name   : CalculateMaxTime
* Function        : calculate the max time of each node
* Input Parameters: int - node_num
                    int* - topology_sort
                    int** - cost
                    int* - node_max_time
                    int* - node_min_time
*/
void CalculateMaxTime(int node_num, int* topology_sort, int** cost, int* node_max_time, int* node_min_time)
{
    node_max_time[topology_sort[1]] = 0;
    node_max_time[topology_sort[node_num]] = node_min_time[topology_sort[node_num]];

    //依次按拓扑排序的逆序计算每个点的最晚完成时间
    for(int i = node_num; i >= 1; i--)
    {
        //对当前点，遍历所有可能的前置点
        for(int j = i - 1; j >= 1; j--)
        {
            //如果当前点到前置点有路径
            if(cost[topology_sort[j]][topology_sort[i]] != 0)
            {
                //前置点的最晚完成时间 = min(其后置点的最晚完成时间-前置点到后置点的耗时) for 后置点 in 所有后置点
                //取min是因为所有前置点的最晚完成时间都取决于当前点的最晚完成时间
                node_max_time[topology_sort[j]] = Min(node_max_time[topology_sort[j]], node_max_time[topology_sort[i]] - cost[topology_sort[j]][topology_sort[i]]);
            }
        }
    }
}

/*
* Function Name   : OutPut
* Function        : output the result
* Input Parameters: int - node_num
                    int** - cost
                    int* - node_min_time
                    int* - node_max_time
*/
void OutPut(int node_num, int** cost, int* node_min_time, int* node_max_time)
{
    cout << endl << ">>> 关键活动为：" << endl;
    for(int i = 1; i <= node_num; i++)
    {
        if(node_min_time[i] != node_max_time[i])
            continue;
        for(int j = node_num; j >= 1; j--)
        {
            if(cost[i][j] != 0 && node_min_time[j] == node_max_time[j])
                cout << i << " -> " << j << endl;
        }
    }
}

int main()
{
    int node_num;
    int task_num;
    int **cost;
    //the indegree of each node
    int *indegree;
    //the topology sort of the nodes
    int *topology_sort;
    int *node_min_time;
    int *node_max_time;

    Initialize(node_num, task_num, cost, indegree, topology_sort, node_min_time, node_max_time);
    TopologySort(node_num, indegree, cost, topology_sort);
    CalculateMinTime(node_num, topology_sort, cost, node_min_time);
    CalculateMaxTime(node_num, topology_sort, cost, node_max_time, node_min_time);
    OutPut(node_num, cost, node_min_time, node_max_time);

    for(int i = 1; i <= node_num; i++)
        delete[] cost[i];
    delete[] cost;
    delete[] indegree;
    delete[] topology_sort;
    delete[] node_min_time;
    delete[] node_max_time;
    return 0;
}