
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

int ing_boyut();

FILE *dic, *rel,*aa;
char c;

char sorgu[36];
int Adr;
int Temp;

int hashBoyutu=0;
char ingilizce[36];
char turkce[85];
char dizi[122];

time_t start_t, end_t, total_t;
double dif_sec;

int sure()
{

   double diff_t;

   time(&end_t);
   diff_t = difftime(end_t, start_t);

    return diff_t;
}

int Hash ()
{
  long int sum = 0;
  int j=0;
  int s=ing_boyut();
  for ( j=0; j<s; j++)
  sum=sum+pow(ingilizce[j],3);
  return sum;
}


int Hash1 ()
{
  long int sum = 0;
  int j=0;
  int s=ing_boyut();
  for ( j=0; j<s; j++)
sum=sum+ingilizce[j];

  return (7-sum%7)+1;
}



int ing_boyut()
{
    int i=0;
    for(;i<36;i++)
    {
        if(ingilizce[i]==' ')
            if(ingilizce[i+1]==' ')
            return i;
    }
    return 0;
}
void LineerRelativeOlustur()
{
    int fileSize=0;
    int cakisma=0;
     time(&start_t);
	dic = fopen("sozluk.txt", "r");
	rel = fopen("lineer.txt", "w+");

     int i=0;
	for( i=0; i<=hashBoyutu; i++)
	{
		fseek(rel,i*120,0);
		fputc('*', rel );
	}

	for( i=1; i<=hashBoyutu; i++)
	{

int f=0;
for(;f<85;f++)
    turkce[f]=' ';

     f=0;
for(;f<35;f++)
    ingilizce[f]=' ';




  fgets(dizi,120,dic);

  strncpy(ingilizce,dizi,36);
  ingilizce[35] = '\0';


  int k=35;
  char c='a';
  int s=0;
  for(; c!='\n';k++)
{
    c=dizi[k+1];
    if(c!='\n')
      	{
      	turkce[s]=c;
      	s++;
        }
	  }
    turkce[84]='\0';



fseek(rel,(Hash()*120)+1,0);
        c=fgetc(rel);
		//printf("*****%d****0",c);
		int kk=0;
		while(c!=0)
        {
            kk++;
            fseek(rel,(((Hash()+kk)%hashBoyutu)*120)+1,0);
             c=fgetc(rel);
             cakisma++;

        }
		fseek(rel,(((Hash()+kk)%hashBoyutu)*120)+1,0);

		fprintf(rel, "%s", ingilizce);

		fprintf(rel, "%s", turkce);

         if(fileSize<ftell(rel))
            fileSize=ftell(rel);


	}



	printf("\n\n /lineer BAGIL DOSYA OLUSTURULDU \n sure :  %d\ncakisma: %d -- %d KB",sure(),cakisma,fileSize/1000);
	fclose(rel);
	fclose(dic);
	getch();
}


void LineerKelimeSorgula(){
printf("\nLineer Dosyada kelime sorgulama \n ING kelimeyi giriniz : ");
fflush(stdin);
gets(sorgu);

 time(&start_t);

 int fileSize=0;
    int cakisma=0;
     time(&start_t);
	dic = fopen("sozluk.txt", "r");
	rel = fopen("lineer.txt", "r");

     int i=0;

   strcpy(ingilizce,sorgu);
   int hHash=Hash();

char dd;
int kk=0;
int kontrol=0;
int boyut=hashBoyutu;
     for( i=0; i<=boyut; i++)
	{


	 fseek(rel,(((hHash+kk)%hashBoyutu)*120)+1,0);
	  kk++;
    fgets(dizi,120,rel);

    strncpy(ingilizce,dizi,36);
    ingilizce[ing_boyut()] = '\0';



  if(strcmp(ingilizce,sorgu)==0)
     {
       puts(dizi);
       printf("\n dongu sayisi %d",i);
       i= boyut;
     kontrol=1;
     }

	}
	if(kontrol==0)
        printf("\n* Kelime Bulunamadi !!!");

	fclose(rel);
	fclose(dic);
	getch();


}

