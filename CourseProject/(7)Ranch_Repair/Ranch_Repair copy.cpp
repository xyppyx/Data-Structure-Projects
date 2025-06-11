/**********************************************
# Project Name : Ranch_Repair
# File Name    : Ranch_Repair.cpp
# File Function: solve the problem
# Author       : YunPeng Xu(徐云鹏)
# Update Date  : 2024/10/9
**********************************************/

#include<iostream>
#include"MyDataStructure.h"

using std::cin;
using std::cout;
using std::endl;
using std::cerr;
using my::heap;

class RanchRepair
{
    private://members
        //create a min heap
        heap<int, my::greater<int>> fences;
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