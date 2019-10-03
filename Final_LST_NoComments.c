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
	int iddle_total =0;
	char Gantt[MAX_T];
	int Sobra[MAX_T];
	int flag = 1, clear;
	int aux_ponteiro = 0, aux_slack = 65535, aux_prioridade = 65535;
	int flag_iddle = 1;
	while (1)
	{
		//read
		scanf("%d %d", &n_tasks, &time);
		if ((n_tasks == 0) || (time == 0))
			break;
		for (leitura = 0; leitura < n_tasks; leitura++)
		{
			task[leitura].id = 'A' + leitura; 
			scanf("%d %d %d", &(task[leitura].c), &(task[leitura].p), &(task[leitura].d));
			task[leitura].Sobra_ctr = 1;
			Sobra[leitura] = 1;
			task[leitura].Comp_Sobra = task[leitura].c; 
			task[leitura].p_aux = task[leitura].p;
			task[leitura].d_aux = task[leitura].d;
			task[leitura].Prioridade = task[leitura].Prioridade + leitura;
		}

		for (clear = 0; clear < time; clear++)
		{
			Gantt[clear] = '\0';
		}

		for (t = 0; t < time; t++)
		{
			flag_iddle = 1;
			//calcula os slack para cada tempo

			for (i = 0; i < n_tasks; i++)
			{
				if (t == 0)
				{
					task[i].p_aux = task[i].p;
					task[i].d_aux = task[i].d;
					task[i].Comp_Sobra = task[i].c;				
					task[i].slack = ((task[i].d_aux - t) - task[i].Comp_Sobra);
					flag = 1;
					task[i].Sobra_ctr = 1;
				}
				else if (task[i].p_aux == t)
				{	
					task[i].p_aux = task[i].p_aux + task[i].p;
					task[i].d_aux = task[i].d_aux + task[i].p;
					task[i].Comp_Sobra = task[i].c;
					task[i].slack = ((task[i].d_aux - t) - task[i].Comp_Sobra);
					flag = 1;
					task[i].Sobra_ctr = 1;
				}
				else
				{
					if ((task[i].Comp_Sobra >= 1) && (task[i].Sobra_ctr == 1))
					{
						task[i].slack = ((task[i].d_aux - t) - task[i].Comp_Sobra);
						flag = 1;
					}
					else
					{
						task[i].Sobra_ctr = 0;
						task[i].slack = 65535;
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

			for (i = 0; i < n_tasks; i++)
			{
				if ((Tarefa.id == task[i].id) && (flag == 1) && (task[i].Sobra_ctr == 1))
				{
					task[i].Comp_Sobra = task[i].Comp_Sobra - 1;
					flag = 0;
				}
			}

			//calculo do iddle
			Gantt[t] = Tarefa.id;
			Sobra[t] = Tarefa.Comp_Sobra;
			iddle = 0;
			for (j = 0; j < n_tasks; j++)
			{
				if (task[j].Sobra_ctr == 0)
				{
					iddle++;
				}
				if (iddle == n_tasks)
				{
					iddle = 1;
					Gantt[t] = '.';
					if ((iddle == 1) && (Gantt[t] != Gantt[t - 1]))
					{
						iddle_total = iddle_total +1;
						Troca_Contexto = Troca_Contexto + 1;
						Num_Premp = Num_Premp + 1;
						flag_iddle = 0;
					}
				}
			}
			//calcula preempcoes e troca de contexto

			if ((Gantt[t] != Gantt[t - 1]) && (flag_iddle != 0))
			{
				Troca_Contexto++;
			}

			if ((Gantt[t] != Gantt[t - 1]) && (Sobra[t - 1] > 1))
			{
				Num_Premp++;
			}
			printf("\n%s\n%d %d \n\n", Gantt, (Num_Premp), (Troca_Contexto));
			if (t == (time -1)){
				Gantt[t] = '\0';
				//printf("\nGantt: %s\nP:  %d+%d=%d TC: %d+%d=%d \n\n", Gantt, (Num_Premp-iddle_total),(iddle_total),(Num_Premp), (Troca_Contexto-iddle_total),(iddle_total),(Troca_Contexto));
			}
		}

		return 0;
	}
}
