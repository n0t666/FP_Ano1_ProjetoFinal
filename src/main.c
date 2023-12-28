/*
 *
 * Autores:
 *  - Leandro Alves Pereira <223175@my.ipleiria.pt> <PL2>
 *
 * Data:
 *
 * Descri��o:
    - Trabalho realizado no �mbito do projeto final da disciplina de Fundamentos de Programa��o
 */


//------------------------------------------------------------------------------------------------
// Bibliotecas de pr�-processamento
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

#define DATA_MINIMA 2000

//-------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------
// Defini��o das estruturas de dados
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
// Fun��es relacionadas com menus e submenujs
//------------------------------------------------------------------------------------------------
int menu_principal(void);
int submenu_estudantes(void);
int submenu_ucs(void);
int submenu_avaliacoes(void);
int submenu_estatisticas_gerais(void);
int submenu_estatisticas_especificas(void);
//-------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------------------
// Fun��es utilit�rias do programa
//------------------------------------------------------------------------------------------------
void lerNumCardinal(char* resultado,int len,char sufixo[],int max,int min);

int ler_numero(int valor_min,int valor_max);
int ler_tecla(void);

char confirmarAcao(char msg[]);
//-------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------------------
// Fun��es relacionados com os ficheiros
//------------------------------------------------------------------------------------------------

//Leitura
void gravarFicheiroEstudantes(t_estudante vetor_estudantes[],int numero_estudantes);
void gravarFicheiroUcs(t_unidade_curricular vetor_ucs[],int numero_ucs);
void gravarFicheiroAvaliacoes(t_avaliacao vetor_avaliacoes[],int numero_avaliacoes);

//Escrita



//-------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------------------
// Fun��es relacionadas com a manipula��o da  estrutura de dados estudantes
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
// Fun��es relacionadas com a manipula��o da  estrutura de dados unidade_curricular
//------------------------------------------------------------------------------------------------

int ler_dados_unidade_curricular(t_unidade_curricular vetors_ucs[],int numero_ucs);
int procurar_unidade_curricular(t_unidade_curricular vetors_ucs[],int numero_ucs,int codigo_uc);

int verificarUcExistente(t_unidade_curricular vetors_ucs[],int numero_ucs);
int verificarUcInexistente(t_unidade_curricular vetors_ucs[],int numero_ucs);

void mostrar_dados_ucs(t_unidade_curricular vetors_ucs[],int numero_ucs);
void mostrar_dados_uc(t_unidade_curricular vetors_ucs[],int codigo_uc);

//-------------------------------------------------------------------------------------------------

int main(void)
{

    setlocale(LC_ALL,"Portuguese");

    t_estudante vetor_estudantes[MAXIMO_ESTUDANTES];
    t_unidade_curricular vetor_ucs[MAXIMO_UNIDADES_CURRICULARES];
    t_avaliacao vetor_avaliacoes[MAXIMO_AVALIACOES];

    int menu_principal_op,submenu_estudantes_op,submenu_ucs_op,submenu_avaliacoes_op,submenu_estatisticas_op;

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
                        printf("\nPara usar esta op��o necessita de ter pelo menos 1 estudante inserido no sistema");
                        fflush(stdin);
                        printf("\n\nPRESSIONE <ENTER> PARA CONTINUAR...");
                        getchar();
                    }
                    break;
                case 3:
                    if(numero_estudantes>0)
                    {
                        printf("\nIntroduza o n�mero de estudante que pretende consultar: ");
                        indice_estudante = verificarNumAlunoExistente(vetor_estudantes,numero_estudantes);
                        mostrar_dados_estudante(vetor_estudantes,indice_estudante);

                    }
                    else
                    {
                        printf("\nPara usar esta op��o necessita de ter pelo menos 1 estudante inserido no sistema");
                        fflush(stdin);
                        printf("\n\nPRESSIONE <ENTER> PARA CONTINUAR...");
                        getchar();
                    }
                    break;
                case 4:
                    if(numero_estudantes>0)
                    {
                        printf("\nIntroduza o n�mero de estudante que pretende editar: ");
                        indice_estudante = verificarNumAlunoExistente(vetor_estudantes,numero_estudantes);
                        mostrar_editar_estudante(vetor_estudantes,numero_estudantes,indice_estudante);

                    }
                    else
                    {
                        printf("\nPara usar esta op��o necessita de ter pelo menos 1 estudante inserido no sistema");
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
                        printf("\nPara usar esta op��o necessita de ter pelo menos 1 UC inserido no sistema");
                        fflush(stdin);
                        printf("\n\nPRESSIONE <ENTER> PARA CONTINUAR...");
                        getchar();
                    }
                    break;
                case 3:
                    if(numeros_ucs>0)
                    {
                        printf("\nIntroduza o c�digo da UC que pretende consultar: ");
                        indice_uc = verificarUcExistente(vetor_ucs,numeros_ucs);
                        mostrar_dados_uc(vetor_ucs,indice_uc);
                    }
                    else
                    {
                        printf("\nPara usar esta op��o necessita de ter pelo menos 1 UC inserido no sistema");
                        fflush(stdin);
                        printf("\n\nPRESSIONE <ENTER> PARA CONTINUAR...");
                        getchar();
                    }
                    break;
                case 4:
                    if(numeros_ucs>0)
                    {
                        printf("\nIntroduza o c�digo da UC que pretende editar: ");
                        indice_uc = verificarUcExistente(vetor_ucs,numeros_ucs);
                        mostrar_editar_uc(vetor_ucs,numeros_ucs,indice_uc);
                    }
                    else
                    {
                        printf("\nPara usar esta op��o necessita de ter pelo menos 1 UC inserido no sistema");
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
                    printf("\nOp��o inv�lida");
                }

            }
            while(submenu_avaliacoes_op!=0);
            break;
        case 4:
            break;
        default:
            printf("\nOp��o inv�lida");
            fflush(stdin);
            printf("\n\nPRESSIONE <ENTER> PARA CONTINUAR...");
            getchar();
            system("cls||clear"); // Limpar o ecr� tanto para Windows como para Linux
        }
    }
    while(saida!='S');
    gravarFicheiroEstudantes(vetor_estudantes,numero_estudantes);
    gravarFicheiroUcs(vetor_ucs,numeros_ucs);
    gravarFicheiroAvaliacoes(vetor_avaliacoes,numero_avaliacoes);
}

