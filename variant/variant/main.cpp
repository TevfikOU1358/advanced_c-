#include <iostream>
#include <string>
#include <variant>


using namespace std;
//C++!7 den beri var.C 'deki union'a denk geliyor. variadic template


struct S
{
    S(int i) : i(i) {}
    int i;
};


int main() {
//	1) Default constructor.Constructs a variant holding the value - initialized value of the first alternative(index() is zero).
//		This constructor is constexpr ifand only if the value initialization of the alternative type T_0 would satisfy the requirements for a constexpr function.
//		This overload participates in overload resolution only if std::is_default_constructible_v<T_0> is true.
	variant<int, double, float> va; //variant int tutuyor. ilk arguman mutlaka default constructible olmali
	variant<int, double, float> va2{3.2}; //variant int tutuyor. ilk arguman mutlaka default constructible olmali
	//index():return that hold alternatives
	cout << va2.index(); //1 double
	va2 = 3.2f;
	cout << va2.index(); //2 float
	va2 = 29;
	cout << boolalpha << holds_alternative<int>(va2)<<'\n'; //true;

	variant<int, string, float> va3{ in_place_index<1>, 10, 'A' };
	variant<int, string, float> va4{ in_place_type<string>, 10, 'A' };

    //global get() tutmadýgi ööeye baktigi zaman exception throw eder.
    std::variant<int, float> v{ 12 }, w;
    std::cout << std::get<int>(v) << '\n';
    w = std::get<int>(v);
    w = std::get<0>(v); // same effect as the previous line

    //  std::get<double>(v); // error: no double in [int, float] //compile time
    //  std::get<3>(v);      // error: valid index values are 0 and 1 //compile type

    try
    {
        w = 42.0f;
        std::cout << std::get<float>(w) << '\n'; // ok, prints 42
        w = 42;
        std::cout << std::get<float>(w) << '\n'; // throws
    }
    catch (std::bad_variant_access const& ex)
    {
        std::cout << ex.what() << ": w contained int, not float\n";
    }
    //get_if   obtains a pointer to the value of a pointed - to variant given the index or the type(if unique), returns null on error


    auto check_value = [](const std::variant<int, float>& v)
    {
        if (const int* pval = std::get_if<int>(&v))
            std::cout << "variant value: " << *pval << '\n';
        else
            std::cout << "failed to get value!" << '\n';
    };

    std::variant<int, float> k{ 12 }, t{ 3.f };
    check_value(k);  //variant value: 12
    check_value(t);  //failed to get value!

    //emplace():eski degeri destroy eder yeni deger perfect forward

    std::variant<std::string> v1;
    v1.emplace<0>("abc"); // OK
    std::cout << std::get<0>(v1) << '\n'; //abc
    v1.emplace<std::string>("def"); // OK
    std::cout << std::get<0>(v1) << '\n'; //def

    //monostate:ilk  deger yapilarak default ctoru olmayan S class i kullanilmiþ oldu.
        // Without the monostate type this declaration will fail.
    // This is because S is not default-constructible.
    std::variant<std::monostate, S> var;
    std::variant<std::monostate, S> var2{5};
    var2 = monostate{};
    var2 = {};


    //visit():: variadic fonksiyon sablonu arguman olarak callable alir.+
    variant<int, double, string> vx{ "hakan" };
    const auto f{ [](auto x) { std::cout << x << '\n'; } }; //visitor

    visit(f, vx); //"hakan"
    vx = 15;  //15
    visit(f, vx);
    vx = 15.4; //15.4
    visit(f, vx);
}

struct triple {
	template<typename T>
	void operator()(T& t)const //t türü referans olduðu için t'yi degistiriyoruz
	{
		t = t + t + t;
	}
};

int main()
{

	variant<int, string, double> vx{ 243 };

	visit(triple{}, vx);

	cout << get<0>(vx) << '\n'; //729
	vx = "can";
	visit(triple{}, vx);
	cout << get<1>(vx) << '\n'; //cancancan
	vx = 4.5;
	visit(triple{}, vx);
	cout << get<2>(vx) << '\n'; //13.5
}


template<typename... Ts>
struct overload : Ts...
{
	using Ts::operator()...;
};

// base types are deduced from passed arguments:
template<typename... Ts>  //dedection guide(C++17'de):C++20'de gereksiz
overload(Ts...)->overload<Ts...>;

int main()
{
	using namespace std;
	variant<int, string> vx(99);
	visit(overload{
		[](int ival) {cout << "int: " << ival << '\n'; },
		[](const std::string& s) {
			std::cout << "string: " << s << '\n'; },
		},
		vx);

	auto twice = overload{
		[](std::string& s) { s += s; },
		[](auto& i) { i *= 2; },
	};

	visit(twice, vx);
	std::cout << get<0>(vx) << "\n";
}