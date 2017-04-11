#include <thread>
#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <utility>

using namespace std;

class scoped_thread {
	thread t;
public:
	explicit scoped_thread(thread t_) : t(move(t_)) {
		if (!t.joinable())
			throw logic_error("No thread");
	}
	~scoped_thread() {
		t.join();
	}
	scoped_thread(scoped_thread const&) = delete;
	scoped_thread& operator=(scoped_thread const&) = delete;
};

void do_something(int& i) {
	++i;
	cout << i << endl;
}

struct func {
	int& i;
	func(int& i_) : i(i_) {}
	void operator()() {
		for (unsigned j = 0; j<1000000; ++j) {
			do_something(i);
		}
	}
};

void do_something_in_current_thread() {
	cout << "Fucking in current thread!" << endl;
}

void f() {
	int some_local_state;
	scoped_thread t(thread(func(some_local_state)));
	do_something_in_current_thread();
}

int main() {
	f();
}
