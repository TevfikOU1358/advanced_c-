#include <iostream>
#include <any>
//any:: bir sýnýf þablonu deðil.

int main() {
	using namespace std;
	any x;// default ctor bos durumda
	//has_value()
	cout<<boolalpha<<x.has_value()<<'\n'; //false;
	any a1(12);
	any a2(12.4);
	any a3("mustafa");
	any a4("mustafa"s);
	any a5("mustafa"sv);
	cout<<a5.type().name()<<'\n';  //class std::basic_string_view<char,struct std::char_traits<char> >


	//any_cast():degere erisir. Yanlýs degerde exception throw eder.
	any a{ 12 };

	try {
		int ival = any_cast<int>(a);
		cout << "ival = " << ival << '\n';
		a = 3.4;
		ival = any_cast<int>(a);
		cout << "ival = " << ival << '\n';  //ival:12
	}
	//catch (const bad_any_cast& ex) {
	//catch (const bad_cast& ex) {
	catch (const exception& ex) {
		cout << "exception caught: " << ex.what() << '\n';  //exception caught: Bad any_cast
	}
}