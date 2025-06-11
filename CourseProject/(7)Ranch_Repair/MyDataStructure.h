/**********************************************
# Project Name : MyHeaderFile
# File Name    : MyDataStructure.h
# File Function: provide my own data structor, including vector, queue, stack, list, map, heap, etc.
# Author       : YunPeng Xu(徐云鹏)
# Update Date  : 2024/10/9
**********************************************/

#pragma once
#include<iostream>
#include<cstring>

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

//deque
template<typename T>
class deque : public SingleList<T>
{
    protected:
        using typename List<T>::LinkNode;
        using SingleList<T>::m_head;
        using SingleList<T>::m_tail;
        using SingleList<T>::m_size;

    public:
        using SingleList<T>::front;
        using SingleList<T>::back;
        using SingleList<T>::clear;
        using SingleList<T>::empty;
        using SingleList<T>::size;
        using SingleList<T>::display;
        using SingleList<T>::push_front;
        using SingleList<T>::pop_front;
        using SingleList<T>::push_back;
        using SingleList<T>::pop_back;

        /*
        * Function        : constructor
        */
        deque() = default;

        /*
        * Function        : constructor
        */
        ~deque() = default;
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

//map
template<typename Key, typename Value>
class map
{//map
    private://members
        struct Node
        {
            Key key;
            Value val;
            Node* left = nullptr;
            Node* right = nullptr;
            Node* parent = nullptr;
            enum{red, black} color = red;
            
            Node(const Key& k, const Value& v): key(k), val(v) {}

            /*
            * Function Name   : Release
            * Function        : delete all nodes in the tree
            */
            void Release()
            {
                if(left != nullptr)
                {
                    left -> Release();
                    delete left;
                    left = nullptr;
                }

                if(right != nullptr)
                {
                    right -> Release();
                    delete right;
                    right = nullptr;
                }
            }

            /*
            * Function Name   : Display
            * Function        : display all values in non-decreasing order of keys
            */
            void Display()
            {
                if(left != nullptr)
                    left -> Display();
                cout << "Key: " << key << ", Value: " << val << endl;
                if(right != nullptr)
                    right -> Display();
            }
        };

        Node* m_root = nullptr;
        size_t m_size = 0;

    private://internal functions
        /*
        * Function Name   : ReverseColor
        * Function        : change the given node from black to red, and vice versa
        * Input Parameters: Node* - the node to be reversed
        */
        inline void ReverseColor(Node* cur)
        {
            if(cur == nullptr)
                return;
            if(cur -> color == Node::black)
                cur -> color = Node::red;
            else
                cur -> color = Node::black;
        }

        /*
        * Function Name   : GetUthis = nullptr;ncle
        * Function        : get the uncle of the given node(cur -> parent -> parent -> left or right)
        * Input Parameters: Node* - the node to get its uncle
        * Return Value    : Node* - the uncle of the given node
        */
        inline Node* GetUncle(Node* cur)
        {
            if(cur -> parent == nullptr || cur -> parent -> parent == nullptr)
                return nullptr;
            
            //if parent is the left son of the grandparent
            if(cur -> parent == cur -> parent -> parent -> left)
                return cur -> parent -> parent -> right;
            else
                return cur -> parent -> parent -> left;
        }
        /*
        * Function Name   : LeftRotate
        * Function        : left rotate the given node
        * Input Parameters: Node* - the node to rotate
        *
        *     |                       |
        *     X                       Y
        *    / \     l-rotate(X)     / \
        *   L   Y    ==========>    X   R
        *      / \                 / \
        *     M   R               L   M
        */
        void LeftRotate(Node* x)
        {
            Node* y = x -> right;
            //move M
            x -> right = y -> left;
            if(y -> left != nullptr)
                y -> left -> parent = x;

            //move Y
            y -> parent = x -> parent;
            if(x -> parent == nullptr)
                m_root = y;
            else if(x == x -> parent -> left)
                x -> parent -> left = y;
            else
                x -> parent -> right = y;
            
            y -> left = x;
            x -> parent = y;
        }

