#include <iostream>
#include <string>
#include "functions.hpp"

int main(){
    std::cout<<"Welcome to the COP3504C casino!"<<std::endl;
    std::cout<<"Enter how much money to start with"<<std::endl;
    int balance;
    int profit=0;
    std::string inp;
    std::cin>>inp;
    while (!isInt(inp)){
        std::cout<<"invalid input"<<std::endl;
        std::cin>>inp;
    }
    balance=std::stoi(inp);
    std::cout<<"\nCasino Menu\n-----------\n0. Leave\n1. Visit the ATM\n2. Play blackjack\nWhat would you like do to?"<<std::endl;
    std::cin>>inp;
    while (inp!="0"){
        if (inp=="1"){
            ATM(balance);
        }
        std::cout<<"\nCasino Menu\n-----------\n0. Leave\n1. Visit the ATM\n2. Play blackjack\nWhat would you like do to?"<<std::endl;

        std::cin>>inp;

    }
    if (profit > 0){
        std::cout<<"\nLucky day huh? Congrats on your $"+std::to_string(profit)+" in winnings!"<<std::endl;
    }
    else if (profit==0){
        std::cout<<"\nLooks like you ended with what you started!"<<std::endl;
    }
    else{
        std::cout<<"\nYeowch lady luck wasn't on your side. You lost "+std::to_string(-1*profit)+" today."<<std::endl;
    }
    std::cout<<"Thanks for playing!"<<std::endl;
    return 0;
}