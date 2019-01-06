#include <stdio.h>
#include "Blitzbot.h"

int main(int argc, const char* argv[]) {
	Blitzbot bb;
	bb.initialize(argc, argv);
	bb.run();
}
