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
using namespace std;   // �O�ѤF using ���A���M de ���� bug 

void this_is_template();
int setBrickType_1x2 ( int ID );
int setBrickType_2x4 ( int ID );
int setBrickType_2x2 ( int ID );
int setPlateType_1x4_clockY ( int ID ); //rotate Y clockwise ���ɰw
char * setBrickType(char * tok, char matrixStr[50], int ID );
bool isRotate( char matrixStr[50] );


//    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
//    *
//    *                         setBrickType( )                           -
//    *
//    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

char * setBrickType(char * tok, char matrixStr[50], int ID )
{ 

	int compare;//*int strcmp ( const char * str1, const char * str2 );*/
	char *brickType = new char[100];
	bool rotateBool = isRotate(matrixStr);



    //    S T A R T  ::   brick 1x1    _______________________________________________

	if(  compare=strcmp(tok,"3005.dat") == 0 ){ // brick 1x1 
		if( rotateBool==0 ){
			brickType = "1x1";
			bricks[ID].holeXNum = 1;
			bricks[ID].holeZNum = 1;
			bricks[ID].stubXNum = 1;
			bricks[ID].stubZNum = 1;
			bricks[ID].heightY = 24; 
        }    //    END if( isNOTRotate ) 
		else if( rotateBool==1 ){
			brickType = "1x1";
			bricks[ID].holeXNum = 1;
			bricks[ID].holeZNum = 1;
			bricks[ID].stubXNum = 1;
			bricks[ID].stubZNum = 1;
			bricks[ID].heightY = 24; 
		}    //    END if ( isRotate) 
		else{
		    logFile2 << "\nERROR! isRotate() �S���^�ǥ��T���ȵ� setBrickType() !\n"; 
			return "ERROR_TYPE";
		}    //    END if( error_type ) 
			logFile2 << "�o�O ID ��"<<ID<< " �� " << brickType<<"\n" << "x ��V�W���X�� hole  is : " << bricks[ID].holeXNum<<"\n";

	}        //    E N D   <<�@ if( brick 1x1 )    :: _______________________________________________


	else if( compare = strcmp(tok, "3004.dat") == 0){ // brick 1x2
		if( rotateBool==0 ){
			brickType = "1x2";
			bricks[ID].holeXNum = 2;
			bricks[ID].holeZNum = 1;
			bricks[ID].stubXNum = 2;
			bricks[ID].stubZNum = 1;
			bricks[ID].heightY = 24; 
        }    //    END if( isNOTRotate ) 
		else if( rotateBool==1 ){
			brickType = "1x2_90";
			bricks[ID].holeXNum = 1;
			bricks[ID].holeZNum = 2;
			bricks[ID].stubXNum = 1;
			bricks[ID].stubZNum = 2;
			bricks[ID].heightY = 24; 
		}    //    END if ( isRotate) 
		else{
		    logFile2 << "\nERROR! isRotate() �S���^�ǥ��T���ȵ� setBrickType() !\n"; 
			return "ERROR_TYPE";
		}    //    END if( error_type ) 
			logFile2 << "�o�O ID ��"<<ID<< " �� " << brickType<<"\n" << "x ��V�W���X�� hole  is : " << bricks[ID].holeXNum<<"\n";
			return brickType;	

	}        //    E N D   <<�@ if( brick 1x2 ) _______________________________________________



	else if( compare=strcmp(tok,"3622.dat") == 0 ){ // brick 1x3 
		if( rotateBool==0 ){
			brickType = "brick1x3"; // stday-WARNING! (1,3) is(z,x), NOT (x,z) !!
			bricks[ID].holeXNum = 3;
			bricks[ID].holeZNum = 1;
			bricks[ID].stubXNum = 3;
			bricks[ID].stubZNum = 1;
			bricks[ID].heightY = 24; 
        }    //    END if( isNOTRotate ) 
		else if( rotateBool==1 ){
			brickType = "brick1x2_90";
			bricks[ID].holeXNum = 1;
			bricks[ID].holeZNum = 3;
			bricks[ID].stubXNum = 1;
			bricks[ID].stubZNum = 3;
			bricks[ID].heightY = 24; 
		}    //    END if ( isRotate) 
		else{
		    logFile2 << "\nERROR! isRotate() �S���^�ǥ��T���ȵ� setBrickType() !\n"; 
			return "ERROR_TYPE";
		}    //    END if( error_type ) 
			logFile2 << "�o�O ID ��"<<ID<< " �� " << brickType<<"\n" << "x ��V�W���X�� hole  is : " << bricks[ID].holeXNum<<"\n";
			return brickType;	

	}        //    E N D   <<�@ if( brick 1x3 ) _______________________________________________



	else if( compare=strcmp(tok,"3001.dat") == 0 ){    // brick 2x4 (3001.dat)
		if( rotateBool==0 ){
			brickType = "brick1x3"; // stday-WARNING! (1,3) is(z,x), NOT (x,z) !!
			bricks[ID].holeXNum = 4;
			bricks[ID].holeZNum = 2;
			bricks[ID].stubXNum = 4;
			bricks[ID].stubZNum = 2;
			bricks[ID].heightY = 24; 
        }    //    END if( isNOTRotate ) 
		else if( rotateBool==1 ){
			brickType = "brick1x3_90";
			bricks[ID].holeXNum = 2;
			bricks[ID].holeZNum = 4;
			bricks[ID].stubXNum = 2;
			bricks[ID].stubZNum = 4;
			bricks[ID].heightY = 24; 
		}    //    END if ( isRotate) 
		else{
		    logFile2 << "\nERROR! isRotate() �S���^�ǥ��T���ȵ� setBrickType() !\n"; 
			return "ERROR_TYPE";
		}    //    END if( error_type ) 
			logFile2 << "�o�O ID ��"<<ID<< " �� " << brickType<<"\n" << "x ��V�W���X�� hole  is : " << bricks[ID].holeXNum<<"\n";
			return brickType;	

	}         //    E N D   <<�@ if( brick 2x4 ) _______________________________________________



	else if( (compare = strcmp(tok, "3003.dat")) ==0 ){ // brick 2x2
	//���ŦA�ӸѶ}�ʦL : �H�U�o�� : //setBrickType_2x2( ID );
		if( rotateBool==0 ){
			brickType = "brick2x2";
			bricks[ID].holeXNum = 2;
			bricks[ID].holeZNum = 2;
			bricks[ID].stubXNum = 2;
			bricks[ID].stubZNum = 2;
			bricks[ID].heightY = 24; 
        }    //    END if( isNOTRotate ) 
		else if( rotateBool==1 ){
			brickType = "brick2x2";
			bricks[ID].holeXNum = 2;
			bricks[ID].holeZNum = 2;
			bricks[ID].stubXNum = 2;
			bricks[ID].stubZNum = 2;
			bricks[ID].heightY = 24; 
		}    //    END if ( isRotate) 
		else{
		    logFile2 << "\nERROR! isRotate() �S���^�ǥ��T���ȵ� setBrickType() !\n"; 
			return "ERROR_TYPE";
		}    //    END if( error_type ) 
	    logFile2 << "�o�O ID ��"<<ID<< " �� " << brickType<<"\n" << "x ��V�W���X�� hole  is : " << bricks[ID].holeXNum<<"\n";
		return brickType;

	}        //    E N D   <<�@ if( brick 2x2 ) _______________________________________________


	else if( (compare = strcmp(tok, "3710.dat")) ==0 ){ // plate 1x4
		if( rotateBool==0 ){
			brickType = "plate1x4"; // "brickType" should follow what MLCAD name the brick 
			bricks[ID].holeXNum = 4;
			bricks[ID].holeZNum = 1;
			bricks[ID].stubXNum = 4;
			bricks[ID].stubZNum = 1;
            bricks[ID].heightY = 8;  
        }    //    END if( isNOTRotate ) 
		else if( rotateBool==1 ){
			brickType = "plate1x4_90"; // is rotated clockwise along Y-axis by 90 degrees 
			bricks[ID].holeXNum = 1; 
			bricks[ID].holeZNum = 4;
			bricks[ID].stubXNum = 1;
			bricks[ID].stubZNum = 4;
            bricks[ID].heightY = 8;  
		}    //    END if ( isRotate) 
		else{
		    logFile2 << "\nERROR! isRotate() �S���^�ǥ��T���ȵ� setBrickType() !\n"; 
			return "ERROR_TYPE";
		}
	    logFile2 << "�o�O ID ��"<<ID<< " �� " << brickType<<"\n" << "x ��V�W���X�� hole  is : " << bricks[ID].holeXNum<<"\n";
		return brickType;	

	}        //    E N D   <<�@ if( plate 1x4 ) _______________________________________________



	else{
        brickType = "nxn";
	    return brickType;
	}        //    E N D   <<�@ if( brick nxn ) _______________________________________________
    //*Nicole STYLE //*Thanks to what Luchian Grigore answered to how to return char array in c++ 
	logFile2 <<"\n- - - - -      E N D   <<   setBrickType()     - - - - - \n\n" ;
    return brickType;
}

