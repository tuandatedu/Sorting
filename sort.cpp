#include <iostream>
using namespace std;

void max_heapify(int a[100], int n, int i){
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if(left < n && a[left] > a[largest]){ // nếu con trái tồn tại và lớn hơn cha
        largest = left; // đổi giá trị giữa cha với con
    }

    if(right < n && a[right] > a[largest]){ // nếu con phải tồn tại, lớn hơn cha 
        largest = right;
    }

    if(largest != i){ // nếu nút cha ko phải là cha ban đầu
        swap(a[i], a[largest]);
        max_heapify(a, n,largest);
    }
}

void build_maxheap(int a[100], int n){
    for(int i = n/2 - 1; i >= 0; i--){ //duyệt từ nút cha cuối lên gốc
        max_heapify(a, n,i);
    }
}

void heap_sort(int a[100], int n){
    build_maxheap(a,n); // bước 1: xây dựng max_heap

    for(int i = n-1; i > 0; i--){
        swap(a[i], a[0]); //đưa max về cuối
        max_heapify(a, i, 0); //gọi heapify trên phần còn lại
    }
}

// shell sort
void shell_sort(int a[100], int n){
    int gap = n/2;

    while(gap > 0){
        for(int i = 0; i < n; i++){
            int temp = a[i];
            int j = i;
            while (j >= gap && a[j - gap] > temp)
            {
                a[j] = a[j - gap];
                j = j-gap;
            }
            a[j] = temp;
        }
        cout << "\n";
        for(int i = 0; i < n; i++){
            cout << a[i] << " ";
        }
        gap /= 2;
    }
}

int main(){
    int n;
    int a[100];

    cout << "Nhập số phần tử mảng: "; cin >> n;

    cout << "Nhập mảng: " << endl;
    for(int i = 0; i < n; i++){
        cout << "Nhập phần a[" << i << "]: ";
        cin >> a[i];
    }

    // heap_sort(a, n);

    shell_sort(a, n);

    cout << "\n";
    for(int i = 0; i < n; i++){
        cout << a[i] << " ";
    }
}