#ifndef FUNCOES_H_INCLUDED
#define FUNCOES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // Necessário para a função tolower()

// Estruturas de dados
struct add_produto
{
    char nome_p[50];  // Nome do produto
    float quantidade; // Quantidade do produto
    float preco;      // Preço do produto
};

struct add_fornecedor
{
    char nome_f[70];                 // Nome do fornecedor
    int dia, mes, ano;               // Data de entrega
    struct add_produto produtos[10]; // Array de produtos entregue, até 10
    int num_produtos;                // Numero de produtos que foram entregues
};

// Declaração das funções
void menuverdinho();
void menuAdm();
void menuUsuario();
void lerData(int *dia, int *mes, int *ano);
void cadastrarProduto(struct add_produto *produtos, int *contador);
void cadastrarFornecedor(struct add_fornecedor *fornecedor, int *contador);
void cadastrarFunc();
void exibirProdutos(struct add_produto *produtos, int *contador);
void exibirFornecedores(struct add_fornecedor *fornecedor, int *contador);
void exibirFunc();
void exibirvendas(struct add_produto *produtos, int *contador);
void editarProduto(struct add_produto *produtos, int *contador);
void editarFornecedor(struct add_fornecedor *fornecedor, int *contador);
void editarFunc();
void editarSaldo();
void remover_p(struct add_produto *produtos, int *contador);
void remover_f(struct add_fornecedor *fornecedor, int *contador);
void removerFunc();
void carregar_p(struct add_produto *produtos, int *contador);
void carregar_f(struct add_fornecedor *fornecedor, int *contador);
void carregar_func();
void carregar_s();
void salvar_p(struct add_produto *produtos, int contador);
void salvar_f(struct add_fornecedor *fornecedor, int contador);
void salvar_v(char *produtoNome, float quantidade, float total);
void salvar_u(char login[][50], char senha[][50], int contador);
void salvar_s(float saldo);
void saldoCaixa();
void venderProd(struct add_produto *produtos, int *contador);
void toLowerStr(char *str);
int loginFunc();

// Função com o nome do hortfruti
void menuverdinho()
{
    puts("===================");
    puts("Hortifruti verdinho");
    puts("===================\n");
}

// Função de exibição do menu para admin
void menuAdm()
{
    puts("Menu:");
    puts("1. Gerenciar Produto");
    puts("2. Gerenciar Fornecedor");
    puts("3. Gerenciar Usuário");
    puts("4. Gerenciar Venda");
    puts("5. Gerenciar Saldo em caixa");
    puts("6. Logar com outro usuário");
    puts("0. Sair");
}

// Função de exibição do menu para usuário
void menuUsuario()
{
    puts("Menu:");
    puts("1. Exibir Produtos");
    puts("2. Exibir Fornecedor");
    puts("3. Exibir saldo em caixa");
    puts("4. Realizar Venda");
    puts("5. Logar com outro usuário");
    puts("0. Sair");
}

// Função para ler a data (dia, mês e ano)
void lerData(int *dia, int *mes, int *ano)
{
    printf("Dia: ");
    while (scanf("%d", dia) != 1 || *dia < 1 || *dia > 31)
    {
        fflush(stdin);
        printf("Entrada inválida! Insira um dia válido (1-31): ");
    }
    printf("Mês: ");
    while (scanf("%d", mes) != 1 || *mes < 1 || *mes > 12)
    {
        fflush(stdin);
        printf("Entrada inválida! Insira um mês válido (1-12): ");
    }
    printf("Ano: ");
    while (scanf("%d", ano) != 1)
    {
        fflush(stdin);
        printf("Entrada inválida! Insira um ano válido: ");
    }
    return;
}

