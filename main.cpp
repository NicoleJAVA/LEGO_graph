#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
#include "brick.h"
#include "brickType.h"
int bnum = 2500;
using namespace std;
string ldrToBrickNode(string ldrLine, int c, int ldrLineLength);
int closeFile();
char filename[] = "mini_lego_for_graph_4"; /*filename must be array*//*dolphin_ldraw_0922*//*mini_lego_set_for_building_dependency_graph*///"mini_lego_for_graph_2"*/
std::fstream ldrFile;
std::fstream logFile;
char brickNodeTxt[100];
int find_dependency( int bricksIndex1, int bricksIndex2 );
int output_graph(int ID1, int ID2, int v1, int v2);

//**************************************/

int vvv, www= -20;
char * setBrickType(char * tok, char matrixStr[50], int ID );
struct brick bricks[2500];
/*
alongXpi = "1 0 0 0 -1 0 0 0 -1";
String alongXpiY90 = "0 0 1 0 -1 0 -1 0 0";
*/
/*    std::fstream graphFile; */
int main()
{    
	//**************************************/
	logFile.open("log.txt",std::fstream::trunc | std::fstream::out); /*ref-A*//*graph.txt*/
	logFile.close();
	logFile.open("log.txt",std::fstream::out | std::fstream::app); /*must reopen with the same flag as ref-A*//*graph.txt*/
    /**************************************/
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
先藏起來等一下再解開封印吼，這是幫全部的人都找出 dependency，但是目前都只做兩兩測試
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
先藏起來等一下再解開封印吼
*/    find_dependency(0, 8); //旋轉的 plate 1x4 和 Brick 2x4 

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
   char ldrTxt[50]= "";  /*不得不說有個 [50] 還是最好用的*//* Or Use char ldrTxt[] = "";*/
   char matStr[50] =""; /* matStr is the rotation matrix that includes 9 matrix elements in one line*/
   int mat1, mat2, mat3, mat4, mat5, mat6, mat7, mat8, mat9; /*the 1st to 9th element in the rotation matrix*/
   char temp[120];
   char *legoType = new char[50]; /*.\main.cpp(109) : error C2440: '=' : 無法由 'char *' 轉換為 'char [50]'*/
   char c_char[50];  
   /* int ldrLineLength = ldrLine.length(); */
   strncpy(ldrTxt, ldrLine.c_str(), ldrLineLength);   /*strcpy(ldrTxt, ldrLine.c_str()); */
   /*right now, 馬上先檢查!*/
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
	   legoType = setBrickType(tok, matStr, c ); /*.\main.cpp(109) : error C2440: '=' : 無法由 'char *' 轉換為 'char [50]'*/
	   }
	   // Initialize the friend list of our new-comer brick !
       bricks[c].priorCount = 0;
	   bricks[c].dpdtCount = 0;
	   k++; // k : the k-th token of a line in the .ldr file
   }
   return  string(brickNodeTxt);
}