int menu_principal()
{
    int op;
    printf(" ******************************************\n");
    printf(" *           MENU PRINCIPAL               *\n");
    printf(" ******************************************\n");
    printf(" * 1 - Estudantes                         *\n");
    printf(" * 2 - Unidades Curriculares              *\n");
    printf(" * 3 - Avalia��es                         *\n");
    printf(" * 4 - Estat�sticas                       *\n");
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
    printf(" * 3 - Consultar aluno espec�fico         *\n");
    printf(" * 4 - Editar aluno espec�fico            *\n");
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
    printf(" **************************************************\n");
    printf(" *            MENU UNIDADES CURRICULARES         **\n");
    printf(" **************************************************\n");
    printf(" * 1 - Registrar novas unidades curriculares      *\n");
    printf(" * 2 - Consultar unidades curriculares existentes *\n");
    printf(" * 3 - Consultar unidade curricular existente     *\n");
    printf(" * 4 - Editar unidade curricular espec�fica       *\n");
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
    printf(" *           MENU AVALIA��ES              *\n");
    printf(" ******************************************\n");
    printf(" * 1 - Registrar novas avalia��es         *\n");
    printf(" * 2 - Consultar avalia��es existentes    *\n");
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
    printf(" *           MENU ESTAT�STICAS ESPEC�FICAS       *\n");
    printf(" ************************************************\n");
    printf(" * Total de ECTS aprovados pelos estudantes:     *\n");
    printf(" * 0 - Voltar                                   *\n");
    printf(" ************************************************\n\n");
    printf(" -->");
    scanf("%d",&op);
    return op;
}

void escolha_epoca_avaliacao(char* str)
{
    int op;
    printf("\n");
    printf("************************************************\n");
    printf("*           Escolha a �poca de avalia��o:      *\n");
    printf("************************************************\n");
    printf("\n1 -  Avalia��o Final Semestre");
    printf("\n2 -  Avalia��o De Recurso");
    printf("\n3 -  Avalia��o De �poca Especial");
    printf("\n-->");
    scanf("%d",&op);
    switch(op)
    {
    case 1:
        strcpy(str,"Avalia��o Final Semestre");
        break;
    case 2:
        strcpy(str,"Avalia��o De Recurso");
        break;
    case 3:
        strcpy(str,"Avalia��o De �poca Especial");
        break;
    default:
        printf("\nPor favor,escolha uma op��o v�lida\n");
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
            printf("\nO n�mero est� abaixo do valor pretendido (Os valores devem estar entre %d e %d)",valor_min,valor_max);
            printf("\n\nIntroduza o valor novamente: ");
        }
        else if(num > valor_max)
        {
            printf("\nO n�mero est� acima do valor pretendido (Os valores devem estar entre %d e %d)",valor_min,valor_max);
            printf("\n\nIntroduza o valor novamente novamente: ");
        }
    }
    while(num < valor_min || num > valor_max);

    return num;
}


