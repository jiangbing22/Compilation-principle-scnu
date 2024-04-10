#include <unordered_map>
#include <stack>
#include <string>
#include<set>
using namespace std;

class RE {
public:
    RE(string initial) : re(initial) {
        init();
        to_post();
    };

    RE() {}

    void init();
    string get_post() { return re_post; };
    string get_re() { return re; };

private:
    unordered_map<char, int> prior = {
        {'*', 100}, {'+', 100}, {'?', 100}, {'.', 80}, {'|', 60}, {'@', 70}
    };
    string re;
    string re_post;

    void to_post();
};

void RE::init() {
    string result = "";
    string regex = re;
    for (size_t i = 0; i < regex.length(); i++) {
        result += regex[i];
        if (i == regex.length() - 1)
        {
            break;
        }
        if (isalpha(regex[i])||regex[i] == '*' || regex[i] == '+' || regex[i] == '?'||regex[i]==')')
        {
            
            if (isalpha(regex[i + 1]) || regex[i + 1] == '(')
            {
                result.push_back('@');
            }
        }
        
        

    }
    re = result;
}

void RE::to_post() {
    if (re.empty()) {
        re_post = "";
        return;
    }

    stack<char> operators;
    string postfix = "";
    string infix = re;

    for (char c : infix) {
        if (isalnum(c)) {
            
            postfix += c;
            
        }
        else if (c == '(') {
            operators.push(c);
        }
        else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                postfix += operators.top();
                operators.pop();
            }
            operators.pop();
        }
        else {
            while (!operators.empty() && prior[operators.top()] >= prior[c]) {
                postfix += operators.top();
                operators.pop();
            }
            operators.push(c);
        }
    }

    while (!operators.empty()) {
        postfix += operators.top();
        operators.pop();
    }

    re_post = postfix;
}

//struct  NFA_node
//{
//    int index; //×´Ì¬ºÅ
//    char input;//±ßÉÏµÄÖµ
//    int Trans;//»¡×ªÒÆ×´Ì¬ºÅ
//    set<int> epTrans;//3×ªÒÆ×´Ì¬ºÅ¼¯ºÏ
//
//};


class NFA
{
public:
    void build_NFA();
    
    


private:
    struct NFA_graph
    {
    public:
        NFA_graph()
        {
            Graph.resize(1);
            start = end = 0;
        }
        size_t size() const
        {
            return Graph.size();
        }
        unordered_map<char, vector<int>>& operator[](int n)
        {
            if (n < Graph.size())
            {
                return Graph[n];
            }
        }
        NFA_graph& operator+=(NFA_graph b)
        {
            int offset = size();
            for (int i = 0; i < b.size(); ++i)
            {
                Graph.push_back(b[i]);
                for (auto& k : Graph.back())
                    for (auto& v : k.second)
                        v += offset;
            }
            return *this;
        }
        vector<unordered_map<char, vector<int>>> Graph;
        int start, end;
    };
    stack<NFA_graph> stk;

};
void NFA::build_NFA()
{

}



class DFA
{
public:


private:
   



};
std::string NFA::re_post(std::string re)
{
    string a;
        return  a;
}

