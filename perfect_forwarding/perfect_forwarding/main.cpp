#include <iostream>

using namespace std;
//Perfect Frwarding: de�i�kendin t�r kategorisi neyse o de�erde iletilir

class Myclass{};

void bar(Myclass&) { cout << "Lvalue ref.\n"; }
void bar(const Myclass&) { cout << "const Lvalue ref.\n"; }
void bar(Myclass&&) { cout << "R value ref.\n"; }
void bar(const Myclass&&) { cout << "const R value ref.\n"; }

template <typename T>
void foo(T&& arg) {  //forwarding reference
	//bar(std::forward<T>(arg)); //perfect forwarding
	bar(std::forward<decltype(arg)>(arg)); //perfect forwarding  //is same above 
}
int main() {
	Myclass m1;
	const Myclass m2;
	Myclass& m3{ m1 };
	Myclass&& m4{ move(m1) };
	foo(m1);
	foo(m2);
	foo(m3);
	foo(m4);
	foo(move(m3));
	foo(move(m4));

	//Lvalue ref.
	//const Lvalue ref.
	//Lvalue ref.
	//Lvalue ref.
	//R value ref.
	//R value ref.

	auto fn = [](auto&& r) {  //forwarding reference
		std::forward<decltype(r)>(r);
	};


}
//********************
//T ye yap�lan �a�r� lvalue reference ise T t�r� Lvalue reference
//T ye yap�lan �a�r� rvalue reference ise T t�r� referencet�r� de�il
//bu durum auto&& de auto ya yap�lan �a�r�n�n ayn�s�d�r
template <typename T>
void foo(T&&) {   

}

template <typename T>
void foo(T, T);

foo("ali", "veli"); //syntax error ilk T param: const char[3] ikincisi const char[4]



