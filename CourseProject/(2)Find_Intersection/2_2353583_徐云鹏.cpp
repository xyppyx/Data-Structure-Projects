/**********************************************
# Project Name : Find_Intersection
# File Name    : Find_Intersection.cpp
# File Function: find the intersection of 2 sorted linked lists
# Author       : YunPeng Xu(徐云鹏)
# Update Date  : 2024/9/27
**********************************************/

#include<iostream>

using std::cin;
using std::cout;
using std::endl;
using std::cerr;

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

}

template<typename T>
class FindIntersection
{
    private://members
        my::SingleList<T> list1;
        my::SingleList<T> list2;
        my::SingleList<T> intersection;
        typename my::SingleList<T>::iterator p_list1;
        typename my::SingleList<T>::iterator p_list2;

    public://external interface

        /*
        * Function Name   : Input
        * Function        : input the two linked lists and check the validity of the input
        */
        void Input()
        {
            //input list1
            while(true)
            {
                bool invalid_flag = false;
                cout<<"Please input the first positive integers linked list in non-decreasing order, end with -1:"<<endl;

                //input data
                while(true)
                {
                    int temp;
                    cin >> temp;
                    if(cin.fail())
                    {
                        cin.clear();
                        cin.ignore(1024, '\n');
                        cerr << "Invalid input!" << endl;
                        invalid_flag = true;
                        break;
                    }
                    else if(temp == -1)
                        break;
                    list1.push_back(temp);
                }

                int pre_data = 0, temp_data = 0;
                for(size_t i = 1; i <= list1.size(); i++)
                {
                    temp_data = list1[i];
                    if(temp_data < 0)
                    {
                        cerr << "Invalid negative input!" << endl;
                        invalid_flag = true;
                        break;
                    }
                    else if(temp_data < pre_data)
                    {
                        cerr << "Invalid decreasing input!" << endl;
                        invalid_flag = true;
                        break;
                    }
                    else
                        pre_data = temp_data;
                }

                if(invalid_flag)
                {
                    list1.clear();
                    cerr << "Please input again!" << endl;
                }
                else
                    break; 
            }

            //input list2
            while(true)
            {
                bool invalid_flag = false;
                cout<<"Please input the second positive integers linked list in non-decreasing order, end with -1:"<<endl;

                //input data
                while(true)
                {
                    int temp;
                    cin >> temp;
                    if(cin.fail())
                    {
                        cin.clear();
                        cin.ignore(1024, '\n');
                        cerr << "Invalid input!" << endl;
                        invalid_flag = true;
                        break;
                    }
                    else if(temp == -1)
                        break;
                    list2.push_back(temp);
                }

                int pre_data = 0, temp_data = 0;
                for(size_t i = 1; i <= list2.size(); i++)
                {
                    temp_data = list2[i];
                    if(temp_data < 0)
                    {
                        cerr << "Invalid negative input!" << endl;
                        invalid_flag = true;
                        break;
                    }
                    else if(temp_data < pre_data)
                    {
                        cerr << "Invalid decreasing input!" << endl;
                        invalid_flag = true;
                        break;
                    }
                    else
                        pre_data = temp_data;
                }

                if(invalid_flag)
                {
                    list2.clear();
                    cerr << "Please input again!" << endl;
                }
                else
                    break;
                    
            }
        } 

        /*
        * Function Name   : Solve
        * Function        : solve the problem
        */
        void Solve()
        {
            Input();
            p_list1 = list1.begin();
            p_list2 = list2.begin();

            //exist empty list 
            if(p_list1 == list1.end() || p_list2 == list2.end())
            {
                cout << endl << "NULL" << endl;
                return;
            }

            //find the intersection
            while(p_list1 != list1.end() && p_list2 != list2.end())
            {
                if(*p_list1 == *p_list2)
                {
                    intersection.push_back(*p_list1);
                    p_list1++;
                    p_list2++;
                }
                else if(*p_list1 < *p_list2)
                    p_list1++;
                else
                    p_list2++;
            }

            //output the intersection
            if(intersection.empty())
                cout << endl << "NULL" << endl;
            else
            {
                cout << endl << "The intersection is:" << endl;
                for(auto it = intersection.begin(); it != intersection.end(); it++)
                    cout << *it << " ";
                cout << endl;
            }
        }
};

signed main()
{
    FindIntersection<int> solution;
    solution.Solve();
    return 0;
}