#include <stdio.h>
#include <string.h>

int usuario=0; // identifica o tipo de usuario
int nivel=0; //´para controle dos acessos dentro dos menus
char consultas[6][9]; // armazena as consultas 
FILE *fpaciente, *fagenda, *fpconsulta;
char pacienteLogado[12]; //cpf do paciente logado
char paciente_consultas[20][2]; //consultas do paciente logado


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
void carregaConsultas(int);
void carregaP_consultas();
int conv_dia(char[]);
int conv_horario(char[]);
void entreMenus();
void exibirConsultas();
void imprimeAgenda(int);
void marcaConsulta();
int menus(int);
int opcao();
void salvaPaciente(Paciente);
int verificaCadastro(char*);

int main(){
	char cpf[11];
	int opcao;
	int i, j;
	Paciente p1;
	if((fagenda = fopen("agenda.txt", "r"))==NULL){
		carregaConsultas(1);
	}
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
					exibirConsultas();
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

/*
	DESCRICAO: grava agenda.txt 
*/
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



/* 
	DESCRICAO:altera os dados do cadastro do paciente
*/
void alterarCadastro(){
	Paciente aux;
	int op;
	entreMenus();
	printf("MENU DO PACIENTE - Alterar Cadastro\n");
	aux = carregaDados(pacienteLogado);
	printf("\nCPF:%s\nNOME:%s\n\n\n1 - TELEFONE:%s\n", aux.cpf, aux.nome, aux.telefone);
	if(aux.tipo_consulta == 1){
		printf("2 - TIPO DE CONSULTA: 1 - Particular\n");
	} else {
		printf("2 - TIPO DE CONSULTA: 2 - Convenio\n");
	}
	printf("%s\n", "Insira a opcao do dado que deseja alterar");
	op = opcao();
	switch(op){
		case 1:
			printf("\nInsira o novo TELEFONE: ");
			strcpy(aux.telefone, "");
			scanf("%s", aux.telefone);			
			break;
		case 2:
			printf("%s\n","Insira o novo TIPO DE CONSULTA (1 ou 2)" );
			aux.tipo_consulta = opcao();
			while(op != 1 || op != 2){
				printf("OPÇÃO INVÁLIDA\nInsira novamente o novo tipo_consulta(1 ou 2)");
				aux.tipo_consulta = opcao();
			}
			break;
	}
	salvaPaciente(aux);
}

/*
	DESCRICAO: Recebe os dados do usuário
*/
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

/*
	DESCRICAO: funcao retorna os dados de um paciente;	
*/
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

/* 
	DESCRICAO: carrega a matriz consultas a partir de agenda.txt
*/
void carregaConsultas(int tipo){
	int i,j;
	char aux;
	printf("161");
	
	if(tipo){
		fagenda = fopen("agenda.txt", "w");
		for (i= 0; i<5; i++){
			fprintf(fagenda, "\n" );
			for (j=0; j<8; j++){
				consultas[i][j] = '-';
				fprintf(fagenda, "%c ", consultas[i][j]);
			}
		}
		fclose(fagenda);
	} else {
		fagenda = fopen("agenda.txt", "r");
		for(i=0;i<5;i++){
				fscanf(fagenda, "\n");
			for (j=0; j<8; j++){
				fscanf(fagenda, "%c ", &consultas[i][j]);
			}
		}
		fclose(fagenda);
	}
	
}

int conv_dia(char dia[]){
	int i;
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
	return i;
}
int conv_horario(char horario[]){
	int j;
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
	return j;
}

/* 
	DESCRICAO: limpa a tela entre os menus
*/
void entreMenus(){
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n################################################\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}


/*
	DESCRICAO: imprime a agenda na tela
*/
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
      	carregaConsultas(0);
      	carregaP_consultas();
				for(i=0; i<20; i++){

					consultas[paciente_consultas[i][0]][paciente_consultas[i][1]] = 'O';
				}
				carregaConsultas(1);

         
         


          
      }
  }
	int hora[8] = {8,9,10,11,13,14,15,16};
	printf("\t \t | \t SEG \t | \t TER \t | \t QUA \t | \t QUI \t | \t SEX \t |\n");
	for(i=0; i<8; i++){
		printf("%dh \t\t | \t  %c  \t | \t  %c  \t | \t  %c  \t | \t  %c  \t | \t  %c  \t |\n", hora[i], consultas[0][i], consultas[1][i], consultas[2][i],consultas[3][i], consultas[4][i]);
	}
	printf("%s\n", "[-] - Horarios livres\n[X] - Horarios ocupados");
}


/*
	DESCRICAO: paciente marca consulta
*/
void marcaConsulta(){
	char dia[4], horario[3];
	int i,j;
	char aux[20];
	carregaConsultas(0);
	printf("269");
	imprimeAgenda(1);
	printf("271");
	printf("\n\nDia: ");
	scanf("%s", dia);
	printf("\n\nHorario: ");
	scanf("%s", horario);
	i = conv_dia(dia);
	j = conv_horario(horario);
	//verifica se a data escolhida está vazia
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

/*
	DESCRICAO: imprime os menus do sistema e recebe a entrada da opcao do usuario
		+ 1 - menu principal
		+ 2 - menu do paciente
*/
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

/*
	DESCRICAO: le a opcao (numero inteiro) do usuario e retorna
*/
int opcao(){
	int opcao = 0;
	scanf("%d", &opcao);
	return opcao;
}

/*
	DESCRICAO: salva os dados do paciente num arquivo
*/
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

/*
	DESCRICAO: verifica se o paciente esta cadastrado no sistema
*/
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


/*
	DESCRICAO: funcao do menu exibir consultas
*/
void exibirConsultas(){
	imprimeAgenda(2);

}

void carregaP_consultas(){
	char aux[20]="";
	int i=0, auxi, auxj;
	strcat(aux, pacienteLogado);
	strcat(aux, "_c.txt");
	fpconsulta = fopen(aux, "r");
	//carrega no vetor o conteudo do arquivo de consultas do paciente
	while(!(feof(fagenda))){
		fscanf(fagenda, "%d %d", &auxi, &auxj);
		paciente_consultas[i][0] = auxi;
		paciente_consultas[i][1] = auxj;
		i++;
	}
	paciente_consultas[i][0] = 11;
	paciente_consultas[i][1] = 11;

}


// void gravaP_consultas(){
// 		char aux[20]="";
// 	int i=0;
// 	strcat(aux, pacienteLogado);
// 	strcat(aux, "_c.txt");
// 	fpconsulta = fopen(aux, "r");
// 	//carrega no vetor o conteudo do arquivo de consultas do paciente
// 	while(!(feof(agenda))){
// 		fscanf(fagenda, "%d %d", &paciente_consultas[i][0], &paciente_consultas[i][1]);
// 		i++;
// 	}
// 	paciente_consultas[i][0] = 11;
// 	paciente_consultas[i][1] = 11;

// }