void LineerKelimeEkle()
{

    int fileSize=0;
    int cakisma=0;
     time(&start_t);
	dic = fopen("sozluk.txt", "r");
	rel = fopen("lineer.txt", "r+");

     int i=0;

  char c;
  int kontrol=0;
 for( i=0; i<=hashBoyutu; i++)
	{
	    fseek(rel,i*120+1,0);
	    c=fgetc(rel);
	    if(c==32 || c==0 )
            kontrol=1;
	}

if(kontrol==1)
{


char ing[35];


int f=0;
for(;f<85;f++)
    turkce[f]=' ';

     f=0;
for(;f<35;f++)
    ingilizce[f]=' ';




printf("ingilizce kelimeyi giriniz : ");
fflush(stdin);
gets(ing);
strncpy(ingilizce,ing,strlen(ing));


  int k=35;
  char c='a';
  int s=0;

printf("turkce kelimeyi giriniz : ");
fflush(stdin);
gets(turkce);

    turkce[84]='\0';



fseek(rel,(Hash()*120)+1,0);
        c=fgetc(rel);
		printf("*****%d****",c);
		int kk=0;
		while(c!=32)
        {
            kk++;
            printf("\n%d %d",(Hash()+kk)%hashBoyutu , c);
            fseek(rel,(((Hash()+kk)%hashBoyutu)*120)+1,0);
             c=fgetc(rel);
             cakisma++;

        }
		fseek(rel,(((Hash()+kk)%hashBoyutu)*120)+1,0);

       ingilizce[35] = '\0';
		fprintf(rel, "%s", ingilizce);

		fprintf(rel, "%s", turkce);



    /* file pointer at the end of file */

 printf("\n Kelime Basari ile kaydedildi %d ",(Hash()+kk)%hashBoyutu);

	printf("\n sure :  %d\ncakisma: %d -- %d KB",sure(),cakisma,fileSize/1000);

	}
	if(kontrol==0)
        printf("* Dosya Dolu !!!");
	fclose(rel);
	fclose(dic);
	getch();

}

void LineerKelimeSil() {

printf("\nLineer Dosyada kelime sorgulama \n ING kelimeyi giriniz : ");
fflush(stdin);
gets(sorgu);

 time(&start_t);

 int fileSize=0;
    int cakisma=0;
     time(&start_t);
	dic = fopen("sozluk.txt", "r");
	rel = fopen("lineer.txt", "r+");

     int i=0;
  char di[121];
     for(i=0;i<121;i++)
     di[i]=' ';
     di[119]='\0';

   strcpy(ingilizce,sorgu);
   int hHash=Hash();

char dd;
int kk=0;
     for( i=0; i<=hashBoyutu+hHash; i++)
	{

	 fseek(rel,(((hHash+kk)%hashBoyutu)*120)+1,0);
	  kk++;
    fgets(dizi,120,rel);

    strncpy(ingilizce,dizi,36);
    ingilizce[ing_boyut()] = '\0';



  if(strcmp(ingilizce,sorgu)==0)
     {
       kk--;
       fseek(rel,(((hHash+kk)%hashBoyutu)*120)+1,0);
       fprintf(rel,di);

       printf("\n dongu sayisi %d",i);
       i= hashBoyutu+hHash;
     }

	}

	fclose(rel);
	fclose(dic);
	getch();


}



