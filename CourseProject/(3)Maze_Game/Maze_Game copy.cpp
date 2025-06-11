/**********************************************
# Project Name : Maze_Game
# File Name    : Maze_Game.cpp
# File Function: solve the maze by Dfs, Bfs, Bidirectional Bfs and A* algorithm
# Author       : YunPeng Xu(徐云鹏)
# Update Date  : 2024/10/13
**********************************************/

#include<iostream>
#include<ctime>
#include<climits>
#include<windows.h>
#include"MyDataStructure.h"

using std::cin;
using std::cout;
using std::endl;
using std::cerr;

class Maze
{
    private://members
        static const int KMaxSize = 250;
        const int m_dx[4] = {0, 1, 0, -1};
        const int m_dy[4] = {1, 0, -1, 0};
        int m_row, m_col;
        bool m_random_maze;

        enum class Condition{visited, backward_visited, not_visited};
        enum class Type{wall, road, path, backward_path, unknown};
        struct Node
        {
            int x, y;
            int distance;
            Condition condition = Condition::not_visited;
            Type type = Type::wall;

            Node() : x(0), y(0), distance(INT_MIN), condition(Condition::not_visited), type(Type::unknown) {}
            Node(int new_x, int new_y) : x(new_x), y(new_y), distance(INT_MIN), condition(Condition::not_visited), type(Type::unknown) {}
            Node(int new_x, int new_y, Type new_type) : x(new_x), y(new_y), distance(INT_MIN), condition(Condition::not_visited), type(new_type) {}
        };

        my::vector<my::vector<Node*>> m_maze;

    private://internal functions - Input & Output
        /*
        * Function Name   : InputInt
        * Function        : input a int in the range of [0, limits] and check the validation
        * Input Parameters: int& - number
                            const int - limits
                            const char* - prompt
        */
        void InputInt(int& number, const int limits, const char* prompt)
        {
            cout << endl << ">>> 请输入" << prompt << "，范围[0 - " << limits << "]：" << endl;
            while(true)
            {
                cin>>number;
                if(cin.fail() || number < 0 || number > limits)
                {
                    cout << endl << ">>> 输入不合法，请重新输入！" << endl;
                    cin.clear();
                    cin.ignore(1024, '\n');
                }
                else
                    break;
            }
        }

        /*
        * Function Name   : InputBool
        * Function        : input a bool and check the validation
        * Input Parameters: bool& - number
                            const char* - prompt
        */
        void InputBool(bool& number, const char* prompt)
        {
            cout << endl << ">>> " << prompt << endl;
            while(true)
            {
                cin>>number;
                if(cin.fail() || number < 0 || number > 1)
                {
                    cout << endl << ">>> 输入不合法，请重新输入！" << endl;
                    cin.clear();
                    cin.ignore(1024, '\n');
                }
                else
                    break;
            }
        }

        /*
        * Function Name   : DisplayMaze
        * Function        : display the maze
        */
        void DisplayMaze()
        {
            cout << endl << ">>> 迷宫地图：" << endl;
            for(int i = 0; i <= m_row + 1; i++)
            {
                for(int j = 0; j <= m_col + 1; j++)
                {
                    if(i == 1 && j == 1)
                    {
                        cout<<"起";
                        continue;
                    }
                    else if(i == m_row && j == m_col)
                    {
                        cout<<"终";
                        continue;
                    }
                    else if(m_maze[i][j] -> type == Type::wall)
                        cout << "██";
                    else if(m_maze[i][j] -> type == Type::road)
                        cout << "  ";
                    else if(m_maze[i][j] -> type == Type::path)
                    {
                        setColor(FOREGROUND_INTENSITY | FOREGROUND_RED); 
                        cout << "██";
                        setColor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    }
                    else if(m_maze[i][j] -> type == Type::backward_path)
                    {
                        setColor(FOREGROUND_INTENSITY | FOREGROUND_GREEN);
                        cout << "██";
                        setColor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    }
                        
                }
                cout<<endl;
            }
        }

