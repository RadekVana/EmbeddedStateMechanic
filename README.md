# StateMechanic
Embedded C++ implementation of StateMechanic https://github.com/canton7/StateMechanic
targeted for IAR V850 
Code was originally created in IAR version 4.X, last changes were made in 5.10
Project targets the V850 simulator, V850 chip is not needed to run it.
This project is ment just to show my work


*************************************************************************************************************************************
Used language: extended embedded C++
Limitations:
	no C++11 support
	no Exception handling
	namespaces (does not work in 4.X, started to work in 5.10, backward compatibility to 4.X is needed so no namespaces are used)
	Multiple and virtual inheritance (documentation says it is supported, but it still does not work)
	no runtime information (dynamic_cast cannot be used)

	
*************************************************************************************************************************************
HOW TO RUN THE CODE

1) download a free trial of IAR V850 from https://www.iar.com/iar-embedded-workbench/#!?architecture=V850
2) install it
3) when you run the IAR, licence manager notifies you that you need an licence
	it could be also found in help -> License Manager... -> License -> Get Evaluation License...
4) click register and get a licence. Code size limited version would not work because code size is bigger than 64K.
	- get time limited version
5) activate the licence
6) click on green arrow or "Ctrl+D" to run debugger 
7) Click View -> Terminal I/O to see program output
8) Click GO arrow or F5 to run the code


*************************************************************************************************************************************
MISSING THINGS - STILL WORK IN PROGRESS
*	CHILD STATE MACHINES 

*	UNIT TESTS OF STATE TEMPLATE METHODS
*	UNIT TESTS OF TRANSITION GUARDS



*************************************************************************************************************************************
NOT IMPLEMENTED THINGS:
*	Event.Fire() method (due no exception handling), only Event.TryFire() can be used
*	Serializatoin or printing state machine 
*	Names of objects (so they can be much smaller) 
*	Forced fransitions. They are very unclean. I do not think they are needed at all.
 
*************************************************************************************************************************************
NON ESSENCIAL FUNCTIONALITY THAT COULD BE IMPLEMENTED IN FUTURE 
*	Dynamic Transitions
*	STATE GROUPS 