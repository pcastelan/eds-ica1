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
FILE *fpaciente, *fagenda, *fpconsulta;
char pacienteLogado[12];

typedef struct paciente{
	char cpf[12];
	char nome[31];
	char telefone[10];
	int tipo_consulta;
}Paciente;


void agenda();
void alterarCadastro();
void cadastro(Paciente);
Paciente carregaDados(char[]);
void carregaConsultas();
void entreMenus();
void imprimeAgenda(int);
void marcaConsulta();
int menus(int);
int opcao();
void salvaAgenda();
void salvaPaciente(Paciente);
int verificaCadastro(char*);


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
					marcaConsulta();
				}
				if(opcao == 3){
					alterarCadastro();
				}
				if(opcao == 2){

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
		fagenda = fopen("agenda.txt", "w");
		for(i=0; i<5; i++){
			fprintf(fagenda, "\n");
			for(j=0; j<8; j++){
				fprintf(fagenda, "%c ", consultas[i][j]);
			}
		}
		fclose(fagenda);
	
}

void imprimeAgenda(int tipo){
	int i;
		printf("%s\n", "MENU DO PACIENTE - Agenda\n");

		// se tipo= 2 imprime o agendado pelo paciente logado
    if(tipo == 2){
        char aux[20];
        strcpy(aux, "");
        strcat(aux, pacienteLogado);
        strcat(aux, "_c.txt");
        fpconsulta = fopen(aux, "r");
        if (fpconsulta == NULL){
            printf("Você não tem consultas agendadas");
        } else {
            while (!(feof(fagenda))){
                // consulta na posicao do fpconsulta recebe "O"
            }
        }
    }

	int hora[8] = {8,9,10,11,13,14,15,16};
	printf("\t \t | \t SEG \t | \t TER \t | \t QUA \t | \t QUI \t | \t SEX \t |\n");
	for(i=0; i<8; i++){
		printf("%dh \t\t | \t  %c  \t | \t  %c  \t | \t  %c  \t | \t  %c  \t | \t  %c  \t |\n", hora[i], consultas[0][i], consultas[1][i], consultas[2][i],consultas[3][i], consultas[4][i]);
	}
	printf("%s\n", "[-] - Horarios livres\n[X] - Horarios ocupados");
}

/* carrega a matriz consultas a partir de agenda.txt*/
void carregaConsultas(){
	int i,j;
	char aux;
	fagenda = fopen("agenda.txt", "r");
	if(fagenda == NULL){

		for (i= 0; i<5; i++){
			fprintf(fagenda, "\n" );
			for (j=0; j<8; j++){
				consultas[i][j] = '-';
				fprintf(fagenda, "%c ", consultas[i][j]);
			}
		}
		fclose(fagenda);
	} else {
		for(i=0;i<5;i++){
				fscanf(fagenda, "\n");
			for (j=0; j<8; j++){
				fscanf(fagenda, "%c ", &consultas[i][j]);
			}
		}
	}
	fclose(fagenda);
}

/* altera os dados do cadastro do paciente*/
void alterarCadastro(){
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
			printf("Seu CPF atual é: %s\n", aux.cpf);
			if (!(strcmp(aux.cpf, pacienteLogado))){
				salvaPaciente(aux);
				char auxp[20];
				int i, j;
				strcpy(auxp, "");
				strcat(auxp, pacienteLogado);
				strcat(auxp, "_c.txt");
				fpconsulta=fopen(auxp, "r");
				strcpy(auxp, "");
				strcat(auxp, aux.cpf);
				strcat(auxp, "_c.txt");
				fagenda=fopen(auxp, "w");
				while(!(feof(fpconsulta))){
					fscanf(fpconsulta, "%d %d\n", &i, &j);
					fprintf(fagenda, "%d %d\n", i, j);
				}
				fclose(fpconsulta);
				fclose(fagenda);
				strcpy(pacienteLogado, aux.cpf);
			}
			break;
		case 2:
			printf("Seu NOME atual é: %s\nInsira o novo NOME: ", aux.nome);
			strcpy(aux.nome, "");
			scanf("%s", aux.nome);
			break;
		case 3:
			printf("Seu TELEFONE atual é: %s\nInsira o novo TELEFONE: ", aux.telefone);
			strcpy(aux.telefone, "");
			scanf("%s", aux.telefone);
			break;
		case 4:
			break;
	}
	salvaPaciente(aux);
}

/*paciente marca consulta*/
void marcaConsulta(){
	char dia[4], horario[3];
	int i,j;
	char aux[20];
	carregaConsultas();
	imprimeAgenda(1);
	printf("\n\nDia: ");
	scanf("%s", dia);
	printf("\n\nHorario: ");
	scanf("%s", horario);
	if ((strcmp(dia, "SEG")) == 0|| (strcmp(dia, "seg")) == 0){
		i = 0;
	} else if((strcmp(dia, "TER")) == 0 || (strcmp(dia, "ter")) == 0){
		i = 1;
	} else if((strcmp(dia, "QUA")) == 0 || (strcmp(dia, "qua")) == 0){
		i = 2;
	} else if((strcmp(dia, "QUI")) == 0 || (strcmp(dia, "qui")) == 0){
		i = 3;
	} else if((strcmp(dia, "SEX")) == 0 || (strcmp(dia, "sex")) == 0){
		i = 4;
	}

	if ((strcmp(horario, "8")) == 0 ){
		j = 0;
	} else if ((strcmp(horario, "9")) == 0 ){
		j = 1;
	} else if ((strcmp(horario, "10")) == 0 ){
		j = 2;
	} else if ((strcmp(horario, "11")) == 0 ){
		j = 3;
	} else if ((strcmp(horario, "12")) == 0 ){
		j = 4;
	} else if ((strcmp(horario, "14")) == 0 ){
		j = 5;
	} else if ((strcmp(horario, "15")) == 0 ){
		j = 6;
	} else if ((strcmp(horario, "16")) == 0 ){
		j = 7;
	}
	if(consultas[i][j] == '-'){
		strcpy(aux, pacienteLogado);
		strcat(aux, "_c.txt");
		fpconsulta=fopen(aux, "a");
		fprintf(fpconsulta, "%d %d\n", i, j);
		fclose(fpconsulta);
		consultas[i][j] = 'X';
		agenda();
	} else {
		printf("DATA OCUPADA, escolha novamente\n");
		entreMenus();
		marcaConsulta();
	}

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




