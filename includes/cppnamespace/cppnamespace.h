/*

Copyright (c) 2014 Tobias Becker
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/



/// expands the expression X
#define NS_EXPAND(X) X
/// concatenates to elements
#define NS_CONCAT(X,Y) X##Y
/// helper
#define NS_NUM_ARGS_(X100, X99, X98, X97, X96, X95, X94, X93, X92, X91, X90, X89, X88, X87, X86, X85, X84, X83, X82, X81, X80, X79, X78, X77, X76, X75, X74, X73, X72, X71, X70, X69, X68, X67, X66, X65, X64, X63, X62, X61, X60, X59, X58, X57, X56, X55, X54, X53, X52, X51, X50, X49, X48, X47, X46, X45, X44, X43, X42, X41, X40, X39, X38, X37, X36, X35, X34, X33, X32, X31, X30, X29, X28, X27, X26, X25, X24, X23, X22, X21, X20, X19, X18, X17, X16, X15, X14, X13, X12, X11, X10, X9, X8, X7, X6, X5, X4, X3, X2, X1, N, ...)   N
/// expands to the number of arguments passed to the macro or rather the number of commas + 1
#define NS_NUM_ARGS(...) NS_EXPAND(NS_NUM_ARGS_(__VA_ARGS__, 100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1))

/// returns the first element of a preprocessor argument list
#define NS_FIRST(X, ...) X
/// returns all elements except the first of a preprocessor argument list
#define NS_REST(X, ...) __VA_ARGS__


#define NS_REDUCE_1(M, SEPARATOR,X) M(X)
#define NS_REDUCE_2(M, SEPARATOR,...)  NS_EXPAND(M(NS_FIRST(__VA_ARGS__))) SEPARATOR NS_REDUCE_1(M,SEPARATOR,NS_EXPAND(NS_REST(__VA_ARGS__)))
#define NS_REDUCE_3(M, SEPARATOR,...)  NS_EXPAND(M(NS_FIRST(__VA_ARGS__))) SEPARATOR NS_REDUCE_2(M,SEPARATOR,NS_EXPAND(NS_REST(__VA_ARGS__)))
#define NS_REDUCE_4(M, SEPARATOR,...)  NS_EXPAND(M(NS_FIRST(__VA_ARGS__))) SEPARATOR NS_REDUCE_3(M,SEPARATOR,NS_EXPAND(NS_REST(__VA_ARGS__)))
#define NS_REDUCE_5(M, SEPARATOR,...)  NS_EXPAND(M(NS_FIRST(__VA_ARGS__))) SEPARATOR NS_REDUCE_4(M,SEPARATOR,NS_EXPAND(NS_REST(__VA_ARGS__)))
#define NS_REDUCE_6(M, SEPARATOR,...)  NS_EXPAND(M(NS_FIRST(__VA_ARGS__))) SEPARATOR NS_REDUCE_5(M,SEPARATOR,NS_EXPAND(NS_REST(__VA_ARGS__)))
#define NS_REDUCE_7(M, SEPARATOR,...)  NS_EXPAND(M(NS_FIRST(__VA_ARGS__))) SEPARATOR NS_REDUCE_6(M,SEPARATOR,NS_EXPAND(NS_REST(__VA_ARGS__)))
#define NS_REDUCE_8(M, SEPARATOR,...)  NS_EXPAND(M(NS_FIRST(__VA_ARGS__))) SEPARATOR NS_REDUCE_7(M,SEPARATOR,NS_EXPAND(NS_REST(__VA_ARGS__)))
#define NS_REDUCE_9(M, SEPARATOR,...)  NS_EXPAND(M(NS_FIRST(__VA_ARGS__))) SEPARATOR NS_REDUCE_8(M,SEPARATOR,NS_EXPAND(NS_REST(__VA_ARGS__)))
#define NS_REDUCE_10(M, SEPARATOR,...)  NS_EXPAND(M(NS_FIRST(__VA_ARGS__))) SEPARATOR NS_REDUCE_9(M,SEPARATOR,NS_EXPAND(NS_REST(__VA_ARGS__)))
#define NS_REDUCE_N(N, M, SEPARATOR, ...) NS_CONCAT(NS_REDUCE_,N) (M,SEPARATOR,__VA_ARGS__)
/// reduce macro expands M for every element of the VAR_ARGS and separates them by the separator given
/// e.g.  #define MYOP(X) X##X 
///       NS_REDUCE(MYOP,_,a,b,c) will expand to aa_bb_cc
#define NS_REDUCE(M,SEPARATOR,...) NS_REDUCE_N(NS_NUM_ARGS(__VA_ARGS__),M,SEPARATOR,__VA_ARGS__)
/// macro which does nothing but expand X



#define NS_NAMESPACE_PREPEND_NAMESPACE(X) namespace X {
#define NS_NAMESPACE_APPEND_NAMESPACE(X) }


// long form macros
#define NS_NAMESPACE_BEGIN(...) NS_REDUCE(NS_NAMESPACE_PREPEND_NAMESPACE, , __VA_ARGS__)
#define NS_NAMESPACE_END(...) NS_REDUCE(NS_NAMESPACE_APPEND_NAMESPACE, ,__VA_ARGS__)
#define NS_NAMESPACE(...) NS_REDUCE(NS_EXPAND, ::, __VA_ARGS__)
#define NS_NAMESPACE_USE(...) using namespace NS_NAMESPACE(__VA_ARGS__)

/// renamed macros for ease of use

/// converts the list of namespaces into the namespace qualification e.g. NS(a,b,c) will expand to a::b::c
#define NS(...) NS_NAMESPACE(__VA_ARGS__)
/// converts the list of namespaces into the corresponding namespace headers
/// e.g.  NS_BEGIN(a,b,c) expands to namespace a{namespace b{ namespace c{
#define NS_BEGIN(...)NS_NAMESPACE_BEGIN(__VA_ARGS__)
/// converts the list of namespace into the corresponding namespace footers
/// e.g. NS_END(a,b,c) expands to }}}
#define NS_END(...) NS_NAMESPACE_END(__VA_ARGS__)
/// shorthand for using namespace NS(...) 
/// e.g.  NS_USE(a,b,c); will result in using namespace a,b,c;
#define NS_USE(...) NS_NAMESPACE_USE(__VA_ARGS__)


