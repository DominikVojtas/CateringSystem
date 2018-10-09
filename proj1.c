/*************************************************
 * Subor: proj.c                                 *
 * Datum vytvorenia: 11/10/2014                  *
 * Datum poslednej upravy: 01:15 - 25/10/2014    *
 * Autor: Peter Tisovcik                         *
 * Projekt: Projekt 1 - Vypocty v tabulke        *
 ************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ROW 50 /* Maximalna dlzka riadka */
#define SECTION_NUMBER 3 /* Cislo, od ktoreho zacinaju parametre pre
                            vyber riadkov, stlpcov alebo rozsahu*/

/** Chybove kody programu */
enum errcode{
  ESUCCESS = 0, /**< Program prebehol v poriadku */
  ENARG, /**< Nebol zadany ziaden parameter */
  EUARG, /**< Bol zadany nepodporovany parameter/parametre */
  ELARG, /**< Bol zadany nedostatocny pocet parametrov */
  EMARG, /**< Boli zadane parametre navyse */
  ENEGARG, /**< Bol zadany zly argument, hodnoty mozu byt od 1, vratane 1 */
  ETWOISH, /**< Rozsah buniek musi byt a, b, kde a <= b */
  ENDATA, /**< Neboli najdene dalsie data na spracovanie */
  ENUMBER, /**< Na vykonanie tejto operacie musia byt v bunkach iba cisla */
  EOVRFLW, /**< Na riadok bolo zadanych viacej znakov ako je maximalny limit d*/
  EUNKNOWN /**< Neocakavana chyba */
};

/** Spravy programu */
char* errstr[] = {
  "Program prebehol v poriadku.",
  "Nebol zadany ziaden parameter.",
  "Bol zadany nepodporovany parameter/parametre.",
  "Bol zadany nedostatocny pocet parametrov.",
  "Boli zadane parametre navyse.",
  "Bol zadany zly argument, hodnoty mozu byt od 1, vratane 1.",
  "Rozsah buniek musi byt a, b, kde a <= b.",
  "Neboli najdene dalsie data na spracovanie, zadali ste neexistujuce ciso"
  "riadka/stlpca alebo v danom rozsahu sa nachada bunka bez dat.",
  "Na vykonanie tejto operacie musia byt v bunkach iba cisla.",
  "Na riadok bolo zadanych viacej znakov ako je maximalny limit.",
  "Neocakavana chyba."
};

/** Kody pre parametre programu */
enum comcode {
  HELP = 0,
  SELECT,
  MIN,
  MAX,
  SUM,
  AVG,
  ROW,
  COL,
  ROWS,
  COLS,
  RANGE,
  UNKNOWN
};

/** Textova reprezentacia parametrov programu */
char* command[] = {
  "--help",
  "select",
  "min",
  "max",
  "sum",
  "avg",
  "row",
  "col",
  "rows",
  "cols",
  "range",
  "unknown"
};

/** Struktura, ktora v sebe uchovava prvy a druhy
    argument a stav programu/chybovu spravu. */
typedef struct com{
  char com1; // Prvy argument
  char com2; // Druhy argument
  int argv[4]; // Pole argumentov pre operacie
  char status; //Stav programu/chybovy stav programu
} Tcom;

