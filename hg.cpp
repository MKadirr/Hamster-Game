#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include <cstdlib>

#include <cmath>

using namespace std;

/*
compile commande
cd C:\Users\Simon\Desktop\developement
g++ hg.cpp -o hg.exe
*/
typedef void (*fonctiontype)(vector<int> paramF, const struct Database*, const struct Constant*, int, int, struct PurchaseSale*);

struct PurchaseSale{
    int maleSolded;
    int femSolded;
    int foodBuy;
    int cageBuy;
};

struct Database{
    int adultMale;
    int adultFem;
    int kidMale;
    int kidFem;
    int kidMale2;
    int kidFem2;
    int money;
    double food;
    int cage;
    int week;
};

struct Constant{
    int seed;
    int weekMax;
    float foodWeek;
    short pxCage;
    short spaceCage;

    short fertilMin;
    short fertilMax;

    short pxHamsterMin;
    short pxHamsterMax;

    short pxFoodMin;
    short pxFoodMax;
};

int rand_a_b(int min, int max);

int secureInput(const string text, const int available, const int unite);
int verification(int value, int available, int unite);
void showStateGame(const struct Database *d, const struct Constant *c, int pxHamster, int pxFood);
int game(fonctiontype f, vector<int> paramF, const struct Constant *c, struct Database d);

void humanSelection(vector<int> paramF, const struct Database *d, const struct Constant *c, int pxHamster, int pxFood, struct PurchaseSale *ps);
void simpletBot(vector<int> paramF, const struct Database *d, const struct Constant *c, int pxHamster, int pxFood, struct PurchaseSale *ps);


int rand_a_b(int min, int max) 
{
    if(min == max) return min;
    else return ((rand()%(max-min)) + min);
}

int verification(int value, int available, int unite)
{
    return ((value*unite<=available && value>=0)) ? 1 : 0;
}

void showStateGame(const struct Database *d, const struct Constant *c, int pxHamster, int pxFood)
{
    int totHamster = d->adultMale + d->adultFem + d->kidFem2 + d->kidMale2;

    printf("Tt's turn %d\n" , d->week);
    printf("You own:\n");
    printf("   %d $\n" , d->money);
    printf("   %d adultes males\n" , d->adultMale);
    printf("   %d adultes femmelles\n" , d->adultFem);
    printf("   %d kids males\n" , d->kidMale2);
    printf("   %d kids femelles\n" , d->kidFem2);
    printf("   %d hamsters au total\n" , totHamster);
    printf("   %f kg de nourriture\n" , d->food);
    printf("   %d cages\n" , d->cage);
    printf("    \n");
    printf("les prix du jour sont:\n");
    printf("   les cages coutent %d $\n" , c->pxCage);
    printf("   la nourriture coute %d $ le kg\n" , pxFood);
    printf("   les hamsters adultes valent %d $\n" , pxHamster);
}

int secureInput(const string text, int available, int unite)
{
    int check = 1000;
    
    //char buffer[32];
    int result;
    do
    {
        check--;
        if(cin >> result)
        {
            if(result<0) cout << "you should use positive number.\n";
            else if(verification(result, available, unite)) check = 0;
            else cout << "You don't have enough " << text << endl;
        }
        else
        {
            cin.ignore();
            printf("please use only digit.\n");
        }
    }
    while(check != 0);

    return result;
}


