// Sorting_algorithm.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include<ctime>

#define LineEnd 15
#define Array_length 100000
#define random(x) (rand()%(x))
//C++标准函数库提供一随机数生成器rand，返回0－RAND_MAX之间均匀分布的伪随机整数

using  namespace std;

clock_t startTime, endTime;




/*打印随机数组*/
template<typename T> void ArrayPrint(T A[], int n)
{
	cout << "数组长度：" << n << endl;
	if (n > 200) cout << "数组过长" << endl;
	else
	{
		for (int i = 0; i < abs(n); i++)
		{
			if (i > LineEnd - 1 && i % LineEnd == 0) cout << endl;
			cout << A[i] << "  ";
		}
		cout << endl;
	}

}

/*生成随机数组*/
 int* ArrayGen(int n, int mode=1)
{
	int *res = new int[n];
	if(mode == 2) //正序数组
	{
		for (int i = 0; i < abs(n); i++)
		{
			res[i] = i;
		}
	}
	else if (mode == 3) //逆序
	{
		for (int i = 0; i < abs(n); i++)
		{
			res[i] = n-i;
		}
	}
	else
	{
		for (int i = 0; i < abs(n); i++)
		{
			res[i] = random(n * 10);
		}
	}

	cout << "原始数组为：" << endl;
	ArrayPrint(res, n);
	return res;
}


/*直接插入排序的核心思想就是：将数组中的所有元素依次跟前面已经排好的元素相比较，
如果选择的元素比已排序的元素小，则交换，直到全部元素都比较过。*/
template<typename T> void InsertSort(T A[], int n) 
{
	for (int i = 0; i < n; i++)
	{
		T temp = A[i]; //记录当前值
		int j = i - 1;
		while (j >= 0 && A[j] > temp)
	//当前值依次和前面的比较,前面的都是排好序的
	//如果前一个值小于等于当前值，就没必要交换了
	//如果前一个值小于当前值，就交换两个数
		{
			A[j + 1] = A[j]; //如果前一个数较大，就把前一个数换到后一个的位置上
			j--; 
		}
		A[j+1] = temp;//j再减了一次，不满足条件，while退出了循环。也就是说赋值要在上一次循环，所以这里是j+1
	}
	cout << "插入排序后数组为：" << endl;
	ArrayPrint(A, n);
}



//将待排序数组按照步长gap进行分组，然后将每组的元素利用直接插入排序的方法进行排序；
//每次将gap折半减小，循环上述操作；当gap = 1时，利用直接插入，完成排序。
template<typename T> void ShellSort(T A[], int n)
{
	int gap = n / 2;//步长
	while (gap > 0)
	{
		for (int i = gap; i < n; i++)
		{
			T temp = A[i]; //记录当前值
			int j = i - 1;
			while (j >= 0 && A[j] > temp)
				//当前值依次和前面的比较,前面的都是排好序的
				//如果前一个值小于等于当前值，就没必要交换了
				//如果前一个值小于当前值，就交换两个数
			{
				A[j + 1] = A[j]; //如果前一个数较大，就把前一个数换到后一个的位置上
				j--;
			}
			A[j + 1] = temp;//j再减了一次，不满足条件，while退出了循环。也就是说赋值要在上一次循环，所以这里是j+1
		}
		gap /= 2;
	}
	cout << "希尔排序后数组为：" << endl;
	ArrayPrint(A, n);
}



//在长度为N的无序数组中，第一次遍历n - 1个数，找到最小的数值与第一个元素交换；
//第二次遍历n - 2个数，找到最小的数值与第二个元素交换；
//。。。
//第n - 1次遍历，找到最小的数值与第n - 1个元素交换，排序完成。
template<typename T> void SelectSort(T A[], int n)
{
	int loc = 0;
	T min_num = A[0],tmp = 0;
	int i = 1;
	while (i < n)
	{
		for (int j = i; j < n; j++)//找最小的数
		{
			if (A[j] < A[loc])
				loc = j; //记录这个数的下标，这样就可以知道它的位置和它的数值
			else  continue;
		}

		if (A[loc]<A[i-1])//将最小值，与当前元素交换
		{
			tmp = A[i-1];
			A[i-1] = A[loc];
			A[loc] = tmp;
		}
		i++;
	}
	cout << "选择排序后数组为：" << endl;
	ArrayPrint(A, n);
}