// Função para adicionar um produto
void cadastrarProduto(struct add_produto *produtos, int *contador)
{
    carregar_p(produtos, contador);
    if (*contador < 100)
    {                     
        char nomeTemp[50]; // Variável temporária para armazenar o nome do produto
        printf("Nome do produto: ");
        fflush(stdin);
        scanf("%49[^\n]", nomeTemp);

        // Converter o nome para minúsculas antes de comparar
        toLowerStr(nomeTemp);

        // Verifica se o produto já está cadastrado
        for (int i = 0; i < *contador; i++)
        {
            if (strcmp(produtos[i].nome_p, nomeTemp) == 0)
            {
                printf("Produto '%s' já está cadastrado.\n", nomeTemp);
                system("pause");
                return;
            }
        }

        // Se não estiver cadastrado, adiciona o produto
        strcpy(produtos[*contador].nome_p, nomeTemp);

        printf("Quantidade do produto em kg: ");
        while (scanf("%f", &produtos[*contador].quantidade) != 1)
        {
            fflush(stdin);
            printf("Entrada inválida! Entre com uma quantidade válida: ");
        }
        printf("Preço do produto por kg: ");
        while (scanf("%f", &produtos[*contador].preco) != 1)
        {
            fflush(stdin);
            printf("Entrada inválida! Entre com um preço válido: ");
        }
        puts("Produto cadastrado com sucesso.\n");
        (*contador)++;

        // Salva o produto no arquivo
        salvar_p(produtos, *contador);
    }
    else
    {
        puts("Limite de produtos atingido.\n");
    }
    system("pause");
}

// Função para adicionar um fornecedor
void cadastrarFornecedor(struct add_fornecedor *fornecedor, int *contador)
{
    carregar_f(fornecedor, contador);
    if (*contador < 100)
    { // Verifica se ainda há espaço para adicionar fornecedores
        printf("Nome do fornecedor: ");
        fflush(stdin);
        scanf("%69[^\n]", fornecedor[*contador].nome_f);

        printf("Data da entrega:\n");
        lerData(&fornecedor[*contador].dia, &fornecedor[*contador].mes, &fornecedor[*contador].ano);

        // Valida a quantidade de produtos
        printf("Quantidade de produto(s) entregue(s) (máx 10): ");
        while (1)
        {
            if (scanf("%d", &fornecedor[*contador].num_produtos) != 1 ||
                fornecedor[*contador].num_produtos < 1 ||
                fornecedor[*contador].num_produtos > 10)
            {
                fflush(stdin);
                printf("Entrada inválida! Informe um número entre 1 e 10: ");
            }
            else
            {
                break; // Entrada válida
            }
        }

        // Cadastro de múltiplos produtos
        for (int i = 0; i < fornecedor[*contador].num_produtos; i++)
        {
            printf("Cadastro do produto %d:\n", i + 1);
            printf("Nome do produto: ");
            fflush(stdin);
            scanf("%49[^\n]", fornecedor[*contador].produtos[i].nome_p);

            printf("Quantidade do produto em kg: ");
            while (1)
            {
                if (scanf("%f", &fornecedor[*contador].produtos[i].quantidade) != 1)
                {
                    fflush(stdin);
                    printf("Entrada inválida! Informe uma quantidade válida: ");
                }
                else
                {
                    break; // Entrada válida
                }
            }
        }

        puts("Fornecedor cadastrado com sucesso!\n");
        (*contador)++;

        // Salva todos os fornecedores no arquivo
        salvar_f(fornecedor, *contador);
    }
    else
    {
        puts("Limite de fornecedores atingido.\n");
    }
    system("pause");
}

// Função para cadastrar novo funcionário
void cadastrarFunc()
{
    carregar_func();
    char login[50];
    char senha[50];

    system("cls");
    menuverdinho();
    printf("\nCadastre o usuário: ");
    fflush(stdin);
    fgets(login, sizeof(login), stdin);
    strtok(login, "\n"); // Remove a nova linha do final

    printf("Cadastre a senha: ");
    fflush(stdin);
    fgets(senha, sizeof(senha), stdin);
    strtok(senha, "\n"); // Remove a nova linha do final

    printf("\nSucesso no cadastro do usuário!\n");

    // Salva o usuário no arquivo
    FILE *arq = fopen("informacoes_u.txt", "a");
    if (arq != NULL)
    {
        fprintf(arq, "%s\n%s\n", login, senha);
        fclose(arq);
    }
    else
    {
        puts("Erro ao abrir o arquivo para salvar os usuários.");
    }

    system("pause");
}

