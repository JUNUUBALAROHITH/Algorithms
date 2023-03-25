#include <bits/stdc++.h>
using namespace std;

struct node
{
    int key;
    node *next;
};

typedef struct node node;

node *createNode(int n)
{
    node *temp = new node;
    temp->key = n;
    temp->next = NULL;
    return temp;
}

node *append(node *head, int n)
{
    node *temp = head;
    while (temp->next)
    {
        temp = temp->next;
    }
    temp->next = createNode(n);
    return head;
}

void bucketSort(int arr[], int k, int n)
{
    node *count[k + 1];
    for (int i = 0; i <= k; i++)
    {
        count[i] = NULL;
    }
    for (int i = 0; i < n; i++)
    {
        count[arr[i]] = append(count[arr[i]], arr[i]);
    }
    for (int i = 0; i <= k; i++)
    {
        node *temp = count[i];
        while (temp)
        {
            cout << temp->key << " ";
            temp = temp->next;
        }
    }
    cout << '\n';
}
void swap(int &a, int &b)
{
    int c = a;
    a = b;
    b = c;
}

// void merge(int arr[], int l, int mid, int h)
// {
//     int temp[h - l + 1], k = 0;
//     int i = l, j = mid + 1;
//     while (i <= mid && j <= h)
//     {
//         if (arr[i] <= arr[j])
//             temp[k++] = arr[i++];
//         else
//             temp[k++] = arr[j++];
//     }
//     while (i <= mid)
//         temp[k++] = arr[i++];
//     while (j <= h)
//         temp[k++] = arr[j++];
//     for (i = l; i <= h; i++)
//         arr[i] = temp[i - l];
// }

void merge(int arr[],int low,int mid,int high){
    int n1=mid-low+1,n2=high-mid;
    int left[n1],right[n2];
    for(int i=0;i<n1;i++) left[i]=arr[low+i];
    for(int i=0;i<n2;i++) right[i]=arr[low+n1+i];
    int i=0,j=0,k=0;
    while(i<n1 && j<n2){
        if(left[i]<=right[j]){ arr[k]=left[i];i++;k++; }
        else {arr[k]=right[j];j++;k++;}
    }
    while(i<n1) {arr[k]=left[i];i++;k++;}
    while(j<n2) {arr[k]=right[j];j++;k++;}
}

void mergeSort(int a[], int l, int r)
{
    if (r > l)
    {
        int m = l + (r - l) / 2;
        mergeSort(a, l, m);
        mergeSort(a, m + 1, r);
        merge(a, l, m, r);
    }
}

void maxHeapify(int arr[], int n, int i)
{
    int l = (2 * i) + 1, r = (2 * i) + 2;
    int largest = i;
    if (l < n && arr[l] > arr[largest])
        largest = l;
    if (r < n && arr[r] > arr[largest])
        largest = r;
    if (largest != i)
    {
        swap(arr[largest], arr[i]);
        maxHeapify(arr, n, largest);
    }
}

void buildHeap(int arr[], int n)
{
    for (int i = (n - 2) / 2; i >= 0; i--)
    {
        maxHeapify(arr, n, i);
    }
}

void heapSort(int arr[], int n)
{
    buildHeap(arr, n);
    for (int i = n - 1; i >= 1; i--)
    {
        swap(arr[0], arr[i]);
        maxHeapify(arr, i, 0);
    }
}

void countingSort(int arr[], int exp, int n)
{
    int count[10] = {0}, output[n] = {0};
    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; i--)
    {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

void radixSort(int arr[], int n)
{
    int m = 0;
    for (int i = 0; i < n; i++)
        m = max(m, arr[i]);
    for (int exp = 1; m / exp > 0; exp *= 10)
    {
        countingSort(arr, exp, n);
    }
}

int partition(int arr[], int l, int r)
{
    int i = l, j = r, pivot = arr[l];
    while (i < j)
    {
        while (arr[i] <= pivot && i <= r)
            i++;
        while(arr[j] > pivot)
            j--;
        if (i < j)
        {
            swap(arr[i], arr[j]);
            j--;
            i++;
        }
    }
    swap(arr[l], arr[j]);
    return j;
}

void quickSort(int arr[], int l, int r)
{
    if (l >= r)
        return;
    int index = partition(arr, l, r);
    quickSort(arr, l, index - 1);
    quickSort(arr, index + 1, r);
}

void bubbleSort(int arr[], int n)
{
    for (int i = n - 1; i >= 0; i--)
    {
        int max = 0;
        for (int j = 0; j <= i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void selectionSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int index = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[index])
            {
                index = j;
            }
        }
        if (index != i)
            swap(arr[i], arr[index]);
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int i, n;
    cin >> n;
    int arr[n];
    for (i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    // selectionSort(arr,n);
    // for(i=0;i<n;i++) cout<<arr[i]<<" ";
    quickSort(arr, 0, n - 1);
    for (i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << '\n';
}
