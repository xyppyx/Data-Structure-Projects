/**********************************************
# Project Name : Exam_Registration_System
# File Name    : Exam_Registration_System.cpp
# File Function: implement an exam registration system
# Author       : YunPeng Xu(徐云鹏)
# Update Date  : 2024/9/26
**********************************************/

#include <iostream>
#include <cstring>
#include <climits>
#include <iomanip>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;

namespace my
{

class string
{
    protected:
        //the length of string
        size_t m_length;
        //pointer to the char[] that holds the string
        char* m_data;

    public://constructor&destrutor
        /*
        * Function Name   : string
        * Function        : initialize a string object by default
        */  
        string() : m_length(0), m_data(nullptr){}

        /*
        * Function Name   : string
        * Input Parameters: const char* - a given char[]
        * Function        : initialize a string object by a given const char* str
        */  
        string(const char* str)
        {
            m_length = strlen(str);
            m_data = new char[m_length + 1];
            strcpy(m_data, str);
        }

        /*
        * Function Name   : string
        * Input Parameters: const string& - another string object
        * Function        : copy another Mystring object
        */  
        string(const string& other)
        {
            m_length = other.m_length;
            if (other.m_data != nullptr) {
                m_data = new char[m_length + 1];
                strcpy(m_data, other.m_data);
            } 
            else 
            {
                m_data = nullptr;
            }
        }

        // TODO : add a move constructor

        /*
        * Function Name   : ~string
        * Function        : delete the string object
        */
        ~string()
        {
            if(m_data != nullptr)
            {
                delete[] m_data;
                //NOTE ：set the pointer to nullptr to avoid a dangling pointer after deletion
                m_data = nullptr;
            }
        }
        
    public://external interface
        /*
        * Function Name   : operator+
        * Function        : overload the addition operator to concatenate two string objects
        * Input Parameters: const string& - another string object
        * Return Value    : string - the result of the concatenation
        */
        string operator+(const string& other) const
        {
            string new_string;
            new_string.m_length = m_length + other.m_length;
            new_string.m_data = new char[new_string.m_length + 1];
            if(m_data)
                strcpy(new_string.m_data, m_data);
            else
                new_string.m_data[0] = '\0';
            
            if(other.m_data)
                strcat(new_string.m_data, other.m_data);
            return new_string;
        }

        /*
        * Function Name   : operator+=
        * Function        : overload the += operator to concatenate two string objects
        * Input Parameters: const string& - another string object
        * Return Value    : string& - the result of the concatenation
        */
        string& operator+=(const string& other)
        {
            *this = *this + other;
            return *this;
        }

        /*
        * Function Name   : operator-
        * Function        : overload the subtraction operator to remove the last n characters of the string object
        * Input Parameters: size_t - the number of characters to be removed
        * Return Value    : string - the result of the subtraction
        */
        string operator-(size_t m_length) const
        {
            if(m_length >= this->m_length)
                return string();
            string new_string;
            new_string.m_length = this -> m_length - m_length;
            new_string.m_data = new char[new_string.m_length + 1];
            std::strncpy(new_string.m_data, this -> m_data, new_string.m_length);
            new_string.m_data[new_string.m_length] = '\0';
            return new_string;
        }

        /*
        * Function Name   : operator-=
        * Function        : overload the -= operator to remove the last n characters of the string object
        * Input Parameters: size_t - the number of characters to be removed
        * Return Value    : string& - the result of the subtraction
        */
        string& operator-=(size_t m_length)
        {
            if(m_length >= this -> m_length)
            {
                if(m_data != nullptr)
                    delete[] m_data;
                m_data = nullptr;
                this -> m_length = 0;
            }
            else
                *this = *this - m_length;
            return *this;
        }

        /*
        * Function Name   : operator==
        * Function        : overload the equality operator to compare two string objects
        * Input Parameters: const string& - another string object
        * Return Value    : bool - true if two string objects are equal
        */
        bool operator==(const string& other) const
        {
            if(m_length != other.m_length)
                return false;

            return std::strcmp(m_data, other.m_data) == 0;
        }

        /*
        * Function Name   : operator!=
        * Function        : overload the inequality operator to compare two string objects
        * Input Parameters: const string& - another string object
        * Return Value    : bool - true if two string objects are not equal
        */
        bool operator!=(const string& other) const
        {
            if(m_length != other.m_length)
                return true;

            return std::strcmp(m_data, other.m_data) != 0;
        }

