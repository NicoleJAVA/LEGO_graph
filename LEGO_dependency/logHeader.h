#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;   // �O�ѤF using ���A���M de ���� bug

std::fstream logFile2;

void openLogFile2()
{
//**************************************
	logFile2.open("log2.txt",std::fstream::trunc | std::fstream::out); /*ref-A*//*graph.txt*/
	logFile2.close();
	logFile2.open("log2.txt",std::fstream::out | std::fstream::app); /*must reopen with the same flag as ref-A*//*graph.txt*/
//**************************************
}
