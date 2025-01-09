/* Integrantes do grupo
Ashmide jn Baptiste             - CP3025501 (Clientes)
Kézia Maria Pereira Francisco   - CP3025756 (Animais)
Rafaela Ferreira Dos santos     - CP3026353 (consultas)
*/

#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>// localtime()para obter os dados atuais do sistema

#define MAX_CLIENTES 100
#define MAX_NOME 50

#define MAX_ANIMAIS 100

//Cliente
typedef struct {
    int id;
    char nome[MAX_NOME];
    char telefone[MAX_NOME];
} Cliente;

//Animal
typedef struct {
    int id;
    char nome[50];
    char especie[30];
    int idade;
} Animal;

//Consulta
typedef struct {
    char cliente[100];
    char animal[100];
    char data[20];
    char hora[10];
    int ativo; // 1 para ativo, 0 para cancelado
} Consulta;


//variaveis globais
//CLIENTES
Cliente clientes[MAX_CLIENTES];
int totalClientes = 0;

//ANIMAIS
Animal animais[MAX_ANIMAIS];
int totalAnimais = 0;

//CONSULTAS
Consulta consultas[100];
int total_consultas = 0;
char caminho_arquivo_consultas[] = "consultas.txt";


// Submenu para gerenciamento de clientes
void menuClientes();  
void cadastrarCliente();
void listarClientes();
void editarCliente();
void excluirCliente();

// Submenu para gerenciamento de animais
void menuAnimais();   
void cadastrarAnimal();
void listarAnimais();
void editarAnimal();
void excluirAnimal();

// Submenu para gerenciamento de consultas
void menuConsultas();
void agendarConsulta();
void listarConsultas();
void editarConsulta();
void cancelarConsulta();


// Funções para manipulação de arquivos
//ANIMAIS
void salvarAnimais();
void carregarAnimais();
//CONSULTAS
void inicializar_arquivo_consultas();
void carregar_dados_consultas();
void salvar_dados_consultas();