        /*
        * Function Name   : operator<
        * Function        : overload the < operator to compare two string objects
        * Input Parameters: const string& - another string object
        * Return Value    : bool - true if the current string object is less than the other string object
        */
        bool operator<(const string& other) const
        {
            return std::strcmp(m_data, other.m_data) < 0;
        }

        /*
        * Function Name   : operator>
        * Function        : overload the > operator to compare two string objects
        * Input Parameters: const string& - another string object
        * Return Value    : bool - true if the current string object is greater than the other string object
        */
        bool operator>(const string& other) const
        {
            return std::strcmp(m_data, other.m_data) > 0;
        }

        /*
        * Function Name   : operator=
        * Function        : overload the assignment operator to assign one string object to another
        * Input Parameters: const string& - another string object
        * Return Value    : string& - the assigned string object
        */ 
        string& operator=(const string& other) 
        {
            if(this == &other)
                return *this;
            // NOTE : before new, remember delete
            delete[] m_data;
            m_length = other.m_length;
            m_data = new char[m_length + 1];
            if(other.m_data != nullptr)
                strcpy(m_data, other.m_data);
            else
                m_data[0] = '\0';
            return *this;
        }

        /*
        * Function Name   : operator[]
        * Function        : overload the [] operator to get the character at the index given
        * Input Parameters: size_t - index
        * Return Value    : char - the character at the index given
        */ 
        char& operator[](size_t index)
        {
            if(index < 0 || index >= m_length)
            {
                throw std::out_of_range("Invalid index!");
            }
            return m_data[index];
        }

        /*
        * Function Name   : operator[]
        * Function        : overload the [] operator to get the character at the index given
        * Input Parameters: size_t - index
        * Return Value    : const char - the character at the index given
        */ 
        const char& operator[](size_t index) const
        {
            if(index >= m_length)
            {
                throw std::out_of_range("Invalid index!");
            }
            return m_data[index];
        }

        // TODO : add a move assignment operator

        /*
        * Function Name   : size
        * Function        : get string's length
        * Return Value    : size_t - string's length
        */
        size_t size() const
        {
            return m_length;
        }

        /*
        * Function Name   : c_str
        * Function        : get the pointer to the char[] that holds the string
        * Return Value    : const char* - the pointer to the char[]
        */
        const char* c_str() const
        {
            return m_data;
        }

        /*
        * Function Name   : width
        * Function        : get string's display width
        * Return Value    : size_t - string's display width
        */
        size_t width() const
        {
            size_t display_width = 0;
            for(size_t i = 0; i < m_length; i++)
            {
                if ((m_data[i] & 0xF0) == 0xE0 && (m_data[i+1] & 0xC0) == 0x80 && (m_data[i+2] & 0xC0) == 0x80)
                {
                    display_width += 2;
                    i += 2;
                }
                else
                {
                    display_width++;
                }
            }
            return display_width;        
        }

        /*
        * Function Name   : hash
        * Function        : get the hash value of the string object(using FNV-1a)
        * Return Value    : int - the hash value
        */
        int hash() const
        {
            int p = 16777619;
            int hash = (int)2166136261L;
            for(int i = 0; i < m_length; i++)
            {
                hash = (hash ^ m_data[i]) * p;
            }
            hash += hash << 13;
            hash ^= hash >> 7;
            hash += hash << 3;
            hash ^= hash >> 17;
            hash += hash << 5;
            return hash;
        }

        /*
        * Function Name   : getline
        * Function        : get a line from an input stream
        * Input Parameters: std::istream& - the input stream
        */
        void getline(std::istream& is) 
        {
            char buffer[1024];
            is.getline(buffer, 1024);

            delete[] m_data;

            m_length = strlen(buffer);
            m_data = new char[m_length + 1];
            strcpy(m_data, buffer);
        }

        /*
        * Function Name   : push_back
        * Function        : add a new character to the end of the string
        * Input Parameters: char - the new character
        */
        void pop_back()
        {
            if(m_length > 0)
            {
                m_data[m_length - 1] = '\0';
                m_length--;
            }
        }

        /*
        * Function Name   : push_back
        * Function        : add a new string to the end of the string
        * Input Parameters: string - the new string
        */
        void push_back(string str)
        {
            *this += str;
        }

        /*
        * Function Name   : substr
        * Function        : get a substring of the string object
        * Input Parameters: size_t - the start position of the substring
        *                   int - the length of the substring
        * Return Value    : string - the substring
        */
        string substr(size_t pos, int len = -1) const
        {
            if(pos >= m_length)
                return string();

            if(pos + len > m_length || len == -1)
                len = m_length - pos;
            
            string new_string;
            new_string.m_length = len;
            new_string.m_data = new char[len + 1];
            strncpy(new_string.m_data, m_data + pos, len);
            new_string.m_data[len] = '\0';
            return new_string;
        }

