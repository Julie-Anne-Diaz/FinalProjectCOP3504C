#include <iostream>     
#include <string>
#include <cstdlib>
#include "functions.hpp"

//add a random card to the hand (one number and one suit)
void Hit(std::vector<int>& hand){
    hand.push_back(rand()%13+1);
    hand.push_back((rand()%4+1)*-1);
}

//return the suit or symbol equivalent of the number
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

//display the dealer and player hands to the console
void ShowHands(const std::vector<int>& dealer, const std::vector<int>& player, const bool& revealDealer){
    //if the dealer has shown his cards
    std::string out = "Dealer Hand\n-----------\n";
    if (revealDealer){
        for (size_t i = 0; i < dealer.size()-1; i+=2){
            //display each card
            out+="["+GetSuit(dealer[i])+GetSuit(dealer[i+1])+"] ";
        }
    }
    //if it isnt the dealers turn
    else{
        //display each card except the last
        out+="["+GetSuit(dealer[0])+GetSuit(dealer[1])+"] [** ]";
    }
    out+="\n\nPlayer Hand\n-----------\n";
    
    //display players hand
    for (size_t i = 0; i <player.size()-1; i+=2){
        //dislay each card
        out+="["+GetSuit(player[i])+GetSuit(player[i+1])+"] ";
    }
    out+="\n";
    std::cout<<out<<std::endl;
}

//black jack game
void Black_Jack(int& balance, int& profit){
    std::string inp = "";

    //initialize the bets to zero and make vectors to hold the dealer and player hands
    int bet = 0;
    std::vector<int> dealerHand;
    std::vector<int> playerHand;

    std::cout<<"\nWelcome to BlackJack!\n"<<std::endl;

    //while the player doesnt input 0 to leave
    while (inp!="0"){
        //ask the player how much they want to bet
        std::cout<<"Current balance: "+std::to_string(balance)<<std::endl;
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

        //empty the player hand set the bet and add two cards to both players hands
        bet = std::stoi(inp);
        std::cout<<"\n";
        bool lost = false;
        playerHand.clear();
        dealerHand.clear();
        Hit(playerHand);
        Hit(playerHand);
        Hit(dealerHand);
        Hit(dealerHand);

        ShowHands(dealerHand,playerHand,false);
        
        while (!lost){
            //check for blackjacks (Ace and a 10)
            if ((dealerHand[0]>=11&&dealerHand[2]==1)||(dealerHand[0]==1&&dealerHand[2]>=11)){
                std::cout<<"BlackJack\n";
                lost=true;
                ShowHands(dealerHand,playerHand,true);
                break;
            }
            else if ((playerHand[0]>=11&&playerHand[2]==1)||(playerHand[0]==1&&playerHand[2]>=11)){
                std::cout<<"BlackJack\n";
                ShowHands(dealerHand,playerHand,true);
                break;
            }

            //ask if the player would like to stand hit or double their bet
            std::cout<<"Bet: $"+std::to_string(bet)+"\n"<<std::endl;
            std::cout<<"Would you like to: \n1. Stand\n2. Hit\n3. Double Down"<<std::endl;

            std::cin>>inp;
            //input check
            while (inp!="1"&&inp!="2"&&inp!="3"){
                std::cout<<"Invalid Input."<<std::endl;
                std::cout<<"Would you like to: \n1. Stand\n2. Hit\n3. Double Down"<<std::endl;
                std::cin>>inp;
            }
            //stand
            if (inp=="1"){
                std::cout<<"\nStanding\nDealer Shows\n";
                //show dealers cards
                ShowHands(dealerHand,playerHand,true);
                std::cout<<"Bet: $"+std::to_string(bet)+"\n\n"<<std::endl;
                //while the dealer hasnt beat the player or hit 21 keep adding cards to his hand
                while (Sum(dealerHand)<Sum(playerHand)&&Sum(dealerHand)<21){
                    Hit(dealerHand);
                    std::cout<<"Dealer Hits\n\n";
                    ShowHands(dealerHand,playerHand,true);
                    std::cout<<"Bet: $"+std::to_string(bet)+"\n\n"<<std::endl;

                }
                //check if dealer won
                if (Sum(dealerHand)>Sum(playerHand)&&Sum(dealerHand)<=21){
                    lost=true;
                }
                break;
            }
            //hit
            else if (inp=="2"){
                //add a card to players hand
                Hit(playerHand);
                //check if player lost
                ShowHands(dealerHand,playerHand,false);
                if (Sum(playerHand)>21){
                    lost=true;
                    break;
                }

            }
            //double bets
            else if (inp=="3"){
                //check if hte player has enough to double
                if (bet*2>balance){
                    std::cout<<"Insuffiecient funds to double!"<<std::endl;
                }
                //if player holds two cards
                else if (playerHand.size()==4){
                    bet*=2;
                    std::cout<<"Feeling Lucky! Bets doubled to: $"<<std::to_string(bet)<<std::endl;
                }
                //too late to double (more than two cards)
                else{
                    std::cout<<"Game already started cannot double!"<<std::endl;
                }
            }
            else{
                std::cout<<"Invalid Input."<<std::endl;
            }

        }
        //equal hands return bets
        if (Sum(playerHand)==Sum(dealerHand)){
            std::cout<<"Push"<<std::endl;
            std::cout<<"Bets returned to balance"<<std::endl;
        }
        //player lost
        else if (lost){
            std::cout<<"You Lose."<<std::endl;
            std::cout<<"$"+std::to_string(bet)+" lost"<<std::endl;
            //adjust profit count and balance
            profit-=bet;
            balance-=bet;
            bet=0;
        }
        //player won
        else{
            std::cout<<"You Win!"<<std::endl;
            std::cout<<"$"+std::to_string(bet)+" won"<<std::endl;
            //adjust profit count and balance
            profit+=bet;
            balance+=bet;
            bet=0;
        }

        std::cout<<"Press 0 to return to the main menu, or any key to continue"<<std::endl;
        std::cin>>inp;
    }
    
}