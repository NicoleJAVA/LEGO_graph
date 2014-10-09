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


//                    *-  -  -  -  -  -  -  -  -  -  -  -  -  -  - *
//                    *                                            *
//                    *                                            *
//                    *             Find the Dependency            *
//                    *                                            *
//                    *                                            *
//                    *-  -  -  -  -  -  -  -  -  -  -  -  -  -  - *

//���ð_�ӵ��@�U�A�Ѷ}�ʦL�q�A�o�O���������H����X dependency�A���O�ثe���u��������
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
//���ð_�ӵ��@�U�A�Ѷ}�ʦL�q

	logFile.close();
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
   //�ڦb�٨S�� setBrickType �� return �ȧאּ const char * �e���g�k�O
   //char *legoType = new char[50]; //error C2440: '=' : �L�k�� 'char *' �ഫ�� 'char [50]' 
   //���ڲ{�b�אּ
   //char *legoType;

   char c_char[50];  
   strncpy(ldrTxt, ldrLine.c_str(), ldrLineLength);   // strcpy(ldrTxt, ldrLine.c_str()); 
   char * tok;

//     S T A R T   >>   

   tok = strtok(ldrTxt," "); //tokenize out the first thing of the first line
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
		   logFile << "\n bricks[c].y is : " << bricks[c].y;
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
	   setBrickType(tok, matStr, c ); // error C2440: '=' : �L�k�� 'char *' �ഫ�� 'char [50]'

	   }
	   
       bricks[c].priorCount = 0; // Initialize the friend list of our new-comer brick !
	   bricks[c].dpdtCount = 0;
	   k++;                      // k : the k-th token of a line in the .ldr file
   }
   logFile << "\n �a �o�O bricks[c].btype �� : " << bricks[c].btype << "�n�����ơC\n" ;
   return  string(brickNodeTxt);
}



