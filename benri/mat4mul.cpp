#include <iostream>
#include <array>

using namespace std;

auto main() -> int {
	array<int, 4> range = {1, 2, 3, 4};

	for(int x : range) {
		for(int y : range) {
			cout << "out->v" << x << y << " = ";
			for (int w : range) {
				cout << "a->v" << x << w << " * b->v" << w << y;
				if(w < 4) cout << " + ";
			}
			cout << ";\n";
		}
	}
	return 0;
}