    public://friends
        friend std::ostream& operator<<(std::ostream& os, const string& str);

        friend std::istream& operator>>(std::istream& is, string& str);

    public://iterator
        class iterator
        {
            public://members
                enum class Direction{forward, backward};

            private://members
                char* m_ptr;
                Direction m_dir;

            public://constructor
                iterator() : m_ptr(nullptr), m_dir(iterator::Direction::forward) {}

                iterator(char* ptr, Direction dir) : m_ptr(ptr), m_dir(dir) {}

            public://external interface
                /*
                * Function Name   : operator*
                * Function        : overload the * operator to get the element the pointer points to
                * Return Value    : char& - the element the pointer points to
                */
                char& operator*()
                {
                    return *m_ptr;
                }

                /*
                * Function Name   : operator->
                * Function        : overload the -> operator to get the pointer of the element the pointer points to
                * Return Value    : char* - the pointer of the element the pointer points to
                */
                char* operator->()
                {
                    return m_ptr;
                }

                /*
                * Function Name   : operator==
                * Function        : overload the == operator to compare two pointers
                * Input Parameters: const iterator& - other
                * Return Value    : bool - true if two pointers are equal
                */
                bool operator==(const iterator& other) const
                {
                    return m_ptr == other.m_ptr;
                }

                /*
                * Function Name   : operator!=
                * Function        : overload the != operator to compare two pointers
                * Input Parameters: const iterator& - other
                * Return Value    : bool - true if two pointers are not equal
                */
                bool operator!=(const iterator& other) const
                {
                    return m_ptr != other.m_ptr;
                }

                /*
                * Function Name   : operator++
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
                        ++m_ptr;
                    else
                        --m_ptr;

                    return temp;
                }

                /*
                * Function Name   : operator+(int)
                * Function        : overload the + operator to move the pointer to the next n elements
                * Input Parameters: int - n
                * Return Value    : iterator - the pointer to the next n elements
                */
                iterator operator+(int n)
                {
                    iterator temp = *this;
                    if(m_dir == Direction::forward)
                        temp.m_ptr = m_ptr + n;
                    else
                        temp.m_ptr = m_ptr - n;

                    return temp;
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
                        --m_ptr;
                    else
                        ++m_ptr;

                    return temp;
                }

                /*
                * Function Name   : operator-(int)
                * Function        : overload the - operator to move the pointer to the previous n elements
                * Input Parameters: int - n
                * Return Value    : iterator - the pointer to the previous n elements
                */
                iterator operator-(int n)
                {
                    iterator temp = *this;
                    if(m_dir == Direction::forward)
                        temp.m_ptr = m_ptr - n;
                    else
                        temp.m_ptr = m_ptr + n;

                    return temp;
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
        };

        iterator begin()
        {
            return iterator(m_data, iterator::Direction::forward);
        }

        iterator end()
        {
            return iterator(m_data + m_length, iterator::Direction::forward);
        }

        iterator rbegin()
        {
            return iterator(m_data + m_length - 1, iterator::Direction::backward);
        }

        iterator rend()
        {
            return iterator(m_data - 1, iterator::Direction::backward);
        }
};

/*
* Function Name   : operator<<
* Function        : overload the insertion operator to output a string object to an output stream
* Input Parameters: std::ostream& - the output stream
*                   const string& - the string object to be output
* Return Value    : std::ostream& - the output stream
*/
std::ostream& operator<<(std::ostream& os, const string& str)
{
    os<<str.m_data;
    return os;
}

/*
* Function Name   : operator>>
* Function        : overload the extraction operator to input a string object from an input stream
* Input Parameters: std::istream& - the input stream
*                   string& - the string object to be input
* Return Value    : std::istream& - the input stream
*/
std::istream& operator>>(std::istream& is, string& str)
{
    char buffer[4096];
    is >> buffer;
    delete[] str.m_data;
    str.m_length = std::strlen(buffer);
    str.m_data = new char[str.m_length + 1];
    strcpy(str.m_data, buffer);
    return is;
}

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

}

class ExamRegisterSystem
{
    protected://members
        //define the structure of student information
        using StuInfo = struct
        {
            my::string id;
            my::string name;
            //0-male  1-female
            bool sex;
            short age;
            my::string category;
        };

        using Statistics = struct
        {
            //the num of students in each age group(< 18, 18-35, 36-60, > 60)
            size_t age_num[4] = {0};
            size_t gender_num[2] = {0};
            size_t all_num = 0;
            my::map <my::string, size_t> category_num;
        };

