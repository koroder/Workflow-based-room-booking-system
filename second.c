#include <string.h>
#include <stdio.h>

#define max_room 4
#define max_cpa 4
#define no_room 3
#define time 8
//#define OPERATOR 7
//#define MIC_FONES 7
#define property 13
//#define size 8
//int MIC_FONES,OPERATOR;
//char MIC_FONES[50],OPERATOR[50];
// 1st after rooms is operator 2nd mic.

struct data
	{
		char status;
		char pass;
		int room;
		int cpa;
		char prop[property];
		char time_slot[48];
		//char a1;
		//char a2;
	};
struct data A[no_room+2];
void db_process(struct data A[])
{
	
	FILE *fp;
	fp=fopen("data/database.c","r");
	char ch='a';
	char s[80] ;
	int i=0,j=0,k=0;
	i=0;
	for(i=0;i<no_room;i++)
		A[i].pass='y';
	i=0;
	//int OPERATOR,MIC_FONES;	
	fscanf(fp,"%d",&A[no_room].cpa);
	fscanf(fp,"%d",&A[no_room+1].cpa);
	while ( fscanf(fp,"%d %d %c %c %c %c %c %c %c %c %c %c %c %c %s",&A[i].room,&A[i].cpa,&A[i].prop[0],&A[i].prop[1],&A[i].prop[2],&A[i].prop[3],&A[i].prop[4],&A[i].prop[5],&A[i].prop[6],&A[i].prop[7],&A[i].prop[8],&A[i].prop[9],&A[i].prop[10],&A[i].prop[11],A[i].time_slot)!=EOF )
	{
		i++;
	}
	fclose(fp);
	//int op[A[no_room].cpa][48];
	//int mic[A[no_room+1].cpa][48];
	//fp=fopen("data/database_operator.c","w+");
	//for(i=0;i<A[no_room].cpa;i++)
	//{
	//	for(k=0;k<48
}
		
char check(char A[])
{
	FILE *istream;
	if((istream=fopen(A,"a+"))==NULL)
	{
		fclose ( istream);
		return 'n';
	}
	else
	{
		fclose ( istream);
		return 'y';
	}
}

char search(struct data A[],struct data B[],int size)
{
		struct data C;
		int a,b,c,i,j,k;
		int varop,varmic;
		int op[A[no_room].cpa][48];
		int mic[48];
		for(i=0;i<A[no_room].cpa;i++)
			for(j=0;j<48;j++)
				op[i][j]=0;
			for(j=0;j<48;j++)
				mic[j]=A[no_room+1].cpa;
		char time1[4],time2[4];
		for(i=0;i<size;i++)
		{
			if(B[i].status!='c')
			{
				for(j=0;j<no_room;j++)
				{
					if(A[j].pass=='y' && A[j].cpa<B[i].cpa)
						A[j].pass='n';
				}
				for(j=0;j<no_room;j++)
				{
					for(k=0;k<12;k++)
					{
						if(A[j].pass=='y' && B[i].prop[k]=='y' && A[j].prop[k]=='n')
							{A[j].pass='n';break;}
					}
				}
				
				for(k=0;k<2;k++)
				{
					time1[k]=B[i].time_slot[k];
					time2[k]=B[i].time_slot[4+k];
				}
				a=atoi(time1);
				b=atoi(time2);
				if(B[i].time_slot[2]=='3')
					a=2*a+1;
				else 
					a=2*a;
				if(B[i].time_slot[6]=='3')
					b=2*b+1;
				else 
					b=2*b;
				for(j=0;j<no_room;j++)
				{
					if(A[j].pass=='y')
					{
						for(k=a;k<b;k++)
						{
							if(A[j].time_slot[k]=='1')
							{
								A[j].pass='n';
								break;
							}
						}
					}
				}
				if(B[i].prop[6]=='y' || B[i].prop[8]=='y')
				{
					for(j=0;j<A[no_room].cpa;j++)
					{
						for(k=a;k<b;k++)
							{
								if(op[j][k]==1)
								{
									break;
								}
							}
						if(k==b-1)
						{
							for(k=a;k<b;k++)
							{
								op[j][k]=1;
							}
							break;
						}
					}
					if(j==no_room)
						{
							B[i].status='c';
							
						}
				}
				if(B[i].prop[5]=='y' || B[i].prop[7]=='y' || B[i].prop[9]=='y')
				{	
					for(k=a;k<b;k++)
					{
						if(mic[k]<B[i].cpa)
						B[i].status='c';
					}
					for(k=a;k<b;k++)
					{
						mic[k]=mic[k]-B[i].cpa;
					}
				}
				for(j=0;j<no_room;j++)
				{
					if(A[j].pass=='y')
						{
							C=A[j];
							j=-1;
							break;
						}
				}
				if(j!=-1)
					B[i].status='c';
				for(j=0;j<no_room;j++)
				{
					if(A[j].pass=='y' && C.cpa>A[j].cpa)
					{
						C=A[j];
					}
				}
				B[i].room=C.room;
				for(j=0;j<no_room;j++)
				{
					if(A[j].room==C.room)
					{
						for(k=a;k<b;k++)
						{
							A[j].time_slot[k]='1';
						}
					}
					A[j].pass='y';
					
				}
				
			}
			
		}
		
	return 'y';
			
}


