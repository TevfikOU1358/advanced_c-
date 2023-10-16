#include <iostream>
#include <optional>
//C++17
//bir nesne T turunden degerine sahip olup olmadigini anlamaya yarayan arac setidir.

class Myclass {
public:
    Myclass(int, int, int) {};
};

struct A {
    std::string s;
    A(std::string str) : s(std::move(str)), id{ n++ } { note("+ constructed"); }
    ~A() { note("~ destructed"); }
    A(const A& o) : s(o.s), id{ n++ } { note("+ copy constructed"); }
    A(A&& o) : s(std::move(o.s)), id{ n++ } { note("+ move constructed"); }
    A& operator=(const A& other) {
        s = other.s;
        note("= copy assigned");
        return *this;
    }
    A& operator=(A&& other) {
        s = std::move(other.s);
        note("= move assigned");
        return *this;
    }
    inline static int n{};
    int id{};
    void note(auto s) { std::cout << "  " << s << " #" << id << '\n'; }
};
int main()
{
    std::cout << std::boolalpha;

    std::optional<int> opt;
    std::cout << opt.has_value() << '\n';  //false

    opt = 43;
    if (opt)
        std::cout << "value set to " << opt.value() << '\n'; //value set to 43
    else
        std::cout << "value not set\n";

    opt.reset();  //tutulan deðeri yok edr.
    if (opt.has_value())
        std::cout << "value still set to " << opt.value() << '\n';
    else
        std::cout << "value no longer set\n";  //value no longer set

    //std::nullopt_t is an empty class type used to indicate optional type with uninitialized state.
    //In particular, std::optional has a constructor with nullopt_t as a single argument, 
    //which creates an optional that does not contain a value.

    std::optional<int> op1{ std::nullopt };
    if (op1.has_value())
        std::cout << "value still set to " << op1.value() << '\n';
    else
        std::cout << "value no longer set\n";  //value no longer set
    op1.value() = 28; //op1 degeri 28 oldu cunku value() refernce doner


    std::optional<std::string> opt1{"tevfik"};
    //operator*, operator->, value()
    if (opt1) {
        std::cout << *opt1 << '\n'; //tevfik
        std::cout << opt1->length()<<'\n'; //6
    }

    std::optional<std::string> opt2{std::nullopt};

    try {
        auto val = opt2.value();  //exception throw eder
    }
    catch (const std::bad_optional_access& ex) {
        std::cout << "exception caught:" << ex.what() << '\n';  //exception caught:Bad optional access
    }
   // std::cout << *opt2 << '\n'; //bos icerik u.b
    std::optional<std::string> opt4{};

    //reference semantiðine sahip deðil
    std::cout<<opt4.value_or("tefo"); //deðeri varsa deðerle dönüce, yoksa parametre deðiþkenine sahip olucak//tefo
    
    //optional sýnýfý referans tutmaz ama þöyle yapabiliriz
     
    std::string name{ "tevfik" };
    std::optional<std::reference_wrapper<std::string>> opt5{ std::ref(name)};

    opt5->get() += "uluocak";
    std::cout << "name" << name<<'\n'; //tevfikuluocak
    

    //std::optional<Myclass> op6{ 1, 2, 3 }; //syntax error Myclass parametrelri olduðumu anlamaz
    std::optional<Myclass> op6{std::in_place, 1, 2, 3 };   //in_place() parametreleri perfect forward eder.
    auto op7 = std::make_optional<Myclass>(1, 2, 3 );   //yukaridaki ile ayný


    //emplace:Constructs the contained value in-place. If *this already contains a value before the call, the contained value is destroyed by calling its destructor.
    std::optional<A> opt8;

    std::cout << "Assign:\n";
    opt8 = A("Lorem ipsum dolor sit amet, consectetur adipiscing elit nec.");

    std::cout << "Emplace:\n";
    // As opt contains a value it will also destroy that value
    opt8.emplace("Lorem ipsum dolor sit amet, consectetur efficitur.");

    std::cout << "End example\n";
}

std::optional<int> to_int(const std::string& s)
{
    try {
        return std::stoi(s);
    }
    catch (...) {
        //return {};
        return std::nullopt;
    }
}

std::optional<int> to_int2(const std::string& s)
{
    std::optional<int> ret; // deger tutmuyor
    try {
        ret = std::stoi(s);
    }
    catch (...) {}

    return ret;
}

int main()
{
    for (auto s : { "42", " 077", "necati", "0x33" }) {
        // ogeleri int'e donusturup cikis akimina yazdiriyoruz:
        std::optional<int> op = to_int(s);
        if (op) {
            std::cout << s << " yazisi int'e donusturuldu... deger : " << *op << "\n";
        }
        else {
            std::cout << "(" << s << ") yazisi int'e donusturulemiyor\n";
        }
    }
}  
struct Nec
{
    std::optional<double> mx;
    std::optional<double> my;
};


int main()
{
    std::cout << "sizeof(Nec) = " << sizeof(Nec) << '\n';  //16
}