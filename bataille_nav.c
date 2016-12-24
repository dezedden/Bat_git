#include<stdlib.h>
#include<stdio.h>
#include<time.h>
void affiche_tab();
int placer_bateau();
char intialiser_tableau();
int Tab[10][10];
int Tab_ordi[10][10];
int Tab_ordi_a_afficher[10][10];
char intialiser_tableau_ordi();
void affiche_tab_ordi();
char tirer();
char tirer_ordi();
int placer_bateau_ordi();
int OnPeutTirer(); //le compteur du nombre de bateau restant
int OnPeutTirer_Ordi();
void ordi_ma_touche(); //dit combien de fois l ordi m'a touché
char initialiser_tableau_ordi_a_afficher();
void affiche_tab_ordi_a_afficher();
char tirer_ordi_haut(int i,int j);
char tirer_ordi_droite(int i,int j);
char tirer_ordi_bas(int i,int j);



char tirer_ordi()
{
    int i,j,n,bon;
    char c;
    int z;
    z=rand()%2;//ou on tire? haut ou bas?
  	i=rand()%10;
  	j=rand()%10;
	bon=0;
	if(Tab[i][j]=='0' || Tab[i][j]=='R')
	{
         Tab[i][j]='x';
         ordi_ma_touche();
         affiche_tab();
         bon=1;
	}
	if(bon)
	{
        if (OnPeutTirer_Ordi()) //compte le nombre de T
        {
            printf("L ORDI GARDE LA MAIN IL RETIRE \n\n\n");
            tirer_ordi_haut(i,j);
            affiche_tab_ordi_a_afficher();
            tirer_ordi_droite(i,j);
            affiche_tab_ordi_a_afficher();
            tirer_ordi_bas(i,j);
            //affiche_tab_ordi_a_afficher();
        }
        else printf("VOUS AVEZ PERDU DESOLE!!!");
	}
	else
	{
        Tab[i][j]='W';
        affiche_tab();
        printf("L ORDINATEUR VIENT DE RATE. A VOTRE TOUR\n\n !");
        tirer();
	}

}
char tirer_ordi_haut(int i,int j){
    int c;
    c=i;
    if(c-1<0) tirer_ordi_droite(0,j);
    while(Tab[c-1][j]=='0')
        {
            Tab[c-1][j]='x';
            ordi_ma_touche();
            affiche_tab();
            c--;
            tirer_ordi_haut(c,j);
        }
	//else tirer_ordi_droite(i,j);
	/*if(Tab[i-1][j]!='0')
	{
        Tab[i][j]='W';
        affiche_tab();
        printf("L ORDINATEUR VIENT DE RATE. A VOTRE TOUR\n\n !");
        tirer();
	}*/
}
char tirer_ordi_droite(int i,int j){
    int k;
    k=j;
    if((k+1)>9) tirer_ordi_haut(i,9);
    while(Tab[i][k+1]=='0')
        {
            Tab[i][k]='x';
            ordi_ma_touche();
            affiche_tab();
            k++;
            tirer_ordi_droite(i,k);
        }
    }
char tirer_ordi_bas(int i,int j){
    int c;
    c=i;
    if(c+1>9) tirer_ordi_droite(9,j);
    while(Tab[c+1][j]=='0')
        {
            Tab[c+1][j]='x';
            ordi_ma_touche();
            affiche_tab();
            c++;
            tirer_ordi_bas(c,j);
        }

}
char tirer()
{
    int i,j,n,bon,x,y;
    char c;
  	do
    { printf("Entre la ligne (de A a J): ");
	  scanf("%c",&c);
	  i=(c|32)-'a';
    } while(i<0 || i>9);
	do
	{ printf("entre la cordonnee de j : ");
	  while (scanf("%d",&n)!=1) fflush(stdin);
	  j=n-1;
	}while(j<0 || j>9);//tant
	bon=0;
	if(Tab_ordi[i][j]=='0')
	{
         Tab_ordi[i][j]='T';
         //Tab[i][j]='T';
         //affiche_tab();
         Tab_ordi_a_afficher[i][j]='T';
         affiche_tab_ordi_a_afficher();
         bon=1;
	}
	if(bon)
	{
        if (OnPeutTirer()) tirer();
        else printf("BRAVO VOUS AVEZ GAGNEZ!!!");
	}
	else
	{
        Tab_ordi[i][j]='R';
        Tab_ordi_a_afficher[i][j]='R';

        //Tab[i][j]='R';
        printf("-----------------------------------------------------------------\n\n ETAT BATEAUX ORDI:\n\n ");
        //affiche_tab();
        affiche_tab_ordi_a_afficher();
        printf("VOUS AVEZ RATE\n---AU TOUR DE L ORDI \n\n\n");
        tirer_ordi();
    }
}
void ordi_ma_touche(){
    int x,y,c;
    c=0;
    for (x=0;x<10;x++)
    {
        for(y=0;y<10;y++)
        {
            if (Tab[x][y]=='x') c++;
        }
    }
    printf("L ORDI VIENT DE VOUS TOUCHER UNE %d IEME FOIS\n\n\n", c);
}