// Função para exibir produtos cadastrados
void exibirProdutos(struct add_produto *produtos, int *contador)
{
    carregar_p(produtos, contador);

    system("cls");
    menuverdinho();

    puts("Produtos cadastrados:\n");
    for (int i = 0; i < *contador; i++)
    {
        printf("Produto: %d\n", i + 1);
        printf("Nome: %s\n", produtos[i].nome_p);
        printf("Quantidade: %.2f/kg\n", produtos[i].quantidade);
        printf("Preço por kg: R$ %.2f\n\n", produtos[i].preco);
    }

    system("pause");
}

// Função para exibir fornecedores cadastrados
void exibirFornecedores(struct add_fornecedor *fornecedor, int *contador)
{
    carregar_f(fornecedor, contador);
    system("cls");
    menuverdinho();

    puts("Fornecedores cadastrados:\n");
    for (int i = 0; i < *contador; i++)
    {
        printf("Fornecedor %d:\n", i + 1);
        printf("Nome: %s\n", fornecedor[i].nome_f);
        printf("Data: %d/%d/%d\n", fornecedor[i].dia, fornecedor[i].mes, fornecedor[i].ano);
        for (int j = 0; j < fornecedor[i].num_produtos; j++)
        {
            printf("Produto %d:\n", j + 1);
            printf("Nome: %s\n", fornecedor[i].produtos[j].nome_p);
            printf("Quantidade: %.2f/kg\n", fornecedor[i].produtos[j].quantidade);
        }
        printf("\n");
    }
    system("pause");
}

char usuarios[100][50];  // Array para armazenar os nomes dos usuários
char senhas[100][50];    // Array para armazenar as senhas
int contador = 0;   // Contador de usuários cadastrados
// Função para exibir usuários cadastrados
void exibirFunc()
{
    carregar_func();

    if (contador == 0)
    {
        printf("Nenhum usuario cadastrado.\n");
        system("pause");
        return;
    }
    system("cls");
    menuverdinho();
    puts("Usuários cadastrados:");
    for (int i = 0; i < contador; i++)
    {
        printf("Usuário %d:\n", i + 1);
        printf("Login: %s\n", usuarios[i]);
        printf("Senha: %s\n\n", senhas[i]);
    }
    system("pause");
}

// Função para exibir vendas
void exibirvendas(struct add_produto *produtos, int *contador)
{
    FILE *arq;
    arq = fopen("informacoes_v.txt", "r");
    if (arq == NULL)
    {
        puts("Nenhuma venda realizada.");
        system("pause");
        return;
    }
    *contador = 0; // Reinicia o contador de produtos
    // Lê os produtos do arquivo
    while (fscanf(arq, "%49[^\n]\n%f\n%f\n",
                  produtos[*contador].nome_p,
                  &produtos[*contador].quantidade,
                  &produtos[*contador].preco) != EOF)
    {
        (*contador)++;
    }
    fclose(arq);

    system("cls");
    menuverdinho();
    puts("Vendas realizadas:\n");
    for (int i = 0; i < *contador; i++)
    {
        printf("Venda: %d\n", i + 1);
        printf("Nome: %s - ", produtos[i].nome_p);
        printf("Quantidade em kg: %.2f - ", produtos[i].quantidade);
        printf("Preço: R$ %.2f/kg\n\n", produtos[i].preco);
    }

    system("pause");
}

