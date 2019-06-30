# StateMechanic
Embedded C++ implementation of StateMechanic targeted for IAR V850 
Code was originally created in IAR version 4.X, last changes were made in 5.10
Project targets an simulator, V850 chip is not needed to run it.


*************************************************************************************************************************************
STILL WORK IN PROGRESS


*************************************************************************************************************************************
Language used: extended embedded C++
Limitations:
	no C++11 support
	no Exception handling
	namespaces (does not work in 4.X, started to work in 5.10, backward compatibility to 4.X is needed so no namespaces are used)
	Multiple and virtual inheritance (documentation say it is supported, but it still does not work)
	no runtime information (dynamic_cast cannot be used)

	
*************************************************************************************************************************************
HOW TO RUN THE CODE

1) download a free trial of IAR V850 from https://www.iar.com/iar-embedded-workbench/#!?architecture=V850
2) install it
3) when you run the IAR, licence manager will notyfi you that you need an licence
	it can be also find in help -> License Manager... -> License -> Get Evaluation License...
4) click register and get a licence. Code size limited version will not work because codesize is bigger than 64K.
	- get time limited version
5) activate the licence
6) click on green arrow or "Ctrl+D" to run debugger 
7) Click View -> Terminal I/O to see program output
8) Click GO arrow or F5 to run the code