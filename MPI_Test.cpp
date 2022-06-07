#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include "/usr/include/x86_64-linux-gnu/mpich/mpi.h"

using namespace std;
using namespace std::chrono;

int max_sum = INT32_MIN;
const int root = 0;

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

int main(int argc, char **argv) {
    int rank, commSize;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &commSize);

    double start, end;
    vector<int> arr;
    vector<int> pos;
    ifstream is("data.txt");

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

    start = MPI_Wtime();

    int parts = (pos.size() - 1) / commSize;

    for(int j = parts * rank; j < pos.size() - 1 && j < parts * (rank + 1); ++j) {
        process(arr, pos[j], pos[j + 1]);
    }

    if(rank != root) {
        MPI_Send(&max_sum, 1, MPI_INT, root, 0, MPI_COMM_WORLD);
    } else {
        cout << "parts " << parts << "\n";

        for(int j = 1; j < commSize; ++j) {
            int max;
            MPI_Recv(&max, 1, MPI_INT, j, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
    }

    end = MPI_Wtime();

    if (rank == root) {
        cout << "max sum is " << max_sum;

        printf("\nTime elapsed: %.5f\n", end - start);
    }

    MPI_Finalize();
    return 0;
}