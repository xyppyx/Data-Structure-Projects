/**********************************************
# Project Name : Find_Intersection
# File Name    : Find_Intersection.cpp
# File Function: find the intersection of 2 sorted linked lists
# Author       : YunPeng Xu(徐云鹏)
# Update Date  : 2024/9/27
**********************************************/

#include<iostream>
#include "MyDataStructure.h"

using std::cin;
using std::cout;
using std::endl;
using std::cerr;


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