int main() {
    setlocale(LC_ALL, "portuguese");
    //system("chcp 1252 > null");
    
    int opcao = -1;

    do {
        printf("\n=== Sistema de Clínica Veterinária ===\n\n");
        printf("1. Gerenciar Clientes\n");
        printf("2. Gerenciar Animais\n");
        printf("3. Gerenciar Consultas\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida. Por favor, insira um número.\n");

            while (getchar() != '\n'); 
            opcao = -1;
            continue;
        }

        switch (opcao) {
            case 1:
                menuClientes();
                break;
            case 2:
                menuAnimais();
                break;
            case 3:
                menuConsultas();
                break;
            case 0:
                printf("Encerrando o sistema...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

void menuClientes() {
    int opcao = -1;

    do {
        printf("\n=== Gerenciamento de Clientes ===\n");
        printf("1. Cadastrar Novo Cliente\n");
        printf("2. Listar Clientes\n");
        printf("3. Editar Cliente\n");
        printf("4. Excluir Cliente\n");
        printf("0. Voltar\n");
        printf("Escolha uma opção: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida. Por favor, insira um número.\n");

            while (getchar() != '\n'); 
            opcao = -1;
            continue;
        }

        switch (opcao) {
            case 1:
                cadastrarCliente();
                break;
            case 2:
                listarClientes();
                break;
            case 3:
                editarCliente();
                break;
            case 4:
                excluirCliente();
                break;
            case 0:
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);
}

void cadastrarCliente() {
    if (totalClientes >= MAX_CLIENTES) {
        printf("Limite de clientes atingido. Não é possível cadastrar mais clientes.\n");
        return;
    }
    Cliente novoCliente;
    novoCliente.id = totalClientes + 1;

    printf("Digite o nome do cliente: ");
    getchar();
    fgets(novoCliente.nome, MAX_NOME, stdin);
    novoCliente.nome[strcspn(novoCliente.nome, "\n")] = '\0';
    printf("Digite o telefone do cliente: ");
    fgets(novoCliente.telefone, MAX_NOME, stdin);
    novoCliente.telefone[strcspn(novoCliente.telefone, "\n")] = '\0';

    clientes[totalClientes] = novoCliente;
    totalClientes++;

    printf("Cliente cadastrado com sucesso!\n");
}

void listarClientes() {
    if (totalClientes == 0) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    printf("\n=== Lista de Clientes ===\n");
    for (int i = 0; i < totalClientes; i++) {
        printf("ID: %d\n", clientes[i].id);
        printf("Nome: %s\n", clientes[i].nome);
        printf("Telefone: %s\n", clientes[i].telefone);
        printf("----------------------\n");
    }
}

void editarCliente() {
    int idCliente;
    printf("Digite o ID do cliente que deseja editar: ");
    scanf("%d", &idCliente);

    if (idCliente < 1 || idCliente > totalClientes) {
        printf("Cliente não encontrado.\n");
        return;
    }

    Cliente* cliente = &clientes[idCliente - 1];

    printf("Digite o novo nome para o cliente: ");
    getchar();
    fgets(cliente->nome, MAX_NOME, stdin);
    cliente->nome[strcspn(cliente->nome, "\n")] = '\0';

    printf("Digite o novo telefone para o cliente: ");
    fgets(cliente->telefone, MAX_NOME, stdin);
    cliente->telefone[strcspn(cliente->telefone, "\n")] = '\0';

    printf("Cliente atualizado com sucesso!\n");
}

void excluirCliente() {
    int idCliente;
    printf("Digite o ID do cliente que deseja cancelar: ");
    scanf("%d", &idCliente);

    if (idCliente < 1 || idCliente > totalClientes) {
        printf("Cliente não encontrado.\n");
        return;
    }

    // Remove o cliente do array
    for (int i = idCliente - 1; i < totalClientes - 1; i++) {
        clientes[i] = clientes[i + 1];
    }

    totalClientes--;
    printf("Cliente cancelado com sucesso!\n");
}

void menuAnimais() {
    int opcao = -1;

    do {
        printf("\n=== Gerenciamento de Animais ===\n");
        printf("1. Cadastrar Novo Animal\n");
        printf("2. Listar Animais\n");
        printf("3. Editar Animal\n");
        printf("4. Excluir Animal\n");
        printf("0. Voltar\n");
        printf("Escolha uma opção: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida. Por favor, insira um número.\n");

            while (getchar() != '\n'); 
            opcao = -1;
            continue;
        }

        switch (opcao) {
            case 1:
                cadastrarAnimal();
                break;
            case 2:
                listarAnimais();
                break;
            case 3:
                editarAnimal();
                break;
            case 4:
                excluirAnimal();
                break;
            case 0:
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);
}

void cadastrarAnimal() {
    if (totalAnimais >= MAX_ANIMAIS) {
        printf("Limite de animais atingido.\n");
        return;
    }

    Animal novo;
    novo.id = totalAnimais + 1;
    printf("Nome do animal: ");
   scanf(" %49[^\n]", novo.nome);

    printf("Espécie: ");
    scanf(" %29[^\n]", novo.especie);
    printf("Idade: ");
    scanf("%d", &novo.idade);

    animais[totalAnimais] = novo;
    totalAnimais++;
    printf("Animal cadastrado com sucesso!\n");
}

void listarAnimais() {
    if (totalAnimais == 0) {
        printf("Nenhum animal cadastrado.\n");
        return;
    }

    printf("\n=== Lista de Animais ===\n");
    for (int i = 0; i < totalAnimais; i++) {
        printf("ID: %d, Nome: %s, Espécie: %s, Idade: %d\n", animais[i].id, animais[i].nome, animais[i].especie, animais[i].idade);
    }
}

void editarAnimal() {
    int id;
    printf("Informe o ID do animal que deseja editar: ");
    scanf("%d", &id);

    for (int i = 0; i < totalAnimais; i++) {
        if (animais[i].id == id) {
            printf("Novo nome: ");
            scanf(" %49[^\n]", animais[i].nome);
            printf("Nova espécie: ");
            scanf(" %29[^\n]", animais[i].especie);
            printf("Nova idade: ");
            scanf("%d", &animais[i].idade);
            printf("Animal atualizado com sucesso!\n");
            return;
        }
    }
    printf("Animal não encontrado.\n");
}

void excluirAnimal() {
    int id;
    printf("Informe o ID do animal que deseja excluir: ");
    scanf("%d", &id);

    for (int i = 0; i < totalAnimais; i++) {
        if (animais[i].id == id) {
            for (int j = i; j < totalAnimais - 1; j++) {
                animais[j] = animais[j + 1];
            }
            totalAnimais--;
            printf("Animal excluído com sucesso!\n");
            return;
        }
    }
    printf("Animal não encontrado.\n");
}

//ARQUIVO
void salvarAnimais() {
    FILE *arquivo = fopen("animais.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao salvar os dados dos animais.\n");
        return;
    }

    for (int i = 0; i < totalAnimais; i++) {
        fprintf(arquivo, "%d %s %s %d\n", animais[i].id, animais[i].nome, animais[i].especie, animais[i].idade);
    }
    fclose(arquivo);
}

void carregarAnimais() {
    FILE *arquivo = fopen("animais.txt", "r");
    if (arquivo == NULL) {
        printf("Nenhum arquivo de dados encontrado. Iniciando com lista vazia.\n");
        return;
    }

    while (fscanf(arquivo, "%d %s %s %d", &animais[totalAnimais].id, animais[totalAnimais].nome, animais[totalAnimais].especie, &animais[totalAnimais].idade) != EOF) {
        totalAnimais++;
    }
    fclose(arquivo);
}

void menuConsultas() {
    int opcao = -1;

    do {
        printf("\n=== Gerenciamento de Consultas ===\n");
        printf("1. Agendar Consulta\n");
        printf("2. Listar Consultas\n");
        printf("3. Editar Consulta\n");
        printf("4. Cancelar Consulta\n");
        printf("0. Voltar\n");
        printf("Escolha uma opção: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida. Por favor, insira um número.\n");

            while (getchar() != '\n'); 
            opcao = -1;
            continue;
        }

        switch (opcao) {
            case 1:
                agendarConsulta();
                break;
            case 2:
                listarConsultas();
                break;
            case 3:
                editarConsulta();
                break;
            case 4:
                cancelarConsulta();
                break;
            case 0:
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);
}

void agendarConsulta() {
    if (total_consultas >= 100) {
        printf("Capacidade máxima de consultas atingida!\n");
        return;
    }

    Consulta nova;
    printf("Digite o nome do cliente: ");
    scanf(" %99[^\n]", nova.cliente);
    printf("Digite o nome do animal: ");
    scanf(" %99[^\n]", nova.animal);

    struct tm data_inserida = {0};
    struct tm *data_atual;
    time_t t = time(NULL);

    data_atual = localtime(&t);

    // Loop para validar a data
    int data_valida = 0;
    while (!data_valida) {
        printf("Digite a data da consulta (dd/mm/aaaa): ");
        scanf(" %19[^\n]", nova.data);
        if (sscanf(nova.data, "%d/%d/%d", &data_inserida.tm_mday, &data_inserida.tm_mon, &data_inserida.tm_year) != 3) {
            printf("Formato inválido. Tente novamente.\n");
            continue;
        }

        data_inserida.tm_mon -= 1;
        data_inserida.tm_year -= 1900;

        // Comparar com a data atual
        if (mktime(&data_inserida) >= mktime(data_atual)) {
            data_valida = 1;
        } else {
            printf("A data não pode ser no passado. Insira uma data futura.\n");
        }
    }

    printf("Digite a hora da consulta (hh:mm): ");
    scanf(" %9[^\n]", nova.hora);
    nova.ativo = 1;

    consultas[total_consultas++] = nova;
    salvar_dados_consultas();

    printf("Consulta agendada com sucesso!\n");
}

void listarConsultas() {
    if (total_consultas == 0) {
        printf("Nenhuma consulta cadastrada.\n");
        return;
    }

    for (int i = 0; i < total_consultas; i++) {
        if (consultas[i].ativo) {
            printf("\nConsulta %d:\n", i + 1);
            printf("Cliente: %s\n", consultas[i].cliente);
            printf("Animal: %s\n", consultas[i].animal);
            printf("Data: %s\n", consultas[i].data);
            printf("Hora: %s\n", consultas[i].hora);
        }
    }
}

void editarConsulta() {
    listarConsultas();

    int id;
    printf("\nDigite o número da consulta que deseja editar: ");
    scanf("%d", &id);

    // Verifica se o número da consulta é válido
    if (id < 1 || id > total_consultas || !consultas[id - 1].ativo) {
        printf("Consulta inválida!\n");
        return;
    }

    // Exibe os dados atuais da consulta
    Consulta *consulta = &consultas[id - 1];
    printf("\nConsulta Selecionada:\n");
    printf("Cliente: %s\n", consulta->cliente);
    printf("Animal: %s\n", consulta->animal);
    printf("Data: %s\n", consulta->data);
    printf("Hora: %s\n", consulta->hora);

    printf("\n--- Edite os campos (ou pressione Enter para manter o atual) ---\n");

    printf("Digite o nome do cliente (%s): ", consulta->cliente);
    char buffer[100];
    getchar(); // Limpa o buffer
    fgets(buffer, 100, stdin);
    if (buffer[0] != '\n') {
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove o '\n' do fgets
        strcpy(consulta->cliente, buffer);
    }

    printf("Digite o nome do animal (%s): ", consulta->animal);
    fgets(buffer, 100, stdin);
    if (buffer[0] != '\n') {
        buffer[strcspn(buffer, "\n")] = '\0';
        strcpy(consulta->animal, buffer);
    }

    printf("Digite a data da consulta (%s): ", consulta->data);
    fgets(buffer, 20, stdin);
    if (buffer[0] != '\n') {
        buffer[strcspn(buffer, "\n")] = '\0';
        strcpy(consulta->data, buffer);
    }

    printf("Digite a hora da consulta (%s): ", consulta->hora);
    fgets(buffer, 10, stdin);
    if (buffer[0] != '\n') {
        buffer[strcspn(buffer, "\n")] = '\0';
        strcpy(consulta->hora, buffer);
    }

    // Salva as alterações no arquivo
    salvar_dados_consultas();
    printf("Consulta editada com sucesso!\n");
}

void cancelarConsulta() {
    listarConsultas();
    int id;
    printf("Digite o número da consulta que deseja cancelar: ");
    scanf("%d", &id);

    if (id < 1 || id > total_consultas || !consultas[id - 1].ativo) {
        printf("Consulta inválida!\n");
        return;
    }

    consultas[id - 1].ativo = 0;
    salvar_dados_consultas();

    printf("Consulta cancelada com sucesso!\n");
}

//ARQUIVO
void inicializar_arquivo_consultas() {
    FILE *fp = fopen(caminho_arquivo_consultas, "r");
    if (fp == NULL) {
        fp = fopen(caminho_arquivo_consultas, "w");
        fprintf(fp, "%d\n", total_consultas);
        fclose(fp);
    } else {
        fclose(fp);
    }
}

void carregar_dados_consultas() {
    FILE *fp = fopen(caminho_arquivo_consultas, "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo de consultas!\n");
        return;
    }

    fscanf(fp, "%d ", &total_consultas);
    for (int i = 0; i < total_consultas; i++) {
        fscanf(fp, "%99[^\n] ", consultas[i].cliente);
        fscanf(fp, "%99[^\n] ", consultas[i].animal);
        fscanf(fp, "%19[^\n] ", consultas[i].data);
        fscanf(fp, "%9[^\n] ", consultas[i].hora);
        fscanf(fp, "%d ", &consultas[i].ativo);
    }

    fclose(fp);
}

void salvar_dados_consultas() {
    FILE *fp = fopen(caminho_arquivo_consultas, "w");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo de consultas!\n");
        return;
    }

    fprintf(fp, "%d\n", total_consultas);
    for (int i = 0; i < total_consultas; i++) {
        fprintf(fp, "%s\n", consultas[i].cliente);
        fprintf(fp, "%s\n", consultas[i].animal);
        fprintf(fp, "%s\n", consultas[i].data);
        fprintf(fp, "%s\n", consultas[i].hora);
        fprintf(fp, "%d\n", consultas[i].ativo);
    }

    fclose(fp);
}

//FUNÇÃO PARA OBTER DATA ATUAL DO SISTEMA.
void obter_data_atual(int *dia, int *mes, int *ano) {
    time_t t = time(NULL); // Obtem o tempo atual em segundos desde 1970
    struct tm tm = *localtime(&t); // Converte para a estrutura de data local

    *dia = tm.tm_mday;
    *mes = tm.tm_mon + 1;
    *ano = tm.tm_year + 1900;
}

int verificar_data(int dia, int mes, int ano) {
    int dia_atual, mes_atual, ano_atual;
    obter_data_atual(&dia_atual, &mes_atual, &ano_atual);

    // Comparação de ano, mês e dia
    if (ano < ano_atual || 
        (ano == ano_atual && mes < mes_atual) || 
        (ano == ano_atual && mes == mes_atual && dia < dia_atual)) {
        return 0; // Data inválida (passada)
    }

    return 1; // Data válida
}