        Statistics statistics;

    protected://internal functions
        /*
        * Function Name   : RenewStatistics
        * Function        : renew the statistics of students
        * Input Parameters: SingleList<StuInfo>& - the list of students
                            const string& - id
                            const string& - operation(insert/remove)
        */
        void RenewStatistics(my::SingleList<StuInfo>& stu_list, const my::string& id, const my::string& opt)
        {
            for(size_t i = 1; i <= stu_list.size(); i++)
            {
                if(stu_list[i].id == id && opt == "insert")
                {
                    statistics.all_num++;
                    if(stu_list[i].age < 18)
                        statistics.age_num[0]++;
                    else if(stu_list[i].age <= 35)
                        statistics.age_num[1]++;
                    else if(stu_list[i].age <= 60)
                        statistics.age_num[2]++;
                    else
                        statistics.age_num[3]++;

                    if(stu_list[i].sex == 0)
                        statistics.gender_num[0]++;
                    else
                        statistics.gender_num[1]++;
                    
                    statistics.category_num[stu_list[i].category]++;
                    break;
                }
                else if(stu_list[i].id == id && opt == "remove")
                {
                    statistics.all_num--;
                    if(stu_list[i].age < 18)
                        statistics.age_num[0]--;
                    else if(stu_list[i].age <= 35)
                        statistics.age_num[1]--;
                    else if(stu_list[i].age <= 60)
                        statistics.age_num[2]--;
                    else
                        statistics.age_num[3]--;

                    if(stu_list[i].sex == 0)
                        statistics.gender_num[0]--;
                    else
                        statistics.gender_num[1]--;

                    statistics.category_num[stu_list[i].category]--;
                    break;
                }
            }
        }

        /*
        * Function Name   : SetwPrint
        * Function        : print a string with a certain width(fill with space)
        */
        void SetwPrint(const my::string& str, size_t width)
        {
            cout<<str;
            cout<<std::setw(width - str.width())<<" ";
        }

        /*
        * Function Name   : SearchInfo
        * Function        : check if the student with the id given exists
        * Input Parameters: SingleList<StuInfo>& - the list of students
                            const string& - id
        * Return Value    : bool - true if find the id
        */ 
        bool SearchInfo(my::SingleList<StuInfo>& stu_list, const my::string& id)
        {
            for(int i = 1; i <= stu_list.size(); i++)
            {
                if(stu_list[i].id == id)
                    return true;
            }
            return false;
        }

        /*
        * Function Name   : DisplayInfo
        * Function        : print the information of all students
        * Input Parameters: SingleList<StuInfo>& - the list of students
        */
        void DisplayInfo(my::SingleList<StuInfo>& stu_list)
        {
            cout << std::endl << ">>> 考生信息" << std::endl;
            cout << "+--------------+--------------------------+------+------+----------------------------------+" << std::endl;
            cout << "| 考号         | 姓名                     | 性别 | 年龄 | 报考类别                         |" << std::endl;
            cout << "+--------------+--------------------------+------+------+----------------------------------+" << std::endl;
            for(int i = 1; i <= stu_list.size(); i++)
            {
                cout<<"| ";
                cout<<std::setw(12)<<stu_list[i].id;
                cout<<" | ";
                SetwPrint(stu_list[i].name, 24);
                cout<<" | ";
                if(stu_list[i].sex == 1) cout<<"女  ";
                else cout<<"男  ";
                cout<<" | ";
                cout<<std::setw(4)<<stu_list[i].age;
                cout<<" | ";
                SetwPrint(stu_list[i].category, 32);
                cout<<" |"<<endl;
            }
            cout << "+--------------+--------------------------+------+------+----------------------------------+" << std::endl;
        }

        /*
        * Function Name   : DisplayInfo
        * Function        : print the information of a specific student
        * Input Parameters: SingleList<StuInfo>& - the list of students
                            size_t - the index of the student
        */
        void DisplayInfo(my::SingleList<StuInfo>& stu_list, size_t idx)
        {
            cout << std::endl << ">>> 所选考生信息" << std::endl;
            cout << "+--------------+--------------------------+------+------+----------------------------------+" << std::endl;
            cout << "| 考号         | 姓名                     | 性别 | 年龄 | 报考类别                         |" << std::endl;
            cout << "+--------------+--------------------------+------+------+----------------------------------+" << std::endl;
            cout<<"| ";
            cout<<std::setw(12)<<stu_list[idx].id;
            cout<<" | ";
            SetwPrint(stu_list[idx].name, 24);
            cout<<" | ";
            if(stu_list[idx].sex == 1) cout<<"女  ";
            else cout<<"男  ";
            cout<<" | ";
            cout<<std::setw(4)<<stu_list[idx].age;
            cout<<" | ";
            SetwPrint(stu_list[idx].category, 32);
            cout<<" |"<<endl;
            cout << "+--------------+--------------------------+------+------+----------------------------------+" << std::endl;
        }

