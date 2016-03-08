#include "Factory.h"
//You may add #include statements here
#include "QS.h"
/*
	You will MODIFY THIS DOCUMENT.
*/
//=======================================================================================
/*
	getQS()

	Creates and returns an object whose class extends QSInterface.
	This should be an object of a class you have created.

	Example: If you made a class called "QS", you might say, "return new QS();".
*/
QSInterface * Factory::getQS()
{
  //return NULL;//Modify this line
  return new QS();
}
