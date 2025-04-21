#include <iostream>
#include <string>
#include <limits>

bool isInt(std::string inp){
    for (size_t i = 0; i < inp.length(); i++){
        if (!isdigit(inp[i])){
            return false;
        }
    }
    return true;
}

int main(){
    std::cout<<"Welcome to COP3504C blackjack!"<<std::endl;
    std::cout<<"Enter how much money to start with"<<std::endl;
    int funds;
    std::string inp;
    std::cin>>inp;
    while (!isInt(inp)){
        std::cout<<"invalid input"<<std::endl;
        std::cin>>inp;
    }
    funds=stoi(inp);
    std::cout<<"$"<<funds<<std::endl;
    return 0;
}