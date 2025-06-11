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

//stack
template<typename T>
class stack : public SingleList<T>
{//stack
    protected:
        //using members of the base class — MyList->SingleList
        using typename List<T>::LinkNode;
        using SingleList<T>::m_head;
        using SingleList<T>::m_size;
        using SingleList<T>::push_front;
        using SingleList<T>::pop_front;

    public:
        /*
        * Function        : constructor
        */
        stack() = default;

        /*
        * Function        : destructor
        */
        ~stack() = default;

        using SingleList<T>::front;
        using SingleList<T>::clear;
        using SingleList<T>::empty;
        using SingleList<T>::size;
        using SingleList<T>::display;

        /*
        * Function Name   : push
        * Function        : using push_front as push
                            add a node with value given to the top of the stack
        * Input Parameters: const T& - the value of the new node
        */
        void push(const T& value)
        {
            push_front(value);
        }

        /*
        * Function Name   : pop
        * Function        : using pop_front as pop
                            delete the top node of the stack
        */
        void pop()
        {
            pop_front();
        }

        /*
        * Function Name   : top
        * Function        : get the top element of the stack
        * Return Value    : const T - the top element of the stack
        */
        const T top() const
        {
            return front();
        }
};

//vector
template <typename T>
class vector 
{//vector
    private://members
        size_t m_size;
        size_t m_capacity;
        T* m_data;

    public://consructor & destructor
        vector() : m_size(0), m_capacity(1), m_data(new T[1]) {}

        vector(size_t size) : m_size(size), m_capacity(size), m_data(new T[size]) {}

        vector(size_t size, const T& value) : m_size(size), m_capacity(size), m_data(new T[size]) 
        {
            for (size_t i = 0; i < size; ++i) 
                m_data[i] = value;
        }

        vector(const vector<T>& other) : m_size(other.m_size), m_capacity(other.m_capacity), m_data(new T[other.m_capacity]) 
        {
            for (size_t i = 0; i < m_size; ++i) 
                m_data[i] = other.m_data[i];
        }

        ~vector() 
        {
            delete[] m_data;
        }

    public://external interface
        /*
        * Function Name   : resize
        * Function        : resize the vector, copy the old data to the new data, delete the old data, and double the capacity
        * Input Parameters: size_t - new_capacity
        */
        void resize(size_t new_capacity) 
        {
            T* new_data = new T[new_capacity];
            //copy [m_data, m_data + m_size) to new_data
            for (size_t i = 0; i < m_size; ++i) {
                new_data[i] = m_data[i];
            }
            delete[] m_data;
            m_data = new_data;
            m_capacity = new_capacity;
        }

        
        void resize(size_t new_capacity, const T& value)
        {
            if (new_capacity <= m_size) 
            {
                m_size = new_capacity;
                for (size_t i = 0; i < new_capacity; ++i)
                    m_data[i] = value;
            }
            else if (new_capacity > m_capacity)
            {
                T* new_data = new T[new_capacity];
                for (size_t i = 0; i < m_size; ++i)
                    new_data[i] = m_data[i];
                delete[] m_data;
                m_data = new_data;
                m_capacity = new_capacity;
                for (size_t i = m_size; i < new_capacity; ++i)
                    new_data[i] = value;
                m_size = new_capacity;
            }
        }
        
        /*
        * Function Name   : push_back
        * Function        : add a new element to the end of the vector
        * Input Parameters: const T& - the value of the new element
        */
        void push_back(const T& value) 
        {
            if (m_size == m_capacity) 
            {
                resize(m_capacity * 2);
            }
            m_data[m_size++] = value;
        }

        /*
        * Function Name   : pop_back
        * Function        : delete the last element of the vector
        */
        void pop_back() 
        {
            if (m_size > 0) 
            {
                --m_size;
            }
        }

        /*
        * Function Name   : size
        * Function        : get the size of the vector
        * Return Value    : size_t - the size of the vector
        */
        size_t size() const 
        {
            return m_size;
        }

        /*
        * Function Name   : capacity
        * Function        : get the capacity of the vector
        * Return Value    : size_t - the capacity of the vector
        */
        size_t capacity() const 
        {
            return m_capacity;
        }

        /*
        * Function Name   : empty
        * Function        : check if the vector is empty
        * Return Value    : bool - true if the vector is empty, false otherwise
        */
        bool empty() const 
        {
            return m_size == 0;
        }

        /*
        * Function Name   : clear
        * Function        : clear the vector
        */
        void clear() 
        {
            m_size = 0;
        }

        /*
        * Function Name   : front
        * Function        : get the first element of the vector
        * Return Value    : T& - the first element of the vector
        */
        const T& front() const 
        {
            if (m_size == 0) 
            {
                cerr <<"Vector is empty" <<endl;
            }
            return m_data[0];
        }

