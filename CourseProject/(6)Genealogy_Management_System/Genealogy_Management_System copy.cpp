/**********************************************
# Project Name : Genealogy_Management_System
# File Name    : Genealogy_Management_System.cpp
# File Function: implement a genealogy management system
# Author       : YunPeng Xu(徐云鹏)
# Update Date  : 2024/10/12
**********************************************/

#include<iostream>
#include<sstream>
#include"MyString.h"
#include"MyDataStructure.h"

using std::cin;
using std::cout;
using std::endl;
using std::cerr;

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