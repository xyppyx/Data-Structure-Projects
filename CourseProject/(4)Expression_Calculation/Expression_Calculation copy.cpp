/**********************************************
# Project Name : Expression_Converter
# File Name    : Expression_Converter.cpp
# File Function: change the expression to postfix infix and prefix expression, and calculate the answer
# Author       : YunPeng Xu(徐云鹏)
# Update Date  : 2024/10/9
**********************************************/

#include<iostream>
#include<cstring>
#include<sstream>
#include"MyDataStructure.h"
#include"MyString.h"

using std::cin;
using std::cout;
using std::endl;
using std::cerr;
using std::istringstream;

class ExpressionConverter
{
    private://members
        enum class Type{prefix, infix, postfix, unknown};
        //the node of the expression tree
        struct Node
        {
            my::string data;
            Node* left;
            Node* right;

            Node(const my::string& data)
            {
                this -> data = data;
                left = nullptr;
                right = nullptr;
            }
            
            Node()
            {
                this -> data = my::string();
                left = nullptr;
                right = nullptr;
            }

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
        };

        //the pointer to the root of the expression tree
        Node* m_root;
        my::string m_expression;
        double m_expression_ans;
        Type m_type;

    private://internal functions
        /*
        * Function Name   : OperatorPriority
        * Function        : get the priority of the operator
        * Input Parameters: const my::string& - the operator
        * Return Value    : int - the priority of the operator
        */
        int OperatorPriority(const my::string& str) const
        {
            if(str == "+" || str == "-")
                return 1;
            else if(str == "*" || str == "/")
                return 2;
            else
                return 0;
        }

        /*
        * Function Name   : IsOperator
        * Function        : check if the my::string is an operator
        * Input Parameters: const my::string& - the my::string
        * Return Value    : bool - if the my::string is an operator
        */
        bool IsOperator(const my::string& str) const
        {
            return (str == "+" || str == "-" || str == "*" || str == "/");
        }

        /*
        * Function Name   : GetInfixOutput
        * Function        : serve as a recursive function to get the infix expression
        * Input Parameters: Node* - the root of the subtree
        *                   my::string& - the infix expression
        *                   int - the priority of the parent node
        */
        void GetInfixOutput(Node* node, my::string& infix_expression, int parent_precedence = 0) const
        {
            if (node == nullptr)
                return;

            bool need_parentheses = IsOperator(node -> data) && OperatorPriority(node -> data) < parent_precedence;

            if (need_parentheses)
                infix_expression += "( ";

            GetInfixOutput(node -> left, infix_expression, OperatorPriority(node -> data));

            infix_expression += node -> data;
            infix_expression += " ";

            GetInfixOutput(node -> right, infix_expression, OperatorPriority(node -> data));

            if (need_parentheses)
                infix_expression += ") ";
        }

        /*
        * Function Name   : GetPrefixOutput
        * Function        : serve as a recursive function to get the prefix expression
        * Input Parameters: Node* - the root of the tree
        *                   my::string& - the prefix expression
        */
        void GetPrefixOutput(Node* node, my::string& prefix_expression) const
        {
            if(node == nullptr)
                return;

            prefix_expression += node -> data;
            prefix_expression += " ";
            GetPrefixOutput(node -> left, prefix_expression);
            GetPrefixOutput(node -> right, prefix_expression);
        }

        /*
        * Function Name   : TypeDetection
        * Function        : detect the type of the expression
        * Return Value    : Type - the type of the expression
        */
        Type TypeDetection() const
        {
            istringstream iss(m_expression.c_str());
            my::string token;
            iss >> token;
            if(IsOperator(token))
                return Type::prefix;
            else
            {
                while(iss >> token){};
                if(IsOperator(token))
                    return Type::postfix;
                else
                    return Type::infix;
            }
            return Type::infix;
        }

        /*
        * Function Name   : RemoveAdd
        * Function        : remove the "+" in the my::string
        * Input Parameters: const my::string& - the my::string
        * Return Value    : my::string - the my::string without "+"
        */
        my::string RemoveAdd(const my::string& str) const
        {
            if(str[0] == '+')
                return str.substr(1);
            else
                return str;
        }

