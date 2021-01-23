/*

  Type traits defines a compile-time template-based interface to query or modify
  the properties of types.

  Generic programming (writing code which works with any data type meeting a set
  of requirements) has become the method of choice for providing reusable code.
  However, there are times in generic programming when "generic" just isn't good
  enough - sometimes the differences between types are too large for an
  efficient generic implementation. This is when the traits technique becomes
  important - by encapsulating those properties that need to be considered on a
  type by type basis inside a traits class, we can minimise the amount of code
  that has to differ from one type to another, and maximise the amount of
  generic code.

  Defines templates for compile-time constants that give information about the
  properties of their type arguments, or produce transformed types.

  For performance/efficiency : 
  The type-traits support in the first step to analyse the code at the compile
  time and in the second step, to optimize the code based on that analysis. How
  is that possible? Dependent on the type of a variable a faster variant of an
  algorithm will be chosen.

  example: If the elements of a container are simple enough, algorithm of the
  STL like std::copy, std::fill, or std::equal will directly be applied on the
  memory area. Instead of using std::copy to copy the elements one by one, all
  is done in one large step. Internally, C functions like memcmp, memset,
  memcpy, or memmove are used.

  - anytime you need to know specific info about a type 
  - choose a particular efficient algorithm
  - or disallow certain data types
  
  typetrait provides attributes about a template parameter
  - can T be copied
  - is T a pointer
  - if T is a const, remove the const

  typetrait can be a template class but is usually implemented as a template struct
  Its only purpose is to store info about type, at a compile time.
  Default struct/class can be empty or provide default values. body is often a tyepdef.
  
  example
  Trait categories 

  * numeric
  long max = std::numeric_limits <long>::max();
  is_signed, is_interger ...

  * type categories 
  bool isEnum = std::is_enum<T>::value;
  bool isConst = std::is_const<T>::value;
  is_array, is_pointer ...

  * supported operations
  is_copy_assignable<T>::value
  is_copy_constructible<T>::value
  
  * relationship
  is_same<T, U>::value
  is_convertible<T, U>::value

  * Modifications (returns a new data type)
  remove_const<T>::type
  add_const<T>::type
  remove_reference<T>::type

  * transformation 
  enable_if<B, T>::type
  When setting up a template to implement SFINAE. It is used in combination with 1 or more other typetraits
  to determine whether the template param is valid for current template specialization.
  
  C++14 shortened where type was returned: remove_const<T>::type to remove_const_t<T>
  C++17 shortened where value was returned: is_enum<T>::value to is_enum__v<T>

  Policy class 
  3rd and 4th param to stl map is a policy class, custom compare and custom allocator
*/

