#include "SlotMachine.hpp"
#include <vector>
#include <string>
#include <iostream>
#include "functions.hpp"
#include <cstdlib>

//bound so its a valid outcome from the slots outcomes vector
void Bound(int& num){
    if (num>=9){
        num=num-9;
    }
    if (num<0){
        num=num+9;
    }
}

//show the slots
bool Display_Slots(int one, int two, int three){
    //vector of the possible outcomes
    std::vector<std::string> outcomes = {"🍒","💎","🍋‍🟩","❤️","💸","🔔","🍀","👑","🪙"};

    //display the top two rows of the slots
    for (int i = 0; i < 2; i++){
        Bound(one);
        Bound(two);
        Bound(three);
        std::cout<<outcomes[one]<<outcomes[two]<<outcomes[three]<<std::endl;
        one++;
        two++;
        three++;
    }

    //display the middle row of the slots
    Bound(one);
    Bound(two);
    Bound(three);
    std::cout<<"-------\n"+outcomes[one]+outcomes[two]+outcomes[three]+"\n-------"<<std::endl;
    one++;
    two++;
    three++;

    //display the bottom two rows of the slots
    for (int i = 0; i < 2; i++){
        Bound(one);
        Bound(two);
        Bound(three);
        std::cout<<outcomes[one]<<outcomes[two]<<outcomes[three]<<std::endl;
        one++;
        two++;
        three++;
    }

    //if the player wins return true
    if (one==two&&two==three){
        return true;
    }
    return false;
}

void Slot_Machine(int& balance, int& profit){
    std::string inp = "";

    int bet = 0;

    std::cout<<"\nWelcome to the Slots!\n"<<std::endl;
    std::cout<<"Line up the figures to 100x your money\n"<<std::endl;

    //while player doesnt press 0 to exit
    while (inp!="0"){

        //place bets
        std::cout<<"\nCurrent balance: "+std::to_string(balance)<<std::endl;
        std::cout<<"Place your bets"<<std::endl;
        std::cin>>inp;
        //input check
        while (!isInt(inp) || std::stoi(inp) > balance || std::stoi(inp)<=0){
            if (!isInt(inp) || std::stoi(inp)<=0){
                std::cout<<"Invalid input. Please Enter a positive integer."<<std::endl;
            }
            else{
                std::cout<<"Insufficient funds!"<<std::endl;
            }
            std::cout<<"Current balance: "+std::to_string(balance)<<std::endl;
            std::cout<<"Place your bets"<<std::endl;
            std::cin>>inp;
        }

        //display random slots
        bet = std::stoi(inp);
        std::cout<<"Rolling..."<<std::endl;
        if (Display_Slots(rand()%9,rand()%9,rand()%9)){
            //player wins adjust balance and profit
            std::cout<<"YOU WIN $"+std::to_string(bet*100)<<std::endl;
            balance+=bet*100;
            profit+=bet*100;
        }
        else{
            //player loses adjust balance and profit
            std::cout<<"You lost $"+std::to_string(bet)<<std::endl;
            balance-=bet;
            profit-=bet;
        }
        std::cout<<"Press any key to continue, 0 to exit."<<std::endl;
        std::cin>>inp;

    }

}