/* Sprava po zadani argumentu --help */
const char *HELPMSG =
  "*****************************************************************\n"
  "* Program: Vypocty v tabulke                                    *\n"
  "* Autor:   Peter Tisovcik 2014                                  *\n"
  "* ------------------------------------------------------------- *\n"
  "* Pouzitie:                                                     *\n"
  "*   ./proj1 [operacia] [vyber_buniek]                           *\n"
  "*   ./proj1 --help zobrazi sa napoveda                          *\n"
  "*                                                               *\n"
  "* operacia:                                                     *\n"
  "*   select          vypise hodnoty zadanych buniek              *\n"
  "*   min             vyhlada minimum z danych buniek             *\n"
  "*   max             vyhlada maximum z danych buniek             *\n"
  "*   sum             vypise sucet danych buniek                  *\n"
  "*   avg             vypise priemer danych buniek                *\n"
  "* vyber_buniek:                                                 *\n"
  "*   row             upresnuje vyber vsetkych buniek na riadku   *\n"
  "*   col             upresnuje vyber vsetkych buniek v stlpci    *\n"
  "*   rows X Y        upresnuje vyber vsetkych buniek od riadka   *\n"
  "*                   X az po Y, vrate X a Y                      *\n"
  "*   cols X Y        upresnuje vyber vsetkych buniek od stlpca   *\n"
  "*                   X az po Y, vrate X a Y                      *\n"
  "*   range A B X Y   upresnuje vyber vsetkych buniek od riadka   *\n"
  "*                   A az po B a od stlpca X po stlpec Y         *\n"
  "*                   vratane A, B, X, Y                          *\n"
  "*****************************************************************\n";

/** Print error message
 * Vypise spravu na zaklade chyboveho kodu programu
 * @param error Chybovy kod programu
 */
void printemsg(int error) {
  fprintf(stderr, "%s\n", errstr[error]);
}

/** Get arguments
 * Zisti argumenty programu a zapise ich do struktury,
 * na ktoru sa ukazuje v parametroch programu
 * @param argc Pocet argumentov
 * @param argv Pole argumentov
 * @param operation Ukazovatel na strukturu Tcom
*/
void get_argv(int argc, char** argv, Tcom* operation) {
  int count_argv = 0; /* Pocet argumentov, ktore sa maju spracovat */
  int k = 0; /* Index pola cisel v strukture Tcom */
  int temp;

  /* Podmienka vyhodnoti na zaklade operacie pocet argumentov,
     ktore sa maju spracovat */
  if (operation->com2 == ROW || operation->com2 == COL)
    count_argv = 1;
  else if (operation->com2 == ROWS || operation->com2 == COLS)
    count_argv = 2;
  else if (operation->com2 == RANGE)
    count_argv = 4;

  /* Podmienka vyhodnoti ci je pocet argumentov, ktore sa zadali do
     programu zhodny s poctom argumentov, ktore sa vyzaduju k prevedeniu
     jednotlivych operacii. Ak nezodpoveda pocet zadanych argumentov
     poctu argumentov, ktore aperacia potrebuje, vypise sa chyba */
  if ( count_argv == (argc - SECTION_NUMBER) ) {

    /* Cyklus, ktory zapise jednotlive argumenty operacie do struktury,
       a predtym sa kontroluje ci je zadany argument cislo ak ano prevedie
       sa na cislo a ulozi sa do stuktury. Ak nie je vrati sa chyba */
    /* Avsak cislo zmensime o 1, lebo dalej s tymto udajom nebudeme
       pracovat ako s cislom riadku ale s indexom, ktory zacina od 0 */
    for (int i = SECTION_NUMBER; i < SECTION_NUMBER + count_argv; i++) {
      temp = (atoi(argv[i]) - 1);
      if ( temp >= 0) {
        /* Ulozenie argumentu do strktury. */
        operation->argv[k] = temp;
        k++;
      } else
        /* Osetrenie ak sa zada zaporne cislo*/
        operation->status = ENEGARG;
    } /* Koniec cyklu */
  }
  else if (count_argv > (argc - SECTION_NUMBER))
    operation->status = ELARG; /* Chyba ak bolo zadanych malo parametrov */
  else
    operation->status = EMARG; /* Chyba ak bolo zadanych vela parametrov */

  /* Osetrenie ak sa zada b < a, podmienka mysli aj na stav, kedy
     sa bude pracovat iba s ROW a COL, cize vyzaduje sa iba jeden
     parameter a ostatne su 0 */
  if (( operation->argv[0] > operation->argv[1]) && operation->com2 != ROW && operation->com2 != COL)
    operation->status = ETWOISH;

  /* Osetrenie ak sa zada b < a */
  if (( operation->argv[2] > operation->argv[3]))
    operation->status = ETWOISH;
}

