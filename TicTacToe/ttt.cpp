#include "ttt.h"
#include <iostream>

using namespace std;

ttt::ttt(int size): turn{"X"} {
	if (size <= 0) {
		throw new range_error("Size must be greater than one!");
	}

	table.resize(size, {' ', ' ', ' '});
} //ctor

string ttt::help() {
	return "Input any non-numerical character to withdraw.\n\n1|2|3\n-----\n4|5|6\n-----\n7|8|9 .....\n\n";
} //help

void ttt::awaitloop() {
	int query;

	cout << print();
	while (!ended) {
		cout << endl << endl << "It's " + turn + "'s turn." << endl;
		cout << ">";
		cin >> query;
		if (query == 0) {
			ended = true;
			cout << turn << " decided to withdraw..." << endl;
		}
		tick(query);
		cout << print();
	}
} //awaitloop

bool ttt::tick(int pick) {
	pick--;

	if (!ended) {
		if (pick > table.size() * table.size()) {
			cerr << "Out of bounds." << endl;
			return false;
		}
		if (table[pick / table.size()][pick % table.size()] != ' ') {
			cout << "Illegal move." << endl;
		} else {
			table[pick / table.size()][pick % table.size()] = turn.at(0);
			turn = turn == "X" ? "O" : "X";
		}
		cout << scan();
		return true;
	}

	cerr << "The match has ended." << endl;
	return false;
} //tick

string ttt::scan() {
	string trdiaguide(1, table[0][table.size() - 1]),
		tldiaguide(1, table[0][0]);
	int tldiagcnt = 0, trdiagcnt = 0;

	for (int y = 0; y < table.size(); y++) {
		string hguide(1, table[y][0]),
			vguide(1, table[0][y]);
		int cnthor = 1, cntver = 1;

		if (table[y][y] == tldiaguide.at(0) && tldiaguide != " ") tldiagcnt++;
		if (table[y][table.size() - 1 - y] == trdiaguide.at(0) && trdiaguide != " ") trdiagcnt++;

		for (int x = 1; x < table.size(); x++) {
			if (table[y][x] == hguide.at(0) && hguide != " ") cnthor++;
			if (table[x][y] == vguide.at(0) && vguide != " ") cntver++;
		}

		if (cnthor == table.size()) {
			ended = true;
			return hguide + " wins!\n";
		}
		if (cntver == table.size()) {
			ended = true;
			return vguide + " wins!\n";
		}
		if (tldiagcnt == table.size()) {
			ended = true;
			return tldiaguide + " wins!\n";
		}
		if (trdiagcnt == table.size()) {
			ended = true;
			return trdiaguide + " wins!\n";
		}
	}

	return "";
} //scan

string ttt::print() {
	string out = "";
	
	for (int y = 0; y < table.size(); y++) {
		for (int x = 0; x < table.size(); x++) {
			if (x) out += '|';
			out += table[y][x];
		}
		if (y != table.size() - 1) out += '\n' + string(table.size() * 2 - 1, '-') + '\n';
	}

	return out;
} //print
