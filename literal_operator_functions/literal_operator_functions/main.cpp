#include <iostream>
#include <string>
#include <iomanip>
using namespace std;


//User Defined Literal operators
//int operator""_k(const char* p) { //uncooked
int operator""_k(unsigned long long val) { //cooked
	cout << val << '\n';

	return val;
}

constexpr int operator"" _bin(const char* p) {
	int ret{};
	while (*p) {
		if (!(*p == '0' || *p == '1')) {
			throw std::runtime_error{ "bad binary constant" };
		}
		ret = ret * 2 + (*p - '0');
		++p;
	}
	return ret;
}

constexpr std::string operator"" _ds(const char* p, std::size_t) {  //constexpr c++ 20 ile geldi
	return std::string{ p } + p;
}


int main() {
	897'275'678'672;
	0x1234'ABCDE;
	0b1110'1110;

	8888_k; //8888
	operator""_k(5555); //5555

	constexpr auto val = 101010101011_bin;
	cout << val << '\n'; //2731

	cout<<"tevfik"_ds<<'\n'; //tevfiktevfik


	//raw string literals
	const char* p = R"nec(("ali"))nec";

	std::puts(p); //("ali")
	const char* p2 = R"(
		necati ergin
		eray goksu
		volkan gundogdu
		hasan kaynar
	)";
	std::puts(p2);
	    //necati ergin
		//eray goksu
		//volkan gundogdu
		//hasan kaynar

	auto str = quoted("ahmet");
	cout << str<<'\n'; //"ahmet"
	auto str2 = quoted("mehmet", '*');
	cout << str2<<'\n'; //*mehmet*
}    