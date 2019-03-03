#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MAXSIZE  10
void InsertSort(int arr[],int len)
{
	int tmp = 0;//临时量记录有序序列的值
	int i = 0;//控制无序序列的走向
	int j = i+1;//控制有序序列的走向
	for(i;i<len;i++)
	{
		tmp = arr[i];
		for(j = i-1;j >= 0 && arr[j]> tmp;j--)
		{
			arr[j+1] = arr[j];//
		}
		arr[j+1] = tmp;
	}
}

void Shell(int arr[], int len, int dk)//dk是增量区间
{
	int tmp = 0;
	int i = dk;
	int j = i - dk;
	for (i; i < len; ++i)
	{
		tmp = arr[i];
		for (j = i - dk; j >= 0 && arr[j] > tmp; j -= dk)
		{
			arr[j + dk] = arr[j];
		}
		arr[j + dk] = tmp;
	}
}
void ShellSort(int arr[], int len, int dk[], int dlen)
{
	for (int i = 0; i < dlen; ++i)
	{
		Shell(arr, len, dk[i]);
	}
}


void BulleSort(int arr[],int len)
{
	int flag = false;
	for(int i = 0;i<len-1;i++)
	{
		for(int j=0;j<len-i-1;j++)
		{
			flag = true;
			if(arr[j] > arr[j+1])
			{
				int tmp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = tmp;
			}
		}
		if(!flag)
		{
			return;
		}
	}
}

int Patition(int arr[],int left,int right)
{
	int key = arr[left];
	while(left < right)
	{
		while(left < right && arr[right] > key) 
			right--;
		arr[left] = arr[right];
		while(left < right && arr[left] < key)
			left++;
		arr[right] = arr[left];
	}
	arr[right] = key;
	return left;
}

void Quick(int arr[],int startindex,int endindex)
{
	if (startindex < endindex)
	{	
		int k = Patition(arr, startindex, endindex);
		Quick(arr, startindex, k - 1);
		Quick(arr, k + 1, endindex);
	}
}
void QuickSort(int arr[], int len)
{
	Quick(arr, 0, len - 1);
}


void SimpleSelectSort(int arr[],int len)
{
	int min = 0;
	for(int i = 0;i < len-1;i++)
	{
		min = i;
		for(int j = i+1;j < len;j++)
		{
			if(arr[j] < arr[min])
			{
				min = j;
			}
		}
		if(min != i)
		{
			int tmp = arr[i];
			arr[i] = arr[min];
			arr[min] = tmp;
		}
	}
}

void HeapAdjust(int arr[],int pos,int len)
{
	//根节点：i
	//左结点：2*i+1
	//右结点：2*i+2
	int i = pos;
	int j = 2 * i + 1;
	int tmp = 0;
	for (j; j < len; j = 2 * i + 1)
	{
		if(j < len - 1 && arr[j+1] > arr[j])
			++j;
		if(arr[i] >= arr[j])
			break;
		tmp = arr[i];
		arr[i] = arr[j];
		arr[j] = tmp;
		i = j;
	}
}
void HeapSort(int arr[],int len)
{
	//交换
	int tmp = 0;
	for(int i = len/2-1;i>=0;--i)
	{
		HeapAdjust(arr,i,len);//调整i节点的堆关系
	}
	for(int i = len -1;i > 0;--i)
	{
		tmp = arr[0];
		arr[0] = arr[i];
		arr[i] = tmp;
		HeapAdjust(arr, 0, i);//调整根节点的堆关系
	}
}


void Merge(int arr[], int tmp[], int startindex,
	int mid, int  endindex)
{
	int i = startindex;
	int j = mid + 1;
	int k = startindex;
	while (i < mid + 1 && j < endindex + 1)
	{
		if (arr[i] <= arr[j])
		{
			tmp[k++] = arr[i++];
		}
		if (arr[i] > arr[j])
		{
			tmp[k++] = arr[j++];
		}
	}
	while (i < mid + 1)
	{
		tmp[k++] = arr[i++];
	}
	while (j < endindex + 1)
	{
		tmp[k++] = arr[j++];
	}
	for (int i = startindex; i <= endindex; ++i)
	{
		arr[i] = tmp[i];
	}
}

void MergeS(int arr[], int tmp[], int startindex, int endindex)
{
	if (startindex < endindex)
	{
		int mid = (startindex + endindex) / 2;
		MergeS(arr, tmp, startindex, mid);
		MergeS(arr, tmp, mid + 1, endindex);
		Merge(arr, tmp, startindex, mid, endindex);
	}
}
void MergeSort(int arr[], int len)
{
	int *tmp = (int*)malloc(sizeof(arr[0])*len);
	MergeS(arr, tmp, 0, len - 1);
	free(tmp);
}


int FindMaxFinger(int arr[], int len)
{
	int maxnum = arr[0];
	for (int i = 1; i < len; ++i)
	{
		if (arr[i]>maxnum)
		{
			maxnum = arr[i];
		}
	}
	int count = 0;
	while (maxnum != 0)
	{
		maxnum /= 10;
		count++;
	}
	return count;
}
int FindFinNumber(int num, int fin)
{
	return num / (int)pow(10.0, fin) % 10;
}
void Radix(int arr[], int len, int fin)
{
	int backet[10][MAXSIZE] = {};
	int finnum = 0;
	int num[10] = {};
	for (int i = 0; i < len; ++i)
	{
		finnum = FindFinNumber(arr[i], fin);
		backet[finnum][num[finnum]] = arr[i];
		num[finnum]++;
	}
	int aindex = 0;
	int bindex = 0;
	for (int i = 0; i < 10; ++i)
	{
		bindex = 0;
		while (bindex != num[i])
		{
			arr[aindex++] = backet[i][bindex++];
		}
	}
}
void RadixSort(int arr[], int len)
{
	int max = FindMaxFinger(arr, len);
	for (int i = 0; i < max; ++i)
	{
		Radix(arr, len, i);
	}
}
void show(int arr[],int len)
{
	for(int i=0;i<len;i++)
	{
		printf("%d ",arr[i]);
	}
	printf("\n");
}
int main()
{
	//int arr[] = {4,5,3,2,6,1,8};
	//int len = sizeof(arr)/arr[0];
	//InsertSort(arr,len);
	//BulleSort(arr,len);
	//QuickSort(arr,len);
	//SimpleSelectSort(arr,len);
	//HeapSort(arr,len);	
	//MergeSort(arr,len);


	int arr[] = {154,8956,3210,2015,123,452};
	//int arr[] = { 312, 31, 234, 32, 4, 23, 4, 23, 1431, 21 };
	int len = sizeof(arr) / sizeof(arr[0]);
	RadixSort(arr, len);
	show(arr,len);

	return 0;
}
