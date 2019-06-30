#ifndef _MY_MUTEX_
#define _MY_MUTEX_

#include <intrinsics.h>
#include "stdint.h"
//Pokud nejakej podprogram/metoda/blok
//pouzije napr: Mutex m;
//tak zakazu preruseni do konce podprogramu/metody/bloku

class Mutex 
{ 
public: 
 Mutex(){
 stav_preruseni = __get_interrupt_state();
    __disable_interrupt(); 
 } 
 ~Mutex(){ 
 __set_interrupt_state(stav_preruseni);
 } 
 
 void unlock(){
   __set_interrupt_state(stav_preruseni);
 }
 
 void lock(){
   __disable_interrupt();
 } 

private: 
 uint8_t stav_preruseni; 
};

#endif