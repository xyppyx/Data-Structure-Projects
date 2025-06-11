/**********************************************
# Project Name : Key_Tasks
# File Name    : Key_Tasks.cpp
# File Function: solve the problem
# Author       : YunPeng Xu(徐云鹏)
# Update Date  : 2024/10/16
**********************************************/

#include<iostream>
#include<climits>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;

namespace my
{

//the base of list
template<typename T>
class List
{//list
    protected://members
        struct LinkNode
        {
            T data;
            LinkNode* next;

            /*
            * Function Name   : LinkNode
            * Function        : constructor of LinkNode
            * Input Parameters: T - value of the node
            */
            LinkNode(const T& value) : data(value), next(nullptr){}
        };

        using LinkNode = struct LinkNode;

        //pointer to head additional node
        LinkNode* m_head;
        //pointer to tail valid node
        LinkNode* m_tail;
        size_t m_size;

    public://external interface
        virtual void push_back(const T& value) = 0;
        virtual void push_front(const T& value) = 0;
        virtual void pop_back() = 0;
        virtual void pop_front() = 0;
        virtual void insert(size_t idx, const T& value) = 0;
        virtual void remove(size_t idx) = 0;

        /*
        * Function Name   : front
        * Return Value    : T - the value of the front node
        */
        virtual T front() const
        {
            if(m_size == 0)
                throw std::out_of_range("The list is empty!");
            else
                return m_head -> next -> data;
        }

        /*
        * Function Name   : back
        * Return Value    : T - the value of the back node
        */
        virtual T back() const
        {
            if(m_size == 0)
                throw std::out_of_range("The list is empty!");
            else
                return m_tail -> data;
        }

        /*
        * Function Name   : display
        * Function        : display the value of the list from head to tail
        */
        void display() const
        {
            if(m_size == 0)
            {
                cerr << "The list is empty!" << endl;
                return;
            }
            LinkNode* current = m_head -> next;
            while(current != m_tail)
            {
                cout<<current -> data<<" ";
                current = current -> next;
            }
            cout<<m_tail -> data<<endl;
        }

        /*
        * Function Name   : search
        * Function        : search the node with the given value
        * Input Parameters: const T& -- value  
        * Return Value    : LinkNode* - the pointer to the node, otherwise nullptr
        */  
        LinkNode* search(const T& value) const
        {
            LinkNode* current = m_head -> next;
            if(current == m_tail)
                return nullptr;
            else if(current -> data == value)
                return current;
            else if(m_tail -> data == value)
                return m_tail;

            while(current != m_tail)
            {
                if(current -> data == value)
                    return current;
                current = current -> next;
            }
            return nullptr;
        }

        /*
        * Function Name   : size
        * Return Value    : size_t - the length of the list
        */
        size_t size() const
        {
            return m_size;
        }

        /*
        * Function Name   : empty
        * Return Value    : bool - true if the list is empty
        */
        bool empty() const
        {
            return m_size == 0;
        }

        /*
        * Function Name   : clear
        * Function        : clear all nodes
        */
        void clear()
        {
            if(m_size != 0)
            {
                LinkNode* current = m_head -> next;
                while(current != m_tail)
                {
                    LinkNode* temp = current;
                    current = temp -> next;
                    delete temp;
                }
                delete m_tail;
            }
            m_head -> next = nullptr;
            m_tail = nullptr;
            m_size = 0;
        }
        
        /*
        * Function Name   : operator[]
        * Function        : overload the [] operator to get the value of the node with subscript idx
        * Input Parameters: size_t - the subscript of the node
        * Return Value    : T - the value of the node
        */
        T& operator[](size_t idx)
        {
            if(idx <= 0 || idx > m_size)
                throw std::out_of_range("Invalid index!");

            LinkNode* current = m_head -> next;
            for(size_t i = 1; i <= m_size; i++)
            {
                if(i == idx)
                    return current -> data;
                else
                    current = current -> next;
            }
            throw std::out_of_range("Invalid index!");
        }

    public://constructor&destructor
        //NOTE : the constructor cannot be virtual

