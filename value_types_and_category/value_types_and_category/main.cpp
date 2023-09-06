#include <iostream>


//link cppreference: https://en.cppreference.com/w/cpp/language/value_category

using namespace std;

//primary value categories:
//Prvalue:Sa� taraf de�eri ifadeler. Kimli�i olmayan ta��nabilen ifadeler  
//Lvalue
//x value
//
//mixed value category:
//gl value: (L value veya x value)
//r value:(prvalue veya x value )


//Referans t�rleri 3 tanedir.
// 1)L-value reference:T& r
// 2)R-value reference:T&& R
// 3)Forwarding reference(universal reference)


//decltype((ifade));
//Prvalue ==> T
//Lvalue ==> T&
//xvalue ==> T&&

template <typename T> constexpr const char* p = "PRValue"; 
template <typename T> constexpr const char* p<T&> = "lValue";  //partial specialization
template <typename T> constexpr const char* p<T&&> = "XValue"; //partial specialization
//decltype:unevaluated
int bar();
int& baz() { int x = 0; return x; }
int&& foo();
void foo2();
int main() {
	struct Tefo { int a; };
	int x{};
	cout << p<decltype(10)><<'\n'; //PRValue
	cout << p<decltype((x + 5))> << '\n'; //PRValue
	cout << p<decltype((x))> << '\n'; //LValue
	cout << p<decltype(x++)> << '\n'; //PRValue
	cout << p<decltype(++x)> << '\n'; //LValue
	cout << p<decltype(bar())> << '\n'; //PRValue
	cout << p<decltype(baz())> << '\n'; //LValue
	cout << p<decltype(foo())> << '\n'; //XValue
	cout << p<decltype(foo2())> << '\n'; //PRValue //void
	cout << p<decltype("tefo")> << '\n'; //LValue string literal
	cout << p<decltype((bar))> << '\n'; //LValue fonksiyon isimleri
	
	cout << p<decltype(move(x))> << '\n'; //XValue move() geri d�n�� &&
	cout << p<decltype(static_cast<int&&>(x))> << '\n'; //XValue static_cast() geri d�n�� &&
	cout << p<decltype(nullptr)> << '\n'; //PRValue
	cout << p<decltype(Tefo{})> << '\n'; //PRValue ge�ici nesne ifadeleri
   //lambda ifadeleri prvalue

	Tefo t1;
	Tefo& t2{ t1 };
	Tefo&& t3{ Tefo{} };

	cout << p<decltype((t1))> << '\n'; //L VALUE isimler her zaman lvalue
	cout << p<decltype((t2))> << '\n'; //L VALUE isimler her zaman lvalue
	cout << p<decltype((t3))> << '\n'; //L VALUE isimler her zaman lvalue
	cout << p<decltype((t1.a))> << '\n'; //L VALUE nesne l value member da l value
	cout << p<decltype((Tefo{}.a))> << '\n'; //X VALUE nesne pr value member da x value
	cout << p<decltype((move(t1).a))> << '\n'; //X VALUE nesne pr value member da x value
	
	//ternary operator:PR Value   
	//Bir nesnenin kayna��n�n �al�nabilmesi i�in move ctor veya move assginment �a��r�lmal�d�r.
	//nesneyi referansa ba�lamakla asla neyse �al�nmaz
	class Myclass {

	};
	Myclass m;
	Myclass&& m2 = move(m); //nesne asla �al�nmad� sadeve r value referansa ba�land�
	Myclass m3 = m2; //nesne yine �al�nmad�.copy ctor �a��r�ld�.
	Myclass m4 = move(m2); //nesne �al�nd� move ctor �a��r�ld�.

	void tef(Myclass&);  //parametreye sadece const olmayan l value reference ge�ilebilir
	void tef(const Myclass&); //const olan olmayan b�t�n l value r value referanslar ge�ilebilir.
	void tef( Myclass&&); //sadece const olmayan r value reference �a��r�labilir.
	void tef(const Myclass&); //b�t�n r value reference lar �a��r�labilir.
	  
	return 0;

}