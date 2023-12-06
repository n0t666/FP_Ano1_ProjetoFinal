#include <stdio.h>
#include <stdlib.h>
#include <locale.h>


#define MAXIMO_ESTUDANTES 150
#define MAXIMO_AVALIACOES 5000
#define UNIDADES_CURRICULARES 18

typedef struct
{
    int dia,mes,ano;
} data;

typedef struct
{
    int id,numero_estudante,cod_curso;
    char nome[80],email[50];
} estudante;

typedef struct
{
    int id,cod_uc,ects;
    char nome_uc[50],ano_curricular[20],semestre[20];
} unidade_curricular;

typedef struct
{
    int id,id_estudante,id_uc,classificao_final;
    char ano_letivo[20],epoca_avaliacao[50];
    data data_avaliacao;
} avaliacao;



int menu_principal(void);
void submenu_estudantes(void);
void submenu_ucs(void);
void pausar(void);

void main(void)
{

    setlocale(LC_ALL,"Portuguese");

    int menu_principal_op;


    do
    {
        menu_principal_op=menu_principal();
        switch(menu_principal_op)
        {
        case 1:
            submenu_estudantes();
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        default:
            printf("\nOpção inválida");
            pausar();
            system("cls||clear"); // Limpar o ecrã tanto para Windows como para Linux
        }
    }
    while(menu_principal_op < 1 || menu_principal_op > 5);



    getchar();
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
    printf(" * 5 - Sair do programa                   *\n");
    printf(" ******************************************\n\n");
    printf(" -->");
    scanf("%d",&op);
    return op;
}

void submenu_estudantes()
{
    int op;
    system("cls||clear");
    printf(" ******************************************\n");
    printf(" *           MENU ESTUDANTES              *\n");
    printf(" ******************************************\n");
    printf(" * 1 - Registrar novos alunos             *\n");
    printf(" * 2 - Consultar alunos existentes        *\n");
    printf(" ******************************************\n\n");
    printf(" -->");
    scanf("%d",&op);
}

void submenu_ucs()
{
    int op;
    system("cls||clear");
    printf(" ******************************************\n");
    printf(" *           MENU ESTUDANTES              *\n");
    printf(" ******************************************\n");
    printf(" * 1 - Registrar novos alunos             *\n");
    printf(" * 2 - Consultar alunos existentes        *\n");
    printf(" ******************************************\n\n");
    printf(" -->");
    scanf("%d",&op);
}

void pausar()
{
    fflush(stdin);
    printf("\n\nPRESSIONE <ENTER> PARA CONTINUAR...");
    getchar();
}

