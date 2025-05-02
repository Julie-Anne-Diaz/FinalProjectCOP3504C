#include <string>
#include <iostream>
#include <vector>

//returns whether a string is an integer
bool isInt(std::string inp){
    for (size_t i = 0; i < inp.length(); i++){
        if (!isdigit(inp[i])){
            return false;
        }
    }
    return true;
}
//returns the sum of a blackjack hand according to blackjack rules (A can be 11/1 and faces are 10)
int Sum(const std::vector<int>& vec){
    int sum = 0;
    for (size_t i = 0; i < vec.size()-1; i+=2){
        if (vec[i]>10){
            //for face cards only add 10
            sum+=10;
            continue;
        }
        //otherwise add regular value
        sum+=vec[i];
    }
    for (size_t i = 0; i < vec.size()-1; i+=2){
        if (sum+10<=21 && vec[i]==1){
            //if there is an Ace and when counted as 11 the sum doesnt go over 21, adjust the sum
            sum+=10;
        }
    }
    return sum;
}
void ATM(int& balance){
    std::cout<<"\nYou are at the ATM"<<std::endl;

    //ask to withdraw or desposit money
    std::cout<<"Would you like to withdraw or deposit? (input w or d)"<<std::endl;
    std::string inp;
    std::cin>>inp;
    //input check
    while (inp!="w"&&inp!="W"&&inp!="d"&&inp!="D"){
        std::cout<<"Invalid Input"<<std::endl;
        std::cout<<"Would you like to withdraw or deposit? (input w or d)"<<std::endl;
        std::cin>>inp;
    }

    //if you want to withdraw
    if (inp=="w"||inp=="W"){
        std::cout<<"How much would you like to withdraw? Current balance: $"+std::to_string(balance)<<std::endl;
        std::cin>>inp;
        //input check
        while (!isInt(inp) || std::stoi(inp)<0){
            std::cout<<"Invalid Input. Please enter a positive integer."<<std::endl;
            std::cout<<"How much would you like to withdraw? Current balance: $"+std::to_string(balance)<<std::endl;
            std::cin>>inp;
        }
        //add to the balance
        balance+=std::stoi(inp);
        std::cout<<"$"+inp+" were added to your balance\nNew balance: $"+std::to_string(balance)<<std::endl;
    }
    //if you want to deposit
    else if (inp=="d"||inp=="D"){
        std::cout<<"How much would you like to deposit? Current balance: $"+std::to_string(balance)<<std::endl;
        std::cin>>inp;
        //input check
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
        //subtract from the balance
        balance-=std::stoi(inp);
        std::cout<<"$"+inp+" were deposited to your bank\nNew balance: $"+std::to_string(balance)<<std::endl;
    }

}
