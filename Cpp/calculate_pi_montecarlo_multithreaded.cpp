#include <iostream>
#include <random>
#include <cmath>
#include <thread>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

const int N = 1E6;
const int CHUNKS = 10;
std::default_random_engine generator;
std::uniform_real_distribution<double> distribution(-1,1);

void get_points_on_circle(const int total_tries, int* number_of_hits_in_circle)
{
    for (int i = 0; i < total_tries ; ++i) {
        double x = distribution(generator);
        double y = distribution(generator);

        if (x*x + y*y <= 1) {
            *(number_of_hits_in_circle) += 1;
        }
    }
}

int main () {

    auto startTime = high_resolution_clock::now();

    int circ[CHUNKS] = {0};
    double total_circs = 0;

    vector <thread> threads;
    for (int i = 0; i < CHUNKS; ++i) {
        threads.push_back(thread(get_points_on_circle, N/CHUNKS, &circ[i]));
    }

    for (auto& thr : threads) {
        thr.join();
    }

    for (int i = 0; i < CHUNKS; ++i) {
        total_circs+=circ[i];
    }

    std::cout << (4*total_circs)/N << std::endl;

    // correct answer = 0.7857142857142857

    auto stopTime = high_resolution_clock::now();
    auto duration = duration_cast <microseconds> (stopTime - startTime);

    cout << "In multithreaded Sec: " << duration.count()/1000000.0 << endl;

    return 0;

}