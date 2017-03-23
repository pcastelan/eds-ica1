# eds-ica1
primeiro trabalho da disciplina de estrutura de dados

### Requisitos
+ O sistema deve permitir que o próprio paciente faça o agendamento da sua consulta e que a secretária visualize todas as consultas agendadas.
+ O sistema deve verificar se o paciente já esta cadastrado no sistema antes de mostrar o menu do paciente.
+ Se o paciente não estiver cadastrado ele deve se cadastar antes de acessar o menu do paciente.
+ Menu do paciente:
  - Agendar uma consulta: 
  	 1. mostrar a agenda da semana, com um "X" nos horários já ocupados e um "-" nos horarios livres
  	 1. depois o paciente seleciona o dia desejado e um horario disponível
  	 1. se o horario escolhido estiver ocupado o sistema deve exibir uma mensagem de erro e reexibir a agenda.
  - Exibir minhas consultas agendadas:
  	 1. mostrar a agenda da semana, com um "X" nos horários já ocupados, um "-" nos horarios livres e um "O" nos horários agendados.
  	 1. um novo submenu
  	  + Alterar um agendamento: o sistema pede que o paciente informe o dia e horario do agendamento que deseja alterar e em seguida solicita o novo dia e horário. Se o novo dia e horário for valido, reagenda a consulta e retorna para o menu do paciente. Se for inválido o sistema exibe uma mensagem de erro e repete a operação.
      + Excluir um agendamento: o sistema pede que o paciente informe o dia e horario que deseja apagar, remove o agendamento e em seguida retorna para o menu do paciente. Se as entradas forem inválidas o sistema deve informar o erro e repetir a operação.
      + Voltar ao menu do paciente.
  - Alterar dados cadastrais: O sistema exibe o cpf e o nome do paciente e permite que ele altere telefone e tipo de consulta.
  - Voltar ao menu principal.
      