        /*
        * Function Name   : InputPrompt
        * Function        : print the input prompt
        * Input Parameters: const string& - prompt
        */ 
        void InputPrompt(const my::string& prompt)
        {
            std::cout << std::endl << ">>> " << prompt << std::endl;
            std::cout << "    [输入格式] 考号 姓名 性别 年龄 报考类别 (用空格分隔数据)" << std::endl;
            std::cout << "    [考    号] 不超过 12 个数字字符组成的字符串" << std::endl;
            std::cout << "    [姓    名] 不超过 24 个英文字符或 12 个汉字字符组成的字符" << std::endl;
            std::cout << "    [性    别] 男 / 女" << std::endl;
            std::cout << "    [年    龄] 在 1 至 99 范围内的整型数据" << std::endl;
            std::cout << "    [报考类别] 不超过 32 个英文字符或 16 个汉字字符组成的字符串" << std::endl << std::endl;
        }

        /*
        * Function Name   : IsChapterValid
        * Function        : check if the input is valid(belong to the language given && in the range)
        * Input Parameters: const string& - input
                            const string& - language(Chinese/English/Number)
                            size_t - limit
        * Return Value    : bool - true if valid
        */ 
        bool IsChapterValid(const my::string& input, const my::string& language, size_t limit)
        {
            //check language
            for(size_t i = 0; i < input.size(); i++)
            {
                if(language == "Chinese")
                {
                    if((unsigned char)input[i] < 0xE0)
                        return false;
                    else
                        i += 2;
                }
                else if(language == "English")
                {
                    if(!('a' <= input[i] && input[i] <= 'z') && !('A' <= input[i] && input[i] <= 'Z'))
                        return false;
                }
                else if(language == "Number")
                {
                    if(!('0' <= input[i] && input[i] <= '9'))
                        return false;
                }   
            }

            //check width
            if(language == "Chinese")
            {
                if(input.size() > 3 * limit)
                    return false;
            }
            else if(language == "English")
            {
                if(input.size() > limit)
                    return false;
            }
            else
            {
                if(input.size() > limit)
                    return false;
            }

            return true;
        }

        /*
        * Function Name   : InputInt
        * Function        : get integer input of a certain range
        * Input Parameters: int - lower bound
                            int - upper bound
                            const string& - prompt
        * Return Value    : the correct input
        */ 
        int InputInt(int lower_bound, int upper_bound, const my::string& prompt)
        {
            double temp_input;
            while(true)
            {
                cout<<endl<<prompt<<"[整数范围: "<<lower_bound<<"~"<<upper_bound<<"]:"<<endl;
                cin>>temp_input;
                if(cin.good() && temp_input == (int)temp_input && lower_bound <= temp_input && temp_input <= upper_bound)
                {
                    return (int)temp_input;
                }
                else
                {
                    cerr<<endl<<">>> 输入不合法，请重新输入"<<endl<<endl;
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                }
            }
        }