// Função para editar um produto
void editarProduto(struct add_produto *produtos, int *contador)
{
    carregar_p(produtos, contador);
    system("cls");
    menuverdinho();
    int edit;
    if (*contador == 0)
    {
        printf("Não há produtos cadastrados para editar.\n");
        system("pause");
        return; // Retorna imediatamente se não houver produtos
    }
    // Exibe os produtos cadastrados
    for (int i = 0; i < *contador; i++)
    {
        printf("Produto %d: %s\n", i + 1, produtos[i].nome_p);
    }
    printf("Qual produto deseja editar? (de 1 a %d): ", *contador);
    while (scanf("%d", &edit) != 1 || edit < 1 || edit > *contador)
    {
        fflush(stdin);
        printf("Entrada inválida! entre com o produto (1-%d): ", *contador);
    }
    edit--; // Ajusta o índice para o vetor
    // Permite editar o nome, quantidade e preço do produto
    printf("\nEditar nome do produto (atual: %s): ", produtos[edit].nome_p);
    fflush(stdin);
    scanf("%49[^\n]", produtos[edit].nome_p);

    printf("Editar quantidade em kg do produto (atual: %.2f/kg): ", produtos[edit].quantidade);
    while (scanf("%f", &produtos[edit].quantidade) != 1)
    {
        fflush(stdin);
        printf("Entrada inválida! Entre com uma quantidade válida: ");
    }
    printf("Editar preço em kg do produto (atual: R$ %.2f/kg): ", produtos[edit].preco);
    while (scanf("%f", &produtos[edit].preco) != 1)
    {
        fflush(stdin);
        printf("Entrada inválida! Entre com um preço válido: ");
    }
    puts("Produto editado com sucesso.\n");

    // Atualiza o arquivo com as informações editadas
    salvar_p(produtos, *contador);
    system("pause");
}

// Função para editar um fornecedor
void editarFornecedor(struct add_fornecedor *fornecedor, int *contador)
{
    carregar_f(fornecedor, contador);
    system("cls");
    menuverdinho();
    int edit;
    if (*contador == 0)
    {
        printf("Não há fornecedores cadastrados para editar.\n");
        system("pause");
        return;
    }
    // Exibe os fornecedores cadastrados
    for (int i = 0; i < *contador; i++)
    {
        printf("Fornecedor %d: %s\n", i + 1, fornecedor[i].nome_f);
    }

    printf("Qual fornecedor deseja editar? (de 1 a %d): ", *contador);
    while (scanf("%d", &edit) != 1 || edit < 1 || edit > *contador)
    {
        fflush(stdin);
        printf("Entrada inválida! Entre com o fornecedor (1-%d): ", *contador);
    }
    edit--; // Ajusta o índice para o vetor

    // Permite editar o nome, a data e a quantidade de produtos do fornecedor
    printf("\nEditar nome do fornecedor (atual: %s): ", fornecedor[edit].nome_f);
    fflush(stdin);
    scanf("%69[^\n]", fornecedor[edit].nome_f);

    printf("Data da entrega (atual: %d/%d/%d):\n", fornecedor[edit].dia, fornecedor[edit].mes, fornecedor[edit].ano);
    lerData(&fornecedor[edit].dia, &fornecedor[edit].mes, &fornecedor[edit].ano);

    printf("Quantidade de produtos (atual: %d): ", fornecedor[edit].num_produtos);
    while (1)
    {
        if (scanf("%d", &fornecedor[edit].num_produtos) != 1 || fornecedor[edit].num_produtos < 1 || fornecedor[edit].num_produtos > 10)
        {
            fflush(stdin);
            printf("Entrada inválida! Informe um número entre 1 e 10: ");
        }
        else
        {
            break; // Entrada válida
        }
    }

    // Cadastro de produtos
    for (int i = 0; i < fornecedor[edit].num_produtos; i++)
    {
        printf("Editar nome do produto (atual: %s): ", fornecedor[edit].produtos[i].nome_p);
        fflush(stdin);
        scanf("%49[^\n]", fornecedor[edit].produtos[i].nome_p);

        printf("Editar quantidade em kg do produto (atual: %.2f): ", fornecedor[edit].produtos[i].quantidade);
        while (1)
        {
            if (scanf("%f", &fornecedor[edit].produtos[i].quantidade) != 1)
            {
                fflush(stdin);
                printf("Entrada inválida! Informe uma quantidade válida: ");
            }
            else
            {
                break; // Entrada válida
            }
        }
    }

    puts("Fornecedor editado com sucesso.\n");
    salvar_f(fornecedor, *contador);
    system("pause");
}

