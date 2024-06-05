#include "grammar.h"
#include<sstream>
#include<iostream>
grammar::grammar(const std::string filepath)
{
    std::ifstream infile(filepath);

    if (infile.is_open()) {
        std::string sentence;
        while (std::getline(infile, sentence))
        {
            std::stringstream ss(sentence);
            std::string left,assign,right;
            grammarNode newnode;
            ss >> left>>assign;
            unendSet.insert(left);
            newnode.left = left;
            while (ss >> right){
            
                newnode.right.push_back(right);
            }
            G.push_back(newnode);
            
        }

    }
    else
    {
        std::cout << "grammar error";
    }

    return;
}
