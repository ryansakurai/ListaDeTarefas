# Lista de Tarefas - Projeto de Estruturas de Dados

## Conceito
Projeto que implementa uma lista de tarefas com interface gráfica, com funcionalidade para escolher prioridade, adicionar tarefa, remover tarefa, desfazer ação e visualizar suas tarefas.

## Como usar
Ao executar o programa, a interface gráfica aparecerá.

![imagem](https://github.com/kkurasai/ListaDeTarefas/blob/main/img00.png)

### Adicionar tarefa
1. Digite-a na primeira caixa;
2. Selecione seu nível de prioridade logo à direita;
3. Clique em “Adicionar tarefa”.

A lista é ordenada primariamente em relação à prioridade e secundariamente em ordem de
chegada.

![imagem](https://github.com/kkurasai/ListaDeTarefas/blob/main/img01.png)

### Remover tarefa
1. Digite-a na segunda caixa;
2. Clique em “Remover tarefa”.

Se tiver mais de uma tarefa com o mesmo nome, a que aparecer primeiro na lista será
removida.

![imagem](https://github.com/kkurasai/ListaDeTarefas/blob/main/img02.png)

### Desfazer ação
Ao clicar em “Desfazer ação”:
- se a ultima ação foi adicionar uma atividade, ela será removida;
- se a ultima ação foi remover uma atividade, ela será adicionada à lista como uma nova
atividade.

![imagem](https://github.com/kkurasai/ListaDeTarefas/blob/main/img03.png)

## Recursos utilizados
O programa foi feito usando a biblioteca padrão da linguagem C e a biblioteca GTK3.

## Implementação
A interface gráfica foi implementada usando a bibliteca de interface gráfica GTK, a lista de tarefas usando uma lista ordenada e o sistema de desfazer ações usando uma pilha.

## Bugs/problemas conhecidos
Devido ao uso de uma lista ordenada, quando uma remoção é desfeita, a atividade não voltará à sua posição exata, mas sim ao topo das tarefas da mesma prioridade.

## Autor
- Guilherme Bortoletto
- Ryan Sakurai
- Vinicius Castro

(Estudantes de Ciência da Computação na UFSCAR)