/** Get operation
 * Vyberie operaciu, ktora sa ma vykonat alebo
 * vrati chybovu spravu, ktora popisuje chybu.
 * @param argc Pocet argumentov
 * @param argv Pole argumentov
 * @return Vracia strukturu Tcom
 */
Tcom get_op(int argc, char** argv) {

  /* Deklaracia a inicializacia datovej struktury,
     hodnota -1 reprezentuje chybovy argument a
     v pripade, ze tato hodnota nebude vacsia ako -1
     vypise sa prisluchajuca chyba */
  Tcom operation = {
    .com1 = -1,
    .com2 = -1,
    .argv = {0,0,0,0},
    .status = ESUCCESS
  };

  /* Vyhodnoti ci bol zadany aspon jeden parameter */
  if (argc == 1 )
    operation.status = ENARG;

  /* Ak bol zadany len jeden parameter a to --help */
  else if (argc == 2 && (strcmp(argv[1], command[HELP]) == 0)) {
    operation.com1 = HELP;
    return operation;
  }

  /* Ak boli zadane aspon 3 parametre, zisti, ktore */
  else if (argc >= 3) {
    for (int i = 0; i <= AVG; i++) // Prvy argument
      if (strcmp(argv[1], command[i]) == 0)
        operation.com1 = i;

    for (int i = ROW; i <= RANGE; i++) // Druhy argument
      if (strcmp(argv[2], command[i]) == 0)
        operation.com2 = i;
  }

  /* Ak nebol najdeny argument vrati sa chybova hlaska
     V prvej podmienka sa testuje ci bo aspon jeden argument spravny
     V druhej podmienke sa testuje ci bol zadany zly druhy argument
     V tretej podmienke sa testuje ci bol zadany zly treti argument */
  if ( operation.com1 == -1 && operation.com2 == -1 )
    operation.status = EUARG;
  if (operation.com1 != -1 && !(operation.com2 <= RANGE && operation.com2 > -1) )
    operation.status = EUARG;
  if (operation.com2 != -1 && !(operation.com1 <= RANGE && operation.com1 > -1) )
    operation.status = EUARG;

  /* Ak operacia nebola --help tak sa zisti pocet argumentov,
     ktore treba na dalsie spracovanie vypisu, takisto sa aj
     ulozia do struktury*/
  if (operation.status == ESUCCESS)
    get_argv(argc, argv, &operation);

  return operation;
}

/** Read empty line
 * Cyklus, ktory preskoci riadky pokial nenajde zaciatocnu
 * hodnotu, od ktorej sa maju riadky vypisat alebo pokial
 * nie je koniec suboru
 * @param to Limit, do ktoreho ma citat prazdne riadky
 * @param last_char Vrati posledny nacitany znak
 */
void re_line(int to, int* last_char) {
  int i = 0, c;

  while (i != to && (c = getchar()) != EOF)
    if (c == '\n')
      i++;

  *last_char = c; /* Ulozenie posledneho znaku, vacsinou EOF ak je rozsah
                     znakov na vypisanie vacsi ako udajov na vstupe */
}

/** Get row
 * Funkcia vrati pole znakov z riadku, umoznuje, vratit pole,
 * obsahujuce len cisla, medzery a zamienka
 * @param only_digit Cislo vyjadruje ci ma byt retazec ciselny
 * @param pole Obahuje hodnoty z riadku
 * @param last_char Vrati posledny nacitany znak
 */
