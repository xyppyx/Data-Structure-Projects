/**********************************************
# Project Name : Genealogy_Management_System
# File Name    : Genealogy_Management_System.cpp
# File Function: implement a genealogy management system
# Author       : YunPeng Xu(徐云鹏)
# Update Date  : 2024/10/12
**********************************************/

#include<iostream>
#include<cstring>
#include<sstream>

using std::cin;
using std::cout;
using std::endl;
using std::cerr;

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
            strncpy(new_string.m_data, this -> m_data, new_string.m_length);
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

            return  strcmp(m_data, other.m_data) == 0;
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

            return  strcmp(m_data, other.m_data) != 0;
        }

        /*
        * Function Name   : operator<
        * Function        : overload the < operator to compare two string objects
        * Input Parameters: const string& - another string object
        * Return Value    : bool - true if the current string object is less than the other string object
        */
        bool operator<(const string& other) const
        {
            return  strcmp(m_data, other.m_data) < 0;
        }

        /*
        * Function Name   : operator>
        * Function        : overload the > operator to compare two string objects
        * Input Parameters: const string& - another string object
        * Return Value    : bool - true if the current string object is greater than the other string object
        */
        bool operator>(const string& other) const
        {
            return  strcmp(m_data, other.m_data) > 0;
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
        * Input Parameters:  istream& - the input stream
        */
        void getline(std::istream& is) 
        {
            char buffer[1024];
            is.getline(buffer, 1024);

            delete[] m_data;

            m_length =  strlen(buffer);
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
* Input Parameters:  ostream& - the output stream
*                   const string& - the string object to be output
* Return Value    :  ostream& - the output stream
*/
std::ostream& operator<<(std::ostream& os, const string& str)
{
    os<<str.m_data;
    return os;
}

/*
* Function Name   : operator>>
* Function        : overload the extraction operator to input a string object from an input stream
* Input Parameters:  istream& - the input stream
*                   string& - the string object to be input
* Return Value    :  istream& - the input stream
*/
std::istream& operator>>(std::istream& is, string& str)
{
    char buffer[4096];
    is >> buffer;
    delete[] str.m_data;
    str.m_length =  strlen(buffer);
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


class GenealogyManagementSystem
{
    private://members
        const int KMaxNameLength = 16;
        enum class Input{Exist, New};
        struct Person
        {
            my::string m_name;
            my::vector<Person*> m_children;
            Person* m_parent;

            Person() : m_name(my::string()), m_parent(nullptr) {}
            Person(const my::string& name) : m_name(name), m_parent(nullptr) {}
            ~Person(){ Release(); }

            /*
            * Function Name   : Release
            * Function        : recursively delete all children of the person
            */
            void Release()
            {
                if(m_children.size() == 0)
                    return;
                for(my::vector<Person*>::iterator it = m_children.rbegin(); it != m_children.rend(); ++it)
                {
                    if(*it == nullptr)
                        continue;
                    (*it) -> Release();
                    delete *it;
                    *it = nullptr;
                    m_children.pop_back();
                }
            }
        };
        //pointer to the ancestor
        Person* m_root;

    private://internal functions - Input
        /*
        * Function Name   : SelectOption
        * Function        : select an option from the menu
        * Return Value    : int - the option selected by the user
        */
        int SelectOption()
        {
            cout << endl << ">>> 菜单: [1]完善家谱 [2]添加家庭成员 [3]解散家庭成员 [4]更改家庭成员姓名 [5]查询家庭成员 [6]退出系统";
            cout << endl << ">>> 请选择要执行的操作：" << endl;
            int opt;
            while(true)
            {
                cin >> opt;
                if(cin.fail() || opt < 0 || opt > 6)
                {
                    cin.clear();
                    cin.ignore(1024, '\n');
                    cout << endl << ">>> 非法选项，请重新输入！" << endl;
                }
                else
                    return opt;
            }

        }

        /*
        * Function Name   : IsChapterValid
        * Function        : check if the language and length of input is valid in Chinese, English or Number
        * Input Parameters: const my::string& - the input string
        *                   const my::string& - the language of the input
        *                   size_t - the max length of the input
        * Return Value    : bool - true if the input is valid
        */
        bool IsChapterValid(const my::string& input, const my::string& language, size_t limit) const
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
        * Function Name   : InputName
        * Function        : input the name of the person
        * Input Parameters: my::string& - the name of the person
        *                   const my::string& - the prompt of the input
        *                   Input - the condition of the input(New or Exist)
        */
        void InputName(my::string& name, const my::string& prompt, Input condition) const
        {
            cout << endl << ">>> 请输入" << prompt << "的姓名：" << endl;

            while(true)
            {
                cin >> name;
                if(cin.fail() || (!IsChapterValid(name, "Chinese", KMaxNameLength / 2) && !IsChapterValid(name, "English", KMaxNameLength)))
                {
                    cout << endl << ">>> 输入不合法，" << "请重新输入" << prompt << "的姓名！" << endl;
                    cin.clear();
                    cin.ignore(1024, '\n');
                }
                else if(condition == Input::Exist && Find(name) == nullptr)
                {
                    cout << endl << ">>> 此人不存在，" << "请重新输入" << prompt << "的姓名！" << endl;
                    cin.clear();
                    cin.ignore(1024, '\n');
                }
                else
                {
                    break;
                }
            }
        }   

        /*
        * Function Name   : InputInt
        * Function        : input the number of the person
        * Input Parameters: int& - the number of the person
        *                   const my::string& - the prompt of the input
        */
        void InputInt(int& num, const my::string& prompt) const
        {
            cout << endl << ">>> 请输入" << prompt << "的个数：" << endl;    

            while(true)
            {
                cin >> num;
                if(cin.fail() || num <= 0)
                {
                    cout << endl << ">>> 个数不合法，" << "请重新输入" << prompt << "的个数！" << endl;
                    cin.clear();
                    cin.ignore(1024, '\n');
                }
                else
                {
                    break;
                }
            }
        }

    private://internal functions - CURD
        /*
        * Function Name   : Find
        * Function        : find the person with the given name
        * Input Parameters: const my::string& - the name of the person
        * Return Value    : Person* - the pointer to the person, otherwise nullptr
        */
        Person* Find(const my::string& name) const
        {
            if(m_root == nullptr)
                return nullptr;
            my::queue<Person*> people;
            people.push(m_root);

            while(!people.empty())
            {
                Person* cur = people.front();
                people.pop();

                if(cur -> m_name == name)
                    return cur;
                for(auto it = (cur -> m_children).begin(); it != (cur -> m_children).end(); ++it)
                {
                    if((*it) -> m_name == name)
                        return *it;
                    else
                        people.push(*it);
                }
            }
            return nullptr;
        }

        /*
        * Function Name   : OutputParentAndChildren
        * Function        : output the parent and children of the person
        * Input Parameters: Person* - the pointer to the person
        */
        void OutputParentAndChildren(Person* person) const
        {
            if(person -> m_parent != nullptr)
                cout << endl << ">>> " << person -> m_name << "的家长是" << person -> m_parent -> m_name << endl;

            cout << ">>> " << person -> m_name << "共有" << (person -> m_children).size() << "个儿女，";
            if(!(person -> m_children).empty())
            {
                cout << "分别是：";
                for(auto it = (person -> m_children).begin(); it != (person -> m_children).end(); ++it)
                {
                    if(*it != nullptr)
                    {
                        cout << (*it) -> m_name << " ";
                    }
                }
            }
            cout << endl;
        }

    private://internal control funtions
        /*
        * Function Name   : CompleteGenealgoy
        * Function        : complete the genealogy of the person
        */
        void CompleteGenealgoy()
        {
            my::string person_name;
            int children_num;
            InputName(person_name, "要建立家庭的人", Input::Exist);
            InputInt(children_num, "其儿女");
            Person* person = Find(person_name);

            for(int i = 1; i <= children_num; i++)
            {
                my::string child_name;
                char temp[] = {char(i + '0')};
                my::string prompt = my::string("第") + my::string(temp) + my::string("个儿女");
                InputName(child_name, prompt, Input::New);

                Person* child = new Person(child_name);
                child -> m_parent = person;
                (person -> m_children).push_back(child);
            }

            OutputParentAndChildren(person);
        }

        /*
        * Function Name   : AddFamilyMember
        * Function        : add a family member to the person
        */
        void AddFamilyMember()
        {
            my::string person_name, child_name;
            InputName(person_name, "要添加儿女的人", Input::Exist);
            InputName(child_name, "新添加的儿女", Input::New);

            Person* person = Find(person_name);
            Person* child = new Person(child_name);
            child -> m_parent = person;
            (person -> m_children).push_back(child);

            OutputParentAndChildren(person);
        }

        /*
        * Function Name   : DeleteSubFamily
        * Function        : delete the sub family of the person
        */
        void DeleteSubFamily()
        {
            my::string person_name;
            InputName(person_name, "要解散家庭的人", Input::Exist);
            Person* person = Find(person_name);
            OutputParentAndChildren(person);
            person -> Release();
            cout << endl << ">>> 儿女已全部断绝关系清出族谱" << endl;
        }

        /*
        * Function Name   : ChangeName
        * Function        : change the name of the person
        */
        void ChangeName()
        {
            my::string old_name, new_name;
            InputName(old_name, "要更改姓名的人", Input::Exist);
            InputName(new_name, "更改后", Input::New);

            Person* person = Find(old_name);
            person -> m_name = new_name;
            cout << endl << ">>> " << old_name << " 已更名为：" << new_name << endl;
        }

        /*
        * Function Name   : Query
        * Function        : query the parent and children of the person
        */
        void Query() const
        {
            my::string query_person;
            InputName(query_person, "要查询的人", Input::Exist);

            OutputParentAndChildren(Find(query_person));
        }

    public://constructor&destructor
        ~GenealogyManagementSystem()
        {
            m_root -> Release();
            delete m_root;
            m_root = nullptr;
        }

    public://external interfaces
        /*
        * Function Name   : Launch
        * Function        : launch the genealogy management system
        */
        void Launch()
        {
            cout << "+-------------------------------+" << endl;
            cout << "|         家谱管理系统          |"  << endl;
            cout << "|  Genealogy Management System  |" << endl;
            cout << "+-------------------------------+" << endl;

            cout << endl << ">>> 请建立家谱管理系统" << endl;
            cout << endl << ">>> [姓名输入要求] 不超过 " << KMaxNameLength << " 个英文字符或 " << KMaxNameLength / 2 << " 个汉字字符组成的字符串：" << endl;
            my::string ancester_name;
            InputName(ancester_name, "祖先", Input::New);
            m_root = new Person(ancester_name);
            cout << endl << ">>> 家谱建立成功！祖先是："  << m_root -> m_name << endl;

            while(true)
            {
                switch(SelectOption())
                {
                    case 1:
                        CompleteGenealgoy();
                        break;
                    case 2:
                        AddFamilyMember();
                        break;
                    case 3:
                        DeleteSubFamily();
                        break;
                    case 4:
                        ChangeName();
                        break;
                    case 5:
                        Query();
                        break;
                    case 6:
                        break;
                    default:
                        cerr << endl << ">>> Out of valid option!" << endl;
                        break;
                }
            }
        }
};

signed main()
{
    cout << ">>> Please use UTF-8 encoding to ensure the normal operation of the program" << endl;
    GenealogyManagementSystem genealogy_management_system;
    genealogy_management_system.Launch(); 
    return 0;
}