//**********************************************************/
char * setBrickType(char * tok, char matrixStr[50], int ID ){
/*
不需要考慮 maxStr[2]，只需要檢查 [0]以及[1]就足以應付 “是否旋轉” 的判斷了。
cosine will be determined by the first and 2nd ele of maxtrixStr
而 consine 的值 has 4 possibility 四種可能：
一，maxStr[0] maxStr[1] 分別為 [1][空格]
二，maxStr[0] maxStr[1] 分別為 [-][1]
三，maxStr[0] maxStr[1] 分別為 [0][空格]
四，maxStr[0] maxStr[1] 分別為 [-][0] 
*/  
	int compare;//*int strcmp ( const char * str1, const char * str2 );*/
	int compare2;
	char *brickType = new char[100]; 
    char cosine[]=""; //我 cosine[] 最終的寫法是非常類似 filename[] 的寫法

		//   >>   element 1 will be put into cosine:
	string s = std::string(1, matrixStr[0]); 
	const char *S  =s.c_str();
	strcat(cosine, S); // wrong code: cosine = strcat(cosine, S); 

	//   >>   element 2 will be put into cosine: 
	s = std::string(1, matrixStr[1]); 
	S = s.c_str();
	strcat(cosine, S); // [請永遠記得 strcat有兩大種用法，別搞混] 

	if(  compare=strcmp(tok,"3005.dat") == 0 ){
			brickType = "1x1";
			bricks[ID].holeXNum = 1;
			bricks[ID].holeZNum = 1;
			bricks[ID].stubXNum = 1;
			bricks[ID].stubZNum = 1;
			logFile << "這是 ID 為"<<ID<< " 的 " << brickType<<"\n" << "x 方向上有幾個 hole  is : " << bricks[ID].holeXNum<<"\n";
	}
	else if( compare = strcmp(tok, "3004.dat") == 0){ //*brick 1x2
	    compare2 = strcmp(matrixStr, "1 0 0 0 -1 0 0 0 -1"); 
		if( compare == 0){
			brickType = "1x2";
			bricks[ID].holeXNum = 2;
			bricks[ID].holeZNum = 1;
			bricks[ID].stubXNum = 2;
			bricks[ID].stubZNum = 1;
			logFile << "這是 ID 為"<<ID<< " 的 " << brickType<<"\n" << "x 方向上有幾個 hole  is : " << bricks[ID].holeXNum<<"\n";
			/*有空再來解開封印 : 以下這行 : */
            //setBrickType_1x2( ID );
            return brickType;
		}
		else{
			brickType = "1x2_90"; //* similar to brick 1x2 but is rotated 90 degree
			bricks[ID].holeXNum = 1;
			bricks[ID].holeZNum = 2;
			bricks[ID].stubXNum = 1;
			bricks[ID].stubZNum = 2;

			logFile << "這是 ID 為"<<ID<< " 的 " << brickType<<"\n" << "x 方向上有幾個 hole  is : " << bricks[ID].holeXNum<<"\n";
			return brickType;				
		}

	}            //    END    if( compare == 0)
	else if( compare=strcmp(tok,"3622.dat") == 0 ){
	    brickType = "1x3"; // stday-WARNING! (1,3) is(z,x), NOT (x,z) !!
			bricks[ID].holeXNum = 3;
			bricks[ID].holeZNum = 1;
			bricks[ID].stubXNum = 3;
			bricks[ID].stubZNum = 1;
			logFile << "這是 ID 為"<<ID<< " 的 " << brickType<<"\n" << "x 方向上有幾個 hole  is : " << bricks[ID].holeXNum<<"\n";
	}

	else{
		compare = strcmp(tok, "3001.dat"); //*brick 2x4*/
		if(compare==0){
			//*	stday Warning! 
			//* If MLCad names a brick axb, notice that a is for Z, and b is for X 
	        //之後可解開封印哈哈 setBrickType_2x4();
            brickType = "2x4";
			bricks[ID].holeXNum = 4; //For a brick 2x4: 2 is for Z, and 4 is for X 
			bricks[ID].holeZNum = 2; 
			bricks[ID].stubXNum = 4;
			bricks[ID].stubZNum = 2;
			logFile << "這是 ID 為"<<ID<< " 的 " << brickType<<"\n" << "x 方向上有幾個 hole  is : " << bricks[ID].holeXNum<<"\n";

	        return brickType;
		}
		/********* 以下是嘗試中的程式 *************/
	else if( (compare = strcmp(tok, "3003.dat")) ==0 ){ //*brick 2x2*/
			brickType = "2x2";
			bricks[ID].holeXNum = 2;
			bricks[ID].holeZNum = 2;
			bricks[ID].stubXNum = 2;
			bricks[ID].stubZNum = 2;
			/*有空再來解開封印 : 以下這行 : */
			//setBrickType_2x2( ID );
			logFile << "這是 ID 為"<<ID<< " 的 " << brickType<<"\n" << "x 方向上有幾個 hole  is : " << bricks[ID].holeZNum<<"\n";
	}
	else if( (compare = strcmp(tok, "3710.dat")) ==0 ){ // plate 1x4
		logFile <<"\n"<< matrixStr<<"\n";
		logFile <<"\n來看看matrixStr[0]"<< matrixStr[0]<<"停\n";
		logFile <<"\n來看看matrixStr[1]"<< matrixStr[1]<<"停\n";
		logFile <<"\n來看看matrixStr[2]"<< matrixStr[2]<<"停\n";
		logFile <<"\n來看看matrixStr[3]"<< matrixStr[3]<<"停\n";
		logFile <<"\n來看看matrixStr[4]"<< matrixStr[2]<<"停\n";
		logFile <<"\n來看看matrixStr[5]"<< matrixStr[5]<<"停\n";
		logFile <<"\n來看看cosine[0]"<< cosine[0]<<"停\n";
		logFile <<"\n來看看cosine[1]"<< cosine[1]<<"停\n";
			brickType = "plate1x4";
			//brickType = "plate1x4cY"; // cY is clockwise along Y axis
			bricks[ID].holeXNum = 4;
			bricks[ID].holeZNum = 1;
			bricks[ID].stubXNum = 4;
			bricks[ID].stubZNum = 1;
			bricks[ID].heightY = 8; // height is 1/3 LDU 
			logFile << "這是 ID 為"<<ID<< " 的 " << brickType<<"\n" << "x 方向上有幾個 hole  is : " << bricks[ID].holeZNum<<"\n";
	}
	else{
        brickType = "nxn";
	    return brickType;
	}

	}


    //*Nicole STYLE //*Thanks to what Luchian Grigore answered to how to return char array in c++ 
    return brickType;
    
}