        /*
        * Function Name   : back
        * Function        : get the last element of the vector
        * Return Value    : T& - the last element of the vector
        */
        const T& back() const 
        {
            if (m_size == 0) 
            {
                cerr <<"Vector is empty" <<endl;
            }
            return m_data[m_size - 1];
        }

        /*
        * Function Name   : erase
        * Function        : delete the element at the index given
        * Input Parameters: size_t - the index of the element to delete
        */
        void erase(size_t idx)
        {
            if(idx >= m_size)
            {
                cerr << "Out of range!" << endl;
                return;
            }

            --m_size;
            for(size_t i = idx; i < m_size; i++)
                m_data[i] = m_data[i + 1];
        }

        /*
        * Function Name   : erase
        * Function        : delete the elements in the range of [begin, end)
        * Input Parameters: size_t - the begin of the range
                            size_t - the end of the range
        */
        void erase(size_t begin, size_t end)
        {
            if(begin >= m_size || end > m_size || begin > end)
            {
                cerr << "Out of range!" << endl;
                return;
            }

            m_size -= end - begin;
            for(size_t i = begin; i < m_size; i++)
                m_data[i] = m_data[i + end - begin];
        }
    
    public://operator
        /*
        * Function Name   : operator[]
        * Function        : overload the [] operator to get the element at the index given(from 0 to m_size - 1)
        * Input Parameters: size_t - index
        * Return Value    : T& - the element at the index given
        */
        T& operator[](size_t index) 
        {
            if (index >= m_size) 
            {
                cerr <<"Index out of range" <<endl;
            }
            return m_data[index];
        }

        /*
        * Function Name   : operator[]
        * Function        : overload the [] operator to get the element at the index given(from 0 to m_size - 1)
        * Input Parameters: size_t - index
        * Return Value    : const T& - the element at the index given
        */
        const T& operator[](size_t index) const 
        {
            if (index >= m_size) 
            {
                cerr <<"Index out of range" <<endl;
            }
            return m_data[index];
        }

        /*
        * Function Name   : operator=
        * Function        : overload the = operator to copy the vector
        * Input Parameters: const vector<T>& - the vector to copy
        * Return Value    : vector& - the vector copied
        */
        vector& operator=(const vector<T>& other) 
        {
            if (this != &other) {
                delete[] m_data; // 先释放旧内存
                m_size = other.m_size;
                m_capacity = other.m_capacity;
                m_data = new T[m_capacity];
                for (size_t i = 0; i < m_size; ++i) 
                    m_data[i] = other.m_data[i];
            }
            return *this;
        }
    
    public://class-iterator
        class iterator
        {
            public://members
                enum class Direction{forward, backward};

            private://members
                T* m_ptr;
                T* m_begin;
                T* m_end;
                Direction m_dir;
            
            public://constructor
                /*
                * Function Name   : constructor
                * Function        : assure the pointer is in the range of [begin, end)
                * Input Parameters: T* - the pointer
                                    T* - the begin of the range 
                                    T* - the end of the range
                */
                iterator(T* ptr, T* begin, T* end, iterator::Direction dir) : m_ptr(ptr), m_begin(begin), m_end(end), m_dir(dir){}

            public://external interface
                /*
                * Function Name   : operator*
                * Function        : overload the * operator to get the value of the element
                * Return Value    : T& - the value
                */
                T& operator*() const
                {
                    return *m_ptr;
                }

                /*
                * Function Name   : operator->
                * Function        : overload the -> operator to get the pointer of the element
                * Return Value    : T* - the pointer
                */
                T* operator->() const
                {
                    return m_ptr;
                }

                /*
                * Function Name   : operator++(prefix)
                * Function        : overload the ++ operator to move the pointer to the next element
                * Return Value    : iterator& - the pointer to the next element
                */
                iterator& operator++()
                {
                    if(m_dir == Direction::forward)
                        m_ptr++;
                    else
                        m_ptr--;

                    return *this;
                }

                /*
                * Function Name   : operator++(postfix)
                * Function        : overload the ++ operator to move the pointer to the next element, and return a copy of the current element
                * Return Value    : iterator - the pointer to the next element
                */
                iterator operator++(int)
                {
                    iterator temp = *this;
                    if(m_dir == Direction::forward)
                        m_ptr++;
                    else
                        m_ptr--;

                    return temp;
                }

                /*
                * Function Name   : operator+(int)
                * Function        : overload the + operator to move the pointer to the next n elements
                * Input Parameters: int - n
                * Return Value    : iterator - the pointer to the next n elements
                */
                iterator operator+(int n) const
                {
                    T* new_ptr;
                    if(m_dir == Direction::forward)
                        new_ptr = m_ptr + n;
                    else
                        new_ptr = m_ptr - n;
                    return iterator(new_ptr, m_begin, m_end, m_dir);
                }
                