void abdul_ki_string(char STRING[],struct data A[],char finder1[])
{
	
	int dual=0;
	if(strlen(STRING)<13)
		dual=1;   // admin business mode
	char date[9];
	char leftout[37];
	char s[80];
	char ch;
	int i=0,j=0,k=0;
	char present,present1;
	FILE *istream,*buffer;
	char answer;
	char a[20]="request/";
	char a1[20]="request/a";
	char stat[50]="n ";
	
	if(dual==0)
	{
		for(i=0;i<8;i++)
		{
			date[i]=STRING[j];
			j++;
		}j++;date[9]='\0';
		for(i=0;i<37;i++)
		{
			leftout[i]=STRING[j];
			j++;
		}
		strcat(stat,leftout);
		strcat(a,date);
		a[16]='\0';
		stat[39]='\0';
	}
	if(dual==1)
	{
		strcat(a,STRING);
		strcat(a1,STRING);
	}
	present=check(a);i=0;j=0;
	if((buffer=fopen(a1,"r"))!=NULL)
	{present1='y';fclose(buffer);}
	else
	present1='n';
	if(present1=='y')
	{
		buffer=fopen("buffer.c","w+");
		istream=fopen(a1,"r");
		while(fgets(s,79,istream)!=NULL )
		{
			fputs(s,buffer);
		}
		fclose(istream);
		fclose(buffer);
	}
	if(present=='y')
	{
		if(present1=='y')
		{
			buffer=fopen("buffer.c","a");
		}
		else 
		buffer=fopen("buffer.c","w+");
		istream=fopen(a,"r");
		while(fgets(s,79,istream)!=NULL )
		{
			fputs(s,buffer);i++;
		}
		if(dual==0)
		{fputs(stat,buffer);i++;}
		fclose(istream);
		
	}
	else
	{
		if(present1=='y')
		buffer=fopen("buffer.c","a");
		else 
		buffer=fopen("buffer.c","w+");
		if(dual==0)
		{fputs(stat,buffer);i++;}
	}
	fclose(buffer);
	int size=i;
	int size1=i+j;
	
	struct data B[size1];char last_space;
	buffer=fopen("buffer.c","r");i=0;
	while ( fscanf(buffer,"%c %d %s %c %c %c %c %c %c %c %c %c %c %c %c %d%c",&B[i].status,&B[i].cpa,B[i].time_slot,&B[i].prop[0],&B[i].prop[1],&B[i].prop[2],&B[i].prop[3],&B[i].prop[4],&B[i].prop[5],&B[i].prop[6],&B[i].prop[7],&B[i].prop[8],&B[i].prop[9],&B[i].prop[10],&B[i].prop[11],&B[i].room,&last_space)!=EOF)
	{
		i++;
	}
	fclose(buffer);
	answer=search(A,B,size1);
	i=0;
	if(answer=='y')
	{
		istream=fopen(a,"w+");
		i=size1-size;
		while(i<size1)
		{
			fprintf(istream,"%c %d %s %c %c %c %c %c %c %c %c %c %c %c %c %d\n",B[i].status,B[i].cpa,B[i].time_slot,B[i].prop[0],B[i].prop[1],B[i].prop[2],B[i].prop[3],B[i].prop[4],B[i].prop[5],B[i].prop[6],B[i].prop[7],B[i].prop[8],B[i].prop[9],B[i].prop[10],B[i].prop[11],B[i].room);
			i++;
		}
		fclose(istream);
		i=0;
		char c[17]="data/";
		if(dual==0)
		strcat(c,date);
		if(dual==1)
		strcat(c,STRING);
		c[13]='\0';
		istream=fopen(c,"w+");
		while(i<no_room)
		{
			fprintf(istream,"%d %d %c %c %c %c %c %c %c %c %c %c %c %c %s\n",A[i].room,A[i].cpa,A[i].prop[0],A[i].prop[1],A[i].prop[2],A[i].prop[3],A[i].prop[4],A[i].prop[5],A[i].prop[6],A[i].prop[7],A[i].prop[8],A[i].prop[9],A[i].prop[10],A[i].prop[11],A[i].time_slot);
			i++;
		}
		fclose(istream);
	}
	if(dual==1)
	{
		istream=fopen(a1,"w+");
		i=0;
		while(i<size1-size)
		{
			fprintf(istream,"%c %d %s %c %c %c %c %c %c %c %c %c %c %c %c %d\n",B[i].status,B[i].cpa,B[i].time_slot,B[i].prop[0],B[i].prop[1],B[i].prop[2],B[i].prop[3],B[i].prop[4],B[i].prop[5],B[i].prop[6],B[i].prop[7],B[i].prop[8],B[i].prop[9],B[i].prop[10],B[i].prop[11],B[i].room);
			i++;
		}
		fclose(istream);
	}
	sprintf(finder1,"%d",size);
	if(B[size1-1].status=='n')
		sprintf(finder1,"%d",size);
	if(B[size1-1].status=='c')
		{
			finder1[0]='-';
			finder1[1]='1';
			finder1[2]='\0';
		}
	
}
void status(char STRING[],char finder1[])
{
	char s[80];
	char date[8];
	char leftout[3];
	FILE *fp;
	int i=0,j=0,k=0;
	char ret[25];
	char temp[4],temp1[12];
	struct data Z;
	for(i=0;i<8;i++)
	{
		date[i]=STRING[j];
		j++;
	}j++;
	for(i=0;i<3;i++)
	{
		leftout[i]=STRING[j];
		j++;
	}
	if(leftout[0]!='a')
	{
		char last_space;
		k=atoi(leftout);
		char a[20]="request/";
		a[8]='\0';
		strcat(a,date);
		a[16]='\0';
		fp=fopen(a,"r");
		for(i=0;i<k;i++)
		{
			fscanf(fp,"%c %d %s %c %c %c %c %c %c %c %c %c %c %c %c %d%c",&Z.status,&Z.cpa,Z.time_slot,&Z.prop[0],&Z.prop[1],&Z.prop[2],&Z.prop[3],&Z.prop[4],&Z.prop[5],&Z.prop[6],&Z.prop[7],&Z.prop[8],&Z.prop[9],&Z.prop[10],&Z.prop[11],&Z.room,&last_space);
		
		}
		ret[0]=Z.status;
		sprintf(temp,"%d",Z.room);
		for(i=0;i<3-strlen(temp);i++)
			{ret[1+i]='0';}
		ret[1+i]='\0';
		strcat(ret,temp);
		strcat(ret,Z.time_slot);
		
	}
	else if(leftout[0]=='a')
	{
		char last_space;
		char left[2];
		for(i=0;i<2;i++)
		left[i]=leftout[i+1];
		k=atoi(left);
		char a[20]="admin/";
		strcat(a,date);
		fp=fopen(a,"r");
		for(j=0;j<k;j++)
		{
			fscanf(fp,"%c %d %s %c %c %c %c %c %c %c %c %c %c %c %c %d%c",&Z.status,&Z.cpa,Z.time_slot,&Z.prop[0],&Z.prop[1],&Z.prop[2],&Z.prop[3],&Z.prop[4],&Z.prop[5],&Z.prop[6],&Z.prop[7],&Z.prop[8],&Z.prop[9],&Z.prop[10],&Z.prop[11],&Z.room,&last_space);
		}
		ret[0]=Z.status;
		for(i=0;i<3-strlen(temp);i++)
			ret[1+i]='0';
		ret[1+i]='\0';
		strcat(ret,temp);
		strcat(ret,Z.time_slot);
		
	}
	strcpy(finder1,ret);
	
}
void cancel(char STRING[])
{
	char s[80];
	char date[9];
	char leftout[4];
	FILE *fp,*faltu;
	int i=0,j=0,k=0;
	for(i=0;i<8;i++)
	{
		date[i]=STRING[j];
		j++;
	}j++;
	date[9]='\0';
	for(i=0;i<3;i++)
	{
		leftout[i]=STRING[j];
		j++;
	}
	leftout[4]='\0';
	k=atoi(leftout);
	char a[18]="request/";
	a[8]='\0';
	strcat(a,date);
	a[16]='\0';
	fp=fopen(a,"r");
	faltu=fopen("faltu.c","w+");
	for(i=0;i<k-1;i++)
	{
		fgets(s,79,fp);
		fputs(s,faltu);
	}
	fgets(s,79,fp);
	s[0]='c';
	fputs(s,faltu);
	while(fgets(s,79,fp)!=NULL)
	{
		fputs(s,faltu);
	}
	fclose(fp);
	fclose(faltu);
	fp=fopen(a,"w+");
	faltu=fopen("faltu.c","r");
	while(fgets(s,79,faltu)!=NULL)
	{
		fputs(s,fp);
	}
	fclose(fp);
	fclose(faltu);
}
void admin(char STRING[])
{
	FILE *fp,*istream,*file;
	char a[20]="admin/";
	char s[80],s1[80];
	char date[8];
	char leftout[2];
	int i=0,j=0,k=0;
	char last_space;
	for(i=0;i<8;i++)
	{
		date[i]=STRING[j];
		j++;
	}j++;j++;
	for(i=0;i<2;i++)
	{
		leftout[i]=STRING[j];
		j++;
	}
	k=atoi(leftout);
	struct data C[1];
	strcat(a,date);
	fp=fopen(a,"r");
	istream=fopen("faltu.c","w+");
	char b[18]="request/a";
	strcat(b,date);
	file=fopen(b,"a");
	i=1;
	while(fgets(s,79,fp)!=NULL)
	{
		if(i==k)
		{
			strcpy(s1,s);
			s[0]='a';
			fputs(s,file);
		}
		fputs(s,istream);
		i++;
	}
	fclose(fp);
	fclose(istream);
	istream=fopen("faltu.c","r");
	fp=fopen(a,"w+");
	while(fgets(s,79,istream)!=NULL)
	{
		fputs(s,fp);
	}
	
	
	fclose(fp);
	fclose(file);
	fclose(istream);
	char answer1[50];
	abdul_ki_string(s1,A,answer1);
	istream=fopen(a,"w+");
	fp=fopen(b,"r");
	while(fgets(s,79,fp)!=NULL)
	{
		fputs(s,istream);
	}
	fclose(fp);
	fclose(istream);
}
		
//------------------------------------------------------------------------------

void processing(int pro_check, char data_pro[],char finder1[])
{
	FILE *fp;
	struct data B[no_room];
	int a;
	char c;
	db_process(A);
	
	if(pro_check == 1)
	{
		abdul_ki_string(data_pro,A,finder1);//s-input string,return-int(line no)
		if(finder1[0]=='-')
			printf("\nnai rahega tu\n");
	//here things being told to user as he is not entertained
		else
		printf("\nrah le yaar tu   %d\n",a);
	}
	if(pro_check==2) 
	{
		cancel(data_pro);//user id for cancel
	}
	if(pro_check==3)
	{
		status(data_pro,finder1);
	}
	if(pro_check==4)
	{
		admin(data_pro);
	}	
	
}
		
		
	
