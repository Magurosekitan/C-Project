
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphics.h>
#include <math.h>



int shoelace_area(int *x, int *y, int n) {
  int area = 0;
  int i; 
  for (i = 0; i < n - 1; i++) {
    area += x[i] * y[i + 1] - x[i + 1] * y[i];
  }
  area += x[n - 1] * y[0] - x[0] * y[n - 1]; 
  area = abs(area) / 2; 
  return area; 
}


int main()
{
    
    system("curl http://bilgisayar.kocaeli.edu.tr/prolab1/prolab1.txt > veri.txt");
    FILE *dosya = fopen("veri.txt", "r");
    if (dosya == NULL) {
        printf("Dosya açma hatasý");
        return 1;
    }
    int satir1;
    printf("Hangi satiri istiyorsun?");
    scanf("%d",&satir1);
    int BSM;
    printf("Birim Sondaj Maliyetini giriniz:");
    scanf("%d",&BSM);
   int hedef_satir = satir1; 
    int satir_sayaci = 0;
    int indeks= 0;
    int x,y;
    int i;
    int xDizi[10];
    int yDizi[10];
    char satir[256]; // Satýrýn maksimum uzunluðu


    while (fgets(satir, sizeof(satir), dosya) != NULL) {
        satir_sayaci++;
        if (satir_sayaci == hedef_satir) {
        	
            //printf("Okunan satir: %s", satir);
           	break; 
        }
    }
    
    int j=0;    
    char *ptr = strstr(satir, "B");
    if (ptr != NULL) {
        ptr++; // 'B' karakterinin sonundan baþlamak için
        while (*ptr != 'F') {
            if (sscanf(ptr, "(%d,%d", &x, &y) == 2) {
                xDizi[indeks] = x;
                yDizi[indeks] = y;
                indeks++;
                ptr++;
                j++;
            } else {
                ptr++;
            }
        }
    }

    //int gd = DETECT, gm;
    //initgraph(&gd, &gm, "");
    
    initwindow(5000,1000);
     int unitSize = 10;  // Birim kare boyutu (10x10 piksel)

   
    setbkcolor(BLACK);
    cleardevice();

    setcolor(BLUE);
    for (int x = 0; x < getmaxx(); x += unitSize) {
        line(x, 0, x, getmaxy());
    }
    for (int y = 0; y < getmaxy(); y += unitSize) {
        line(0, y, getmaxx(), y);
    }
    
    int add;
    
    setcolor(WHITE);
    line(10*xDizi[0], 10*yDizi[0],10* xDizi[1], 10*yDizi[1]);
    int Kenar=0;
    int Kenar2=0;
    int Alan;
    int sayac=0;
    int First;
	for (i = 1; i < indeks - 1; i++) {
		if(xDizi[0] == xDizi[i] && yDizi[0] == yDizi[i])
		{
			Kenar = i;
			sayac = 1;
			continue;
		}
       	else
       	First=i+1;//eðer tek þekil varsa o þeklin kenar sayýsý veriyor
	    line(10*xDizi[i], 10*yDizi[i], 10*xDizi[i + 1],10* yDizi[i + 1]);
        
    }
  //  printf("%d\n",i);
	int n,m,r=0,t=0;
    
    
    Kenar2=i - Kenar-1;
    int k=0;
    int xcont[Kenar2];
    int ycont[Kenar2];
    int l = Kenar+1;
    while(k<Kenar2)
    {
    	xcont[k] = xDizi[l];
    	ycont[k] = yDizi[l];
    	k++;
    	l++;
	}
	//printf("%d\n",Kenar);
	

   if(sayac == 1)
    {
    int firstColor[2*Kenar];
    Alan=shoelace_area(xDizi,yDizi,Kenar);
    printf("1.Alan= %d\n",Alan);
    Alan=shoelace_area(xcont,ycont,Kenar2);
    printf("2. alan:%d\n ",Alan);
    
    
    for(n = 0; n<2*Kenar; n++){
    	firstColor[n]=10*xDizi[r];
    	n++;
    	firstColor[n]=10*yDizi[r];
    	r++;
	}
	setfillpattern("\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF", RED); // dolgu stili ve rengi
    fillpoly(Kenar, firstColor); // dörtgenin içini kýrmýzýyla boyama
    
    
    int secondColor[2*Kenar2];
    for(m = 0; m<2*Kenar2; m++){
    	secondColor[m]=10*xcont[t];
    	m++;
    	secondColor[m]=10*ycont[t];
    	t++;
	}
	setfillpattern("\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF", BLUE); // dolgu stili ve rengi
    fillpoly(Kenar2, secondColor); // þeklin içini boyamaya yarar
	
	}
	
	else 
	{
		Alan=shoelace_area(xDizi,yDizi,First);
		//printf("%d\n",First);
    	printf("Alan= %d\n",Alan);
    	int firstColor[2*i];
    for(n = 0; n<2*i; n++){
    	firstColor[n]=10*xDizi[r];
    	n++;
    	firstColor[n]=10*yDizi[r];
    	r++;
	}
	setfillpattern("\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF", RED);
    fillpoly(i, firstColor);
    	
	}


    getch();// kullanýcý bir tuþa bastýðýnda ekraný kapatýr

    closegraph(); // Grafik penceresini kapat

    fclose(dosya);
    return 0;
}










