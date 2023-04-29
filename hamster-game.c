#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "hamster-game.h"

/*
compile commande
cd C:\Users\Simon\Desktop\developement
gcc hamster-game.c -o hamster-game.exe
*/


/*
Fonction that return random number beetwen min and max exclu
*/


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

void humanSelection(const struct Database *d, const struct Constant *c, int pxHamster, int pxFood, struct PurchaseSale *ps, void* Argument)
{
    int check = 1;
    int a = 0;
    char exit;
    do
    {
        printf("How many male hamster do you want to sold ?\n");
        ps->maleSolded = secureInput("male hamster", d->adultMale, 1);
        
        printf("How many female hamster do you want to sold ?\n");
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
        fflush(stdin);
        if(getchar()=='r') check == 0; // to fix;
    }
    while(a<10 && check==0);
}

void simplestSelect(const struct Database *d, const struct Constant *c, int pxHamster, int pxFood, struct PurchaseSale *ps, void* Argument)
{
    ps->femSolded = 0;
    ps->maleSolded = 1;
    ps->foodBuy = 10;
    ps->cageBuy = 3;
}

int game(const struct Constant *c, 
         struct Database d, 
         struct Player *p, 
         int* pregenerateRandom)
{
    //temp
    int pxHamster;
    int pxFood;

    int check = 0;

    int totHamster = d.adultMale + d.adultFem + d.kidFem2 + d.kidMale2;

    while(d.week<c->weekMax && check == 0)
    {
        
        if(flag&2)
        {
            pxHamster = pregenerateRandom[d.week * 2];
            pxFood =    pregenerateRandom[d.weed * 2 + 1];
        }
        else
        {
            pxHamster = rand_a_b(c->pxHamsterMin, c->pxHamsterMax+1);
            pxFood = rand_a_b(c->pxFoodMin, c->pxFoodMax+1);
        }
        d.week++;

        d.adultMale += d.kidMale2;
        d.adultFem += d.kidFem2;
        d.kidMale2 = d.kidMale;
        d.kidFem2 = d.kidFem;
        


        struct PurchaseSale ps;
        if (flag&1)
        {
            printf("Tt's turn %d\n" , d.week);
            printf("You own:\n");
            printf("   %d $\n" , d.money);
            printf("   %d adultes males\n" , d.adultMale);
            printf("   %d adultes femmelles\n" , d.adultFem);
            printf("   %d kids males\n" , d.kidMale2);
            printf("   %d kids femelles\n" , d.kidFem2);
            printf("   %d hamsters au total\n" , totHamster);
            printf("   %f kg de nourriture\n" , d.food);
            printf("   %d cages\n" , d.cage);
            printf("    \n");
            printf("les prix du jour sont:\n");
            printf("   les cages coutent %d $\n" , c->pxCage);
            printf("   la nourriture coute %d $ le kg\n" , pxFood);
            printf("   les hamsters adultes valent %d $\n" , pxHamster);
        }
        
        p->Selection(d, c, int pxHamster, int pxFood, &ps, p->Argument)
        
        
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
            newBabies -= death;
            death = 0;
        }
        totHamster = d.adultMale + d.adultFem + d.kidFem2 + d.kidMale2 + newBabies;
        d.kidFem = rand_a_b(0, newBabies);
        d.kidMale = newBabies - d.kidFem;

        if(totHamster == 0) check = 1;
    }

    int score = totHamster * c->pxHamsterMax + d.money;
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
    c.seed = 0;
    if(argc>1)
    {
        c.seed = atoi(argv[1]);//set seed
        srand(c.seed);
    }
    else  srand(time(NULL));
    
    

    game(0, &c, d);


    //if(argc<2) game(0);//set seed
    //else game(rand(), 0);
}