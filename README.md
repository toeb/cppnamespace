# cppnamespace
![cppnamespace logo](/cppnamespacelogo.png "cppnamespace logo")

## Motiviation

If you work are starting to work on a library and do not know exactly how your namespaces are going to look these macro helper are for you.  I have written helpers that simplify using namespace and lets you build up your namespaces with preprocessor variables. This allows you to quickly rename your namespaces which in turn makes it alot more flexible.  

The reason why I wanted to have my namespaces dynamically generated allow me to statically link multiple versions of the same library and to achieve this I want to prepende a versioned namespace e.g. wrap all namespaces in another namespace.  This could have been achieved by wrapping the all include files in another namespace but some edge cases did not allow me to do it.  So I chose to let make the namespaces "dynamic" as in compile time dynamic.

## Documentation
I provide you with the following macros:

```
NS_BEGIN(...)
NS_END(...)
NS(...)
NS_USE(...)  
```

Instead of using `namespace X{ namespace Y{  ... } }` you write `NS_BEGIN(X,Y)  ... NS_END(X,Y)` these macros expand to the namespace definitions and allow you to use preprocessor defines to name your namespaces.  As nice side effect is that your code is not indented anymore by your IDE which, in my opinion, makes the code harder to read as you have more and more nested namespaces. Also you can explicitly see where your namespace ends.  

Of course your personal preferences may differ, but when refactoring without expensive tools defining your namespaces like this helps alot as you only have to change it once.  Furthermore you can easily ad a build task that replaces these macros with the correct namespaces if you release your source code/ headers. (or leave them in, especially if you want your library users to be able to change the namespace as well).

Besides beginning and ending a namespace you can also use `NS(X,Y)` to reference a namespace as it is expanded to `X::Y` and another shorthand which is useful is `NS_USE(X,Y)` which just creates a using namespace statement: `using namespace X::Y`.

Of course you can also mix the macro based namespace and hardcoded namespace statement to your hearts content.

## Example 
Here is an example application that shows you how to use these macros:

```
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

```



Limitations:
* Due to NS_REDUCE you can at most nest 100 namespaces (which is unrealistic) 
* No anonymouse namespaces are possible using this technique (but you can still hardcode them)


I am happy for any critiques in form of comments, stars, upvotes, likes, etc.  Especially if you find this useful let me know! I am aware there is only a niche audience for this kind of preprocessor stuff but I do like to share :)


