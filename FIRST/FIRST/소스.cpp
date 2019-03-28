#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MAX1000 1000
#define MAX10000 10000
#define MAX1000000 1000000
double selectionSort(int A[], int n);
int findMAX(int A[], int n);
void swap(int A[],int a, int b);
double bubbleSort(int A[], int n);
double InsertionSort(int A[], int n);
void merge(int A[], int p, int q, int r);
void mergeSort(int A[], int p, int r);
void quickSort(int A[], int left, int right);
int partition(int A[], int left, int right);
void quickSort_Mid(int A[], int left, int right);
void quickSort_Random(int A[], int left,int right);
void Random1000();
void Random10000();
void Random100000();
void Reverse1000();
void Reverse10000();
void Reverse100000();
void reset_re(int n);
void reset_ran(int n);
void print();
double DATA[7][6] = { 0 };//Bubble,Selection,Insertion,Merge,Quick1,2,3
char data_index[7][100] = { "\t","Random1000","Reverse1000","Random10000","Reverse10000","Random100000","Reverse100000" };
char Category[7][100] = {"Bubble","Selection","Insertion","Merge","Quick1","Quick2","Quick3" };
clock_t end, start;
#define DATALENGTH 100000
int data[100000];
int tmp[DATALENGTH];
int main() {
	srand(time(NULL));
	Random1000();
	Reverse1000();
	Random10000();
	Reverse10000();
	Reverse100000();
	Random100000();
	print();

	return 0;
}
double selectionSort(int A[], int n) {
	start = clock();
	for (int last = n-1; last >= 1; last--) {
		int max = findMAX(A, last);
		swap(A,last,max);
	}
	end = clock();
	return (double)(end - start)/CLK_TCK;
}
int findMAX(int A[],int n) {
	int max_index = n;
	for (int i = n-1; i >= 0; i--) {
		if (A[max_index] < A[i]) {
			max_index = i;
		}
	}
	return max_index;
}
void swap(int A[],int a, int b) {

	int tmp = A[a];
	A[a] = A[b]; A[b] = tmp;
}
double bubbleSort(int A[], int n) {
	start = clock();
	for (int last = n - 1; last >= 1; last--) {
		for (int i = 0; i < n - 1; i++) {
			if (A[i] > A[i + 1]) {
				swap(A, i, i + 1);
			}
		}
	}
	end = clock();
	return (double)(end - start)/CLK_TCK;
}
double InsertionSort(int A[], int n) {
	int tmp; int j;
	start = clock();
	for (int i = 1; i < n; i++) {
		tmp = A[i];
		 j= i - 1;
		while (j >= 0 && A[j] > tmp) {
			A[j+1] = A[j];
			j--;
		}
		A[j + 1] = tmp;
	}
	end = clock();
	return (double)(end - start)/CLK_TCK;
}
void mergeSort(int A[], int p, int r) {

	int q;
	if (p < r) {
		q = (p + r) / 2;
		mergeSort(A, p, q);
		mergeSort(A, q + 1, r);
		merge(A, p, q, r);
	}
}
void merge(int A[], int p, int q, int r) {
	int i = p,j = q + 1, k = p;
	
	while (i <= q && j <= r) {
		if (A[i] <= A[j])
			tmp[k++] = A[i++];
		else
			tmp[k++] = A[j++];
	}
	while (i <= q)
		tmp[k++] = A[i++];
	while (j <= r)
		tmp[k++] = A[j++];
	for (int i = p; i <= r; i++)
		A[i] = tmp[i];
}
int partition(int A[], int left, int right) {
	int pivot = A[right];
	int pindex = left;
	for (int i = left; i < right; i++) {
		if (A[i] <= pivot) {
			swap(A, i, pindex); pindex++;
		}
	}swap(A, pindex, right);
	return pindex;
}

