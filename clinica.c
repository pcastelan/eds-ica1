#include <stdio.h>
/* 
	menus
		+ 1 - menu principal
		+ 2 - menu do paciente

*/
int usuario=0;
int nivel=0;

int opcao();
int menus(int);
int verificaCadastro(char*);
void cadastro();

int main(){	
	char *cpf;
	int opcao;
	usuario = menus(1);

	if (usuario == 3){
		printf("%s\n", "O sistema está sendo encerrado");
	}

	while (usuario != 3){

		while (usuario == 1){

			if(verificaCadastro(cpf) == 0){
				cadastro();

			} else {
			
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
			printf("%s\n", "MENU PACIENTE\n1 - Agendar uma consulta\n2 - Exibir minhas consultas\n3 - Alterar dados cadastrais\n4 - Voltar ao menu Prinipal");
			return opcao();
			break;
	}
}

int verificaCadastro(char *cpf){

}

void cadastro(){

}