//-----------------Quadratic probing----
void QuadraticRelativeOlustur() {


printf("\n------------------\n");
int fileSize=0;
    int cakisma=0;
     time(&start_t);
	dic = fopen("sozluk.txt", "r");
	rel = fopen("quadratic.txt", "w+");

     int i=0;


	for( i=0; i<=hashBoyutu; i++)
	{
		fseek(rel,i*120,0);
		fputc('*', rel );
	}

	for( i=1; i<=hashBoyutu; i++)
	{

int f=0;
for(;f<85;f++)
    turkce[f]=' ';

     f=0;
for(;f<35;f++)
    ingilizce[f]=' ';



  fgets(dizi,120,dic);

  strncpy(ingilizce,dizi,36);
  ingilizce[35] = '\0';


  int k=35;
  char c='a';
  int s=0;
  for(; c!='\n';k++)
{
    c=dizi[k+1];
    if(c!='\n')
      	{
      	turkce[s]=c;
      	s++;
        }
	  }
    turkce[84]='\0';



fseek(rel,(Hash()*120)+1,0);
        c=fgetc(rel);

		int kk=0;

		while(c!=0)
        {
            kk++;

            fseek(rel,(((Hash()+(kk*kk%hashBoyutu))%hashBoyutu)*120)+1,0);
             c=fgetc(rel);
             cakisma++;

             if(kk>hashBoyutu)
                break;

        }
        if(kk<hashBoyutu)
           {


		 fseek(rel,(((Hash()+(kk*kk%hashBoyutu))%hashBoyutu)*120)+1,0);

		fprintf(rel, "%s", ingilizce);

		fprintf(rel, "%s", turkce);

           }
           else
            {
            printf("\nKelime eklenemedi %s",ingilizce);
           }
         if(fileSize<ftell(rel))
            fileSize=ftell(rel);


	}
    /* file pointer at the end of file */


	printf("\n\n Quad BAGIL DOSYA OLUSTURULDU \n sure :  %d\ncakisma: %d -- %d KB",sure(),cakisma,fileSize/1000);
	fclose(rel);
	fclose(dic);
	getch();


}

void QuadraticKelimeSorgula() {

printf("\nQuadratic Dosyada kelime sorgulama \n ING kelimeyi giriniz : ");
fflush(stdin);
gets(sorgu);

 time(&start_t);

 int fileSize=0;
    int cakisma=0;
     time(&start_t);
	dic = fopen("sozluk.txt", "r");
	rel = fopen("quadratic.txt", "r");

     int i=0;

   strcpy(ingilizce,sorgu);
   int hHash=Hash();

char dd;
int kk=0;
int kontrol=0;
     for( i=0; i<=hashBoyutu; i++)
	{



	 fseek(rel,(((hHash+(kk*kk))%hashBoyutu)*120)+1,0);
	  kk++;
    fgets(dizi,120,rel);

    strncpy(ingilizce,dizi,36);
    ingilizce[ing_boyut()] = '\0';



  if(strcmp(ingilizce,sorgu)==0)
     {
       puts(dizi);
       printf("\n dongu sayisi %d",i);
       i= hashBoyutu+hHash;
       kontrol=1;
     }

	}
	if(kontrol==0)
         printf("\n* Kelime Bulunamadi !!!");

	fclose(rel);
	fclose(dic);
	getch();



}

void QuadraticKelimeEkle() {

int fileSize=0;
    int cakisma=0;
     time(&start_t);
	dic = fopen("sozluk.txt", "r");
	rel = fopen("quadratic.txt", "r+");

     int i=0;

char ing[35];


int f=0;
for(;f<85;f++)
    turkce[f]=' ';

     f=0;
for(;f<35;f++)
    ingilizce[f]=' ';





  int k=35;
  char c='a';
  int s=0;

   int kontrol=0;
 for( i=0; i<=hashBoyutu; i++)
	{
	    fseek(rel,i*120+1,0);
	    c=fgetc(rel);
	    if(c==32 || c==0 )
            kontrol=1;
	}
	if(kontrol==1)
    {

printf("ingilizce kelimeyi giriniz : ");
fflush(stdin);
gets(ing);
strncpy(ingilizce,ing,strlen(ing));


   printf("turkce kelimeyi giriniz : ");
fflush(stdin);
gets(turkce);

    turkce[84]='\0';


fseek(rel,(Hash()*120)+1,0);
        c=fgetc(rel);

		int kk=0;

		while(c!=32 && c!=0)
        {
            kk++;
            fseek(rel,(((Hash()+(kk*kk%hashBoyutu))%hashBoyutu)*120)+1,0);
             c=fgetc(rel);
             cakisma++;
             if(kk>hashBoyutu)
                break;

        }
        if(kk<hashBoyutu)
        {


		 fseek(rel,(((Hash()+(kk*kk%hashBoyutu))%hashBoyutu)*120)+1,0);

    ingilizce[35] = '\0';

		fprintf(rel, "%s", ingilizce);

		fprintf(rel, "%s", turkce);




    /* file pointer at the end of file */

 printf("\n Kelime Basari ile kaydedildi %d ",(Hash()+kk)%hashBoyutu);


	printf("\n\n Quad BAGIL DOSYA KELIME EKLENDI \n sure :  %d\ncakisma: %d -- %d KB",sure(),cakisma,fileSize/1000);
        }
        else printf("\n!!!Kelime Eklenemedi");
	  }
    else printf("\n* Dosya Dolu !!!");

	fclose(rel);
	fclose(dic);
	getch();





}

