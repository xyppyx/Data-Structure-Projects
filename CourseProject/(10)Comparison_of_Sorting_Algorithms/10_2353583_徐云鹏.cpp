#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <climits>
#include <vector>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;

/*
* Function Name   : GenerateRandomNumbers
* Function        : generate random numbers and store them in the vector
* Input Parameters: vector<int>& - the vector to store the random numbers
*                   int - the number of random numbers to generate
*/
void GenerateRandomNumbers(vector<int>& nums, int n) 
{
    srand((unsigned)time(0));
    for (int i = 0; i < n; ++i)
        nums[i] = rand() % 100000;
}

/*
* Function Name   : BubbleSort
* Function        : sort the vector using bubble sort
* Input Parameters: vector<int>& - the vector to sort
*                   long long& - the number of swaps
*                   long long& - the number of comparisons
*/
void BubbleSort(vector<int>& nums, long long& swap_num, long long& comparison_num) 
{
    int n = nums.size();
    bool is_swapped;
    for (int i = 0; i < n - 1; i++) 
    {
        is_swapped = false;
        for (int j = 0; j < n - i - 1; j++) 
        {
            comparison_num++;
            if (nums[j] > nums[j + 1]) 
            {
                std::swap(nums[j], nums[j + 1]);
                swap_num++;
                is_swapped = true;
            }
        }
        if (!is_swapped)
            break;
    }
}

/*
* Function Name   : SelectionSort
* Function        : sort the vector using selection sort
* Input Parameters: vector<int>& - the vector to sort
*                   long long& - the number of swaps
*                   long long& - the number of comparisons
*/
void SelectionSort(vector<int>& nums, long long& swap_num, long long& comparison_num) 
{
    int n = nums.size();
    for (int i = 0; i < n - 1; i++) 
    {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) 
        {
            comparison_num++;
            if (nums[j] < nums[min_idx]) 
                min_idx = j;
        }
        if (min_idx != i) 
        {
            std::swap(nums[i], nums[min_idx]);
            swap_num++;
        }
    }
}

/*
* Function Name   : InsertionSort
* Function        : sort the vector using insertion sort
* Input Parameters: vector<int>& - the vector to sort
*                   long long& - the number of swaps
*                   long long& - the number of comparisons
*/
void InsertionSort(vector<int>& nums, long long& swap_num, long long& comparison_num) 
{
    int n = nums.size();
    for (int i = 1; i < n; i++) 
    {
        int key = nums[i];
        int j = i - 1;
        while (j >= 0 && nums[j] > key) 
        {
            comparison_num++;
            nums[j + 1] = nums[j];
            swap_num++; 
            j--;
        }
        comparison_num++;
        nums[j + 1] = key;
    }
}

/*
* Function Name   : ShellSort
* Function        : sort the vector using shell sort
* Input Parameters: vector<int>& - the vector to sort
*                   long long& - the number of swaps
*                   long long& - the number of comparisons
*/
void ShellSort(vector<int>& nums, long long& swap_num, long long& comparison_num) 
{
    int n = nums.size();
    for (int gap = n / 2; gap > 0; gap /= 2) 
    {
        for (int i = gap; i < n; i++) 
        {
            int temp = nums[i];
            int j;
            for (j = i; j >= gap && nums[j - gap] > temp; j -= gap) 
            {
                comparison_num++;
                nums[j] = nums[j - gap];
                swap_num++;
            }
            comparison_num++;
            nums[j] = temp;
            if (i != j) swap_num++;
        }
    }
}

/*
* Function Name   : Partition
* Function        : partition the vector
* Input Parameters: vector<int>& - the vector to partition
*                   int - the low index
*                   int - the high index
*                   long long& - the number of swaps
*                   long long& - the number of comparisons
* Return Value    : int - the partition index
*/
int Partition(vector<int>& nums, int low, int high, long long& swap_num, long long& comparison_num) 
{
    int pivot = nums[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) 
    {
        comparison_num++;
        if (nums[j] < pivot) 
        {
            i++;
            std::swap(nums[i], nums[j]);
            swap_num++;
        }
    }
    std::swap(nums[i + 1], nums[high]);
    swap_num++;
    return (i + 1);
}

