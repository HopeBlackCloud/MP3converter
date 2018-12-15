/****************************************************************
This class aims to implement custom exception for wav files.

 Author: Murat Karabulut
 Date:   06.06.2018
*****************************************************************/
#ifndef WAVFILEEXCEPTION_H
#define WAVFILEEXCEPTION_H

#include <iostream>
#include <exception>

using namespace std;

namespace MediaFramework
{
   
	class WavFileException : public exception
	{
		public:
		
			virtual const char* what() const throw() 
			{ 
				return "Wav file open/read error occured!"; 
			}
	};
}

#endif

