#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
/*
compile commande
cd C:\Users\Simon\Desktop\developement
gcc hamster-game.c -o hamster-game.exe
*/
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

/*
Fonction that return random number beetwen min and max exclu
*/
int rand_a_b(int min, int max);
/*provide a secure input for int*/
int secureInput(const char* text, const int available, const int unite);

int verification(int value, int available, int unite);

/* the whole game */
int game(int type, const struct Constant *c, struct Database g);

/*fonction for human input*/
void humanSelection(const struct Database *g, const struct Constant *c, int pxHamster, int pxCage, struct PurchaseSale *ps);

int verification(int value, int available, int unite)
{
    return ((value*unite<=available && value>=0)) ? 1 : 0;
}

int secureInput(const char* text, int available, int unite)
{
    int check = 1000;
    
    //char buffer[32];
    int result;
    do
    {
        check--;
        fflush(stdin);
        if(scanf("%d", &result))
        {
            if(result<0) printf("you should use positive number.\n");
            else if(verification(result, available, unite)) check = 0;
            else printf("You don't have enough %s\n", text);
        }
        else printf("please use only digit.\n");
    }
    while(check != 0);

    return result;
}

int rand_a_b(int min, int max) 
{
    if(min == max) return min;
    else return ((rand()%(max-min)) + min);
}

void humanSelection(const struct Database *g, const struct Constant *c, int pxHamster, int pxFood, struct PurchaseSale *ps)
{
    int check = 1;
    int a = 0;
    char exit;
    do
    {
        printf("How many male hamster do you want to sold ?\n");
        ps->maleSolded = secureInput("male hamster", g->adultMale, 1);
        
        printf("How many female hamster do you want to sold ?\n");
        ps->femSolded = secureInput("female hamster", g->adultFem, 1);

        int tempMoney = (ps->maleSolded + ps->femSolded)*pxHamster;
        printf("You sold %d female and %d male for %d$(sold:%d$)\n\n", ps->femSolded, ps->maleSolded, tempMoney, (tempMoney + g->money));

        tempMoney += g->money;

        printf("How many cage do you want to purchase ?\n");
        ps->cageBuy = secureInput("money", tempMoney, c->pxCage);
        tempMoney -= ps->cageBuy * c->pxCage;
        printf("You buy %d cage(s) for %d$(new sold : %d$)\n\n", ps->cageBuy, (ps->cageBuy*c->pxCage), tempMoney);
        printf("How many food do you want to purchase ?\n");
        ps->foodBuy = secureInput("money", tempMoney, pxFood);
        tempMoney -= ps->foodBuy * pxFood;
        printf("You buy %d kg of food for %d$(new sold : %d$)\n\n", ps->foodBuy, (ps->foodBuy * pxFood), tempMoney);

        printf("do you want to restart selection ? (tape 'r')\n");
        fflush(stdin);
        if(getchar()=='r') check == 0; // to fix;
    }
    while(a<10 && check==0);
}