/*
* Function Name   : QuickSort
* Function        : sort the vector using quick sort
* Input Parameters: vector<int>& - the vector to sort
*                   int - the low index
*                   int - the high index
*                   long long& - the number of swaps
*                   long long& - the number of comparisons
*/
void QuickSort(vector<int>& nums, int low, int high, long long& swap_num, long long& comparison_num) 
{
    if (low < high) 
    {
        int mid = Partition(nums, low, high, swap_num, comparison_num);
        QuickSort(nums, low, mid - 1, swap_num, comparison_num);
        QuickSort(nums, mid + 1, high, swap_num, comparison_num);
    }
}

/*
* Function Name   : Heapify
* Function        : heapify the vector
* Input Parameters: vector<int>& - the vector to heapify
*                   int - the size of the heap
*                   int - the index of the root
*                   long long& - the number of swaps
*                   long long& - the number of comparisons
*/
void Heapify(vector<int>& nums, int n, int i, long long& swap_num, long long& comparison_num) 
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && nums[l] > nums[largest]) {

        comparison_num++;
        largest = l;
    }

    if (r < n && nums[r] > nums[largest]) 
    {
        comparison_num++;
        largest = r;
    }

    if (largest != i) 
    {
        std::swap(nums[i], nums[largest]);
        swap_num++;
        Heapify(nums, n, largest, swap_num, comparison_num);
    }
}

/*
* Function Name   : HeapSort
* Function        : sort the vector using heap sort
* Input Parameters: vector<int>& - the vector to sort
*                   long long& - the number of swaps
*                   long long& - the number of comparisons
*/
void HeapSort(vector<int>& nums, long long& swap_num, long long& comparison_num) 
{
    int n = nums.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        Heapify(nums, n, i, swap_num, comparison_num);
    for (int i = n - 1; i > 0; i--) 
    {
        std::swap(nums[0], nums[i]);
        swap_num++;
        Heapify(nums, i, 0, swap_num, comparison_num);
    }
}

