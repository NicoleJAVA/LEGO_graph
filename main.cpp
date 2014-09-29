#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
#include "brick.h"
int bnum = 2500;
using namespace std;
string ldrToBrickNode(string ldrLine, int c, int ldrLineLength);
int closeFile();
char filename[] = "mini_lego_set_for_building_dependency_graph"; /*filename must be array*//*dolphin_ldraw_0922*/
std::fstream ldrFile;
char brickNodeTxt[100];


char * setBrickType(char * tok, char matrixStr[50] );
struct brick bricks[2500];
/*
alongXpi = "1 0 0 0 -1 0 0 0 -1";
String alongXpiY90 = "0 0 1 0 -1 0 -1 0 0";
*/
/*    std::fstream graphFile; */
int main()
{   
	strcat(filename,".ldr");
    /* if graphFile is local, use this :    */
	std::fstream graphFile; 
	/**//*這句成語就叫做標(冒冒)檔流開，因為標(std)檔(f)流(stream)開(xxx.open())*/

	ldrFile.open(filename,std::fstream::in);
	graphFile.open("graph_mini.txt",std::fstream::trunc | std::fstream::out); /*ref-A*//*graph.txt*/
	graphFile.close();
	graphFile.open("graph_mini.txt",std::fstream::out | std::fstream::app); /*must reopen with the same flag as ref-A*//*graph.txt*/
	int c = 0; /* c is brickCounter*/
	string brickTxt;
	/*graphFile.open("graph.txt", std::fstream::out | std::fstream::app);*/
	string curLine; /*this will be current line read from the getline() function, see this later */
	/*First, check out whether graph.txt can be created*/
	if(graphFile.is_open()){ /*該.是底開()*/
        /*Secondly, make sure that the existing ldr file can be open and read*/
		if(ldrFile.is_open()){
            
			while( !ldrFile.eof() ){
            
			    getline(ldrFile, curLine);
				int curLineLength = curLine.length();
				if( curLine[0] == '1' ){
                
				brickTxt = ldrToBrickNode(curLine, c, curLineLength);
				graphFile << brickTxt << '\n';
				
					graphFile <<"shit" << '\n';
				}
				c++;
			}
		}   /*   END if(ldrFile.is_open())  END */
	    closeFile();
	}   /*   END if(graphFile.is_open())   END   */
	return 0;
}
/*
我現在要分清楚哪些是 per step 做
per step : 先讀 line ，然後 strtk，(然後判斷是哪一種type(是幾乘幾)的積木，不過這個步驟先不要管，我現在先做一個type就好)，然後把座標的位置截取下來，
然後計算(a).stud的位置 (b).hole的位置 
然後分配一個ID，然後開一個新的檔案，把ID，積木位置，此type積木的stud與hole的個數(也就是最多有幾個鄰居)，hole和stud的位置寫下來*/


int closeFile()
{
	ldrFile.close();
	return 0;

}

string ldrToBrickNode(string ldrLine, int c, int ldrLineLength)
{
   int k = 0;

   char ldrTxt[50]= "";  /*不得不說有個 [50] 還是最好用的*//* Or Use char ldrTxt[] = "";*/
   char matStr[50] =""; /* matStr is the rotation matrix that includes 9 matrix elements in one line*/
   int mat1, mat2, mat3, mat4, mat5, mat6, mat7, mat8, mat9; /*the 1st to 9th element in the rotation matrix*/
   char temp[120];
   char *legoType = new char[50]; /*.\main.cpp(109) : error C2440: '=' : 無法由 'char *' 轉換為 'char [50]'*/
   
   /* int ldrLineLength = ldrLine.length(); */
   strncpy(ldrTxt, ldrLine.c_str(), ldrLineLength);   /*strcpy(ldrTxt, ldrLine.c_str()); */
   /*right now, 馬上先檢查!*/


   char * tok;
   char tokTemp[120];
  /*tokenize out the first thing of the first line*/
   tok = strtok(ldrTxt," ");
   while(tok!=NULL){
	   
	   strcpy(brickNodeTxt, tok);
	   /*   
	   strcat(brickNodeTxt, "W");
	   */
	   tok = strtok(NULL," "); 
	   if(k==0){ /*After I test this , I found that this is not the first item in the ldraw format, this is the second, i.e., the color*/
 		   int v2 = atoi( tok);
	       bricks[c].nbNum = v2;
	   }

	   if(k==1){
 		   int x2 = atoi( tok);
	       bricks[c].x = x2;
	   }
	   if(k==2){
	       int y2 = atoi(tok);
		   bricks[c].y = y2;
	   }
	   if(k==3){
	       int z2 = atoi(tok);
		   bricks[c].z = z2;}
	   if(k==4){	       mat1 = atoi(tok);strcat(matStr,tok);}/*I don't want the 1st character of matStr to be a space*/	   
	   if(k==5){	       mat2 = atoi(tok);strcat(matStr," ");strcat(matStr,tok);}
	   if(k==6){	       mat3 = atoi(tok);strcat(matStr," ");strcat(matStr,tok);}
	   if(k==7){	       mat4 = atoi(tok);strcat(matStr," ");strcat(matStr,tok);}
	   if(k==8){	       mat5 = atoi(tok);strcat(matStr," ");strcat(matStr,tok);}
	   if(k==9){	       mat6 = atoi(tok);strcat(matStr," ");strcat(matStr,tok);}
	   if(k==10){	       mat7 = atoi(tok);strcat(matStr," ");strcat(matStr,tok);}
	   if(k==11){	       mat8 = atoi(tok);strcat(matStr," ");strcat(matStr,tok);}
	   if(k==12){	       mat9 = atoi(tok);strcat(matStr," ");strcat(matStr,tok);}
	   if(k==13){
	       legoType = setBrickType(tok, matStr); /*.\main.cpp(109) : error C2440: '=' : 無法由 'char *' 轉換為 'char [50]'*/
	   }
	   sprintf(temp, "%d", bricks[c].z);
       strcat(brickNodeTxt, temp );
	   strcat(brickNodeTxt, matStr);
       strcat(brickNodeTxt, legoType);
	   strcat(brickNodeTxt, "\nanother shit");
	   k++;
   }

   return  string(brickNodeTxt);

}

char * setBrickType(char * tok, char matrixStr[50] ){

    /*int strcmp ( const char * str1, const char * str2 );*/
	int compare;
	int compare2;
	char *brickType = new char[50]; 
	compare = strcmp(tok, "3004.dat");
	if( compare == 0){
	    compare2 = strcmp(matrixStr, "1 0 0 0 -1 0 0 0 -1"); 
		if( compare == 0){
			brickType = "1x1";
            return brickType;
		}

	}
	else{
        brickType = "nxn";
	    return brickType;
	}

    /*Nicole STYLE*//*Thanks to what Luchian Grigore answered to how to return char array in c++*/
    return brickType;
    
}