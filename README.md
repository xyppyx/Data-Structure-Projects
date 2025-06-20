# 2024同济大学数据结构课程项目

本仓库包含数据结构课程的完整项目代码和相关文档。

## 项目结构

```
DataStructure/
├── CourseProject/          				    # 十个课程项目代码与课程论文
│   ├── (1)Exam_Registeration_System/         		    # 项目1代码
│   ├── (2)Find_Intersection/                 		    # 项目2代码
│   ├── (3)Maze_Game/                         		    # 项目3代码
│   ├── (4)Expression_Calculation/            		    # 项目4代码
│   ├── (5)Bank_Operatio/            			    # 项目5代码
│   ├── (6)Genealogy_Management_System/         	    # 项目6代码
│   ├── (7)Ranch_Repair/         			    # 项目7代码
│   ├── (8)Power_Grid_Construction_Cost_Simulation_System/  # 项目8代码
│   ├── (9)Key_Tasks/         			            # 项目9代码
│   ├── (10)Comparison_of_Sorting_Algorithms/         	    # 项目10代码
│   └── 2353583_徐云鹏_红黑树优化综述         		    # 课程论文
├── MyHeaderFile/                 			    # 自定义头文件实现
│   ├── MyDataStructure.h       	 		    # 常用数据结构头文件
│   └── MyString.h            		 		    # 字符串头文件
└── README.md              				    # 项目说明文档
```

## 项目介绍

### CourseProject 目录

包含十个完整的数据结构课程项目，每个项目都有：

- 完整的源代码实现
- 项目说明文档
- 测试用例
- 相关的课程论文和报告

主要项目类型包括：

- 线性表的应用
- 栈和队列的实现与应用
- 树结构的操作与遍历
- 图算法的实现
- 字典的实现与应用
- 排序和查找算法
- 综合性数据结构应用

注：为了项目便于批改，各项目目录下以编号-学号-姓名的cpp文件为整合了头文件的项目文件，以项目名命名的cpp文件为include头文件的项目文件。同时将所有数据结构整合到同一个MyDataStructure.h头文件中。

### MyHeaderFile 目录

包含自己实现的各种数据结构头文件，主要特点：

- **模块化设计**：按数据结构类型分类组织
- **完整实现**：包含基本操作和高级功能
- **注释详细**：每个函数都有详细的说明
- **可复用性**：可以在其他项目中直接使用

#### 主要头文件类别

- **SingleList**：单链表的实现
- **Vector**：vector的实现
- **Queue**：队列与双端队列的实现
- **Stack**：栈的实现
- **Map**：基于红黑树的字典实现
- **Heap**：大根堆与小根堆的实现

## 技术特点

- 使用C++语言实现
- 采用面向对象的设计思想
- 注重代码的可读性和可维护性
- 包含完整的测试用例
- 遵循良好的编程规范

## 学习价值

本项目适合：

- 数据结构课程学习参考
- 算法实现的学习材料
- C++编程实践的示例
- 软件工程思想的体现

---

*本项目为数据结构课程的学习成果，仅供学习交流使用。*
