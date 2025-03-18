#include <iostream>
#include <fstream>
#include <cmath>
#include <time.h>
using namespace std;

template <class T>
void HoanVi(T &a, T &b)
{
	T x = a;
	a = b;
	b = x;
}

//-------------------------------------------------

// Hàm phát sinh mảng dữ liệu ngẫu nhiên
void GenerateRandomData(int a[], int n)
{
	srand((unsigned int)time(NULL));

	for (int i = 0; i < n; i++)
	{
		a[i] = rand()%n;
	}
}

// Hàm phát sinh mảng dữ liệu có thứ tự tăng dần
void GenerateSortedData(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = i;
	}
}

// Hàm phát sinh mảng dữ liệu có thứ tự ngược (giảm dần)
void GenerateReverseData(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = n - 1 - i;
	}
}

// Hàm phát sinh mảng dữ liệu gần như có thứ tự
void GenerateNearlySortedData(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = i;
	}
	srand((unsigned int) time(NULL));
	for (int i = 0; i < 10; i ++)
	{
		int r1 = rand()%n;
		int r2 = rand()%n;
		HoanVi(a[r1], a[r2]);
	}
}

void GenerateData(int a[], int n, int dataType)
{
	switch (dataType)
	{
	case 0:	// ngẫu nhiên
		GenerateRandomData(a, n);
		break;
	case 1:	// có thứ tự
		GenerateSortedData(a, n);
		break;
	case 2:	// có thứ tự ngược
		GenerateReverseData(a, n);
		break;
	case 3:	// gần như có thứ tự
		GenerateNearlySortedData(a, n);
		break;
	default:
		printf("Error: unknown data type!\n");
	}
}

long long int comparisonCount = 0;

// Binary insertion sort algorithm
int binarySearch(int a[], int left, int right, int key) {
    while (true) {
		comparisonCount++; 
		if (left > right) {
			return left;
		}

		int mid = (left + right) / 2;

		comparisonCount++;
		if (key == a[mid]) {
			return mid + 1;
		}

		comparisonCount++;
		if (key < a[mid]) {
			right = mid - 1;
		} else {
			left = mid + 1;
		}
	}
}

void binaryInsertionSort(int a[], int n) {
    int i = 1;
	while (true) {
		comparisonCount++;
		if (i >= n) {
			break;
		}

		int key = a[i];
		int j = i - 1;

		int loc = binarySearch(a, 0, j, key);
		
		while (true) {
			comparisonCount++;
			if (j < loc) {
				break;
			}

			a[j + 1] = a[j];
			j--;
		}

		a[j + 1] = key;
		i++;
	}
}

// Insertion sort algorithm
void insertionSort(int arr[], int n)
{
	int current, temp;	//current là biến vị trí hiện tại
	for (int i = 1; i < n; i++)
	{
        comparisonCount++;
		current = i;
		temp = arr[i];

		while (current > 0 && arr[current - 1] > temp)
		{
            comparisonCount += 2;
			arr[current] = arr[current - 1];
			current--;
		}

        if (current > 0) {
            comparisonCount++;
        }

		arr[current] = temp;
	}

    comparisonCount++;
}

// Quick sort algorithm
int medianOfThree(int a[], int left, int right) {
    int mid = left + (right - left) / 2;

    if (a[left] > a[mid]) HoanVi(a[left], a[mid]);
    if (a[left] > a[right]) HoanVi(a[left], a[right]);
    if (a[mid] > a[right]) HoanVi(a[mid], a[right]);

    return mid;
}

int partition(int a[], int left, int right) {
    int pivotIndex = medianOfThree(a, left, right);
    HoanVi(a[pivotIndex], a[right]);

    int pivot = a[right];
    int i = left - 1;

    for (int j = left; ++comparisonCount && j < right; j++) {
        if (++comparisonCount && a[j] < pivot) {
            HoanVi(a[++i], a[j]);
        }
    }

    HoanVi(a[i + 1], a[right]);
    return i + 1;
}

