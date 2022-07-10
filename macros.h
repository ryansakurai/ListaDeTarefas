//Guilherme Bortoletto
//Ryan Sakurai
//Vinicius Castro

#ifndef MACROS_H
#define MACROS_H

enum nivel {baixa, media, alta};

typedef enum nivel nivel;

typedef struct atividade {
  char texto[100];
  nivel prioridade;
} atividade;

typedef struct acao {
  char texto[10];
  atividade atividade;
} acao;

#endif