int placer_bateau_ordi()
{
  int j;//colonne
  int l=1;//longueur bateau
  int k;
  int i;//ligne
  int a;//alignement vertical ou horizontal
  int u,h,n;
  int bon;
  char c;
  while (l<=2)//placer tous les baateaux d'un coup
  {
    i=rand()%10;
	j=rand()%10;
	a=rand()%2;
	if(l<6 || l<=9-i+1 || l<=9-j+1)
	{

    if(a==1)
    { bon=1;
      for (h=0;h<l;h++) // Ici on parcourt d'abord la colonne pour savoir s'il n'y a pas d'autres valeurs"0"
      {
        if(Tab_ordi[i+h][j]=='0' || (i+h)>=10) bon=0;
      }
      if(bon)
      {
        for (k=0;k<l;k++) Tab_ordi[i+k][j]='0';
        l+=1;
      }

    }
    if(a==0)
    { bon=1;
      for (h=0;h<l;h++)
      {
        if(Tab_ordi[i][j+h]=='0' || (j+h)>=10) bon=0;
      }
      if(bon)
      {
        for (k=0;k<l;k++) Tab_ordi[i][j+k]='0';
        l+=1;
      }
      else u--;
    }
    else u--;
    }
   }
   //tirer();
}

int placer_bateau()
{
  int j;//colonne
  int l=1;//longueur bateau
  int k;
  int i;//ligne
  int a;//alignement vertical ou horizontal
  int u,h,n;
  int bon;
  char c;
  while (l<=5)//placer tous les baateaux d'un coup
  {
    do
    { printf("Entre la ligne (de A a J): ");
	  scanf("%c",&c);
	  fflush(stdin);
	  i=(c|32)-'a';
    } while(i<0 || i>9);
	do
	{ printf("entre la cordonnee de j : ");
	  while (scanf("%d",&n)!=1) fflush(stdin);
	  j=n-1;
	}while(j<0 || j>9);//tant que j n'est pas inf à 0 et sup a dix, on applique l instruct
	do
    { printf("tape 1 pour alignement vertical ou 0 pour horizontal\n");
      while(scanf("%d",&a)!=1) fflush(stdin);
	}while(a<0 || a>1);
	if(l<6 || l<=9-i+1 || l<=9-j+1)
	{

    if(a==1)
    { bon=1;
      for (h=0;h<l;h++) // Ici on parcourt d'abord la colonne pour savoir s'il n'y a pas d'autres valeurs"0"
      {
        if(Tab[i+h][j]=='0' || (i+h)>=10) bon=0;
      }
      if(bon)
      {
        for (k=0;k<l;k++) Tab[i+k][j]='0';
        l+=1;
      }

    }
    if(a==0)
    { bon=1;
      for (h=0;h<l;h++)
      {
        if(Tab[i][j+h]=='0' || (j+h)>=10) bon=0;
      }
      if(bon)
      {
        for (k=0;k<l;k++) Tab[i][j+k]='0';
        l+=1;
      }
      else u--;
    }
    else u--;
    }
    affiche_tab();
   }
   printf("L ORDINATEUR VIENT DE PLACER SES BATEAUX   LA PARTIE PEUT COMMENCER :) \n\nVEUILLEZ TIRER SVP\n\n");
   tirer();
}
int OnPeutTirer()
{
    int i,j,c;
    c=0;
    for(i=0;i<10;i++)
    {
        for(j=0;j<10;j++)
        {
            if (Tab[i][j]=='T') c++;
        }
    }
    if(c==3) return 0;
    else return 1;

}
int OnPeutTirer_Ordi()
{
    int i,j,c;
    c=0;
    for(i=0;i<10;i++)
    {
        for(j=0;j<10;j++)
        {
            if (Tab[i][j]=='x') c++;
        }
    }
    if(c==10) return 0;
    else return 1;

}



 char intialiser_tableau()
 {
 	int i;
 	int j;

    	for(i=0;i<10;i++)
    	{
    		for(j=0;j<10;j++)
    		{
    			Tab[i][j]='1';
    		}
 		}
 }
 char initialiser_tableau_ordi()
 {
 	int i;
 	int j;

    	for(i=0;i<10;i++)
    	{
    		for(j=0;j<10;j++)
    		{
    			Tab_ordi[i][j]='1';
    		}
 		}
 }
 char initialiser_tableau_ordi_a_afficher()
 {
 	int i;
 	int j;

    	for(i=0;i<10;i++)
    	{
    		for(j=0;j<10;j++)
    		{
    			Tab_ordi_a_afficher[i][j]='1';
    		}
 		}
 }

void affiche_tab_ordi()
{
	int i,j;
	printf("   1     2     3     4     5     6     7     8     9    10\n");
	for(i=0;i<10;i++){
		for(printf("%c",'A'+i),j=0;j<10;j++){

			printf( "  %c   ",Tab_ordi[i][j]);

		}
		printf("\n");
	}

}

void affiche_tab()
{
	int i,j;
	printf("   1     2     3     4     5     6     7     8     9    10\n");
	for(i=0;i<10;i++){
		for(printf("%c",'A'+i),j=0;j<10;j++){

			printf( "  %c   ",Tab[i][j]);

		}
		printf("\n");
	}

}
void affiche_tab_ordi_a_afficher()
{
	int i,j;
	printf("  1     2     3     4     5     6     7     8     9    10\n");
	for(i=0;i<10;i++){
		for(printf("%c",'A'+i),j=0;j<10;j++){

			printf( "  %c   ",Tab_ordi_a_afficher[i][j]);

		}
		printf("\n");
	}

}
int main ()
{
    srand(time(NULL));
    intialiser_tableau();
    initialiser_tableau_ordi();
    initialiser_tableau_ordi_a_afficher();
    //affiche_tab();

    placer_bateau_ordi();
    affiche_tab_ordi();
    placer_bateau();

}