void quickSort(int a[], int left, int right, int depth = 0) {
    const int maxDepth = log2(right - left + 1) * 2;  // Giới hạn độ sâu đệ quy
    comparisonCount++;

    while (left < right) {
        if (depth > maxDepth) {
            insertionSort(a + left, right - left + 1);
            return;
        }

        if (right - left <= 10) {  
            insertionSort(a + left, right - left + 1);
            return;
        }

        int pivot = partition(a, left, right);

        // Chia nhánh nhỏ trước để tối ưu stack
        if (pivot - left < right - pivot) {
            quickSort(a, left, pivot - 1, depth + 1);
            left = pivot + 1;
        } else {
            quickSort(a, pivot + 1, right, depth + 1);
            right = pivot - 1;
        }
    }
}



// Merge sort algorithm
void merge(int b[], int p, int c[], int q, int a[]) {
	int i = 0;
	int j = 0;
	int k = 0;

	while (true) {
		comparisonCount++;
		if (i >= p) {
			break;
		}

		comparisonCount++;
		if (j >= q) {
			break;
		}

		comparisonCount++;
		if (b[i] <= c[j]) {
			a[k] = b[i];
			i++;
		} else {
			a[k] = c[j];
			j++;
		}
		k++;
	}

	while (true) {
		comparisonCount++;
		if (i >= p) {
			break;
		}

		a[k] = b[i];
		i++;
		k++;
	}

	while (true) {
		comparisonCount++;
		if (j >= q) {
			break;
		}

		a[k] = c[j];
		j++;
		k++;
	}
}

void mergeSort(int a[], int n) {
	comparisonCount++;
	if (n > 1) {
		int mid = n / 2;
		int p = mid;
		int q = n - mid;

		int* b = new int[p];
		int* c = new int[q];

		int i = 0;
		while (true) {
			comparisonCount++;
			if (i >= p) {
				break;
			}

			b[i] = a[i];
			i++;
		}

		int j = 0;
		while (true) {
			comparisonCount++;
			if (j >= q) {
				break;
			}

			c[j] = a[j + mid];
			j++;
		}

		mergeSort(b, p);
		mergeSort(c, q);

		merge(b, p, c, q, a);

		delete[] b;
		delete[] c;
	}
}

// Selection sort algorithm
void selectionSort(int a[], int n) {
	for (int i = 0; ++comparisonCount && i < n - 1; i++) {
		comparisonCount++;
		int min = i;

		for (int j = 1 + i; ++comparisonCount && j < n; j++) {
			comparisonCount += 1;
			if (a[j] < a[min]) {
				min = j;
			}
		}

		HoanVi(a[i], a[min]);
	}
}
// Counting sort algorithm
void countingSort(int a[], int n) {
	int maxVal = a[0];
	for (int i = 1; i < n; i++) {
		comparisonCount += 2;
		if (a[i] > maxVal) {
			maxVal = a[i];
		}
	}
	comparisonCount++;

	int size = maxVal + 1;
	int* output = new int[n];
	int* count = new int[size];

	for (int i = 0; i < size; i++) {
		comparisonCount++;
		count[i] = 0;
	}
	comparisonCount++;

	for (int i = 0; i < n; i++) {
		comparisonCount++;
		count[a[i]]++;
	}
	comparisonCount++;

	for (int i = 1; i < size; i++) {
		comparisonCount++;
		count[i] += count[i - 1];
	}
	comparisonCount++;

	for (int i = n - 1; i >= 0; i--) {
		comparisonCount++;
		output[count[a[i]] - 1] = a[i];
		count[a[i]]--;
	}
	comparisonCount++;

	for (int i = 0; i < n; i++) {
		comparisonCount++;
		a[i] = output[i];
	}
	comparisonCount++;

	delete[] count;
	delete[] output;
}

