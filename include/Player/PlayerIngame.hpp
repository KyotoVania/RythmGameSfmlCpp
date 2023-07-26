/*
** EPITECH PROJECT, 2023
** newtry
** File description:
** PlayerIngame.hpp
*/
#ifndef PLAYERINGAME_HPP_
	#define PLAYERINGAME_HPP_
#include <string>
using namespace std;

class PlayerIngame {
	public:
		PlayerIngame();
		~PlayerIngame();
		
	protected:
	bool GotHit;
    bool mode;
    int Score;
    int Combo;
    int Accuracy;
    int Health;
	private:
};

#endif /*PLAYERINGAME_HPP_*/