                /*
                * Function Name   : operator+=(int)
                * Function        : overload the += operator to move the pointer to the next n elements
                * Input Parameters: int - n
                * Return Value    : iterator& - the pointer to the next n elements
                */
                iterator& operator+=(int n)
                {
                    if(m_dir == Direction::forward)
                        m_ptr = m_ptr + n;
                    else
                        m_ptr = m_ptr - n;

                    return *this;
                }

                /*
                * Function Name   : operator--(prefix)
                * Function        : overload the -- operator to move the pointer to the previous element
                * Return Value    : iterator& - the pointer to the previous element
                */
                iterator& operator--()
                {
                    if(m_dir == Direction::forward)
                        m_ptr--;
                    else
                        m_ptr++;

                    return *this;
                }

                /*
                * Function Name   : operator--(postfix)
                * Function        : overload the -- operator to move the pointer to the previous element, and return a copy of the current element
                * Return Value    : iterator - the pointer to the previous element
                */
                iterator operator--(int)
                {
                    iterator temp = *this;
                    if(m_dir == Direction::forward)
                        m_ptr--;
                    else
                        m_ptr++;

                    return temp;
                }

                /*
                * Function Name   : operator-(int)
                * Function        : overload the - operator to move the pointer to the previous n elements
                * Input Parameters: int - n
                * Return Value    : iterator - the pointer to the previous n elements
                */
                iterator operator-(int n) const
                {
                    T* new_ptr;
                    if(m_dir == Direction::forward)
                        new_ptr = m_ptr - n;
                    else
                        new_ptr = m_ptr + n;
                    return iterator(new_ptr, m_begin, m_end, m_dir);

                    return *this;
                }

                /*
                * Function Name   : operator-=(int)
                * Function        : overload the -= operator to move the pointer to the previous n elements
                * Input Parameters: int - n
                * Return Value    : iterator& - the pointer to the previous n elements
                */
                iterator& operator-=(int n)
                {
                    if(m_dir == Direction::forward)
                        m_ptr = m_ptr - n;
                    else
                        m_ptr = m_ptr + n;

                    return *this;
                }

                /*
                * Function Name   : operator==
                * Function        : overload the == operator to compare two pointers
                * Input Parameters: const iterator& - other
                * Return Value    : bool - true if the two pointers are equal
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

                /*
                * Function Name   : operator<
                * Function        : overload the < operator to compare two pointers
                * Input Parameters: const iterator& - other
                * Return Value    : bool - true if the current pointer is less than the other pointer
                */
                bool operator<(const iterator& other) const
                {
                    if(m_dir == Direction::forward)
                        return m_ptr < other.m_ptr;
                    else
                        return m_ptr > other.m_ptr;
                }

                /*
                * Function Name   : operator>
                * Function        : overload the > operator to compare two pointers
                * Input Parameters: const iterator& - other
                * Return Value    : bool - true if the current pointer is greater than the other pointer
                */
                bool operator>(const iterator& other) const
                {
                    if(m_dir == Direction::forward)
                        return m_ptr > other.m_ptr;
                    else
                        return m_ptr < other.m_ptr;
                }

                /*
                * Function Name   : operator<=
                * Function        : overload the <= operator to compare two pointers
                * Input Parameters: const iterator& - other
                * Return Value    : bool - true if the current pointer is less than or equal to the other pointer
                */
                bool operator<=(const iterator& other) const
                {
                    if(m_dir == Direction::forward)
                        return m_ptr <= other.m_ptr;
                    else
                        return m_ptr >= other.m_ptr;
                }

                /*
                * Function Name   : operator>=
                * Function        : overload the >= operator to compare two pointers
                * Input Parameters: const iterator& - other
                * Return Value    : bool - true if the current pointer is greater than or equal to the other pointer
                */
                bool operator>=(const iterator& other) const
                {
                    if(m_dir == Direction::forward)
                        return m_ptr >= other.m_ptr;
                    else
                        return m_ptr <= other.m_ptr;
                }
        };

        //the begin of the vector
        iterator begin()
        {
            return iterator(m_data, m_data, m_data + m_size, iterator::Direction::forward);
        }

        //the end of the vector
        iterator end()
        {
            return iterator(m_data + m_size, m_data, m_data + m_size, iterator::Direction::forward);
        }

        //the reverse begin of the vector
        iterator rbegin()
        {
            return iterator(m_data + m_size - 1, m_data, m_data + m_size, iterator::Direction::backward);
        }

        //the reverse end of the vector
        iterator rend()
        {
            return iterator(m_data - 1, m_data, m_data + m_size, iterator::Direction::backward);
        }
};

}

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

            bool dir_used[4] = {false};
            for (int i = 0; i < 4; i++) 
            {
                int dir = rand() % 4;
                if (dir_used[dir]) 
                {
                    i--;
                    continue;
                }
                dir_used[dir] = true;
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