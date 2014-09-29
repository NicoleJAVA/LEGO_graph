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
	/**//*�o�y���y�N�s����(�_�_)�ɬy�}�A�]����(std)��(f)�y(stream)�}(xxx.open())*/

	ldrFile.open(filename,std::fstream::in);
	graphFile.open("graph_mini.txt",std::fstream::trunc | std::fstream::out); /*ref-A*//*graph.txt*/
	graphFile.close();
	graphFile.open("graph_mini.txt",std::fstream::out | std::fstream::app); /*must reopen with the same flag as ref-A*//*graph.txt*/
	int c = 0; /* c is brickCounter*/
	string brickTxt;
	/*graphFile.open("graph.txt", std::fstream::out | std::fstream::app);*/
	string curLine; /*this will be current line read from the getline() function, see this later */
	/*First, check out whether graph.txt can be created*/
	if(graphFile.is_open()){ /*��.�O���}()*/
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
�ڲ{�b�n���M�����ǬO per step ��
per step : ��Ū line �A�M�� strtk�A(�M��P�_�O���@��type(�O�X���X)���n��A���L�o�ӨB�J�����n�ޡA�ڲ{�b�����@��type�N�n)�A�M���y�Ъ���m�I���U�ӡA
�M��p��(a).stud����m (b).hole����m 
�M����t�@��ID�A�M��}�@�ӷs���ɮסA��ID�A�n���m�A��type�n�쪺stud�Phole���Ӽ�(�]�N�O�̦h���X�ӾF�~)�Ahole�Mstud����m�g�U��*/


int closeFile()
{
	ldrFile.close();
	return 0;

}

string ldrToBrickNode(string ldrLine, int c, int ldrLineLength)
{
   int k = 0;

   char ldrTxt[50]= "";  /*���o�������� [50] �٬O�̦n�Ϊ�*//* Or Use char ldrTxt[] = "";*/
   char matStr[50] =""; /* matStr is the rotation matrix that includes 9 matrix elements in one line*/
   int mat1, mat2, mat3, mat4, mat5, mat6, mat7, mat8, mat9; /*the 1st to 9th element in the rotation matrix*/
   char temp[120];
   char *legoType = new char[50]; /*.\main.cpp(109) : error C2440: '=' : �L�k�� 'char *' �ഫ�� 'char [50]'*/
   
   /* int ldrLineLength = ldrLine.length(); */
   strncpy(ldrTxt, ldrLine.c_str(), ldrLineLength);   /*strcpy(ldrTxt, ldrLine.c_str()); */
   /*right now, ���W���ˬd!*/


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
	       legoType = setBrickType(tok, matStr); /*.\main.cpp(109) : error C2440: '=' : �L�k�� 'char *' �ഫ�� 'char [50]'*/
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