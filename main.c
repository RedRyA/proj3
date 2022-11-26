/* Ryan Reddoch
   CS-1714-B1
   Project Three
   main.c */

#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR_TRAP_BUFFER 1024
#define MAX_YEAR 2022
#define MIN_YEAR 1475
#define MIN_EDITION 1
#define MAX_EDITION 10
#define AUTHOR_CHAR_LIMIT 32
#define BOOK_TITLE_LIMIT 128
#define CITY_AND_PUB_LIMIT 64
#define ISBN_MIN 1000000000000
#define ISBN_MAX 9999999999999
#define MAX_COUNTER 2
#define DEF_CATALOG_NAME "cardcat.txt"
#define DEF_ARG_COUNT 3
typedef struct LIBRARY_STRUCT libraryStruct;
typedef struct COMMAND_PARAMS commParams;
/*
FIRST NAME:
LAST NAME:
BOOK TITILE:
EDITION:
PUB COMPAMNY:
PUB YEAR:
PUB CITY:
ISBN:
*/
struct COMMAND_PARAMS {

  char *fileName;
  size_t fileNameLen;
};

commParams cmdLineParams;

struct LIBRARY_STRUCT {

  // Author First Name //
  char *authorFName;
  size_t fNamelen;
  // Author Last Name //
  char *authorLName;
  size_t lNamelen;
  // Book Title //
  char *bookTitle;
  size_t bookTitleLen;
  // Book Edition //
  unsigned int bookEdition;
  // Publication Company //
  char *pubCompany;
  size_t pCompanyLen;
  // Publicatiuon Year //
  unsigned int pubYear;
  // Publication City //
  char *pubCity;
  size_t pCityLen;
  // ISBN-13 Number //
  unsigned long isbn;
};

int stringCheck(char str[ERROR_TRAP_BUFFER], size_t maxSize);
void getFName(char *nameEnter);
void getLName(char *nameEnter);
void getBookName(char *nameEnter);
void getBookEdit(unsigned int *val);
void getPubComp(char *nameEnter);
void getPubYear(unsigned int *val);
void getPubCity(char *nameEnter);
void getISBN(unsigned long *val);
void printCard(libraryStruct *card, FILE *fptr);
int parseParams(int argc, char *argv[]);

int main(int argc, char *argv[]) {

  FILE *cardOut;

  if (&cardOut == NULL) {
    printf("File Exists");
    cardOut = fopen(DEF_CATALOG_NAME, "r");
  }

  libraryStruct libStruct[MAX_COUNTER];
  libraryStruct *cardCat =
      (libraryStruct *)malloc(MAX_COUNTER * sizeof(libraryStruct));

  int counter = 0;
  int idx = 0;

  char buffer[ERROR_TRAP_BUFFER];
  size_t len;

  for (idx = 0; idx < MAX_COUNTER; idx++) {

    /////////// AUTHOR FIRST NAME  /////////////////

    getFName(buffer);
    len = strlen(buffer);

    libStruct[idx].authorFName = (char *)malloc((len + 1) * sizeof(char));
    strncpy(libStruct[idx].authorFName, buffer, (len + 1));

    libStruct[idx].fNamelen = (len);
    memset(buffer, '\0', ERROR_TRAP_BUFFER);

    ////////////// AUTHOR LAST NAME  ////////////////////////

    getLName(buffer);
    len = strlen(buffer);
    libStruct[idx].authorLName = (char *)malloc((len + 1) * sizeof(char));
    libStruct[idx].lNamelen = (len);

    strncpy(libStruct[idx].authorLName, buffer, (len + 1));
    memset(buffer, '\0', ERROR_TRAP_BUFFER);

    /////////////  BOOK TITILE  ////////////////////////

    getBookName(buffer);
    len = strlen(buffer);
    libStruct[idx].bookTitle = (char *)malloc((len + 1) * sizeof(char));
    libStruct[idx].bookTitleLen = (len);

    strncpy(libStruct[idx].bookTitle, buffer, (len + 1));
    memset(buffer, '\0', ERROR_TRAP_BUFFER);

    /////////////// BOOK EDITION  ////////////////////////

    getBookEdit(&libStruct[idx].bookEdition);

    //////////////// PUBLICATION COMPANY  ////////////////

    getPubComp(buffer);
    len = strlen(buffer);
    libStruct[idx].pubCompany = (char *)malloc((len + 1) * sizeof(char));
    libStruct[idx].pCompanyLen = (len);

    strncpy(libStruct[idx].pubCompany, buffer, (len + 1));
    memset(buffer, '\0', ERROR_TRAP_BUFFER);

    ///////////// PUBLICATION YEAR  //////////////////////

    getPubYear(&libStruct[idx].pubYear);

    /////////// PUBLICATION CITY  //////////////////////

    getPubCity(buffer);
    len = strlen(buffer);
    libStruct[idx].pubCity = (char *)malloc((len + 1) * sizeof(char));
    libStruct[idx].pCityLen = (len);

    strncpy(libStruct[idx].pubCity, buffer, (len + 1));
    memset(buffer, '\0', ERROR_TRAP_BUFFER);

    //////////////// ISBN  ////////////////////////

    getISBN(&libStruct[idx].isbn);

    counter++;

    if (counter < MAX_COUNTER) {

      printf("Would you like to continue?\n Y/N\n");
      scanf("%s", buffer);
      getchar();
      char ans = toupper(buffer[0]);
      memset(buffer, '\0', ERROR_TRAP_BUFFER);
      if (ans != 'Y') {
        break;
      }
    }
  }

  for (idx = 0; idx < counter; idx++) {

    printCard(&libStruct[idx], stdout);
  }

  printf("Would you like to save to a file? Y/N\n");
  scanf("%c", buffer);
  getchar();
  char ans = toupper(buffer[0]);
  printf("%c", ans);
  memset(buffer, '\0', ERROR_TRAP_BUFFER);
  if (ans == 'Y') {

    if (cardOut == NULL) {
      printf("Creating new file");
      cardOut = fopen(DEF_CATALOG_NAME, "w");
      for (idx = 0; idx < counter; idx++) {
        printCard(&libStruct[idx], cardOut);
      }

    } else if (cardOut != NULL) {
      cardOut = fopen(DEF_CATALOG_NAME, "a");
      for (idx = 0; idx < counter; idx++) {
        printCard(&libStruct[idx], cardOut);
      }
    }
  }

  for (idx = 0; idx < counter; idx++) {
    free(libStruct[idx].authorFName);
    free(libStruct[idx].authorLName);
    free(libStruct[idx].bookTitle);
    free(libStruct[idx].pubCompany);
    free(libStruct[idx].pubCity);
  }

  fclose(cardOut);

  return 0;
}