    private://internal functions - algorithm
        /*
        * Function Name   : DFS
        * Function        : solve the maze by DFS algorithm
        */
        void DFS()
        {
            Node* parent[KMaxSize + 2][KMaxSize + 2] = {nullptr};
            my::stack<Node*> Nodes;
            my::stack<Node*> Path;

            Nodes.push(m_maze[1][1]);
            m_maze[1][1] -> condition = Condition::visited;
            m_maze[1][1] -> distance = 0;
            parent[1][1] = nullptr;

            while(!Nodes.empty())
            {
                Node* current = Nodes.top();
                Nodes.pop();

                for(int i = 0; i < 4; i++)
                {
                    int new_x = current -> x + m_dx[i];
                    int new_y = current -> y + m_dy[i];
                    if(!(1 <= new_x && new_x <= m_row && 1 <= new_y && new_y <= m_col) 
                    || m_maze[new_x][new_y] -> condition == Condition::visited 
                    || m_maze[new_x][new_y] -> type == Type::wall)
                        continue;
                        
                    Nodes.push(m_maze[new_x][new_y]);
                    m_maze[new_x][new_y] -> condition = Condition::visited;
                    m_maze[new_x][new_y] -> distance = current -> distance + 1;
                    parent[new_x][new_y] = current; 
                }

                if(m_maze[m_row][m_col] -> condition == Condition::visited)
                    break;
            }

            int cur_x = m_row, cur_y = m_col;
            while(parent[cur_x][cur_y] != nullptr)
            {
                Path.push(parent[cur_x][cur_y]);
                Node* temp = parent[cur_x][cur_y];
                cur_x = temp -> x;
                cur_y = temp -> y;
                
            }

            cout << endl << ">>> DFS求解结果为：" << endl;
            while(!Path.empty())
            {
                cout << "(" << Path.top() -> x << "," << Path.top() -> y << ") --> ";
                m_maze[Path.top() -> x][Path.top() -> y] -> type = Type::path;
                Path.pop();
            }
            cout << "(" << m_row << "," << m_col << ")";
            cout << endl << ">>> 所用步数为：" << m_maze[m_row][m_col] -> distance << endl;

            DisplayMaze();
            RenewMaze();
        }

        /*
        * Function Name   : BFS
        * Function        : solve the maze by BFS algorithm
        */
        void BFS()
        {
            Node* parent[KMaxSize + 2][KMaxSize + 2] = {nullptr};
            my::queue<Node*> Nodes;
            my::stack<Node*> Path;

            Nodes.push(m_maze[1][1]);
            m_maze[1][1] -> condition = Condition::visited;
            m_maze[1][1] -> distance = 0;
            parent[1][1] = nullptr;

            while(!Nodes.empty())
            {
                Node* current = Nodes.front();
                Nodes.pop();

                for(int i = 0; i < 4; i++)
                {
                    int new_x = current -> x + m_dx[i];
                    int new_y = current -> y + m_dy[i];
                    if(!(1 <= new_x && new_x <= m_row && 1 <= new_y && new_y <= m_col) 
                    || m_maze[new_x][new_y] -> condition == Condition::visited 
                    || m_maze[new_x][new_y] -> type == Type::wall)
                        continue;
                        
                    Nodes.push(m_maze[new_x][new_y]);
                    m_maze[new_x][new_y] -> condition = Condition::visited;
                    m_maze[new_x][new_y] -> distance = current -> distance + 1;
                    parent[new_x][new_y] = current; 
                }

                if(m_maze[m_row][m_col] -> condition == Condition::visited)
                    break;
            }

            int cur_x = m_row, cur_y = m_col;
            while(parent[cur_x][cur_y] != nullptr)
            {
                Path.push(parent[cur_x][cur_y]);
                Node* temp = parent[cur_x][cur_y];
                cur_x = temp -> x;
                cur_y = temp -> y;
                
            }

            cout << endl << ">>> BFS求解结果为：" << endl;
            while(!Path.empty())
            {
                cout << "(" << Path.top() -> x << "," << Path.top() -> y << ") --> ";
                m_maze[Path.top() -> x][Path.top() -> y] -> type = Type::path;
                Path.pop();
            }
            cout << "(" << m_row << "," << m_col << ")";
            cout << endl << ">>> 所用步数为：" << m_maze[m_row][m_col] -> distance << endl;

            DisplayMaze();
            RenewMaze();
        }   

