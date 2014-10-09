#ifndef BRICK
#define BRICK "brick.h"
#include BRICK 
#endif


#ifndef LOGHEADER
#define LOGHEADER "logHeader.h"
#include LOGHEADER 
#endif



#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
#include "brickType.h"
using namespace std;   // �O�ѤF using ���A���M de ���� bug 
// - - - - - - - - - - - - - - - - - - - - - - - -
string ldrToBrickNode(string ldrLine, int c, int ldrLineLength);
int closeFile();
char filename[] = "mini_lego_for_graph_4"; /*filename must be array*//*dolphin_ldraw_0922*//*mini_lego_set_for_building_dependency_graph*///"mini_lego_for_graph_2"*/
std::fstream ldrFile;
std::fstream logFile;
char brickNodeTxt[100];
int find_dependency( int bricksIndex1, int bricksIndex2 );
int output_graph(int ID1, int ID2, int v1, int v2);
// �o��Q�ڮ��� brickType.h �̭��F : bool isRotate( char matrixStr[50] );
// �o��Q�ڮ��� brick.h �̭��F : struct brick bricks[2500];
//    alongXpi = "1 0 0 0 -1 0 0 0 -1";
//    String alongXpiY90 = "0 0 1 0 -1 0 -1 0 0";


int main()
{    
	openLogFile2();
	//**************************************
	logFile.open("log.txt",std::fstream::trunc | std::fstream::out); /*ref-A*//*graph.txt*/
	logFile.close();
	logFile.open("log.txt",std::fstream::out | std::fstream::app); /*must reopen with the same flag as ref-A*//*graph.txt*/
    //**************************************

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
				c++;
				}
				
			}
		}   /*   END if(ldrFile.is_open())  END */
		
       
	    closeFile();
	}   /*   END if(graphFile.is_open())   END   */



	// *  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - 
    // *  
    // * 
	// *             Find the Dependency       
	// *
	// * 
	// *  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  
/*
���ð_�ӵ��@�U�A�Ѷ}�ʦL�q�A�o�O���������H����X dependency�A���O�ثe���u��������
int i,j; // i is BOTTOM brick; j is UPPER brick
	for( i=0; i<c; i++ ){
		for( j=0; j<c; j++ ){

			if( bricks[i].y != bricks[j].y){
				if( (bricks[i].y-12) < (bricks[j].y+12) ){
	                //Cannot Compare because i is ABOVE j
				}
				else{
				    find_dependency(i, j);
				}

			}    //   END    if( bricks[i].y != bricks[j].y) 
		}        //   END    for( j=0 )
	}            //   END    for( i=0 )
���ð_�ӵ��@�U�A�Ѷ}�ʦL�q
*/    find_dependency(0, 8); //���઺ plate 1x4 �M Brick 2x4 

	logFile.close();
	return 0;
}



int closeFile()
{
	ldrFile.close();
	return 0;

}

string ldrToBrickNode(string ldrLine, int c, int ldrLineLength)
/* c will be the ID of the brick because this is the c-th line of .ldr file*/
{
   int k = 0; /* k : the k-th token of a line in the .ldr file*/
   char ldrTxt[50]= "";  /*���o�������� [50] �٬O�̦n�Ϊ�*//* Or Use char ldrTxt[] = "";*/
   char matStr[50] =""; /* matStr is the rotation matrix that includes 9 matrix elements in one line*/
   int mat1, mat2, mat3, mat4, mat5, mat6, mat7, mat8, mat9; /*the 1st to 9th element in the rotation matrix*/
   char temp[120];
   char *legoType = new char[50]; /*.\main.cpp(109) : error C2440: '=' : �L�k�� 'char *' �ഫ�� 'char [50]'*/
   char c_char[50];  
   /* int ldrLineLength = ldrLine.length(); */
   strncpy(ldrTxt, ldrLine.c_str(), ldrLineLength);   /*strcpy(ldrTxt, ldrLine.c_str()); */
   /*right now, ���W���ˬd!*/
   char * tok;
   char tokTemp[120];
  /*tokenize out the first thing of the first line*/
   tok = strtok(ldrTxt," ");
   while(tok!=NULL){
	   strcpy(brickNodeTxt, tok);
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
	   legoType = setBrickType(tok, matStr, c ); /*.\main.cpp(109) : error C2440: '=' : �L�k�� 'char *' �ഫ�� 'char [50]'*/
	   }
	   // Initialize the friend list of our new-comer brick !
       bricks[c].priorCount = 0;
	   bricks[c].dpdtCount = 0;
	   k++; // k : the k-th token of a line in the .ldr file
   }
   return  string(brickNodeTxt);
}


