#include <stdio.h>
#include <string.h>
/* 
	menus
		+ 1 - menu principal
		+ 2 - menu do paciente

*/
int usuario=0;
int nivel=0;
FILE *fpaciente, *fagenda;

typedef struct paciente{
	char cpf[12];
	char nome[31];
	char telefone[10];
	int tipo_consulta;
}Paciente;


int opcao();
int menus(int);
int verificaCadastro(char*);
void cadastro(Paciente);
void salvaPaciente(Paciente);
void entreMenus();
void agenda();


int main(){	
	char cpf[11];
	int opcao;
	int i, j;
	Paciente p1;	

	


	while (usuario != 3){
		usuario = menus(1);		
		if (usuario == 3){
			printf("%s\n", "O sistema está sendo encerrado");
		}

		while (usuario == 1){

			if(verificaCadastro(cpf) == 0){
				cadastro(p1);

			} else {
				opcao = menus(2);
				if(opcao)
			}
		}
	}
	
	return 0;
}
int opcao(){
	int opcao = 0;
	scanf("%d", &opcao);
	return opcao;
}
int menus(int tipo){
	switch (tipo){
		case 1:
			printf("%s\n", "BEM VINDO A CLINICA MÉDICA BEM ESTAR\n1 - Paciente\n2 - Administrador\n3 - Sair do Sistema");
			return opcao();
			break;
		case 2:
			printf("%s\n", "MENU DO PACIENTE\n1 - Agendar uma consulta\n2 - Exibir minhas consultas\n3 - Alterar dados cadastrais\n4 - Voltar ao menu Prinipal");			
			return opcao();
			break;
	}
}

int verificaCadastro(char cpf[]){
	entreMenus();
	printf("%s\n", "\nINSIRA SEU CPF");
	scanf("%s", cpf);
	strcat(cpf, ".txt");
	if ((fpaciente = fopen(cpf, "r")) == NULL){
		printf("%s\n", "CPF NÃO CADASTRADO NO SISTEMA");
		entreMenus();
		return 0;
	} else{
		return 1;
	}
}

void cadastro(Paciente p){
	printf("%s", "MENU DO PACIENTE - Cadastro\n");
	printf("\nCPF: ");
	scanf("%s", p.cpf);
	printf("\nnome: ");
	scanf("%s", p.nome);
	printf("\nTELEFONE: ");
	scanf("%s", p.telefone);
	printf("\nTIPO DE CONSULTA (1 - particular | 2 - convenio): ");
	scanf("%d", &p.tipo_consulta);
	printf("\n%s\n%s\n%s\n%d\n", p.cpf, p.nome,p.telefone, p.tipo_consulta);
	salvaPaciente(p);
}

void salvaPaciente(Paciente p){
	char aux[20]="";
	strcat(aux, p.cpf);
	strcat(aux, ".txt");
	printf("%s\n", aux);
	fpaciente = fopen(aux, "w");
	fprintf(fpaciente, "\n%s\n%s\n%s\n%d\n", p.cpf, p.nome, p.telefone, p.tipo_consulta);
	fclose(fpaciente);
}

void entreMenus(){
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n################################################\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

void agenda(){
	int i, j;
	char horarios[6][9];

	printf("%s\n", "MENU DO PACIENTE - Agenda");

	if ((fagenda = fopen(cpf, "r+")) == NULL){
		for (i = 0; i++, i<5){ 
			for (j=0; j++; j<8){
				horarios[i][j] = '-';
				fprintf(fagenda, "%c\n", horarios);
			}
		}
	}
	
	
}