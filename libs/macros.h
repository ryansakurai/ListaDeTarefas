//Guilherme Bortoletto
//Ryan Sakurai
//Vinicius Castro

#ifndef MACROS_H
#define MACROS_H

#include <time.h>


enum Level {LOW, MID, HIGH};
typedef enum Level Level;

typedef struct Task {
  char description[100];
  Level priority;
  unsigned index;
  time_t timestamp;
} Task;


enum Action {ADDITION, REMOVAL};
typedef enum Action Action;

typedef struct Change {
  Action description;
  Task target;
} Change;


#endif
