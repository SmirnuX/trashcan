#include <cmath>
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <ctime>

typedef float real;

struct matrix
{
    uint size;
    real** A;
    real* B;
};


matrix matrix_alloc(uint size);
void matrix_generate(matrix* mx, real max);
void matrix_dealloc(matrix* mx);

real* matrix_solve(matrix* mx); //Solve linear equation

void run_test(matrix* mx);

unsigned long long flops;
thread_local unsigned long long thr_flops;
std::mutex flops_mutex;

int main(int argc, char* argv[])
{
    uint N = 1000;   //Size of matrix
    uint repeat = 1;    //Count of tests
    uint thread_count = 8;
    if (argc == 1)
        std::cout << "Usage: ./linpack [size of problem] [number of threads] [number of tests]\n";
    if (argc > 1)
        N = std::atoi(argv[1]);
    if (argc > 2)
        thread_count = std::atoi(argv[2]);
    if (argc > 3)
        repeat = std::atoi(argv[3]);

    if (N == 0 || thread_count == 0 || repeat == 0)
    {
        std::cout << "Error: wrong arguments.\n";
        return 1;
    }

    std::cout << "Matrix: " << N <<"x" << N << '\n';
    std::cout << "Threads selected: " << thread_count << "/" << std::thread::hardware_concurrency() << '\n';
    std::srand(std::time(NULL));
    matrix* mx = new matrix[thread_count];
    for (uint i = 0; i < thread_count; i++)
        mx[i] = matrix_alloc(N);
    std::thread* threads = new std::thread[thread_count];

    for (uint i = 0; i < repeat; i++)
    {
        std::cout << "Setting up test " << i+1 << "/" <<repeat<<'\n';
        for (uint j = 0; j < thread_count; j++)
            matrix_generate(mx + j, 1.0f);
        std::cout << "Starting solving of " << thread_count << " linear equations: ";
        flops = 0;
        auto start = std::chrono::high_resolution_clock::now(); //!Timer start
        //Start tests

        for (uint j = 0; j < thread_count; j++)
            threads[j] = std::thread([mx, j] () {run_test(mx + j);});

        for (uint j = 0; j < thread_count; j++)
            threads[j].join();
        

        auto end = std::chrono::high_resolution_clock::now();   //!Timer end
        std::chrono::duration<double> diff = end-start;
        std::cout << diff.count() << "s\n";
        double MFlops = flops;
        MFlops /= diff.count() * 1000000;
        std::cout << "MFlops = " << MFlops << '\n';
    }
    

    for (uint i = 0; i < thread_count; i++)
        matrix_dealloc(mx+i);
    delete[] mx;
    delete[] threads;


    std::cout << "End";
    return 0;
}

matrix matrix_alloc(uint size)
{
    matrix result;
    result.size = size;
    result.A = new real*[size];
    for (uint i = 0; i < size; i++)
        result.A[i] = new real[size];
    result.B = new real[size];
    return result;
}

void matrix_generate(matrix* mx, real max)
{
    //Generate random matrix
    for (uint i = 0; i < mx->size; i++)
        for (uint j = 0; j < mx->size; j++)
            mx->A[i][j] = rand() / max;

    //Calculate vector B
    for (uint i = 0; i < mx->size; i++)
    {
        mx->B[i] = 0;
        for (int j = 0; j < mx->size; j++)
        {
            mx->B[i] += mx->A[i][j];
        }
    }
}

void matrix_dealloc(matrix* mx)
{
    for (uint i = 0; i < mx->size; i++)
        delete[] mx->A[i];
    delete[] mx->A;
    delete[] mx->B;
}

real* matrix_solve(matrix* mx)  //Solve linear equation
{
    //LU decompose: A = L*U
    real maxA;
    uint imax;
    uint* pivot = new uint[mx->size];   //Permutation matrix as vector
    for (uint i = 0; i < mx->size; i++)
        pivot[i] = i;
    for (uint i = 0; i < mx->size; i++)
    {
        maxA = 0;
        imax = i;

        for (uint k = i; k < mx->size; k++) //Max element
        {
            if (mx->A[k][i] > maxA)
            {
                maxA = mx->A[k][i];
                imax = k;
            }
        }

        if (imax != i) //Changinf order of rows
        {
            uint tmp = pivot[i];
            pivot[i] = pivot[imax];
            pivot[imax] = tmp;

            real* tmp_ptr = mx->A[i];
            mx->A[i] = mx->A[imax];
            mx->A[imax] = tmp_ptr;
        }

        for (uint j = i+1; j < mx->size; j++)
        {
            mx->A[j][i] /= mx->A[i][i];
            thr_flops++;

            for (uint k = i+1; k < mx->size; k++)
            {
                mx->A[j][k] -= mx->A[j][i] * mx->A[i][k];
                thr_flops += 2;
            }
        }
    }

    //Actually solving
    real* x = new real[mx->size];
    for (uint i = 0; i < mx->size; i++)
    {
        x[i] = mx->B[pivot[i]];

        for(uint k = 0; k < i; k++)
        {
            x[i] -= mx->A[i][k] * x[k];
            thr_flops++;
        }
    }

    for (uint i = (mx->size)-1; i >= 0; i--)
    {
        for (uint k = i+1; k < mx->size; k++)
        {
            x[i] -= mx->A[i][k] * x[k];
            thr_flops++;
        }
            

        x[i] /= mx->A[i][i];
        thr_flops++;
        if (i == 0)
            break;
    }

    delete[] x;
    delete[] pivot;

    return NULL;
}

void run_test(matrix* mx)
{
    thr_flops = 0;
    matrix_solve(mx);
    
    std::lock_guard<std::mutex> lock(flops_mutex);
    flops += thr_flops;
}