void humanSelection(vector<int> paramF, const struct Database *d, const struct Constant *c, int pxHamster, int pxFood, struct PurchaseSale *ps)
{
    cout << "\n\n\n";
    showStateGame(d, c, pxHamster, pxFood);

    int check = 1;
    int a = 0;
    string exit;
    do
    {
        cout << "How many male hamster do you want to sold ?\n";
        ps->maleSolded = secureInput("male hamster", d->adultMale, 1);
        
        cout << "How many female hamster do you want to sold ?\n";
        ps->femSolded = secureInput("female hamster", d->adultFem, 1);

        int tempMoney = (ps->maleSolded + ps->femSolded)*pxHamster;
        printf("You sold %d female and %d male for %d$(sold:%d$)\n\n", ps->femSolded, ps->maleSolded, tempMoney, (tempMoney + d->money));

        tempMoney += d->money;

        printf("How many cage do you want to purchase ?\n");
        ps->cageBuy = secureInput("money", tempMoney, c->pxCage);
        tempMoney -= ps->cageBuy * c->pxCage;
        printf("You buy %d cage(s) for %d$(new sold : %d$)\n\n", ps->cageBuy, (ps->cageBuy*c->pxCage), tempMoney);
        printf("How many food do you want to purchase ?\n");
        ps->foodBuy = secureInput("money", tempMoney, pxFood);
        tempMoney -= ps->foodBuy * pxFood;
        printf("You buy %d kg of food for %d$(new sold : %d$)\n\n", ps->foodBuy, (ps->foodBuy * pxFood), tempMoney);

        printf("do you want to restart selection ? (tape 'r')\n");

        cin.ignore();
        getline(cin, exit);
        if(exit == "r") check = 0; 
    }
    while(a<10 && check==0);
}

void simpletBot(vector<int> paramF, const struct Database *d, const struct Constant *c, int pxHamster, int pxFood, struct PurchaseSale *ps)
{
    //showStateGame(d, c, pxHamster, pxFood);
    double coef = (1 /(1 + exp(-(pxHamster-20)/paramF[0]/10)));
    ps->maleSolded =  round((d->adultMale) * coef * paramF[1]/100); //random.randint(0,adultmale - 1)
    ps->femSolded = round((d->adultFem) * coef * paramF[2]/100);

    int tempMoney = d->money + (ps->maleSolded + ps->femSolded)*pxHamster;
    ps->cageBuy = (int)tempMoney/100 * paramF[3]/100;
    tempMoney -= ps->cageBuy * c->pxCage;

    int achatNour = 0;
    
    achatNour = round((d->cage+ps->cageBuy) * (1/(1+exp((pxFood-12.5)/paramF[4]/10)) - paramF[5]/100)*paramF[6]/100) + (d->cage + ps->cageBuy);
    if ((achatNour*pxFood)>=tempMoney)  achatNour = int(tempMoney/pxFood);
    ps->foodBuy = achatNour;
    //printf("%dFo %dHa\n", pxFood, pxHamster);
    //printf("%d %d %d %d\n\n", ps->maleSolded, ps->femSolded, ps->cageBuy, ps->foodBuy);
}

//1 50
//0 100
//0 100
//0 100
//1 50
//0 100
//0 100

