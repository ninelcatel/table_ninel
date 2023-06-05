#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;
char a[20][20];
int alb[25],ngr[25];
int k=0,x=1,y=1;
int bar_negru=0;
int bar_alb=0;
int punct_negru,punct_alb;
char j1[15], j2[15];
// ////////////////////ZAR
void citire_alegere(int &alegere)
{
     if(alegere!=1 && alegere!=2)
                    {
                        cout<<"Ai introdus un numar gresit , te rog scrie 1 sau 2"<<endl;
                        cin>>alegere;
                        citire_alegere(alegere);
                        return;
                    }
}
int suma_vector(int v[])
{
    unsigned int s=0;

    for(int i=1; i<=24; i++)
        s+=v[i];
    return s;
}
int roll()
{
    srand(time(0));
    return (1 + (rand() % 6));


}
int roll2()
{
    srand(time(0)+1);
    return (1 + (rand() % 6));


}
void zar()
{
    cout << roll()<<" Primul zar"<<endl<<roll2()<<" Al doilea zar"<<endl<<" Scrie 1 pentru a folosi primul zar sau 2 pentru a folosi al doilea zar "<<endl;
}
//
//
//
//
/////////////////////JOC
//
//
//
//
//

void afiseazatabla()
{
    for (int i = 0; i <= 13; i++)
    {
        for (int j = 0; j <= 13; j++)
        {
            if(j==7) cout<<"| |";
            if (a[i][j] == '1')  cout << 'A';
            else if (a[i][j] == '2')cout << 'N';
            else cout << a[i][j];
        }
        cout << endl;
    }
}
void afisaretablainitiala()
{
    int i, j;                 
    for (i = 0; i <= 13; i++)      
        for (j = 0; j <= 13; j++)
        {
            if (i == 0  || j == 0 || j == 13 || i==13) a[i][j] = ' #';          //pls dont judge my way of creating the gameboard.
            else if (i > 0 && i < 6 && j == 1) a[i][j] = '1';
            else if (i > 0 && i < 3 && j == 12) a[i][j] = '1';
            else if (i > 9 && i < 13 && j == 5) a[i][j] = '1';
            else if (i > 7 && i < 13 && j == 7) a[i][j] = '1';
            else if (i > 7 && i < 13 && j == 1) a[i][j] = '2';
            else if (i > 10 && i < 13 && j == 12) a[i][j] = '2';
            else if (i > 0 && i < 4 && j == 5) a[i][j] = '2';
            else if (i > 0 && i < 6 && j == 7) a[i][j] = '2';
            else a[i][j] = ' ';

        }
    afiseazatabla();
}
void numarare_piese_albe()
{
    for(int i=1; i<=24; i++) alb[i]=0;
    for(int i=1; i<=6; i++)
    {
        for(int j=1; j<=12; j++) if(a[i][j]=='1') alb[j]++;
    }
    for(int i=7; i<=12; i++)
        for(int j=1; j<=12; j++) if(a[i][j]=='1') alb[12+j]++;

}
void numarare_piese_negre()
{
    for(int i=1; i<=24; i++) ngr[i]=0;
    for(int i=1; i<=6; i++)
    {
        for(int j=1; j<=12; j++) if(a[i][j]=='2') ngr[j]++;
    }
    for(int i=7; i<=12; i++)
        for(int j=1; j<=12; j++) if(a[i][j]=='2') ngr[12+j]++;

}
int Check_pul_casa_alb()
{
    int s=0;
    numarare_piese_albe();
    for(int i=1; i<=18; i++)
        s+=alb[i];
    return s;
}
int Check_pul_casa_negru()
{
    int s=0;
    numarare_piese_negre();
    for(int i=1;i<=6; i++)
        s+=ngr[i];
    for(int i=13;i<=24;i++)
        s+=ngr[i];
    return s;
}
int check_win_cond_alb()
{
    numarare_piese_albe();
    int s=0;
    for(int i=1; i<=24; i++) s+=alb[i];
    return s;
}
int check_win_cond_negru()
{
    numarare_piese_negre();
    int s=0;
    for(int i=1; i<=24; i++) s+=ngr[i];
    return s;
}
int check_penalty_alb(int zarr)
{
    numarare_piese_negre();
    numarare_piese_albe();
    if(ngr[12-zarr+1]>=2)
    {
        return 0;
    }
    else if(ngr[12-zarr+1]==1)
    {
        bar_negru++;
        bar_alb--;
        a[1][12-zarr+1]='1';
        return 1;
    }
    else
    {
        a[alb[12-zarr+1]+1][12-zarr+1]='1';
        bar_alb--;
        return 1;
    }
}
int check_penalty_negru(int zarr)
{
    numarare_piese_albe();
    numarare_piese_negre();
    if(alb[24-zarr+1]>=2)
    {
        return 0;
    }
    else if(alb[24-zarr+1]==1)
    {
        bar_negru--;
        bar_alb++;
        a[12][12-zarr+1]='2';
        system("CLS");
        afiseazatabla();
        return 1;
    }
    else
    {
        a[12-ngr[24-zarr+1]][12-zarr+1]='2';
        bar_negru--;
        system("CLS");
        afiseazatabla();
        return 1;

    }
}
void scoaterepiesa_alba(int p,int zarr)
{
    if(x%4==0)
    {
        cout<<" 3 mutari invalide, vom trece peste acest zar"<<endl;

        x++;
        return;
    }
    numarare_piese_albe();
    if(alb[p]==0)
    {
        cout<<"Mutare invalida,alege alta coloana"<<endl;

        cin>>p;
        x++;
        scoaterepiesa_alba(p,zarr);
        return;
    }
    if(p+zarr>=25)  a[13-alb[p]][p-12]=' ';

    else if(p>12) //muta din stanga in dr partea jos
    {

        numarare_piese_negre();
        if(ngr[p+zarr]>=2) //CONDITIA DE POARTA
        {
            cout<<"Mutare invalida,alege alta coloana"<<endl;

            cin>>p;
            x++;
            scoaterepiesa_alba(p,zarr);
            return;
        }
        else if (ngr[p+zarr]==1)
        {
            a[13-alb[p]][p-12]=' ';
            a[12-alb[p+zarr]][p+zarr-12]='1';
            bar_negru++;
        }
        else
        {
            a[12-alb[p+zarr]][p+zarr-12]='1';
            a[13-alb[p]][p-12]=' ';
        }
    }

}
void scoaterepiesa_neagra(int p, int zarr)
{
    if(y%4==0)
    {
        cout<<"3 mutari invalide, vom trece peste acest zar"<<endl;

        y++;
        return;
    }
    numarare_piese_negre();
    if(ngr[p]==0)
    {
        cout<<"Mutare invalida,alege alta coloana"<<endl;

        cin>>p;
        y++;
        scoaterepiesa_neagra(p,zarr);
        return;
    }
    if(zarr+p>=13)
    {
        a[ngr[p]][p]=' ';
    }
    else  //st->dr
    {
        numarare_piese_albe();
        if(alb[p+zarr]>=2)
        {
            cout<<"Mutare invalida,alege alta coloana"<<endl;

            cin>>p;
            y++;
            scoaterepiesa_neagra(p,zarr);
            return;
        }
        else if(alb[p+zarr]==1)
        {
            a[ngr[p]][p]=' ';
            a[1+ngr[p+zarr]][p+zarr]='2';
            bar_alb++;
        }
        else
        {
            a[1+ngr[p+zarr]][p+zarr]='2';
            a[ngr[p]][p]=' ';
        }
    }
}
void mutarepiesa_alba(int p,int zarr)
{
    if(x%4==0)
    {
        cout<<" 3 mutari invalide, vom trece peste acest zar"<<endl;

        x++;
        return;

    }
    numarare_piese_albe();
    if(alb[p]==0)
    {
        cout<<"Mutare invalida,alege alta coloana"<<endl;

        cin>>p;
        x++;
        mutarepiesa_alba(p,zarr);
        return;
    }
    else if(zarr-p>=0)//muta de sus in jos gen
    {

        numarare_piese_negre();
        if(ngr[13+zarr-p]>=2)//CONDITIA DE POARTA
        {
            cout<<"Mutare invalida,alege alta coloana"<<endl; // ceva gresit ai uitat sa adaugi cin>>p; (la fiecare mutare invalida, alge alta coloana)

            cin>>p;
            x++;
            mutarepiesa_alba(p,zarr);
            return;
        }
        else if (ngr[13+zarr-p]==1)
        {
            a[alb[p]][p]=' '; 
            a[12-alb[13+(zarr-p)]][1+(zarr-p)]='1';
            bar_negru++;
        }
        else
        {
            a[alb[p]][p]=' '; 
            a[12-alb[13+(zarr-p)]][1+(zarr-p)]='1';
        }
    }
    else if(p<=12)//muta din dr in stanga partea sus
    {

        numarare_piese_negre();
        if(ngr[p-zarr]>=2)//CONDITIA DE POARTA
        {
            cout<<"Mutare invalida,alege alta coloana"<<endl;

            cin>>p;
            x++;
            mutarepiesa_alba(p,zarr);
            return;
        }
        else if (ngr[p-zarr]==1)
        {
            a[alb[p]][p]=' ';
            a[alb[p-zarr]+1][p-zarr]='1';
            bar_negru++;
        }
        else
        {
            a[alb[p]][p]=' ';
            a[alb[p-zarr]+1][p-zarr]='1';
        }
    }
    else if(p>12) //muta din stanga in dr partea jos
    {

        numarare_piese_negre();
        if(ngr[p+zarr]>=2) //CONDITIA DE POARTA
        {
            cout<<"Mutare invalida,alege alta coloana"<<endl;

            cin>>p;
            x++;
            mutarepiesa_alba(p,zarr);
            return;
        }
        else if (ngr[p+zarr]==1)
        {
            a[13-alb[p]][p-12]=' ';
            a[12-alb[p+zarr]][p+zarr-12]='1';
            bar_negru++;
        }
        else
        {
            a[13-alb[p]][p-12]=' ';
            a[12-alb[p+zarr]][p+zarr-12]='1';
        }
    }

}
 void mutarepiesa_neagra(int p,int zarr)//p e numarul coloanei si este numerotat de la stanga  la dreapta 1-12 sus 13-24 jos
{
    if(y%4==0)
    {
        cout<<"3 mutari invalide, vom trece peste acest zar"<<endl;

        y++;
        return;
    }
    numarare_piese_negre();
    if(ngr[p]==0)
    {
        cout<<"Mutare invalida,alege alta coloana"<<endl;

        cin>>p;
        y++;
        mutarepiesa_neagra(p,zarr);
        return;
    }
    else if(p-zarr>=7 && p-zarr<13)//jos in sus
    {
        numarare_piese_albe();
        if(alb[13-p+zarr]>=2)
        {
            cout<<"Mutare invalida,alege alta coloana"<<endl;

            cin>>p;
            y++;
            mutarepiesa_neagra(p,zarr);
            return;
        }
        else if (alb[13-p+zarr]==1)
        {
            a[13-ngr[p]][p-12]=' ';
            a[1+ngr[13-p+zarr]][13-p+zarr]='2';
            bar_alb++;
        }
        else
        {
            a[1+ngr[13-p+zarr]][13-p+zarr]='2';
            a[13-ngr[p]][p-12]=' ';
        }
    }
    else if (p>13)  //dr->st
    {

        numarare_piese_albe();
        if(alb[p-zarr]>=2)
        {
            cout<<"Mutare invalida,alege alta coloana"<<endl;

            cin>>p;
            y++;
            mutarepiesa_neagra(p,zarr);
            return;

        }
        else if(alb[p-zarr]==1)
        {
            a[13-ngr[p]][p-12]=' ';
            a[12-ngr[p-zarr]][p-zarr-12]='2'; // :    ^)
            bar_alb++;
        }
        else
        {
            a[12-ngr[p-zarr]][p-zarr-12]='2';
            a[13-ngr[p]][p-12]=' ';
        }
    }
    else if(p<13) //st->dr
    {

        numarare_piese_albe();
        if(alb[p+zarr]>=2)
        {
            cout<<"Mutare invalida,alege alta coloana"<<endl;

            cin>>p;
            y++;
            mutarepiesa_neagra(p,zarr);
            return;
        }
        else if(alb[p+zarr]==1)
        {
            a[ngr[p]][p]=' ';
            a[1+ngr[p+zarr]][p+zarr]='2';
            bar_alb++;
        }
        else
        {
            a[ngr[p]][p]=' ';
            a[1+ngr[p+zarr]][p+zarr]='2';
        }
    }

}

