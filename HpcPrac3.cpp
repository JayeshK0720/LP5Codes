#include<iostream>
#include<omp.h>
#include<chrono>
using namespace std;
using namespace std::chrono;

int sum_sequential(int arr[], int n){
    int sum =0;
    for(int i=0; i<n;i++){
        sum += arr[i];
    }
    return sum;
}

int sum_parallel(int arr[], int n){
    int sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for(int i=0; i<n; i++) sum += arr[i];
    return sum;
}

float avg_sequential(int arr[], int n){
    int sum = sum_sequential(arr, n);
    // return static_cast<float>(sum) / n;
    return sum/n;
}

float avg_parallel(int arr[], int n){
    int sum = sum_parallel(arr, n);
    // return static_cast<float>(sum) / n;
    return sum/n;
}

int min_sequential(int arr[], int n){
    int minVal = INT_MAX; // 9999999
    for(int i=0; i<n; i++){
        if(arr[i] < minVal) minVal = arr[i];
    }
    return minVal;
}

int min_parallel(int arr[], int n){
    int minVal = INT_MAX; 
    #pragma omp parallel for reduction(min:minVal)
    for(int i=0; i<n; i++){
        if(arr[i] < minVal) minVal = arr[i];
    }
    return minVal;
}

int max_sequential(int arr[], int n){
    int maxVal = INT_MIN; // 00000
    for(int i=0; i<n; i++){
        if(arr[i] > maxVal) maxVal = arr[i];
    }
    return maxVal;
}

int max_parallel(int arr[], int n){
    int maxVal = INT_MIN;
    #pragma omp parallel for reduction(max:maxVal)
    for(int i=0; i<n; i++){
        if(arr[i] > maxVal) maxVal = arr[i];
    }
    return maxVal;
}

// long long prod_sequential(int arr[], int n){
//     long long prod = 1;
//     for(int i=0; i<n; i++){
//         prod *= arr[i];
//     }
//     return prod;
// }

// long long prod_parallel(int arr[], int n) {
//     long long prod = 1;
//     #pragma omp parallel for reduction(*:prod)
//     for (int i = 0; i < n; i++) {
//         if (arr[i] == 0) {
//             prod = 0; // if any element is zero, product is zero
//         } else {
//             prod *= arr[i];
//         }
//     }
//     return prod;
// }

int main(){
    int n, ch;
    cout<<"Enter 1-User Defined Array | 2-Static Array : ";
    cin>>ch;
    cout<<"Enter array length | Any-Custom array | 100-Static Array : ";
    cin>> n;
    int arr[n];

    if(ch == 1){
        for(int i=0; i<n; i++){
            cout<<"Enter element at position " << i << " : ";
            cin>>arr[i];
        }
        cout<<endl<<endl;
    } else{
        int arr2[100] = {52, 93, 15, 72, 61, 21, 83, 87, 75, 75, 88, 24, 3, 22,
            53, 2, 88, 30, 38, 2, 64, 60, 21, 33, 76, 58, 22, 89, 49, 91, 59, 42, 92, 60,
            80, 15, 62, 62, 47, 62, 51, 55, 64, 3, 51, 7, 21, 73, 39, 18, 4, 89, 60, 14, 9,
            90, 53, 2, 84, 92, 60, 71, 44, 8, 47, 35, 78, 81, 36, 50, 4, 2, 6, 54, 4, 54,
            93, 63, 18, 90, 44, 34, 74, 62, 14, 95, 48, 15, 72, 78, 87, 62, 40, 85, 80, 82,
            53, 24, 26, 89};

        for(int i=0; i<n; i++){
            arr[i] = arr2[i];
        }    
    }

    cout<< "Array = ";
    for(int i=0; i<n; i++){
        cout<<arr[i] << ",";
    }
    cout<<endl<<endl;

    while(true){
        cout<<"Enter 1-Sum | 2-Avg | 3-Min | 4-Max | 5-Product | 0-Exit : ";
        cin>>ch;

        if(ch == 1){
            int ans;
            auto start = high_resolution_clock::now();
            ans = sum_sequential(arr,n);
            auto end = high_resolution_clock::now();
            cout<<"Sum Sequential Answer = "<< ans<<endl;
            cout<<"Sum Sequential Time = " << duration_cast<nanoseconds>(end-start).count() << " ns"<<endl;

            start = high_resolution_clock::now();
            ans = sum_parallel(arr,n);
            end = high_resolution_clock::now();
            cout<<"Sum Parallel Answer = "<<ans<<endl;
            cout<<"Sum Parallel Reduction Time = " <<duration_cast<nanoseconds>(end-start).count()<< " ns"<<endl;
        } else if(ch==2){
            float ans;
            auto start = high_resolution_clock::now();
            ans = avg_sequential(arr,n);
            auto end = high_resolution_clock::now();
            cout<<"Avg Sequential Answer = "<<ans<<endl;
            cout<<"Avg Sequential Time = "<<duration_cast<nanoseconds>(end - start).count()<<" ns"<<endl;

            start = high_resolution_clock::now();
            ans = avg_parallel(arr,n);
            end = high_resolution_clock::now();
            cout<<"Avg Parallel Answer = "<<ans<<endl;
            cout<<"Avg Parallel Reduction Time = "<<duration_cast<nanoseconds>(end-start).count();<<" ns"<<endl;
        }
        else if (ch == 3)
        {
            int ans;
            auto start = high_resolution_clock::now();
            ans = min_sequential(arr, n);
            auto end = high_resolution_clock::now();
            cout << "Min Sequential Answer = " << ans << endl;
            cout << "Min Sequential Time = " << duration_cast<nanoseconds>(end - start).count() << " ns" << endl;

            start = high_resolution_clock::now();
            ans = min_parallel(arr, n);
            end = high_resolution_clock::now();
            cout << "Min Parallel Answer = " << ans << endl;
            cout << "Min Parallel Reduction Time = " << duration_cast<nanoseconds>(end - start).count() << " ns" << endl << endl;
        }
        else if (ch == 4)
        {
            int ans;
            auto start = high_resolution_clock::now();
            ans = max_sequential(arr, n);
            auto end = high_resolution_clock::now();
            cout << "Max Sequential Answer = " << ans << endl;
            cout << "Max Sequential Time = " << duration_cast<nanoseconds>(end - start).count() << " ns" << endl;

            start = high_resolution_clock::now();
            ans = max_parallel(arr, n);
            end = high_resolution_clock::now();
            cout << "Max Parallel Answer = " << ans << endl;
            cout << "Max Parallel Reduction Time = " << duration_cast<nanoseconds>(end - start).count() << " ns" << endl << endl;
        }
        // else if(ch == 5){
        //     long long ans;
        //     auto start = high_resolution_clock::now();
        //     ans = prod_sequential(arr, n);
        //     auto end = high_resolution_clock::now();
        //     cout<< "Product = " <<ans<<endl;
        //     cout<< "Product Sequential Time = "<<duration_cast<nanoseconds>(end - start).count()<< " ns"<<endl;
            
        //     start = high_resolution_clock::now();
        //     ans = prod_parallel(arr, n);
        //     end = high_resolution_clock::now();
        //     cout<< "Product = " <<ans<<endl;
        //     cout<< "Product Parallel Time = "<<duration_cast<nanoseconds>(end - start).count()<< " ns"<<endl; 
        // }
        else if (ch == 0)
        {
            cout << "Exited Successfully." << endl;
            break;
        }
        else
        {
            cout << "Invalid Choice." << endl << endl;
        }
    }
    return 0;
}

// to run this file:
// g++ filename.cpp -o filename -fopenmp -std=c++11
// ./filename