/*
* Function Name   : Merge
* Function        : merge the two subvectors
* Input Parameters: vector<int>& - the vector to merge
*                   int - the low index
*                   int - the middle index
*                   int - the high index
*                   long long& - the number of swaps
*                   long long& - the number of comparisons
*/
void Merge(vector<int>& nums, int l, int m, int r, long long& swap_num, long long& comparison_num) 
{
    int n1 = m - l + 1;
    int n2 = r - m;
    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = nums[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = nums[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) 
    {
        comparison_num++;
        if (L[i] <= R[j]) 
        {
            nums[k] = L[i];
            i++;
        }
        else 
        {
            nums[k] = R[j];
            j++;
        }
        swap_num++;
        k++;
    }

    while (i < n1) 
    {
        nums[k] = L[i];
        i++;
        k++;
        swap_num++;
    }

    while (j < n2) 
    {
        nums[k] = R[j];
        j++;
        k++;
        swap_num++;
    }
}

/*
* Function Name   : MergeSort
* Function        : sort the vector using merge sort
* Input Parameters: vector<int>& - the vector to sort
*                   int - the low index
*                   int - the high index
*                   long long& - the number of swaps
*                   long long& - the number of comparisons
*/
void MergeSort(vector<int>& nums, int l, int r, long long& swap_num, long long& comparison_num) 
{
    if (l >= r) 
        return;
    int m = l + (r - l) / 2;
    MergeSort(nums, l, m, swap_num, comparison_num);
    MergeSort(nums, m + 1, r, swap_num, comparison_num);
    Merge(nums, l, m, r, swap_num, comparison_num);
}

/*
* Function Name   : GetMax
* Function        : get the maximum element in the vector
* Input Parameters: vector<int>& - the vector to get the maximum element
* Return Value    : int - the maximum element
*/
int GetMax(vector<int>& nums) 
{
    int mx = nums[0];
    for (int i = 1; i < nums.size(); i++)
        if (nums[i] > mx)
            mx = nums[i];
    return mx;
}

/*
* Function Name   : CountSort
* Function        : sort the vector using count sort
* Input Parameters: vector<int>& - the vector to sort
*                   int - the exponent
*                   long long& - the number of swaps
*                   long long& - the number of comparisons
*/
void CountSort(vector<int>& nums, int exp, long long& swap_num, long long& comparison_num) 
{
    int n = nums.size();
    vector<int> output(n);
    int i, count[10] = { 0 };

    for (i = 0; i < n; i++)
        count[(nums[i] / exp) % 10]++;

    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (i = n - 1; i >= 0; i--) {
        output[count[(nums[i] / exp) % 10] - 1] = nums[i];
        count[(nums[i] / exp) % 10]--;
        swap_num++;
    }

    for (i = 0; i < n; i++)
        nums[i] = output[i];
}

/*
* Function Name   : RadixSort
* Function        : sort the vector using radix sort
* Input Parameters: vector<int>& - the vector to sort
*                   long long& - the number of swaps
*                   long long& - the number of comparisons
*/
void RadixSort(vector<int>& nums, long long& swap_num, long long& comparison_num) 
{
    int m = GetMax(nums);
    for (int exp = 1; m / exp > 0; exp *= 10)
        CountSort(nums, exp, swap_num, comparison_num);
}

int main() 
{
    const char* prompt[] = {nullptr, "冒泡排序", "选择排序", "直接插入排序", "希尔排序", "快速排序", "堆排序", "归并排序", "基数排序"};
    cout << "=============================================" << endl;
    cout << "**             八种排序算法比较            **" << endl;
    cout << "=============================================" << endl;
    cout << "**             1---冒泡排序                **" << endl;
    cout << "**             2---选择排序                **" << endl;
    cout << "**             3---直接插入排序            **" << endl;
    cout << "**             4---希尔排序                **" << endl;
    cout << "**             5---快速排序                **" << endl;
    cout << "**             6---堆排序                  **" << endl;
    cout << "**             7---归并排序                **" << endl;
    cout << "**             8---基数排序                **" << endl;
    cout << "**             9---退出程序                **" << endl;
    cout << "=============================================" << endl;
    cout << endl;

    int n;
    cout << endl << ">>> 请输入随机数的个数: " << endl;
    cin >> n;

    while (true) 
    {
        int choice;
        cout << endl << ">>> 输入选择 (1-9): " << endl;
        cin >> choice;

        if (choice == 9) break;
        if (cin.fail() || choice < 1 || choice>9)
        {
            cin.clear();
            cin.ignore(1024, '\n');
            cout << endl << ">>> 输入错误，请重新输入!" << endl;
            continue;
        }
    
        vector<int> nums(n);
        //generate random numbers
        GenerateRandomNumbers(nums, n);

        long long swap_num = 0;
        long long comparison_num = 0;
        //start timing
        auto start = std::chrono::high_resolution_clock::now();

        switch (choice) 
        {
            case 1:
                BubbleSort(nums, swap_num, comparison_num);
                break;
            case 2:
                SelectionSort(nums, swap_num, comparison_num);
                break;
            case 3:
                InsertionSort(nums, swap_num, comparison_num);
                break;
            case 4:
                ShellSort(nums, swap_num, comparison_num);
                break;
            case 5:
                QuickSort(nums, 0, nums.size() - 1, swap_num, comparison_num);
                break;
            case 6:
                HeapSort(nums, swap_num, comparison_num);
                break;
            case 7:
                MergeSort(nums, 0, nums.size() - 1, swap_num, comparison_num);
                break;
            case 8:
                RadixSort(nums, swap_num, comparison_num);
                break;
            case 9:
                break;
            default:
                cout << endl << ">>> 无效选择!" << endl;
                break;
        }

        //stop timing
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

        cout << endl << ">>> " << prompt[choice] << "排序用时（微秒）: " << duration.count();
        cout << endl << ">>> " << prompt[choice] << "交换次数: " << swap_num;
        cout << endl << ">>> " << prompt[choice] << "比较次数: " << comparison_num << endl << endl;
    }

    return 0;
}

