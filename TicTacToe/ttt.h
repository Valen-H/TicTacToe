#pragma once
#include <string>
#include <vector>

using namespace std;

class ttt {
	public:
		vector<vector<char>> table;
		bool ended = false;
		string turn;

		ttt(int size = 3);

		string print();
		string help();
		string scan();
		void awaitloop();
		bool tick(int pick);
};
