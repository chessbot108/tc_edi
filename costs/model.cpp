#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int arr[1010], cnt[1010];

int main(){
	int n;
	cin >> n;
	
	for(int i = 0; i<n; i++){
		cin >> arr[i];
	}
	sort(arr, arr+n);
	int mean = 0, median = 0, mode = arr[0], sum = 0;
	//finding the mean
	for(int i = 0; i<n; i++){
		sum += arr[i];
	}
	mean = sum/n;

	//finding the median
	if(n%2 == 0){
		median = (arr[(n/2) -1] + arr[(n/2)])/2;
	}else{
		median = arr[n/2];
	}

	//finding the mode
	for(int i = 0; i<n; i++){
		cnt[arr[i]]++;
	}
	for(int i = 0; i<n; i++){
		if(cnt[arr[i]] > cnt[mode] || (cnt[arr[i]] == cnt[mode] && arr[i] > mode)){
			mode = arr[i];
		}
	}
	cout << mean << "\n" << median << "\n" << mode << "\n";
	return 0;
}