int get_row(int only_digit, char pole[MAX_ROW], int *last_char) {
  int j = 0, c;

  while ((c = getchar()) != EOF && c != '\n' && j < MAX_ROW) {

    /* Podmienka, ktora vrati kontroluje ci znak sa da previest na cislicu,
       pocita s tym ze medzeri sa neskor pouziju na rozdelenie pola na cisla,
       pocita s moznostou, ze cisla budu mat znamienka */
    if (only_digit == 1) {
      if (isspace(c))
        c = ' ';

      if (!isdigit(c) && c != ' ' && c != '-' && c != '+')
        return ENUMBER;
    }

    pole[j++] = c;
  }
  *last_char = c;

  /* Chyba v pripade ze pocet znakov je vacsi ako dovoluje
     konstanta */
  if (j == MAX_ROW)
    return EOVRFLW;

  pole[j] = '\0'; /* Na koniec retazca pridame znak koncu retazca */

  return ESUCCESS;
}

/** Get row for msa_col
 * Funkcia vrati pole znakov z riadku, umoznuje osetrit len tie
 * znaky, ktore sa budu vypisovat a osatne ignoruje
 * @param pole Obahuje hodnoty z riadku
 * @param from Hodnota(vratane), od ktorej sa maju citat stlpce
 * @param to Hodnota(vratane), do ktorej sa maju citat stlpce
 */
int get_row_col(char pole[MAX_ROW], int from, int to, int* last_char) {
  int j = 0, c;

  while ((c = getchar()) != EOF && c != '\n' && j < MAX_ROW) {
    if (isspace(c))
      c = ' ';

    if (!isdigit(c) && c != ' ' && c != '-' && c != '+' && j >= from && j <= to)
      return ENUMBER;

    pole[j++] = c;
  }
  *last_char = c;

  /* Chyba v pripade ze pocet znakov je vacsi ako dovoluje
     konstanta */
  if (j == MAX_ROW)
    return EOVRFLW;

  pole[j] = '\0'; /* Na koniec retazca pridame znak koncu retazca */

  return ESUCCESS;
}

/** Select rows
 * Vyberie riadok/riadky a vypise ho/ich na obrazovku
 * @param from Cislo riadku odkial sa ma zacat citat, vratane
 * @param to Cislo riadku, do ktoreho sa ma citat, vratane
 * @return Vracia kod chyby alebo uspesneho ukoncenia funkcie
 */
int select_rows(int from, int to) {
  int c, i = 0, temp;
  char pole[MAX_ROW];

  re_line(from, &c);

  /* Vypise riadky v danom rozsahu, v pripade, ze je koniec
     suboru, cyklus sa preskoci */
  for (i = from; i <= to && c != EOF; i++) {
    if ( (temp = get_row(0, pole, &c)) != ESUCCESS)
      return temp;
    printf("%s\n", pole);
  }

  /* Vypise chybu v pripade, ze sa zadal vacsi pocet riadkov ako
     je pocet riadkov s datami */
  if (i-1 != to)
    return ENDATA;

  return ESUCCESS;
}