int find_dependency( int bricksIndex1, int bricksIndex2 )
{   
    //    Brick1 is the BOTTOM brick, Brick2 is the UPPER brick
    //    This function wants to know whether they connect at Brick1's stud and Brick2's HOLE. 
    //    [�o�O���~: �ѼƤ@�O�W�h�n��. �ѼƤG�O�U�h�n��] 
    //    �ǰѼƪ��ɭԤ@�w�n�O (�@��, �G��) �~�i�H��
	//    x1, y1_stud, z1 �O�Ĥ@�ӿn��̥��W���� stud 
	//    x2, y2_hole, z2 �O�ĤG�ӿn��̥��W���� hole 

    int brickHeight1 = bricks[bricksIndex1].heightY;
	int brickHeight2 = bricks[bricksIndex2].heightY;
	int x1, y1_stud, z1, centerX1, topSurfaceY1, centerZ1; // �u��Y�O���Y�������ӹ���n��A�ҥH�����W�s centerY1 �P centerY2, �ӬO�s topSurfaceY1 �P topSurfaceY2
	int x2, y2_hole, z2, centerX2, topSurfaceY2, centerZ2;
	centerX1 = bricks[bricksIndex1].x;
	centerZ1 = bricks[bricksIndex1].z;
	centerX2 = bricks[bricksIndex2].x;
	centerZ2 = bricks[bricksIndex2].z;
	topSurfaceY1 = bricks[bricksIndex1].y;
	topSurfaceY2 = bricks[bricksIndex2].y;
	y1_stud = topSurfaceY1; 
	y2_hole = topSurfaceY2 + brickHeight2; 
	//�`�`�|�Ψ쪺 log 
    //logFile << "\n\n\n\n\n --------In function find_dependency() -------\n" ;
	//logFile << "\n ID1 is " << bricksIndex1<<".\n ID2 is "<<bricksIndex2<<".\n";
	//�`�`�|�Ψ쪺 log 
	//logFile << "\n topSurfaceY2 is : " << topSurfaceY2 ;
	//logFile << "\n y1_stud = bricks[bricksIndex2].y is : " << bricks[bricksIndex2].y;
	//logFile << "\n y2_hole = topSurfaceY2 + brickHeight2 = " << y2_hole << "\n";

    if( (topSurfaceY1-brickHeight1) == (topSurfaceY2-brickHeight2) ){ // If Sit On Same Y (Sit On Same Floor), ERROR.
            logFile << "\n Logic Error! \nThe first argument of find_dependency() must be BOTTOM brick.";
	    	logFile << "\n But now the two bricks are Sitting On the Same Floor.";
			logFile << "\n The bottom of argument 1 is at Y = topSurfaceY1-brickHeight1 = "<< topSurfaceY1-brickHeight1;
			logFile << "\n The bottom of argument 2 is at Y = topSurfaceY2-brickHeight2 = "<< topSurfaceY2-brickHeight2 ;
	    	logFile << "\n Terminate function  find_dependency() !\n";
			return -1;
	}
	else if( y1_stud < y2_hole ){   // If stud(y1) Is ABOVE Hole(y2), ERROR.

            logFile << "\n Logic Error! \nThe first argument of find_dependency() must be BOTTOM brick.";
	    	logFile << "\n But now brick 1 ["<< bricksIndex1 << "] is above brick 2 [" << bricksIndex2 << "] ...";
			// ���e�� logFile << "\nThe stud of argument 1 is at (Y-12) = "<<bricks[bricksIndex1].y - 12<<"\nThe HOLE of argument 2 is at (Y+12) = "<<bricks[bricksIndex2].y + 12;
			logFile << "\n topSurfaceY1 : " << topSurfaceY1; 
			logFile << "\n brickHeight1 : " << brickHeight1;
			logFile << "\n topSurfaceY2 : " << topSurfaceY2; 
			logFile << "\n brickHeight2 : " << brickHeight2;
			logFile << "\n The stud of argument 1 is at y1_stud = " << y1_stud;
			logFile << "\n The HOLE of argument 2 is at y2_hole = " << y2_hole; 
			logFile << "\n Or equivalent as topSurfaceY2 + brickHeight2 = "<< topSurfaceY2 + brickHeight2;
	    	logFile << "\nTerminate function  find_dependency() !\n";
			return -1;
	}    // - - - - - E N D - - - - - ERROR (y1_stud ABOVE y2_hole) - - - - - - - - - - 
 
	int v1 = bricks[bricksIndex1].priorCount; // v1 is N of friends of Bottom Brick 1 
	int v2 = bricks[bricksIndex1].dpdtCount;  // v2 is N of friends of Upper_ Brick 2
	int flag = -100;
	int i, j, a, b, K1, K2, K3, K4;
	int diffx, diffy, diffz;

    //- - - -  For a K-stud-on-x  (or for a K-stud-on-z), let's say:
    //- - - -  leftmost �� stud ����ߪ� x �y�Ь� Center stud ��x�y��  -10 K  + 10 #
    //- - - -  Therfore, Brick (1) is : 
    K1 = bricks[bricksIndex1].studXNum;
	K2 = bricks[bricksIndex1].studZNum;
    x1 = centerX1 - (10*K1) + 10;    // X1 = X - 10K + 10 �I�_�ӧa!
	z1 = centerZ1 + (10*K2) - 10;    // Z1 = Z - 10K + 10 �I�_�ӧa!
    
    //- - - -  And Brick (2) is : 
	K3 = bricks[bricksIndex2].studXNum;
	K4 = bricks[bricksIndex2].studZNum;
    x2 = centerX2 - (10*K3) + 10 ;   // X2 = X - 10K + 10 �I�_�ӧa!
	z2 = centerZ2 + (10*K4) - 10 ;   // Z2 = Z - 10K + 10 �I�_�ӧa!


    //�٬O���`�ݭn�ˬd���ҥH�ڥ����R���o�X�� log ���{��
	/*
	logFile << "\n �U�h�n�줤���I x �O : " << centerX1 << " . �U�h�n�줤���I z �O : " << centerZ1 ;
	logFile << "\n �U�h�n�쥪�W�� stud ��x�O : " << x1;
	logFile << "\n �U�h�n�쥪�W�� stud ��z�O : " << z1 << "\n";
	*/
    //�٬O���`�ݭn�ˬd���ҥH�ڥ����R���o�X�� log ���{��
	/*
	logFile << "\n �W�h�n�줤���I x �O : " << centerX2 << " . �W�h�n�줤���I z �O : " << centerZ2;
	logFile << "\n �W�h�n�쥪�W�� hole ��x�O : " << x2;
	logFile << "\n �W�h�n�쥪�W�� hole ��z�O : " << z2 << "\n";
	*/


// [Outer Loop] Loop-1 : The bottom Brick1, traverse X-axis 
// [Outer Loop] Loop-2 : The bottom Brick1, traverse Z-axis 
// [Inner Loop] Loop-3 : The upper Brick2, traverse X-axis 
// [Inner Loop] Loop-4 : The upper Brick2, traverse Z-axis 
	for( i=0; i<K1; i++){                //    Brick1, traverse X
        for( j=0; j<K2; j++){            //    Brick1, traverse Z
			for( a=0; a<K3; a++ ){       //    Brick2, traverse X
				for( b=0; b<K4; b++){    //    Brick2, traverse Z
					diffx = (x2+(a*20)) - (x1+(i*20));
					diffz = (z2-(b*20)) - (z1-(j*20));
					diffy = y1_stud - y2_hole;

					//�٬O���`�ݭn�ˬd���ҥH�ڥ����R���o�X�� log ���{��
					//logFile << "\n BOTTOM brick: " << "\n i is " << i << "\n j is " << j;
					//logFile << "\n UPPER brick: " << "\n a is " << a << "\n b is " << b;
					//logFile << "\n Brick1 x �O����F " << x1+(i*20);
					//logFile << "\n Brick2 x �O����F " << x2+(a*20) << "\n";

					if( diffx==0 && diffz ==0){
						flag = 1;
						// update friend list of both brick1 and brick2
						bricks[bricksIndex1].prior_to[v1] = bricks[bricksIndex2].ID;
						bricks[bricksIndex2].dpdt_on[v2] = bricks[bricksIndex1].ID;
						bricks[bricksIndex1].priorCount ++;
						bricks[bricksIndex1].dpdtCount ++;						
                        logFile << "\n BOTTOM brick: " << "\n i is " << i << "\n j is " << j << "\n";
						logFile << "\n UPPER brick: " << "\n a is " << a << "\n b is " << b << "\n";
						logFile << "\n Brick1 x �O����F " << x1+(i*20);
					    logFile << "\n Brick2 x �O����F " << x2+(a*20);
						logFile << "\n Brick1 z �O����F " << z1-(j*20);
					    logFile << "\n Brick2 z �O����F " << z2-(b*20);
						logFile << "\n diffz is " << diffz << "\n";
                        output_graph( bricksIndex1, bricksIndex2, v1, v2 );  
					    return flag;
					}
					diffx = -1;
					diffz = -1;
				}    //    END    for( b=0; b<1; b++)   
			}        //    END    for( a=0; a<2; a++)   
		}            //    END    for( j=0; j<2; j++)  
	}                //    END    for( i=0; i<4; i++)   
    return flag;   
}

int output_graph( int ID1, int ID2, int v1, int v2)
{
	// �o��ڤ@�w�n�G�N�L�X brickType �A�n���M�p�G�u�� ID �A�ڦb�ˬd���ɭԦp�G�ʤߴN�|���O�ɶ�debug
	logFile << "\n Found brick "      << ID2 << " " << bricks[ID2].btype; // I purposedly printf the btype, for easier debugging
	logFile << " is depdent on brick "<< ID1 << " " << bricks[ID1].btype << " \n\n";
    /*
	logFile << bricks[ID1].prior_to[v1];
	logFile <<"\n";
	logFile << bricks[ID2].dpdt_on[v2];
	logFile <<"\n";
	*/
    return 0;
}


int closeFile()
{
	ldrFile.close();
	return 0;

}