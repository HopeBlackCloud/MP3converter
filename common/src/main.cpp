#include <iostream>
#include "EncoderController.h"

using namespace std;
using namespace MediaFramework;

int main(int argc, char* args[])
{
	if (argc == 2)
	{
		string dirPath = args[1];
		EncoderController encoderController(dirPath);
		encoderController.StartEncoders();
		encoderController.Cleanup();
	}
	else
	{
		cout<<"Usage:\nMP3Encoder <directoryPath> "<<endl;
		return 0;
	}

	return 1;
}
