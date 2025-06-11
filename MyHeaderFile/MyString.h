                                                                                                                                                                                                                                                                                                                                                                                                                                                    /**********************************************
# Project Name : MyHeaderFile
# File Name    : MyString.h
# File Function: provide my own string class
# Author       : YunPeng Xu(徐云鹏)
# Update Date  : 2024/9/19   
**********************************************/

#pragma once
#pragma execution_character_set("utf-8")
#include<iostream>
#include<cstring>

namespace my
{

// TODO : add a move constructor
// TODO : add a move assignment operator
// TODO : add exception handling
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

}
