
// C++14 feature

[[deprecated]] 
int f() {
  return 0;
}

[[deprecated("g() is thread-unsafe. Use h() instead")]]
void g ( int& x ) {

}

void h ( int& x ) {

}

void test() {
  int a = f(); // warning: 'f' is deprecated  [-Wdeprecated-declarations]
  g(a); // warning: 'g' is deprecated: g() is thread-unsafe. Use h() instead  [-Wdeprecated-declarations]
}
int main () {
  test();
  return 0;
}
