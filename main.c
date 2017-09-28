#include <stdio.h>
#include <stdlib.h>

void wypisz(); //funkcja wypisujaca aktualny stan rozgrywki, pola o wartosci powyzej 128 sa wypisywane jako liczby calkowite
               //o 128 mniejsze od wartosci pola, reszta jest wypisywana jako char, przed wypisaniem funkcja czysci ekran
int mozliwe_ruchy(); //funkcja sprawdzajaca na jakie pola mozna wskoczyc oraz podpisujaca je w tablicy odpowiednimi literami, zwraca ona ilosc mozliwych ruchow i zapisuje wspolrzedne mozliwego skoku w tablicy skoki
void wykonaj_ruch(); //funkcja ktora ustawia odpowiednie wartosci zmiennych w tablicy oraz dla zmiennych w zaleznosci od podjetego ruchu
void czysc_skoki(); //funkcja usuwajaca z tablicy podpisane pola na ktore mozna wykonac ruch - ustawia dla nich domyslna wartosc ' ' czyli spacje
void czysc_tablice(); //funkcja ustawiajaca cala tablice na wartosc domyslna ' ' czyli spacje

int szachownica[8][8]; //tablica sluzaca do gromadzenia informacji o aktualnym stanie rozgrywki oraz do utworzenia jego grafiki
int kolumna, wiersz, tura, ruchy; //globalne zmienne gromadzace informacje o stanie rozgrywki
int skoki[8][2]; //tablica przechowujaca wspolrzedne mozliwych skokow usuwa ona koniecznosc wielokrotnego obliczania tychze wspolrzednych