/** Min, max, sum, avg rows
 * Na zaklade cisla prvej operacie vypise hodnotu a to bud
 * MIN, MAX, SUM alebo AVG, funkcia overuje ci su zadane
 * len cisla, pocita aj s moznostou, ze budu cisla uvedene
 * so znamienkom
 * @param from Cislo riadku odkial sa ma zacat citat, vratane
 * @param to Cislo riadku, do ktoreho sa ma citat, vratane
 * @return Vracia kod chyby alebo uspesneho ukoncenia funkcie
*/
int msa_rows(int from, int to, int com1) {
  int c, i = 0, k = 0, result = 0, temp;
  int pocet_cisiel = 0; /* Pocet cisel, sluzi na vypocet AVG */
  char pole[MAX_ROW];

  re_line(from, &c);

  /* Do pola sa ulozi retazec cakajuci na prevedenie na retazce
     rozdele na zaklade medzier a nasledne vykona MIN, MAX, SUM, AVG*/
  for (i = from; i <= to && c != EOF; i++)
  {
    if ( (temp = get_row(1, pole, &c)) != ESUCCESS)
      return temp;

    /* Koniec programu ak uz nie su data na citanie */
    if (strlen(pole) == 0 && c == (int)EOF)
      return ESUCCESS;

    /* Nahradime medzeri znakom \0 a postupne budeme nacitavat
       retazce a konvertovat na cislo v cykle. */
    char *data = strtok(pole, " ");

    while (data != NULL) {
      sscanf(data, "%d", &temp); /* Skonvertovanie stringu na cislo */

      /* Prvotne priradenie hodnoty do premennej, kora vyjadruje
         MIN, MAX okrem AVG a SUM, pretoze tie by a pripocitali dvakrat */
      if (k == 0 && com1 != SUM && com1 != AVG) {
        result = temp;
        k++;
      }

      /* Podmienka, ktora ulozi MIN, MAX, SUM alebo AVG z cisiel,
         ktore dostava na vstup */
      if (com1 == MIN && result > temp)
        result = temp;
      else if (com1 == MAX && result < temp)
        result = temp;
      else if (com1 == SUM)
        result += temp;
      else if (com1 == AVG) {
        result += temp;
        pocet_cisiel++;
      }

      data = strtok(NULL, " ");
    }
  } /* Koniec citania riadkov */

  /* Vypise MIN, MAX, SUM, AVG */
  if (com1 == AVG)
    printf("%.2f\n", (double) result/pocet_cisiel);
  else
    printf("%d\n", result);

  /* Vypise chybu v pripade, ze sa zadal vacsi pocet riadkov ako
     je pocet riadkov s datami */
  if (i-1 != to)
    return ENDATA;

  return ESUCCESS;
}

/** Select cols
 * Vyberie stlpec/stlpce a vypise ho/ich na obrazovku
 * @param from Cislo riadku odkial sa ma zacat citat, vratane
 * @param to Cislo riadku, do ktoreho sa ma citat, vratane
 * @return Vracia kod chyby alebo uspesneho ukoncenia funkcie
 */
int select_cols(int from, int to) {
  int temp, c, i;
  char pole[MAX_ROW] = {0};

  /* Cyklus, ktory pojde dovtedy pokym sa neskonci vstup alebo pokial
     ma data na vstupe alebo pokial nedojde k chybe */
  while(1) {
    if ( (temp = get_row(0, pole, &c)) != ESUCCESS)
      return temp;

    /* Koniec programu ak uz nie su data na citanie */
    if (strlen(pole) == 0 && c == (int)EOF)
      return ESUCCESS;

    /* Nahradime medzeri znakom \0 a postupne budeme nacitavat
       retazce a konvertovat na cislo v cykle. */
    char *data = strtok(pole, " ");

    i = 0; /* Pocitadlo poctu stlpcov*/
    while (data != NULL) {
      /* Ukoncenie v pripade ze je zadany vacsi pocet stlpcov ako sa
         objavilo na vstupe */
      if (i > to)
        break;

      /* Zobrazia sa iba data v zadanom rozsahu*/
      if (i >= from && i <= to)
        printf("%s\n", data);

      data = strtok(NULL, " ");
      i++;
    }

    /* Vrati chybu v pripade, ze bol zadany select na stlpce,
       ktore sa v zadanom rozsahu nevyskytuju */
    if (i-1 != to)
      return ENDATA;
  }
  return ESUCCESS;
}

