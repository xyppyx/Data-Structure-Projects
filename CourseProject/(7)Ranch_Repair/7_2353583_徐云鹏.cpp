/**********************************************
# Project Name : Ranch_Repair
# File Name    : Ranch_Repair.cpp
# File Function: solve the problem
# Author       : YunPeng Xu(徐云鹏)
# Update Date  : 2024/10/9
**********************************************/

#include<iostream>

using std::cin;
using std::cout;
using std::endl;
using std::cerr;

namespace my
{

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

class RanchRepair
{
    private://members
        //create a min my::heap
        my::heap<int, my::greater<int>> fences;
        int num;
    
    private://internal functions
        /*
        * Function Name   : Input
        * Function        : input the number of cows and the height of the cows
        */
        void Input()
        {
            cout<<">>> 请输入栅栏的数量:"<<endl;
            cin >> num;
            cout<<">>> 请输入每段栅栏的长度:"<<endl;
            for(int i = 1; i <= num; i++)
            {
                int temp;
                while(true)
                {
                    cin >> temp;
                    if(temp <= 0 || cin.fail())
                    {
                        cerr << endl << ">>> 非法输入，请重新输入第 " << i << " 个栅栏的长度!" << endl;
                        cin.clear();
                        cin.ignore(1024, '\n');
                    }
                    else
                        break;
                }
                fences.push(temp);
            }
        }

    public://external interface
        /*
        * Function Name   : Solve
        * Function        : solve the problem
        */
        void Solve()
        {
            Input();
            int cost = 0;
            
            while(!fences.empty())
            {
                int temp1 = fences.top();
                fences.pop();
                if(fences.empty())
                    break;
                int temp2 = fences.top();
                fences.pop();
                cost += temp1 + temp2;
                fences.push(temp1 + temp2);
            }
            cout << ">>> 最小费用是: " << endl << cost << endl;
        }
};

int main()
{   
    cout << ">>> Please use UTF-8 encoding to ensure the normal operation of the program" << endl;
    RanchRepair Solution;
    Solution.Solve();
    return 0;
}