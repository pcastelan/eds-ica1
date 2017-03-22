#include <stdio.h>
#include <string.h>
/* 
	menus
		+ 1 - menu principal
		+ 2 - menu do paciente
*/
int usuario=0;
int nivel=0;
char consultas[6][9];
FILE *fpaciente, *fagenda;
char pacienteLogado[12];

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
void imprimeAgenda();
void carregaConsultas();
void alterarCadastro();
void marcaConsulta();
Paciente carregaDados(char[]);


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

			if(nivel != 0){
				opcao = menus(2);
				if (opcao == 1){
					agenda();
				}
				if(opcao == 3){
					alterarCadastro();
				}				
				if(opcao == 4){
					usuario = 0;
					entreMenus();
				}
			} else {				
				if(verificaCadastro(cpf) == 0){
					cadastro(p1);
				} 
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
	char aux[20];
	entreMenus();
	printf("%s\n", "\nINSIRA SEU CPF");
	scanf("%s", cpf);
	strcpy(aux, cpf);	
	strcat(aux, ".txt");
	
	if ((fpaciente = fopen(aux, "r"))==NULL){
		printf("%s\n", "CPF NÃO CADASTRADO NO SISTEMA");
		entreMenus();
		return 0;
	} else{
		strcpy(pacienteLogado, cpf);
		printf("%s\n", pacienteLogado);
		nivel=1;
		return 1;
	}
	fclose(fpaciente);
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
	nivel = 1;
}

void salvaPaciente(Paciente p){
	char aux[20]="";
	strcat(aux, p.cpf);
	strcat(aux, ".txt");
	printf("%s\n", aux);
	fpaciente = fopen(aux, "w");
	fprintf(fpaciente, "\n%s\n%s\n%s\n%d\n", p.cpf, p.nome, p.telefone, p.tipo_consulta);
	fclose(fpaciente);
	strcpy(pacienteLogado, p.cpf);
}

void entreMenus(){
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n################################################\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

void agenda(){
	int i, j;
	printf("%s\n", "MENU DO PACIENTE - Agenda");
	if ((fagenda = fopen("agenda.txt", "r")) == NULL){
		fagenda = fopen("agenda.txt", "a+");
		for (i= 0; i<5; i++){ 
			fprintf(fagenda, "\n" );
			for (j=0; j<8; j++){
				consultas[i][j] = '-';
				fprintf(fagenda, "%c ", consultas[i][j]);
			}
		}
		fclose(fagenda);
		imprimeAgenda();
	} else {
		carregaConsultas();	
		imprimeAgenda();
	}	
}

void imprimeAgenda(){
	int i;
	int hora[8] = {8,9,10,11,13,14,15,16};
	printf("\t\t \t | \t SEG \t | \t TER \t | \t QUA \t | \t QUI \t | \t SEX \t |\n");
	for(i=0; i<8; i++){
		printf("%dh \t\t | \t  %c  \t | \t  %c  \t | \t  %c  \t | \t  %c  \t | \t  %c  \t |\n", hora[i], consultas[0][i], consultas[1][i], consultas[2][i],consultas[3][i], consultas[4][i]);
	}

}

void carregaConsultas(){
	//TODO: função que popula a matriz consultas a partir do arquivo agenda.txt
	int i,j;
	char aux;
	fagenda = fopen("agenda.txt", "r");
	for(i=0;i<5;i++){
			fscanf(fagenda, "\n");
		for (j=0; j<8; j++){
			fscanf(fagenda, "%c ", &consultas[i][j]);
		}
	}
	fclose(fagenda);
}


void alterarCadastro(){
	//TODO: função que permite que o usuário altere seus dados cadastrais
	Paciente aux;
	int opcao;
	entreMenus();
	printf("MENU DO PACIENTE - Alterar Cadastro\n");
	aux = carregaDados(pacienteLogado);
	printf("\n1 - CPF:%s\n2 - NOME:%s\n3 - TELEFONE:%s\n", aux.cpf, aux.nome, aux.telefone);
	if(aux.tipo_consulta == 1){
		printf("4 - TIPO DE CONSULTA: 1 - Particular\n");
	} else{
		printf("4 - TIPO DE CONSULTA: 2 - Convenio\n");
	}
	switch(opcao){
		case 1:
			// TODO: se o cpf for diferente do anterior tem que criar um arquivo novo 
			break;
		case 2:
			printf("Seu NOME atual é: %s\nInsira o novo NOME", aux.nome);
			strcpy(aux.nome, "");
			scanf("%s", aux.nome);
			break;
		case 3:
			printf("Seu TELEFONE atual é: %s\nInsira o novo TELEFONE", aux.telefone);
			strcpy(aux.telefone, "");
			scanf("%s", aux.telefone);
			break;
		case 4:
			//TODO: mudar tipo de consulta
			break;
	}
	salvaPaciente(aux);
}

void marcaConsulta(){
	//TODO: funcao que marca consulta
	char dia[4], horario[3];
	carregaConsultas();
	imprimeAgenda();
	printf("\n\nDia: ");
	scanf("%s", dia);
	printf("\n\nHorario: ");
	scanf("%s", horario);	
}

/*funcao retorna os dados de um paciente;	*/
Paciente carregaDados(char cpf[]){
	Paciente aux;
	char filename[20];
	strcpy(filename, cpf);
	strcat(filename, ".txt");
	printf("%s\n",filename);
	fpaciente = fopen(filename, "r");
	fscanf(fpaciente, "\n%s\n%s\n%s\n%d\n", aux.cpf, aux.nome, aux.telefone, &aux.tipo_consulta);
	fclose(fpaciente);
	return aux;
}