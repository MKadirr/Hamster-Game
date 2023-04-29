#define WEEK_MAX 52;
#define FOOD_WEEK 0.1;
#define PX_CAGE 100;
#define  SPACE_CAGE 10;

#define  FERTIL_MIN 2;
#define  FERTIL_MAX 10;

#define PX_HAMSTER_MIN 10;
#define PX_HAMSTER_MAX 30;

#define PX_FOOD_MIN 5;
#define PX_FOOD_MAX 20;

    
    //set data of the game
#define ADULT_MALE_BEGINNING 1;
#define ADULT_FEM_BEGINNING 1;
#define KID_MALE_BEGINNING 0;
#define KID_FEM_BEGINNING 0;
#define MONEY_BEGINNING 1000;
#define FOOD_BEGINNING 1.0;
#define CAGE_BEGINNING 1;
#define STARTING_WEEK 0;

typedef struct PurchaseSale{
    int maleSolded;
    int femSolded;
    int foodBuy;
    int cageBuy;
} PurchaseSale;

typedef struct Database{
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
} Database;

typedef struct Constant{
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
} Constant;

typedef struct Player{
    int flag;
    void (Selection*)(struct Database* d, struct Constant* c, int pxHamster, int pxFood, struct PurchaseSale *ps, void* arguments);
    void* Argument;
}

int rand_a_b(int min, int max);
/*provide a secure input for int*/
int secureInput(const char* text, const int available, const int unite);

int verification(int value, int available, int unite);

/* the whole game */
int game(int type, const struct Constant *c, struct Database d);

/*fonction for human input*/
void humanSelection(const struct Database *d, const struct Constant *c, int pxHamster, int pxCage, struct PurchaseSale *ps);