/** Min, max, sum, avg cols
 * Na zaklade cisla prvej operacie vypise hodnotu a to bud
 * MIN, MAX, SUM alebo AVG
 * @param from Cislo riadku odkial sa ma zacat citat, vratane
 * @param to Cislo riadku, do ktoreho sa ma citat, vratane
 * @return Vracia kod chyby alebo uspesneho ukoncenia funkcie
*/
int msa_cols(int from, int to, int com1) {
  int c, temp = 0, k = 0, result = 0, pocet_cisiel = 0;
  char pole[MAX_ROW] = {0};

  /* Cyklus, ktory pojde dovtedy pokym sa neskonci vstup alebo pokial
     ma data na vstupe */
  while(1) {
    if ( (temp = get_row_col(pole, from, to, &c)) != ESUCCESS)
      return temp;

    /* Koniec programu ak uz nie su data na citanie */
    if (strlen(pole) == 0 && c == (int)EOF)
      break;

    /* Nahradime medzeri znakom \0 a postupne budeme nacitavat
       retazce a konvertovat na cislo v cykle. */
    char *data = strtok(pole, " ");

    int i = 0;
    while (data != NULL) {
      sscanf(data, "%d", &temp); /* Skonvertovanie stringu na cislo */

      /* Prvotne priradenie hodnoty do premennej, kora vyjadruje
         MIN, MAX, SUM alebo AVG */
      if (k == 0 && com1 != SUM && com1 != AVG) {
        result = temp;
        k++;
      }

      /* Ukoncenie v pripade ze je zadany vacsi pocet stlpcov ako sa
         objavilo na vstupe */
      if (i > to)
        break;

      /* Podmienka, ktora bud ulozi MIN, MAX, SUM alebo AVR z cisiel,
         ktore dostava na vstup */
      if (com1 == MIN && result > temp)
        result = temp;
      else if (com1 == MAX && result < temp)
        result = temp;
      else if (com1 == SUM)
        result += temp;
      else if (com1 == AVG) {
        result += temp;
        pocet_cisiel++;
      }

      data = strtok(NULL, " ");

      i++; /* Pocitadlo poctu stlpcov*/
    }

    /* Vrati chybu v pripade, ze bol zadany select na stlpce,
       ktore sa v zadanom rozsahu nevyskytuju */
    if (i-1 != to)
      return ENDATA;

  }

  /* Vypise MIN, MAX, SUM, AVG */
  if (com1 == AVG)
    printf("%.2f\n", (double) result/pocet_cisiel);
  else
    printf("%d\n", result);

  return ESUCCESS;
}

/** Select range
 * Vyberie rozsah z riadkov a stlpcov a tie vypise na obrazovku
 * @param x Cislo riadku odkial sa ma zacat citat, vratane
 * @param y Cislo riadku, do ktoreho sa ma citat, vratane
 * @param from Cislo stlpca, od ktoreho sa ma zacat citat, vratane
 * @param to Cislo stlpca, do ktoreho sa ma citat, vratane
 * @return Vracia kod chyby alebo uspesneho ukoncenia funkcie
 */
int select_range(int r_from, int r_to, int c_from, int c_to) {
  int temp, i, c;
  char pole[MAX_ROW] = {0};

  re_line(r_from, &c);

  /* Cyklus, ktory pojde dovtedy pokym sa neskonci vstup alebo pokial
     ma data na vstupe */
  while(r_from <= r_to && c != EOF) {
    if ( (temp = get_row(0, pole, &c)) != ESUCCESS)
      return temp;

    /* Nahradime medzeri znakom \0 a postupne budeme nacitavat
       retazce a konvertovat na cislo v cykle. */
    char *data = strtok(pole, " ");

    i = 0; /* Pocitadlo poctu stlpcov*/
    while (data != NULL) {
      /* Ukoncenie v pripade ze je zadany vacsi pocet stlpcov ako sa
         objavilo na vstupe */
      if (i > c_to)
        break;

      /* Zobrazia sa iba data v zadanom rozsahu*/
      if (i >= c_from && i <= c_to)
        printf("%s\n", data);

      data = strtok(NULL, " ");
      i++;
    }

    /* Vrati chybu v pripade, ze bol zadany select na stlpec,
       ktore sa v zadanom rozsahu nevyskytuju */
    if (i-1 != c_to)
      return ENDATA;

    r_from++; /* pocet riadkov*/
  }

  /* Vrati chybu v pripade, ze bol zadany select na riadok,
     ktore sa v zadanom rozsahu nevyskytuju */
  if (r_from-1 != r_to)
    return ENDATA;

  return ESUCCESS;
}