// check string //
int stringCheck(char str[ERROR_TRAP_BUFFER], size_t maxSize) {
  int strReturnSize = (int)(strlen(str) - maxSize);

  (strReturnSize <= 0)
      ? strReturnSize = 0
      : printf("Input size is too big, you are %d over, please try again \n",
               strReturnSize);

  return strReturnSize;
}

// First Name //
void getFName(char *nameEnter) {
  do {

    printf("What is the author's first name? \n");
    scanf(" %[^\n]*c", nameEnter);

  } while (stringCheck(nameEnter, AUTHOR_CHAR_LIMIT) > 0);
}

// Last Name //
void getLName(char *nameEnter) {

  do {
    printf("What is the author's last name? \n");
    scanf(" %[^\n]*c", nameEnter);

  } while (stringCheck(nameEnter, AUTHOR_CHAR_LIMIT) > 0);
}
// Book Title //
void getBookName(char *nameEnter) {

  do {
    printf("What is the book's title? \n");
    scanf(" %[^\n]*c", nameEnter);

  } while ((stringCheck(nameEnter, BOOK_TITLE_LIMIT) > 0));
}
// Book Edition //
void getBookEdit(unsigned int *val) {
  bool isGood;
  do {
    isGood = false;

    printf("What is the book's edition? \nEnter 1 if NA\n");
    scanf("%u", val);
    getchar();

    if (*val < MIN_EDITION || *val > MAX_EDITION) {
      printf("Book edition must be in between 1 and 10. ");
      isGood = true;
    }

  } while (isGood);
}

// Publication Company //
void getPubComp(char *nameEnter) {
  do {
    printf("What is the publication company? \n");
    scanf(" %[^\n]*c", nameEnter);

  } while ((stringCheck(nameEnter, CITY_AND_PUB_LIMIT) > 0));
}

// Publication Year //
void getPubYear(unsigned int *val) {
  bool isGood;
  do {
    isGood = false;

    printf("What is the publication year?\n");
    scanf("%u", val);
    getchar();

    if ((*val < MIN_YEAR) || (*val > MAX_YEAR)) {
      printf("Publication year must be between 1475 and 2022\n");
      isGood = true;
    }

  } while (isGood);
}

// Publication City //
void getPubCity(char *nameEnter) {
  do {

    printf("What is the publication city?\n");
    scanf(" %[^\n]*c", nameEnter);

  } while ((stringCheck(nameEnter, CITY_AND_PUB_LIMIT) > 0));
}

// ISBN //
void getISBN(unsigned long *val) {
  bool isGood;
  do {
    isGood = false;

    printf("What is the ISBN-13 number?\n");
    scanf("%lu", val);
    getchar();
    if ((*val < ISBN_MIN) || (*val > ISBN_MAX)) {
      printf("ISBN-13 must be 13 digits long\n");
      isGood = true;
    }

  } while (isGood);
}

void printCard(libraryStruct *card, FILE *fptr) {

  fprintf(fptr, "\nAuthor's First Name: %s", card->authorFName);
  fprintf(fptr, "\nAuthor's Last Name: %s", card->authorLName);
  fprintf(fptr, "\nBook Title: %s", card->bookTitle);
  fprintf(fptr, "\nBook Edition: %d", card->bookEdition);
  fprintf(fptr, "\nPublication Company: %s", card->pubCompany);
  fprintf(fptr, "\nPublication Year: %d", card->pubYear);
  fprintf(fptr, "\nPublication City %s", card->pubCity);
  fprintf(fptr, "\nISBN: %lu \n", card->isbn);
}

int parseParams(int argc, char *argv[]) {
  size_t len;
  if (argc != DEF_ARG_COUNT) {
    return -1;
  }
  int idx = 1;
  for (; idx < DEF_ARG_COUNT; idx++) {

    switch (argv[idx][1]) {
    case 'f':
      if (idx++ < DEF_ARG_COUNT) {
        len = strlen(argv[idx] + 1);
        cmdLineParams.fileName = (char *)malloc(len * sizeof(char));
        if (cmdLineParams.fileName != NULL) {
          strcpy(cmdLineParams.fileName, argv[idx]);
          cmdLineParams.fileNameLen = strlen(cmdLineParams.fileName);
        } else {
          return -4;
        }
        cmdLineParams.fileNameLen = len;
      }

      break;
    default:
      return -2;
    }
  }
}