        /*
        * Function Name : constructor
        */
        List() : m_head(new LinkNode(T())), m_tail(nullptr), m_size(0){}

        //TODO : add a copy constructor
        //TODO : add a variadic template constructor
    
        /*
        * Function Name   : destructor
        */
        ~List()
        {
            clear();
        }

    public://iterator
        class iterator
        {
            private://members
                LinkNode* m_ptr;
            
            public://constructor&destuctor
                /*
                * Function Name   : constructor
                */
                iterator() : m_ptr(nullptr) {}

                /*
                * Function Name   : constructor
                */
                iterator(LinkNode* ptr) : m_ptr(ptr) {}
            
            public://external interface
                /*
                * Function Name   : operator*
                * Function        : overload the * operator to get the value of the node
                * Return Value    : T& - the value of the node
                */
                T& operator*() const
                {
                    return m_ptr -> data;
                }

                /*
                * Function Name   : operator->
                * Function        : overload the -> operator to get the pointer of the node
                * Return Value    : LinkNode* - the pointer of the node
                */
                LinkNode* operator->() const
                {
                    return m_ptr;
                }

                /*
                * Function Name   : operator++
                * Function        : overload the ++ operator to move the pointer to the next node
                * Return Value    : iterator& - the pointer to the next node
                */
                virtual iterator& operator++() 
                {
                    if(m_ptr)
                        m_ptr = m_ptr -> next;
                    return *this;
                }

                /*
                * Function Name   : operator++(int)
                * Function        : overload the ++ operator to move the pointer to the next node, and return a copy of the current node
                * Return Value    : iterator - the pointer to the next node
                */
                virtual iterator operator++(int)
                {
                    iterator temp = *this;
                    if(m_ptr)
                        m_ptr = m_ptr -> next;
                    return temp;
                }

                /*
                * Function Name   : operator+(int)
                * Function        : overload the + operator to move the pointer to the next n nodes
                * Input Parameters: int - n
                * Return Value    : iterator - the pointer to the next n nodes
                */
                virtual iterator operator+(int n)
                {
                    iterator temp = *this;
                    for(int i = 1; i <= n && temp.m_ptr != nullptr; i++)
                    {
                        temp.m_ptr = temp.m_ptr -> next;
                    }
                    return temp;
                }
                
                /*
                * Function Name   : operator+=(int)
                * Function        : overload the += operator to move the pointer to the next n nodes
                * Input Parameters: int - n
                * Return Value    : iterator& - the pointer to the next n nodes
                */
                virtual iterator& operator+=(int n)
                {
                    for(int i = 1; i <= n && m_ptr != nullptr; i++)
                    {
                        m_ptr = m_ptr -> next;
                    }
                    return *this;
                }

                /*
                * Function Name   : operator--(prefix)
                * Function        : overload the -- operator to move the pointer to the previous node
                * Return Value    : iterator& - the pointer to the previous node
                */
                bool operator==(const iterator& other) const
                {
                    return m_ptr == other.m_ptr;
                }

                /*
                * Function Name   : operator!=
                * Function        : overload the != operator to compare two pointers
                * Input Parameters: const iterator& - other
                * Return Value    : bool - true if the two pointers are not equal
                */
                bool operator!=(const iterator& other) const
                {
                    return m_ptr != other.m_ptr;
                }

        };

        virtual iterator begin() = 0;
        virtual iterator end() = 0;
};

//single linked list
template<typename T>
class SingleList : public List<T>
{//SingleList
    protected://members
        using List<T>::m_head;
        using List<T>::m_tail;
        using List<T>::m_size;
        using typename List<T>::LinkNode;

    public://constructor&destructor
        //NOTE : xxx = default means (1)using default constructor or destructor
        //                           (2)using its base class's constructor or destructor
        SingleList() = default;

        ~SingleList() = default;

    public://external interface      
        using List<T>::front;
        using List<T>::back;
        using List<T>::search;

