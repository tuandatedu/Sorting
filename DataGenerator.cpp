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



double getTime(clock_t start, clock_t end) {
    return ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0; 
}


long long comparisonCount = 0;


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
            comparisonCount+=2;
			arr[current] = arr[current - 1];
			current--;
		}
        if(current>0){
            comparisonCount++;
        }
		arr[current] = temp;
	}
    comparisonCount++;
}

void bubbleSort(int arr[], int n)
{

	int index = 1, temp;
	while (++comparisonCount&&index != 0)
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
	while (++comparisonCount && nmax / index>0)
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

void flashSort(int arr[], int n)
{
	int maxVal = arr[0], minVal = arr[0], maxIndex = 0;
	for (int i = 1; i < n; i++)
	{
        comparisonCount++;
		if (arr[i] > maxVal)
		{
			maxVal = arr[i];
			maxIndex = i;
		}
        comparisonCount++;
		if (arr[i] < minVal)
			minVal = arr[i];
        comparisonCount++;
	}
    comparisonCount++;
    comparisonCount++;
	if (maxVal == minVal){
        return;
    }

	int m = floor(0.45 * n);  
	int* L = new int[m]();
	int k;
	for (int i = 0; i < n; i++)
	{
        comparisonCount++;
		k = floor((m - 1) * (arr[i] - minVal) / (maxVal - minVal));
		L[k]++;
	}
    comparisonCount++;

	for (int i = 1; i < m; i++)
	{
        comparisonCount++;
		L[i] += L[i - 1];  
	}
    comparisonCount++;

	int count = 0, index = 0;
	while (++comparisonCount&&count < n)
	{
		k = floor((m - 1) * (arr[index] - minVal) / (maxVal - minVal));
		while (++comparisonCount&&index >= L[k])
		{
			k = floor((m - 1) * (arr[++index] - minVal) / (maxVal - minVal));
		}
		int temp = arr[index];
		while (++comparisonCount&&index < L[k])
		{
			k = floor((m - 1) * (temp - minVal) / (maxVal - minVal));
			swap(temp, arr[--L[k]]);
			count++;
		}
	}
	delete[] L;

    insertionSort(arr, n);
}

void shakerSort(int arr[], int n)
{
	int bienPhai, bienTrai;
	int left = 0, right = n - 1;
	while (++comparisonCount&&left < right)
	{
		bienPhai = -1;
		bienTrai = -1;
		for (int i = left; i < right; i++)
		{
            comparisonCount+=2;

			if (arr[i] > arr[i + 1])
			{
				HoanVi(arr[i], arr[i + 1]);
				bienPhai = i;
			}
		}
        comparisonCount+=2;
		if (bienPhai == -1)
		{
			break;
		}
		right = bienPhai;
        comparisonCount++;
		if (left == right) break;
		
		for (int i = right; i > left; i--)
		{
            comparisonCount+=2;
			if (arr[i] < arr[i - 1])
			{
				HoanVi(arr[i], arr[i - 1]);
				bienTrai = i;
			}
		}
        comparisonCount+=2;
		if (bienTrai == -1)
		{
			break;
		}
		left = bienTrai;
	}
}

void selectionSort(int a[], int n) {
	int comparisonCount = 0;
	for (int i = 0; i < n -1 ; i++) {
		int min = i;
		for (int j = 1 +i; j < n ; j++) {
			comparisonCount++;
			if (a[j] < a[min]) {
				min = j;
			}
		}
		swap(a[i], a[min]);
	}

}

void countingSort(int a[], int n) {

	int maxVal = a[0];
	int comparisonCount = 0;
	for (int i = 1; i < n; i++) {
		comparisonCount++;
		if (a[i] > maxVal) {
			maxVal = a[i];
		}
	}

	int size = maxVal + 1;
	int* output = new int[n];
	int* count = new int[size];

	for (int i = 0; i < size; i++) {
		count[i] = 0;
	}

	for (int i = 0; i < n; i++) {
		count[a[i]]++;
	}

	for (int i = 1; i < size; i++) {
		comparisonCount++;
		count[i] += count[i - 1];
	}

	for (int i = n - 1; i >= 0; i--) {
		output[count[a[i]] - 1] = a[i];
		count[a[i]]--;
	}

	for (int i = 0; i < n; i++) {
		a[i] = output[i];
	}

	delete[] count;
	delete[] output;
}


void readFile(const string &filename, int*& arr, int&n) {
    fstream fin(filename);
    if(!fin){
        cerr<<"Error!\n";
        return;
    }
    string n_temp;
    fin>>n_temp;
    n = stringToInt(n_temp);
    arr = new int[n];
    for(int i =0;i<n;i++){
        fin>>arr[i];
    }
    fin.close();
}


void writeOutputFile(const string &filename, int arr[], int n) {
    ofstream file(filename);
    if (!file) {
        cerr << "Error: Cannot open output file!\n";
        return;
    }

    file << n << endl;
    for (int i = 0; i < n; i++) {
        file << arr[i] << " ";
    }
    file.close();
}

// Hàm xử lý thuật toán sắp xếp
void processSorting(const string &algorithm, int arr[], int n, const string &outputParam) {
    clock_t start = clock();
    //cho chạy nhiều lần để tính thời gian trung bình => Độ chính xác cao hơn
    /*for(int i =0;i<1000;i++){
        int temparr[n];
        for(int j=0;j<n;j++){
            temparr[j]= temparr[j];
        }
        if (algorithm == "insertion-sort") {
            insertionSort(temparr, n);
        }
        else if(algorithm=="flash-sort"){
            flashSort(temparr,n);
        } 
        else if(algorithm=="shaker-sort"){
            shakerSort(temparr,n);
        }
        else if(algorithm=="bubble-sort"){
            bubbleSort(temparr,n);
        }
        else if(algorithm=="radix-sort"){
            radixSort(temparr,n);
        }
        else {
            cerr << "Error: Unsupported sorting algorithm!\n";
            return;
        }
    }
        */
    comparisonCount = 0;
    if (algorithm == "insertion-sort") {
        insertionSort(arr, n);
    }
    else if(algorithm=="flash-sort"){
        flashSort(arr,n);
    } 
    else if(algorithm=="shaker-sort"){
        shakerSort(arr,n);
    }
    else if(algorithm=="bubble-sort"){
        bubbleSort(arr,n);
    }
    else if(algorithm=="radix-sort"){
        radixSort(arr,n);
    }
    else {
        cerr << "Error: Unsupported sorting algorithm!\n";
        return;
    }

    clock_t end = clock();
    double elapsedTime = getTime(start,end);

    // Xuất kết quả ra màn hình
    cout << "-------------------------\n";
    if (outputParam == "-time" || outputParam == "-both") {
        cout << "Running time: " << elapsedTime << " ms\n";
    }
    if (outputParam == "-comp" || outputParam == "-both") {
        cout << "Comparisons: " << comparisonCount << endl;
    }
}

void process2Sorting(const string &algorithm1,const string &algorithm2, int arr1[],int arr2[], int n, const string &outputParam) {
    long long comparisonCount1 = 0;
    long long comparisonCount2 = 0;

    clock_t start1 = clock();

        

    comparisonCount =0;
    // Chạy thuật toán 1 theo yêu cầu
    if (algorithm1 == "insertion-sort") {
        insertionSort(arr1, n);
    }
    else if(algorithm1=="flash-sort"){
        flashSort(arr1,n);
    } 
    else if(algorithm1=="shaker-sort"){
        shakerSort(arr1,n);
    }
    else if(algorithm1=="bubble-sort"){
        bubbleSort(arr1,n);
    }
    else if(algorithm1=="radix-sort"){
        radixSort(arr1,n);
    }
    else {
        cerr << "Error: Unsupported sorting algorithm!\n";
        return;
    }

    clock_t end1 = clock();
    comparisonCount1 = comparisonCount;
    double elapsedTime1 = getTime(start1,end1);

    clock_t start2 = clock();
    
        

    comparisonCount =0;
    // Chạy thuật toán 2 theo yêu cầu
    if (algorithm2 == "insertion-sort") {
        insertionSort(arr2, n);
    }
    else if(algorithm2=="flash-sort"){
        flashSort(arr2,n);
    } 
    else if(algorithm2=="shaker-sort"){
        shakerSort(arr2,n);
    }
    else if(algorithm2=="bubble-sort"){
        bubbleSort(arr2,n);
    }
    else if(algorithm2=="radix-sort"){
        radixSort(arr2,n);
    }
    else {
        cerr << "Error: Unsupported sorting algorithm!\n";
        return;
    }

    clock_t end2 = clock();
    comparisonCount2 = comparisonCount;
    double elapsedTime2 = getTime(start2,end2)/100;

    // Xuất kết quả ra màn hình
    cout << "-------------------------\n";
    if (outputParam == "-time" || outputParam == "-both") {
        cout << "Running time: " << elapsedTime1 << " ms | "<<elapsedTime2<<" ms\n"; 
    }
    if (outputParam == "-comp" || outputParam == "-both") {
        cout << "Comparisons: " << comparisonCount1 << " | "<<comparisonCount2<<endl;
    }

}

// Hàm main xử lý command line
int main(int argc, char* argv[]) {
    string mode = argv[1];
    if (mode != "-a"&& mode!="-c") {
        cerr << "Error: Unsupported mode! Only '-a' and '-c' are supported.\n";
        return 1;
    }
    if(mode=="-a"){
        if(argc==5){
            string algorithm = argv[2];

            string argv3 = argv[3];
            if(argv3.find(".txt")!= string::npos){
                string given_input = argv3;
                string output_para = argv[4];

                int* arr;
                int n;
                readFile(given_input,arr,n);

                //Command line 1
                cout<<"ALGORITHM MODE\n";
                cout<<"Algorithm: "<<algorithm<<endl;
                cout<<"Input file: "<<given_input<<endl;
                cout<<"Input size: "<< n<<endl;

                processSorting(algorithm,arr,n,output_para);
                writeOutputFile("output.txt",arr,n);
                delete arr;
                return 0;

            }
            else{
                int input_size = stringToInt(argv3);
                string output_para = argv[4];
                int* arr = new int[input_size];
                cout<<"ALGORITHM MODE\n";
                cout<<"Input size: "<<input_size<<endl<<endl;
                for(int i=0;i<4;i++){
                    GenerateData(arr,input_size,i);
                    cout<<"Input order: ";
                    switch(i){
                        case 0: 
                        cout<<"Randomize\n";
                        writeOutputFile("input_1.txt",arr,input_size);
                        break;
                        case 1: 
                        cout<<"Sorted\n"; 
                        writeOutputFile("input_3.txt",arr,input_size);
                        break;
                        case 2: 
                        cout<<"Reversed\n";
                        writeOutputFile("input_4.txt",arr,input_size);
                        break;
                        case 3: 
                        cout<<"Nearly Sorted\n"; 
                        writeOutputFile("input_2.txt",arr,input_size);
                        break;
                    }
                    processSorting(algorithm,arr,input_size,output_para);
                    cout<<endl;
                }
                delete arr;
                return 0;
            }
        }
        else if(argc==6){
            string algorithm = argv[2];
            string argv3 = argv[3];
            int input_size = stringToInt(argv3);
            int*arr = new int[input_size];
            string order = argv[4];
            int order_type;
            string input_order;
            if(order=="-rand"){
                input_order="Randomize";
                order_type=0;
            }
            else if(order=="-nsorted"){
                input_order = "Nearly Sorted";
                order_type=3;
            }
            else if(order=="-sorted"){
                input_order ="Sorted";
                order_type=1;
            }
            else if(order=="-rev"){
                input_order = "Reversed";
                order_type=2;
            }
            string output_para = argv[5];
            cout<<"ALGORITHM MODE\n";
            cout<<"Algorithm: "<<algorithm<<endl;
            cout<<"Input size: "<<input_size<<endl;
            cout<<"Input order: "<<input_order<<endl;
            GenerateData(arr,input_size,order_type);
            writeOutputFile("input.txt",arr,input_size);
            processSorting(algorithm,arr,input_size,output_para);
            writeOutputFile("output.txt",arr,input_size);
            delete arr;
            return 0;
        }
    }

    else if(mode=="-c"){
        if(argc ==5){
            string algorithm1 = argv[2];
            string algorithm2 = argv[3];
            string given_input = argv[4];
            int* arr1;
            int* arr2;
            int n;
            readFile(given_input,arr1,n);
            readFile(given_input,arr2,n);
            cout<<"COMPARE MODE\n";
            cout<<"Algorithm: "<<algorithm1<<" | "<<algorithm2<<endl;
            cout<<"Input file: "<<given_input<<endl;
            cout<<"Input size: "<<n<<endl;
            process2Sorting(algorithm1,algorithm2,arr1,arr2,n,"-both");
            delete arr1,arr2;
            return 0;
        }
        else if(argc ==6){
            string algorithm1 = argv[2];
            string algorithm2 = argv[3];
            string argv4 = argv[4];
            int input_size = stringToInt(argv4);

            string order = argv[5];
            int order_type;
            string input_order;
            if(order=="-rand"){
                input_order="Randomize";
                order_type=0;
            }
            else if(order=="-nsorted"){
                input_order = "Nearly Sorted";
                order_type=3;
            }
            else if(order=="-sorted"){
                input_order ="Sorted";
                order_type=1;
            }
            else if(order=="-rev"){
                input_order = "Reversed";
                order_type=2;
            }
            int* arr1 = new int[input_size];
            int* arr2 = new int[input_size];
            GenerateData(arr1,input_size,order_type);
            writeOutputFile("input.txt",arr1,input_size);
            GenerateData(arr2,input_size,order_type);
            cout<<"COMPARE MODE\n";
            cout<<"Algorithm: "<<algorithm1<< " | "<<algorithm2<<endl;
            cout<<"Input size: "<<input_size<<endl;
            cout<<"Input order: "<<input_order<<endl;
            process2Sorting(algorithm1,algorithm2,arr1,arr2,input_size,"-both");
            delete arr1,arr2;
            return 0;
        }
    }

}