//
//
//
//
// thinking about what formulas i needed to use was a PAIN.
int main()
{
    cout << "Bine ai venit la Table!" << endl;
        cout << "Numele primului jucator : ";
        cin.getline(j1,15);
        cout << "Numele celui de al doilea jucator : ";
        cin.getline(j2,15);
    bool restart=true;
    int replay;
    while(restart==true)
    {
        int tura = 1;
        int alegere=0,coloana;
        bool castiga_alb = false;
        bool castiga_negru = false;
        int zar1, zar2;

        if(punct_alb==0 && punct_negru==0) cout<<endl;
            else if(punct_alb>punct_negru) cout<<"Scorul este "<<punct_alb<<"-"<<punct_negru<<" pentru "<<j1<<endl;
            else if(punct_alb<punct_negru) cout<<"Scorul este "<<punct_negru<<"-"<<punct_alb<<" pentru "<<j2<<endl;
            else if(punct_alb==punct_negru) cout<<"Scorul este egal"<<endl;

        cout << "Pentru a determina cine va juca primu va trebuie sa dam cu zarul"<<endl;
        do
        {
            zar1 = roll();
            zar2 = roll2();
            cout << j1 << " a dat " << zar1<<endl;
            cout << j2 << " a dat " << zar2<<endl;
            if (zar1 == zar2)
                cout << " Egalitate, se va da din nou cu zarul ";     // they are never equal i thought they would be but was too lazy to find a way to make them random and possibly equal
        }
        while (zar1 == zar2);
        if (zar1 > zar2)cout << j1 << " joaca primu ";
        else if (zar1 < zar2)
        {
            cout << j2 << " joaca primu";
            tura++;
        }
        cout << endl << endl;
        afisaretablainitiala();
        cout<<endl;
        cout<<"Coloanele sunt numerotate de la 1-24 de la stanga la dreapta incepand de sus in jos."<<endl;
        while(castiga_alb!=true || castiga_negru!=true)
        {
            int n=0;
            int n2=0;
            int ok=0;//break sau nu la while
            int ok2=0;
            int ap=0;//verifica care zar mai ai de mutat
            if(tura%2==0 && check_win_cond_alb()==0)
            {
                system("Color 0B");
                cout<<j1<<" CASTIGA,FELICITARI!"<<endl<<"Daca doresti sa joci din nou scrie '1' ,in caz contrariu scrieti orice"<<endl;

                castiga_alb=true;
                break;
            }
            else if(tura%2==1 && check_win_cond_negru()==0)
            {
                system("Color 0B");
                cout<<j2<<" CASTIGA,FELICITARI!"<<endl<<"Daca doresti sa joci din nou scrie '1' ,in caz contrariu scrieti orice"<<endl;

                castiga_negru=true;
                break;
            }
            if(tura%2==1)
            {
                zar1=roll();
                zar2=roll2();

                cout <<"(Primul jucator)"<<endl<<zar1<<" primul zar"<<endl<<zar2<<" al doilea zar"<<endl<<"scrie 1 pentru a folosi primul zar sau 2 pentru a folosi al doilea zar "<<endl;
                while(bar_alb!=0 && ok==0)
                {
                    cout<<"Ai "<<bar_alb<<" piese pe bar, alege un zar pentru a-ti pune piesa inapoi pe masa de joc"<<endl;
                    cin>>alegere;
                    citire_alegere(alegere);
                    if(alegere==1)
                    {
                        if(check_penalty_alb(zar1)==0)
                        {
                            cout<<"Mutare invalida cu primul zar, vom incerca si cu al doilea"<<endl;


                            if(check_penalty_alb(zar2)==0)
                            {

                                cout<<"Nu ai mutari valide"<<endl;

                                ok=1;
                            }
                            else
                            {
                                ap=2;
                                n++;
                                if(n==2)
                                {
                                    ok=1;
                                    break;
                                }
                            }
                        }
                        else
                        {
                            ap=1;
                            n++;
                            if(n==2)
                            {
                                ok=1;
                                break;
                            }
                        }

                    }
                    else if (alegere==2)
                    {
                        if(check_penalty_alb(zar2)==0)
                        {
                            cout<<"Mutare invalida cu al doilea zar, vom incerca si cu primul"<<endl;


                            if(check_penalty_alb(zar1)==0)
                            {

                                cout<<"Nu ai mutari valide"<<endl;

                                ok=1;
                            }
                            else
                            {
                                ap=1;
                                n++;
                                if(n==2)
                                {
                                    ok=1;
                                    break;
                                }
                            }
                        }
                        else
                        {
                            ap=2;
                            n++;
                            if(n==2)
                            {
                                ok=1;
                                break;
                            }
                        }
                    }
                    system("CLS");
                    afiseazatabla();
                }
                if(ok==1) tura++;
                else if(bar_alb==0 && tura%2==1)
                {
                    if(ap==1)// faci mutarea doar cu al doilea zar copy paste
                    {
                        cout<<"Ai ramas cu al doilea zar selecteaza coloana de la care vrei sa muti piesa "<<zar2<<endl;
                        cin>>coloana;
                        numarare_piese_albe();
                        mutarepiesa_alba(coloana,zar2);
                        system("CLS");
                        afiseazatabla();
                        tura++;
                    }
                    else if (ap==2)
                    {
                        cout<<"Ai ramas cu primul zar selecteaza coloana de la care vrei sa muti piesa "<<zar1<<endl;
                        cin>>coloana;
                        numarare_piese_albe();
                        mutarepiesa_alba(coloana,zar1);
                        system("CLS");
                        afiseazatabla();
                        tura++;
                    }
                    else if (ap==0)
                    {
                        cin>>alegere;
                        citire_alegere(alegere);
                        if(Check_pul_casa_alb()==0)
                        {
                            if(alegere==1)
                            {
                                cout<<"Ai ales primul zar selecteaza coloana de la care vrei sa muti piesa"<<endl;
                                cin>>coloana;
                                numarare_piese_albe();
                                scoaterepiesa_alba(coloana,zar1);
                                system("CLS");
                                afiseazatabla();
                                cout<<endl<<"Ai folosit primul zar,acum selecteaa coloana pe care vrei sa o muti cu al doilea "<<zar2<<endl;
                                cin>>coloana;
                                numarare_piese_albe();
                                scoaterepiesa_alba(coloana,zar2);
                                system("CLS");
                                afiseazatabla();
                                tura++;
                            }
                            else if (alegere==2)
                            {
                                cout<<"Ai ales al doilea zar selecteza coloana de la care vrei sa muti piesa"<<endl;
                                cin>>coloana;
                                numarare_piese_albe();
                                scoaterepiesa_alba(coloana,zar2);
                                system("CLS");
                                afiseazatabla();
                                cout<<endl<<"Ai folosit al doilea zar,acum selecteaza coloana pe care vrei sa o muti cu primul "<<zar1<<endl;
                                cin>>coloana;
                                numarare_piese_albe();
                                scoaterepiesa_alba(coloana,zar1);
                                system("CLS");
                                afiseazatabla();
                                tura++;
                            }
                        }
                        else if (alegere==1)
                        {
                            cout<<"Ai ales primul zar selecteaza coloana de la care vrei sa muti piesa"<<endl;
                            cin>>coloana;
                            numarare_piese_albe();
                            mutarepiesa_alba(coloana,zar1);
                            system("CLS");
                            afiseazatabla();
                            /* for(int i=1;i<=24;i++)
                                cout<<alb[i]<<" "; */
                            cout<<endl<<"Ai folosit primul zar, acum selecteaza coloana pe care vrei sa o muti cu al doilea "<<zar2<<endl;
                            cin>>coloana;
                            numarare_piese_albe();
                            mutarepiesa_alba(coloana,zar2);
                            system("CLS");
                            afiseazatabla();
                            tura++;
                        }
                        else if (alegere==2)
                        {
                            cout<<"Ai ales al doilea zar selecteaza coloana de la care vrei sa muti piesa"<<endl;
                            cin>>coloana;
                            numarare_piese_albe();
                            mutarepiesa_alba(coloana,zar2);
                            system("CLS");
                            afiseazatabla();
                            /* for(int i=1;i<=24;i++)
                                cout<<alb[i]<<" "; */
                            cout<<endl<<"Ai folosit al doilea zar, acum selecteaza coloana pe care vrei sa o muti cu primul "<<zar1<<endl;
                            cin>>coloana;
                            numarare_piese_albe();
                            mutarepiesa_alba(coloana,zar1);
                            system("CLS");
                            afiseazatabla();
                            tura++;
                        }
                    }
                    //ulterior voi face daca nu am ales 1 sau 2
                }
            }
            else if(tura%2==0)
            {
                zar1=roll();
                zar2=roll2();
                cout <<"(al doilea jucator)"<<endl<<"primul zar "<<zar1<<endl<<"al doilea zar "<<zar2<<endl<<"scrie 1 pentru a folosi primul zar sau 2 pentru a folosi al doilea zar "<<endl;
                while(bar_negru!=0 && ok2==0)
                {
                    cout<<"Ai "<<bar_negru<<" piese pe bar, selecteaza unul din zar pentru a-ti pune piesele inapoi pe masa"<<endl;
                    cin>>alegere;
                    citire_alegere(alegere);
                    if(alegere==1)
                    {
                        if(check_penalty_negru(zar1)==0)
                        {
                            cout<<"Mutare invalida cu primul zar,vom incerca cu al doilea"<<endl;

                            if(check_penalty_negru(zar2)==0)
                            {
                                cout<<"Nu ai mutari valide"<<endl;

                                ok2=1;
                            }
                            else
                            {
                                ap=2;
                                n2++;
                                if(n2==2)
                                {
                                    ok2=1;
                                    break;
                                }
                            }
                        }
                        else
                        {
                            ap=1;
                            n2++;
                            if(n2==2)
                            {
                                ok2=1;
                                break;
                            }
                        }
                    }
                    else if (alegere==2)
                    {
                        if(check_penalty_negru(zar2)==0)
                        {
                            cout<<"Mutare invalida cu al doilea zar, vom incerca cu primul zar"<<endl;

                            if(check_penalty_negru(zar1)==0)
                            {
                                cout<<"Nu ai mutari valide"<<endl;

                                ok2=1;
                            }
                            else
                            {
                                ap=1;
                                n2++;
                                if(n2==2)
                                {
                                    ok2=1;
                                    break;
                                }
                            }
                        }
                        else
                        {
                            ap=2;
                            n2++;
                            if(n2==2)
                            {
                                ok2=1;
                                break;
                            }
                        }
                    }
                    system("CLS");
                    afiseazatabla();
                }
                if(ok2==1) tura++;
                else if(bar_negru==0 && tura%2==0)
                {
                    if(ap==1)
                    {
                        cout<<"Ai ramas cu al doilea zar selecteaza coloana de la care vrei sa muti pisea "<<zar2<<endl;
                        cin>>coloana;
                        numarare_piese_negre();
                        mutarepiesa_neagra(coloana,zar2);
                        system("CLS");
                        afiseazatabla();
                        tura++;
                    }
                    else if(ap==2)
                    {
                        cout<<"Ai ramas cu primul zar selecteaza coloana de la care vrei sa muti piesa "<<zar1<<endl;
                        cin>>coloana;
                        numarare_piese_negre();
                        mutarepiesa_neagra(coloana,zar1);
                        system("CLS");
                        afiseazatabla();
                        tura++;
                    }
                    else
                    {
                        cin>>alegere;
                        citire_alegere(alegere);
                        if(Check_pul_casa_negru()==0)
                        {
                            if(alegere==1)
                            {
                                cout<<"Ai ales primul zar selecteaza coloana de la care vrei sa muti piesa"<<endl;
                                cin>>coloana;
                                numarare_piese_negre();
                                scoaterepiesa_neagra(coloana,zar1);
                                system("CLS");
                                afiseazatabla();
                                cout<<endl<<"Ai folosit primul zar,acum selecteaa coloana pe care vrei sa o muti cu al doilea "<<zar2<<endl;
                                cin>>coloana;
                                numarare_piese_negre();
                                scoaterepiesa_neagra(coloana,zar2);
                                system("CLS");
                                afiseazatabla();
                                tura++;
                            }
                            else if (alegere==2)
                            {
                                cout<<"Ai ales al doilea zar selecteza coloana de la care vrei sa muti piesa"<<endl;
                                cin>>coloana;
                                numarare_piese_negre();
                                scoaterepiesa_neagra(coloana,zar2);
                                system("CLS");
                                afiseazatabla();
                                cout<<endl<<"Ai folosit al doilea zar,acum selecteaza coloana pe care vrei sa o muti cu primul"<<zar1<<endl;
                                cin>>coloana;
                                numarare_piese_negre();
                                scoaterepiesa_neagra(coloana,zar1);
                                system("CLS");
                                afiseazatabla();
                                tura++;
                            }
                        }
                        else if (alegere==1)
                        {
                            cout<<"Ai ales primul zar selecteaza coloana de la care vrei sa muti piesa"<<endl;
                            cin>>coloana;
                            numarare_piese_negre();
                           mutarepiesa_neagra(coloana,zar1);
                            /* for(int i=1;i<=24;i++)
                                 cout<<ngr[i]<<" "; */
                            system("CLS");
                            afiseazatabla();
                            cout<<endl<<"Ai folosit primul zar, acum selecteaza coloana pe care vrei sa o muti cu al doilea "<<zar2<<endl;
                            cin>>coloana;
                            numarare_piese_negre();
                            mutarepiesa_neagra(coloana,zar2);
                            system("CLS");
                            afiseazatabla();
                            tura++;
                        }
                        else if (alegere==2)
                        {
                            cout<<"Ai ales al doilea zar selecteaza coloana de la care vrei sa muti piesa"<<endl;
                            cin>>coloana;
                            numarare_piese_negre();
                            mutarepiesa_neagra(coloana,zar2);
                            system("CLS");
                            /* for(int i=1;i<=24;i++)
                                cout<<ngr[i]<<" "; */
                            afiseazatabla();
                            cout<<endl<<"Ai folosit al doilea zar, acum selecteaza coloana pe care vrei sa o muti cu primul "<<zar1<<endl;
                            cin>>coloana;
                            numarare_piese_negre();
                          mutarepiesa_neagra(coloana,zar1);
                            system("CLS");
                            afiseazatabla();
                            tura++;
                        }
                        
                    }

                }
            }
        }
        if(castiga_alb==true) punct_alb++;
        else if(castiga_negru==true) punct_negru++;
        cin>>replay;
        if(replay!=1) restart=false;
        system("CLS");
        system("Color 07");
    }
}
//thanks for checking this out ,this was both fun and hard since i dont know c++ and more c :     ^) , but more fun  
