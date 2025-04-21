#include <string>
#include <iostream>

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
