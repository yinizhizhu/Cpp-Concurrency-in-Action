#include <thread>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <fstream>
#include <iostream>
#include <utility>

using namespace std;

void do_work(unsigned id) {
	cout << id << endl;
}

void f() {
	vector<thread> threads;
	for (unsigned i = 0; i<20; ++i)
		threads.push_back(thread(do_work, i));
	for_each(threads.begin(), threads.end(), mem_fn(&thread::join));
}

int main() {
	f();
}