// Função para editar um usuário
void editarFunc()
{
    carregar_func();
    system("cls");
    menuverdinho();
    if (contador == 0)
    {
        printf("Não há usuários cadastrados para editar.\n");
        system("pause");
        return;
    }
    // Exibe a lista de usuários
    printf("Usuários cadastrados:\n");
    for (int i = 0; i < contador; i++)
    {
        printf("%d: %s\n", i + 1, usuarios[i]);
    }

    int escolha;
    printf("Selecione o usuário que deseja editar (1-%d): ", contador);
    while (scanf("%d", &escolha) != 1 || escolha < 1 || escolha > contador)
    {
        fflush(stdin);
        printf("Entrada inválida! Escolha um usuário válido (1-%d): ", contador);
    }

    escolha--; // Ajusta o índice para o array

    // Permite editar o login e a senha do usuário
    printf("Editar login (atual: %s): ", usuarios[escolha]);
    fflush(stdin);
    scanf("%49[^\n]", usuarios[escolha]);
    printf("Editar senha (atual: %s): ", senhas[escolha]);
    fflush(stdin);
    scanf("%49[^\n]", senhas[escolha]);

    salvar_u(usuarios, senhas, contador);

    printf("Usuário editado com sucesso!\n");

    system("pause");
}

float saldo = 0;
// Função para editar saldo
void editarSaldo()
{
    float novoSaldo;
    printf("Digite o novo saldo: R$ ");
    while (scanf("%f", &novoSaldo) != 1)
    {
        fflush(stdin);
        printf("Entrada inválida! Entre com um valor válido: R$ ");
    }
    saldo = novoSaldo;
    salvar_s(saldo); // Salva o novo saldo no arquivo
    printf("Saldo atualizado com sucesso!\n");
    system("pause");
}

// Função para remover produto
void remover_p(struct add_produto *produtos, int *contador){
    carregar_p(produtos, contador);
    
    int resp, edit;
    system("cls");
    menuverdinho();

    if (*contador == 0)
    {
        printf("Não há produtos cadastrados para remover.\n");
        system("pause");
        return;
    }
    
    for (int i = 0; i < *contador; i++)
    {
        printf("Produto %d: %s\n", i + 1, produtos[i].nome_p);
    }
    printf("Qual produto deseja remover? (de 1 a %d): ", *contador);
    while (scanf("%d", &edit) != 1 || edit < 1 || edit > *contador)
    {
        fflush(stdin);
        printf("Entrada inválida! entre com o produto (1-%d): ", *contador);
    }
    edit--; // Ajusta o índice para o vetor

    printf ("Deseja realmente remover %s (1)Sim | (2)Não? ", produtos[edit].nome_p);
    scanf("%d", &resp);
    if (resp == 2)
    {
    return;
    }
    for (int i = edit; i < *contador - 1; i++){
        produtos[i]=produtos[i+1];
    }
    (*contador)--;
    salvar_p(produtos,*contador);
    printf("Produto removido com sucesso.\n");
    system("pause");
}

// Função para remover fornecedor
void remover_f(struct add_fornecedor *fornecedor, int *contador){
    carregar_f(fornecedor, contador);
    int resp, edit;
    system("cls");
    menuverdinho();

    if (*contador == 0)
    {
        printf("Não há fornecedores cadastrados para remover.\n");
        system("pause");
        return;
    }

    for (int i = 0; i < *contador; i++)
    {
        printf("Fornecedor %d: %s\n", i + 1, fornecedor[i].nome_f);
    }
    printf("Qual fornecedor deseja remover? (de 1 a %d): ", *contador);
    while (scanf("%d", &edit) != 1 || edit < 1 || edit > *contador)
    {
        fflush(stdin);
        printf("Entrada inválida! Entre com o fornecedor (1-%d): ", *contador);
    }
    edit--; // Ajusta o índice para o vetor
    printf ("Deseja realmente remover %s (1)Sim | (2)Não? ", fornecedor[edit].nome_f);
    scanf("%d", &resp);
    if (resp == 2)
    {
    return;
    }
    for (int i = edit; i < *contador - 1; i++){
        fornecedor[i]=fornecedor[i+1];
    }
    (*contador)--;
    salvar_f(fornecedor,*contador);
    printf("Fornecedor removido com sucesso.\n");
    system("pause");
}

