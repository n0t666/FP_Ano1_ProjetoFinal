/*
 *
 * Autores:
 *  - Leandro Alves Pereira <223175@my.ipleiria.pt> <PL2>
 *
 * Data:
 *
 * Descrição:
    - Trabalho realizado no âmbito do projeto final da disciplina de Fundamentos de Programação
 */


//------------------------------------------------------------------------------------------------
// Bibliotecas de pré-processamento
//------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>
//-------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------
// CONSTANTES
//------------------------------------------------------------------------------------------------
#define MINIMO_NUMERO_ESTUDANTE 2190000

#define MAXIMO_ESTUDANTES 150
#define MAXIMO_AVALIACOES 5000
#define MAXIMO_UNIDADES_CURRICULARES 18

#define MAXIMO_NUMERO_ESTUDANTE 2299999
#define DOMINIO_EMAIL_ESTUDANTES "my.ipleiria.pt"

#define TECLA_ESC 27
#define TECLA_ENTER 13
//-------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------
// Definição das estruturas de dados
//------------------------------------------------------------------------------------------------
typedef struct
{
    int dia,mes,ano;
} t_data;

typedef struct
{
    int id,numero_estudante,cod_curso;
    char nome[80],email[50];
} t_estudante;

typedef struct
{
    int id,cod_uc,ects;
    char nome_uc[50],ano_curricular[20],semestre[20];
} t_unidade_curricular;

typedef struct
{
    int id,id_estudante,id_uc,classificao_final;
    char ano_letivo[20],epoca_avaliacao[50];
    t_data data_avaliacao;
} t_avaliacao;
//-------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
// Funções relacionadas com menus e submenujs
//------------------------------------------------------------------------------------------------
int menu_principal(void);
int submenu_estudantes(void);
int submenu_ucs(void);
int submenu_avaliacoes(void);
int submenu_estatisticas_gerais(void);
int submenu_estatisticas_especificas(void);
//-------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------------------
// Funções utilitárias do programa
//------------------------------------------------------------------------------------------------
int ler_numero(int valor_min,int valor_max);
int ler_tecla(void);

char confirmarAcao(char msg[]);
//-------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------------------
// Funções relacionadas com a manipulação da  estrutura de dados estudantes
//------------------------------------------------------------------------------------------------

void mostrar_dados_estudantes(t_estudante vetor_estudantes[],int numero_estudantes);
void mostrar_dados_estudante(t_estudante vetor_estudantes[],int indice_estudante);
void mostrar_editar_estudante(t_estudante vetor_estudantes[],int numero_estudantes,int indice_estudante);
void ler_email_estudante(t_estudante vetor_estudantes[],int numero_estudantes,int indice_especifico);


int  procurar_estudante(t_estudante vetor_estudantes[],int numero_estudantes,int numero_estudante);
int procurar_email_estudante(char email[],t_estudante vetor_estudantes[],int numero_estudantes);
int validar_email_estudante(char email[],t_estudante vetor_estudantes[],int numero_estudantes);
int ler_dados_estudante(t_estudante vetor_estudantes[],int numero_estudantes);
int verificarNumAlunoExistente(t_estudante vetor_estudantes[],int numero_estudantes);
int verificarNumAlunoInexistente(t_estudante vetor_estudantes[],int numero_estudantes);




//-------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
// Funções relacionadas com a manipulação da  estrutura de dados unidade_curricular
//------------------------------------------------------------------------------------------------


int  procurar_unidade_curricular(t_unidade_curricular vetors_ucs[],int numero_ucs,int codigo_uc);

//-------------------------------------------------------------------------------------------------

