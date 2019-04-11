#include <iostream>
#include <unistd.h>

using namespace std;

int main()
{
	struct movement{
		char direction;
		int rotation;
	}vmove;
	vmove.direction='l';
	vmove.rotation=90;
	int obstacle=0;
	int touch=0,infrared=0,photo=0,score=0;
	int actions=1; //Initial action turn left hencc the value 1
	int vachome[1][2]={8,4}; //starting position
	int vrow=8; //current row
	int vcol=4; //current column
	bool cleaned=false;
	int dirty=0;
	char grid[10][10]={
		{' ','_','_','_','_','_','_','_','_',' '}, //254 represents obstacle,177 represents dirt
		{'|','_',254,'_',177,'_','_',254,'_','|'},
		{'|','_','_',254,'_','_',177,'_','_','|'},
		{'|',177,'_','_',254,'_','_','_','_','|'},
		{'|','_',254,'_',177,'_','_',254,177,'|'},
		{'|','_','_','_','_','_','_','_','_','|'},
		{'|','_',177,177,'_',177,'_',177,'_','|'},
		{'|','_','_','_','_','_','_','_','_','|'},
		{'|',177,'_',254,'V','_',177,'_','_','|'},
		{'|','_','_','_','_','_','_','_','_','|'}};

	while(cleaned==false)
	{

	cout<<"\tTouch Sensor: "<<touch<<"\n\tPhoto Sensor: "<<photo<<"\n\tIR Sensor: "<<infrared<<endl;

	for(int i=0;i<10;i++)
	{
		cout<<"\t";
		for(int j=0;j<10;j++)
		{
			cout<<grid[i][j];
			if(grid[i][j]==char(177))
			{
				dirty++;
			}
		}
		cout<<endl;
	}

	if(vmove.direction=='l'&&vmove.rotation==90)
	{
		if(grid[vrow][vcol-1]!=char(254)&&vcol-1!=0) //KEEP MOVING FORWARD IF THERE IS NO OBSTACLE
		{

			if(grid[vrow][vcol-1]==char(177))
			{
				photo=1;
				grid[vrow][vcol-1]='V';
				grid[vrow][vcol]='_';
				vcol--;
				actions++;
				touch=0;
				score+=100;
			}
			else if(grid[vrow-1][vcol]==char(177))
			{
				photo=1;
				vmove.rotation=0;
				vmove.direction='u';
				actions++;
				touch=0;
				score+=100;
			}
			else if(grid[vrow+1][vcol]==char(177))
			{
				photo=1;
				vmove.rotation=180;
				vmove.direction='l';
				actions++;
				touch=0;
				score+=100;
			}
			else{
			photo=0;
			grid[vrow][vcol-1]='V';
			grid[vrow][vcol]='_';
			vcol--;
			actions++;
			touch=0;
			}
		}
		else if((grid[vrow][vcol-1]==char(254)&&grid[vrow-1][vcol]!=char(254)&&vrow-1!=0) || (grid[vrow][vcol-1]=='|'&&grid[vrow-1][vcol]!=char(254)&&vrow-1!=0)) //IF OBSTACLE IN FRONT AND NO OBSTACLE ON THE RIGHT
		{
			if(grid[vrow+1][vcol]==char(177))
			{
				photo=1;
				vmove.rotation=180;
				vmove.direction='l';
				actions++;
				touch=0;
			}
			else
			{
			vmove.direction='u';
			vmove.rotation=0;
			actions++;
			touch=1;
			}
		}
		else if(grid[vrow][vcol-1] == char(254) && grid[vrow+1][vcol] != char(254) || (grid[vrow][vcol-1] =='|' && grid[vrow+1][vcol] != char(254))) //IF OBSTACLE IN FRONT AND NO OBSTACLE ON THE LEFT
		{
			vmove.direction='l';
			vmove.rotation+=90;
			actions++;
			touch=1;
		}
		else if(grid[vrow][vcol-1]==char(254)&&grid[vrow][vcol+1]!=char(254) || (grid[vrow][vcol-1]=='|'&&grid[vrow][vcol+1]!=char(254))) //IF OBSTACLE IN FRONT AND ON RIGHT AND ON LEFT
		{
			vmove.direction='r';
			vmove.rotation=90;
			actions+=2;
			touch=1;
		}
	}
	else if(vmove.direction=='r'&&vmove.rotation==90)
	{
		if(grid[vrow][vcol+1]!=char(254)&&vcol+1!=9) //KEEP MOVING FORWARD IF THERE IS NO OBSTACLE
		{
			if(grid[vrow][vcol+1]==char(177))
			{
				photo=1;
				grid[vrow][vcol+1]='V';
				grid[vrow][vcol]='_';
				vcol++;
				actions++;
				touch=0;
				score+=100;
			}
			else if(grid[vrow-1][vcol]==char(177))
			{
				photo=1;
				vmove.rotation=0;
				vmove.direction='u';
				actions++;
				touch=0;
				score+=100;
			}
			else if(grid[vrow+1][vcol]==char(177))
			{
				photo=1;
				vmove.rotation=180;
				vmove.direction='r';
				actions++;
				touch=0;
				score+=100;
			}
			else
			{
				photo=0;
				grid[vrow][vcol+1]='V';
				grid[vrow][vcol]='_';
				vcol++;
				actions++;
				touch=0;
			}
		}
		else if((grid[vrow][vcol+1] == char(254) && grid[vrow-1][vcol] != char(254) && vrow-1!=0) || (grid[vrow][vcol+1] =='|' && grid[vrow-1][vcol]!=char(254) && vrow-1!=0)) //IF OBSTACLE IN FRONT AND NO OBSTACLE ON THE LEFT
		{
			vmove.direction='u';
			vmove.rotation=0;
			actions++;
			touch=1;
		}
		else if(grid[vrow][vcol+1] == char(254) && grid[vrow+1][vcol] !=char(254) || (grid[vrow][vcol+1] =='|' &&grid[vrow+1][vcol]!=char(254))) //IF OBSTACLE IN FRONT AND NO OBSTACLE ON THE RIGHT
		{
			vmove.direction='r';
			vmove.rotation+=90;
			actions++;
			touch=1;
		}
		else if(grid[vrow][vcol+1]==char(254) && grid[vrow][vcol+1]!=char(254) || (grid[vrow][vcol+1] =='|' && grid[vrow][vcol+1] != char(254))) //IF OBSTACLE IN FRONT AND ON RIGHT AND ON LEFT
		{
			vmove.direction='l';
			vmove.rotation=90;
			actions+=2;
			touch=1;
		}
	}
	else if(vmove.direction=='u' && vmove.rotation==0)
	{
		if(grid[vrow][vcol-1] !='|' && vrow-1!=0) //KEEP MOVING FORWARD IF THERE IS NO OBSTACLE
		{
			grid[vrow-1][vcol]='V';
			grid[vrow][vcol]='_';
			vrow--;
			vmove.direction='l';
			vmove.rotation=90;
			actions+=2;
		}
		else if(grid[vrow][vcol-1] =='|' && vrow-1!=0) //KEEP MOVING FORWARD IF THERE IS NO OBSTACLE
		{
			grid[vrow-1][vcol]='V';
			grid[vrow][vcol]='_';
			vrow--;
			vmove.direction='r';
			vmove.rotation=90;
			actions+=2;
		}
	}

	else if(vmove.direction=='r' && vmove.rotation==180)
	{
		if(vrow+1!=9) //KEEP MOVING FORWARD IF THERE IS NO OBSTACLE
		{
			grid[vrow+1][vcol]='V';
			grid[vrow][vcol]='_';
			vrow++;
			vmove.direction='r';
			vmove.rotation=90;
			actions+=2;
		}
	}
	else if(vmove.direction=='l' && vmove.rotation==180)
	{
		if(vrow+1!=9 && vcol+1!=9 && vrow-1!=0 && grid[vrow+1][vcol]!=char(254)) //KEEP MOVING FORWARD IF THERE IS NO OBSTACLE
		{
			grid[vrow+1][vcol]='V';
			grid[vrow][vcol]='_';
			vrow++;
			vmove.direction='l';
			vmove.rotation=90;
			actions+=2;
		}
		else if(vcol+1==9 && vrow+1!=9 && grid[vrow+1][vcol]!=char(254))
		{
			grid[vrow+1][vcol]='V';
			grid[vrow][vcol]='_';
			vrow++;
			actions++;
		}
		else if(vcol+1==9 && vrow+1!=9 && grid[vrow+1][vcol]==char(254))
		{
			vmove.direction='l';
			vmove.rotation=90;
			actions++;
		}
		else if(vrow+1==9)
		{
			vmove.direction='l';
			vmove.rotation=90;
		}
	}

	if(dirty==0 && vrow==8 && vcol==4)
	{
		cleaned=true;
		infrared=1;
	}
	usleep(1000);
	system("clear");
	dirty=0;
	}


	cout<<"\tTouch Sensor: "<<touch<<"\n\tPhoto Sensor: "<<photo<<"\n\tIR Sensor: "<<infrared<<endl;

	for(int i=0;i<10;i++)
	{
		cout<<"\t";
		for(int j=0;j<10;j++)
		{
			cout<<grid[i][j];
		}
		cout<<endl;
	}
	cout<<"Cleanup score: "<<score<<endl;
	cout<<"Total moves: "<<actions<<endl;
	cout<<"Final score: "<<score-actions<<endl;

	return 0;
}