//**********************************************************/



//*************************************************************
int find_dependency( int bricksIndex1, int bricksIndex2 )
//* Brick1 is the BOTTOM brick, Brick2 is the UPPER brick
// This function wants to know whether they connect at Brick1's STUB and Brick2's HOLE. 
{   
/*
logFile<<"\n--------In function find_dependency-------\n"<<"\n ID1 is "<<bricksIndex1<<". ID2 is "<<bricksIndex2<<"\n";
*/
//�����\ [�ѼƤ@�O�W�h�n��. �ѼƤG�O�U�h�n��] �����p�o��
//�ǰѼƪ��ɭԤ@�w�n�O (�@��, �G��) �~�i�H��
    if(bricks[bricksIndex1].y ==  bricks[bricksIndex2].y ){ 
	// if the bricks are at the same Y coordinte (same floor) , 
	//then find_dependency() cannot accept same-Y bricks to compare them
            logFile << "\nlogic error ! \nThe first argument must be BOTTOM brick n' vice versa.";
	    	logFile << "\nBut now the two bricks are on the same Y.";
			logFile << "\nThe STUB of argument 1 is at Y = "<<bricks[bricksIndex1].y <<"\nThe HOLE of argument 2 is at Y = "<<bricks[bricksIndex2].y ;
	    	logFile << "\nTerminate function  find_dependency() !\n";
			return -1;
	}
	else if(bricks[bricksIndex1].y - 12 < bricks[bricksIndex2].y + 12){

            logFile << "\nlogic error ! \nThe first argument must be BOTTOM brick n' vice versa.";
	    	logFile << "\nBut now brick 1 is above brick 2 .";
			logFile << "\nThe STUB of argument 1 is at (Y-12) = "<<bricks[bricksIndex1].y - 12<<"\nThe HOLE of argument 2 is at (Y+12) = "<<bricks[bricksIndex2].y + 12;
	    	logFile << "\nTerminate function  find_dependency() !\n";
			return -1;
	}
    

	int v1 = bricks[bricksIndex1].priorCount;
	int v2 = bricks[bricksIndex1].dpdtCount;
	//* x1, y1, z1 �O�Ĥ@�ӿn��̥��W���� hole */
	//* x2, y2, z2 �O�ĤG�ӿn��̥��W���� stub */
	int x1, y1, z1, centerX1, centerY1, centerZ1;
	int x2, y2, z2, centerX2, centerY2, centerZ2;
	int flag = -100;
	int i, j, a, b, K1, K2, K3, K4;
	int diffx, diffy, diffz;
	centerX1 = bricks[bricksIndex1].x;
	centerZ1 = bricks[bricksIndex1].z;
	centerX2 = bricks[bricksIndex2].x;
	centerZ2 = bricks[bricksIndex2].z;

//*  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - 

// For a K-stub-on-x  (or for a K-stub-on-z), let's say:
// leftmost �� stub ����ߪ� x �y�Ь� Center stub ��x�y��  -10 K  + 10 #
// Therfore, Brick (1) is : 
	y1 = bricks[bricksIndex1].y - 12;
    K1 = bricks[bricksIndex1].stubXNum;
	K2 = bricks[bricksIndex1].stubZNum;
    x1 = centerX1 - (10*K1) + 10;    // X1 = X - 10K + 10 �I�_�ӧa!
	z1 = centerZ1 + (10*K2) - 10;    // Z1 = Z - 10K + 10 �I�_�ӧa!
    
// And Brick (2) is : 
	y2 = bricks[bricksIndex2].y + 12; 
	K3 = bricks[bricksIndex2].stubXNum;
	K4 = bricks[bricksIndex2].stubZNum;
    x2 = centerX2 - (10*K3) + 10 ;   // X2 = X - 10K + 10 �I�_�ӧa!
	z2 = centerZ2 + (10*K4) - 10 ;   // Z2 = Z - 10K + 10 �I�_�ӧa!
    //  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - 


	logFile << "\n�U�h�n�쥪�W����x�O : " << x1;
	logFile << "\n�W�h�n��x�O : " << centerX2;
	logFile << "\n�W�h�n�쥪�W����x�O : " << x2;
		logFile << "\n�U�h�n�쥪�W����z�O : " << z1;
	logFile << "\n�W�h�n��z�O : " << centerZ2;
	logFile << "\n�W�h�n�쥪�W����z�O : " << z2;


// [Outer Loop] Loop-1 : The bottom Brick1, traverse X-axis 
// [Outer Loop] Loop-2 : The bottom Brick1, traverse Z-axis 
// [Inner Loop] Loop-3 : The upper Brick2, traverse X-axis 
// [Inner Loop] Loop-4 : The upper Brick2, traverse Z-axis 
	for( i=0; i<K1; i++){    
        for( j=0; j<K2; j++){    
			for( a=0; a<K3; a++ ){
				for( b=0; b<K4; b++){
				    
//���@�U�R��
                        logFile << "\nBOTTOM brick: " << "\ni is " << i << "\nj is " << j;
						logFile << "\nUPPER brick: " << "\na is " << a << "\nb is " << b;
//���@�U�R��

					diffx = (x2+(a*20)) - (x1+(i*20));
					diffz = (z2-(b*20)) - (z1-(j*20));
					diffy = y1 - y2;
						logFile << "\nbrick1 x �O����F " << x1+(i*20);
					    logFile << "\nbrick2 x �O����F " << x2+(a*20);

					if( diffx==0 && diffz ==0){
						flag = 1;
						// update friend list of both brick1 and brick2
						bricks[bricksIndex1].prior_to[v1] = bricks[bricksIndex2].ID;
						bricks[bricksIndex2].dpdt_on[v2] = bricks[bricksIndex1].ID;
						bricks[bricksIndex1].priorCount ++;
						bricks[bricksIndex1].dpdtCount ++;

						
                        logFile << "\n\nBOTTOM brick: " << "\ni is " << i << "\nj is " << j;
						logFile << "\nUPPER brick: " << "\na is " << a << "\nb is " << b;
						logFile << "\nbrick1 x �O����F " << x1+(i*20);
					    logFile << "\nbrick2 x �O����F " << x2+(a*20);
						logFile << "\nbrick1 z �O����F " << z1-(j*20);
					    logFile << "\nbrick2 z �O����F " << z2-(b*20);
						logFile << "\niffz is " << diffz;
                        output_graph( bricksIndex1, bricksIndex2, v1, v2 );
                        
					    return flag;
					}
					diffx = -1;
					diffz = -1;
				}    //*    END    for( b=0; b<1; b++)   
			}        //*    END    for( a=0; a<2; a++)   
		}            //*    END    for( j=0; j<2; j++)  
	}                //*    END    for( i=0; i<4; i++)   

    return flag;   
}

int output_graph( int ID1, int ID2, int v1, int v2)

{
	logFile << "\nFound brick "<<ID2<<" is depdent on brick "<<ID1<<"\n";
    /*
	logFile << bricks[ID1].prior_to[v1];
	logFile <<"\n";
	logFile << bricks[ID2].dpdt_on[v2];
	logFile <<"\n";
	*/
    return 0;
}





