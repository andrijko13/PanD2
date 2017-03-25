#include <iostream>
#include "Sprite.h"
#include "Engine.h"

#include <time.h>
#include <thread>
#include <chrono>

using namespace pand2;
using namespace std;

void updateWithTimeInterval(time_t t) {
	cout << "Elapsed time: " << t << endl;
}

int main(int argc, char ** argv) {

	Engine e(300,300);
	e.registerUpdateLoop(updateWithTimeInterval);
	e.start();
	std::this_thread::sleep_for (std::chrono::seconds(5));
	e.pause();
	std::this_thread::sleep_for (std::chrono::seconds(5));

	return 0;
}