        /*
        * Function Name   : BuildTree
        * Function        : build the expression tree based on the type of the expression and renew m_root
        */
        void BuildTree()
        {
            istringstream iss(m_expression.c_str());
            my::string token;

            if(m_type == Type::prefix)
            {
                my::stack<Node*> nodes;
                my::vector<my::string> tokens;
                while(iss >> token)
                    tokens.push_back(token);
                
                //build the tree from right to left
                for(auto it = tokens.rbegin(); it != tokens.rend(); ++it)
                {
                    token = *it;
                    if(IsOperator(token))
                    {
                        Node* node = new Node(token);
                        node -> left = nodes.top();
                        nodes.pop();
                        node -> right = nodes.top();
                        nodes.pop();
                        nodes.push(node);
                    }
                    else
                    {
                        token = RemoveAdd(token);
                        Node* node = new Node(token);
                        nodes.push(node);
                    }
                }

                m_root = nodes.top();
            }
            else if(m_type == Type::infix)
            {
                my::stack<my::string> operators;
                my::stack<Node*> operands;

                while(iss >> token)
                {
                    if(token == "(")
                    {
                        operators.push(token);
                    }
                    else if(token == ")")
                    {
                        //find the nearest "("
                        while(!operators.empty() && operators.top() != "(")
                        {
                            my::string op = operators.top();
                            operators.pop();
                            Node* node = new Node(op);
                            node -> right = operands.top();
                            operands.pop();
                            node -> left = operands.top();
                            operands.pop();
                            operands.push(node);
                        }
                        //pop the "("
                        operators.pop();
                    }
                    else if(IsOperator(token))
                    {
                        while(!operators.empty() && OperatorPriority(token) < OperatorPriority(operators.top()))
                        {
                            my::string op = operators.top();
                            operators.pop();
                            Node* node = new Node(op);
                            node->right = operands.top();
                            operands.pop();
                            node->left = operands.top();
                            operands.pop();
                            operands.push(node);
                        }
                        operators.push(token);
                    }
                    else
                    {
                        token = RemoveAdd(token);
                        Node* node = new Node(token);
                        operands.push(node);
                    }
                }

                while(!operators.empty())
                {
                    my::string op = operators.top();
                    operators.pop();
                    Node* node = new Node(op);
                    node -> right = operands.top();
                    operands.pop();
                    node->left = operands.top();
                    operands.pop();
                    operands.push(node);
                }

                m_root = operands.top();
            }
            else if(m_type == Type::postfix)
            {
                my::stack<Node*> operands;

                while(iss >> token)
                {
                    if(IsOperator(token))
                    {
                        Node* node = new Node(token);
                        node -> right = operands.top();
                        operands.pop();
                        node -> left = operands.top();
                        operands.pop();
                        operands.push(node);
                    }
                    else
                    {
                        token = RemoveAdd(token);
                        Node* node = new Node(token);
                        operands.push(node);
                    }
                }

                m_root = operands.top();
            }
        }

        /*
        * Function Name   : Calculate
        * Function        : calculate the expression and renew m_expression_ans
        * Return Value    : double - the answer of the expression
        */
        double Calculate()
        {
            if(m_root == nullptr)
                return 0;

            my::stack<Node*> nodes;
            my::stack<Node*> output;
            my::stack<double> values;
            Node* cur = m_root;

            nodes.push(cur);
            while(!nodes.empty())
            {
                cur = nodes.top();
                nodes.pop();
                output.push(cur);

                if(cur -> left)
                    nodes.push(cur -> left);
                if(cur -> right)
                    nodes.push(cur -> right);
            }

            while(!output.empty())
            {
                cur = output.top();
                output.pop();

                if(IsOperator(cur -> data))
                {
                    double right = values.top();
                    values.pop();
                    double left = values.top();
                    values.pop();
                    if(cur -> data == "+")
                        values.push(left + right);
                    else if(cur -> data == "-")
                        values.push(left - right);
                    else if(cur -> data == "*")
                        values.push(left * right);
                    else if(cur -> data == "/")
                        values.push(left / right);
                }
                else
                {
                    values.push(std::stod(cur -> data.c_str()));
                }
            }

            return values.top();
        }