void this_is_template(){

// �H�U�O�˪�
/*
		if( rotateBool==0 ){
			brickType = "�Xx�X"; // stday-WARNING! (1,3) is(z,x), NOT (x,z) !!
			bricks[ID].holeXNum = �հհ�;
			bricks[ID].holeZNum = �հհ�;
			bricks[ID].stubXNum = �հհ�;
			bricks[ID].stubZNum = �հհ�;
			bricks[ID].heightY = �ԩԩԩԩ�; 
        }    //    END if( isNOTRotate ) 
		else if( rotateBool==1 ){
		    brickType = "�Xx�X_90"; // stday-WARNING! (1,3) is(z,x), NOT (x,z) !!
			bricks[ID].holeXNum = �հհ�;
			bricks[ID].holeZNum = �հհ�;
			bricks[ID].stubXNum = �հհ�;
			bricks[ID].stubZNum = �հհ�;
			bricks[ID].heightY = �ԩԩԩԩ�; 
		}    //    END if ( isRotate) 
		else{
		    logFile2 << "\nERROR! isRotate() �S���^�ǥ��T���ȵ� setBrickType() !\n"; 
			return "ERROR_TYPE";
		}    //    END if( error_type ) 
			logFile2 << "�o�O ID ��"<<ID<< " �� " << brickType<<"\n" << "x ��V�W���X�� hole  is : " << bricks[ID].holeXNum<<"\n";
			return brickType;	

*/

// �H�W�O�˪�
}


