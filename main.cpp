#include <cppnamespace/cppnamespace.h>

/// defines which for naming the namespaces, allows the parameterized buildup of naming schemes 
#define BASE_NAMESPACE matlib  
#define MATRIX_NAMESPACE BASE_NAMESPACE, matrix
#define VECTOR_NAMESPACE BASE_NAMESPACE, vector

NS_BEGIN(MATRIX_NAMESPACE)
// equivalent to namespace matlib{ namespace matrix{ 
struct Matrix{
  auto operator()(int i, int j)->double;
};
NS_END(MATRIX_NAMESPACE)
//equivalent to }}

NS_BEGIN(VECTOR_NAMESPACE)
struct Vector : public NS(MATRIX_NAMESPACE)::Matrix{ // a vector is a matrix the namespace is accessed via NS(...) macro
 auto operator()(int i)->double;
};

NS_END(VECTOR_NAMESPACE)

int main(){
// using directive to access Vector
 NS_USE(VECTOR_NAMESPACE);

 
 Vector v;
 //global qualification for matrix - also works without using the preprocessor (but makes the code more brittle) 
 ::matlib::matrix::Matrix m;

}