        /*
        * Function Name   : RightRotate
        * Function        : right rotate the given node
        * Input Parameters: Node* - the node to rotate
        *        |                   |
        *        X                   Y
        *       / \   r-rotate(X)   / \
        *      Y   R  ==========>  L   X
        *     / \                     / \
        *    L   M                   M   R
        */
        void RightRotate(Node* x)
        {
            Node* y = x -> left;

            //move M
            x -> left = y -> right;
            if(y -> right != nullptr)
                y -> right -> parent = x;

            //move Y
            y -> parent = x -> parent;
            if(x -> parent == nullptr)
                m_root = y;
            else if(x == x -> parent -> left)
                x -> parent -> left = y;
            else
                x -> parent -> right = y;

            y -> right = x;
            x -> parent = y;
        }

    public://external interface
        /*
        * Function Name   : size
        * Function        : get the number of nodes in the tree
        * Return Value    : size_t - the number of nodes in the tree
        */
        size_t size() const
        {
            return m_size;
        }

        /*
        * Function Name   : empty
        * Function        : check if the tree is empty
        * Return Value    : bool - true if the tree is empty
        */
        bool empty() const
        {
            return m_size == 0;
        }

        /*
        * Function Name   : clear
        * Function        : clear all nodes in the tree
        */
        void clear()
        {
            if(m_root == nullptr)
                return;
            m_root -> Release();
            delete m_root;
            m_root = nullptr;
            m_size = 0;
        }   

        /*
        * Function Name   : display
        * Function        : display all values in non-decreasing order of keys
        */
        void display() const
        {
            if(m_root == nullptr)
                return;
            m_root -> Display();
        }

        /*
        * Function Name   : find
        * Function        : find the node with the given key
        * Input Parameters: const Key& - the key to find
        * Return Value    : Node* - the pointer to the node, otherwise nullptr
        */
        Node* find(const Key& key) const
        {
            Node* cur = m_root;
            while(cur != nullptr)
            {
                if(cur -> key == key)
                    return cur;
                else if(cur -> key < key)
                    cur = cur -> right;
                else
                    cur = cur -> left;
            }
            return nullptr;
        }

        /*
        * Function Name   : insert
        * Function        : insert a new node with the given key and value
        * Input Parameters: const Key& - the key of the new node
        *                   const Value& - the value of the new node
        */
        void insert(const Key& key, const Value& val)
        {
            Node* new_node = new Node(key, val);
            //First: insert the new node
            //if the tree is empty
            if(m_size == 0)
            {
                new_node -> color = Node::black;
                m_root = new_node;
                m_size++;
                return;
            }
            //else find a proper position to insert
            Node* cur = m_root;
            Node* temp_parent = nullptr;
            while(cur != nullptr)
            {
                temp_parent = cur;
                if(key < cur -> key)
                    cur = cur -> left;
                else if(key > cur -> key)
                    cur = cur -> right;
                else if(key == cur -> key)//already exist the same key
                {
                    cur -> val = val;
                    delete new_node;
                    return;
                }
            }
            new_node -> parent = temp_parent;
            cur = new_node;
            if(key > temp_parent -> key)
                temp_parent -> right = new_node;
            else
                temp_parent -> left = new_node;
            m_size++;

            //Second: maintain the balance
            //if already balanced
            if(new_node -> parent -> color == Node::black)
                return;
            //else loop to check and maintain the balance
            while(cur != m_root && cur -> parent -> color != Node::black)//if the parent is black || cur is the root,it's already balanced
            {
                Node* uncle = GetUncle(cur);
                if(uncle == nullptr || uncle -> color == Node::black)
                {
                    //use rotate operation
                    if(cur -> parent == cur -> parent -> parent -> left)
                    {
                        //LL
                        //     G                      P
                        //    / \                    / \
                        //   P   U   r-rotate (G)   C   G
                        //  /        ----------->        \
                        // C                              U
                        if(cur == cur -> parent -> left)
                        {
                            RightRotate(cur -> parent -> parent);
                            ReverseColor(cur -> parent);
                            ReverseColor(cur -> parent -> right);
                            cur = cur -> parent;
                        }
                        //LR
                        //     G                        G                        C  
                        //    / \                      / \                      / \ 
                        //   P   U   l-rotate (P)     C   U    r-rotate (G)    P   G
                        //    \      ----------->    /         ----------->         \
                        //     C                    P                                U
                        else if(cur == cur -> parent -> right)
                        {
                            LeftRotate(cur -> parent);
                            RightRotate(cur -> parent);
                            ReverseColor(cur);
                            ReverseColor(cur -> right);
                        }
                    }
                    else if(cur -> parent == cur -> parent -> parent -> right)
                    {
                        //RL
                        //     G                        G                        C
                        //    / \                      / \                      / \
                        //   U   P   r-rotate (P)     U   C    l-rotate (G)    G   P
                        //      /    ----------->          \   ----------->   /     
                        //     C                            p                U       
                        if(cur == cur -> parent -> left)
                        {
                            RightRotate(cur -> parent);
                            LeftRotate(cur -> parent);
                            ReverseColor(cur);
                            ReverseColor(cur -> left);
                        }
                        //RR
                        //     G                        P
                        //    / \                      / \
                        //   U   P    l-rotate (G)    G   C
                        //        \   ----------->   / 
                        //         C                U   
                        else if(cur == cur -> parent -> right)
                        {
                            LeftRotate(cur -> parent -> parent);
                            ReverseColor(cur -> parent);
                            ReverseColor(cur -> parent -> left);
                            cur = cur -> parent;
                        }
                    }
                }
                else if(uncle -> color == Node::red)
                {
                    ReverseColor(cur -> parent -> parent);
                    ReverseColor(cur -> parent -> parent -> left);
                    ReverseColor(cur -> parent -> parent -> right);
                    cur = cur -> parent -> parent;
                }
            }

            //make sure the root is black
            if(cur -> color == Node::red && cur == m_root)
                cur -> color = Node::black;
        }

