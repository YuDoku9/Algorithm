#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

// Bubble Sort (for initial sorting before search)
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
}

// Binary Search
int binarySearch(int arr[], int n, int target) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid] == target)
            return mid;
        if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

// Exponential Search
int exponentialSearch(int arr[], int n, int target) {
    if (arr[0] == target)
        return 0;
    int i = 1;
    while (i < n && arr[i] <= target)
        i = i * 2;
    return binarySearch(arr, min(i, n - 1) + 1, target);
}

// Quick Sort
void quickSort(int arr[], int low, int high) {
    if (low >= high)
        return;
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++)
        if (arr[j] <= pivot)
            swap(arr[++i], arr[j]);
    swap(arr[i + 1], arr[high]);
    quickSort(arr, low, i);
    quickSort(arr, i + 2, high);
}

// Merge Sort
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1, n2 = right - mid;
    int L[50], R[50];
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int i = 0; i < n2; i++) R[i] = arr[mid + 1 + i];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(int arr[], int left, int right) {
    if (left >= right)
        return;
    int mid = (left + right) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

int main() {
    int n, target;
    cout << "Enter number of elements: ";
    cin >> n;

    int arr[n], arrQuick[n], arrMerge[n];
    cout << "Enter " << n << " numbers:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        arrQuick[i] = arr[i];
        arrMerge[i] = arr[i];
    }

    // Bubble Sort before searching
    bubbleSort(arr, n);
    cout << "\nSorted Array: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    cout << "\nEnter number to search: ";
    cin >> target;

    // Binary Search
    auto start1 = high_resolution_clock::now();
    int binRes = binarySearch(arr, n, target);
    auto stop1 = high_resolution_clock::now();
    cout << "\nBinary Search: " << (binRes != -1 ? "Found" : "Not Found") << endl;
    cout << "Time: " << duration_cast<microseconds>(stop1 - start1).count() << " microseconds\n";

    // Exponential Search
    auto start2 = high_resolution_clock::now();
    int expRes = exponentialSearch(arr, n, target);
    auto stop2 = high_resolution_clock::now();
    cout << "\nExponential Search: " << (expRes != -1 ? "Found" : "Not Found") << endl;
    cout << "Time: " << duration_cast<microseconds>(stop2 - start2).count() << " microseconds\n";

    // Quick Sort
    auto start3 = high_resolution_clock::now();
    quickSort(arrQuick, 0, n - 1);
    auto stop3 = high_resolution_clock::now();
    cout << "\nQuick Sort Result: ";
    for (int i = 0; i < n; i++) cout << arrQuick[i] << " ";
    cout << "\nTime: " << duration_cast<microseconds>(stop3 - start3).count() << " microseconds\n";

    // Merge Sort
    auto start4 = high_resolution_clock::now();
    mergeSort(arrMerge, 0, n - 1);
    auto stop4 = high_resolution_clock::now();
    cout << "\nMerge Sort Result: ";
    for (int i = 0; i < n; i++) cout << arrMerge[i] << " ";
    cout << "\nTime: " << duration_cast<microseconds>(stop4 - start4).count() << " microseconds\n";

    return 0;
}
