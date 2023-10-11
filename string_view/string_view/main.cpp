#include <iostream>
#include <string>
#include <string_view>
//string view: bir ba�lang�� adresini tutan pointer bir de dizinin boyutunu tutan 2 adet member � var
//g�zleme ama�l� kullan�l�r.
//milyon sat�rl�k string nesnesi kopyalamak yerine string view ile g�zlemisi olabiliriz.
using namespace std;

std::string foo() {
	return "betus";
}
int main() {
	std::string s(100'000, 'A');
	string_view sv;
	cout << sv.size() << '\n'; //0
	cout << sv.length() << '\n'; //0
	cout << sv.empty() << '\n'; //1
	cout << (sv.data() == nullptr) << '\n'; //1 yani true

	string_view sv1("tevfik uluocak");
	string_view sv2{ string{"tevfik uluocak"}.c_str()};

	char str[]{"tevfik osman uluocak"};
	string_view sv3(str, 6); //tevfik yaz�s�n� g�zlemliyor.

	std::cout << sv3 << '\n';  //tevfik
	std::cout << sv3.data() << '\n';//tevfik osman uluocak //data const char * d�nd�r�yr .Null terminated byte a kadar gider.

	//string_view sv4 = foo(); //string view nesnesi ge�ici string nesnesi ile ba�l�yor
	//cout<<sv4<<'\n'; //g�zlemcisi oldugu string nesnesi hayatta degil u.b 


	std::string_view str5{ "programming" };
	//string degismez sadece g�zlem araligi degisir.
	str5.remove_prefix(3);
	str5.remove_suffix(4);

	std::cout << "the length of " << str5 << " is " << std::strlen(str5.data()) << '\n';
	std::cout << "the length of " << str5 << " is " << str5.length() << '\n';
	std::cout << "str.data() is " << str5.data() << '\n';
	std::cout << "str is [" << str5 << "]\n";

	the length of gram is 8
	the length of gram is 4
	str.data() is gramming
	str is[gram]
}