/*
堆排序
HeapSort(A, sizeof(A) / sizeof(int) - 1, fMax); //使用大顶堆进行升序排序
HeapSort(A, sizeof(A) / sizeof(int) - 1, fMin);//使用小顶堆进行降序排序
*/

template<typename T> bool fMax(const T& a, const T& b)
{
	return a >= b;
}

template<typename T> bool fMin(const T& a, const T& b)
{
	return a <= b;
}

//将子序列（下标范围：k~size）调整为（大/小）顶堆
template<typename T> void Sift(T A[], int k, int size, bool(*compare)(const T&, const T&))
{
	T x = A[k];    //k是待调整的子树的根
	int i = k;     //i指示空位
	int j = 2 * i;   //j是i的左孩子
	bool fininshed = false;
	while (j <= size && !fininshed)
	{
		//让j指向i的左右孩子中的较（大/小）者
		if (j < size && !compare(A[j], A[j + 1])) j = j + 1;

		//如果根最（大/小）则直接结束
		if (compare(x, A[j])) fininshed = true;
		//否则，孩子节点比根节点（大/小）
		else
		{
			A[i] = A[j];   //（大/小）的孩子节点上移
			//继续往下筛选
			i = j;
			j = 2 * i;
		}
	}
	A[i] = x;
}

//通过（大/小）顶堆对数组A进行（升/降）序排序，数据存放在下标1~n；实际上数组尺寸为n+1，这样做是为了便于二叉树的处理，使得根节点的下标为1
template<typename T> void HeapSort(T A[], int n, bool(*compare)(const T&, const T&))
{
	//构建初始堆
	for (int i = n / 2; i > 0; i--)
	{
		Sift(A, i, n, compare);
	}

	for (int i = n; i > 1; i--)
	{
		T x = A[1];    //输出根
		A[1] = A[i];   //交换当前最后一个元素和根的值
		A[i] = x;
		Sift(A, 1, i - 1, compare);  //调整子序列为堆
	}
	cout << "堆排序后数组为：" << endl;
	ArrayPrint(A, n+1);
}

/*
1.比较相邻的两个数据，如果第二个数小，就交换位置。
2.从后向前两两比较，一直到比较最前两个数据。最终最小数被交换到起始的位置，这样第一个最小数的位置就排好了。
3.继续重复上述过程，依次将第2.3...n-1个最小数排好位置。
*/
template<typename T> void BubbleSort(T A[], int n)
{
	T temp = A[0];
	bool exchange = true;
	for (int i = 0; i < n && exchange; i++)
	{
		exchange = false; //如果第一轮没有发生交换，说明数组已经是正序了。
		for (int j = n - 1; j > i; j--)
		{
			if (A[j] < A[j - 1])
			{
				temp = A[j];
				A[j] = A[j - 1];
				A[j - 1] = temp;
				exchange = true;
			}
		}
	}
	cout << "冒泡排序后数组为：" << endl;
	ArrayPrint(A, n);
}

/*
基本思想：
 将数据划分为两部分，左边的所有元素都小于右边的所有元素；然后，对左右两边进行快速排序。
 划分方法：
 选定一个参考点（中间元素），所有元素与之相比较，小的放左边，大的放右边。
 */
