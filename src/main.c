/*
 *
 * Autores:
 *  - Leandro Alves Pereira <223175@my.ipleiria.pt> <PL2>
 *  - Henrique Grilo Soares <2231678@my.ipleiria.pt> <PL2>
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

#define MAXIMO_ESTUDANTES 150
#define MAXIMO_AVALIACOES 5000
#define MAXIMO_UNIDADES_CURRICULARES 18

#define MAXIMO_NUMERO_ESTUDANTE 2299999
#define MINIMO_NUMERO_ESTUDANTE 2190000

#define DOMINIO_EMAIL_ESTUDANTES "my.ipleiria.pt"

#define TECLA_ESC 27
#define TECLA_ENTER 13

#define DATA_MINIMA 2000
#define NOTA_FINAL_MINIMA 10
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
    int id,cod_uc,ects,semestre;
    char nome_uc[50],ano_curricular[20];
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
int submenu_estatisticas(void);
int submenu_ficheiros(void);
//-------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------------------
// Funções utilitárias do programa
//------------------------------------------------------------------------------------------------
void lerNumCardinal(char* resultado,int len,char sufixo[],int max,int min);

int ler_numero(int valor_min,int valor_max);
int ler_tecla(void);
int validarAnoLetivo(char anoLetivo[]);
int validarData(int dia,int mes,int ano,int max,int min);
int obterDigitosAno(int ano);
int obterPrimeirosDigitosAno(int ano);
int verificarAnoBissexto(int ano);
int acao_ficheiros(char tipoAcao[]);
int concatenar_inteiros(int num1,int num2);

char confirmarAcao(char msg[]);
//-------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------------------
// Funções relacionados com os ficheiros
//------------------------------------------------------------------------------------------------

//Escrita
void gravarFicheiroEstudantes(t_estudante vetor_estudantes[],int numero_estudantes);
void gravarFicheiroUcs(t_unidade_curricular vetor_ucs[],int numero_ucs);
void gravarFicheiroAvaliacoes(t_avaliacao vetor_avaliacoes[],int numero_avaliacoes);



//Leitura
int lerFicheiroEstudantes(t_estudante vetor_estudantes[]);
int lerFicheiroUcs(t_unidade_curricular vetor_ucs[]);
int lerFicheiroAvaliacoes(t_avaliacao vetor_avaliacoes[]);

//Limpeza

void limparFicheiroEstudante(t_estudante vetor_estudantes[]);
void limparFicheiroUcs(t_unidade_curricular vetor_ucs[]);
void limparFicheiroAvaliacoes(t_avaliacao vetor_avaliacoes[]);


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

int ler_dados_unidade_curricular(t_unidade_curricular vetors_ucs[],int numero_ucs);
int procurar_unidade_curricular(t_unidade_curricular vetors_ucs[],int numero_ucs,int codigo_uc);

int verificarUcExistente(t_unidade_curricular vetors_ucs[],int numero_ucs);
int verificarUcInexistente(t_unidade_curricular vetors_ucs[],int numero_ucs);

void mostrar_dados_ucs(t_unidade_curricular vetors_ucs[],int numero_ucs);
void mostrar_dados_uc(t_unidade_curricular vetors_ucs[],int codigo_uc);
void mostrar_editar_uc(t_unidade_curricular vetor_ucs[],int numero_ucs,int indice_uc);
//-------------------------------------------------------------------------------------------------




//------------------------------------------------------------------------------------------------
// Funções relacionadas com a manipulação da  estrutura de dados avaliações
//------------------------------------------------------------------------------------------------
int ler_dados_avaliacao(t_avaliacao vetor_avaliacoes[],int numero_avaliacoes,t_estudante vetor_estudantes[],int numero_estudantes,t_unidade_curricular vetor_ucs[],int numero_ucs);

void mostrar_dados_avaliacoes(t_avaliacao vetor_avaliacoes[], int numero_avaliacoes);
void ler_data_avaliacao(t_avaliacao vetor_avaliacoes[],int indice_avaliacao);

float calcularMediaUcsAprovadas(t_avaliacao vetor_avaliacoes[],int numero_avaliacoes,int id_estudante);
//-------------------------------------------------------------------------------------------------




//------------------------------------------------------------------------------------------------
// Funções relacionadas com a obtenção de estatísticas
//------------------------------------------------------------------------------------------------
int contarUcsAprovadas(t_avaliacao vetor_avaliacoes[],int numero_avaliacoes,int id_estudante);
int calcultarTotalEcts(t_avaliacao vetor_avaliacoes[],int numero_avaliacoes,t_unidade_curricular vetor_ucs[],int numero_ucs,int id_estudante);

void estatisticas_aluno(t_avaliacao vetor_avaliacoes[], int numero_avaliacoes,t_unidade_curricular vetor_ucs[],int numero_ucs, int id_estudante,int codigo_estudante);
void obterDadosEstudantePorSemestre(t_avaliacao vetor_avaliacoes[], int numero_avaliacoes,t_unidade_curricular vetor_ucs[],int numero_ucs, int id_estudante);

//-------------------------------------------------------------------------------------------------

int main(void)
{

    setlocale(LC_ALL,"Portuguese");

    t_estudante vetor_estudantes[MAXIMO_ESTUDANTES];
    t_unidade_curricular vetor_ucs[MAXIMO_UNIDADES_CURRICULARES];
    t_avaliacao vetor_avaliacoes[MAXIMO_AVALIACOES];

    int menu_principal_op,submenu_estudantes_op,submenu_ucs_op,submenu_avaliacoes_op,submenu_estatisticas_op,submenu_ficheiros_op,submenu_ficheiros_acao_op;

    int numero_estudantes=0,numeros_ucs=0,numero_avaliacoes=0;

    int indice_estudante,indice_uc;

    char saida;

    numero_estudantes=lerFicheiroEstudantes(vetor_estudantes);
    numeros_ucs = lerFicheiroUcs(vetor_ucs);
    numero_avaliacoes = lerFicheiroAvaliacoes(vetor_avaliacoes);

    printf("\n\nPRESSIONE <ENTER> PARA CONTINUAR...");
    getchar();

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
                        printf("\n\nPRESSIONE <ENTER> PARA CONTINUAR...");
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
                        printf("\n\nPRESSIONE <ENTER> PARA CONTINUAR...");
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
                        printf("\n\nPRESSIONE <ENTER> PARA CONTINUAR...");
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
                switch(submenu_ucs_op)
                {
                case 1:
                    numeros_ucs = ler_dados_unidade_curricular(vetor_ucs,numeros_ucs);
                    break;
                case 2:
                    if(numeros_ucs>0)
                    {
                        mostrar_dados_ucs(vetor_ucs,numeros_ucs);
                    }
                    else
                    {
                        printf("\nPara usar esta opção necessita de ter pelo menos 1 UC inserido no sistema");
                        fflush(stdin);
                        printf("\n\nPRESSIONE <ENTER> PARA CONTINUAR...");
                        getchar();
                    }
                    break;
                case 3:
                    if(numeros_ucs>0)
                    {
                        printf("\nIntroduza o código da UC que pretende consultar: ");
                        indice_uc = verificarUcExistente(vetor_ucs,numeros_ucs);
                        mostrar_dados_uc(vetor_ucs,indice_uc);
                    }
                    else
                    {
                        printf("\nPara usar esta opção necessita de ter pelo menos 1 UC inserido no sistema");
                        fflush(stdin);
                        printf("\n\nPRESSIONE <ENTER> PARA CONTINUAR...");
                        getchar();
                    }
                    break;
                case 4:
                    if(numeros_ucs>0)
                    {
                        printf("\nIntroduza o código da UC que pretende editar: ");
                        indice_uc = verificarUcExistente(vetor_ucs,numeros_ucs);
                        mostrar_editar_uc(vetor_ucs,numeros_ucs,indice_uc);
                    }
                    else
                    {
                        printf("\nPara usar esta opção necessita de ter pelo menos 1 UC inserido no sistema");
                        fflush(stdin);
                        printf("\n\nPRESSIONE <ENTER> PARA CONTINUAR...");
                        getchar();
                    }
                    break;
                }
            }
            while(submenu_ucs_op!=0);
            break;
        case 3:
            do
            {
                submenu_avaliacoes_op = submenu_avaliacoes();
                switch(submenu_avaliacoes_op)
                {
                case 1:
                    numero_avaliacoes = ler_dados_avaliacao(vetor_avaliacoes,numero_avaliacoes,vetor_estudantes,numero_estudantes,vetor_ucs,numeros_ucs);
                    break;
                case 2:
                    mostrar_dados_avaliacoes(vetor_avaliacoes,numero_avaliacoes);
                    break;
                default:
                    printf("\nOpção inválida");
                }

            }
            while(submenu_avaliacoes_op!=0);
            break;
        case 4:
            if(numeros_ucs > 0 && numero_avaliacoes > 0 && numero_estudantes > 0)
            {
                do
                {
                    submenu_estatisticas_op=submenu_estatisticas();
                    switch(submenu_estatisticas_op)
                    {
                    case 1:
                        printf("\nIntroduza o número de estudante que pretende consultar as estatísticas: ");
                        indice_estudante = verificarNumAlunoExistente(vetor_estudantes,numero_estudantes);
                        estatisticas_aluno(vetor_avaliacoes,numero_avaliacoes,vetor_ucs,numeros_ucs,vetor_estudantes[indice_estudante].id,vetor_estudantes[indice_estudante].numero_estudante);
                        break;
                    }

                }
                while(submenu_estatisticas_op!=0);
            }
            else
            {
                printf("\nPara consultar este menu necessita de ter pelo menos 1 unidade curricular,1 avaliação e 1 estudante inserido no sistema");
                fflush(stdin);
                printf("\n\nPRESSIONE <ENTER> PARA CONTINUAR...");
                getchar();
            }
            break;
        case 5:
            do
            {
                submenu_ficheiros_op = submenu_ficheiros();
                switch(submenu_ficheiros_op)
                {
                case 1:
                    submenu_ficheiros_acao_op=acao_ficheiros("guardar");
                    switch(submenu_ficheiros_acao_op)
                    {
                    case 1:
                        gravarFicheiroEstudantes(vetor_estudantes,numero_estudantes);
                        fflush(stdin);
                        printf("\n\nPRESSIONE <ENTER> PARA CONTINUAR...");
                        getchar();
                        break;
                        break;
                    case 2:
                        gravarFicheiroUcs(vetor_ucs,numeros_ucs);
                        fflush(stdin);
                        printf("\n\nPRESSIONE <ENTER> PARA CONTINUAR...");
                        getchar();
                        break;
                        break;
                    case 3:
                        gravarFicheiroAvaliacoes(vetor_avaliacoes,numero_avaliacoes);
                        fflush(stdin);
                        printf("\n\nPRESSIONE <ENTER> PARA CONTINUAR...");
                        getchar();
                        break;
                        break;
                    case 4:
                        gravarFicheiroEstudantes(vetor_estudantes,numero_estudantes);
                        gravarFicheiroUcs(vetor_ucs,numeros_ucs);
                        gravarFicheiroAvaliacoes(vetor_avaliacoes,numero_avaliacoes);
                        fflush(stdin);
                        printf("\n\nPRESSIONE <ENTER> PARA CONTINUAR...");
                        getchar();
                        break;
                        break;
                    }
                    break;
                case 2:
                    submenu_ficheiros_acao_op=acao_ficheiros("carregar");
                    switch(submenu_ficheiros_acao_op)
                    {
                    case 1:
                        memset(vetor_estudantes,0,sizeof(vetor_estudantes));
                        numero_estudantes = lerFicheiroEstudantes(vetor_estudantes);
                        fflush(stdin);
                        printf("\n\nPRESSIONE <ENTER> PARA CONTINUAR...");
                        getchar();
                        break;
                    case 2:
                        memset(vetor_ucs,0,sizeof(vetor_ucs));
                        numeros_ucs = lerFicheiroUcs(vetor_ucs);
                        fflush(stdin);
                        printf("\n\nPRESSIONE <ENTER> PARA CONTINUAR...");
                        getchar();
                        break;
                    case 3:
                        memset(vetor_avaliacoes,0,sizeof(vetor_avaliacoes));
                        numero_avaliacoes = lerFicheiroAvaliacoes(vetor_avaliacoes);
                        fflush(stdin);
                        printf("\n\nPRESSIONE <ENTER> PARA CONTINUAR...");
                        getchar();
                        break;
                    case 4:
                        memset(vetor_estudantes,0,sizeof(vetor_estudantes));
                        memset(vetor_ucs,0,sizeof(vetor_ucs));
                        memset(vetor_avaliacoes,0,sizeof(vetor_avaliacoes));
                        numero_estudantes = lerFicheiroEstudantes(vetor_estudantes);
                        numeros_ucs = lerFicheiroUcs(vetor_ucs);
                        numero_avaliacoes = lerFicheiroAvaliacoes(vetor_avaliacoes);
                        fflush(stdin);
                        printf("\n\nPRESSIONE <ENTER> PARA CONTINUAR...");
                        getchar();
                        break;
                    }
                    break;
                case 3:
                    submenu_ficheiros_acao_op=acao_ficheiros("limpar");
                    switch(submenu_ficheiros_acao_op)
                    {
                    case 1:
                        numero_estudantes = 0;
                        limparFicheiroEstudante(vetor_estudantes);
                        fflush(stdin);
                        printf("\n\nPRESSIONE <ENTER> PARA CONTINUAR...");
                        getchar();
                        break;
                    case 2:
                        numeros_ucs = 0;
                        limparFicheiroUcs(vetor_ucs);
                        fflush(stdin);
                        printf("\n\nPRESSIONE <ENTER> PARA CONTINUAR...");
                        getchar();
                        break;
                    case 3:
                        numero_avaliacoes = 0;
                        limparFicheiroAvaliacoes(vetor_avaliacoes);
                        fflush(stdin);
                        printf("\n\nPRESSIONE <ENTER> PARA CONTINUAR...");
                        getchar();
                        break;
                    case 4:
                        numero_estudantes = 0;
                        numeros_ucs = 0;
                        numero_avaliacoes = 0;
                        limparFicheiroEstudante(vetor_estudantes);
                        limparFicheiroUcs(vetor_ucs);
                        limparFicheiroAvaliacoes(vetor_avaliacoes);
                        fflush(stdin);
                        printf("\n\nPRESSIONE <ENTER> PARA CONTINUAR...");
                        getchar();
                        break;
                    }
                    break;
                }
            }
            while(submenu_ficheiros_op!=0);
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
    gravarFicheiroEstudantes(vetor_estudantes,numero_estudantes);
    gravarFicheiroUcs(vetor_ucs,numeros_ucs);
    gravarFicheiroAvaliacoes(vetor_avaliacoes,numero_avaliacoes);
}

int acao_ficheiros(char tipoAcao[])
{
    int op;
    printf("\nO que deseja %s:\n",tipoAcao);
    printf("\n1 - Ficheiro 'estudantes'");
    printf("\n2 - Ficheiro 'unidades_curriculares'");
    printf("\n3 - Ficheiro 'avaliações'");
    printf("\n4 - Todos os ficheiros");
    printf("\n0 - Nenhum");
    printf("\n\n-->");
    scanf("%d",&op);
    return op;
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
    printf(" * 5 - Ficheiros                          *\n");
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
    printf(" ************************************************\n");
    printf(" *                 MENU ESTUDANTES              *\n");
    printf(" ************************************************\n");
    printf(" * 1 - Registrar novo aluno                     *\n");
    printf(" * 2 - Listar alunos existentes                 *\n");
    printf(" * 3 - Consultar aluno específico               *\n");
    printf(" * 4 - Editar aluno específico                  *\n");
    printf(" * 0 - Voltar                                   *\n");
    printf(" ************************************************\n\n");
    printf(" -->");
    scanf("%d",&op);
    return op;
}

int submenu_ucs()
{
    int op;
    system("cls||clear");
    printf(" **************************************************\n");
    printf(" *            MENU UNIDADES CURRICULARES         **\n");
    printf(" **************************************************\n");
    printf(" * 1 - Registrar novas unidades curriculares      *\n");
    printf(" * 2 - Consultar unidades curriculares existentes *\n");
    printf(" * 3 - Consultar unidade curricular existente     *\n");
    printf(" * 4 - Editar unidade curricular específica       *\n");
    printf(" * 0 - Voltar                                     *\n");
    printf(" **************************************************\n\n");
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

int submenu_estatisticas()
{
    int op;
    system("cls||clear");
    printf(" *************************************************\n");
    printf(" *             MENU ESTATÍSTICAS                 *\n");
    printf(" *************************************************\n");
    printf(" * 1 - Mostrar estatísticas estudante            *\n");
    printf(" * 0 - Voltar                                    *\n");
    printf(" *************************************************\n\n");
    printf(" -->");
    scanf("%d",&op);
    return op;
}

int submenu_ficheiros()
{
    int op;
    system("cls||clear");
    printf(" *************************************************\n");
    printf(" *                  MENU FICHEIROS               *\n");
    printf(" *************************************************\n");
    printf(" * 1 - Guardar ficheiros                         *\n");
    printf(" * 2 - Carregar ficheiros                        *\n");
    printf(" * 3 - Limpar ficheiros                          *\n");
    printf(" * 0 - Voltar                                    *\n");
    printf(" *************************************************\n\n");
    printf(" -->");
    scanf("%d",&op);
    return op;
}


void estatisticas_aluno(t_avaliacao vetor_avaliacoes[], int numero_avaliacoes,t_unidade_curricular vetor_ucs[],int numero_ucs, int id_estudante,int codigo_estudante)
{
    system("cls||clear"); // Limpar o ecrã tanto para Windows como para Linux
    printf("************************************************\n");
    printf("*                Estudante Nº%d           *\n",codigo_estudante);
    printf("************************************************\n\n");
    printf("Total de UCS aprovadas: %d",contarUcsAprovadas(vetor_avaliacoes,numero_avaliacoes,id_estudante));
    printf("\nTotal de ECTS obtidos nas UCS aprovadas: %d",calcultarTotalEcts(vetor_avaliacoes,numero_avaliacoes,vetor_ucs,numero_ucs,id_estudante));
    printf("\nMédia das classificações nas UCS aprovadas: %.2f\n\n",calcularMediaUcsAprovadas(vetor_avaliacoes,numero_avaliacoes,id_estudante));
    printf("************************************************\n");
    printf("*          Detalhes por semestre letivos       *\n");
    printf("************************************************\n\n");
    obterDadosEstudantePorSemestre(vetor_avaliacoes,numero_avaliacoes,vetor_ucs,numero_ucs,id_estudante);
    fflush(stdin);
    printf("\n\nPRESSIONE <ENTER> PARA CONTINUAR...");
    getchar();
}

void escolha_epoca_avaliacao(char* str)
{
    int op;
    printf("\n");
    printf("Escolha a época de avaliação:\n");
    printf("\n1 -  Avaliação Final Semestre");
    printf("\n2 -  Avaliação De Recurso");
    printf("\n3 -  Avaliação De Época Especial");
    printf("\n-->");
    scanf("%d",&op);
    switch(op)
    {
    case 1:
        strcpy(str,"Avaliação Final Semestre");
        break;
    case 2:
        strcpy(str,"Avaliação De Recurso");
        break;
    case 3:
        strcpy(str,"Avaliação De Época Especial");
        break;
    default:
        printf("\nPor favor,escolha uma opção válida\n");
    }

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
            printf("\nO número está abaixo do valor pretendido (Os valores devem estar entre %d e %d)",valor_min,valor_max);
            printf("\n\nIntroduza o valor novamente: ");
        }
        else if(num > valor_max)
        {
            printf("\nO número está acima do valor pretendido (Os valores devem estar entre %d e %d)",valor_min,valor_max);
            printf("\n\nIntroduza o valor novamente novamente: ");
        }
    }
    while(num < valor_min || num > valor_max);

    return num;
}


int ler_dados_estudante(t_estudante vetor_estudantes[],int numero_estudantes)
{
    system("cls||clear"); // Limpar o ecrã tanto para Windows como para Linux
    printf("************************************************\n");
    printf("*                  Estudante Nº%d               *\n",numero_estudantes+1);
    printf("************************************************\n");
    vetor_estudantes[numero_estudantes].numero_estudante = verificarNumAlunoInexistente(vetor_estudantes,numero_estudantes);
    printf("\nNome: ");
    fflush(stdin);
    scanf("%80[^\n]", vetor_estudantes[numero_estudantes].nome);
    printf("\nCódigo do curso: ");
    scanf("%d",&vetor_estudantes[numero_estudantes].cod_curso);
    printf("\nEmail: ");
    ler_email_estudante(vetor_estudantes,numero_estudantes,-1);
    vetor_estudantes[numero_estudantes].id = numero_estudantes +1;
    fflush(stdin);
    printf("\n\nPRESSIONE <ENTER> PARA CONTINUAR...");
    getchar();
    system("cls||clear"); // Limpar o ecrã tanto para Windows como para Linux
    numero_estudantes++;
    return numero_estudantes;
}

int ler_dados_unidade_curricular(t_unidade_curricular vetor_ucs[],int numero_ucs)
{
    system("cls||clear");
    printf("************************************************\n");
    printf("*             Unidade Curricular Nº%d          *\n",numero_ucs+1);
    printf("************************************************\n\n");
    vetor_ucs[numero_ucs].cod_uc = verificarUcInexistente(vetor_ucs,numero_ucs);
    printf("\nNome: ");
    fflush(stdin);
    scanf("%50[^\n]", vetor_ucs[numero_ucs].nome_uc);
    printf("\nAno curricular: ");
    lerNumCardinal(vetor_ucs[numero_ucs].ano_curricular,sizeof(vetor_ucs[numero_ucs].ano_curricular),"º Ano",8,1);
    printf("\nSemestre: ");
    vetor_ucs[numero_ucs].semestre = ler_numero(1,10);
    printf("\nECTS: ");
    scanf("%d",&vetor_ucs[numero_ucs].ects);
    vetor_ucs[numero_ucs].id = numero_ucs +1;
    fflush(stdin);
    printf("\n\nPRESSIONE <ENTER> PARA CONTINUAR...");
    getchar();
    system("cls||clear");
    numero_ucs++;
    return numero_ucs;
}

int ler_dados_avaliacao(t_avaliacao vetor_avaliacoes[],int numero_avaliacoes,t_estudante vetor_estudantes[],int numero_estudantes,t_unidade_curricular vetor_ucs[],int numero_ucs)
{
    int indice_estudante,indice_uc,ano_letivo_valido;
    char ano_letivo[20];
    system("cls||clear");
    printf("************************************************\n");
    printf("*                 Avaliação  Nº%d              *\n",numero_avaliacoes+1);
    printf("************************************************\n\n");
    vetor_avaliacoes[numero_avaliacoes].id = numero_avaliacoes + 1;
    printf("Número do aluno: ");
    indice_estudante= verificarNumAlunoExistente(vetor_estudantes,numero_estudantes);
    printf("\nCódigo da unidade curricular: ");
    indice_uc = verificarUcExistente(vetor_ucs,numero_ucs);
    vetor_avaliacoes[numero_avaliacoes].id_estudante = vetor_estudantes[indice_estudante].id;
    vetor_avaliacoes[numero_avaliacoes].id_uc = vetor_ucs[indice_uc].id;
    printf("\nAno letivo: ");
    do
    {
        fflush(stdin);
        scanf("%20[^\n]", ano_letivo);
        ano_letivo_valido=validarAnoLetivo(ano_letivo);
    }
    while(ano_letivo_valido!=1);
    strcpy(vetor_avaliacoes[numero_avaliacoes].ano_letivo,ano_letivo);
    escolha_epoca_avaliacao(vetor_avaliacoes[numero_avaliacoes].epoca_avaliacao);
    ler_data_avaliacao(vetor_avaliacoes,numero_avaliacoes);
    printf("\nClassificação final: ");
    vetor_avaliacoes[numero_avaliacoes].classificao_final=ler_numero(0,20);
    printf("\n\nPRESSIONE <ENTER> PARA CONTINUAR...");
    getchar();
    system("cls||clear");
    numero_avaliacoes++;
    return numero_avaliacoes;
}


void ler_data_avaliacao(t_avaliacao vetor_avaliacoes[],int indice_avaliacao)
{
    int dia,mes,ano,dataValida,max,min,seculo;


    sscanf(vetor_avaliacoes[indice_avaliacao].ano_letivo,"%d-%d",&min,&max);
    seculo = obterPrimeirosDigitosAno(min);
    max = concatenar_inteiros(seculo,max);

    printf("\nData (DIA/MÊS/ANO): ");
    do
    {
        scanf("%d/%d/%d",&dia,&mes,&ano);
        dataValida = validarData(dia,mes,ano, max, min);
        if(dataValida !=1)
        {
            printf("\nIntroduza a data novamente: ");
        }
    }
    while(dataValida!=1);

    vetor_avaliacoes[indice_avaliacao].data_avaliacao.ano = ano;
    vetor_avaliacoes[indice_avaliacao].data_avaliacao.mes = mes;
    vetor_avaliacoes[indice_avaliacao].data_avaliacao.dia = dia;
}


int validarData(int dia,int mes,int ano,int max,int min)
{
    int isValido = 0,maximo_dias = 31;
    if( ano >= min && ano <=max && mes > 0 && mes <= 12 && dia > 1)
    {
        if(mes == 4 || mes == 6 || mes == 9 || mes == 11)
        {
            maximo_dias = 30;
        }
        else if (mes==2)
        {
            if(verificarAnoBissexto(ano))
            {
                maximo_dias = 29;
            }
            else
            {
                maximo_dias = 28;
            }
        }
        if(dia>maximo_dias)
        {
            printf("\n(Erro: o mês %d do ano %d não possui %d dias)", mes, ano, dia);
        }
        else
        {
            isValido = 1;
        }
    }
    else
    {
        printf("\n(Erro: Data fora dos intervalos pretendidos)");
    }
    return isValido;
}


int validarAnoLetivo(char anoLetivo[])
{
    int isAnoValido,anoLetivoInicial,anoLetivoFinal,valido=0,ultimosDigitos;

    isAnoValido = sscanf(anoLetivo, "%d-%d", &anoLetivoInicial, &anoLetivoFinal);

    ultimosDigitos = obterDigitosAno(anoLetivoInicial);

    if(isAnoValido==2)
    {
        if(anoLetivoInicial > anoLetivoFinal && anoLetivoFinal > ultimosDigitos )
        {
            valido = 1;
        }
        else
        {
            printf("\nO ano letivo não é válido,tente novamente: ");
        }
    }
    else
    {
        printf("\nO ano letivo deve seguir a seguinte estrutura: 1111-11,tente novamente: ");
    }

    return valido;
}

void lerNumCardinal(char* resultado,int len,char sufixo[],int max,int min)
{
    char frase[50];
    int numero;

    numero = ler_numero(min,max);

    sprintf(frase,"%d %s",numero,sufixo);

    strcpy(resultado,frase);
    resultado[len-1] =0;
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
        if(vetor_ucs[indice].cod_uc == codigo_uc)
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
    system("cls||clear");
    printf("*********************************************************************************************************************************\n");
    printf("*                                                                                                                               *\n");
    printf("*                                               ESTUDANTES EXISTENTES (Total estudantes: %d)                                    *\n",numero_estudantes);
    printf("*                                                                                                                               *\n");
    printf("*********************************************************************************************************************************\n");
    printf("\nID  | Nome                                                                           | Número de estudante | Código Curso | Email\n");
    printf("----|--------------------------------------------------------------------------------|---------------------|--------------|--------------------------------\n");
    for (int indice = 0; indice < numero_estudantes; indice++)
    {
        printf("%-4d| %-78s | %-19d | %-12d | %-30s\n",
               vetor_estudantes[indice].id,
               vetor_estudantes[indice].nome,
               vetor_estudantes[indice].numero_estudante,
               vetor_estudantes[indice].cod_curso,
               vetor_estudantes[indice].email);
    }
    printf("----|--------------------------------------------------------------------------------|---------------------|--------------|--------------------------------\n");
    fflush(stdin);
    printf("\n\nPRESSIONE <ENTER> PARA CONTINUAR...");
    getchar();
}

void mostrar_dados_avaliacoes(t_avaliacao vetor_avaliacoes[], int numero_avaliacoes)
{
    system("cls||clear");
    printf("******************************************************************************************************\n");
    printf("*                                                                                                    *\n");
    printf("*                               AVALIAÇÕES EXISTENTES (Total avaliações: %d)                          *\n",numero_avaliacoes);
    printf("*                                                                                                    *\n");
    printf("******************************************************************************************************\n");
    printf("\nID  | ID Estudante | ID UC | Classificação Final | Ano Letivo |   Época de Avaliação                   | Data Avaliação\n");
    printf("----|--------------|-------|---------------------|------------|----------------------------------------|---------------\n");

    for (int indice = 0; indice < numero_avaliacoes; indice++)
    {
        printf("%-4d| %-13d| %-6d| %-20d| %-11s| %-39s| %02d/%02d/%04d\n",
               vetor_avaliacoes[indice].id,
               vetor_avaliacoes[indice].id_estudante,
               vetor_avaliacoes[indice].id_uc,
               vetor_avaliacoes[indice].classificao_final,
               vetor_avaliacoes[indice].ano_letivo,
               vetor_avaliacoes[indice].epoca_avaliacao,
               vetor_avaliacoes[indice].data_avaliacao.dia,
               vetor_avaliacoes[indice].data_avaliacao.mes,
               vetor_avaliacoes[indice].data_avaliacao.ano);
    }
    printf("----|--------------|-------|---------------------|------------|----------------------------------------|---------------\n");
    fflush(stdin);
    printf("\n\nPRESSIONE <ENTER> PARA CONTINUAR...");
    getchar();
}

void mostrar_dados_estudante(t_estudante vetor_estudantes[], int indice_estudante)
{

    system("cls||clear");
    printf("\n\n");
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

void mostrar_dados_ucs(t_unidade_curricular vetor_ucs[],int numero_ucs)
{
    system("cls||clear");
    printf("**************************************************************************************************************\n");
    printf("*                                                                                                            *\n");
    printf("*                                UNIDADES CURRICULARES EXISTENTES (Total UCS: %d)                             *\n", numero_ucs);
    printf("*                                                                                                            *\n");
    printf("**************************************************************************************************************\n");

    printf("\nID  | Nome da UC                                       | Código da UC | Ano curricular | Semestre      | ECTS \n");
    printf("----|--------------------------------------------------|--------------|----------------|---------------|------\n");
    for (int indice = 0; indice < numero_ucs; indice++)
    {
        printf("%-4d| %-48s | %-12d | %-14s | %-3dº Semestre | %-6d\n",
               vetor_ucs[indice].id,
               vetor_ucs[indice].nome_uc,
               vetor_ucs[indice].cod_uc,
               vetor_ucs[indice].ano_curricular,
               vetor_ucs[indice].semestre,
               vetor_ucs[indice].ects
              );
    }
    printf("----|--------------------------------------------------|--------------|----------------|---------------|------\n");
    fflush(stdin);
    printf("\n\nPRESSIONE <ENTER> PARA CONTINUAR...");
    getchar();

}
void mostrar_dados_uc(t_unidade_curricular vetor_ucs[],int codigo_uc)
{
    system("cls||clear");
    printf(" **********************************************************************************************\n");
    printf("                                    Unidade Curricular Nº.%d                                   \n",vetor_ucs[codigo_uc].id);
    printf(" **********************************************************************************************\n");
    printf("   ID: %d                                                                                      \n",vetor_ucs[codigo_uc].id);
    printf("   Código da UC: %d                                                                            \n",vetor_ucs[codigo_uc].cod_uc);
    printf("   Nome: %s                                                                                    \n",vetor_ucs[codigo_uc].nome_uc);
    printf("   Ano curricular: %s                                                                          \n",vetor_ucs[codigo_uc].ano_curricular);
    printf("   Semestre: %d º Semestre                                                                     \n",vetor_ucs[codigo_uc].semestre);
    printf("   ECTS: %d                                                                                    \n",vetor_ucs[codigo_uc].ects);
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


void mostrar_editar_uc(t_unidade_curricular vetor_ucs[],int numero_ucs,int indice_uc)
{
    char sair;
    printf("\nAno curricular: ");
    do
    {
        mostrar_dados_uc(vetor_ucs,indice_uc);
        if(confirmarAcao("Deseja editar o código da  UC?")=='S')
        {
            printf("\n");
            vetor_ucs[indice_uc].cod_uc = verificarUcInexistente(vetor_ucs,numero_ucs);
        }
        if(confirmarAcao("Deseja editar o nome?")=='S')
        {
            printf("\nNovo nome: ");
            fflush(stdin);
            scanf("%50[^\n]", vetor_ucs[indice_uc].nome_uc);
        }
        if(confirmarAcao("Deseja editar  o campo ECTS?")=='S')
        {
            printf("\nNovo ECTS: ");
            scanf("%d",&vetor_ucs[indice_uc].ects);
        }
        if(confirmarAcao("Deseja editar o ano curricular da UC?")=='S')
        {
            printf("\nNovo ano curricular: ");
            lerNumCardinal(vetor_ucs[indice_uc].ano_curricular,sizeof(vetor_ucs[indice_uc].ano_curricular),"º Ano",8,1);
        }
        if(confirmarAcao("Deseja editar o semestre da UC?")=='S')
        {
            printf("\nNovo semestre: ");
            vetor_ucs[indice_uc].semestre = ler_numero(1,10);
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
            printf("\n(Erro:O aluno com o número de estudante %d não existe),tente novamente: ",numero_estudante);
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
            printf("\n(Erro: O aluno já existe!),tente novamente: ");
        }
    }
    while(indice_estudante !=-1);

    return numero_estudante;
}

int verificarUcExistente(t_unidade_curricular vetor_ucs[],int numero_ucs)
{
    int indice_uc,codigo_uc;
    do
    {
        scanf("%d",&codigo_uc);
        indice_uc = procurar_unidade_curricular(vetor_ucs,numero_ucs,codigo_uc);
        if(indice_uc == -1)
        {
            printf("\n(Erro:A unidade curricular com o código %d não existe),tente novamente: ",codigo_uc);
        }
    }
    while(indice_uc == -1);

    return indice_uc;
}

int verificarUcInexistente(t_unidade_curricular vetor_ucs[],int numero_ucs)
{
    int indice_uc,codigo_uc;
    do
    {
        printf("Código da unidade curricular: ");
        scanf("%d",&codigo_uc);
        indice_uc = procurar_unidade_curricular(vetor_ucs,numero_ucs,codigo_uc);
        if(indice_uc != -1)
        {
            printf("\n(Erro: A unidade curricular já existe!),tente novamente: ");
        }
    }
    while(indice_uc !=-1);

    return codigo_uc;
}

int verificarAnoBissexto(int ano)
{
    int isBissexto;

    if ((ano % 4 == 0) && ((ano % 100 != 0) || (ano % 400 == 0)))

    {
        isBissexto = 1;
    }
    else
    {
        isBissexto = 0;
    }

    return isBissexto;

}


int ler_tecla()
{
    int numero_tecla;
    fflush(stdin);
    numero_tecla = getchar();

    return numero_tecla;
}

void gravarFicheiroEstudantes(t_estudante vetor_estudantes[],int numero_estudantes)
{
    FILE *ficheiro;
    ficheiro = fopen("estudantes.dat","wb");
    if(ficheiro == NULL)
    {
        printf("Não foi posível criar o ficheiro");
    }
    else
    {
        fwrite(&numero_estudantes,sizeof(int),1,ficheiro);
        fwrite(vetor_estudantes,sizeof(t_estudante),numero_estudantes,ficheiro);


        fclose(ficheiro);
        printf("\nEscrita dos dados de %d alunos em ficheiro com sucesso.",numero_estudantes);
    }
}

void gravarFicheiroUcs(t_unidade_curricular vetor_ucs[],int numero_ucs)
{
    FILE *ficheiro;
    ficheiro = fopen("unidades_curriculares.dat","wb");
    if(ficheiro == NULL)
    {
        printf("Não foi posível criar o ficheiro");
    }
    else
    {
        fwrite(&numero_ucs,sizeof(int),1,ficheiro);
        fwrite(vetor_ucs,sizeof(t_unidade_curricular),numero_ucs,ficheiro);
        fclose(ficheiro);
        printf("\nEscrita dos dados de %d unidades curriculares em ficheiro com sucesso.",numero_ucs);
    }
}

void gravarFicheiroAvaliacoes(t_avaliacao vetor_avaliacoes[],int numero_avaliacoes)
{
    FILE *ficheiro;
    ficheiro = fopen("avaliacoes.dat","wb");
    if(ficheiro == NULL)
    {
        printf("Não foi posível criar o ficheiro");
    }
    else
    {
        fwrite(&numero_avaliacoes,sizeof(int),1,ficheiro);
        fwrite(vetor_avaliacoes,sizeof(t_avaliacao),numero_avaliacoes,ficheiro);

        fclose(ficheiro);
        printf("\nEscrita dos dados de %d avaliações em ficheiro com sucesso.",numero_avaliacoes);
    }

}

int lerFicheiroEstudantes(t_estudante vetor_estudantes[])
{
    int numero_estudantes=0,numero_estudantes_lido=0;
    FILE *ficheiro;
    ficheiro = fopen("estudantes.dat","rb");
    if(ficheiro == NULL)
    {
        printf("\nO ficheiro dos estudantes não existe. Será criado um novo ficheiro vazio.\n");
        ficheiro = fopen("estudantes.dat", "wb");
        if (ficheiro != NULL)
        {
            fwrite(&numero_estudantes, sizeof(int), 1, ficheiro);
            fwrite(vetor_estudantes,sizeof(t_estudante),numero_estudantes,ficheiro);
            fclose(ficheiro);
        }
    }
    else
    {
        fread(&numero_estudantes,sizeof(int),1,ficheiro);
        numero_estudantes_lido = fread(vetor_estudantes,sizeof(t_estudante),numero_estudantes,ficheiro);
        fclose(ficheiro);
        if(numero_estudantes_lido != numero_estudantes)
        {
            printf("Erro na leitura de dados do ficheiro!");
        }
        else
        {
            printf("\nLeitura de %d alunos do ficheiro com sucesso.",numero_estudantes_lido);
        }
    }

    return numero_estudantes_lido;
}

int lerFicheiroUcs(t_unidade_curricular vetor_ucs[])
{
    int numero_ucs=0,numero_ucs_lido=0;
    FILE *ficheiro;
    ficheiro = fopen("unidades_curriculares.dat","rb");
    if(ficheiro == NULL)
    {
        printf("\nO ficheiro das unidades curriculares não existe. Será criado um novo ficheiro vazio.\n");
        ficheiro = fopen("unidades_curriculares.dat", "wb");
        if (ficheiro != NULL)
        {
            fwrite(&numero_ucs, sizeof(int), 1, ficheiro);
            fwrite(vetor_ucs,sizeof(t_unidade_curricular),numero_ucs,ficheiro);
            fclose(ficheiro);
        }
    }
    else
    {
        fread(&numero_ucs,sizeof(int),1,ficheiro);
        numero_ucs_lido = fread(vetor_ucs,sizeof(t_unidade_curricular),numero_ucs,ficheiro);
        fclose(ficheiro);
        if(numero_ucs_lido != numero_ucs)
        {
            printf("Erro na leitura de dados do ficheiro!");
        }
        else
        {
            printf("\nLeitura de %d unidades curriculares do ficheiro com sucesso.",numero_ucs_lido);
        }
    }

    return numero_ucs_lido;
}

int lerFicheiroAvaliacoes(t_avaliacao vetor_avaliacoes[])
{
    int numero_avaliacoes=0,numero_avaliacoes_lido=0;
    FILE *ficheiro;
    ficheiro = fopen("avaliacoes.dat","rb");
    if(ficheiro == NULL)
    {
        printf("\nO ficheiro das avaliações não existe. Será criado um novo ficheiro vazio.\n");
        ficheiro = fopen("avaliacoes.dat", "wb");
        if (ficheiro != NULL)
        {
            fwrite(&numero_avaliacoes, sizeof(int), 1, ficheiro);
            fwrite(vetor_avaliacoes,sizeof(t_avaliacao),numero_avaliacoes,ficheiro);
            fclose(ficheiro);
        }

    }
    else
    {
        fread(&numero_avaliacoes,sizeof(int),1,ficheiro);
        numero_avaliacoes_lido = fread(vetor_avaliacoes,sizeof(t_avaliacao),numero_avaliacoes,ficheiro);
        fclose(ficheiro);
        if(numero_avaliacoes_lido != numero_avaliacoes)
        {
            printf("Erro na leitura de dados do ficheiro!");
        }
        else
        {
            printf("\nLeitura de %d avaliações do ficheiro com sucesso.",numero_avaliacoes_lido);
        }
    }

    return numero_avaliacoes_lido;
}

void limparFicheiroEstudante(t_estudante vetor_estudantes[])
{
    FILE *ficheiro;
    ficheiro = fopen("estudantes.dat","wb");
    if(ficheiro == NULL)
    {
        printf("\nNão foi possível limpar o ficheiro das avaliações.\n");

    }
    else
    {
        printf("\nO ficheiro das unidades curriculares foi limpo com sucesso!\n");
        memset(vetor_estudantes,0,sizeof(vetor_estudantes));
    }
    fclose(ficheiro);
    getchar();

}

void limparFicheiroUcs(t_unidade_curricular vetor_ucs[])
{
    FILE *ficheiro;
    ficheiro = fopen("unidades_curriculares.dat","wb");
    if(ficheiro == NULL)
    {
        printf("\nNão foi possível limpar o ficheiro das avaliações.\n");

    }
    else
    {
        printf("\nO ficheiro das unidades curriculares foi limpo com sucesso!\n");
        memset(vetor_ucs,0,sizeof(vetor_ucs));
    }
    fclose(ficheiro);
}


void limparFicheiroAvaliacoes(t_avaliacao vetor_avaliacoes[])
{
    FILE *ficheiro;
    ficheiro = fopen("avaliacoes.dat","wb");
    if(ficheiro == NULL)
    {
        printf("\nNão foi possível limpar o ficheiro das avaliações.\n");

    }
    else
    {
        printf("\nO ficheiro das avaliações foi limpo com sucesso!\n");
        memset(vetor_avaliacoes,0,sizeof(vetor_avaliacoes));
    }
    fclose(ficheiro);
}

//Função para obter os últimos dois digitos de um ano
int obterDigitosAno(int ano)
{
    int ultimo;
    ultimo = ano % 100;
    return ultimo;
}

//Função para obter os primeiros dois digitos de um ano
int obterPrimeirosDigitosAno(int ano)
{
    int primeiro;
    primeiro = ano / 100;
    return primeiro;
}

int contarUcsAprovadas(t_avaliacao vetor_avaliacoes[],int numero_avaliacoes,int id_estudante)
{
    int totalUcsAprovadas = 0;
    for(int indice = 0; indice<numero_avaliacoes; indice++)
    {
        if(vetor_avaliacoes[indice].id_estudante == id_estudante && vetor_avaliacoes[indice].classificao_final >=NOTA_FINAL_MINIMA)
        {
            totalUcsAprovadas++;
        }
    }

    return totalUcsAprovadas;
}

int calcultarTotalEcts(t_avaliacao vetor_avaliacoes[],int numero_avaliacoes,t_unidade_curricular vetor_ucs[],int numero_ucs,int id_estudante)
{
    int totalEcts = 0;
    for(int indice = 0; indice<numero_avaliacoes; indice++)
    {
        if(vetor_avaliacoes[indice].id_estudante == id_estudante && vetor_avaliacoes[indice].classificao_final >=NOTA_FINAL_MINIMA)
        {
            for (int indiceUcs = 0; indiceUcs<numero_ucs; indiceUcs++)
            {
                if(vetor_avaliacoes[indice].id_uc == vetor_ucs[indiceUcs].id)
                {
                    totalEcts += vetor_ucs[indiceUcs].ects;
                }
            }
        }
    }

    return totalEcts;
}

float calcularMediaUcsAprovadas(t_avaliacao vetor_avaliacoes[],int numero_avaliacoes,int id_estudante)
{
    int numeroUcsAprovadas = contarUcsAprovadas(vetor_avaliacoes, numero_avaliacoes, id_estudante);
    int somaNotas = 0;
    float media;

    for(int indice = 0; indice<numero_avaliacoes; indice++)
    {
        if(vetor_avaliacoes[indice].id_estudante == id_estudante && vetor_avaliacoes[indice].classificao_final >=NOTA_FINAL_MINIMA)
        {
            somaNotas += vetor_avaliacoes[indice].classificao_final;
        }
    }

    media = (float)somaNotas / numeroUcsAprovadas;

    return media;
}


int procurar_maior_semestre(t_unidade_curricular vetor_ucs[],int numero_ucs)
{
    int maior = 0;

    for (int indice = 0; indice<numero_ucs; indice++)
    {
        if (vetor_ucs[indice].semestre > maior)
        {
            maior = vetor_ucs[indice].semestre;
        }

    }
    return maior;
}

void obterDadosEstudantePorSemestre(t_avaliacao vetor_avaliacoes[], int numero_avaliacoes,t_unidade_curricular vetor_ucs[],int numero_ucs, int id_estudante)
{
    int numeroSemestres = procurar_maior_semestre(vetor_ucs,numero_ucs);

    int numeroNotasSemestre,numeroNotasAprovadasSemestre;
    float percentagem_aprovados;


    for (int semestre = 1; semestre <= numeroSemestres; semestre++)
    {
        numeroNotasSemestre = 0;
        numeroNotasAprovadasSemestre = 0;
        for (int indiceUc = 0; indiceUc < numero_ucs; indiceUc++)
        {
            if(vetor_ucs[indiceUc].semestre == semestre)
            {
                for (int indiceAvaliacoes = 0; indiceAvaliacoes < numero_avaliacoes; indiceAvaliacoes++)
                {
                    if(vetor_avaliacoes[indiceAvaliacoes].id_estudante == id_estudante && vetor_avaliacoes[indiceAvaliacoes].id_uc == vetor_ucs[indiceUc].id)
                    {
                        numeroNotasSemestre++;


                        if(vetor_avaliacoes[indiceAvaliacoes].classificao_final>=NOTA_FINAL_MINIMA)
                        {
                            numeroNotasAprovadasSemestre++;
                        }

                    }
                }
            }
        }
        if(numeroNotasSemestre > 0)
        {
            percentagem_aprovados = (float)numeroNotasAprovadasSemestre / numeroNotasSemestre * 100.0;
            printf("Semestre %d: %.2f%% de notas aprovadas (%d aprovadas de %d)\n", semestre, percentagem_aprovados,numeroNotasAprovadasSemestre,numeroNotasSemestre);
        }
        else
        {
            printf("Semestre %d: Não existem dados insuficientes\n", semestre);
        }
    }
}

int concatenar_inteiros(int num1,int num2)
{
    int resultado;
    char str[100];
    sprintf(str,"%d%d",num1,num2);
    resultado = strtol(str, NULL, 10);
    return resultado;
}

