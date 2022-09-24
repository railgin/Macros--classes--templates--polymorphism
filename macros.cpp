//основной файл
#include <iostream>
#include "Header.h"
using namespace std;
//макрос - правило, что конвертирует идентификатор в указанные данные
int main()
{
	int n;
	cin >> n;
	double* m1 = new double[n];
	array_initialization(m1, n);
	array_print(m1, n);
	sum_of_negative_elements(m1, n);
	product_between_min_and_max(m1, n);
	arr_sort_2(m1, n);


	delete[] m1;
}

//заголовочный файл
#pragma once
#define head
#ifdef head

#define array_initialization(arr,n)\
{\
	for (int i = 0; i < n; i++)\
	{\
		cin >> arr[i];\
	}\
}
#define array_print(arr,n)\
{\
	for (int i = 0; i < n; i++)\
	{\
		cout<<arr[i]<<"|";\
		cout << endl;\
	}\
}
#define arr_sort_1(arr,n)\
{\
	for(int i = 0; i < n; i++)\
	{\
		for (int j = 0; j < n - i - 1; j++)\
		{\
			if (arr[j]>arr[j+1])\
			{\
				c=arr[j];\
				arr[j] = arr[j+1];\
				arr[j+1] = c;\
			}\
		}\
	}\
}
#define arr_sort_2(arr,n)\
{\
	for (int i = 1; i < n; i++)\
	{\
		int k = i;\
		while(k>0 && arr[k-1]>arr[k])\
		{\
			double tmp = arr[k - 1];\
			arr[k - 1] = arr[k];\
			arr[k] = tmp;\
			k--;\
		}\
	}\
}
#define sum_of_negative_elements(arr,n)\
{\
	double sum = 0.0;\
	for(int i = 0; i < n; i++)\
	{\
		if (arr[i] < 0)\
		{\
			sum+=arr[i];\
		}\
	}\
	cout<<"Sum of negative elements = "<< sum << endl;\
}
#define product_between_min_and_max(arr,n)\
{\
	double max = arr[0];\
	double min = arr[0];\
	int indexMax = 0, indexMin = 0;\
	for(int i = 1; i < n; i++)\
	{\
		if (max < arr[i])\
		{\
			max = arr[i];\
			indexMax = i;\
		}\
		if(min>arr[i])\
		{\
			min = arr[i];\
			indexMin = i;\
		}\
	}\
	cout << "Max = " << max <<endl;\
	cout << "Min = " << min << endl;\
	double product = 1.0;\
	if (abs(indexMin - indexMax) == 1)\
		{\
			cout << "There are no elements" << endl;\
		}\
	else{\
		for (int i = indexMin + 1; i < indexMax; i++)\
		{\
			product *= arr[i]; \
		}\
	}\
	cout << "Product = "<< product << endl;\
}





#endif // head
