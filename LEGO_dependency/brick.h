#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct brick{

    int ID;
	std::string btype;
	std::string btypeStr;
	int x;
	int y;
	int z;
	int nbNum; /*numbers of neighbor*/
	int studXNum;
	int studZNum;
	int holeXNum;
	int holeZNum;
	int heightY;
	int dpdt_on[30];
	int prior_to[30]; //"is dependent upon by"
	int dpdtCount;
	int priorCount;
    
};   /*   END brick   */

//-------------------------- 
struct brick bricks[2500];
//--------------------------