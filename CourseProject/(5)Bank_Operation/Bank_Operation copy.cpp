/**********************************************
# Project Name : Bank_Operation
# File Name    : Bank_Operation.cpp
# File Function: simulate the operation of a bank
# Author       : YunPeng Xu(徐云鹏)
# Update Date  : 2024/10/9
**********************************************/

#include<iostream>
#include"MyDataStructure.h"

using std::cin;
using std::cout;
using std::endl;
using std::cerr;

class BankOperation
{
    private://members
        my::queue<int> counter_A, counter_B;
        int customer_num;
    
    public://external interface
        /*
        * Function Name   : Input
        * Function        : input the number of customers and the sequence of customers
        */
        void Input()
        {
            while(true)
            {
                cout<<">>> Please input the number of customers:"<<endl;
                cin >> customer_num;
                if(customer_num <= 0 || cin.fail())
                {
                    cerr << endl << ">>> Invalid input, please input again!" << endl;
                    continue;
                }

                cout<<">>> Please input the sequence of customers, divided by space:"<<endl;
                for(int i = 1; i <= customer_num; i++)
                {
                    int temp;
                    cin >> temp;
                    if(temp < 0 || cin.fail())
                    {
                        cerr << endl << ">>> Invalid input, please input the" << i << "th customer again!" << endl;
                        cin.clear();
                        cin.ignore(1024, '\n');
                        --i;
                        continue;
                    }
                    else if(temp % 2 == 1)
                        counter_A.push_back(temp);
                    else
                        counter_B.push_back(temp);
                }
                break;
            }
            cout << ">>> Input successfully!" << endl << endl;
        }

        /*
        * Function Name   : Solve   
        * Function        : solve the problem
        */
        void Solve()
        {
            Input();
            cout << ">>> The sequence of customers is:" << endl;
            while(!counter_A.empty() && !counter_B.empty())
            {
                //the first customer of counter A
                cout<<counter_A.front()<<" ";
                counter_A.pop_front();
                //the second customer of counter A
                if(!counter_A.empty())
                {
                    cout<<counter_A.front()<<" ";
                    counter_A.pop_front();
                }
                //the first customer of counter B
                cout<<counter_B.front()<<" ";
                counter_B.pop_front();
            }

            if(!counter_A.empty())
            {
                while(!counter_A.empty())
                {
                    cout<<counter_A.front()<<" ";
                    counter_A.pop_front();
                }
            }
            else if(!counter_B.empty())
            {
                while(!counter_B.empty())
                {
                    cout<<counter_B.front()<<" ";
                    counter_B.pop_front();
                }
            }
        }
        
};

signed main()
{
    BankOperation solution;
    solution.Solve();

    return 0;
}