        /*
        * Function Name   : InputInfo
        * Function        : input the information of students and implement error handling
        * Input Parameters: SingleList<StuInfo>& - the list of students
                            int - the number of students
                            const string& - prompt
        */ 
        void InputInfo(my::SingleList<StuInfo>& stu_list, int stu_num, const my::string& prompt)
        {
            int position = -1;
            if(prompt == "请录入要插入的考生信息:")
                position = InputInt(1, stu_list.size() + 1, ">>> 请输入待插入考生的位置:");
            InputPrompt(prompt);

            for(size_t i = 1; i <= stu_num; i++)
            {
                StuInfo temp_stu;
                my::string temp_sex;
                double temp_age;

                //input student id
                cin>>temp_stu.id;
                if(!IsChapterValid(temp_stu.id, "Number", 12) || cin.fail())
                {
                    cerr<<endl<<">>> 考号输入不合法，请重新输入当前考生信息！"<<endl;
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    i--;
                    continue;
                }
                
                if(SearchInfo(stu_list, temp_stu.id))
                {
                    cerr<<endl<<">>> 考号重复，请重新输入当前考生信息！"<<endl;
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    i--;
                    continue;
                }

                //input student name
                cin>>temp_stu.name;
                if(!IsChapterValid(temp_stu.name, "Chinese", 12) && !IsChapterValid(temp_stu.name, "English", 24) || cin.fail())
                {
                    cerr<<endl<<">>> 姓名输入不合法，请重新输入当前考生信息！"<<endl;
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    i--;
                    continue;
                }
                

                //input student sex
                cin>>temp_sex;
                if(temp_sex == "男")
                    temp_stu.sex = 0;
                else if(temp_sex == "女")
                    temp_stu.sex = 1;
                else
                {
                    cerr<<endl<<">>> 性别输入不合法，请重新输入当前考生信息！"<<endl;
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    i--;
                    continue;
                }
                

                //input student age
                cin>>temp_age;
                if(temp_age == (int)temp_age && 1 <= temp_age && temp_age <= 99)
                    temp_stu.age = (int)temp_age;
                else
                {
                    cerr<<endl<<">>> 年龄输入不合法，请重新输入当前考生信息！"<<endl;
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    i--;
                    continue;
                }
                

                //input student category
                cin>>temp_stu.category;
                if(!IsChapterValid(temp_stu.category, "Chinese", 16) && !IsChapterValid(temp_stu.category, "English", 32) || cin.fail())
                {
                    cerr<<endl<<">>> 报考类别输入不合法，请重新输入当前考生信息！"<<endl;
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    i--;
                    continue;
                }

                if(position == -1)
                    stu_list.push_back(temp_stu);
                else
                    stu_list.insert(position - 1, temp_stu);

                RenewStatistics(stu_list, temp_stu.id, "insert");
            }
            DisplayInfo(stu_list);
        }

        /*
        * Function Name   : RemoveInfo
        * Function        : input an id and remove the student information with the id
        * Input Parameters: SingleList<StuInfo>& - the list of students
                            const string& - prompt
        */ 
        void RemoveInfo(my::SingleList<StuInfo>& stu_list, const my::string& prompt)
        {
            my::string id;
            if(prompt != "")
                cout<<endl<<">>> "<<prompt<<endl;
            while(true)
            {
                cin>>id;
                if(!IsChapterValid(id, "Number", 12) || cin.fail())
                {
                    cerr<<endl<<">>> 考号输入不合法，请重新输入当前考生信息！"<<endl;
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                }
                else if(!SearchInfo(stu_list, id))
                {
                    cerr<<endl<<">>> 未查询到该考生，请重新输入当前考生信息！"<<endl;
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                }
                else
                    break;
            }

            for(size_t i = 1; i <= stu_list.size(); i++)
            {
                if(stu_list[i].id == id)
                {
                    RenewStatistics(stu_list, id, "remove");
                    stu_list.remove(i);
                    break;
                }
            }

            DisplayInfo(stu_list);
        }

        /*
        * Function Name   : QueryInfo
        * Function        : input an id and display the student information with the id
        * Input Parameters: SingleList<StuInfo>& - the list of students
                            const string& - prompt
        */
        void QueryInfo(my::SingleList<StuInfo>& stu_list, const my::string& prompt)
        {
            my::string id;
            if(prompt != "")
                cout<<endl<<">>> "<<prompt<<endl;
            while(true)
            {
                
                cin>>id;
                if(!IsChapterValid(id, "Number", 12) || cin.fail())
                {
                    cerr<<endl<<">>> 考号输入不合法，请重新输入当前考生信息！"<<endl;
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                }
                else if(!SearchInfo(stu_list, id))
                {
                    cerr<<endl<<">>> 未查询到该考生，请重新输入当前考生信息！"<<endl;
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                }
                else
                    break;
            }

            for(size_t i = 1; i <= stu_list.size(); i++)
            {
                if(stu_list[i].id == id)
                {
                    DisplayInfo(stu_list, i);
                    break;
                }
            }
        }

