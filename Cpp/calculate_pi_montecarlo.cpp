#include <iostream>
#include <random>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main () {
    
    auto startTime = high_resolution_clock::now();

    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(-1,1);

    const int N = 1E6;
    double circ = 0.0;
    for (int i = 0; i < N ; ++i) {
        double x = distribution(generator);
        double y = distribution(generator);

        if (x*x + y*y <= 1) {
            ++circ;
        }

    }
    std::cout << (4*circ)/N << std::endl;


    auto stopTime = high_resolution_clock::now();
    auto duration = duration_cast <microseconds> (stopTime - startTime);

    cout << "in non-threaded Sec: " << duration.count()/1000000.0 << endl;
    
    // correct answer = 0.7857142857142857

    return 0;

}