int main()
{

    while(1) //petla umozliwiajaca wielokrotna rozgrywke
    {
        czysc_tablice();
        wypisz();
        puts("Podaj wspolrzedne poczatkowe: np c7");

        while((scanf("%c %d", &kolumna, &wiersz)) != 2 || kolumna < 'a' || kolumna > 'h' || wiersz < 1 || wiersz > 8)  //sprawdzanie czy wprowadzone wartosci sa porpawne
            {
            puts("\nBledne dane, wprowadz jeszcze raz");
            while(getchar() != '\n') //pomijanie reszty wejscia do znaku enter
                continue;
            }
        wiersz = wiersz - 1;   //ustawianie wspolrzednych wybranego punktu poczatkowego w tablicy
        kolumna = kolumna - 'a';
        szachownica[wiersz][kolumna] = 'X';

        tura = 1;


        while(mozliwe_ruchy() != 0) //petla w ktorej odbywa sie glowna rozgrywka, trwa ona dopuki mozna wykonac ruch
        {
            wypisz();
            printf("Ilosc mozliwych skokow wynosi %d, podaj litere na ktora chcesz wskoczyc:\n", ruchy);
            wykonaj_ruch();
            tura++;
        }
        wypisz();

        if(tura == 64)
            puts("BRAWO UDALO CI SIE WSKOCZYC NA KAZDE POLE!!!");

        printf("\nKONIEC GRY\n\nNie mozesz wykonac kolejnych skokow, twoj wynik to: %d"
               "\n\nCzy chcesz zagrac ponownie? Wpisz 1 jesli tak\n", tura);

        getchar();  //wyczyszczenie bufora ze znaku '\n'
        if(getchar() == '1') //umozliwienie uzytkownikowi ponownej rozgrywki
            tura = 0;
        else
            return 0;
    }
    return 0;
}
/***********************FUNKCJE********************************/
void wypisz()
{
    int i, j;

    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__) //w zaleznosci od systemu operacyjnego nalezy uzyc innej komendy do czyszczenia konsoli
        system("clear");
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif


    printf("Aktualna tura: %d\n\n   A   B   C   D   E   F   G   H\n", tura);
    for(i = 0; i < 8; i++)
        {
        printf("%c|",'1'+i);
        for(j = 0; j < 8; j++)
            {
            if(szachownica[i][j] > 127)
                printf("%3d|", szachownica[i][j] - 128); //wypisanie wartosci mowiacej o kolejnosci wskoczenia na to pole
            else                                         //jest ona o 128 wieksza od wartosci pola aby odroznic wartosci calkowite od kodu ascii
                printf("%3c|", szachownica[i][j]);
            }
        putchar('\n');
        }
}
//////////////////////////////////////////////////////
int mozliwe_ruchy()
{
    int x,y; //zmienne sluzace do przechowywania wspolrzednych sprawdzanego pola, zmniejszaja one ilosc wymaganych obliczen

    ruchy = 0;

    x = wiersz+2; //zmienne sluzace do przechowywania wspolrzednych mozliwych skokow, sprawiaja ona ze nie jest konieczne wielokrotne obliczanie ich wartosci w warunku if oraz instrukcjach
    y = kolumna-1;
    if(x >= 0 && x <= 7 && y >= 0 && y <= 7 && szachownica[x][y] == ' ') //sprawdzanie czy mozliwosc skoku na jedna z osmiu kombinacji jest mozliwa
        {                                                                //w razie prawdziwosci wyrazenia program wpisuje do
                                                                        //tablicy znak swiadczacu o mozliwosci wykonania ruchu na to pole
        szachownica[x][y] = 'v';                                         //oraz zwieksza licznik ilosci mozliwych ruchow
        skoki[0][0] = x; //wpisanie do tablicy skoki wspolrzednych mozliwych skokow
        skoki[0][1] = y;
        ruchy++;
        }

    x = wiersz+2;
    y = kolumna+1;
    if(x >= 0 && x <= 7 && y >= 0 && y <= 7 && szachownica[x][y] == ' ')
        {
        szachownica[x][y] = 'm';
        skoki[1][0] = x;
        skoki[1][1] = y;
        ruchy++;
        }

    x = wiersz+1;
    y = kolumna-2;
    if(x >= 0 && x <= 7 && y >= 0 && y <= 7 && szachownica[x][y] == ' ')
        {
        szachownica[x][y] = 'b';
        skoki[2][0] = x;
        skoki[2][1] = y;
        ruchy++;
        }

    x = wiersz+1;
    y = kolumna+2;
    if(x >= 0 && x <= 7 && y >= 0 && y <= 7 && szachownica[x][y] == ' ')
        {
        szachownica[x][y] = 'n';
        skoki[3][0] = x;
        skoki[3][1] = y;
        ruchy++;
        }

    x = wiersz-1;
    y = kolumna-2;
    if(x >= 0 && x <= 7 && y >= 0 && y <= 7 && szachownica[x][y] == ' ')
        {
        szachownica[x][y] = 'g';
        skoki[4][0] = x;
        skoki[4][1] = y;
        ruchy++;
        }

    x = wiersz-1;
    y = kolumna+2;
    if(x >= 0 && x <= 7 && y >= 0 && y <= 7 && szachownica[x][y] == ' ')
        {
        szachownica[x][y] = 'h';
        skoki[5][0] = x;
        skoki[5][1] = y;
        ruchy++;
        }

    x = wiersz-2;
    y = kolumna-1;
    if(x >= 0 && x <= 7 && y >= 0 && y <= 7 && szachownica[x][y] == ' ')
        {
        szachownica[x][y] = 't';
        skoki[6][0] = x;
        skoki[6][1] = y;
        ruchy++;
        }

    x = wiersz-2;
    y = kolumna+1;
    if(x >= 0 && x <= 7 && y >= 0 && y <= 7 && szachownica[x][y] == ' ')
        {
        szachownica[x][y] = 'y';
        skoki[7][0] = x;
        skoki[7][1] = y;
        ruchy++;
        }

        return ruchy;
}
/////////////////////////////////////////////
void wykonaj_ruch()
{
    int x, y;
    _Bool poprawne = 0; //zmienna umozliwiajaca wyjscie z petli while, gdyz break wewnatrz case wychodzi tylko ze switch
    while(1)
    {

        switch(getchar()) //menu w ktorym wybieramy na ktore pole chcemy wskoczyc
        {
        case 'v':
            {
            x = skoki[0][0]; //przypisanie wspolrzednych danej mozliwosci skoku z tablicy je przechowywujacej
            y = skoki[0][1];
            if(szachownica[x][y] == 'v') //jesli na polu odpowiadajacym wybranemu znakowi znajduje sie znak v, to mozna na nie wskoczyc
                poprawne = 1;
            break;
            }
        case 'm':
            {
            x = skoki[1][0];
            y = skoki[1][1];
            if(szachownica[x][y] == 'm')
                poprawne = 1;
            break;
            }
        case 'b':
            {
            x = skoki[2][0];
            y = skoki[2][1];
            if(szachownica[x][y] == 'b')
                poprawne = 1;
            break;
            }
        case 'n':
            {
            x = skoki[3][0];
            y = skoki[3][1];
            if(szachownica[x][y] == 'n')
                poprawne = 1;
            break;
            }
        case 'g':
            {
            x = skoki[4][0];
            y = skoki[4][1];
            if(szachownica[x][y] == 'g')
                poprawne = 1;
            break;
            }
        case 'h':
            {
            x = skoki[5][0];
            y = skoki[5][1];
            if(szachownica[x][y] == 'h')
                poprawne = 1;
            break;
            }
        case 't':
            {
            x = skoki[6][0];
            y = skoki[6][1];
            if(szachownica[x][y] == 't')
                poprawne = 1;
            break;
            }
        case 'y':
            {
            x = skoki[7][0];
            y = skoki[7][1];
            if(szachownica[x][y] == 'y')
                poprawne = 1;
            break;
            }
        }
        if(poprawne) //warunkowe wyjscie z petli while, zostaje ono wykonane gdy wybrany skok jest mozliwy
            break;
    }
    szachownica[x][y] = 'X'; //wpisanie znaku konika w wybrane pole tablicy
    szachownica[wiersz][kolumna] = tura+128; //wpisanie numeru tury w ktorej zosta wykonany skok na poprzednie pole z dodatkiem 128 aby odroznic wartosc calkowita od ascii
    czysc_skoki(); //usuwanie z tablicy wartosci swiadczacych o mozliwosci wskoczenia na pole
    wiersz = x; //zmiana globalnych wartosci wspolrzednych na ktorych znajduje sie konik
    kolumna = y;
    return;
}
///////////////////////////////////////////
void czysc_skoki()
{
    if(szachownica[skoki[0][0]][skoki[0][1]] == 'v') //usuwanie wartosci odpowiadajacych za mozliwosc wskoczenia na dane pole z tablicy szachownica
        szachownica[skoki[0][0]][skoki[0][1]] = ' '; //ich mozliwe wspolrzedne sa przechowywane i wypisane z tablicy skoki
    if(szachownica[skoki[1][0]][skoki[1][1]] == 'm')
        szachownica[skoki[1][0]][skoki[1][1]] = ' ';
    if(szachownica[skoki[2][0]][skoki[2][1]] == 'b')
        szachownica[skoki[2][0]][skoki[2][1]] = ' ';
    if(szachownica[skoki[3][0]][skoki[3][1]] == 'n')
        szachownica[skoki[3][0]][skoki[3][1]] = ' ';
    if(szachownica[skoki[4][0]][skoki[4][1]] == 'g')
        szachownica[skoki[4][0]][skoki[4][1]] = ' ';
    if(szachownica[skoki[5][0]][skoki[5][1]] == 'h')
        szachownica[skoki[5][0]][skoki[5][1]] = ' ';
    if(szachownica[skoki[6][0]][skoki[6][1]] == 't')
        szachownica[skoki[6][0]][skoki[6][1]] = ' ';
    if(szachownica[skoki[7][0]][skoki[7][1]] == 'y')
        szachownica[skoki[7][0]][skoki[7][1]] = ' ';

    return;
}
/////////////////////////////////////////////
void czysc_tablice()
{
    int i,j;
    for(i = 0; i < 8; i++) //podwojna petla wstawiajaca w kazde pole tablicy wartosc ' ' czyli spacje
        for(j = 0; j < 8; j++)
        szachownica[i][j] = ' ';
    return;
}