//*************************************************************
int find_dependency( int bricksIndex1, int bricksIndex2 )
//* Brick1 is the BOTTOM brick, Brick2 is the UPPER brick
// This function wants to know whether they connect at Brick1's STUB and Brick2's HOLE. 
{   
/*
logFile<<"\n--------In function find_dependency-------\n"<<"\n ID1 is "<<bricksIndex1<<". ID2 is "<<bricksIndex2<<"\n";
*/
//不允許 [參數一是上層積木. 參數二是下層積木] 的情況發生
//傳參數的時候一定要是 (一樓, 二樓) 才可以傳
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
	//* x1, y1, z1 是第一個積木最左上角的 hole */
	//* x2, y2, z2 是第二個積木最左上角的 stub */
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
// leftmost 的 stub 的圓心的 x 座標為 Center stub 的x座標  -10 K  + 10 #
// Therfore, Brick (1) is : 
	y1 = bricks[bricksIndex1].y - 12;
    K1 = bricks[bricksIndex1].stubXNum;
	K2 = bricks[bricksIndex1].stubZNum;
    x1 = centerX1 - (10*K1) + 10;    // X1 = X - 10K + 10 背起來吧!
	z1 = centerZ1 + (10*K2) - 10;    // Z1 = Z - 10K + 10 背起來吧!
    
// And Brick (2) is : 
	y2 = bricks[bricksIndex2].y + 12; 
	K3 = bricks[bricksIndex2].stubXNum;
	K4 = bricks[bricksIndex2].stubZNum;
    x2 = centerX2 - (10*K3) + 10 ;   // X2 = X - 10K + 10 背起來吧!
	z2 = centerZ2 + (10*K4) - 10 ;   // Z2 = Z - 10K + 10 背起來吧!
    //  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - 


	logFile << "\n下層積木左上角的x是 : " << x1;
	logFile << "\n上層積木x是 : " << centerX2;
	logFile << "\n上層積木左上角的x是 : " << x2;
		logFile << "\n下層積木左上角的z是 : " << z1;
	logFile << "\n上層積木z是 : " << centerZ2;
	logFile << "\n上層積木左上角的z是 : " << z2;


// [Outer Loop] Loop-1 : The bottom Brick1, traverse X-axis 
// [Outer Loop] Loop-2 : The bottom Brick1, traverse Z-axis 
// [Inner Loop] Loop-3 : The upper Brick2, traverse X-axis 
// [Inner Loop] Loop-4 : The upper Brick2, traverse Z-axis 
	for( i=0; i<K1; i++){    
        for( j=0; j<K2; j++){    
			for( a=0; a<K3; a++ ){
				for( b=0; b<K4; b++){
				    
//等一下刪掉
                        logFile << "\nBOTTOM brick: " << "\ni is " << i << "\nj is " << j;
						logFile << "\nUPPER brick: " << "\na is " << a << "\nb is " << b;
//等一下刪掉

					diffx = (x2+(a*20)) - (x1+(i*20));
					diffz = (z2-(b*20)) - (z1-(j*20));
					diffy = y1 - y2;
						logFile << "\nbrick1 x 是走到了 " << x1+(i*20);
					    logFile << "\nbrick2 x 是走到了 " << x2+(a*20);

					if( diffx==0 && diffz ==0){
						flag = 1;
						// update friend list of both brick1 and brick2
						bricks[bricksIndex1].prior_to[v1] = bricks[bricksIndex2].ID;
						bricks[bricksIndex2].dpdt_on[v2] = bricks[bricksIndex1].ID;
						bricks[bricksIndex1].priorCount ++;
						bricks[bricksIndex1].dpdtCount ++;

						
                        logFile << "\n\nBOTTOM brick: " << "\ni is " << i << "\nj is " << j;
						logFile << "\nUPPER brick: " << "\na is " << a << "\nb is " << b;
						logFile << "\nbrick1 x 是走到了 " << x1+(i*20);
					    logFile << "\nbrick2 x 是走到了 " << x2+(a*20);
						logFile << "\nbrick1 z 是走到了 " << z1-(j*20);
					    logFile << "\nbrick2 z 是走到了 " << z2-(b*20);
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