        //TODO : add a real remove function !!!!HARD!!!!
        /*
        * Function Name   : remove
        * Function        : remove the node with the given key
        * Input Parameters: const Key& - the key to remove
        */
        void remove(const Key& key)
        {
            Node* cur = find(key);
            if(cur == nullptr)
            {
                cerr << "Invalid key" << endl;
                return;
            }
            cur -> val = Value();
            return;
        }

        /*
        * Function Name   : operator[]
        * Function        : get the value of the node with the given key
        * Input Parameters: const Key& - the key to find
        * Return Value    : const Value& - the value of the node with the given key
        */
        const Value& operator[](const Key& key)const
        {
            Node* cur = find(key);
            if(cur == nullptr)
                cerr << "Invalid key" << endl;
            return cur -> val;
        }

        /*
        * Function Name   : operator[]
        * Function        : get the referance of value of the node with the given key
        * Input Parameters: const Key& - the key to find
        * Return Value    : Value& - the referance of the value of the node with the given key
        */
        Value& operator[](const Key& key)
        {
            Node* cur = find(key);
            if(cur == nullptr)
            {
                insert(key, Value());
                cur = find(key);
            }
            return cur -> val;
        }
    
    public://constructor&destructor
        /*
        * Function Name   : destructor
        */
        ~map()
        {
            clear();
        }

        //TOTO : add a copy constructor and copy function

    public://iterator
        class iterator
        {
            private://members
                Node* m_ptr;

            public://constructor&destructor
                /*
                * Function Name   : constructor
                */
                iterator() : m_ptr(nullptr) {}

                /*
                * Function Name   : constructor
                */
                iterator(Node* ptr) : m_ptr(ptr) {}
            
            public://external interface
                /*
                * Function Name   : operator*
                * Function        : overload the * operator to get the value of the node
                * Return Value    : Value& - the value of the node
                */
                Node& operator*() const
                {
                    return *m_ptr;
                }

                /*
                * Function Name   : operator->
                * Function        : overload the -> operator to get the pointer of the node
                * Return Value    : Node* - the pointer of the node
                */
                Node* operator->() const
                {
                    return m_ptr;
                }

                /*
                * Function Name   : operator++
                * Function        : overload the ++ operator to move the pointer to the next node
                * Return Value    : iterator& - the pointer to the next node
                */
                iterator& operator++()
                {
                    if(m_ptr == nullptr)
                        return *this;

                    //if exist right son
                    if(m_ptr -> right != nullptr)
                    {
                        //the next point is the leftmost node of the right son
                        m_ptr = m_ptr -> right;
                        while(m_ptr -> left != nullptr)
                            m_ptr = m_ptr -> left;
                    }
                    else//if not exist right son
                    {
                        //the next point is the first ancestor that the current node is the left son
                        Node* temp = m_ptr -> parent;
                        while(temp != nullptr && m_ptr == temp -> right)
                        {
                            m_ptr = temp;
                            temp = temp -> parent;
                        }
                        m_ptr = temp;
                    }
                    return *this;
                }