int ler_dados_estudante(t_estudante vetor_estudantes[],int numero_estudantes)
{
    system("cls||clear"); // Limpar o ecr� tanto para Windows como para Linux
    printf("************************************************\n");
    printf("*                  Estudante N�%d               *\n",numero_estudantes+1);
    printf("************************************************\n");
    vetor_estudantes[numero_estudantes].numero_estudante = verificarNumAlunoInexistente(vetor_estudantes,numero_estudantes);
    printf("\nNome: ");
    fflush(stdin);
    scanf("%80[^\n]", vetor_estudantes[numero_estudantes].nome);
    printf("\nC�digo do curso: ");
    scanf("%d",&vetor_estudantes[numero_estudantes].cod_curso);
    printf("\nEmail: ");
    ler_email_estudante(vetor_estudantes,numero_estudantes,-1);
    vetor_estudantes[numero_estudantes].id = numero_estudantes +1;
    fflush(stdin);
    printf("\n\nPRESSIONE <ENTER> PARA CONTINUAR...");
    getchar();
    system("cls||clear"); // Limpar o ecr� tanto para Windows como para Linux
    numero_estudantes++;
    return numero_estudantes;
}

int ler_dados_unidade_curricular(t_unidade_curricular vetor_ucs[],int numero_ucs)
{
    system("cls||clear");
    printf("************************************************\n");
    printf("*             Unidade Curricular N�%d          *\n",numero_ucs+1);
    printf("************************************************\n\n");
    vetor_ucs[numero_ucs].cod_uc = verificarUcInexistente(vetor_ucs,numero_ucs);
    printf("\nNome: ");
    fflush(stdin);
    scanf("%50[^\n]", vetor_ucs[numero_ucs].nome_uc);
    printf("\nAno curricular: ");
    lerNumCardinal(vetor_ucs[numero_ucs].ano_curricular,sizeof(vetor_ucs[numero_ucs].ano_curricular),"� Ano",8,1);
    printf("\nSemestre: ");
    lerNumCardinal(vetor_ucs[numero_ucs].semestre,sizeof(vetor_ucs[numero_ucs].semestre),"� Semestre",10,1);
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
    printf("*                 Avalia��o  N�%d              *\n",numero_avaliacoes+1);
    printf("************************************************\n\n");
    vetor_avaliacoes[numero_avaliacoes].id = numero_avaliacoes + 1;
    printf("\nN�mero do aluno: ");
    indice_estudante= verificarNumAlunoExistente(vetor_estudantes,numero_estudantes);
    printf("\nC�digo da unidade curricular: ");
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
    printf("\nClassifica��o final: ");
    vetor_avaliacoes[numero_avaliacoes].classificao_final=ler_numero(0,20);
    printf("\n\nPRESSIONE <ENTER> PARA CONTINUAR...");
    getchar();
    system("cls||clear");
    numero_avaliacoes++;
    return numero_avaliacoes;
}


void ler_data_avaliacao(t_avaliacao vetor_avaliacoes[],int indice_avaliacao)
{
    int dia,mes,ano,dataValida;

    printf("\nData (DIA/M�S/ANO): ");
    do
    {
        scanf("%d/%d/%d",&dia,&mes,&ano);
        dataValida = validarData(dia,mes,ano);
        if(dataValida !=1)
        {
            printf("\Introduza a data novamente: ");
        }
    }
    while(dataValida!=1);

    vetor_avaliacoes[indice_avaliacao].data_avaliacao.ano = ano;
    vetor_avaliacoes[indice_avaliacao].data_avaliacao.mes = mes;
    vetor_avaliacoes[indice_avaliacao].data_avaliacao.dia = dia;
}


