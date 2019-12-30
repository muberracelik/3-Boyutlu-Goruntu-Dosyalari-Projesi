#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <math.h>
struct baslik_oku
{
    char noktalar[100];

} b[20];
struct koordinatlar
{
    float x,y,z;
    int r,g,b;
} nokta[100000];
struct kontrol
{
    int nkt_kontrol;
    int alanlar_kontrol;
    int nokta_sayisi;
    int satir_sayisi_kontrol;
    int ascii_kontrol;
    int binary_kontrol;
    int noktalar_kontrol;
    int alan_uzunlugu;
    int veri_kontrol;
    int satir;
} k;

int dosya_uzantisi(char *buf,FILE *output);
int alanlar_baslik_oku(char *dosya_yolu,FILE *output);
int satir_hesaplama(char *dosya_yolu,FILE *output);
int noktalar_baslik_oku(char *dosya_yolu,FILE *output);
int ascii_baslik_oku(char *dosya_yolu,FILE *output);
int dosya_oku(char *dosya_yolu,FILE *output);
void enYakinEnUzakNokta(char *dosya_yolu,FILE *output);
void uzakliklerin_ortalamasi(char *dosya_yolu,FILE *output);
void kure_hesaplama(char *dosya_yolu,FILE *output);
void kup_hesaplama(char *dosya_yolu,FILE *output);
int main()
{
    DIR *kl;
    struct dirent *dir;
    kl = opendir(".\\dosyalar");
    if (kl)
    {
        while ((dir = readdir(kl)) != NULL)
        {

            if (dir->d_name[0] != '.' )
            {
                char dosya_yolu[1000];
                sprintf (dosya_yolu, "%s\\%s", ".\\dosyalar", dir->d_name);

                FILE *output=fopen("output.nkt","a");
                char *buf;
                buf=dir->d_name;
                printf("%s\n",dir->d_name);
                fprintf(output,"%s\n",dir->d_name);
                int secim;

                while(1)
                {
                    printf("1-5 arasi secim yapiniz.");
                    scanf("%d",&secim);
                    int hatali=0;
                    switch(secim)
                    {
                    case 1:
                        fputs("SECIM 1:\n",output);
                        k.nkt_kontrol = dosya_uzantisi(buf,output);

                        if(k.nkt_kontrol==0)
                        {
                            printf("Dosya nkt dosyasi degildir.\n");
                            fputs("Dosya nkt dosyasi degildir.\n",output);

                            hatali=1;
                            break;
                        }

                        else
                        {
                            k.noktalar_kontrol=noktalar_baslik_oku(dosya_yolu,output);
                            if(k.noktalar_kontrol!=1)
                            {
                                printf("Nokta sayilari esit degildir.\n");
                                fputs("Nokta sayilari esit degildir.\n",output);
                                hatali=1;
                                break;
                            }
                            else
                            {
                                k.ascii_kontrol = ascii_baslik_oku(dosya_yolu,output);
                                if(k.ascii_kontrol==0)
                                {
                                    printf("Data binarydir.\n");
                                    fputs("Data binarydir.\n",output);
                                    hatali=1;
                                    break;

                                }
                                else
                                {
                                    k.veri_kontrol=dosya_oku(dosya_yolu,output);
                                    if(k.veri_kontrol==-1)
                                    {
                                        printf("Dosya uyumsuzdur.\n");
                                        fputs("Dosya uyumsuzdur.\n",output);
                                        hatali=1;
                                        break;
                                    }
                                    else
                                    {
                                        printf("Dosya uyumludur.\n");
                                        fputs("Dosya uyumludur.\n",output);

                                    }
                                }

                            }
                        }

                        break;
                    case 2:
                        fputs("SECIM 2:\n",output);
                        enYakinEnUzakNokta(dosya_yolu,output);
                        break;
                    case 3:
                        fputs("SECIM 4:\n",output);
                        kup_hesaplama(dosya_yolu,output);
                        break;
                    case 4:
                        fputs("SECIM 3:\n",output);
                        kure_hesaplama(dosya_yolu,output);
                        break;
                    case 5:
                        fputs("SECIM 5:\n",output);
                        uzakliklerin_ortalamasi(dosya_yolu,output);
                        hatali=1;
                        break;



                    }
                    if(hatali==1)
                    {
                        break;
                    }
                    printf("\n");
                    fputs("\n",output);
                }


                fclose(output);


            }

        }
        closedir(kl);
    }
    return 0;
}
int dosya_uzantisi(char *buf,FILE *output)
{
    char *pr;
    pr=strtok(buf,".");
    //printf("%s\n",pr);
    pr=strtok(NULL," ");
    //printf("%s",pr);
    if(strcmp(pr,"nkt")==0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int alanlar_baslik_oku(char *dosya_yolu,FILE *output)
{
    FILE *dosya= fopen(dosya_yolu,"r");
    //printf("%s\n",dosya_yolu);
    char line[100];
    for(int i=0; i<2; i++)
    {
        fgets(line,100,dosya);
        //printf("%s",line);
    }
    fgets(line,100,dosya);
    //printf("%s",line);
    char *pr;
    pr=strtok(line," ");
    //printf("%s",pr);
    pr=strtok(NULL," ");
    if(strcmp(pr,"xy")==0)
    {
        //printf("Bu dosya okunamaz.");
        return 0;

    }
    pr=strtok(NULL," ");
    if(strcmp(pr,"yz")==0)
    {
        //printf("Bu dosya okunamaz.");
        return 0;

    }
    pr=strtok(NULL," ");
    if(strcmp(pr,"zr")==0)
    {
        //printf("Bu dosya okunamaz.");
        return 0;

    }
    pr=strtok(NULL," ");
    if(strcmp(pr,"rg")==0)
    {
        //printf("Bu dosya okunamaz.");
        return 0;

    }
    pr=strtok(NULL," ");

    if(strcmp(pr,"gb")==0)
    {
        //printf("Bu dosya okunamaz.");
        return 0;
    }


    if(strcmp(pr,"b"))
    {
        return 1;
    }


    fclose(dosya);
}
int noktalar_baslik_oku(char *dosya_yolu,FILE *output)
{
    FILE *dosya= fopen(dosya_yolu,"r");
    //printf("%s\n",dosya_yolu);

    char line[100];
    for(int i=0; i<3; i++)
    {
        fgets(line,100,dosya);
        //printf("%s",line);
    }
    fgets(line,100,dosya);
    //printf("%s",line);

    char *pr;
    pr=strtok(line," ");
    //printf("%s\n",pr);
    pr=strtok(NULL," ");
    //printf("%s",pr);
    k.nokta_sayisi=atoi(pr);
    //printf("%d",k.nokta_sayisi);
    k.satir_sayisi_kontrol=satir_hesaplama(dosya_yolu,output);
    //printf("%d",k.satir_sayisi_kontrol);
    fclose(dosya);

    if(k.nokta_sayisi==k.satir_sayisi_kontrol)
        return 1;
}
int satir_hesaplama(char *dosya_yolu,FILE *output)
{
    //printf("%s\n", dosya_yolu);

    FILE *dosya = fopen(dosya_yolu, "r");
    int satir=0;
    char line[100];
    for(int i=0; i<5; i++)
    {
        fgets(line,100,dosya);
    }
    while(fgets(line,100,dosya)!=NULL)
    {
        satir++;
    }


    fclose(dosya);
    return satir;
//    printf("%d, %d, %d", satir_uzunlugu, k.alan_uzunlugu, satir_sayisi);
}
int ascii_baslik_oku(char *dosya_yolu,FILE *output)
{
    FILE *dosya= fopen(dosya_yolu,"r");
    //printf("%s\n",dosya_yolu);

    char buf[100];
    for(int i=0; i<4; i++)
    {
        fgets(buf,100,dosya);
        //printf("%s",buf);
    }
    fgets(buf,100,dosya);
    //printf("%s",buf);

    char *pr;
    char dizi[5];
    pr=strtok(buf," ");
    //printf("%s\n",pr);
    pr=strtok(NULL," ");
    //printf("%s\n",pr);



    for(int j=0; j<5; j++)
    {
        dizi[j]=*(pr+j);
        //printf("%c\n",dizi[j]);
    }

    for(int j=0; j<5; j++)
    {
        *(pr+j)=dizi[j];
        if(*(pr+4)==dizi[4])
        {
            *(pr+5)='\0';
        }
    }
    //printf("%s\n",pr);
    if(strcmp(pr,"ascii")==0)
    {
        //printf("data asciidir\n");
        return 1;
    }
    else
    {
        //printf("data ascii degildir");
        return 0;
    }


    fclose(dosya);

}
int dosya_oku(char *dosya_yolu,FILE *output)
{
    //printf("%s\n", dosya_yolu);

    FILE *dosya = fopen(dosya_yolu, "r");


    char line[100];
    int i;
    fgets(line,"%s",dosya);
    //printf("%s",line);
    fgets(line,"%s",dosya);
    //printf("%s",line);

    fgets(line,"%s",dosya);
    //printf("%s",line);



    if(strcmp(line,"ALANLAR x y z r g b\n")==0)
    {
        k.alan_uzunlugu=6;
        // k.uzunluk=6;
    }
    else if(strcmp(line,"ALANLAR x y z\n")==0)
    {
        k.alan_uzunlugu=3;
        // k.uzunluk=3;
    }
    else if(strcmp(line,"ALANLAR r g b\n")==0)
    {
        k.alan_uzunlugu=3;
        // k.uzunluk=3;
    }

    fgets(line,"%s",dosya);
    fgets(line,"%s",dosya);




    char *token;
    int satir_sayisi=0;

    while(fgets(line, 100, dosya)!=NULL)
    {
        satir_sayisi++;

        token=strtok(line, " ");
        nokta[satir_sayisi].x = atof(token);

        int satir_uzunlugu = 1;

        while( token != NULL )
        {

            //printf( " %s\n", token );
            token = strtok(NULL, " ");

            if (token == NULL)
            {
                break;

            }
            satir_uzunlugu++;

            if(satir_uzunlugu==2)
            {
                nokta[satir_sayisi].y = atof(token);

            }
            if(satir_uzunlugu==3)
            {
                nokta[satir_sayisi].z = atof(token);

            }
            if(satir_uzunlugu==4)
            {
                nokta[satir_sayisi].r = atoi(token);
            }
            if(satir_uzunlugu==5)
            {
                nokta[satir_sayisi].g = atoi(token);

            }
            if(satir_uzunlugu==6)
            {
                nokta[satir_sayisi].b = atoi(token);

            }

        }


        // printf("%f %f %f %d %d %d\n",nokta[satir_sayisi].x,nokta[satir_sayisi].y,nokta[satir_sayisi].z,nokta[satir_sayisi].r,nokta[satir_sayisi].g,nokta[satir_sayisi].b);


        if(satir_uzunlugu != k.alan_uzunlugu)
        {

            printf("%d. satirda hata var\n",satir_sayisi);
            fprintf(output,"%d. satirda hata var\n",satir_sayisi);
            //printf("%d, %d, %d", satir_uzunlugu, k.alan_uzunlugu, satir_sayisi);
            return -1;
        }
    }


    fclose(dosya);

//    printf("%d, %d, %d", satir_uzunlugu, k.alan_uzunlugu, satir_sayisi);
    return 0;
}
void enYakinEnUzakNokta(char *dosya_yolu,FILE *output)
{
    k.satir=k.satir_sayisi_kontrol;
    float uzaklik;
    int j,i;
    i=1;
    float enk =sqrt(pow(fabs((nokta[k.satir-1].x-nokta[k.satir-2].x)),2) + pow(fabs((nokta[k.satir-1].y-nokta[k.satir-2].y)),2) + pow(fabs((nokta[k.satir-1].z-nokta[k.satir-2].z)),2));
    float enb =sqrt(pow(fabs((nokta[k.satir-1].x-nokta[k.satir-2].x)),2) + pow(fabs((nokta[k.satir-1].y-nokta[k.satir-2].y)),2) + pow(fabs((nokta[k.satir-1].z-nokta[k.satir-2].z)),2));
    int enk_satir=k.satir-1;
    int enk_satir1=k.satir-2;

    int enb_satir=k.satir-1;
    int enb_satir1=k.satir-2;
    while(i<k.satir)
    {

        for(j=i+1; j<k.satir+1; j++)
        {

            uzaklik=sqrt(pow(fabs((nokta[i].x-nokta[j].x)),2) + pow(fabs((nokta[i].y-nokta[j].y)),2) + pow(fabs((nokta[i].z-nokta[j].z)),2));

            if(enk>uzaklik)
            {
                enk=uzaklik;
                enk_satir=i;
                enk_satir1=j;
            }
            if(enb<uzaklik)
            {
                enb=uzaklik;
                enb_satir=i;
                enb_satir1=j;
            }


        }
        i++;
    }
    printf("%f\n %d. %f %f %f\n %d. %f %f %f\n ",enk,enk_satir,nokta[enk_satir].x,nokta[enk_satir].y,nokta[enk_satir].z,enk_satir1,nokta[enk_satir1].x,nokta[enk_satir1].y,nokta[enk_satir1].z);
    fprintf(output,"%f\n %d. %f %f %f\n %d. %f %f %f\n ",enk,enk_satir,nokta[enk_satir].x,nokta[enk_satir].y,nokta[enk_satir].z,enk_satir1,nokta[enk_satir1].x,nokta[enk_satir1].y,nokta[enk_satir1].z);
    printf("%f\n %d. %f %f %f\n %d. %f %f %f\n",enb,enb_satir,nokta[enb_satir].x,nokta[enb_satir].y,nokta[enb_satir].z,enb_satir1,nokta[enb_satir1].x,nokta[enb_satir1].y,nokta[enb_satir1].z);
    fprintf(output,"%f\n %d. %f %f %f\n %d. %f %f %f\n",enb,enb_satir,nokta[enb_satir].x,nokta[enb_satir].y,nokta[enb_satir].z,enb_satir1,nokta[enb_satir1].x,nokta[enb_satir1].y,nokta[enb_satir1].z);

}
void uzakliklerin_ortalamasi(char*dosya_yolu,FILE *output)
{
    k.satir=k.satir_sayisi_kontrol;
    float toplam_uzaklik=0;
    float uzaklik;
    int i,j;
    i=1;
    int sayac_islem=0;
    while(i<k.satir)
    {

        for(j=i+1; j<k.satir+1; j++)
        {
            uzaklik=sqrt(pow(fabs((nokta[i].x-nokta[j].x)),2) + pow(fabs((nokta[i].y-nokta[j].y)),2) + pow(fabs((nokta[i].z-nokta[j].z)),2));
            toplam_uzaklik+=uzaklik;
            sayac_islem++;
        }

        i++;
    }

    float ortalamalar=toplam_uzaklik/sayac_islem;
    printf("%f\n",ortalamalar);
    fprintf(output,"%f\n",ortalamalar);


}
void kure_hesaplama(char *dosya_yolu,FILE *output)
{
    k.satir=k.satir_sayisi_kontrol;
    float ax,by,cz,r;
    printf("kurenin x y z degerlerini giriniz.\n");
    scanf("%f %f %f",&ax,&by,&cz);
    printf("kurenin yaricapini giriniz.\n");
    scanf("%f",&r);
    float uzaklik;
    float kare_toplam;
    for(int i=1; i<k.satir; i++)
    {
        kare_toplam= pow(nokta[i].x-ax,2) + pow(nokta[i].y-by,2) + pow(nokta[i].z-cz,2);
        uzaklik=sqrt(kare_toplam);
        if(uzaklik<=r)
        {
            printf("%d. %f %f %f\n",i,nokta[i].x,nokta[i].y,nokta[i].z);
            fprintf(output,"%d. %f %f %f\n",i,nokta[i].x,nokta[i].y,nokta[i].z);
        }
    }


}
void kup_hesaplama(char *dosya_yolu,FILE *output)
{
    k.satir=k.satir_sayisi_kontrol;
    dosya_oku(dosya_yolu,output);
    int i=1,j;
    float uzaklik;
    float ayrit;
    float enk_x=nokta[0].x,enk_y=nokta[0].y,enk_z=nokta[0].z;
    float enb_x=nokta[0].x,enb_y=nokta[0].y,enb_z=nokta[0].z;
    while(i<k.satir)
    {

        if(nokta[i].x<=enk_x)
        {
            enk_x=nokta[i].x;
        }

        if(nokta[i].y<=enk_y)
        {
            enk_y=nokta[i].y;
        }

        if(nokta[i].z<=enk_z)
        {
            enk_z=nokta[i].z;
        }


        if(nokta[i].x>=enb_x)
        {
            enb_x=nokta[i].x;
        }

        if(nokta[i].y>=enb_y)
        {
            enb_y=nokta[i].y;
        }

        if(nokta[i].z>=enb_z)
        {
            enb_z=nokta[i].z;
        }


        i++;
    }


    uzaklik=sqrt(pow((enb_x-enk_x),2) + pow((enb_y-enk_y),2) + pow((enb_z-enk_z),2));
   // printf("%f\n",uzaklik);

    ayrit=uzaklik/sqrt(3);
   // printf("%f\n",ayrit);
    float kose1=enk_x+ayrit;
    float kose2=enk_y+ayrit;
    float kose3=enk_z+ayrit;
    float kose4=enb_x-ayrit;
    float kose5=enb_y-ayrit;
    float kose6=enb_z-ayrit;

    printf("%f %f %f\n",enk_x,enk_y,enk_z);
    fprintf(output,"%f %f %f\n",enk_x,enk_y,enk_z);
    printf("%f %f %f\n",kose1,enk_y,enk_z);
    fprintf(output,"%f %f %f\n",kose1,enk_y,enk_z);
    printf("%f %f %f\n",enk_x,kose2,enk_z);
    fprintf(output,"%f %f %f\n",enk_x,kose2,enk_z);
    printf("%f %f %f\n",enk_x,enk_y,kose3);
    fprintf(output,"%f %f %f\n",enk_x,enk_y,kose3);
    printf("%f %f %f\n",kose4,enb_y,enb_z);
    fprintf(output,"%f %f %f\n",kose4,enb_y,enb_z);
    printf("%f %f %f\n",enb_x,kose5,enb_z);
    fprintf(output,"%f %f %f\n",enb_x,kose5,enb_z);
    printf("%f %f %f\n",enb_x,enb_y,kose6);
    fprintf(output,"%f %f %f\n",enb_x,enb_y,kose6);
    printf("%f %f %f\n",enb_x,enb_y,enb_z);
    fprintf(output,"%f %f %f\n",enb_x,enb_y,enb_z);

}