int main(void)
{

    setlocale(LC_ALL,"Portuguese");

    t_estudante vetor_estudantes[MAXIMO_ESTUDANTES];
    t_unidade_curricular vetor_ucs[MAXIMO_UNIDADES_CURRICULARES];
    t_avaliacao vetor_avaliacoes[MAXIMO_AVALIACOES];

    int menu_principal_op,submenu_estudantes_op,submenu_ucs_op,submenu_avaliacoes_op,submenu_estatisticas_op;

    int numero_estudantes=0,numeros_ucs=0,numero_avaliacoes=0;

    int numero_estudante,indice_estudante;

    char saida;


    do
    {
        system("cls||clear");
        menu_principal_op=menu_principal();
        switch(menu_principal_op)
        {
        case 0:
            saida = confirmarAcao("Deseja realmente sair do programa?");
            break;

        case 1:
            do
            {
                submenu_estudantes_op=submenu_estudantes();
                switch(submenu_estudantes_op)
                {
                case 1:
                    numero_estudantes=ler_dados_estudante(vetor_estudantes,numero_estudantes);
                    break;
                case 2:
                    if(numero_estudantes>0)
                    {
                        mostrar_dados_estudantes(vetor_estudantes,numero_estudantes);
                    }
                    else
                    {
                        printf("\nPara usar esta opção necessita de ter pelo menos 1 estudante inserido no sistema");
                        fflush(stdin);
                        getchar();
                    }
                    break;
                case 3:
                    if(numero_estudantes>0)
                    {
                        printf("\nIntroduza o número de estudante que pretende consultar: ");
                        indice_estudante = verificarNumAlunoExistente(vetor_estudantes,numero_estudantes);
                        mostrar_dados_estudante(vetor_estudantes,indice_estudante);

                    }
                    else
                    {
                        printf("\nPara usar esta opção necessita de ter pelo menos 1 estudante inserido no sistema");
                        fflush(stdin);
                        getchar();
                    }
                    break;
                case 4:
                    if(numero_estudantes>0)
                    {
                        printf("\nIntroduza o número de estudante que pretende editar: ");
                        indice_estudante = verificarNumAlunoExistente(vetor_estudantes,numero_estudantes);
                        mostrar_editar_estudante(vetor_estudantes,numero_estudantes,indice_estudante);

                    }
                    else
                    {
                        printf("\nPara usar esta opção necessita de ter pelo menos 1 estudante inserido no sistema");
                        fflush(stdin);
                        getchar();
                    }
                    break;
                }
            }
            while(submenu_estudantes_op!=0);
            break;
        case 2:
            do
            {

                submenu_ucs_op = submenu_ucs();
            }
            while(submenu_ucs_op!=3);
            break;
        case 3:
            break;
        case 4:
            break;
        default:
            printf("\nOpção inválida");
            fflush(stdin);
            printf("\n\nPRESSIONE <ENTER> PARA CONTINUAR...");
            getchar();
            system("cls||clear"); // Limpar o ecrã tanto para Windows como para Linux
        }
    }
    while(saida!='S');
}

int menu_principal()
{
    int op;
    printf(" ******************************************\n");
    printf(" *           MENU PRINCIPAL               *\n");
    printf(" ******************************************\n");
    printf(" * 1 - Estudantes                         *\n");
    printf(" * 2 - Unidades Curriculares              *\n");
    printf(" * 3 - Avaliações                         *\n");
    printf(" * 4 - Estatísticas                       *\n");
    printf(" * 0 - Sair do programa                   *\n");
    printf(" ******************************************\n\n");
    printf(" -->");
    scanf("%d",&op);
    return op;
}

int submenu_estudantes()
{
    int op;
    system("cls||clear");
    printf(" ******************************************\n");
    printf(" *           MENU ESTUDANTES              *\n");
    printf(" ******************************************\n");
    printf(" * 1 - Registrar novo aluno               *\n");
    printf(" * 2 - Listar alunos existentes           *\n");
    printf(" * 3 - Consultar aluno específico         *\n");
    printf(" * 4 - Editar aluno específico            *\n");
    printf(" * 0 - Voltar                             *\n");
    printf(" ******************************************\n\n");
    printf(" -->");
    scanf("%d",&op);
    return op;
}

int submenu_ucs()
{
    int op;
    system("cls||clear");
    printf(" *************************************************\n");
    printf(" *            MENU UNIDADES CURRICULARES         *\n");
    printf(" *************************************************\n");
    printf(" * 1 - Registrar novas unidades curriculares     *\n");
    printf(" * 2 - Consultar alunos existentes               *\n");
    printf(" ************************************************\n\n");
    printf(" -->");
    scanf("%d",&op);
    return op;
}

int submenu_avaliacoes()
{
    int op;
    system("cls||clear");
    printf(" ******************************************\n");
    printf(" *           MENU AVALIAÇÕES              *\n");
    printf(" ******************************************\n");
    printf(" * 1 - Registrar novas avaliações         *\n");
    printf(" * 2 - Consultar avaliações existentes    *\n");
    printf(" * 0 - Voltar                             *\n");
    printf(" ******************************************\n\n");
    printf(" -->");
    scanf("%d",&op);
    return op;
}

int submenu_estatisticas_gerais()
{
    int op;
    system("cls||clear");
    printf(" ************************************************\n");
    printf(" *           MENU ESTATÍSTICAS ESPECÍFICAS       *\n");
    printf(" ************************************************\n");
    printf(" * Total de ECTS aprovados pelos estudantes:     *\n");
    printf(" * 2 - Consultar avaliações existentes          *\n");
    printf(" * 0 - Voltar                                   *\n");
    printf(" ************************************************\n\n");
    printf(" -->");
    scanf("%d",&op);
    return op;
}

char confirmarAcao(char msg[])
{
    char confirmacao;
    do
    {
        printf("\n%s (S/N): ",msg);
        scanf(" %c",&confirmacao);
        confirmacao = toupper(confirmacao);
    }
    while(confirmacao != 'S' && confirmacao !='N');
    return confirmacao;
}