int game(int type, const struct Constant *c, struct Database g)
{
    srand(c->seed);
    //temp
    int pxHamster;
    int pxFood;

    int check = 0;

    int totHamster = g.adultMale + g.adultFem + g.kidFem2 + g.kidMale2;

    while(g.week<c->weekMax && check == 0)
    {
        g.week++;
        pxHamster = rand_a_b(c->pxHamsterMin, c->pxHamsterMax+1);
        pxFood = rand_a_b(c->pxFoodMin, c->pxFoodMax+1);

        g.adultMale += g.kidMale2;
        g.adultFem += g.kidFem2;
        g.kidMale2 = g.kidMale;
        g.kidFem2 = g.kidFem;
        


        struct PurchaseSale ps;
        if(type == 0)
        {
            printf("Tt's turn %d\n" , g.week);
            printf("You own:\n");
            printf("   %d $\n" , g.money);
            printf("   %d adultes males\n" , g.adultMale);
            printf("   %d adultes femmelles\n" , g.adultFem);
            printf("   %d kids males\n" , g.kidMale2);
            printf("   %d kids femelles\n" , g.kidFem2);
            printf("   %d hamsters au total\n" , totHamster);
            printf("   %f kg de nourriture\n" , g.food);
            printf("   %d cages\n" , g.cage);
            printf("    \n");
            printf("les prix du jour sont:\n");
            printf("   les cages coutent %d $\n" , c->pxCage);
            printf("   la nourriture coute %d $ le kg\n" , pxFood);
            printf("   les hamsters adultes valent %d $\n" , pxHamster);

            humanSelection(&g, c, pxHamster, pxFood, &ps);
        }
        else if(type == 1)
        {
            printf("Tt's turn %d\n" , g.week);
            printf("You own:\n");
            printf("   %d $\n" , g.money);
            printf("   %d adultes males\n" , g.adultMale);
            printf("   %d adultes femmelles\n" , g.adultFem);
            printf("   %d kids males\n" , g.kidMale2);
            printf("   %d kids femelles\n" , g.kidFem2);
            printf("   %d hamsters au total\n" , totHamster);
            printf("   %f kg de nourriture\n" , g.food);
            printf("   %d cages\n" , g.cage);
            printf("    \n");
            printf("les prix du jour sont:\n");
            printf("   les cages coutent %d $\n" , c->pxCage);
            printf("   la nourriture coute %d $ le kg\n" , pxFood);
            printf("   les hamsters adultes valent %d $\n" , pxHamster);

            ps.femSolded = 0;
            ps.maleSolded = 1;
            ps.foodBuy = 10;
            ps.cageBuy = 3;
        }
        
        //verification for all ps:
        if(verification(ps.maleSolded, g.adultMale, 1)) g.adultMale -= ps.maleSolded;
        else ps.maleSolded = 0;
        if(verification(ps.femSolded, g.adultFem, 1)) g.adultFem -= ps.femSolded;
        else ps.femSolded = 0;

        g.money += (ps.maleSolded + ps.femSolded) * pxHamster;

        if(verification(ps.foodBuy, g.money, pxFood)) g.food += ps.foodBuy;
        else ps.foodBuy = 0;

        g.money -=  ps.foodBuy * pxFood; 

        if(verification(ps.cageBuy, g.money, c->pxCage))g.cage += ps.cageBuy;
        else ps.cageBuy = 0;
        
        g.money -= ps.cageBuy * (c->pxCage);
        

        //create the babies
        int couple = (g.adultFem<g.adultMale) ? g.adultFem : g.adultMale;
        int newBabies = (couple==0) ? 0 : rand_a_b((c->fertilMin)*couple, (c->fertilMax)*couple); // paren

        //kill time:
        //  from cage limitation

        if(totHamster+newBabies > (g.cage * c->spaceCage)) newBabies = (g.cage * (c->spaceCage)) - totHamster;

        totHamster = g.adultMale + g.adultFem + g.kidFem2 + g.kidMale2 + newBabies;

        //  from food:
        int death = (totHamster<=g.food/c->foodWeek) ? 0 :  totHamster - g.food/c->foodWeek;

        g.food = (death != 0) ?  0 : (g.food - totHamster * (c->foodWeek)); // paren


        if(newBabies<=death)
        {
            //printf("1\n");
            death -= newBabies;
            newBabies = 0;
            if(death != 0 && (g.kidFem2+g.kidMale2) <= death)
            {
                //printf("1-1\n");
                death -= g.kidFem2+g.kidMale2;
                g.kidFem2 = 0;
                g.kidMale2 = 0;

                if(death != 0 && (g.adultMale+g.adultFem) <= death)
                {
                    //printf("1-1-1\n");
                    death = 0;
                    g.adultFem = 0;
                    g.adultMale = 0;
                }
                else
                {
                    //printf("1-1-2'\n");
                    int mid = (int) death/2;
                    if(g.adultFem<mid)
                    {
                        //printf("1-1-2-1\n");
                        death -= g.adultFem;
                        g.adultFem = 0;
                        g.adultMale -= death;
                    }
                    else if(g.adultMale<(death-mid))
                    {
                        //printf("1-1-2-2'\n");
                        death -= g.adultMale;
                        g.adultMale = 0;
                        g.adultFem -= death;
                    }
                    else
                    {
                        //printf("1-1-2-3\n");
                        g.adultFem -= mid;
                        g.adultMale += death - mid;
                    }
                }
            }
            else
            {
                //printf("1-2'\n");
                int mid = (int) death/2;
                if(g.kidFem2<mid)
                {
                    //printf("1-2-1\n");
                    death -= g.kidFem2;
                    g.kidFem2 = 0;
                    g.kidMale2 -= death;
                }
                else if(g.kidMale2<(death-mid))
                {
                    //printf("1-2-2\n");
                    death -= g.kidMale2;
                    g.kidMale2 = 0;
                    g.kidFem2 -= death;
                }
                else
                {
                    //printf("1-2-3\n");
                    g.kidFem2 -= mid;
                    g.kidMale2 += death - mid;
                }
            }
        }
        else {
            printf("2\n");
            newBabies -= death;
            death = 0;
        }
        totHamster = g.adultMale + g.adultFem + g.kidFem2 + g.kidMale2 + newBabies;
        g.kidFem = rand_a_b(0, newBabies);
        g.kidMale = newBabies - g.kidFem;

        if(totHamster == 0) check = 1;
    }

    int score = totHamster * c->pxHamsterMax + g.money;
    if(check) printf("You loose : GAME OVER !");
    else
    {
        printf("Well play you win, you earn %d", score);
    }

    return score;
}

int main(int argc, char *argv[])
{
    struct Constant c;
    //set constant
    if(argc<2) c.seed = atoi(argv[1]);//set seed
    else c.seed=rand();

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

    struct Database g;
    //set data of the game
    g.adultMale = 1;
    g.adultFem = 1;
    g.kidMale = 0;
    g.kidFem = 0;
    g.kidMale2 = 0;
    g.kidFem2 = 0;
    g.money = 1000;
    g.food = 1.0;
    g.cage = 1;
    g.week = 0;

    game(0, &c, g);


    //if(argc<2) game(0);//set seed
    //else game(rand(), 0);
}