        /*
        * Function Name   : ModifyInfo
        * Function        : input an id and modify the student information with the id
        * Input Parameters: SingleList<StuInfo>& - the list of students
                            const string& - prompt
        */
        void ModifyInfo(my::SingleList<StuInfo>& stu_list, const my::string& prompt)
        {
            my::string id;
            if(prompt != "")
                cout<<endl<<">>> "<<prompt<<endl;
            //input student id
            while(true)
            {
                cin>>id;
                if(!IsChapterValid(id, "Number", 12) || cin.fail())
                {
                    cerr<<endl<<">>> 考号输入不合法，请重新输入当前考生信息！"<<endl;
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    continue;
                }
                else if(!SearchInfo(stu_list, id))
                {
                    cerr<<endl<<">>> 未查询到该考生，请重新输入当前考生信息！"<<endl;
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    continue;
                }
                else
                    break;
            }

            for(size_t i = 1; i <= stu_list.size(); i++)
            {
                if(stu_list[i].id == id)
                {
                    DisplayInfo(stu_list, i);
                    RenewStatistics(stu_list, id, "remove");
                    stu_list.remove(i);
                    InputPrompt(">>> 请录入修改后的考生信息:");
                    
                    StuInfo temp_stu;
                    my::string temp_sex;
                    double temp_age;

                    //input new student id
                    while(true)
                    {
                        cin>>temp_stu.id;
                        if(!IsChapterValid(temp_stu.id, "Number", 12) || cin.fail())
                        {
                            cerr<<endl<<">>> 考号输入不合法，请重新输入当前考生信息！"<<endl;
                            cin.clear();
                            cin.ignore(INT_MAX, '\n');
                        }
                        else if(SearchInfo(stu_list, temp_stu.id))
                        {
                            cerr<<endl<<">>> 考号重复，请重新输入当前考生信息！"<<endl;
                            cin.clear();
                            cin.ignore(INT_MAX, '\n');
                        }
                        else 
                            break;
                    }

                    //input student name
                    while(true)
                    {
                        cin>>temp_stu.name;
                        if(!IsChapterValid(temp_stu.name, "Chinese", 12) && !IsChapterValid(temp_stu.name, "English", 24) || cin.fail())
                        {
                            cerr<<endl<<">>> 姓名输入不合法，请重新输入当前考生信息！"<<endl;
                            cin.clear();
                            cin.ignore(INT_MAX, '\n');
                        }
                        else
                            break;
                    }
                        
                    //input student sex
                    while(true)
                    {
                        cin>>temp_sex;
                        if(temp_sex == "男")
                        {
                            temp_stu.sex = 0;
                            break;
                        }
                        else if(temp_sex == "女")
                        {
                            temp_stu.sex = 1;
                            break;
                        }
                        else
                        {
                            cerr<<endl<<">>> 性别输入不合法，请重新输入当前考生信息！"<<endl;
                            cin.clear();
                            cin.ignore(INT_MAX, '\n');
                        }
                    }
                        
                    //input student age
                    while(true)
                    {
                        cin>>temp_age;
                        if(temp_age == (int)temp_age && 1 <= temp_age && temp_age <= 99)
                        {
                            temp_stu.age = (int)temp_age;
                            break;
                        }
                        else
                        {
                            cerr<<endl<<">>> 年龄输入不合法，请重新输入当前考生信息！"<<endl;
                            cin.clear();
                            cin.ignore(INT_MAX, '\n');
                        }
                    }
                        
                    //input student category
                    while(true)
                    {
                        cin>>temp_stu.category;
                        if(!IsChapterValid(temp_stu.category, "Chinese", 16) && !IsChapterValid(temp_stu.category, "English", 32) || cin.fail())
                        {
                            cerr<<endl<<">>> 报考类别输入不合法，请重新输入当前考生信息！"<<endl;
                            cin.clear();
                            cin.ignore(INT_MAX, '\n');
                        }
                        else
                            break;
                    }
                    
                    stu_list.insert(i - 1, temp_stu);
                    RenewStatistics(stu_list, temp_stu.id, "insert");
                    DisplayInfo(stu_list);
                    break;  
                }
            }
        }

        void CategorytStatistics(my::SingleList<StuInfo>& stu_list)
        {

            cout << endl << ">>> 考生报考类别统计" << endl;
            cout << "+----------------------------------+------------+------------+" << endl;
            cout << "| 报考类别                         | 人数       | 比例(%)    |" << endl;
            cout << "+----------------------------------+------------+------------+" << endl;
            for(auto it = statistics.category_num.begin(); it != statistics.category_num.end(); ++it)
            {
                if(it -> val <= 0)
                    continue;
                cout << "| ";
                SetwPrint(it -> key, 32);
                cout << " | ";
                cout << std::setw(10) << it -> val << " | ";
                cout << std::fixed << std::setw(10) << it -> val * 100.0 / statistics.all_num << " |" << std::endl;
                cout << "+----------------------------------+------------+------------+" << endl;
            }
        }