// Bubble sort algorithm
void bubbleSort(int arr[], int n)
{
	int index = 1, temp;

	while (++comparisonCount && index != 0)
	{
		index = 0;
		for (int i = 0; i < n - 1; i++)
		{
            comparisonCount++;
			if (arr[i] > arr[i + 1])
			{
				index++;
				/*
				temp = arr[i];
				arr[i] = arr[i+1];
				arr[i+1] = temp;
				*/
				HoanVi(arr[i], arr[i + 1]);
			}
            comparisonCount++;

		}
        comparisonCount++;
	}
}

// Radix sort algorithm
int findMax(int arr[], int n)
{
	int nmax = arr[0];
	for (int i = 1; i < n; i++)
	{
        comparisonCount++;
		nmax = max(nmax, arr[i]);
	}

    comparisonCount++;
	return nmax;
}

void radixSort(int arr[], int n)
{
	int nmax = findMax(arr, n), index = 1, digit;
	int temp[10] = { 0 };
	int* result = new int[n];

	while (++comparisonCount && nmax / index > 0)
	{
		int temp[10] = { 0 };
		for (int i = 0; i < n; i++)
		{
            comparisonCount++;
			temp[arr[i] / index % 10]++;
		}
		comparisonCount++;

		for (int i = 1; i < 10; i++)
		{
            comparisonCount++;
			temp[i] = temp[i] + temp[i - 1];
		}
        comparisonCount++;

		for (int i = n - 1; i >= 0; i--)
		{
            comparisonCount++;
			digit = arr[i] / index % 10;
			result[temp[digit] - 1] = arr[i];
			temp[digit]--;
		}
        comparisonCount++;

		for (int i = 0; i < n; i++)
		{
            comparisonCount++;
			arr[i] = result[i];
		}
        comparisonCount++;
		index *= 10;
	}

	delete[] result;
}

// Flash sort algorithm
void flashSort(int arr[], int n)
{
    if (++comparisonCount && n <= 1) return;

    // Tìm min và max
    int maxVal = arr[0], minVal = arr[0], maxIndex = 0;
    for (int i = 1; ++comparisonCount && i < n; i++)
    {
        if (++comparisonCount && arr[i] > maxVal)
        {
            maxVal = arr[i];
            maxIndex = i;
        }
        if (++comparisonCount && arr[i] < minVal)
            minVal = arr[i];
    }

    //phần tử giống nhau
    if (++comparisonCount && maxVal == minVal) return;

    // Chọn m
    int m = std::max(1, std::min(n / 50, 50000)); 

    int *L = new int[m]();
    for (int i = 0; ++comparisonCount && i < n; i++)
    {
        int k = (int)((m - 1) * (double)(arr[i] - minVal) / (maxVal - minVal));
        L[k]++;
    }

    for (int i = 1; ++comparisonCount && i < m; i++)
    {
        L[i] += L[i - 1];
    }

    // Hoán vị
    int count = 0, index = 0;

	// Đánh dấu phần tử đã được sắp xếp
    bool *visited = new bool[n](); 

    while (++comparisonCount && count < n)
    {
        while (++comparisonCount && index < n && visited[index])
            index++;

        if (++comparisonCount && index >= n)
            break;

        int k = (int)((m - 1) * (double)(arr[index] - minVal) / (maxVal - minVal));
        int temp = arr[index];

        while (++comparisonCount && !visited[index])
        {
            k = (int)((m - 1) * (double)(temp - minVal) / (maxVal - minVal));
            HoanVi(temp, arr[--L[k]]);
            visited[index] = true;
            count++;
        }
    }

    delete[] L;
    delete[] visited;

    insertionSort(arr, n);  
}



