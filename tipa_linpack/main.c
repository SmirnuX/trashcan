#include <cmath>
#include <iostream>
#include <iomanip>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <ctime>

typedef float real;
//typedef unsigned int uint;    //For some compilers

struct matrix
{
    uint size;
    real** A;
    real* B;
    real* x;
    uint* p;
    unsigned long long flops;
    std::chrono::duration<double> time_elapsed;
};

matrix matrix_alloc(uint size);
void matrix_generate(matrix* mx, real max);
void matrix_dealloc(matrix* mx);

real* matrix_solve(matrix* mx); //Solve linear equation

void run_test(matrix* mx);

std::condition_variable start_test;
std::mutex start_mutex;
bool start = false;

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
    uint** p = new uint*[thread_count]; //Permutation matrices
    real** x = new real* [thread_count];    //Result vectors
    for (uint i = 0; i < thread_count; i++) //Allocating memory for all matrices/vectors for all threads
    {
        mx[i] = matrix_alloc(N);
        p[i] = new uint[N];
        x[i] = new real[N];
        mx[i].x = x[i];
        mx[i].p = p[i];
    }
    std::thread* threads = new std::thread[thread_count - 1];

    for (uint i = 0; i < repeat; i++)
    {
        for (uint j = 0; j < thread_count; j++)
        {
            mx[j].flops = 0;
        }
        std::cout << "Setting up test " << i+1 << "/" <<repeat<<'\n';
        for (uint j = 0; j < thread_count; j++)
            matrix_generate(mx + j, 1.0f);
        std::cout << "Starting solving of " << thread_count << " linear equations: ";
        //Preparing tests
        for (uint j = 0; j < thread_count-1; j++)
            threads[j] = std::thread([mx, j] () {run_test(mx + j);});
        //Starting tests
        {
            std::unique_lock<std::mutex>(start_mutex);
            start = true;
        }
        start_test.notify_all();
        run_test(mx + thread_count - 1);

        for (uint j = 0; j < thread_count-1; j++)
            threads[j].join();

        //Results
        //Result for each thread
        double total_flops = 0;
        for (uint j = 0; j < thread_count; j++) //Allocating memory for all matrices/vectors for all threads
        {
            std::cout    << "Thread # "<< j << "\n\t Time elapsed: " << mx[j].time_elapsed.count()
                    << "s.\n\t FP operations: " << mx[j].flops 
                    << "\n\t Total MFlops: " << std::fixed << mx[j].flops / 1000000.0f /  mx[j].time_elapsed.count() << "\n\n";
            total_flops += mx[j].flops / 1000000.0f / mx[j].time_elapsed.count();
        }
        std::cout << "Total MFlops: " << std::fixed << std::setprecision(8) << total_flops << "\n\n";
    }
    
    for (uint i = 0; i < thread_count; i++)
    {
        matrix_dealloc(mx+i);
        delete[] x[i];
        delete[] p[i];
    }
    delete[] mx;
    delete[] threads;

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
    uint* pivot = mx->p;
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
            mx->flops++;
        }

        if (imax != i) //Changing order of rows
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
            mx->flops++;

            for (uint k = i+1; k < mx->size; k++)
            {
                mx->A[j][k] -= mx->A[j][i] * mx->A[i][k];
                mx->flops += 2;
            }
        }
    }

    //Actually solving
    real* x = mx->x;
    for (uint i = 0; i < mx->size; i++)
    {
        x[i] = mx->B[pivot[i]];

        for(uint k = 0; k < i; k++)
        {
            x[i] -= mx->A[i][k] * x[k];
            mx->flops += 2;
        }
    }

    for (uint i = (mx->size)-1; i >= 0; i--)
    {
        for (uint k = i+1; k < mx->size; k++)
        {
            x[i] -= mx->A[i][k] * x[k];
            mx->flops += 2;
        }
            
        x[i] /= mx->A[i][i];
        mx->flops++;
        if (i == 0)
            break;
    }

    return NULL;
}

void run_test(matrix* mx)
{
    {
        std::unique_lock<std::mutex> lk(start_mutex);
        start_test.wait(lk, []{return start;});
    }
    auto start = std::chrono::high_resolution_clock::now(); //!Timer start
    matrix_solve(mx);
    auto end = std::chrono::high_resolution_clock::now();   //!Timer end
    mx->time_elapsed = end-start;
}