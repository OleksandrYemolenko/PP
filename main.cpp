#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

int max_sum = INT32_MIN;

long curTime(){
    milliseconds ms = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
    return ms.count();
}

void process(vector<int> arr, int a, int b) {
    int curr_sum = 0;

    for(int i = a; i <= b; ++i) {
        if(arr[i] != 0)
            curr_sum += arr[i];
        else {
            if(curr_sum > max_sum)
                max_sum = curr_sum;
        }
    }
}

int main() {
    double start, end;

    vector<int> arr;
    vector<int> pos;
    ifstream is("data2L.txt");

    pos.push_back(0);

    int x;
    int i = 0;
    while (is >> x) {
        if (x == 0)
            pos.push_back(i);
        arr.push_back(x);

        ++i;
    }
    is.close();

    start = curTime();

    for(int j = 0; j < pos.size() - 1; ++j) {
        process(arr, pos[j], pos[j + 1]);
    }

    end = curTime();

    cout << "max sum is " << max_sum;

    printf("\nTime elapsed: %.5f\n", (end-start)/1000);

    return 0;
}