//    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
//    *
//    *                           isRotate( )                             -
//    *
//    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 


bool isRotate( char matrixStr[50])
{
/*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    ���ݭn�Ҽ{ maxStr[2]�A�u�ݭn�ˬd [0]�H��[1]�N���H���I���O�_���ࡨ���P�_�F�C
    cosine will be determined by the first and 2nd ele of maxtrixStr
    �� consine ���� has 4 possibility �|�إi��G
    �@ �A maxStr[0] maxStr[1] ���O�� [1][�Ů�]
    �G �A maxStr[0] maxStr[1] ���O�� [-][1]
    �T �A maxStr[0] maxStr[1] ���O�� [0][�Ů�]
    �| �A maxStr[0] maxStr[1] ���O�� [-][0] 
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - -*/ 

	bool rotateYBool = 0;//rotateYBool will be determined by >>
	    // >> - - - whether the brick is rotated around Y-axis by 90 degrees
	char cosine[]="";  //�� cosine[] �̲ת��g�k�O�D�`���� filename[] ���g�k
	int compareElement1;
	int compareElement2;

	//   >>   element 1 will be put into cosine:
	string s = std::string(1, matrixStr[0]); 
	const char *S  =s.c_str();
	strcat(cosine, S); // wrong code: cosine = strcat(cosine, S); 

	//   >>   element 2 will be put into cosine: 
	s = std::string(1, matrixStr[1]); 
	S = s.c_str();
	strcat(cosine, S); // [�Хû��O�o strcat����j�إΪk�A�O�d�V] 

	// - - - log 
		logFile2 <<"\n�Ӭݬ�cosine[0]"<< cosine[0]<<"��\n";
		logFile2 <<"\n�Ӭݬ�cosine[1]"<< cosine[1]<<"��\n";	    
	// - - - END log 


	compareElement1=strcmp(cosine, "1 ");
	compareElement2=strcmp(cosine, "-1");

	if( (compareElement1==0) || (compareElement2==0) ){
		logFile2 << "\n�S������,rotateYBool�]�w��0.\n";
	    rotateYBool = 0;
	}        //    END outer-if
	else{
	    compareElement1=strcmp(cosine, "0 ");
	    compareElement2=strcmp(cosine, "-0");
		if( (compareElement1==0) || (compareElement2==0) ){
			rotateYBool = 1;
			logFile2 << "\n������,rotateYBool�]�w��1.\n";
		}    //    END inner-if
		else{
		    logFile2 << "\n�L�k�T�{�쩳���S�����஺\n";
			
		}    //    END inner-else
	}        //    END outer-else
	    
    
    return rotateYBool;

}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - -
		logFile2 <<"\n"<< matrixStr<<"\n";
		logFile2 <<"\n�Ӭݬ�matrixStr[0]"<< matrixStr[0]<<"��\n";
		logFile2 <<"\n�Ӭݬ�matrixStr[1]"<< matrixStr[1]<<"��\n";
		logFile2 <<"\n�Ӭݬ�matrixStr[2]"<< matrixStr[2]<<"��\n";
		logFile <<"\n�Ӭݬ�matrixStr[3]"<< matrixStr[3]<<"��\n";
		logFile <<"\n�Ӭݬ�matrixStr[4]"<< matrixStr[2]<<"��\n";
		logFile <<"\n�Ӭݬ�matrixStr[5]"<< matrixStr[5]<<"��\n";
		logFile <<"\n�Ӭݬ�cosine[0]"<< cosine[0]<<"��\n";
		logFile <<"\n�Ӭݬ�cosine[1]"<< cosine[1]<<"��\n";
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - -*/









int setBrickType_1x2 ( int ID )
{


    return 0;
}
int setBrickType_2x4 ( int ID )
{


    return 0;
}
int setBrickType_2x2 ( int ID )
{
/***���ŦA�γo�� �{�b�L�k �]�� bricks[]  �o�ӯx�}�S���b this.���Y�ɤ��ŧi***/   
	/*
	bricks[ID].holeXNum = 2;
	bricks[ID].holeZNum = 2;
	bricks[ID].stubXNum = 2;
	bricks[ID].stubZNum = 2;
	*/

    return 0;
}

int setPlateType_1x4_clockY ( int ID ) // 3710.dat
{
	return 0;
}