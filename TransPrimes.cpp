#include<stdlib.h>
#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<math.h>

void extend(std::vector<int> &S) {
	int x = S[S.size()-1]+1;
	while (true) {
		int a = 0;
		bool prime = true;
		while (a < S.size()) {
			if (x%S[a] == 0) {
				prime = false;
				break;
			} a++;
		}
		if (prime) {
			S.push_back(x);
			break;
		}x++;
	}
}

int check(std::vector<int> chi, int k, int place, std::vector<int> &S, int c, std::vector<int> chains) {
	int type = chi[place];
	int a = 0;
	int cur = 1;
	while (S[a]+c <= place) {
		if (chi[place-(S[a]+c)] == type) {
			int x = chains[place-(S[a]+c)];
			if (x >=cur) {
				cur = x+1;
			}
		} a++;
		if (a == S.size()) {
			extend(S);
		}
	}
	return cur;
}

void print(std::vector<int> chi) {
	int a = 0;
	while (a < chi.size()) {
		std::cout << chi[a];
		a++;
	} std::cout << std::endl;
}

void build(std::vector<int> chi, int r, int k, int &x, std::vector<std::vector<int> > &solutions, std::vector<int> &S, int c, std::vector<int> chains, int early) {
	if (x == chi.size()) {
		solutions.push_back(chi);
	} if (x < chi.size()) {
		x = chi.size();
		solutions.clear();
		solutions.push_back(chi);
	}
	int a = 0;
	while (a < r) {
		if (a < early) {
			std::vector<int> temp = chi;
			temp.push_back(a);
			int cur = check(temp, k, temp.size()-1, S, c, chains);
			if (cur < k) {
				std::vector<int> t = chains;
				t.push_back(cur);
				build(temp, r, k, x, solutions, S, c, t, early);
			}
		}  else if (a==early) {
			std::vector<int> temp = chi;
			temp.push_back(a);
			int cur = check(temp, k, temp.size()-1, S, c, chains);
			if (cur < k) {
				std::vector<int> t = chains;
				t.push_back(cur);
				build(temp, r, k, x, solutions, S, c, t, early+1);
			}
		} a++;
	}
}

int main () {
	int c = 4;
	int k = 3;
	int x = 0;
	int r = 3;
	std::vector<int> S;
	S.push_back(2);
	std::cout << "This program computes Delta(P+c, k; r)" << std::endl;
	std::cout << "What value of r do you want?" << std::endl;
	std::cin >> r;
//	std:: cout << "r = " << r << std::endl;
	std::cout << "What value of k do you want?" << std::endl;
	std::cin >> k;/*
	std:: cout << "k = " << k << std::endl;*/
	std::cout << "What value of c do you want?" << std::endl;
	std::cin >> c;
//	std:: cout << "c = " << c << std::endl;
	std::vector<int> chi;
	chi.push_back(0);
	std::vector<std::vector<int> > solutions;
	std::vector<int> chains;
	chains.push_back(1);
	int useless = 0;
	build(chi, r, k, x, solutions, S, c, chains, 1);
	std::cout << "Delta(P+"<< c << ", " << k << ", " << r << ") = " << x+1 << std::endl;
	if (solutions.size() == 1) {
		std::cout << "The valid coloring of length " << x << " is: " << std::endl;
	} else {
		std::cout << "The valid colorings of length " << x << " are: " << std::endl;
	}
	int a = 0;
	while (a < solutions.size()) {
		std::cout << "Solution " << a+1 << ": ";
		print(solutions[a]);
		a++;
	}
}