int ler_numero(int valor_min,int valor_max)
{
    int num;
    do
    {
        scanf("%d",&num);
        if(num < valor_min)
        {
            printf("\nO número está abaixo do valor pretendido,tente novamente: ");
        }
        else if(num > valor_max)
        {
            printf("\nO número está acima do valor pretendido,tente novamente: ");
        }
    }
    while(num < valor_min || num > valor_max);

    return num;
}


int ler_dados_estudante(t_estudante vetor_estudantes[],int numero_estudantes)
{
    int indice_estudante,numero_estudante;

    system("cls||clear"); // Limpar o ecrã tanto para Windows como para Linux

    printf("************************************************\n");
    printf("*                  Estudante Nº%d               *\n",numero_estudantes+1);
    printf("************************************************\n\n");
    vetor_estudantes[numero_estudantes].numero_estudante = verificarNumAlunoInexistente(vetor_estudantes,numero_estudantes);
    printf("\nNome:");
    fflush(stdin);
    scanf("%80[^\n]", vetor_estudantes[numero_estudantes].nome);
    printf("\nCódigo do curso: ");
    scanf("%d",&vetor_estudantes[numero_estudantes].cod_curso);
    printf("\nEmail: ");
    ler_email_estudante(vetor_estudantes,numero_estudantes,0);
    vetor_estudantes[numero_estudantes].id = numero_estudantes +1;
    fflush(stdin);
    printf("\n\nPRESSIONE <ENTER> PARA CONTINUAR...");
    getchar();
    system("cls||clear"); // Limpar o ecrã tanto para Windows como para Linux
    numero_estudantes++;
    return numero_estudantes;
}


int  procurar_estudante(t_estudante vetor_estudantes[],int numero_estudantes,int numero_estudante)
{
    int encontrado = -1;

    for(int indice=0; indice < numero_estudantes; indice++)
    {
        if(vetor_estudantes[indice].numero_estudante == numero_estudante)
        {
            encontrado =indice;
        }
    }

    return encontrado;
}


int procurar_unidade_curricular(t_unidade_curricular vetor_ucs[],int numero_ucs,int codigo_uc)
{
    int encontrado = -1;

    for(int indice=0; indice < numero_ucs; indice++)
    {
        if(vetor_ucs[indice].cod_uc == numero_ucs)
        {
            encontrado =indice;
        }
    }

    return encontrado;
}

// Função para ler e validar um endereço de email de um estudante
// Recebe como parâmetro o vetor dos estudantes e um índice para adicionar o email válido ao vetor
int validar_email_estudante(char email[],t_estudante vetor_estudantes[],int numero_estudantes)
{
    char username[50], dominio[50];
    int isEmailValido,valido=0;

    // Verificar se o email corresponde ao formato especificado (utilizador@domínio), devolvendo número de parametros cumpridos, no caso de estar totalmente correto devolve 2
    isEmailValido = sscanf(email, "%[_a-zA-Z0-9.]@%[_a-zA-Z0-9.]", username, dominio);
    if(isEmailValido == 2)  // O formato do email é válido
    {
        if(strcmp(dominio,DOMINIO_EMAIL_ESTUDANTES)!=0)  // Caso o dominio do email não for igual a  "my.ipleiria.pt"
        {
            printf("\nTodos os endereços email devem ser do tipo %s\n", DOMINIO_EMAIL_ESTUDANTES); //Messagem de erro
        }
        else
        {
            if(procurar_email_estudante(email,vetor_estudantes,numero_estudantes)==-1)
            {
                valido = 1; //Flag que permite indicar que está tudo correto com endereço email
            }
            else
            {
                printf("\nO endereço email já está associado a outro estudante,tente novamente: ");
            }
        }
    }
    else   //Se o email não tiver todos os requisitos
    {
        printf("\nO endereço email deve ser válido,tente novamente: ");
    }
    return valido;
}

void ler_email_estudante(t_estudante vetor_estudantes[],int numero_estudantes,int indice_especifico)
{
    char email[50];
    int valido = 0;
    do
    {
        fflush(stdin);
        scanf("%50[^\n]",email);
        valido=validar_email_estudante(email,vetor_estudantes,numero_estudantes);
    }
    while(valido!=1);  //Enquanto a flag não for 1 (o email não estiver correto)
    if(indice_especifico==-1)
    {
        strcpy(vetor_estudantes[numero_estudantes].email, email); // Copiar o endereço de email válido para a estrutura
    }
    else
    {
        strcpy(vetor_estudantes[indice_especifico].email, email); // Copiar o endereço de email válido para a estrutura
    }
}

