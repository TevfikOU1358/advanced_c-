#include <iostream>
#include <string>
#include <vector>

using namespace std;
 template <typename T>
 void foo(T&&); //universal reference forwarding referene

 template <typename T>
 void foo2(const T&&);  //R value reference

 template <typename T>
 class Myclass {
	 void foo(T&&); //R value refence çünkü Tnin türü biliniyor.
 };
 auto&& x = 10; //forwarding reference


 //reference collapsing: Rvalue ref to rvalue = rvalue ; diðerleri Lvalue referen
 using LREF = int&;
 using RREF = int&&;
 typedef int& lref;
 typedef int&& rref;
 int n;

 lref& r1 = n; // type of r1 is int&
 lref&& r2 = n; // type of r2 is int&
 rref& r3 = n; // type of r3 is int&
 rref&& r4 = 1; // type of r4 is int&&

 int&& bar();

 decltype(bar()) && x1 = 5; //x rvalue ref;
// int main() {
//	 
//	 string s1(5, 'S');
//	 vector<string> svec;
//	 svec.push_back(s1);   //copied
//	 cout << "s1:" << s1 << '\n';//"SSSSS"
//	 svec.push_back(move(s1)); //"moved"
//	 cout << "s1:" << s1 << '\n';//""
//	return 0;
//}

 //RemoveReference possible implementation
 template <typename T> struct RemoveReference
 {
	 using type = T;
 };

 template <typename T> struct RemoveReference<T&> //partial spec.
 {
	 using type = T;
 };
 template <typename T> struct RemoveReference<T&&> ////partial spec.
 {
	 using type = T;
 };

 int main1() {

     std::cout << std::boolalpha;

     std::cout << "std::remove_reference<int>::type is int? "
         << std::is_same<int, RemoveReference<int>::type>::value << '\n'; //true
     std::cout << "std::remove_reference<int&>::type is int? "
         << std::is_same<int, RemoveReference<int&>::type>::value << '\n'; ////true
     std::cout << "std::remove_reference<int&&>::type is int? "
         << std::is_same<int, RemoveReference<int&&>::type>::value << '\n';
     std::cout << "std::remove_reference<const int&>::type is const int? "//true
         << std::is_same<const int,
         std::remove_reference<const int&>::type>::value << '\n';
 }

 //move posiible implementation

 template <typename T>
 std::remove_reference_t<T>&& Move(T&& t) {
     return static_cast<remove_reference_t<T>&&>();
 }