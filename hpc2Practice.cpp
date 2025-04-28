#include<iostream>
#include<omp.h>
#include<chrono>

using namespace std;
using namespace std::chrono;

void bubble_sort_sequential(int arr[], int n){

    for(int i=0; i<n-1; i++){
        for(int j=0; j<n-1-i; j++){
            if(arr[j] > arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void bubble_sort_parallel(int arr[], int n){
     
    for(int i=0; i<n-1; i++){

        #pragma omp parallel for
        for(int j=0; j<n-1-i; j++){
            #pragma omp critical
            if(arr[j] > arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void merge(int arr[], int lower, int middle, int higher){
    int n1 = middle - lower + 1, n2 = higher - middle;
    int leftArray[n1], rightArray[n2];

    for(int i=0; i<n1; i++){
        leftArray[i] = arr[lower + i];
    }
    for(int i=0; i<n2; i++){
        rightArray[i] = arr[middle + 1 + i];
    }

    int i=0, j=0, k=lower;
    while(i<n1 && j<n2){
        if(leftArray[i] < rightArray[j]){
            arr[k++] = leftArray[i++];
        } else{
            arr[k++] = rightArray[j++];
        }
    }

    while(i<n1){
        arr[k++] = leftArray[i++];
    }

    while(j<n2){
        arr[k++] = rightArray[j++];
    }
}

void merge_sort_sequential(int arr[], int lower, int higher){
    if(lower < higher){
        int middle = lower + (higher - lower)/2;
        merge_sort_sequential(arr, lower, middle);
        merge_sort_sequential(arr, middle+1, higher);
        merge(arr, lower, middle, higher);
    }
}

void merge_sort_parallel(int arr[], int lower, int higher){
    if(lower < higher){
        int middle = lower + (higher - lower)/2;
        #pragma omp parallel
        merge_sort_parallel(arr, lower, middle);
        #pragma omp parallel
        merge_sort_parallel(arr, middle+1, higher);
        #pragma omp critical
        merge(arr, lower, middle, higher);
    }
}

int main(){
    int n, ch;

    cout<< "Enter 1-User Defined Array | 2-Static Array : ";
    cin>>ch;

    cout<<"Enter Array Length | Any Custom Array | 100-Static Array : ";
    cin>>n;
    int arr[n]; 

    if(ch==1){
        for(int i=0; i<n; i++){
            cout<<"Enter element at position " << i << " : ";
            cin>> arr[i];
        }
        cout<<endl<<endl;
    }
    else{
        int arr2[100] = {53, 32, 13, 34, 14, 56, 45, 10, 4, 2, 20, 7, 6, 89, 63, 12, 4, 7, 8, 94, 25, 31, 21, 74, 32, 22, 28, 45, 61, 78, 14, 38, 76, 41, 68, 58, 91, 74, 63, 31, 21, 32, 27, 16, 73, 20, 18, 96, 37, 75, 24, 16,14, 3, 1, 8, 92, 67, 6, 44, 22, 11, 33, 88, 66, 77, 99, 55, 85, 36, 86};
        for(int i=0; i<n; i++){
            arr[i] = arr2[i];
        }
    }

    cout<<"Unsorted Array : ";
    for(int i=0; i<n; i++){
        cout<<arr[i] << ",";
    }
    cout<<endl<<endl;


    while(true){
        cout<<"Enter 1-Bubble Sequential | 2-Bubble Parallel | 3-Merge Sequential | 4-Merge Parallel | 5-Exit : ";
        cin>>ch;

        auto start = high_resolution_clock::now();

        if(ch==1){
            bubble_sort_sequential(arr, n);
            cout<<"Bubble Sequential Sort." << endl;
        } else if(ch==2){
            bubble_sort_parallel(arr, n);
            cout<<"Bubble Parallel Sort." << endl;
        } else if(ch==3){
            merge_sort_sequential(arr, 0, n-1);
            cout<<"Merge Sequential Sort." << endl;
        } else if(ch==4){
            merge_sort_parallel(arr, 0, n-1);
            cout<<"Merge Parallel Sort." << endl;
        } else if(ch==5){
            cout<<"Exited Successfully!!";
            break;
        } else{
            cout<<"Invalid Choice!!";
        }

        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);

        cout<<"Answer : ";
        for(int i=0; i<n; i++){
            cout<<arr[i] << ",";
        }
        cout<<endl<<endl;

        cout<<"Time : "<< duration.count() << " microseconds" << endl;
        cout<<endl;
    }
    return 0;
}

// to run this file:
// g++ filename.cpp -o filename -fopenmp -std=c++11
// ./filename