        /*
        * Function Name   : BidirectionalBFS
        * Function        : solve the maze by Bidirectional BFS algorithm
        */
        void BidirectionalBFS()
        {
            my::queue<Node*> forward;
            my::queue<Node*> backward;
            my::stack<Node*> path;
            Node* parent[KMaxSize + 2][KMaxSize + 2] = {nullptr};
            Node* forward_ans = nullptr;
            Node* backward_ans = nullptr;
            int used_step = 0;
            bool end_flag = 0;

            forward.push(m_maze[1][1]);
            backward.push(m_maze[m_row][m_col]);
            m_maze[1][1] -> condition = Condition::visited;
            m_maze[m_row][m_col] -> condition = Condition::backward_visited;
            m_maze[1][1] -> distance = 0;
            m_maze[m_row][m_col] -> distance = 0;
            parent[1][1] = nullptr;
            parent[m_row][m_col] = nullptr;

            while(!forward.empty() && !backward.empty())
            {
                Node* forward_current = forward.front();
                forward.pop();
                for(int i = 0; i < 4; i++)
                {
                    int new_x = forward_current -> x + m_dx[i];
                    int new_y = forward_current -> y + m_dy[i];
                    if(!(1 <= new_x && new_x <= m_row && 1 <= new_y && new_y <= m_col)
                    || m_maze[new_x][new_y] -> condition == Condition::visited
                    || m_maze[new_x][new_y] -> type == Type::wall)
                    continue;
                    
                    if(m_maze[new_x][new_y] -> condition == Condition::backward_visited)
                    {
                        end_flag = 1;
                        backward_ans = m_maze[new_x][new_y];
                        forward_ans = forward_current;
                        break;
                    }
                    else
                    {
                        parent[new_x][new_y] = forward_current;
                        m_maze[new_x][new_y] -> condition = Condition::visited;
                        m_maze[new_x][new_y] -> distance = forward_current -> distance + 1;
                        forward.push(m_maze[new_x][new_y]);
                    }
                }
                if(end_flag)
                    break;

                Node* backward_current = backward.front();
                backward.pop();
                for(int i = 0; i < 4; i++)
                {
                    int new_x = backward_current -> x + m_dx[i];
                    int new_y = backward_current -> y + m_dy[i];
                    if(!(1 <= new_x && new_x <= m_row && 1 <= new_y && new_y <= m_col)
                    || m_maze[new_x][new_y] -> condition == Condition::backward_visited
                    || m_maze[new_x][new_y] -> type == Type::wall)
                    continue;
                    
                    if(m_maze[new_x][new_y] -> condition == Condition::visited)
                    {
                        end_flag = 1;
                        forward_ans = m_maze[new_x][new_y];
                        backward_ans = backward_current;
                        break;
                    }
                    else
                    {
                        parent[new_x][new_y] = backward_current;
                        m_maze[new_x][new_y] -> condition = Condition::backward_visited;
                        m_maze[new_x][new_y] -> distance = backward_current -> distance + 1;
                        backward.push(m_maze[new_x][new_y]);
                    }
                }
                if(end_flag)
                    break;
            }

            cout << endl << ">>> 双向BFS求解结果为：" << endl;
            used_step = forward_ans -> distance + backward_ans -> distance + 1;

            while(forward_ans != nullptr)
            {
                int x = forward_ans -> x, y = forward_ans -> y;
                m_maze[x][y] -> type = Type::path;
                path.push(forward_ans);
                forward_ans = parent[x][y];
            }

            while(!path.empty())
            {
                int x = path.top() -> x, y = path.top() -> y;
                cout << "(" << x << "," << y << ") --> ";
                path.pop();
            }

            while(!(backward_ans -> x == m_row && backward_ans -> y == m_col))
            {
                int x = backward_ans -> x, y = backward_ans -> y;
                m_maze[x][y] -> type = Type::backward_path;
                backward_ans = parent[x][y];
                cout << "(" << x << "," << y << ") --> ";
            }
            cout << "(" << m_row << "," << m_col << ")";
            cout << endl << ">>> 所用步数：" << used_step << endl;

            DisplayMaze();
            RenewMaze();
        }

