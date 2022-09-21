#include <iostream>
#include <random>
#include <cmath>
#include <thread>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

const int N = 1E4;
const int CHUNKS = 5;
const int SIZE = 50;
std::default_random_engine generator;
std::uniform_real_distribution<double> distribution(-SIZE,SIZE);

int get_index_from_coordinate(int a) {
    return a+SIZE;
}

void get_points_on_circle(const int total_tries, int* number_of_hits_in_circle, char box[2*SIZE + 1][2*SIZE + 2])
{
    for (int i = 0; i < total_tries ; ++i) {
        double x = distribution(generator);
        double y = distribution(generator);

        if (x*x + y*y <= SIZE*SIZE) {
            *(number_of_hits_in_circle) += 1;
            box[int(x)+SIZE][int(y)+SIZE] = 'X';
        } else {
            box[int(x)+SIZE][int(y)+SIZE] = '-';
        }
    }
}

int main () {

    auto startTime = high_resolution_clock::now();

    int circ[CHUNKS] = {0};
    double total_circs = 0;
    char box[CHUNKS][2*SIZE+1][2*SIZE+2] = {0};
    char final_box[2*SIZE+1][2*SIZE+2] = {0};

    for (int h = 0; h < CHUNKS; ++h) {
        for (int i = 0; i < 2*SIZE+1; ++i) {
            for (int j = 0; j < 2*SIZE+2; ++j) {
                box[h][i][j] = ' ';
            }
        }
    }

    for (int i = 0; i < 2*SIZE+1; ++i) {
        for (int j = 0; j < 2*SIZE+1; ++j) {
            final_box[i][j] = ' ';
        }
    }


    vector <thread> threads;
    for (int i = 0; i < CHUNKS; ++i) {
        threads.push_back(thread(get_points_on_circle, N/CHUNKS, &circ[i], box[i]));
    }

    for (auto& thr : threads) {
        thr.join();
    }

    for (int i = 0; i < CHUNKS; ++i) {
        total_circs+=circ[i];
    }

    std::cout << (4*total_circs)/N << std::endl;

    for (int h = 0; h < CHUNKS; ++h) {
        for (int i = 0; i < 2*SIZE+1; ++i) {
            for (int j = 0; j < 2*SIZE+2; ++j) {
                if (box[h][i][j] != ' ') {
                    final_box[i][j] = box[h][i][j];
                }
            }
        }
    }
    
    for (int i = 0; i < 2*SIZE+1; ++i) {
        for (int j = 0; j < 2*SIZE+1; ++j) {
            if (final_box[i][j] == ' '
                && (i-SIZE)*(i-SIZE) + (j-SIZE)*(j-SIZE) > SIZE*SIZE) {
                final_box[i][j] = '.';
            }
        }
    }

    for (int i = 0; i < 2*SIZE+1; ++i) {
        cout << final_box[i] << endl;
    }
    // correct answer = 0.7857142857142857

    auto stopTime = high_resolution_clock::now();
    auto duration = duration_cast <microseconds> (stopTime - startTime);

    cout << "In multithreaded Sec: " << duration.count()/1000000.0 << endl;

    return 0;

}