// Shaker sort algorithm
void shakerSort(int arr[], int n)
{
	int bienPhai, bienTrai;
	int left = 0, right = n - 1;
	while (++comparisonCount && left < right)
	{
		bienPhai = -1;
		bienTrai = -1;
		for (int i = left; i < right; i++)
		{
            comparisonCount += 2;
			if (arr[i] > arr[i + 1])
			{
				HoanVi(arr[i], arr[i + 1]);
				bienPhai = i;
			}
		}
        comparisonCount += 2;
		if (bienPhai == -1)
		{
			break;
		}

		right = bienPhai;

        comparisonCount++;
		if (left == right) break;

		for (int i = right; i > left; i--)
		{
            comparisonCount += 2;
			if (arr[i] < arr[i - 1])
			{
				HoanVi(arr[i], arr[i - 1]);
				bienTrai = i;
			}
		}
        comparisonCount += 2;
		if (bienTrai == -1)
		{
			break;
		}

		left = bienTrai;
	}
}

// Heap Sort Algorithm
void max_heapify(int a[], int n, int i) {
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	comparisonCount++;
	if (left < n) { // nếu con trái tồn tại và lớn hơn cha
		comparisonCount++;
		if (a[left] > a[largest]) {
			largest = left; // đổi giá trị giữa cha với con
		}
	}
	
	comparisonCount++;
	if (right < n) { 
		comparisonCount++;
		if (a[right] > a[largest]) { // nếu con phải tồn tại, lớn hơn cha 
			largest = right;
		}
	}

	comparisonCount++;
    if (largest != i) { // nếu nút cha ko phải là cha ban đầu
        HoanVi(a[i], a[largest]);
        max_heapify(a, n, largest);
    }
}

void build_maxheap(int a[], int n) {
	for (int i = n / 2 - 1; i >= 0; i--) { //duyệt từ nút cha cuối lên gốc
		max_heapify(a, n, i);
		comparisonCount++;
	}
	comparisonCount++;
}

void heapSort(int a[], int n) {
	build_maxheap(a, n); // bước 1: xây dựng max_heap

	for (int i = n - 1; i > 0; i--) {
		swap(a[i], a[0]); //đưa max về cuối
		max_heapify(a, i, 0); //gọi heapify trên phần còn lại
		comparisonCount++;
	}
	comparisonCount++;
}

// shell sort algorithm
void shellSort(int a[], int n) {
	int gap = n / 2;
     
    while (gap > 0) {
        comparisonCount++;
        for (int i = 0; i < n; i++) {
            comparisonCount++;
            int temp = a[i];
 
            int j = i;
             
        	while (true) {
                comparisonCount++;
                if (j < gap) {
                    break;
                }
 
                comparisonCount++;
                if (a[j - gap] > temp) {
                    a[j] = a[j - gap];
                    j = j - gap;
                }
                else {
                    break;
                }
            }
            a[j] = temp;
        }
        comparisonCount++;
        gap /= 2;
    }
    comparisonCount++;
}

double getTime(clock_t start, clock_t end) {
	return ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;
}

int stringToInt(const string &str) {
    int number = 0;
    bool isNegative = false;
    int i = 0;

    if (str[0] == '-') {
        isNegative = true;
        i = 1; 
    }


    for (; i < str.length(); i++) {
        if (str[i] < '0' || str[i] > '9') {
            return -1; 
        }
        number = number * 10 + (str[i] - '0');
    }

    return isNegative ? -number : number;
}

void readFile(const string &fileName, int* &arr, int &n) {
	ifstream fin(fileName);

	if (! fin) {
		cerr << "\nError opening file! \n";
		return;
	}

	if (! (fin >> n)) {
		cerr << "\nError reading number of elements! \n";
		return;
	}

	arr = new int[n];
	for (int i = 0; i < n; i++) {
		if (! (fin >> arr[i])) {
			cerr << "\nError reading element at index " << i << "\n";
			delete[] arr;
			arr = nullptr;
			return;
		}
	}

	fin.close();
}

void writeOutputFile(const string &fileName, int arr[], int n) {
	ofstream fout(fileName);

	if (! fout) {
		cerr << "\nCan't open file " << fileName << " for writing!";
		return;
	}

	fout << n << "\n";

	for (int i = 0; i < n; i++) {
		fout << arr[i] << " ";
	}

	fout.close();
}