void QuadraticKelimeSil() {

printf("\nLineer Dosyada kelime sorgulama \n ING kelimeyi giriniz : ");
fflush(stdin);
gets(sorgu);

 time(&start_t);

 int fileSize=0;
    int cakisma=0;
     time(&start_t);
	dic = fopen("sozluk.txt", "r");
	rel = fopen("quadratic.txt", "r+");

     int i=0;

     char di[121];
     for(i=0;i<121;i++)
     di[i]=' ';
     di[119]='\0';

   strcpy(ingilizce,sorgu);
   int hHash=Hash();

char dd;
int kk=0;
int kontrol=0;
     for( i=0; i<=hashBoyutu; i++)
	{



	 fseek(rel,(((hHash+(kk*kk))%hashBoyutu)*120)+1,0);
	  kk++;
    fgets(dizi,120,rel);

    strncpy(ingilizce,dizi,36);
    ingilizce[ing_boyut()] = '\0';



  if(strcmp(ingilizce,sorgu)==0)
     {
         kk--;

	 fseek(rel,(((hHash+(kk*kk))%hashBoyutu)*120)+1,0);
	 fprintf(rel,di);

       printf("\n Silindi !!! dongu sayisi %d",i);
       i= hashBoyutu;
       kontrol=1;
     }

	}
	if(kontrol==0)
         printf("\n* Kelime Bulunamadi !!!");

	fclose(rel);
	fclose(dic);
	getch();

}

//--------------------Double hashing-------

void DoubleRelativeOlustur() {

printf("\n------------------\n");
    int fileSize=0;
    int cakisma=0;
     time(&start_t);
	dic = fopen("sozluk.txt", "r");
	rel = fopen("double.txt", "w+");

     int i=0;
	for( i=0; i<=hashBoyutu; i++)
	{
		fseek(rel,i*120,0);
		fputc('*', rel );
	}

	for( i=1; i<=hashBoyutu; i++)
	{

int f=0;
for(;f<85;f++)
    turkce[f]=' ';

     f=0;
for(;f<35;f++)
    ingilizce[f]=' ';


  fgets(dizi,120,dic);

  strncpy(ingilizce,dizi,36);
  ingilizce[35] = '\0';


  int k=35;
  char c='a';
  int s=0;
  for(; c!='\n';k++)
{
    c=dizi[k+1];
    if(c!='\n')
      	{
      	turkce[s]=c;
      	s++;
        }
	  }
    turkce[84]='\0';


	int kk=0;
 fseek(rel,(((Hash()+kk*Hash1())%hashBoyutu)*120)+1,0);
        c=fgetc(rel);

		while(c!=0)
        {
               kk++;

            fseek(rel,(((Hash()%hashBoyutu)+(kk*Hash1())+kk/10000 )%hashBoyutu  *120  )+1,0);
             c=fgetc(rel);
             cakisma++;

        }
		   fseek(rel,(((Hash()%hashBoyutu)+(kk*Hash1())+kk/10000 )%hashBoyutu  *120  )+1,0);

		fprintf(rel, "%s", ingilizce);

		fprintf(rel, "%s", turkce);

         if(fileSize<ftell(rel))
            fileSize=ftell(rel);


	}
    /* file pointer at the end of file */


	printf("\n\n Double BAGIL DOSYA OLUSTURULDU \n sure :  %d\ncakisma: %d -- %d KB",sure(),cakisma,fileSize/1000);
	fclose(rel);
	fclose(dic);
	getch();


}