void quickSort(int A[], int left, int right) {
	while (left < right) {
		if (right - left < 10) {
			InsertionSort(A, right + 1); break;
		}
		else {
			int pivot = partition(A, left, right);
			if (pivot - left < right - pivot) {
				quickSort(A, left, pivot - 1); left = pivot + 1;
			}
			else {
				quickSort(A, pivot + 1, right); right = pivot - 1;
			}
		}
	}
}
void quickSort_Mid(int A[], int left, int right) {
	int i = left, j = right;
	int pivot = A[(left + right) / 2];
	while (i <= j)
	{
		while (A[i] < pivot)
			i++;
		while (A[j] > pivot)
			j--;
		if (i <= j)
		{
			swap(A, i, j);
			i++;
			j--;
		}
	}

	if (left < j)
		quickSort_Mid(A, left, j);

	if (i < right)
		quickSort_Mid(A, i, right);
}
void quickSort_Random(int A[],int left,int right) {
	int x,p;
	if (left < right) {
		x = rand() % (right + 1);
		swap(A, x, right);
		p = partition(A, left, right);
		quickSort(A, left, p-1);
		quickSort(A, p + 1, right);
	}
}
void print() {
	printf(" -------------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < 7; i++) {
		printf(" %10s ", data_index[i]);
	} printf("\n"); printf(" -------------------------------------------------------------------------------------------------\n");

	for (int i = 0; i < 7; i++) {
		printf("%10s      ", Category[i]);
		for (int j = 0; j < 6; j++) {
			printf("%10lf    ", DATA[i][j]);
		}printf("\n");
	}
}
void Random1000() {
	double sum[7] = { 0.0 };
	for (int i = 0; i < 10; i++) {
		reset_ran(1000); sum[0] += bubbleSort(data, 1000);
		reset_ran(1000); sum[1] += selectionSort(data, 1000);
		reset_ran(1000); sum[2] += InsertionSort(data, 1000);
		reset_ran(1000);  start = clock(); mergeSort(data, 0, 999); end = clock();
		sum[3]+=(double)(end - start) / CLK_TCK;
		reset_ran(1000);  start = clock(); quickSort(data, 0, 999); end = clock();
		sum[4] += (double)(end - start) / CLK_TCK;
		reset_ran(1000);  start = clock(); quickSort_Mid(data, 0, 999); end = clock();
		sum[5] += (double)(end - start) / CLK_TCK;
		reset_ran(1000);  start = clock(); quickSort_Random(data, 0, 999); end = clock();
		sum[6] += (double)(end - start) / CLK_TCK;
	}
	for (int i = 0; i < 7; i++) {
		DATA[i][0] = sum[i] / 10.0;
	}
}
void Random10000() {
	double sum[7] = { 0.0 };
	for (int i = 0; i < 10; i++) {
		reset_ran(10000); sum[0] += bubbleSort(data, 10000);
		reset_ran(10000); sum[1] += selectionSort(data, 10000);
		reset_ran(10000); sum[2] += InsertionSort(data, 10000);
		reset_ran(10000);  start = clock(); mergeSort(data, 0, 9999); end = clock();
		sum[3] += (double)(end - start) / CLK_TCK;
		reset_ran(10000);  start = clock(); quickSort(data, 0, 9999); end = clock();
		sum[4] += (double)(end - start) / CLK_TCK;
		reset_ran(10000);  start = clock(); quickSort_Mid(data, 0, 9999); end = clock();
		sum[5] += (double)(end - start) / CLK_TCK;
		reset_ran(10000);  start = clock(); quickSort_Random(data, 0, 9999); end = clock();
		sum[6] += (double)(end - start) / CLK_TCK;
	}
	for (int i = 0; i < 7; i++) {
		DATA[i][2] = sum[i] / 10.0;
	}
}
void Random100000() {
	double sum[7] = { 0.0 };
	for (int i = 0; i < 10; i++) {
		reset_ran(100000); sum[0] += bubbleSort(data, 100000);
		reset_ran(100000); sum[1] += selectionSort(data, 100000);
		reset_ran(100000); sum[2] += InsertionSort(data, 100000);
		reset_ran(100000);  start = clock(); mergeSort(data, 0, 99999); end = clock();
		sum[3] += (double)(end - start) / CLK_TCK;
		reset_ran(100000);  start = clock(); quickSort(data, 0, 99999); end = clock();
		sum[4] += (double)(end - start) / CLK_TCK;
		reset_ran(100000);  start = clock(); quickSort_Mid(data, 0, 99999); end = clock();
		sum[5] += (double)(end - start) / CLK_TCK;
		reset_ran(100000);  start = clock(); quickSort_Random(data, 0, 99999); end = clock();
		sum[6] += (double)(end - start) / CLK_TCK;
	}
	for (int i = 0; i < 7; i++) {
		DATA[i][4] = sum[i] / 10.0;
	}
}
void Reverse1000() {
	reset_re(1000); DATA[0][1] = bubbleSort(data, 1000);
	reset_re(1000); DATA[1][1] = selectionSort(data, 1000);
	reset_re(1000); DATA[2][1] = InsertionSort(data, 1000);
	reset_re(1000); start = clock(); mergeSort(data, 0, 999); end = clock();
	DATA[3][1] = (double)(end - start)/CLK_TCK;
	reset_re(1000); start = clock(); quickSort(data, 0, 999); end = clock();
	DATA[4][1] = (double)(end - start)/CLK_TCK;
	reset_re(1000); start = clock(); quickSort_Mid(data, 0, 999); end = clock();
	DATA[5][1] = (double)(end - start)/CLK_TCK;
	reset_re(1000); start = clock(); quickSort_Random(data,0,999); end = clock();
	DATA[6][1] = (double)(end - start)/CLK_TCK;
}
void Reverse10000() {
	reset_re(10000); DATA[0][3] = bubbleSort(data, 10000);
	reset_re(10000); DATA[1][3] = selectionSort(data, 10000);
	reset_re(10000); DATA[2][3] = InsertionSort(data, 10000);
	reset_re(10000); start = clock(); mergeSort(data, 0, 9999); end = clock();
	DATA[3][3] = (double)(end - start) / CLK_TCK;
	reset_re(10000); start = clock(); quickSort(data, 0, 9999); end = clock();
	DATA[4][3] = (double)(end - start) / CLK_TCK;
	reset_re(10000); start = clock(); quickSort_Mid(data, 0, 9999); end = clock();
	DATA[5][3] = (double)(end - start) / CLK_TCK;
	reset_re(10000); start = clock(); quickSort_Random(data,0,9999); end = clock();
	DATA[6][3] = (double)(end - start) / CLK_TCK;
}
void Reverse100000() {
	reset_re(100000); DATA[0][5] = bubbleSort(data, 100000);
	reset_re(100000); DATA[1][5] = selectionSort(data, 100000);
	reset_re(100000); DATA[2][5] = InsertionSort(data, 100000);
	reset_re(100000); start = clock(); mergeSort(data, 0, 9999); end = clock();
	DATA[3][5] = (double)(end - start) / CLK_TCK;
	reset_re(100000); start = clock(); quickSort(data, 0, 9999); end = clock();
	DATA[4][5]=(double)(end - start) / CLK_TCK;
	reset_re(100000); start = clock(); quickSort_Mid(data, 0, 9999); end = clock();
	DATA[5][5] = (double)(end - start) / CLK_TCK;
	reset_re(100000); start = clock(); quickSort_Random(data,0,9999); end = clock();
	DATA[6][5] = (double)(end - start) / CLK_TCK;
	
}
void reset_re(int n) {
	for (int i = 0; i < n; i++) {
		data[i] = n - i;
	}
}
void reset_ran(int n) {
	for (int i = 0; i < n; i++) {
		data[i] = (rand()%n)+1;
	}
}