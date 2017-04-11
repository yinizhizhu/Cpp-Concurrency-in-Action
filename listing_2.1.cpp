#include <thread>
#include <iostream>
#include <fstream>

using namespace std;

struct func {
	int& i;
	func(int& i_) :i(i_) {}
	void operator()() {
		ofstream out("my_thread.txt", 'w');
		for (unsigned j = 0; j < 30; ++j) {
			do_something(i);
			out << i << endl;
		}
		out.close();
	}
	void operator()(int n) {
		for (unsigned j = 0; j<n; ++j)
			do_something(i);
	}
	void do_something(int& i) {
		++i;
		cout << i << endl;
	}
};

void oops() {
	int some_local_state = 0;
	func my_func(some_local_state);
	my_func(100);
	std::thread my_thread(my_func, 18);
	my_thread.join();
}

int main() {
	oops();
}

#include <thread>
#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class x {
public:
	void do_some_work(int a) {
		cout << a << endl;
	}
};

int main() {
	x my_x;
	int num = 0;
	thread t(&x::do_some_work, &my_x, num);
	thread y = move(t);
	y.join();
}