template<typename T> void QuickSort(T A[] , int left, int right)
{
	T mid = A[(left + right) / 2]; //选取数组的中间元素作为划分的基准	
	T temp = mid;
	int i = left, j = right;
	//if (left == 0) cout << "左边快排" << endl;
	//if (right == Array_length - 1) cout << "右边快排" << endl;
	//cout << mid << endl;
	while (i < j)
	{
		while (A[i] < mid) i++; //从左开始搜素，找到大于中间元素的位置
		while (A[j] > mid) j--;//从右开始搜索，找到小于中间元素的位置
		//为什么while里面不能加等号，不加等号，是因为中间元素有可能过大或者过下。
		//这样搜索到中间元素的时候，可以把它交换出去，让一个适中的元素进来

		if (i <= j) //找到一组，交换这两个位置
		//if (i < j)  //为什么i<j就不行，程序无法运行
		{
			
			temp = A[j];
			A[j] = A[i];
			A[i] = temp;
			//交换完成后，ij位置上的数就符合条件了，于是让其自增
			i++;
			j--;
			//自加后进行第二轮搜索
			
			//std::swap(A[i++], A[j--]);
		}
	}
	if (i < right) QuickSort(A, i, right);
	if (j > left) QuickSort(A, left, j);


	//cout << "快速排序后数组为：" << endl;
	//ArrayPrint(A, Array_length);

}


/*
基本思想：
 是指将两个或两个以上的有序表合并成一个新的有序表。
 利用归并的思想进行排序：
1.首先将整个表看成是n个有序子表，每个子表的长度为1；
2.然后两两归并，得到n/2个长度为2的有序子表；
3.然后再两两归并,直至得到一个长度为n的有序表为止。

归并排序是建立在归并操作上的一种有效的排序算法。该算法是采用分治法的一个非常典型的应用。
首先考虑下如何将2个有序数列合并。
这个非常简单，只要从比较2个数列的第一个数，谁小就先取谁，取了后就在对应数列中删除这个数。
然后再进行比较，如果有数列为空，那直接将另一个数列的数据依次取出即可。
*/
//合并数组A中以a和b开始的长度为step的两个子序列，n为整个数组的长度
template<typename T> void Merge(T A[], int start, int mid, int step, int n)
{
	//两个子序列
	//start ->start+step //第一个子序列不会超界
	//mid ->mid+step    //第二个子序列有超界的风险
	int rightLen = 0;
	if (mid + step > n)
	{
		rightLen = n - mid;
	}
	else
	{
		rightLen = step;
	}
	//申请空间存放临时结果
	T *tempArray = new T[step + rightLen]();
	int i = 0, j = 0, k = 0;
	while (i < step && j < rightLen)
	{
		if (A[start + i] < A[mid + j])
		{
			tempArray[k++] = A[start + i];
			i++;
		}
		else
		{
			tempArray[k++] = A[mid + j];
			j++;
		}
	}
	//如果左边没有归并完，那么直接将剩余的元素复制到tempArray的后面
	if (j == rightLen)
	{
		memcpy(tempArray + i + j, A + start + i, (step - i) * sizeof(T));
	}
	//如果右边没有归并完，那么直接将剩余的元素复制到tempArray的后面
	else if (i == step)
	{
		memcpy(tempArray + i + j, A + mid + j, (rightLen - j) * sizeof(T));
	}
	//将临时数组中排好序的内容复制回原数组
	memcpy(A + start, tempArray, (step + rightLen) * sizeof(T));
	delete[] tempArray;
}
template<typename T> void MergeSort(T A[], int n)
{
	for (int step = 1; step < n; step *= 2)
	{
		for (int i = 0; i < n - step; i += 2 * step)//依次合并表中相邻的子表
		{
			Merge(A, i, i + step, step, n);
		}
	}
	cout << "归并排序后数组为：" << endl;
	ArrayPrint(A, n);
}

int main()
{
	startTime = clock();//计时开始

	MergeSort(ArrayGen(Array_length), Array_length);
	//HeapSort(ArrayGen(Array_length), Array_length - 1, fMax);//有问题
	//QuickSort(ArrayGen(Array_length), 0, Array_length - 1);

	endTime = clock();//计时结束
	cout << "The run time is:" << (double)(endTime - startTime)  << "ms" << endl;
	//cout << "The run time is:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	//这是因为clock()是以毫秒为单位，要正确输出时间差需要把它换成秒，因此需要除以CLOCKS_PER_SEC。
	
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