// Função para remover funcionários 
void removerFunc() {
    carregar_func();
    int resp;
    system("cls");
    menuverdinho();

    if (contador == 0)
    {
        printf("Não há usuários cadastrados para remover.\n");
        system("pause");
        return;
    }
    for (int i = 0; i < contador; i++)
    {
        printf("%d: %s\n", i + 1, usuarios[i]);
    }

    int escolha;
    printf("Selecione o usuário que deseja remover (1-%d): ", contador);
    while (scanf("%d", &escolha) != 1 || escolha < 1 || escolha > contador)
    {
        fflush(stdin);
        printf("Entrada inválida! Escolha um usuário válido (1-%d): ", contador);
    }
    escolha--;

    printf ("Deseja realmente remover %s (1)Sim | (2)Não? ", usuarios[escolha]);
    scanf("%d", &resp);
    if (resp == 2)
    {
    return;
    }
    for (int i = escolha; i < contador - 1; i++){
        strcpy(usuarios[i], usuarios[i + 1]);
        strcpy(senhas[i], senhas[i + 1]);
    }
    (contador)--;
    salvar_u(usuarios, senhas, contador);
    printf("Funcionário removido com sucesso.\n");
    system("pause");
}

// Função para lê produtos no arquivo
void carregar_p(struct add_produto *produtos, int *contador){
    FILE *arq;
    arq = fopen("informacoes_p.txt", "r");
    if (arq == NULL)
    {
        printf("Nenhum produto cadastrado.\n");
        system("pause");
        return;
    }
    // Lê os usuários existentes nos arrays
    *contador = 0;
    while (fscanf(arq, "%69[^\n] %f %f\n", produtos[*contador].nome_p, &produtos[*contador].quantidade, &produtos[*contador].preco) != EOF)
    {
        (*contador)++;
    }
    fclose(arq);
}

// Função para lê fornecedores no arquivo
void carregar_f(struct add_fornecedor *fornecedor, int *contador){
    FILE *arq = fopen("informacoes_f.txt", "r+");
    if (arq == NULL)
    {
        puts("Nenhum fornecedor cadastrado.");
        system("pause");
        return;
    }

    *contador = 0; // Inicializa o contador
    while (fscanf(arq, "%69[^\n]\n%d %d %d\n%d\n",
                  fornecedor[*contador].nome_f,
                  &fornecedor[*contador].dia,
                  &fornecedor[*contador].mes,
                  &fornecedor[*contador].ano,
                  &fornecedor[*contador].num_produtos) == 5)
    {
        for (int i = 0; i < fornecedor[*contador].num_produtos; i++)
        {
            fscanf(arq, "%49[^\n] %f\n",
                   fornecedor[*contador].produtos[i].nome_p,
                   &fornecedor[*contador].produtos[i].quantidade);
        }
        (*contador)++;
    }
    fclose (arq);
}

// Função para lê funcionários no arquivo
void carregar_func(){
    FILE *funcionarios;
    funcionarios = fopen("informacoes_u.txt", "r");
    if (funcionarios == NULL)
    {
        printf("Nenhum usuário cadastrado.\n");
        system("pause");
        return;
    }

    contador = 0;
    while (fscanf(funcionarios, "%49s %49s", usuarios[contador], senhas[contador]) != EOF)
    {
        contador++;
    }

    fclose(funcionarios);
}

// Função para lê saldo do caixa do arquivo
void carregar_s()
{
    FILE *arq = fopen("informacoes_s.txt", "r");
    if (arq == NULL)
    {
        puts("Valor em CAIXA: R$ 00,00");
        system("pause");
        return;
    }
    fscanf(arq, "%f", &saldo);
    fclose(arq);
}

