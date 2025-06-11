#include <iostream>
#include <cstring>

using std::cin;
using std::cout;
using std::endl;

class MinimumSpanningTree 
{
    private:
        int vertex;
        int** graph;
        int* parent;
        int* key;
        bool* mst_set;

    public:
        MinimumSpanningTree(int v)
        {
            vertex = v;
            graph = new int* [vertex];
            for (int i = 0; i < vertex; i++) 
                graph[i] = new int[vertex];
            for (int i = 0; i < vertex; i++)
                for (int j = 0; j < vertex; j++)
                    graph[i][j] = 0;

            parent = new int[vertex];
            key = new int[vertex];
            mst_set = new bool[vertex];
        }

        ~MinimumSpanningTree()
        {
            for (int i = 0; i < vertex; i++)
                delete[] graph[i];
            delete[] graph;
            delete[] parent;
            delete[] key;
            delete[] mst_set;
        }

        int MinKey()
        {
            int minVal = 0x7f7f7f7f, minIndex = -1;
            for (int i = 0; i < vertex; i++) 
            {
                if (!mst_set[i] && key[i] < minVal) 
                {
                    minVal = key[i];
                    minIndex = i;
                }
            }
            return minIndex;
        }

        void Print(int start_vertex)
        {
            for (int i = start_vertex + 1; i < vertex + start_vertex; i++)
                cout << char(parent[i % vertex] + 'A') << " --(" << graph[i % vertex][parent[i % vertex]] << ")--> " << char(i % vertex + 'A') << endl;
        }

        void Prim(int start_vertex)
        {
            for (int i = 0; i < vertex; i++) 
            {
                key[i] = 0x7f7f7f7f;
                mst_set[i] = false;
            }

            key[start_vertex] = 0;
            parent[start_vertex] = -1;

            for (int count = 0; count < vertex; count++) 
            {
                int u = MinKey();
                mst_set[u] = true;
                for (int v = 0; v < vertex; v++)
                    if (graph[u][v] && !mst_set[v] && graph[u][v] < key[v]) 
                    {
                        parent[v] = u;
                        key[v] = graph[u][v];
                    }
            }

            Print(start_vertex);
        }

        void SetWeight(int a, int b, int w)
        {
            if(w == 0)
                return;
            graph[a][b] = w;
            graph[b][a] = w;
        }
};

int InputInteger(int lower_limit, int upper_limit, const char* prompt)
{
    while (true) 
    {
        cout << "请输入" << prompt << " [整数范围: " << lower_limit << "~" << upper_limit << "]: ";
        double temp;
        cin >> temp;
        if (cin.good() && temp == int(temp) && temp >= lower_limit && temp <= upper_limit) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            return int(temp);
        }
        else {
            std::cerr << endl << ">>> " << prompt << ">>> 非法输入，请重新输入" << prompt << "！" << endl << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
    }
}

int InputStartVertex(int vertex)
{
    cout << endl << "请输入初始节点 [输入范围: A~" << char(vertex + 'A' - 1) << "]: ";
    char op;
    while (true) 
    {
        op = getchar();
        if (op == 0 || op == -32) 
        {
            op = getchar();
        }
        else if (op >= 'A' && op <= vertex + 'A' - 1) 
        {
            cout << op << endl << endl;
            return op - 'A';
        }
    }
}

signed main()
{
    cout << "+--------------------------------------------------+" << endl;
    cout << "|               电网建设造价模拟系统               |" << endl;
    cout << "|  Power Grid Construction Cost Simulation System  |" << endl;
    cout << "+--------------------------------------------------+" << endl;

    cout << endl << ">>> 请创建电网" << endl << endl;
    int vertex = InputInteger(2, 'Z' - 'A' + 1, "电网节点个数");
    MinimumSpanningTree MST(vertex);
    cout << endl << ">>> 电网节点 A";
    for (int i = 1; i < vertex; i++)
        cout << "、" << char(i + 'A');
    cout << " 创建成功" << endl;

    cout << endl << ">>> 请输入任意两个电网节点之间的距离(0代表两点间不存在边)" << endl << endl;
    for (int i = 0; i < vertex; i++)
        for (int j = i + 1; j < vertex; j++) 
        {
            char tmp[64];
            sprintf(tmp, "电网节点 %c 和 %c 之间的距离", i + 'A', j + 'A');
            MST.SetWeight(i, j, InputInteger(0, SHRT_MAX, tmp));
        }

    int start_vertex = InputStartVertex(vertex);
    cout << ">>> 建立 Prim 最小生成树:" << endl << endl;
    MST.Prim(start_vertex);

    cout << endl << ">>> 按回车键退出" << endl;
    while (getchar() != '\n');
    while (getchar() != '\n');
    return 0;
}