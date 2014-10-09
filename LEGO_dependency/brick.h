
struct brick{

    int ID;
	char btype[20];
	int x;
	int y;
	int z;
	int nbNum; /*numbers of neighbor*/
	int stubXNum;
	int stubZNum;
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