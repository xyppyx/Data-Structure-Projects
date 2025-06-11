/**********************************************
# Project Name : Exam_Registration_System
# File Name    : Exam_Registration_System.cpp
# File Function: implement an exam registration system
# Author       : YunPeng Xu(徐云鹏)
# Update Date  : 2024/9/26
**********************************************/

#include <iostream>
#include <climits>
#include <iomanip>
#include "MyString.h"
#include "MyDataStructure.h"

using std::cin;
using std::cout;
using std::cerr;
using std::endl;


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
        }//错误处理

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