        /*
        * Function Name   : push_back
        * Function        : add a node with value given to the last of the list
        * Input Parameters: const T& - the value of the new node
        */      
        void push_back(const T& value) override
        {
            LinkNode* new_node = new LinkNode(value);
            //if the list is empty
            if(m_size == 0)
                m_head -> next = new_node;
            else
                m_tail -> next = new_node;
            m_tail = new_node;
            m_size++;
        }

        /*
        * Function Name   : push_front
        * Function        : add a node with value given to the first of the list
        * Input Parameters: const T& - the value of the new node
        */  
        void push_front(const T& value) override
        {
            LinkNode* new_node = new LinkNode(value);
            //if the list is empty
            if(m_size == 0)
                m_tail = new_node;
            else
                new_node -> next = m_head -> next;
            m_head -> next = new_node;
            m_size++;
        }

        /*
        * Function Name   : pop_back
        * Function        : delete the last node of the list
        */  
        void pop_back() override
        {
            //if the list is empty
            if(m_size == 0)
            {
                cerr << "The list is empty!" << endl;
                return;
            }
            LinkNode* current = m_head;
            while(current -> next != m_tail)
                current = current -> next;
            delete m_tail;
            m_tail = current;
            m_size--;
        }

        /*
        * Function Name   : pop_front
        * Function        : delete the first node of the list
        */
        void pop_front() override
        {
            //if the list is empty
            if(m_size == 0)
            {
                cerr << "The list is empty!" << endl;
                return;
            }
            LinkNode* temp = m_head -> next;
            m_head -> next = temp -> next;
            delete temp;
            m_size--;
        }

        /*
        * Function Name   : insert
        * Function        : insert a new node with value given after the node with subscript idx
        * Input Parameters: size_t - the index of the node for thr new code to insert after
                            cosnt T& - the value of the new node
        */
        void insert(size_t idx, const T& value) override
        {
            if(idx < 0 || idx > m_size)
            {
                cerr << "Invalid index!" << endl;
                return;
            }
            LinkNode* new_node = new LinkNode(value);
            //the node before the new node
            LinkNode* current = m_head;
            for(size_t i = 0; i < idx; i++)
                current = current -> next;
            new_node -> next = current -> next;
            current -> next = new_node;

            //if the new node is the last node
            if(idx == m_size)
                m_tail = new_node;

            m_size++;
        }

        /*
        * Function Name   : remove
        * Function        : remove the node with subscript idx
        * Input Parameters: size_t - the index of the node to remove
        */
        void remove(size_t idx) override
        {
            if(idx <= 0 || idx > m_size)
            {
                cerr << "Invalid index!" << endl;
                return;
            }
            //the node before the removed node
            LinkNode* before_remove = m_head;
            for(size_t i = 1; i < idx; i++)
                before_remove = before_remove -> next;
            LinkNode* to_remove = before_remove -> next;
            before_remove -> next = to_remove -> next;
            delete to_remove;

            //if the removed node is the last node
            if(idx == m_size - 1)
                m_tail = before_remove;

            m_size--;
        }
    
    public://iterator
        using typename List<T>::iterator;

        /*
        * Function Name   : begin
        * Function        : get the iterator to the first node
        * Return Value    : iterator - the iterator to the first node
        */
        iterator begin() override
        {
            return iterator(this -> m_head -> next);
        }

        /*
        * Function Name   : end
        * Function        : get the iterator to the end of the list
        * Return Value    : iterator - the iterator to the end of the list
        */
        iterator end() override
        {
            return iterator(nullptr);
        }
};

//queue
template<typename T>
class queue : public SingleList<T>
{//queue
    protected:
        using typename List<T>::LinkNode;
        using SingleList<T>::m_head;
        using SingleList<T>::m_tail;
        using SingleList<T>::m_size;

    public:
        using SingleList<T>::front;
        using SingleList<T>::clear;
        using SingleList<T>::empty;
        using SingleList<T>::size;
        using SingleList<T>::display;
        using SingleList<T>::push_back;
        void push(const T& value) { push_back(value); }
        using SingleList<T>::pop_front;
        void pop() { pop_front(); }

        /*
        * Function        : constructor
        */
        queue() = default;

        /*
        * Function        : constructor
        */
        ~queue() = default;
};

}

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