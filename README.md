# Lista de Tarefas

## Conceito
Projeto que implementa uma lista de tarefas com interface gráfica, com funcionalidade para escolher prioridade, adicionar tarefa, remover tarefa, desfazer ação e visualizar suas tarefas. Feito para a disciplina de Estruturas de Dados

## Como usar
Ao executar o programa, a interface gráfica aparecerá.

![imagem](https://github.com/ryansakurai/ListaDeTarefas/blob/main/images/img1.png)

### Adicionar tarefa
1. Digite-a na primeira caixa;
2. Selecione seu nível de prioridade logo à direita;
3. Clique em “Adicionar tarefa”.

A lista é ordenada primariamente em relação à prioridade e secundariamente em ordem de
chegada.

![imagem](https://github.com/ryansakurai/ListaDeTarefas/blob/main/images/img2.png)

### Remover tarefa
1. Digite-a na segunda caixa;
2. Clique em “Remover tarefa”.

Se tiver mais de uma tarefa com o mesmo nome, a que aparecer primeiro na lista será
removida.

![imagem](https://github.com/ryansakurai/ListaDeTarefas/blob/main/images/img3.png)

### Desfazer ação
Ao clicar em “Desfazer ação”:
- se a ultima ação foi adicionar uma atividade, ela será removida;
- se a ultima ação foi remover uma atividade, ela será adicionada à lista como uma nova
atividade.

![imagem](https://github.com/ryansakurai/ListaDeTarefas/blob/main/images/img4.png)

## Recursos utilizados
O programa foi feito usando a biblioteca padrão da linguagem C e a biblioteca GTK3.

## Implementação
A interface gráfica foi implementada usando a bibliteca de interface gráfica GTK, a lista de tarefas usando uma lista ordenada e o sistema de desfazer ações usando uma pilha.

## Bugs/problemas conhecidos
Devido ao uso de uma lista ordenada, quando uma remoção é desfeita, a atividade não voltará à sua posição exata, mas sim ao topo das tarefas da mesma prioridade.

## Autores
- [Guilherme Bortoletto](https://github.com/guilherme-bortoletto)
- [Ryan Sakurai](https://github.com/ryansakurai)
- [Vinicius Castro](https://github.com/vinciuscastro)

(Estudantes de Ciência da Computação na UFSCar)
