// Build using g++ greetings.cpp -o greetings.o
#include <iostream>
#include <string>

void printSpace(int n) {
	for (int i = 0; i < n; ++i) {
		std::cout <<" ";
	}
}

void printStar(int n) {
	for (int i = 0; i < n; ++i) {
		std::cout << ((i%2==1)?".":"*");
	}
}


int main(int argc, char** argv) {
	// Declarations
	std::string input = "";
	int length;
	int halfLength;

	if (argc < 2) {
		std::cout << "Usage: \n\tgreetings.o message\n";
		std::cout << "Example: \n\tgreetings.o 12345\n";
		std::cout << "Output: \n";
		std::cout << "\t   *\n";
		std::cout << "\t  *.*\n";
		std::cout << "\t *.*.*\n";
		std::cout << "\t 12345\n";
		std::cout << "\t *.*.*\n";
		std::cout << "\t  *.*\n";
		std::cout << "\t   *\n";
		exit(1);
	}

	for (int i = 1; i < argc; ++i) {
		input = input + argv[i];
		if (i < argc - 1) {
			input = input + " ";
		}
	}

	length = input.size();
	halfLength = length/2 + 1;

	// print upper triangle
	for (int i = 0; i < halfLength; ++i) {
		printSpace(halfLength - i);
		printStar(2*i + 1);
		std::cout << "\n";
	}

	// print the string
	std::cout << " " << input << "\n";

	// print the lower triangle
	for (int i = halfLength-1; i >= 0; --i) {
		printSpace( halfLength - i);
		printStar( 2*i + 1);
		std::cout << "\n";
	}
	return 0;
}