void DoubleKelimeSorgula() {

printf("\nDouble Dosyada kelime sorgulama \n ING kelimeyi giriniz : ");
fflush(stdin);
gets(sorgu);

 time(&start_t);

 int fileSize=0;
    int cakisma=0;
     time(&start_t);
	dic = fopen("sozluk.txt", "r");
	rel = fopen("double.txt", "r");

     int i=0;

   strcpy(ingilizce,sorgu);
   int hHash=Hash();

char dd;
int kk=0;
int kontrol=0;
     for( i=0; i<=hashBoyutu; i++)
	{

	fseek(rel,(((Hash()%hashBoyutu)+(kk*Hash1())+kk/10000 )%hashBoyutu  *120  )+1,0);

	  kk++;
    fgets(dizi,120,rel);

    strncpy(ingilizce,dizi,36);
    ingilizce[ing_boyut()] = '\0';



  if(strcmp(ingilizce,sorgu)==0)
     {
       puts(dizi);
       printf("\n dongu sayisi %d",i);
       i= hashBoyutu+hHash;
       kontrol=1;
     }

	}

	if(kontrol==0)
          printf("\n* Kelime Bulunamadi !!!");

	fclose(rel);
	fclose(dic);
	getch();




}

void DoubleKelimeEkle() {

 int fileSize=0;
    int cakisma=0;
     time(&start_t);
	dic = fopen("sozluk.txt", "r");
	rel = fopen("double.txt", "r+");

     int i=0;

char ing[35];


int f=0;
for(;f<85;f++)
    turkce[f]=' ';

     f=0;
for(;f<35;f++)
    ingilizce[f]=' ';


  int kontrol=0;
 for( i=0; i<=hashBoyutu; i++)  //number of elements is 40
	{
	    fseek(rel,i*120+1,0);
	    c=fgetc(rel);
	    if(c==32 || c==0 )
            kontrol=1;
	}

	if(kontrol==1)
    {



 printf("ingilizce kelimeyi giriniz : ");
fflush(stdin);
gets(ing);
strncpy(ingilizce,ing,strlen(ing));


  int k=35;
  char c='a';
  int s=0;



   printf("turkce kelimeyi giriniz : ");
fflush(stdin);
gets(turkce);


    turkce[84]='\0';


	int kk=0;
 fseek(rel,(((Hash()+kk*Hash1())%hashBoyutu)*120)+1,0);
        c=fgetc(rel);

		while(c!=32)
        {
             kk++;

            fseek(rel,(((Hash()%hashBoyutu)+(kk*Hash1())+kk/10000 )%hashBoyutu  *120  )+1,0);
             c=fgetc(rel);
             cakisma++;

        }
		   fseek(rel,(((Hash()%hashBoyutu)+(kk*Hash1())+kk/10000 )%hashBoyutu  *120  )+1,0);
 ingilizce[35] = '\0';
		fprintf(rel, "%s", ingilizce);

		fprintf(rel, "%s", turkce);
    printf("\n Kelime Basari ile kaydedildi %d ",((Hash()%hashBoyutu)+(kk*Hash1())+kk/10000 )%hashBoyutu);
    }

    else
          printf("* Dosya Dolu !!!");
    /* file pointer at the end of file */



	fclose(rel);
	fclose(dic);
	getch();




}