                /*
                * Function Name   : operator++(int)
                * Function        : overload the ++ operator to move the pointer to the next node, and return a copy of the current node
                * Return Value    : iterator - the pointer to the next node
                */
                iterator operator++(int)
                {
                    iterator temp = *this;
                    ++(*this);
                    return temp;
                }

                /*
                * Function Name   : operator--
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

        /*
        * Function Name   : begin
        * Function        : get the iterator to the first node
        * Return Value    : iterator - the iterator to the first node
        */
        iterator begin()
        {
            Node* cur = m_root;
            if(cur == nullptr)
                return iterator(nullptr);
            //begin is the leftmost node
            while(cur -> left != nullptr)
                cur = cur -> left;
            return iterator(cur);
        }

        /*
        * Function Name   : end
        * Function        : get the iterator to the end of the tree
        * Return Value    : iterator - the iterator to the end of the tree
        */
        iterator end()
        {
            return iterator(nullptr);
        }
};

//heap
//a function object defining max heap
template<typename T>
class less
{
    public:
        bool operator()(const T& a, const T& b)
        {
            return a < b;
        }
};

//a function object defining min heap
template<typename T>
class greater
{
    public:
        bool operator()(const T& a, const T& b)
        {
            return a > b;
        }
};

//the heap class, and default is max heap
template<typename T, typename Compare = less<T>>
class heap
{//heap
    private://members
        vector<T> m_data;
        Compare m_comparator;
 
    private://internal functions
        void swap(T& a, T& b)
        {
            T temp = a;
            a = b;
            b = temp;
        }

        /*
        * Function Name   : heapify_up
        * Function        : after adding a new element to the end, let the element go up to the right position based on the m_comparator
        * Input Parameters: size_t - the index of the element to be adjusted
        */
        void heapify_up(size_t idx)
        {
            while(idx > 0)
            {
                size_t parent = (idx - 1) / 2;
                if(m_comparator(m_data[idx], m_data[parent]))
                    break;
                swap(m_data[parent], m_data[idx]);
                idx = parent;
            }
        }

        /*
        * Function Name   : heapify_down
        * Function        : after deleting the top element, let the last element go down to the right position based on the m_comparator
        * Input Parameters: size_t - the index of the element to be adjusted
        */
        void heapify_down(size_t idx)
        {
            size_t size = m_data.size();
            while(idx < size)
            {
                size_t left = 2 * idx + 1;
                size_t right = 2 * idx + 2;
                size_t superlative  = idx;
                //find the largest/smallest element among the current element, left child and right child
                if(left < size && m_comparator(m_data[superlative], m_data[left]))
                    superlative  = left;
                if(right < size && m_comparator(m_data[superlative], m_data[right]))
                    superlative  = right;
                if(superlative == idx)
                    break;
                swap(m_data[superlative], m_data[idx]);
                idx = superlative;
            }
        }

    public://external interface
        /*
        * Function Name   : empty
        * Function        : check if the heap is empty
        * Return Value    : bool - true if the heap is empty
        */
        bool empty() const
        {
            return m_data.empty();
        }

        /*
        * Function Name   : size
        * Function        : get the size of the heap
        * Return Value    : size_t - the size of the heap
        */
        size_t size() const
        {
            return m_data.size();
        }

        /*
        * Function Name   : top
        * Function        : get the top element of the heap
        * Return Value    : const T& - the top element of the heap
        */
        const T& top() const
        {
            if(m_data.empty())
                cerr << "The heap is empty!" << endl;
            return m_data[0];
        }

        /*
        * Function Name   : push
        * Function        : push a new element into the heap
        * Input Parameters: const T& - the value of the new element
        */
        void push(const T& val)
        {
            m_data.push_back(val);
            heapify_up(m_data.size() - 1);
        }

        /*
        * Function Name   : pop
        * Function        : delete the top element of the heap
        */
        void pop()
        {
            if(m_data.empty())
            {
                cerr << "The heap is empty!" << endl;
                return;
            }
            m_data[0] = m_data.back();
            m_data.pop_back();
            if(!m_data.empty())
                heapify_down(0);
        }

        /*
        * Function Name   : clear
        * Function        : clear all elements in the heap
        */
        void clear()
        {
            m_data.clear();
        }
};

}