        /*
        * Function Name   : AgeStatistics
        * Function        : print the statistics of the age
        * Input Parameters: SingleList<StuInfo>& - the list of students
        */
        void AgeStatistics(my::SingleList<StuInfo>& stu_list)
        {
            cout << endl << ">>> 考生年龄统计" << endl;
            cout << "+----------+------------+------------+" << endl;
            cout << "| 年龄区间 | 人数       | 比例(%)    |" << endl;
            cout << "+----------+------------+------------+" << endl;
            cout << "|   < 18   | "<< std::setw(10) << statistics.age_num[0] <<" | "<< std::fixed << std::setw(10) << statistics.age_num[0] * 100.0 / statistics.all_num <<" |" << endl;
            cout << "+----------+------------+------------+" << endl;
            cout << "| 18 ~ 35  | "<< std::setw(10) << statistics.age_num[1] <<" | "<< std::fixed <<  std::setw(10) << statistics.age_num[1] * 100.0 / statistics.all_num <<" |" << endl;
            cout << "+----------+------------+------------+" << endl;
            cout << "| 36 ~ 60  | "<< std::setw(10) << statistics.age_num[2] <<" | "<< std::fixed <<  std::setw(10) << statistics.age_num[2] * 100.0 / statistics.all_num <<" |" << endl;
            cout << "+----------+------------+------------+" << endl;
            cout << "|   > 60   | "<< std::setw(10) << statistics.age_num[3] <<" | "<< std::fixed <<  std::setw(10) << statistics.age_num[3] * 100.0 / statistics.all_num <<" |" << endl;
            cout << "+----------+------------+------------+" << endl;
        }

        /*
        * Function Name   : GenderStatistics
        * Function        : print the statistics of gender
        * Input Parameters: SingleList<StuInfo>& - the list of students
        */
        void GenderStatistics(my::SingleList<StuInfo>& stu_list)
        {
            cout << endl << ">>> 考生性别统计" << endl;
            cout << "+------+------------+------------+" << endl;
            cout << "| 性别 | 人数       | 比例(%)    |" << endl;
            cout << "+------+------------+------------+" << endl;
            cout << "|  男  | " << std::setw(10) << statistics.gender_num[0] << " | " << std::setw(10) << (statistics.gender_num[0] * 100.0 / statistics.all_num) << " |" << std::endl;
            cout << "|  女  | " << std::setw(10) << statistics.gender_num[1] << " | " << std::setw(10) << (statistics.gender_num[1] * 100.0 / statistics.all_num) << " |" << std::endl;
            cout << "+------+------------+------------+" << std::endl;
        }

        /*
        * Function Name   : StatisticsInfo
        * Function        : print the statistics of the students
        * Input Parameters: SingleList<StuInfo>& - the list of students
        */
        void StatisticsInfo(my::SingleList<StuInfo>& stu_list)
        {
            if(stu_list.empty())
            {
                cerr<<endl<<">>> 未录入考生信息，请先录入考生信息！"<<endl<<endl;
                return;
            }
            CategorytStatistics(stu_list);
            AgeStatistics(stu_list);
            GenderStatistics(stu_list);
        }

    public:
        /*
        * Function Name   : Launch
        * Function        : perform the initialization and main loop of the program
        */
        void Launch()
        {
            //System entry prompt
            cout << std::left;
            cout << "+----------------------------+" << endl;
            cout << "|        考试报名系统        |"  << endl;
            cout << "|  Exam Registration System  |" << endl;
            cout << "+----------------------------+" << endl;

            //initialize the list of students
            cout<<endl<<">>> 请先建立考生信息系统"<<endl;
            my::SingleList<StuInfo> stu_list;
            int stu_num = InputInt(1, INT_MAX, ">>> 请输入考生人数");
            InputInfo(stu_list, stu_num, "请依次录入考生信息");

            while(true)
            {
                switch(InputInt(0, 5, ">>> 请选择您要进行的操作[1:插入 2:删除 3:查询 4:修改 5:统计 0:退出] "))
                {
                    case 1:
                        InputInfo(stu_list, 1, "请录入要插入的考生信息:");
                        break;
                    case 2:
                        RemoveInfo(stu_list, "请录入要删除的考生的考号:");
                        break;
                    case 3:
                        QueryInfo(stu_list, "请录入要查询的考生的考号:");
                        break;
                    case 4:
                        ModifyInfo(stu_list, "请录入要修改的考生的考号:");
                        break;
                    case 5:
                        StatisticsInfo(stu_list);
                        break;
                    default:
                        cout<<"考试报名系统已退出"<<endl;
                        return;
                }
            }
        }
};

signed main()
{
    cout << ">>> Please use UTF-8 encoding to ensure the normal operation of the program" << endl;
    ExamRegisterSystem exam_register_system;
    exam_register_system.Launch();
    return 0;
}