void genetique(int nb, int gene)
{
    struct Constant c;
    c.weekMax = 52;
    c.foodWeek = 0.1;
    c.pxCage = 100;
    c.spaceCage = 10;

    c.fertilMin = 2;
    c.fertilMax = 10;

    c.pxHamsterMin = 10;
    c.pxHamsterMax = 30;

    c.pxFoodMin = 5;
    c.pxFoodMax = 20;

    struct Database d;
    //set data of the game
    d.adultMale = 1;
    d.adultFem = 1;
    d.kidMale = 0;
    d.kidFem = 0;
    d.kidMale2 = 0;
    d.kidFem2 = 0;
    d.money = 1000;
    d.food = 1.0;
    d.cage = 1;
    d.week = 0;


    fonctiontype simBot = &simpletBot;
    fonctiontype humSel = &humanSelection;
    vector<int> gen[nb];
    for(int i = 0; i<nb; i++)
    {
        gen[i].push_back(rand_a_b(1,101));
        gen[i].push_back(rand_a_b(1,101));
        gen[i].push_back(rand_a_b(1,101));
        gen[i].push_back(rand_a_b(1,101));
        gen[i].push_back(rand_a_b(1,101));
        gen[i].push_back(rand_a_b(1,101));
        gen[i].push_back(rand_a_b(1,101));
    }
    for(int i = 1; i<=gene; i++)
    {
        for(int y = 0; y<7; y++)
        {
            for(int z = 0; z<nb; z++) 
            {
                //cout << gen[y][z] << " ";
            }
            //cout << endl;
        }
        long scores[nb];
        int seed = time(NULL);
        for(int y = 0; y<nb; y++)
        {
            srand(i);
            scores[y] = game(simBot, gen[y], &c, d);
            cout << scores[y] << " ";
        }
        cout << endl;
        //cout << "1\n";
        int indiceMax = 0;
        int indiceMin = 0;
        for(int y = 0; y<nb; y++)
        {
            if(scores[y] > scores[indiceMax]) indiceMax = y;
            if(scores[y] < scores[indiceMin]) indiceMin = y;
        }
        //cout << indice << endl << endl;
        //cout << "2\n";
        for(int y = 0; y<nb; y++)
        {
            //cout << "3 " << y << endl;
            if(y==indiceMax) y++;
            for(int z = 0; z<7; z++)
            {
                //cout << "4 " << z << endl;
                if(rand()%2 == 1) gen[y][z] = gen[indiceMax][z];
            }
        }
        gen[indiceMin][0] = (rand_a_b(1,101));
        gen[indiceMin][1] = (rand_a_b(1,101));
        gen[indiceMin][2] = (rand_a_b(1,101));
        gen[indiceMin][3] = (rand_a_b(1,101));
        gen[indiceMin][4] = (rand_a_b(1,101));
        gen[indiceMin][5] = (rand_a_b(1,101));
        gen[indiceMin][6] = (rand_a_b(1,101));
        //cout << endl;
    }

    for(int i = 0; i<nb; i++)
    {
        srand(1);
        game(simBot, gen[i], &c, d);
    }

}

