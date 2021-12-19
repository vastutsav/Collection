#include <iostream>
#include <string>

void printStar(int n) {
	for (int i = 0; i < n; ++i) {
		std::cout << "*";
	}
}

void printPlus(int n) {
	for (int i = 0; i < n; ++i) {
		std::cout << "+";
	}
}

void printSpace(int n) {
	for (int i = 0; i < n; ++i) {
		std::cout << " ";
	}
}

void newLine() {
	std::cout << "\n";
}

int main(int argc, char** argv) {
	std::string input;

	if (argc < 2) {
		std::cout << "plrase enter string\n";
		exit(1);
	}

	for (int i = 1; i < argc; ++i) {
		if ( i == 1 )
			input = argv[i];
		else
			input = input + " " + argv[i];
	}

	int length = input.size();
	printPlus(length + 8);
	newLine();
	printPlus(1); printStar(length + 6); printPlus(1);
	newLine();
	printPlus(1); printStar(1); printSpace(length + 4); printStar(1); printPlus(1);
	newLine();
	printPlus(1); printStar(1); printSpace(2); std::cout << input; printSpace(2); printStar(1); printPlus(1);
	newLine();
	printPlus(1); printStar(1); printSpace(length + 4); printStar(1); printPlus(1);
	newLine();
	printPlus(1); printStar(length + 6); printPlus(1);
	newLine();
	printPlus(length + 8);
	newLine();
	
	return 0;
}
