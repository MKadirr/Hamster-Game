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
    float food;
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

/* the whole game */
int game(int type, const struct Constant *c, struct Database g);

/*fonction for human input*/
void humanSelection(const struct Database *g, const struct Constant *c, int pxHamster, int pxCage, struct PurchaseSale *ps);

/*provide a secure input for int*/
int secureInput(const char* text, const int dispo, const int unite);


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
            else if(result*unite<=available) check = 0;
            else printf("You don't have enought %s\n", text);
        }
        else printf("please use only digit.\n");
    }
    while(check != 0);

    return result;
}

int rand_a_b(int min, int max) {return ((rand()%(max-min)) + min);}

void humanSelection(const struct Database *g, const struct Constant *c, int pxHamster, int pxFood, struct PurchaseSale *ps)
{
    int check = 0;
    int a = 0;
    char exit;
    while(a<10 && check==0)
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
        printf("You buy %d cage(s) for %d$(new sold : %d$)\n\n", ps->foodBuy, (ps->foodBuy * pxFood), tempMoney);

        printf("do you want to restart selection ? (tape 'r')\n");
        if(getchar()!='r') check == 1;
    }
}

int game(int type, const struct Constant *c, struct Database g)
{
    //temp
    int pxHamster;
    int pxFood;

    
    while(g.week<=c->weekMax)
    {
        g.week++;
        pxHamster = rand_a_b(c->pxHamsterMin, c->pxHamsterMax+1);
        pxFood = rand_a_b(c->pxFoodMin, c->pxFoodMax+1);

        g.adultMale += g.kidMale2;
        g.adultFem += g.kidFem2;
        g.kidMale2 = g.kidMale;
        g.kidFem2 = g.kidFem;
        int totHamster = g.adultMale + g.adultFem + g.kidFem2 + g.kidMale2;


        struct PurchaseSale ps;
        if(type == 0)
        {
            printf("Tt's turn %d" , g.week);
            printf("You own:");
            printf("   %d $" , g.money);
            printf("   %d adultes males" , g.adultMale);
            printf("   %d adultes femmelles" , g.adultFem);
            printf("   %d kids males" , g.kidMale2);
            printf("   %d kids femelles" , g.kidFem2);
            printf("   %d hamsters au total" , totHamster);
            printf("   %d kg de nourriture" , g.food);
            printf("   %d cages" , g.cage);
            printf("    ");
            printf("les prix du jour sont:");
            printf("   les cages coutent %d $" , c->pxCage);
            printf("   la nourriture coute %d $ le kg" , pxFood);
            printf("   les hamsters adultes valent %d $" , pxHamster);

            humanSelection(&g, c, pxHamster, pxFood, &ps);
        }

        g.adultMale -= ps.maleSolded;
        g.adulteFem -= ps.femSolded;
        g.food += ps.foodBuy;
        g.cage += pas.cageBuy;

        g.money = g.money + ((ps.maleSolded + ps. femSolded)*pxHamster) - (ps.cageBuy*c.pxCage + ps.foodBuy*pxFood);

        //create the babies
        int couple = (g.adulteFem<g.adultMale) ? adulteFem : adultMale;
        int newBabies = rand_a_b(c->fertilmin*couple, c->fertilMax*couple);

        //kill time
        totHamster = g.adultMale + g.adultFem + g.kidFem2 + g.kidMale2 + newBabies;
        if(totalhamster > (g.cage * c->spaceCage)) newBabies = (g.cage * c->spaceCage) - totalhamster;


    }

    return g.money;
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
    g.food = 1;
    g.cage = 1;
    g.week = 0;

    struct PurchaseSale ps;
    humanSelection(&g, &c, 30, 10, &ps);
    //if(argc<2) game(0);//set seed
    //else game(rand(), 0);
}

/*
    printf("C'est le tour %d" , week)
    printf("You own:")
    printf("   %d $" , money)
    printf("   %d adultes males" , adultMale)
    printf("   %d adultes femmelles" , adultFem)
    printf("   %d kids males" , kidMale2)
    printf("   %d kids femelles" , kidfem2)
    printf("   %d hamsters au total" , totalhamster)
    printf("   %d kg de nourriture" , nourriture)
    printf("   %d cages" , cage)
    printf("    ")
    printf("les prix du jour sont:")
    printf("   les cages coutent %d $" , pxCage)    
    printf("   la nourriture coute %d $ le kg" , pxFood)
    printf("   les hamsters adultes valent %d $" , pxHamster)    
*/