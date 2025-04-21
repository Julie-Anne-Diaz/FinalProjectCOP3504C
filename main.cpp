#include <iostream>
#include <string>

bool isInt(std::string inp){
    for (size_t i = 0; i < inp.length(); i++){
        if (!isdigit(inp[i])){
            return false;
        }
    }
    return true;
}
void ATM(int& balance){
    std::cout<<"\nYou are at the ATM"<<std::endl;
    std::cout<<"Would you like to withdraw or deposit? (input w or d)"<<std::endl;
    std::string inp;
    std::cin>>inp;
    while (inp!="w"&&inp!="W"&&inp!="d"&&inp!="D"){
        std::cout<<"Invalid Input"<<std::endl;
        std::cout<<"Would you like to withdraw or deposit? (input w or d)"<<std::endl;
        std::cin>>inp;
    }
    if (inp=="w"||inp=="W"){
        std::cout<<"How much would you like to withdraw? Current balance: $"+std::to_string(balance)<<std::endl;
        std::cin>>inp;
        while (!isInt(inp) || std::stoi(inp)<0){
            std::cout<<"Invalid Input. Please enter a positive integer."<<std::endl;
            std::cout<<"How much would you like to withdraw? Current balance: $"+std::to_string(balance)<<std::endl;
            std::cin>>inp;
        }
        balance+=std::stoi(inp);
        std::cout<<"$"+inp+" were added to your balance\nNew balance: $"+std::to_string(balance)<<std::endl;
    }
    else if (inp=="d"||inp=="D"){
        std::cout<<"How much would you like to deposit? Current balance: $"+std::to_string(balance)<<std::endl;
        std::cin>>inp;
        while (!isInt(inp) || std::stoi(inp)<0 || std::stoi(inp)>balance){
            if (!isInt(inp) || std::stoi(inp)<0){
                std::cout<<"Invalid Input. Please enter a positive integer."<<std::endl;
            }
            else{
                std::cout<<"You can't deposit more than what's in your balance!"<<std::endl;
            }
            std::cout<<"How much would you like to deposit? Current balance: $"+std::to_string(balance)<<std::endl;
            std::cin>>inp;
        }
        balance-=std::stoi(inp);
        std::cout<<"$"+inp+" were deposited to your bank\nNew balance: $"+std::to_string(balance)<<std::endl;
    }

}

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