void DoubleKelimeSil() {

printf("\nDouble Dosyada kelime sorgulama \n ING kelimeyi giriniz : ");
fflush(stdin);
gets(sorgu);

 time(&start_t);

 int fileSize=0;
    int cakisma=0;
     time(&start_t);
	dic = fopen("sozluk.txt", "r");
	rel = fopen("double.txt", "r+");

     int i=0;

char di[121];
     for(i=0;i<121;i++)
     di[i]=' ';
     di[119]='\0';

   strcpy(ingilizce,sorgu);
   int hHash=Hash();

char dd;
int kk=0;
int kontrol=0;
     for( i=0; i<=hashBoyutu+hHash; i++)
	{


	fseek(rel,(((Hash()%hashBoyutu)+(kk*Hash1())+kk/10000 )%hashBoyutu  *120  )+1,0);

	  kk++;
    fgets(dizi,120,rel);

    strncpy(ingilizce,dizi,36);
    ingilizce[ing_boyut()] = '\0';



  if(strcmp(ingilizce,sorgu)==0)
     {
       puts(dizi);
       kk--;
       fseek(rel,(((Hash()%hashBoyutu)+(kk*Hash1())+kk/10000 )%hashBoyutu  *120  )+1,0);
        fprintf(rel,di);
       printf("\n Silindi dongu sayisi %d",i);
       i= hashBoyutu+hHash;
       kontrol=1;
     }

	}
	if(kontrol==0)
         printf("\n* Kelime Bulunamadi !!!");

	fclose(rel);
	fclose(dic);
	getch();

}

//------------------------
void HashBuyuklukSec() {printf("Hash Buyuklugunu giriniz : "); scanf("%d",&hashBoyutu);}

void RelativeOlustur() {


 	LineerRelativeOlustur();
    QuadraticRelativeOlustur();
	DoubleRelativeOlustur();

}

//---------bonuslar--------
void OrtalamaSorgu (){} //sorgu.txt icin ortalama sorgu zamanını ekranda gösterir

void ArdisilLookUpOrtalamaSorgu (){} //sorgu.txt'in ardısıl lookup tablosu üzerindeki ortalama sorgu zamanını ekranda gösterir

void BinaryLookUpOrtalamaSorgu (){} //sorgu.txt'in ardısıl lookup tablosu üzerindeki ortalama sorgu zamanını ekranda gösterir
//---------------------------

int main(int argc, char* argv[])
{
	HashBuyuklukSec();
	RelativeOlustur();




char s;
	do
	{
		system("cls");

		printf(" \n");
		printf(" SOZLUK UYGULAMASI\n\n");
		printf(" [1] KELIME SORGULA \n");
		printf(" [2] KELIME EKLE\n");
		printf(" [3] KELIME SIL \n");
		printf(" [4] EXIT \n");
		printf(" \n SECIMINIZ [1..3] = ");

		s=getch();

		switch(s)
		{
			case '1' :
        system("cls");
        printf("  KELIME SORGULA \n");
		printf(" [1] Lineer KELIME SORGULA\n");
		printf(" [2] Quadratic KELIME SORGULA \n");
        printf(" [3] Double KELIME SORGULA \n");
             s=getch();

              if(s=='1') LineerKelimeSorgula();
              if(s=='2') QuadraticKelimeSorgula();
              if(s=='3') DoubleKelimeSorgula();
                break;
			case '2' :

			      system("cls");
        printf("  KELIME EKLE \n");
		printf(" [1] Lineer KELIME EKLE\n");
		printf(" [2] Quadratic KELIME EKLE \n");
        printf(" [3] Double KELIME EKLE \n");
             s=getch();

              if(s=='1') LineerKelimeEkle();
              if(s=='2') QuadraticKelimeEkle();
              if(s=='3') DoubleKelimeEkle();
                break;

			case '3' :

			     system("cls");
        printf("  KELIME Sil \n");
		printf(" [1] Lineer KELIME Sil\n");
		printf(" [2] Quadratic KELIME Sil \n");
        printf(" [3] Double KELIME Sil \n");
             s=getch();

              if(s=='1') LineerKelimeSil();
              if(s=='2') QuadraticKelimeSil();
              if(s=='3') DoubleKelimeSil();
                break;


			case '4' :	return 1;
		}

	}  while(1);

	return 0;
}