void processSorting(const string &algorithm, int arr[], int n, const string &outputParam) {
	const int NUM_RUNS = 1;

    double totalTime = 0.0;
    long long int totalComparisons = 0;

    for (int i = 0; i < NUM_RUNS; i++) {
        int tempArr[n];
        copy(arr, arr + n, tempArr);

        clock_t start = clock();
        comparisonCount = 0;

        if (algorithm == "selection-sort") {
            selectionSort(tempArr, n);
        } else if (algorithm == "insertion-sort") {
            insertionSort(tempArr, n);
        } else if (algorithm == "binary-insertion-sort") {
            binaryInsertionSort(tempArr, n);
        } else if (algorithm == "bubble-sort") {
            bubbleSort(tempArr, n);
        } else if (algorithm == "shaker-sort") {
            shakerSort(tempArr, n);
        } else if (algorithm == "shell-sort") {
            shellSort(tempArr, n);
        } else if (algorithm == "heap-sort") {
            heapSort(tempArr, n);
        } else if (algorithm == "merge-sort") {
            mergeSort(tempArr, n);
        } else if (algorithm == "quick-sort") {
            quickSort(tempArr, 0, n - 1);
        } else if (algorithm == "counting-sort") {
            countingSort(tempArr, n);
        } else if (algorithm == "radix-sort") {
            radixSort(tempArr, n);
        } else if (algorithm == "flash-sort") {
            flashSort(tempArr, n);
        } else {
            cerr << "Error: Unsupported sorting algorithm!\n";
            return;
        }

        clock_t end = clock();
        totalTime += (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
        totalComparisons += comparisonCount;
    }

    double avgTime = totalTime / NUM_RUNS;
    long long int avgComparisons = totalComparisons / NUM_RUNS;

    // Xuất kết quả ra màn hình
    cout << "-------------------------\n";
    if (outputParam == "-time" || outputParam == "-both") {
        printf("Running time: %.5f ms\n", avgTime);
    }
    if (outputParam == "-comp" || outputParam == "-both") {
        cout << "Comparisons: " << avgComparisons << endl;
    }
}

void process2Sorting(const string &algorithm1, const string &algorithm2, int arr1[], int arr2[], int n, const string &outputParam) {
	// // Run one time
	// long long comparisonCount1 = 0;
    // long long comparisonCount2 = 0;

    // comparisonCount = 0;
    // // Run algorithm1
	// clock_t start1 = clock();
    // if (algorithm1 == "selection-sort") {
	// 	selectionSort(arr1, n);
	// } else if (algorithm1 == "insertion-sort") {
	// 	insertionSort(arr1, n);
	// } else if (algorithm1 == "binary-insertion-sort") {
	// 	binaryInsertionSort(arr1, n);
	// } else if (algorithm1 == "bubble-sort") {
	// 	bubbleSort(arr1, n);
	// } else if (algorithm1 == "shaker-sort") {
	// 	shakerSort(arr1, n);
	// } else if (algorithm1 == "shell-sort") {
	// 	shellSort(arr1, n);
	// } else if (algorithm1 == "heap-sort") {
	// 	heapSort(arr1, n);
	// } else if (algorithm1 == "merge-sort") {
	// 	mergeSort(arr1, n);
	// } else if (algorithm1 == "quick-sort") {
	// 	quickSort(arr1, 0, n - 1);
	// } else if (algorithm1 == "counting-sort") {
	// 	countingSort(arr1, n);
	// } else if (algorithm1 == "radix-sort") {
	// 	radixSort(arr1, n);
	// } else if (algorithm1 == "flash-sort") {
	// 	flashSort(arr1, n);
	// } else {
	// 	cerr << "Error: Unsupported sorting algorithm!\n";
	// 	return;
	// }
    // clock_t end1 = clock();
    // comparisonCount1 = comparisonCount;
    // double elapsedTime1 = getTime(start1,end1);

    // comparisonCount = 0;
    // // Run algorithm2
	// clock_t start2 = clock();
    // if (algorithm2 == "selection-sort") {
	// 	selectionSort(arr2, n);
	// } else if (algorithm2 == "insertion-sort") {
	// 	insertionSort(arr2, n);
	// } else if (algorithm2 == "binary-insertion-sort") {
	// 	binaryInsertionSort(arr2, n);
	// } else if (algorithm2 == "bubble-sort") {
	// 	bubbleSort(arr2, n);
	// } else if (algorithm2 == "shaker-sort") {
	// 	shakerSort(arr2, n);
	// } else if (algorithm2 == "shell-sort") {
	// 	shellSort(arr2, n);
	// } else if (algorithm2 == "heap-sort") {
	// 	heapSort(arr2, n);
	// } else if (algorithm2 == "merge-sort") {
	// 	mergeSort(arr2, n);
	// } else if (algorithm2 == "quick-sort") {
	// 	quickSort(arr2, 0, n - 1);
	// } else if (algorithm2 == "counting-sort") {
	// 	countingSort(arr2, n);
	// } else if (algorithm2 == "radix-sort") {
	// 	radixSort(arr2, n);
	// } else if (algorithm2 == "flash-sort") {
	// 	flashSort(arr2, n);
	// } else {
	// 	cerr << "Error: Unsupported sorting algorithm!\n";
	// 	return;
	// }
    // clock_t end2 = clock();
    // comparisonCount2 = comparisonCount;
    // double elapsedTime2 = getTime(start2, end2);

	// // Print result
    // cout << "-------------------------\n";
    // if (outputParam == "-time" || outputParam == "-both") {
    //     cout << "Running time: " << elapsedTime1 << " ms | "<< elapsedTime2 << " ms \n"; 
    // }
    
	// if (outputParam == "-comp" || outputParam == "-both") {
    //     cout << "Comparisons: " << comparisonCount1 << " | "<< comparisonCount2 << "\n\n\n";
    // }
	
	// Run 10 times
	long long comparisonCount1 = 0;
	long long comparisonCount2 = 0;

	// Algorithm 1
	double totalTime1 = 0;
	int iterations = 10;

	int* temp = new int[n];
	for (int i = 0; i < iterations; i++) {
		for (int j = 0; j < n; j++) {
			temp[j] = arr1[j];
		}

		comparisonCount = 0; // Reset comparisonCount
		clock_t start1 = clock();
		if (algorithm1 == "selection-sort") {
			selectionSort(temp, n);
		} else if (algorithm1 == "insertion-sort") {
			insertionSort(temp, n);
		} else if (algorithm1 == "binary-insertion-sort") {
			binaryInsertionSort(temp, n);
		} else if (algorithm1 == "bubble-sort") {
			bubbleSort(temp, n);
		} else if (algorithm1 == "shaker-sort") {
			shakerSort(temp, n);
		} else if (algorithm1 == "shell-sort") {
			shellSort(temp, n);
		} else if (algorithm1 == "heap-sort") {
			heapSort(temp, n);
		} else if (algorithm1 == "merge-sort") {
			mergeSort(temp, n);
		} else if (algorithm1 == "quick-sort") {
			quickSort(temp, 0, n - 1);
		} else if (algorithm1 == "counting-sort") {
			countingSort(temp, n);
		} else if (algorithm1 == "radix-sort") {
			radixSort(temp, n);
		} else if (algorithm1 == "flash-sort") {
			flashSort(temp, n);
		} else {
			cerr << "Error: Unsupported sorting algorithm!\n";
			delete[] temp;
			return;
		}
		clock_t end1 = clock();
		totalTime1 += getTime(start1, end1);
		comparisonCount1 += comparisonCount;
	}
	double elapsedTime1 = totalTime1 / iterations;
	comparisonCount1 /= iterations;

	// Algorithm 2
	double totalTime2 = 0;
	for (int i = 0; i < iterations; i++) {
		for (int j = 0; j < n; j++) {
			temp[j] = arr2[j];
		}

		comparisonCount = 0; // Reset comparisonCount
		clock_t start2 = clock();
		if (algorithm2 == "selection-sort") {
			selectionSort(temp, n);
		} else if (algorithm2 == "insertion-sort") {
			insertionSort(temp, n);
		} else if (algorithm2 == "binary-insertion-sort") {
			binaryInsertionSort(temp, n);
		} else if (algorithm2 == "bubble-sort") {
			bubbleSort(temp, n);
		} else if (algorithm2 == "shaker-sort") {
			shakerSort(temp, n);
		} else if (algorithm2 == "shell-sort") {
			shellSort(temp, n);
		} else if (algorithm2 == "heap-sort") {
			heapSort(temp, n);
		} else if (algorithm2 == "merge-sort") {
			mergeSort(temp, n);
		} else if (algorithm2 == "quick-sort") {
			quickSort(temp, 0, n - 1);
		} else if (algorithm2 == "counting-sort") {
			countingSort(temp, n);
		} else if (algorithm2 == "radix-sort") {
			radixSort(temp, n);
		} else if (algorithm2 == "flash-sort") {
			flashSort(temp, n);
		} else {
			cerr << "Error: Unsupported sorting algorithm!\n";
			delete[] temp;
			return;
		}
		clock_t end2 = clock();
		totalTime2 += getTime(start2, end2);
		comparisonCount2 += comparisonCount;
	}
	double elapsedTime2 = totalTime2 / iterations;
	comparisonCount2 /= iterations;

	// Print result
    cout << "-------------------------\n";
    if (outputParam == "-time" || outputParam == "-both") {
        cout << "Running time: " << elapsedTime1 << " ms | "<< elapsedTime2 << " ms \n"; 
    }
    
	if (outputParam == "-comp" || outputParam == "-both") {
        cout << "Comparisons: " << comparisonCount1 << " | "<< comparisonCount2 << "\n\n\n";
    }
	delete[] temp;
}

int main(int argCount, char* argv[]) {
	string mode = argv[1];
	if (mode != "-a" && mode != "-c") {
		cerr << "\nError: Unsupported mode! Only '-a' and '-c' are supported. \n";
		return -1;
	}

	if (mode == "-a") {
		if (argCount == 5) {
			string algorithm = argv[2];

			string argv3 = argv[3];
			if (argv3.find(".txt") != string::npos) {
				string givenInput = argv3;
				string outputParam = argv[4];

				int* arr = nullptr;
				int n = 0;
				readFile(givenInput, arr, n);

				if (arr == nullptr) {
					cerr << "\nCan't open file " << givenInput;
					return -1;
				}

				// Command line 1
				cout << "ALGORITHM MODE \n";
				cout << "Algorithm: " << algorithm << "\n";
				cout << "Input file: " << givenInput << "\n";
				cout << "Input size:" << n << "\n";
				processSorting(algorithm, arr, n, outputParam);
				writeOutputFile(givenInput, arr, n);

				delete[] arr;
				return 0;

			} else {
				int inputSize = stringToInt(argv[3]);
				string outputParam = argv[4];
				int* arr = new int[inputSize];

				// Command line 3
				cout << "ALGORITHM MODE \n";
				cout << "Input size: " << inputSize << "\n\n";
				for (int i = 0; i < 4; i++) {
					GenerateData(arr, inputSize, i);

					cout << "Input order: ";
					switch(i) {
						case 0:
						cout << "Randomize\n";
						writeOutputFile("input_1.txt", arr, inputSize);
						break;

						case 1:
						cout << "Sorted\n";
						writeOutputFile("input_3.txt", arr, inputSize);
						break;

						case 2:
						cout << "Reversed\n";
						writeOutputFile("input_4.txt", arr, inputSize);
						break;

						case 3:
						cout << "Nearly Sorted\n";
						writeOutputFile("input_2.txt", arr, inputSize);
						break;
					}
					processSorting(algorithm, arr, inputSize, outputParam);
					cout << "\n";
				}
				delete[] arr;
				return 0;
			}

		} else if (argCount == 6) {
			string algorithm = argv[2];
			string argv3 = argv[3];
			int inputSize = stringToInt(argv3);
			int* arr = new int[inputSize];
			
			string order = argv[4];
			int orderType = 0;
			string inputOrder = "";
			if (order == "-rand") {
				inputOrder = "Randomize";
				orderType = 0;
			} else if (order == "-nsorted") {
				inputOrder = "Nearly Sorted";
				orderType = 3;
			} else if (order == "-sorted") {
				inputOrder = "Sorted";
				orderType = 1;
			} else if (order == "-rev") {
				inputOrder = "Reversed";
				orderType = 2;
			}
			string outputParam = argv[5];
			// Command line 2
			cout << "ALGORITHM MODE \n";
			cout << "Algorithm: " << algorithm << "\n";
			cout << "Input size: " << inputSize << "\n";
			cout << "Input order: " << inputOrder << "\n";
			GenerateData(arr, inputSize, orderType);
			writeOutputFile("input.txt", arr, inputSize);
			processSorting(algorithm, arr, inputSize, outputParam);
			writeOutputFile("output.txt", arr, inputSize);

			delete[] arr;
			return 0;
		}

	} else if (mode == "-c") {
		if (argCount == 5) {
			string algorithm1 = argv[2];
			string algorithm2 = argv[3];
			string givenInput = argv[4];
			int* arr1 = nullptr;
			int* arr2 = nullptr;
			int n = 0;
			readFile(givenInput, arr1, n);
			readFile(givenInput, arr2, n);

			if (arr1 == nullptr) {
				cerr << "\nCan't open file " << givenInput;
				return -1;
			}

			if (arr2 == nullptr) {
				cerr << "\nCan't open file " << givenInput;
				return -1;
			}

			// Command line 4
			cout << "COMPARE MODE \n";
			cout << "Algorithm: " << algorithm1 << " | " << algorithm2 << "\n";
			cout << "Input file: " << givenInput << "\n";
			cout << "Input size: " << n << "\n";
			process2Sorting(algorithm1, algorithm2, arr1, arr2, n, "-both");

			delete[] arr1;
			delete[] arr2;
			return 0;

		} else if (argCount == 6) {
			string algorithm1 = argv[2];
			string algorithm2 = argv[3];
			string argv4 = argv[4];
			int inputSize = stringToInt(argv4);

			string order = argv[5];
			int orderType = 0;
			string inputOrder = "";
			if (order == "-rand") {
				inputOrder = "Randomize";
				orderType = 0;
			} else if (order == "-nsorted") {
				inputOrder = "Nearly Sorted";
				orderType = 3;
			} else if (order == "-sorted") {
				inputOrder = "Sorted";
				orderType = 1;
			} else if (order == "-rev") {
				inputOrder = "Reversed";
				orderType = 2;
			}

			int* arr1 = new int[inputSize];
			int* arr2 = new int[inputSize];
			GenerateData(arr1, inputSize, orderType);
			writeOutputFile("input.txt", arr1, inputSize);
			GenerateData(arr2, inputSize, orderType);
			cout<< "COMPARE MODE\n";
            cout<< "Algorithm: " << algorithm1 << " | " << algorithm2 << "\n";
            cout<< "Input size: " << inputSize << "\n";
            cout<< "Input order: " << inputOrder << "\n";
			process2Sorting(algorithm1, algorithm2, arr1, arr2, inputSize, "-both");
			
			delete[] arr1;
			delete[] arr2;
			return 0;
		}
	}
}
