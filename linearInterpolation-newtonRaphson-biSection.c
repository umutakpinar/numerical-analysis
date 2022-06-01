#include "stdio.h"
#include "stdlib.h"
#include "math.h"

#define STARTPOINT 2 // a
#define ENDPOINT 12  // b
//[a,b] -> [2,12]

double error = 0.02;
double koklerIkiyeBolme[10]; //İkiye bölme methoduyla elde ettiğim kökler
double errIkiyeBolme[10];    // İkiye bölme metodu error değerleri

double koklerNewtonRaphson[10];
double errNewtonRaphson[10];

double koklerLineerInterpolasyon[10];
double errLineerInterpolasyon[10];

double f(double x) // fonksiyonum
{
    return 0.85 * x * x - 2.14 * x;
}

double df(double x) // fonksiyonumun 1. dereceden türevi
{
    return 1.7 * x - 2.14;
}

double ikiyeBolme(double a, double b)
{
    double c; // orta kök tutucu
    for (int i = 1; i <= 10; i++)
    {
        if (f(a) * f(b) < 0) // Kapalı aralıkta kök kontrolü
        {
            c = (a + b) / 2;             // i. adımdaki kök
            koklerIkiyeBolme[i - 1] = c; // i. adımdaki kökü kökler dizime kaydet

            errIkiyeBolme[i - 1] = (double)(c - a) / pow((double)2, (double)i); // Hata değerimi ve adım sayımı kaydettim

            if (f(b) * f(c) < 0) // demek ki kök ortadaki değer ile b arasında
            {
                a = c; // o halde yeni a değerim c olmalı
            }
            else if (f(a) * f(c) < 0) // demek ki kök a ve ortadaki değer arasında o halde
            {
                b = c; // yeni b değerim c olmalı
            }
        }
        else // Daha ilk adımda dahi kök yok demek ki ikiye bölme metodu uygulanamaz
        {
            break; // döngüyü kır
        }
    }
}

double newtonRaphson(double a, double b, double x0)
{
    double c = x0;
    for (int i = 1; i <= 10; i++)
    {
        c = c - (f(c) / df(c));                 // bir sonraki adımda kullanılacak olan kök adayımı bul (aslında her adımda bir sonraki kökü hesaplamış olduk, bu adımın hata değerinin bulabilmek adına)
        koklerNewtonRaphson[i - 1] = c;         // kökü kaydet (bu adımdaki (aslında bir önceki adımda hesaplanan) kökümü kaydet)
        errNewtonRaphson[i - 1] = fabs(c - x0); // yeni kökten ilk kökü çıkartıp mutlak değer içine al o adımdaki hata değerini kaydet
        x0 = c;                                 // artık c benim eski köküm bu nedenle onu kaydettim ki bir sonraki iterasyonun en sonunda farklarını alırken yaparken kullanabileyim
    }
}

double lineerInterpolasyon(double a, double b)
{
    double c = ((a * f(b)) - (b * f(a))) / (f(b) - f(a)); // ilk kök değerimi hesapladım ( c benim kök tutucum)
    for (int i = 1; i <= 10; i++)
    {
        koklerLineerInterpolasyon[i - 1] = c; // kök değerimi kaydettim
        if (c > 0)                            // aralıktaki kök pozitif ise yeni b değerim c olmalı
        {
            b = c;
        }
        else if (c < 0) // aralıktaki kök negatif ise yeni a değerim c olmalı
        {
            a = c;
        }
        c = ((a * f(b)) - (b * f(a))) / (f(b) - f(a));                              // yeni kök değerimi hesapladım ancak henüz kaydetmedim bir sonraki adım başlayınca kaydedecek bu adımda bir sonraki adımın kök değerinii hesaplamamın nedeni hata dğerini bulmak istememden kaynaklı
        errLineerInterpolasyon[i - 1] = fabs(c - koklerLineerInterpolasyon[i - 1]); // bir sonraki adımın kök değerinden şuanki adımın kök değerini mutalk değer içerisinde çıkarttım ve sonucu bu adımın error değeri olarak kaydettim.
    }
}

int main()
{

    ikiyeBolme(STARTPOINT, ENDPOINT);                //[a,b] -> [2,12]
    newtonRaphson(STARTPOINT, ENDPOINT, STARTPOINT); //[a,b ve x0] -> [2,12 ve x0 = 2] Ödev açıklamasında ilk sayfada x0 değerinin 2 seçilmesi gerektiği belirtilmiş ancak 2. sayfada 12 denilmiş ben 2 yani aralığın min değerini aldım.
    lineerInterpolasyon(STARTPOINT, ENDPOINT);       //[a,b] -> [2,12]

    printf("                               İkiye Bölme Metodu         /       Newton Raphson Metodu      /       Lineer Interpolasyon Metodu\n\n");
    printf("#n. iterasyon :                 kök   ->     e            /          kök   ->     e          /             kök   ->     e       \n");
    for (int i = 1; i <= 10; i++)
    {
        if (i == 10)
        {
            printf("#%d. iterasyon :             %f ->  %f        /       %f ->  %f      /          %f ->  %f\n", i, koklerIkiyeBolme[i - 1], errIkiyeBolme[i - 1], koklerNewtonRaphson[i - 1], errNewtonRaphson[i - 1], koklerLineerInterpolasyon[i - 1], errLineerInterpolasyon[i - 1]);
        }
        else
        {
            printf("#%d. iterasyon :              %f ->  %f        /       %f ->  %f      /          %f ->  %f\n", i, koklerIkiyeBolme[i - 1], errIkiyeBolme[i - 1], koklerNewtonRaphson[i - 1], errNewtonRaphson[i - 1], koklerLineerInterpolasyon[i - 1], errLineerInterpolasyon[i - 1]);
        }
    }

    int sayac1 = 0;
    int sayac2 = 0;
    int sayac3 = 0;

    for (int i = 0; i <= 9; i++)
    {
        if (errIkiyeBolme[i] < error)
        {
            if (sayac1 == 0)
            {
                sayac1++;
                printf("\nİkiye Bölme Metodu ile %.2f den daha küçük bir hata değerine %d. iterasyonda ulaşılmıştır. (Kök : %f)", error, i + 1, koklerIkiyeBolme[i]);
            }
        }

        if (errNewtonRaphson[i] < error)
        {
            if (sayac2 == 0)
            {
                sayac2++;
                printf("\nNewton Raphson Metodu ile %.2f den daha küçük bir hata değerine %d. iterasyonda ulaşılmıştır. (Kök : %f)", error, i + 1, koklerNewtonRaphson[i]);
            }
        }

        if (errLineerInterpolasyon[i] < error)
        {
            if (sayac3 == 0)
            {
                sayac3++;
                printf("\nLineer İnterpolasyon Metodu ile %.2f den daha küçük bir hata değerine %d. iterasyonda ulaşılmıştır. (Kök : %f)", error, i + 1, koklerLineerInterpolasyon[i]);
            }
        }
    }
    return 0;
}