// Função para salvar produtos em um arquivo
void salvar_p(struct add_produto *produtos, int contador)
{
    FILE *arq;
    arq = fopen("informacoes_p.txt", "w");
    if (arq == NULL)
    {
        puts("Erro ao abrir o arquivo para salvar os produtos.");
        system("pause");
        return;
    }
    for (int i = 0; i < contador; i++)
    {
        fprintf(arq, "%s\n%.2f\n%.2f\n\n", produtos[i].nome_p, produtos[i].quantidade, produtos[i].preco);
    }
    fclose(arq);
}

// Função para salvar fornecedores em um arquivo
void salvar_f(struct add_fornecedor *fornecedor, int contador)
{
    FILE *arq;
    arq = fopen("informacoes_f.txt", "w");
    if (arq == NULL)
    {
        puts("Erro ao abrir o arquivo para salvar os fornecedores.");
        system("pause");
        return;
    }
    for (int i = 0; i < contador; i++)
    {
        fprintf(arq, "%s\n%d %d %d\n%d\n",
                fornecedor[i].nome_f,
                fornecedor[i].dia,
                fornecedor[i].mes,
                fornecedor[i].ano,
                fornecedor[i].num_produtos);
        for (int j = 0; j < fornecedor[i].num_produtos; j++)
        {
            fprintf(arq, "%s\n%.2f\n", fornecedor[i].produtos[j].nome_p,
                    fornecedor[i].produtos[j].quantidade);
        }
        fprintf(arq, "\n");
    }
    fclose(arq);
}

// Função para salvar venda em um arquivo
void salvar_v(char *produtoNome, float quantidade, float total)
{
    FILE *arq = fopen("informacoes_v.txt", "a");
    if (arq == NULL)
    {
        puts("Erro ao abrir o arquivo para salvar os fornecedores.");
        system("pause");
        return;
    }
    fprintf(arq, "%s\n%.2f\n%.2f\n",
            produtoNome, quantidade, total);
    fclose(arq);
}

// Função para salvar usuário em um arquivo
void salvar_u(char usuarios[][50], char senhas[][50], int contador)
{
    FILE *arq = fopen("informacoes_u.txt", "w");
    if (arq == NULL)
    {
        puts("Erro ao abrir o arquivo para salvar os usuários.");
        system("pause");
        return;
    }
    for (int i = 0; i < contador; i++)
    {
        fprintf(arq, "%s\n%s\n", usuarios[i], senhas[i]);
    }
    fclose(arq);
}

// Função para salvar o saldo do caixa em um arquivo
void salvar_s(float saldo)
{
    FILE *arq = fopen("informacoes_s.txt", "w");
    if (arq == NULL)
    {
        puts("Erro ao abrir o arquivo para salvar o saldo do caixa.");
        system("pause");
        return;
    }
    fprintf(arq, "%.2f", saldo);
    fclose(arq);
}

// Função para exibir saldo do caixa
void saldoCaixa()
{
    FILE *arq = fopen("informacoes_s.txt", "r");
    if (arq == NULL)
    {
        puts("Valor em CAIXA: R$ 00,00");
        system("pause");
        return;
    }
    fscanf(arq, "%f", &saldo);
    fclose(arq);

    system("cls");
    menuverdinho();
    printf("Valor em CAIXA: R$ %.2f\n\n", saldo);
    system("pause");
}

