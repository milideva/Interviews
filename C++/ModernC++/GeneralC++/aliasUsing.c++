/*

  • typedefs don’t support templatization, but alias declarations do.
  • Alias templates avoid the “::type” suffix and, in templates, the “typename”
  prefix often required to refer to typedefs.
  • C++14 offers alias templates for all the C++11 type traits transformations.
*/


/*
  std::remove_const<T>::type // C++11: const T → T
  std::remove_const_t<T> // C++14 equivalent
  
  std::remove_reference<T>::type // C++11: T&/T&& → T
  std::remove_reference_t<T> // C++14 equivalent
  
  std::add_lvalue_reference<T>::type // C++11: T → T&
  std::add_lvalue_reference_t<T> // C++14 equivalent
  
*/


typedef void (*FP)(int, const std::string&);

using FP = void (*)(int, const std::string&); // alias 