int validarData(int dia,int mes,int ano)
{
    int isValido = 0,maximo_dias = 31;
    if( ano >= DATA_MINIMA && mes > 0 && mes <= 12 && dia > 1)
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
            printf("\n(Erro: o m�s %d do ano %d n�o possui %d dias)", mes, ano, dia);
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
            printf("\nO ano letivo n�o � v�lido,tente novamente: ");
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


// Fun��o para ler e validar um endere�o de email de um estudante
// Recebe como par�metro o vetor dos estudantes e um �ndice para adicionar o email v�lido ao vetor
int validar_email_estudante(char email[],t_estudante vetor_estudantes[],int numero_estudantes)
{
    char username[50], dominio[50];
    int isEmailValido,valido=0;

    // Verificar se o email corresponde ao formato especificado (utilizador@dom�nio), devolvendo n�mero de parametros cumpridos, no caso de estar totalmente correto devolve 2
    isEmailValido = sscanf(email, "%[_a-zA-Z0-9.]@%[_a-zA-Z0-9.]", username, dominio);
    if(isEmailValido == 2)  // O formato do email � v�lido
    {
        if(strcmp(dominio,DOMINIO_EMAIL_ESTUDANTES)!=0)  // Caso o dominio do email n�o for igual a  "my.ipleiria.pt"
        {
            printf("\nTodos os endere�os email devem ser do tipo %s\n", DOMINIO_EMAIL_ESTUDANTES); //Messagem de erro
        }
        else
        {
            if(procurar_email_estudante(email,vetor_estudantes,numero_estudantes)==-1)
            {
                valido = 1; //Flag que permite indicar que est� tudo correto com endere�o email
            }
            else
            {
                printf("\nO endere�o email j� est� associado a outro estudante,tente novamente: ");
            }
        }
    }
    else   //Se o email n�o tiver todos os requisitos
    {
        printf("\nO endere�o email deve ser v�lido,tente novamente: ");
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
    while(valido!=1);  //Enquanto a flag n�o for 1 (o email n�o estiver correto)
    if(indice_especifico==-1)
    {
        strcpy(vetor_estudantes[numero_estudantes].email, email); // Copiar o endere�o de email v�lido para a estrutura
    }
    else
    {
        strcpy(vetor_estudantes[indice_especifico].email, email); // Copiar o endere�o de email v�lido para a estrutura
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
    printf("ID  | Nome                                                                           | N�mero de estudante | C�digo Curso | Email\n");
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

void mostrar_dados_avaliacoes(t_avaliacao vetor_avaliacoes[], int numero_avaliacoes)
{
    printf("ID  | ID Estudante | ID UC | Classifica��o Final | Ano Letivo | �poca de Avalia��o | Data Avalia��o\n");
    printf("----|--------------|-------|---------------------|------------|--------------------|---------------\n");

    for (int indice = 0; indice < numero_avaliacoes; indice++)
    {
        printf("%-4d| %-13d| %-6d| %-20d| %-11s| %-19s| %02d/%02d/%04d\n",
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
    printf("----|--------------|-------|---------------------|------------|--------------------|---------------\n");
    fflush(stdin);
    getchar();
}

void mostrar_dados_estudante(t_estudante vetor_estudantes[], int indice_estudante)
{
    system("cls||clear");
    printf(" **********************************************************************************************\n");
    printf("                                        ALUNO N�.%d                                            \n",vetor_estudantes[indice_estudante].numero_estudante);
    printf(" **********************************************************************************************\n");
    printf("   ID: %d                                                                                      \n",vetor_estudantes[indice_estudante].id);
    printf("   N�mero de estudante: %d                                                                     \n",vetor_estudantes[indice_estudante].numero_estudante);
    printf("   Nome: %s                                                                                    \n",vetor_estudantes[indice_estudante].nome);
    printf("   C�digo de curso: %d                                                                         \n",vetor_estudantes[indice_estudante].cod_curso);
    printf("   Email: %s                                                                                   \n",vetor_estudantes[indice_estudante].email);
    printf(" **********************************************************************************************\n\n");
    fflush(stdin);
    printf("\n\nPRESSIONE <ENTER> PARA CONTINUAR...");
    getchar();
}

void mostrar_dados_ucs(t_unidade_curricular vetor_ucs[],int numero_ucs)
{
    printf("ID  | Nome da UC                                       | C�digo da UC | Ano curricular | Semestre      | ECTS\n");
    printf("----|--------------------------------------------------|--------------|----------------|---------------|------\n");
    for (int indice = 0; indice < numero_ucs; indice++)
    {
        printf("%-4d| %-48s | %-12d | %-14s | %-13s | %-6d\n",
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
    getchar();

}
void mostrar_dados_uc(t_unidade_curricular vetor_ucs[],int codigo_uc)
{
    system("cls||clear");
    printf(" **********************************************************************************************\n");
    printf("                                    Unidade Curricular N�.%d                                   \n",vetor_ucs[codigo_uc].id);
    printf(" **********************************************************************************************\n");
    printf("   ID: %d                                                                                      \n",vetor_ucs[codigo_uc].id);
    printf("   C�digo da UC: %d                                                                            \n",vetor_ucs[codigo_uc].cod_uc);
    printf("   Nome: %s                                                                                    \n",vetor_ucs[codigo_uc].nome_uc);
    printf("   Ano curricular: %s                                                                          \n",vetor_ucs[codigo_uc].ano_curricular);
    printf("   Semestre: %s                                                                                \n",vetor_ucs[codigo_uc].semestre);
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
        if(confirmarAcao("Deseja editar o n�mero de  estudante?")=='S')
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
        if(confirmarAcao("Deseja editar o c�digo do curso?")=='S')
        {
            printf("\nNovo c�digo de curso: ");
            scanf("%d", &vetor_estudantes[indice_estudante].cod_curso);
        }
        printf("-----------------------------------------------");
        sair = confirmarAcao("Continuar no modo edi��o?");
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
        if(confirmarAcao("Deseja editar o c�digo da  UC?")=='S')
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
            lerNumCardinal(vetor_ucs[indice_uc].ano_curricular,sizeof(vetor_ucs[indice_uc].ano_curricular),"� Ano",8,1);
        }
        if(confirmarAcao("Deseja editar o semestre da UC?")=='S')
        {
            printf("\nNovo semestre: ");
            lerNumCardinal(vetor_ucs[indice_uc].semestre,sizeof(vetor_ucs[indice_uc].semestre),"� Semestre",10,1);
        }
        printf("-----------------------------------------------");
        sair = confirmarAcao("Continuar no modo edi��o?");
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
            printf("\n(Erro:O aluno com o n�mero de estudante %d n�o existe),tente novamente: ",numero_estudante);
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
        printf("N�mero de estudante: ");
        numero_estudante = ler_numero(MINIMO_NUMERO_ESTUDANTE,MAXIMO_NUMERO_ESTUDANTE);
        indice_estudante = procurar_estudante(vetor_estudantes,numero_estudantes,numero_estudante);
        if(indice_estudante != -1)
        {
            printf("\n(Erro: O aluno j� existe!),tente novamente: ");
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
            printf("\n(Erro:A unidade curricular com o c�digo %d n�o existe),tente novamente: ",codigo_uc);
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
        printf("C�digo da unidade curricular: ");
        scanf("%d",&codigo_uc);
        indice_uc = procurar_unidade_curricular(vetor_ucs,numero_ucs,codigo_uc);
        if(indice_uc != -1)
        {
            printf("\n(Erro: A unidade curricular j� existe!),tente novamente: ");
        }
    }
    while(indice_uc !=-1);

    return codigo_uc;
}

int verificarAnoBissexto(int ano)
{
    int isBissexto;

    if((ano % 4 == 0) && (ano % 100!=0) || (ano%400==0))
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
        printf("N�o foi pos�vel criar o ficheiro");
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
        printf("N�o foi pos�vel criar o ficheiro");
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
        printf("N�o foi pos�vel criar o ficheiro");
    }
    else
    {
        fwrite(&numero_avaliacoes,sizeof(int),1,ficheiro);
        fwrite(vetor_avaliacoes,sizeof(t_avaliacao),numero_avaliacoes,ficheiro);

        fclose(ficheiro);
        printf("\nEscrita dos dados de %d avalia��es em ficheiro com sucesso.",numero_avaliacoes);
    }

}

int lerFicheiroEstudantes(t_estudante vetor_estudantes[])
{
    int numero_estudantes=0,numero_estudantes_lido=0;
    FILE *ficheiro;
    ficheiro = fopen("estudantes.dat","rb");
    if(ficheiro == NULL)
    {
        printf("\nO ficheiro dos estudantes n�o existe. Ser� criado um novo ficheiro vazio.\n");
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
        printf("\nO ficheiro das unidades curriculares n�o existe. Ser� criado um novo ficheiro vazio.\n");
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
        printf("\nO ficheiro das avalia��es n�o existe. Ser� criado um novo ficheiro vazio.\n");
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
            printf("\nLeitura de %d avalia��es do ficheiro com sucesso.",numero_avaliacoes_lido);
        }
    }

    return numero_avaliacoes_lido;
}

//Fun��o para obter os �ltimos dois digitos de um ano
int obterDigitosAno(ano)
{
    int ultimo;
    ultimo = ano % 100;
    return ultimo;
}