/*
3.1464
.................................................. ..................................................
....-.----....-.---.-.-..-......------...- -  X X XX X  X  X--.--.-..-.-..---.....-.---..-.-.-.---.-.
..-...-.--.--....-.....-.-.-.---.-..   -XX   X X X   X XXX   XX--..-.----..--...--.-...-..-..-.----..
...-..-..-..-..-.-.-.-..-.--..-.-  XX X X X   XX X X  XX  X   X     ..-...-.-.--....--.-..--.-..-..-.
.-.--...--.-......-.-..-..-..--    X XX    X  X     X   XX XX     XX-X..-..-..-.-..-.-.....--.....--.
.........-....-.--....-..--..  X X   X  X   XXX   XXXXX X          X X X-.---..---...-...--....-...-.
.-....-.--.--.-.-..---..-.. -   X XX  X  X  XXX X X  XX X XX   X   X  XX  -.---.--.-......--.......-.
.--.-.-..-........--.--..- X   X     XXXX X  XXXXXXX      X    X  X  XXX   -.-...-...-..-......-..--.
.---.-.....-....-..-...-  X   X X X  XXXX    XX X  XXXX  XX    X  X X X  XXX -......--..-..-.-.....-.
...---..-..--...-----.  XXXXX X XX     X XX  XXX  XX    X X  XXXX  XXXX    XX- ..-.-..-...-...--..-..
.-....-...-.---.....-XX XX   XX  XXX     X X X         X XX    XX  X X X  X  XX- ....-....-....-..-..
...-...--.-.--...---- X     XX       XX  XX X    X     XX X     X  XXX   XXXX  X ---..---..-..--..-..
..--.--.-......---    XX   XX X  X     X XX XX    X X XXXX  X  XXX XXX    X XXXXX ---...---..-.---...
.....--.-.--.-.-.-XXXX XXX X    X  XXXXXXXX  XX   X  XXX  XX X XXXX X XX   XXX  XX --.-..-...--..--..
..-.......-.---.   XX  XX    X     XX XX   X  X  X  XXXXX       X   XXX   XX  XXXX   ...-..--.--.--..
...--..-..-----X X X  XX      XXX X    XXX  X XX XX    XX X   X  X  X XX    XX X  XXX ....-...--..--.
.-.-.-.-......-X X X  X X  X X X XXX   X    X X   X     XX X  X XX    X X X XX     X X-...-.-----.-..
.---.-.--.----  XXX  X  XX   XX X XXXXX XXX        X   X X   XX XXXX XX XX XXXX X     X ......--..--.
....-.-..... XX XXX X  X   X X   X XXXXXX XXX   X XXX   X   XX XX X X  X X  XXXX  XX  X  .....-.----.
....---..-- X   XX     XX XX X XX  X  XX XX     X XXXXXXX    X  X  XXX      X X  XX X  XX-......-..-.
.....----.-    XXXXXX XX     XX XX X X    XX  X  X XX  XXXXX  X X   X   XX    XXXXXXX  XX  ....--.--.
.--......-  X    X  XX     XX X X   XXXXXX    X     X X    X X XXX XX  X X X X X XXXX   XX ....-----.
..-.-....X XX XXX X  XX X XXX   X  X  XX     XX XXX X   XXX  X XXXXX XX      XX   XXXXX X X ....--...
..---... X       XXX   XX  XXX XX X  X    XX X XXXXX    XX  X XXXX   X   XXXX XX X   XXXXX ---...--..
..--..-.-X X  XX X XXX   X XX     XXX X  X     X  XXXXX   XX       XXX X   X  X  XX      XX --.-.--..
.-..-..  XXX     X X  X  XX    X X  XXXXX   X  X     XX XX X XXXX X    XX    X  XXXXXX  XX    .......
...-..- X XXXX  X     X XXX     X XXX X  X X X X XX X   X    X X XXXX  X     X   XX XXX X     -.-.--.
.-.-..   X X        XX  X    XXX     XX  X  X XXXXXX XXXXX  X  X X  X  X X  X     X XX XXX X   ..---.
.-....  X XXXXX  XX   X XX     X   X    XXX   XXXX    X   X   X X   X X X    X   X     X  XX X ...--.
..-.- X X  XX   XX XXX X X X  X  X  XXX XX  XX     X XXX       XX  X X XX  X   X   XX X X    XX ..-..
.-.-.X  X      XX     X             X         X X XX X      XX   X  XX   XX XXX   X      XXX    -.-..
.--.    X     XXXX  XX    X  XX   XX X  X   X    X    X XXX X X X     X     X X  X   XX   X     -.--.
...- X   X XXX XX   XX  X XX XXXXXXX X X      X   X      XXXX    X X  X  X     XX  XXX    XX   X ---.
...-  X    X     XXX    X  X X  X    X X X     X  X  X XXXX X XXX X   X X XXX    XXX  X  X        -..
.---      XX XXXXX   XX  X   XX  XX X  XXX   XX   X  X  XX XXXX   XX      XX    XX XX X    X  XXX ...
.-.XX     X       XXX X  X X X      X X           X XXXXX XX         XX    X X X   X     X X    X -..
.. X XX X  X X X     X    XX  X  X X   XX XXXX       XXX X XX X     XXXX X    X      XX  X  XX     -.
..  X    X  X  X XXX  X    X X     XXXX  X XX   XXXX XX  XXX X   X  X X XX XXXX   X XX X X X X XXX--.
..   X  X    X X XXXX X X        X XXX XX XX  XX XX        XXX X X  X  X XX     XXX       X X  X  -..
..    X X   X X    X XXX  X  X  XXXX  X XXXX  XX  XX  X  X X XX X X  XX    XX       X   X XXXXX   --.
.-           X X   XXX XX     XXXXX  X   XXX XX  X X XX   XX X XX   XX    XXXXX    X       X  XXX  -.
.    XXX  X    X X X          X XX   XX  X X         XXXXX X      X        X    XX    XX XXX   XX X-.
.  XXX X   X    X X  XXXXXX X X X X XX  X  XXXXXXXX X       X  XXX XX XX  XX     X   X XXX X XX X   .
.- X      XXXX      XXX XXX XX X  X   X X  X X XX X X X XXX   X XXX   XX    X    X  X     X     XX X.
.      XX   X XX  X XXX XXXX X XX XXX X XXX    XXXX X XX XX X   X XX       X  X X X   X   X XX   XX .
.  XXXXX   XXXXX XX X XX    X  X X  X XXX   X    XXXXX XX      X     XXX    X XX      XXXXXXX  XXXXX.
. X  X XX X     XXX  XX  X  X X     XX  X  X   XXX  X  XXX     X  X  XX XX     XX XXX    X   X  X XX.
.  X  X X   XXX  XX    X XXX     X X XX  XX X X X XX   X XX  X   XX X XX XXXX  X    X X  XX   X  X  .
. XXXX    XX      XX XXXX X XX   XX   XX   XX   X XX XXXXXX X   X  XX   XX    XXXXXXX XX  X X   X   .
.X     XX XX   X  XX   XXX       XXXXXX XX   X X XX  X X X X XX X   X    X    X   X X X XXXX XXXXX  .
 XXXX XXXXX X   XXXXX XXX X XXX XXX   X XXXXXXXXXXX XX  X  XX X X  X XX  XX   XXX  X   XXXXXXXXXX X  
. X    XX XX   XXX X   X  XX X  X    XXXXX  X  X XXXX XX  XXXX     X X   X  XX XX X XXXX  X   XX XX .
. X    XX XX  X X XX     XX X X   XX X  XX   X XXX XXXXXXXX   X XXX XXX X X X X       X  X    X X   .
.X   X XXX      X XX    X  XX  X XXX X X X   XX      X   X XXXX    XXXXXXX       X    X   X X  XX   .
.-XX     X X    XX XXXX X XXXXX   X X X  X      XXXX         X X  X   X XXXX XXX  X XXX    X X     X.
. X        X XX  XX  XXX        XX    XXXXXXX XXX  X    XXX  XX XXXXXX  XX X X X   X  X   X XX      .
. X   XXXX  XXX  X XXXXX X X  X XXX  X X   X     X X     XXXX     X XX   X X  X  X X     X  X       .
.X  XXX    XX XX   X     X    X X XXX   X  X  X   X  XXXX   XX         X X      XXXXXX  XX  XXX XX -.
.-XXX    X    XX X   X   XX X X   X  X     X   X        X X X X  XXX XX   X   X XX   XXX     X   XX-.
.   X XXXXX X   X X XX   XXXX   XXXX  X        X  X     X X X X    X  XXX    XX XXXX  XX  XX  X X X .
..X X  X  X  XXXXX  X  XXX  X    XXX XXXXX XX X X  X    X   XXX       XX  X XXXX  XX X  X X XXX XXX-.
.-   X     X X XX X XXX X        XXXXX XXXX  X X  XX         XX  X     XX     XX XX X  X          X-.
.--    XXXX X X  X X  X XXX   X  XX X   X   X   X X X X XX    XXX  X  XXX X  XX X XXXX XX  XX X X  -.
..  XX       XXXXX  X  XXX     XXX   XXX       X   X  X     X XX     X  X  XX XX  X    X   XXX     -.
..-X XXXX XX   X    XX  XX    X  XX  X  X XX  X     X X  XX    XX X XX          XX  X X  X X X X  -..
.-- XXXX  XX XXXX XX X X   XX  XX  XX XXX XXX XX  X  XX   X  X  X X XXXX  XXX  XXX     XXXX  X    --.
..- X XXXXX X  X XXXXX          XX  X  XX XX   X      XX X     X       XXX X X XXX        XXXXXX -...
...  X X      XX X     XX       XX X   XXXX XXX X XXXXX       XXX XXXX  X   X   XX XXXXXX XX X  X--..
...-XX    X X  X X  XX  XX  XX XX   XX X X X X  X X X  X         X               XXX XX XX   XXX .-..
..-.-   XX    X X X    X X X   XXXXX  X      X   X  XXX X  X X X   X   XX XX XX  X     X      X  -.-.
.--.-  XXX  X X  XXXX   XX X         X   X X    X XX     XX     X X     X  XX XX  X  XXXXX X X X.....
...---XXXX  XXX X X XXX X X X XX X     XXXX XX  X XX   XXXXXXX XX       X  X X   XXXX           ...-.
.-....XXX  XX XX   X X  X    XXXX XXX  X  XXX  X   XX  XXX X  XXXX  X XX XXXX        XX XX    X......
.....-XX  XX  X    XX  X    X XXXXX  X XX  XX XXXXXXXXXX  X  XXX X   XXX    XX XX X  XX    X X -.--..
......- X      X  X   XXX   X   X XX       X  X XX XX X    XXXX  X XX X XXX  XX X   XX   XX   -..---.
...-...-X X  XXX XX  X   X    X    X XX XXXX XXXXX         X  XXX  X XXX  X XX     XX   XX  --....--.
..-----.X X       X  X  X XXXXXX X  XX XX X    XX X   X  X XX  XXX  XX XX X  XX  XX    X XX  .-.-..-.
.-...--. X     X   XX   XX X  XX X  X  X    XX  XXX X XXXX  XX XX XX X   XX X  XX    XX XX X --..-...
..--.-.--     X X  X XX XXXX X XX      X      XX  X X       X X  X X  XX X  XX X X   XXX    ......-..
.-.--.---.XX X X X   XX   X  X XX   XX X X    X  XXXX  X   XXXX XXX XX  XXX   X      X  X  ..-.....-.
.......--.- X  XX X  XXXXXX      XX  X   X      X X X     XX XXXX  XX     X  XX  XXXXXXXX  .--....-..
.-..-...-.--   X X XX    X  X XXX   X X XXX    XX  XX X XXXX XX     XX X XX X        XX   .--.---....
.--...----..   XX   XX     X      X         X X    XX X  X  X X    XX XXX   X XX  XX XXX-........-...
....-.--.....-   X X X  XX X X XX  X   X    X XX  X  X X   XXXXXX  XXXXX X     XXX   X  ....----.....
..---...-...-.XX   X XXX X  XXX  X  X X  XX   X XXXX X X   X  X X     X  X       X     ...-...-.-.--.
...-..-......--   X   X X  XXX  X X XX   X   XXXXXX X    XXXXXX X   X  X X XX  X     --..-..--.-..-..
..------.--.-.--    X  X    X  X  X XXXX XXX X XX XXX X  XXX X X X X XXXX X XXX X    ......-...-...-.
...--.-----.-.... X X  XX X    X X  X   XX     X  X XX       X XXX   X    X  XX   XX.-.....-...-...-.
......-.........-- XXXX   X X  XX X  X   X X      X   X   X X X   X    X  XXX    X-..-..---.-.-.-.--.
.-..--.-...-..-....  X    XXXX  X X    X    X    XXX      XX X XX XX  XX    XXXX  .--.-.------..-..-.
.-..-.--..-....-..---  XX XXX XX X   X       X X  X X XX  X XXX           X   X --..----.-.--.--...-.
..-..--.-.....-.----..    X XX X   X    X XXXX X   X  XXXX  X  X  X  XX   X  ---...-.-.-.--.------.-.
.---..-..-.-.--..--..-.  -XX    X    X XX X XX X  X    X   X           X   X  ---.---..--.-...-...-..
....-..---....--.-.-.--..--   X XX   X     X    X XXX  X X   X    XX  X   - ..-..-.--.-.-.-----..-...
..-.-.---.-..----...-..-.--  X    X   X  XX XX X        X   X X    XX X  -..-.-.---....--....-------.
..-----.--.-..--.----......-. X   X XX    X  X   XX    XX   X XX  X X   -.-..--.--.--.--..-.-.-...-..
.-.-.-..-.-...-.-.-.----.-.....--X  X     X   XX XXXXX XXXXX  X  X   -.-..-.-..-...---..-..--......-.
....--.-.-....--.-.....---....----  XX   X  X XX XX X X XXX  X     -.--.-.--.---.---...---...-.....-.
.-...-...-.-..---......-.-.-...-.---  - X           X  XXX   ----.-..----.--.........-.----.--.-.....
.-..-.--.--......-..--..-...---.----.....-       XX  XX-  - -.-......-...--..-........-...----.--..-.
.................................................. ..................................................
In multithreaded Sec: 0.001003
 */