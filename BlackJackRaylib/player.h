#pragma once  
#include "Person.h"  
class Player : public Person  
{  
	enum Choice
   {
      HIT,
      STAND,
   };
public:  
   bool allowPlayerInput = true;
   Choice choice;
   Player() : Person() 
   {
      score = checkHand();
   } 
   void stand(); 
   bool isPlaying(bool choice);
};