        /*
        * Function Name   : GenerateMaze
        * Function        : generate the maze by DFS 
        * Input Parameters: int - start -> x
                            int - start -> y
        */
        void GenerateMaze(int x, int y)
        {
            static bool is_first = true;
            if(is_first)
            {
                m_maze.resize(m_row + 2, my::vector<Node*>(m_col + 2, nullptr));
                srand(static_cast<unsigned>(time(0)));

                for (int i = 0; i <= m_row + 1; i++)
                    for (int j = 0; j <= m_col + 1; j++)
                        m_maze[i][j] = new Node(i, j, Type::wall);

                m_maze[1][1] -> type = Type::road;

                is_first = false;
            }
            m_maze[x][y] -> type = Type::road;

            bool die_used[4] = {false};
            for (int i = 0; i < 4; i++) 
            {
                int dir = rand() % 4;
                if (die_used[dir]) 
                {
                    i--;
                    continue;
                }
                die_used[dir] = true;
                int new_x = x + 2 * m_dx[dir];
                int new_y = y + 2 * m_dy[dir];
                if (new_x >= 1 && new_x <= m_row && new_y >= 1 && new_y <= m_col && m_maze[new_x][new_y] -> type == Type::wall) {
                    m_maze[x + m_dx[dir]][y + m_dy[dir]] -> type = Type::road;
                    GenerateMaze(new_x, new_y);
                }
            }
        }

    private://internal functions - others
        //set the color of the console
        void setColor(WORD color) 
        {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, color);
        }

        /*
        * Function Name   : InitializeMaze
        * Function        : used the default maze
        */
        void InitializeMaze()
        {
            m_row = 5;
            m_col = 5;
            m_maze.resize(m_row + 2, my::vector<Node*>(m_col + 2, nullptr));
            //1st col
            for(int i = 1; i <= 5; i++)m_maze[i][1] = new Node(i, 1, Type::road);
            //2nd col
            m_maze[3][2] = new Node(3, 2, Type::road);
            //3rd col
            for(int i = 1; i <= 5; i++)m_maze[i][3] = new Node(i, 3, Type::road);
            //4th col
            m_maze[1][4] = new Node(1, 4, Type::road);
            m_maze[4][4] = new Node(4, 4, Type::road);
            //5th col
            for(int i = 1; i <= 5; i++)m_maze[i][5] = new Node(i, 5, Type::road);

            m_maze[2][5] = new Node(1, 1, Type::wall);
            for(int i = 0; i <= 6; i++)
                for(int j = 0; j <= 6; j++)
                    if(m_maze[i][j] == nullptr)
                        m_maze[i][j] = new Node(i, j, Type::wall);
        }

        /*
        * Function Name   : RenewMaze
        * Function        : renew the maze[i][j] -> condition
        */
        void RenewMaze()
        {
            for(int i = 1; i <= m_row; i++)
                for(int j = 1; j <= m_col; j++)
                    m_maze[i][j] -> condition = Condition::not_visited;

        }

    public://external interface
        /*
        * Function Name   : Launch
        * Function        : launch the maze game
        */
        void Launch()
        {
            InputBool(m_random_maze, "请选择是否使用随机迷宫(0：不使用；1：使用)：");
            if(m_random_maze)
            {
                InputInt(m_row, KMaxSize, "迷宫的行数(请确保为奇数)");
                InputInt(m_col, KMaxSize, "迷宫的列数(请确保为奇数)");
                GenerateMaze(1, 1);
            }
            else
                InitializeMaze();
            DisplayMaze();

            while(true)
            {
                int opt;
                InputInt(opt, 3, "求解迷宫的算法(0:退出 1:深搜 2:广搜 3:双向广搜)：");
                switch(opt)
                {
                    case 0:
                        return;
                    case 1:
                        DFS();
                        break;
                    case 2:
                        BFS();
                        break;
                    case 3:
                        BidirectionalBFS();
                        break;
                    default:
                        break;
                }
            }
        }
};

int main()
{
    cout << ">>> Please use UTF-8 encoding to ensure the normal operation of the program" << endl;
    Maze maze;
    maze.Launch();
    return 0;
}