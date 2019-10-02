#include <stdio.h>
#include <string.h>
#define MAX_N 26
#define MAX_T 2048

typedef struct
{
	char id;
	int c;
	int p;
	int d;
	int Comp_Sobra;
	int slack;
	int Prioridade;
	int Sobra_ctr;
	int p_aux;
	int d_aux;
} Task;

Task Tarefa;
Task task[MAX_N];
int Num_Premp = 0, Troca_Contexto = 0;

int main(void)
{
	int n_tasks = 0, time = 0, i, j, t;
	int leitura = 0;
	int iddle = 0;
	char Gantt[MAX_T];
	int Sobra[MAX_T];
	int flag = 1, clear;
	int aux_ponteiro = 0, aux_slack = 65535, aux_prioridade = 65535;
	int iddle_total = 0;
	int flag_iddle = 1;
	while (1)
	{
		//read
		printf("Nº de Tarefas \nTempo de Simulacao\n");
		scanf("%d %d", &n_tasks, &time);
		if ((n_tasks == 0) || (time == 0))
			break;
		for (leitura = 0; leitura < n_tasks; leitura++)
		{
			task[leitura].id = 'A' + leitura; 
			printf("\nTempo de Computacao (C) \nPeriodo (P) \nDeadline(D)\n");
			scanf("%d %d %d", &(task[leitura].c), &(task[leitura].p), &(task[leitura].d));
			task[leitura].Sobra_ctr = 1;
			Sobra[leitura] = 1;
			task[leitura].Comp_Sobra = task[leitura].c; 
			task[leitura].p_aux = task[leitura].p;
			task[leitura].d_aux = task[leitura].d;
			task[leitura].Prioridade = task[leitura].Prioridade + leitura;

			//printf("task %d \nsobra %d\nCtr %d\n", leitura, task[leitura].Comp_Sobra, task[leitura].Sobra_ctr);

		}

		/*for (i = 0; i < n_tasks; ++i)
		{
			printf("T(%c) = [(C:%d);(P:%d);(D:%d)] ", task[i].id, task[i].c, task[i].p, task[i].d);
			if ((i % 2) != 0)
			printf("\n");
		}*/

		for (clear = 0; clear < time; clear++)
		{
			Gantt[clear] = '.';
		}
		for (t = 0; t < time; t++)
		{
			flag_iddle = 1;
			//calcula os slack para cada tempo

			for (i = 0; i < n_tasks; i++)
			{
				printf("Tempo Atual %d\nPeriodo da Task %c==%d \n", t, task[i].id, task[i].p);
				printf("Calculo Periodo da Task %c %d==%d \n", task[i].id, (task[i].p_aux), (t));
				if (t == 0)
				{
					printf("Zerei A Vida \n");
					task[i].p_aux = task[i].p;
					task[i].d_aux = task[i].d;
					task[i].Comp_Sobra = task[i].c;
					printf("Tarefa %c\nComp_Sobra==%d\nComp da Task==%d \n", task[i].id, task[i].Comp_Sobra, task[i].c);
					task[i].slack = ((task[i].d_aux - t) - task[i].Comp_Sobra);
					printf("Tarefa %c\nSlack==%d\n", task[i].id, task[i].slack);
					flag = 1;
					task[i].Sobra_ctr = 1;
					printf("Zerei A Vida \n");
				}
				else if (task[i].p_aux == t)
				{
					printf("Zerei A Vida 2 \n");
					task[i].p_aux = task[i].p_aux + task[i].p;
					task[i].d_aux = task[i].d_aux + task[i].p;
					task[i].Comp_Sobra = task[i].c;
					printf("Tarefa %c\nComp_Sobra==%d\nComp da Task==%d \n", task[i].id, task[i].Comp_Sobra, task[i].c);
					task[i].slack = ((task[i].d_aux - t) - task[i].Comp_Sobra);
					printf("Tarefa %c\nSlack==%d\n", task[i].id, task[i].slack);
					flag = 1;
					task[i].Sobra_ctr = 1;
					printf("Zerei A Vida  2\n");
				}
				else
				{
					printf("task %c p %d \n", task[i].id, task[i].p);
					printf("task %c sobra %d Slack %d \n", task[i].id, task[i].Comp_Sobra, task[i].slack);
					if ((task[i].Comp_Sobra >= 1) && (task[i].Sobra_ctr == 1))
					{
						printf("task %c sobra %d \n", task[i].id, task[i].Comp_Sobra);
						task[i].slack = ((task[i].d_aux - t) - task[i].Comp_Sobra);
						printf("task %c slack %d \n", task[i].id, task[i].slack);
						flag = 1;
					}
					else
					{
						task[i].Sobra_ctr = 0;
						//Sobra[t] = task[i].Sobra_ctr;
						task[i].slack = 65535;
						printf("Entrei no ELSE do ELSE\n");
					}
				}
			}
			//escolhe o com menor slack

			aux_ponteiro = 0;
			aux_slack = 65535;
			aux_prioridade = 65535;

			for (i = 0; i < n_tasks; i++)
			{
				if (task[i].slack < aux_slack)
				{
					aux_slack = task[i].slack;
					aux_ponteiro = i;
					aux_prioridade = task[i].Prioridade;
					Tarefa.id = task[i].id;
					Tarefa.Comp_Sobra = task[i].Comp_Sobra;
				}
				else if (task[i].slack == aux_slack)
				{
					if (aux_prioridade > task[i].Prioridade)
					{
						aux_slack = task[i].slack;
						aux_ponteiro = i;
						aux_prioridade = task[i].Prioridade;
						Tarefa.id = task[i].id;
						Tarefa.Comp_Sobra = task[i].Comp_Sobra;
					}
				}
			}

			//decrementa a computacao
			printf("Quem saiu do comparador %c\n", Tarefa.id);
			for (i = 0; i < n_tasks; i++)
			{
				printf("Antes do IF Tarefa ID %c\nTask ID %c\nTask CompSobra %d\n", Tarefa.id, task[i].id, task[i].Comp_Sobra);
				if ((Tarefa.id == task[i].id) && (flag == 1) && (task[i].Sobra_ctr == 1))
				{
					task[i].Comp_Sobra = task[i].Comp_Sobra - 1;
					printf("Depois do IF Tarefa ID %c\nTask ID %c\nTask CompSobra %d\n", Tarefa.id, task[i].id, task[i].Comp_Sobra);
					flag = 0;
					printf("Flag==%d\nSobra Ctr %d\n", flag, task[i].Sobra_ctr);
				}
			}

			Gantt[t] = Tarefa.id;
			Sobra[t] = Tarefa.Comp_Sobra;
			iddle = 0;
			for (j = 0; j < n_tasks; j++)
			{
				printf("Sobra CTR %d da TAREFA %c\n", task[j].Sobra_ctr, task[j].id);
				if (task[j].Sobra_ctr == 0)
				{
					printf("ENTREI NO IF COM TASK %c\n IDDLE == %d\n", task[j].id, iddle);
					iddle++;
					printf("SAI NO IF COM TASK %c\n IDDLE == %d\n", task[j].id, iddle);
				}
				if (iddle == n_tasks)
				{
					printf("ENTREI NO IF FINAL COM TASK %c\n IDDLE == %d\n", task[j].id, iddle);
					iddle = 1;
					Gantt[t] = '.';
					printf("SAI NO IF FINAL COM TASK %c\n IDDLE == %d\n", task[j].id, iddle);

					if ((iddle == 1) && (Gantt[t] != Gantt[t - 1]))
					{

						Troca_Contexto = Troca_Contexto + 1;
						Num_Premp = Num_Premp + 1;

						flag_iddle = 0;
						printf("troca de contexto==%d do iddle", Troca_Contexto);
					}
				}
			}
			//calcula preempcoes

			printf("Task ID==%c\nSobra Ctr %d\nTask ID==%c\nSobra Ctr %d\n", Gantt[t], Sobra[t], Gantt[t - 1], Sobra[t - 1]);

			if ((Gantt[t] != Gantt[t - 1]) && (flag_iddle != 0))
			{
				Troca_Contexto++;
				printf("troca de contexto==%d processo", Troca_Contexto);
			}

			if ((Gantt[t] != Gantt[t - 1]) && (Sobra[t - 1] > 1))
			{
				Num_Premp++;
			}

			//printa no diagrama
			//printf("T: %d  S: %c \n", t,Tarefa.id);

			printf("\nGantt: %s\nP:  %d TC: %d \n\n", Gantt, Num_Premp, Troca_Contexto);
		}

		return 0;
	}
}