    public://constructor and destructor
        ExpressionConverter() : m_root(nullptr), m_expression(my::string()), m_expression_ans(0), m_type(Type::unknown) {}

        ExpressionConverter(const my::string& expression) : m_root(nullptr), m_expression(expression), m_expression_ans(0)
        {
            m_expression = expression;
            m_type = TypeDetection();
            BuildTree();
            m_expression_ans = Calculate();
        }

        ~ExpressionConverter()
        {
            clear();
        }

    public://external interfaces
        /*
        * Function Name   : Assign
        * Function        : assign a new expression to the object
        * Input Parameters: const my::string& - the new expression
        */
        void Assign(const my::string& expression)
        {
            clear();
            m_expression = expression;
            m_type = TypeDetection();
            BuildTree();
            m_expression_ans = Calculate();
        }   

        /*
        * Function Name   : clear
        * Function        : clear the expression stored in the object
        */
        void clear()
        {
            if(m_root != nullptr)
            {
                m_root -> Release();
                delete m_root;
                m_root = nullptr;
                m_expression = my::string();
                m_expression_ans = 0;
                m_type = Type::unknown;
            }
        }

        /*
        * Function Name   : expression
        * Function        : get the expression
        * Return Value    : my::string - the expression
        */
        const my::string expression() const
        {
            return m_expression;
        }

        /*
        * Function Name   : prefix
        * Function        : get the prefix expression
        * Return Value    : my::string - the prefix expression
        */
        const my::string prefix() const
        {
            if(m_root == nullptr)
                return ">>> The expression is empty!";

            my::string prefix_expression;
            //use the recursive function to get the prefix expression
            GetPrefixOutput(m_root, prefix_expression);

            return prefix_expression; 
        }

        /*
        * Function Name   : infix
        * Function        : get the infix expression
        * Return Value    : my::string - the infix expression
        */
        const my::string infix() const
        {
            if(m_root == nullptr)
                return ">>> The expression is empty!";

            my::string infix_expression;
            //use the recursive function to get the infix expression
            GetInfixOutput(m_root, infix_expression);

            infix_expression.pop_back();
            return infix_expression;
        }

        /*
        * Function Name   : postfix
        * Function        : get the postfix expression
        * Return Value    : my::string - the postfix expression
        */
        my::string postfix() const
        {
            if(m_root == nullptr)
                return ">>> The expression is empty!";

            my::string postfix_expression;
            my::stack<Node*> nodes;//root -> left -> right 
            my::stack<Node*> output;//left -> right -> root
            Node* cur = m_root;

            nodes.push(cur);
            while (!nodes.empty())
            {
                cur = nodes.top();
                nodes.pop();
                output.push(cur);

                if (cur -> left)
                    nodes.push(cur -> left);
                if (cur -> right)
                    nodes.push(cur -> right);
            }

            while (!output.empty())
            {
                cur = output.top();
                output.pop();
                postfix_expression += cur->data;
                postfix_expression += " ";
            }

            postfix_expression.pop_back();

            return postfix_expression;
        }

        /*
        * Function Name   : ans
        * Function        : get the answer of the expression
        * Return Value    : double - the answer of the expression
        */
        double ans()
        {
            return m_expression_ans;
        }

        /*
        * Function Name   : type
        * Function        : get the type of the expression
        * Return Value    : my::string - the type of the expression
        */ 
        my::string type()
        {
            if(m_type == Type::prefix)
                return "prefix";
            else if(m_type == Type::infix)
                return "infix";
            else if(m_type == Type::postfix)
                return "postfix";
            else
                return "unknown";
        }
};

signed main()
{
    cout<<">>> Please input the expression, divided by space :"<<endl;
    my::string infix;
    infix.getline(cin);

    ExpressionConverter converter(infix);
    cout << endl << ">>> The type of expression is :" << endl << converter.type() << endl;
    cout << endl << ">>> The prefix expression is :" << endl << converter.prefix() << endl;
    cout << endl << ">>> The infix expression is :" << endl << converter.infix() << endl;
    cout << endl << ">>> The postfix expression is :" << endl << converter.postfix() << endl;
    cout << endl << ">>> The answer of the expression is :" << endl << converter.ans() << endl;

    return 0;
}