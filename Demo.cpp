/**
 * Demo file for Ex3.
 *
 */
#include <iostream>
#include <stdexcept>
#include <vector>
#include "catan.hpp"
#include "player.hpp"
#include "board.hpp"
using namespace std;

int main()
{
    player p1("Amit", 1);
    player p2("Yossi", 2);
    player p3("Dana", 3);
    catan game(p1, p2, p3);
    game.howIsFirst();
    board& B = game.getBoard();
    p1.placeSettelemnt(5, B, game.getTurn(), true);
    p1.placeRoad(5, 6, B, game.getTurn(), true);
    p1.placeSettelemnt(6, B, game.getTurn(), true);
    p1.placeRoad(6, 7, B, game.getTurn(), true);
    game.end_turn();
    try
    {
        p3.placeSettelemnt(2, B, game.getTurn(), true); // p3 tries to place a settlement in the turn of p2.
    }
    catch (const std::exception &e)
    {
        cout << e.what() << endl;
    }
    p2.placeSettelemnt(2, B, game.getTurn(), true);
    p2.placeRoad(2, 3, B, game.getTurn(), true);
    p2.placeSettelemnt(12, B, game.getTurn(), true);
    p2.placeRoad(12, 11, B, game.getTurn(), true);
    game.end_turn();
    try
    {
        p3.placeSettelemnt(2, B, game.getTurn(), true); // p3 tries to place a settlement in the same location as p2.
    }
    catch (const std::exception &e)
    {
        cout << e.what() << endl;
    }

    cout << p3.getName() << " (p3) dosen't know the roles, she's retarded, please be inclusive. :) " << endl;

    p3.placeSettelemnt(16, B, game.getTurn(), true);
    p3.placeRoad(16, 15, B, game.getTurn(), true);
    p3.placeSettelemnt(15, B, game.getTurn(), true);

    try
    {
        p3.placeRoad(15, 16, B, game.getTurn(), true); // p3 tries to place a road in the same as she did.
    }
    catch (const std::exception &e)
    {
        cout << e.what() << endl;
    }
    p3.placeRoad(16, 17, B, game.getTurn(), true);
    game.end_turn();

    //to prevent low resorces throws:
    for(int i=0;i<5000;i++){
        game.split_resorces(p1.rollDice(game.getTurn()));
        game.end_turn(); 
        game.split_resorces(p2.rollDice(game.getTurn()));
        game.end_turn(); 
        game.split_resorces(p3.rollDice(game.getTurn()));
        game.end_turn(); 
    }

    // p1 has wood,bricks, and wheat, p2 has wood, ore, and wool, p3 has ore, wool, wheat.
    game.split_resorces(p1.rollDice(game.getTurn()));  
                                     // Lets say it's print 4. Then, p2 gets ore from the mountations.
    p1.placeRoad(4, 5, B, game.getTurn()); // p1 continues to build a road.
    game.end_turn();                                     // p1 ends his turn.

    game.split_resorces(p2.rollDice(game.getTurn())); // Lets say it's print 3. Then, p3 gets wheat from the Agricultural Land and Ore from the Mountains, p1 gets wheat from the Agricultural Land.
    game.end_turn();  // p3 ends his turn.
    try
    {
        game.split_resorces(p2.rollDice(game.getTurn())); // p2 tries to roll the dice again, but it's not his turn.
    }
    catch (const std::exception &e)
    {
        cout << e.what() << endl;
    }
    game.split_resorces(p3.rollDice(game.getTurn()));                       // Lets say it's print 6. Then, p1 gets bricks from the hills.
    p3.trade(p2, "Wood", "Bricks", 1, 1, game.getTurn());
    game.end_turn();                        // p1 ends his turn.

    game.split_resorces(p1.rollDice(game.getTurn()));           // Lets say it's print 9. Then, p3 gets wool from the Pasture Land, p2 gets wool from the Pasture Land.
    p1.buyDevelopmentCard(game.getTurn());
    p1.buyDevelopmentCard(game.getTurn());
    p1.buyDevelopmentCard(game.getTurn());
    p1.buyDevelopmentCard(game.getTurn());
    p1.buyDevelopmentCard(game.getTurn()); // p2 buys a development card. Lets say it is a bonus points card.
    game.end_turn();            // p2 ends his turn.

    p1.printPoints(); // p1 has 2 points because it has two settelments.
    p2.printPoints(); // p2 has 3 points because it has two settelments and a bonus points card.
    p3.printPoints(); // p3 has 2 points because it has two settelments.

    game.printWinner(); // Should print None because no player reached 10 points.
}