int procurar_email_estudante(char email[],t_estudante vetor_estudantes[],int numero_estudantes)
{
    int encontrado = -1;

    for(int indice=0; indice < numero_estudantes; indice++)
    {
        if(strcmp(vetor_estudantes[indice].email,email)==0)
        {
            encontrado =indice;
        }
    }

    return encontrado;
}

void mostrar_dados_estudantes(t_estudante vetor_estudantes[], int numero_estudantes)
{
    printf("\n%d\n",numero_estudantes);
    printf("ID  | Nome                                                                           | Número de estudante | Código Curso | Email\n");
    printf("----|--------------------------------------------------------------------------------|---------------------|--------------|-------\n");
    for (int indice = 0; indice < numero_estudantes; indice++)
    {
        printf("%-4d| %-78s | %-19d | %-12d | %s\n",
               vetor_estudantes[indice].id,
               vetor_estudantes[indice].nome,
               vetor_estudantes[indice].numero_estudante,
               vetor_estudantes[indice].cod_curso,
               vetor_estudantes[indice].email);
    }
    printf("----|--------------------------------------------------------------------------------|---------------------|--------------|-------\n");
    fflush(stdin);
    getchar();
}

void mostrar_dados_estudante(t_estudante vetor_estudantes[], int indice_estudante)
{
    system("cls||clear");
    printf(" **********************************************************************************************\n");
    printf("                                        ALUNO Nº.%d                                            \n",vetor_estudantes[indice_estudante].numero_estudante);
    printf(" **********************************************************************************************\n");
    printf("   ID: %d                                                                                      \n",vetor_estudantes[indice_estudante].id);
    printf("   Número de estudante: %d                                                                     \n",vetor_estudantes[indice_estudante].numero_estudante);
    printf("   Nome: %s                                                                                    \n",vetor_estudantes[indice_estudante].nome);
    printf("   Código de curso: %d                                                                         \n",vetor_estudantes[indice_estudante].cod_curso);
    printf("   Email: %s                                                                                   \n",vetor_estudantes[indice_estudante].email);
    printf(" **********************************************************************************************\n\n");
    fflush(stdin);
    printf("\n\nPRESSIONE <ENTER> PARA CONTINUAR...");
    getchar();
}
void mostrar_editar_estudante(t_estudante vetor_estudantes[],int numero_estudantes,int indice_estudante)
{
    char sair;
    do
    {
        mostrar_dados_estudante(vetor_estudantes,indice_estudante);
        if(confirmarAcao("Deseja editar o número de  estudante?")=='S')
        {
            printf("\n");
            vetor_estudantes[indice_estudante].numero_estudante = verificarNumAlunoInexistente(vetor_estudantes,numero_estudantes);
        }

        if(confirmarAcao("Deseja editar o nome?")=='S')
        {
            printf("\nNovo nome: ");
            fflush(stdin);
            scanf("%80[^\n]", vetor_estudantes[indice_estudante].nome);
        }


        if(confirmarAcao("Deseja editar o  email?")=='S')
        {
            printf("\nNovo email: ");
            ler_email_estudante(vetor_estudantes,numero_estudantes,indice_estudante);
        }
        if(confirmarAcao("Deseja editar o código do curso?")=='S')
        {
            printf("\nNovo código de curso: ");
            scanf("%d", &vetor_estudantes[indice_estudante].cod_curso);
        }
        printf("-----------------------------------------------");
        sair = confirmarAcao("Continuar no modo edição?");
    }
    while(sair=='S');
}

int verificarNumAlunoExistente(t_estudante vetor_estudantes[],int numero_estudantes)
{
    int indice_estudante,numero_estudante;
    do
    {
        scanf("%d",&numero_estudante);
        indice_estudante = procurar_estudante(vetor_estudantes,numero_estudantes,numero_estudante);
        if(indice_estudante == -1)
        {
            printf("\n(Erro:O aluno com o número de estudante %d não existe),tente novamente:",numero_estudante);
            fflush(stdin);
            getchar();
        }
    }
    while(indice_estudante == -1);

    return indice_estudante;
}

int verificarNumAlunoInexistente(t_estudante vetor_estudantes[],int numero_estudantes)
{
    int indice_estudante,numero_estudante;
    do
    {
        printf("Número de estudante: ");
        numero_estudante = ler_numero(MINIMO_NUMERO_ESTUDANTE,MAXIMO_NUMERO_ESTUDANTE);
        indice_estudante = procurar_estudante(vetor_estudantes,numero_estudantes,numero_estudante);
        if(indice_estudante != -1)
        {
            printf("\n(Erro: O aluno já existe!),tente novamente:");
            fflush(stdin);
            getchar();
        }
    }
    while(indice_estudante !=-1);

    return numero_estudante;
}

int ler_tecla()
{
    int numero_tecla;
    fflush(stdin);
    numero_tecla = getchar();

    return numero_tecla;
}


