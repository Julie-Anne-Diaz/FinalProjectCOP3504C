#include <iostream>     
#include <string>
#include <cstdlib>
#include "functions.hpp"

void Hit(std::vector<int>& hand){
    hand.push_back(rand()%13+1);
    hand.push_back((rand()%4+1)*-1);
}

std::string GetSuit(const int& suit){
    if (suit==1){
        return "A";
    }
    else if (suit==-1){
        return "❤️";
    }
    else if (suit ==-2 ){
        return "♦️";
    }
    else if (suit==-3){
        return "♣️";
    }
    else if (suit==-4){
        return "♠️";
    }
    else if (suit==11){
        return "J";
    }
    else if (suit==12){
        return "Q";
    }
    else if (suit==13){
        return "K";
    }
    else{
        return std::to_string(suit);
    }
}
void ShowHands(const std::vector<int>& dealer, const std::vector<int>& player, const bool& revealDealer){
    std::string out = "Dealer Hand\n-----------\n";
    if (revealDealer){
        for (size_t i = 0; i < dealer.size()-1; i+=2){
            out+="["+GetSuit(dealer[i])+GetSuit(dealer[i+1])+"] ";
        }
    }
    else{
        out+="["+GetSuit(dealer[0])+GetSuit(dealer[1])+"] [** ]";
    }
    out+="\n\nPlayer Hand\n-----------\n";
    
    for (size_t i = 0; i <player.size()-1; i+=2){
        out+="["+GetSuit(player[i])+GetSuit(player[i+1])+"] ";
    }
    out+="\n";
    std::cout<<out<<std::endl;
}

void Black_Jack(int& balance, int& profit){
    std::string inp = "";

    int bet = 0;
    std::vector<int> dealerHand;
    std::vector<int> playerHand;

    std::cout<<"\nWelcome to BlackJack!\n"<<std::endl;
    while (inp!="0"){
        std::cout<<"Current balance: "+std::to_string(balance)<<std::endl;
        std::cout<<"Place your bets"<<std::endl;
        std::cin>>inp;

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
        bet = std::stoi(inp);
        std::cout<<"\n";
        bool lost = false;
        playerHand.clear();
        dealerHand.clear();
        Hit(playerHand);
        Hit(playerHand);
        Hit(dealerHand);
        Hit(dealerHand);
        if ((dealerHand[0]>=11&&dealerHand[2]==1)||(dealerHand[0]==1&&dealerHand[2]>=11)){
            std::cout<<"BlackJack\n";
            lost=true;
            ShowHands(dealerHand,playerHand,true);
        }
        else{
            ShowHands(dealerHand,playerHand,false);
        }
        while (!lost){
            std::cout<<"Bet: $"+std::to_string(bet)+"\n"<<std::endl;
            std::cout<<"Would you like to: \n1. Stand\n2. Hit\n3. Double Down"<<std::endl;

            std::cin>>inp;
            while (inp!="1"&&inp!="2"&&inp!="3"){
                std::cout<<"Invalid Input."<<std::endl;
                std::cout<<"Would you like to: \n1. Stand\n2. Hit\n3. Double Down"<<std::endl;
                std::cin>>inp;
            }
            if (inp=="1"){
                std::cout<<"\nStanding\nDealer Shows\n";
                ShowHands(dealerHand,playerHand,true);
                std::cout<<"Bet: $"+std::to_string(bet)+"\n\n"<<std::endl;

                while (Sum(dealerHand)<Sum(playerHand)&&Sum(dealerHand)<21){
                    Hit(dealerHand);
                    std::cout<<"Dealer Hits\n\n";
                    ShowHands(dealerHand,playerHand,true);
                    std::cout<<"Bet: $"+std::to_string(bet)+"\n\n"<<std::endl;

                }
                if (Sum(dealerHand)>Sum(playerHand)&&Sum(dealerHand)<=21){
                    lost=true;
                }
                break;
            }
            else if (inp=="2"){
                Hit(playerHand);
                ShowHands(dealerHand,playerHand,false);
                if (Sum(playerHand)>21){
                    lost=true;
                    break;
                }

            }
            else if (inp=="3"){
                if (bet*2>balance){
                    std::cout<<"Insuffiecient funds to double!"<<std::endl;
                }
                else if (playerHand.size()==4){
                    bet*=2;
                    std::cout<<"Feeling Lucky! Bets doubled to: $"<<std::to_string(bet)<<std::endl;
                }
                else{
                    std::cout<<"Game already started cannot double!"<<std::endl;
                }
            }
            else{
                std::cout<<"Invalid Input."<<std::endl;
            }

        }
        if (Sum(playerHand)==Sum(dealerHand)){
            std::cout<<"Push"<<std::endl;
            std::cout<<"Bets returned to balance"<<std::endl;
        }
        else if (lost){
            std::cout<<"You Lose."<<std::endl;
            std::cout<<"$"+std::to_string(bet)+" lost"<<std::endl;
            profit-=bet;
            balance-=bet;
            bet=0;
        }
        else{
            std::cout<<"You Win!"<<std::endl;
            std::cout<<"$"+std::to_string(bet)+" won"<<std::endl;
            profit+=bet;
            balance+=bet;
            bet=0;
        }

        std::cout<<"Press 0 to return to the main menu, or any key to continue"<<std::endl;
        std::cin>>inp;
    }
    
}