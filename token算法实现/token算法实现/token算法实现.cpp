#include <iostream>
#include <string>
#include<unordered_set>
using namespace std;

/* 单词编码 */
enum TokenCode
{
	UNDEF=0,
	KEYWORD,
	OPERATOR,
	IDENTIFIER,
	COMMENT,
	PUNCTUATION,
	INT,
	FLOAT,
	CHAR,
	STRING,
};
const std::unordered_set<std::string> keywords = {
    "alignas", "alignof", "and", "and_eq", "asm", "atomic_cancel", "atomic_commit", "atomic_noexcept", "auto",
    "bitand", "bitor", "bool", "break", "case", "catch", "char", "char8_t", "char16_t", "char32_t", "class",
    "compl", "concept", "const", "consteval", "constexpr", "constinit", "const_cast", "continue", "co_await",
    "co_return", "co_yield", "decltype", "default", "delete", "do", "double", "dynamic_cast", "else", "enum",
    "explicit", "export", "extern", "false", "float", "for", "friend", "goto", "if", "inline", "int", "long",
    "mutable", "namespace", "new", "noexcept", "not", "not_eq", "nullptr", "operator", "or", "or_eq", "private",
    "protected", "public", "register", "reinterpret_cast", "requires", "return", "short", "signed", "sizeof",
    "static", "static_assert", "static_cast", "struct", "switch", "synchronized", "template", "this",
    "thread_local", "throw", "true", "try", "typedef", "typeid", "typename", "union", "unsigned", "using",
    "virtual", "void", "volatile", "wchar_t", "while", "xor", "xor_eq"
};

bool isKeyword(const std::string& word) {
    return keywords.find(word) != keywords.end();
}
string to_chinese(TokenCode key)
{
    switch (key)
    {
    case UNDEF:
        return "未定义字符";
        break;
    case KEYWORD:
        return "关键字";
        break;
    case OPERATOR:
        return "运算符";
        break;
    case IDENTIFIER:
        return "标识符";
        break;
    case COMMENT:
        return "注释";
        break;
    case PUNCTUATION:
        return "标点符号";
        break;
    case INT:
        return "整数";
        break;
    case FLOAT:
        return "浮点数";
        break;
    case CHAR:
        return "字符";
        break;
    case STRING:
        return "字符串";
        break;
    default:
        return "未知类型";
        break;
    }
}
bool isLetter(char letter)
{
    if ((letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z'))
        return true;
    return false;

}
bool isDigit(char digit)
{
    if (digit >= '0' && digit <= '9')
        return true;
    return false;
}

string scan(string code)
{
    string token="";
    string result = "";
    auto it = code.begin();
    while (it != code.end())
    {
        char ch = *it;
        if (ch == ' ')
        {
            continue;
        }
       else if (isLetter(ch))
        {
            token + ch;
            ch++;
        }
       else if (isDigit(ch))
        {

        }
       else
        {

        }
    }
    return result;
}