int game(fonctiontype f, vector<int> paramF, const struct Constant *c, struct Database d)
{
    //temp
    int pxHamster;
    int pxFood;

    int check = 0;

    int totHamster = d.adultMale + d.adultFem + d.kidFem2 + d.kidMale2;

    while(d.week<c->weekMax && check == 0)
    {
        d.week++;
        pxHamster = rand_a_b(c->pxHamsterMin, c->pxHamsterMax+1);
        pxFood = rand_a_b(c->pxFoodMin, c->pxFoodMax+1);

        d.adultMale += d.kidMale2;
        d.adultFem += d.kidFem2;
        d.kidMale2 = d.kidMale;
        d.kidFem2 = d.kidFem;

        struct PurchaseSale ps;
        (*f)(paramF, &d, c, pxHamster, pxFood, &ps);
        
        //verification for all ps:
        if(verification(ps.maleSolded, d.adultMale, 1)) d.adultMale -= ps.maleSolded;
        else ps.maleSolded = 0;
        if(verification(ps.femSolded, d.adultFem, 1)) d.adultFem -= ps.femSolded;
        else ps.femSolded = 0;

        d.money += (ps.maleSolded + ps.femSolded) * pxHamster;

        if(verification(ps.foodBuy, d.money, pxFood)) d.food += ps.foodBuy;
        else ps.foodBuy = 0;

        d.money -=  ps.foodBuy * pxFood; 

        if(verification(ps.cageBuy, d.money, c->pxCage))d.cage += ps.cageBuy;
        else ps.cageBuy = 0;
        
        d.money -= ps.cageBuy * (c->pxCage);
        

        //create the babies
        int couple = (d.adultFem<d.adultMale) ? d.adultFem : d.adultMale;
        int newBabies = (couple==0) ? 0 : rand_a_b((c->fertilMin)*couple, (c->fertilMax)*couple); // paren

        //kill time:
        //  from cage limitation

        if(totHamster+newBabies > (d.cage * c->spaceCage)) newBabies = (d.cage * (c->spaceCage)) - totHamster;

        totHamster = d.adultMale + d.adultFem + d.kidFem2 + d.kidMale2 + newBabies;

        //  from food:
        int death = (totHamster<=d.food/c->foodWeek) ? 0 :  totHamster - d.food/c->foodWeek;

        d.food = (death != 0) ?  0 : (d.food - totHamster * (c->foodWeek)); // paren


        if(newBabies<=death)
        {
            //printf("1\n");
            death -= newBabies;
            newBabies = 0;
            if(death != 0 && (d.kidFem2+d.kidMale2) <= death)
            {
                //printf("1-1\n");
                death -= d.kidFem2+d.kidMale2;
                d.kidFem2 = 0;
                d.kidMale2 = 0;

                if(death != 0 && (d.adultMale+d.adultFem) <= death)
                {
                    //printf("1-1-1\n");
                    death = 0;
                    d.adultFem = 0;
                    d.adultMale = 0;
                }
                else
                {
                    //printf("1-1-2'\n");
                    int mid = (int) death/2;
                    if(d.adultFem<mid)
                    {
                        //printf("1-1-2-1\n");
                        death -= d.adultFem;
                        d.adultFem = 0;
                        d.adultMale -= death;
                    }
                    else if(d.adultMale<(death-mid))
                    {
                        //printf("1-1-2-2'\n");
                        death -= d.adultMale;
                        d.adultMale = 0;
                        d.adultFem -= death;
                    }
                    else
                    {
                        //printf("1-1-2-3\n");
                        d.adultFem -= mid;
                        d.adultMale += death - mid;
                    }
                }
            }
            else
            {
                //printf("1-2'\n");
                int mid = (int) death/2;
                if(d.kidFem2<mid)
                {
                    //printf("1-2-1\n");
                    death -= d.kidFem2;
                    d.kidFem2 = 0;
                    d.kidMale2 -= death;
                }
                else if(d.kidMale2<(death-mid))
                {
                    //printf("1-2-2\n");
                    death -= d.kidMale2;
                    d.kidMale2 = 0;
                    d.kidFem2 -= death;
                }
                else
                {
                    //printf("1-2-3\n");
                    d.kidFem2 -= mid;
                    d.kidMale2 += death - mid;
                }
            }
        }
        else {
            //printf("2\n");
            newBabies -= death;
            death = 0;
        }
        totHamster = d.adultMale + d.adultFem + d.kidFem2 + d.kidMale2 + newBabies;
        d.kidFem = rand_a_b(0, newBabies);
        d.kidMale = newBabies - d.kidFem;

        if(totHamster == 0) check = 1;
    }

    int score = totHamster * c->pxHamsterMax + d.money;
    if(check) 
    {
        //printf("You loose : GAME OVER !\n");
        return 0;
    }
    else
    {
        //printf("Well play you win, you earn %d\n", score);
    }

    return score;
}

int main(int argc, char *argv[])
{
    struct Constant c;
    //set constant
    c.seed = 0;
    if(argc>1)
    {
        c.seed = atoi(argv[1]);//set seed
        srand(c.seed);
    }
    else  srand(time(NULL));
    
    c.weekMax = 52;
    c.foodWeek = 0.1;
    c.pxCage = 100;
    c.spaceCage = 10;

    c.fertilMin = 2;
    c.fertilMax = 10;

    c.pxHamsterMin = 10;
    c.pxHamsterMax = 30;

    c.pxFoodMin = 5;
    c.pxFoodMax = 20;

    struct Database d;
    //set data of the game
    d.adultMale = 1;
    d.adultFem = 1;
    d.kidMale = 0;
    d.kidFem = 0;
    d.kidMale2 = 0;
    d.kidFem2 = 0;
    d.money = 1000;
    d.food = 1.0;
    d.cage = 1;
    d.week = 0;


    fonctiontype simBot = &simpletBot;
    fonctiontype humSel = &humanSelection;


    //double test = 100 *(1 /(1 + exp(-(10-20))));
    //double test2 =  100*(1 /(1 + exp(-(30-20))));
    //cout << test << " " << test2 << endl;
    vector<int> p;
    //game(simBot, p, &c, d);

    genetique(5, 5);

    return 0;
}