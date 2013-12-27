#ifndef CONSTANTS_H
#define CONSTANTS_H

static const int BOARD_SIZE = 15;           // ilosc pol planszy
static const int GRID_STEP = 30;            // wymiar boku pojedynczego pola
static const int USER = 1;                  // wartosc uzytkownika na polu gry
static const int CPU = -1;                  // wartosc CPU na polu gry
static const int DIAMETER = 26;             // srednica kamienia
static const int FIRST_GRID_CENTRE = -210;  // srodek pierwszego pola na planszy (lewy gorny rog)

// punktacja za pola
static const int CPU_4 = 10000;
static const int USER_4 = 5000;

static const int CPU_3_PRIO_1_HIGH = 150;
static const int CPU_3_PRIO_1_LOW = 50;
static const int USER_3_PRIO_1_HIGH = 400;
static const int USER_3_PRIO_1_LOW = 150;

static const int CPU_3_PRIO_2_HIGH = 150;
static const int CPU_3_PRIO_2_MEDIUM = 100;
static const int CPU_3_PRIO_2_LOW = 70;
static const int USER_3_PRIO_2_HIGH = 400;
static const int USER_3_PRIO_2_MEDIUM = 300;
static const int USER_3_PRIO_2_LOW = 100;

static const int CPU_3_PRIO_3_HIGH = 80;
static const int CPU_3_PRIO_3_LOW = 40;
static const int USER_3_PRIO_3_HIGH = 100;
static const int USER_3_PRIO_3_LOW = 80;

static const int CPU_3_PRIO_4_HIGH = 40;
static const int CPU_3_PRIO_4_LOW = 20;
static const int USER_3_PRIO_4_HIGH = 80;
static const int USER_3_PRIO_4_LOW = 60;


#endif // CONSTANTS_H