// Função para vender produtos
void venderProd(struct add_produto *produtos, int *contador_v)
{
    carregar_p(produtos, contador_v);
    carregar_s();

    FILE *aq;
    aq = fopen("informacoes_s.txt", "r");
    if (aq == NULL)
    {
        puts("Erro na abertura do arquivo.");
        system("pause");
        return;
    }
    fscanf(aq, "%f", &saldo);
    fclose(aq);

    int id, continuar;
    float quant;

    system("cls");
    menuverdinho();
    for (int i = 0; i < *contador_v; i++)
    {
        printf("Produto %d: %s | Quantidade: %.2f/kg | Preço por kg: R$ %.2f\n", i + 1, produtos[i].nome_p, produtos[i].quantidade, produtos[i].preco);
    }

    printf("Qual produto deseja vender? (de 1 a %d): ", *contador_v);
    while (scanf("%d", &id) != 1 || id < 1 || id > *contador_v)
    {
        fflush(stdin);
        printf("Entrada inválida! entre com o produto (1-%d): ", *contador_v);
    }
    id--; // Ajustando para o índice do array
    if (id < 0 || id >= *contador_v)
    {
        printf("Produto inexistente\n\n");
        system("pause");
        return;
    }

    printf("Qual a quantidade em kg que deseja vender? ");
    while (scanf("%f", &quant) != 1 || quant <= 0)
    {
        fflush(stdin);
        printf("Entrada inválida. Entre com a quantidade válida: ");
    }

    if (quant <= produtos[id].quantidade)
    {
        produtos[id].quantidade -= quant;
        float total = quant * produtos[id].preco;
        saldo += total;

        salvar_v(produtos[id].nome_p, quant, total);
        salvar_p(produtos, *contador_v);
        salvar_s(saldo);

        printf("Venda realizada com sucesso!\n");
        printf("Valor total: R$ %.2f\n", total);
    }
    else
    {
        puts("Quantidade indisponivel.\n");
        system("pause");
    }

    printf("Deseja realizar outra compra? (1) Sim | (2) Não: ");
    while (scanf("%d", &continuar) != 1 || (continuar != 1 && continuar != 2))
    {
        fflush(stdin);
        printf("Entrada inválida, Entre com a opção correta (1) Sim | (2) Não: ");
    }
    if (continuar == 1)
    {
        venderProd(produtos, contador_v);
    }
}

// Função para converter uma string para letras minúsculas
void toLowerStr(char *str)
{
    for (int i = 0; str[i]; i++)
    {
        str[i] = tolower(str[i]); // Converte cada caractere para minúsculo
    }
}

// Funçao para entrar com login e senha para acessar os menus
int loginFunc()
{
    char login[50], senha[50];
    char login_1[50], senha_1[50];
    FILE *funcionarios;

    system("cls");
    funcionarios = fopen("informacoes_u.txt", "a+");
    if (funcionarios == NULL)
    {
        printf("Erro ao abrir o arquivo! ");
        return 0; // add retorno pro caso de falhar na abertura
    }

    const char *usuarioPadrao = "adm";
    const char *senhaPadrao = "12345";

    menuverdinho();
    while (1)
    {
        printf("Entre com o usuário: ");
        fflush(stdin);
        scanf("%49[^\n]", login_1);

        printf("Entre com a senha: ");
        fflush(stdin);

        int i = 0;
        char caract;
        while ((caract = getch()) != '\r') // Enquanto não pressionar Enter
        {
            if (caract == '\b') // Se pressionar Backspace
            {
                if (i > 0) // Para evitar buffer overflow
                {
                    i--;
                    printf("\b \b"); // Remove o caractere anterior da tela
                }
            }
            else
            {
                senha_1[i++] = caract; // Armazena o caractere
                printf("*");           // Exibe o asterisco
            }
        }
        senha_1[i] = '\0'; // Finaliza a string

        // Verifica as credenciais padrão
        if (strcmp(login_1, usuarioPadrao) == 0 && strcmp(senha_1, senhaPadrao) == 0)
        {
            fclose(funcionarios);
            printf("\nLogin bem-sucedido! Acesso total.\n\n");
            system("pause");
            return 1; // Acesso total
        }

        // Verifica se o login é no arquivo
        rewind(funcionarios); // Volta ao início do arquivo
        while (fscanf(funcionarios, "%s %s", login, senha) != EOF)
        {
            if (strcmp(login_1, login) == 0 && strcmp(senha_1, senha) == 0)
            {
                fclose(funcionarios);
                printf("\nLogin bem-sucedido!\n\n");
                system("pause");
                return 2;
            }
        }
        system("cls");
        printf("Senha ou usuário incorreto! \n");
    }
    fclose(funcionarios);
    return 0;
}
#endif // FUNCOES_H_INCLUDED