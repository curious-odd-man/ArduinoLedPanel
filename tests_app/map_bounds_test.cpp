#include <map>
#include <iostream>

using namespace std;

std::map<unsigned int, unsigned long> loopTimesCounter;

static void initLoopTimesCounter() {
	loopTimesCounter[35] = 0;
}

static void printAllMap() {
	cout << "Output..." << endl;
	for (auto const &pair : loopTimesCounter) {
		std::cout << "{" << pair.first << ": " << pair.second << "}\n";
	}
}

int main(int argc, const char **argv) {
	initLoopTimesCounter();

	++loopTimesCounter.upper_bound(0)->second;
	++loopTimesCounter.upper_bound(0)->second;

	auto it = loopTimesCounter.upper_bound(36);
	if (it == loopTimesCounter.end()) {
		--it;
	}
	++it->second;

	printAllMap();

	return 0;
}