void select(Tcom* operation) {
  if (operation->com2 == ROW )
    operation->status = select_rows(operation->argv[0], operation->argv[0]);
  else if (operation->com2 == ROWS)
    operation->status = select_rows(operation->argv[0], operation->argv[1]);
  else if (operation->com2 == COL)
    operation->status = select_cols(operation->argv[0], operation->argv[0]);
  else if (operation->com2 == COLS)
    operation->status = select_cols(operation->argv[0], operation->argv[1]);
  else if (operation->com2 == RANGE)
    operation->status = select_range(operation->argv[0], operation->argv[1], operation->argv[2], operation->argv[3]);
}
void min(Tcom* operation) {
  if (operation->com2 == ROW)
    operation->status = msa_rows(operation->argv[0], operation->argv[0], MIN);
  if (operation->com2 == ROWS)
    operation->status = msa_rows(operation->argv[0], operation->argv[1], MIN);
  else if (operation->com2 == COL)
    operation->status = msa_cols(operation->argv[0], operation->argv[0], MIN);
  else if (operation->com2 == COLS)
    operation->status = msa_cols(operation->argv[0], operation->argv[1], MIN);
}
void max(Tcom* operation) {
  if (operation->com2 == ROW)
    operation->status = msa_rows(operation->argv[0], operation->argv[0], MAX);
  if (operation->com2 == ROWS)
    operation->status = msa_rows(operation->argv[0], operation->argv[1], MAX);
  else if (operation->com2 == COL)
    operation->status = msa_cols(operation->argv[0], operation->argv[0], MAX);
  else if (operation->com2 == COLS)
    operation->status = msa_cols(operation->argv[0], operation->argv[1], MAX);
}
void sum(Tcom* operation) {
  if (operation->com2 == ROW)
    operation->status = msa_rows(operation->argv[0], operation->argv[0], SUM);
  if (operation->com2 == ROWS)
    operation->status = msa_rows(operation->argv[0], operation->argv[1], SUM);
  else if (operation->com2 == COL)
    operation->status = msa_cols(operation->argv[0], operation->argv[0], SUM);
  else if (operation->com2 == COLS)
    operation->status = msa_cols(operation->argv[0], operation->argv[1], SUM);
}
void avg(Tcom* operation) {
  if (operation->com2 == ROW)
    operation->status = msa_rows(operation->argv[0], operation->argv[0], AVG);
  if (operation->com2 == ROWS)
    operation->status = msa_rows(operation->argv[0], operation->argv[1], AVG);
  else if (operation->com2 == COL)
    operation->status = msa_cols(operation->argv[0], operation->argv[0], AVG);
  else if (operation->com2 == COLS)
    operation->status = msa_cols(operation->argv[0], operation->argv[1], AVG);
}

/**
 * Hlavny program
 * @param argv Parametre pre vypis tabulky
 */
int main(int argc, char *argv[]) {

  Tcom operation = get_op(argc, argv);

  for (int i = 0; i < 4; i++)
    printf("%d\n", operation.argv[i]);
  printf("***************\n");


  if (operation.status != ESUCCESS) {
    printemsg(operation.status);
    return operation.status;
  }

  switch (operation.com1) {
    case HELP:
      printf("%s", HELPMSG);

      break;
    case SELECT:
      select(&operation);
      //select_data(&operation);
      break;
    case MIN:
      min(&operation);
      break;
    case MAX:
      max(&operation);
      break;
    case SUM:
      sum(&operation);
      break;
    case AVG:
      avg(&operation);
      break;
    default:
      printemsg(EUARG);
      break;
  }

  if (operation.status != ESUCCESS) {
    printemsg(operation.status);
    return operation.status;
  }

  return EXIT_SUCCESS;
}
