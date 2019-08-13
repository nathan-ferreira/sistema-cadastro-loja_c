#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max 8
#define lgn 30

//Estruturas

typedef struct principal
{
    char nome[100];
    int id;
    float preco;
}games;

games jogo[max];

struct cadastro
{   
    //Variaveis de Informacoes Pessoais 
    char nome[50];
    char sobrenome[50];
    char cpf[50];
    char email[50];

    //Variaveis de Endereco
    char rua[100];
    char numero[100];
    char cep[15];
    
    //Variaveis de Login
    char busca[0];
    char senha [500];
    char pass[100];
    char usuario[100];

    //Variaveis de cartao
    char cartao[50];
    char titular[80];
    char cvv[10];
    char val[10]; 
};

struct cadastro user[50];
struct cadastro procurar;


//funções auxiliares

void limpabufer()
//Como o próprio nome já diz, ela tem como função limpar o bufer do teclado.
{
    int aux9;
    do
    {
        aux9 = fgetc(stdin);
    }
    while(aux9 != EOF && aux9 != '\n');
}

int search(char a[],char b[],char c[], char d[]) //Essa função recebe as strings de login e faz a comparação com os registros já cadastrados na estrutura.
{
    if(strcmp(a,b) == 0 && strcmp(c,d) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


void preencher(games *jogo)
{    
    jogo[0].id = 0; jogo[0].preco = 0; strcpy(jogo[0].nome, "");
    //posicao jogo[0] sera inutilizada
    jogo[1].id = 1; jogo[1].preco = 100; strcpy(jogo[1].nome, "Battlefield 1");
    jogo[2].id = 2; jogo[2].preco = 50;  strcpy(jogo[2].nome, "Battlefield 4");
    jogo[3].id = 3; jogo[3].preco = 100; strcpy(jogo[3].nome, "Dark Souls: Remastered"); 
    jogo[4].id = 4; jogo[4].preco = 80;  strcpy(jogo[4].nome, "Dark Souls 2: Scholar of the First Sin");
    jogo[5].id = 5; jogo[5].preco = 100; strcpy(jogo[5].nome, "Dark Souls 3");
    jogo[6].id = 6; jogo[6].preco = 200; strcpy(jogo[6].nome, "Red Dead Redemption 2");
    jogo[7].id = 7; jogo[7].preco = 200; strcpy(jogo[7].nome, "Call of Duty: Black Ops 4");
    //jogo[].id = ; jogo[].preco = ; strcpy(jogo[].nome, "");
}

void ver_jogos(games *jogo)
{
    int i, j, ids[max], auxi;
    float precos[max], auxf;
    char ordem_alfa[max][100]/*ira armazenar os nomes em ordem alfabetica*/, aux2[100];

    for (i=1; i<max; i++)
    {
        strcpy(ordem_alfa[i], jogo[i].nome);
        ids[i] = jogo[i].id;
        precos[i] = jogo[i].preco;
    }

    for (j=1; j<max; j++)
    {
        for (i=1; i<max; i++)
        { //iremos passar as informacoes de "games jogo" para vetores auxiliares
            if ((strcmp(ordem_alfa[i], ordem_alfa[i-1])) < 0)
            {
                strcpy(aux2, ordem_alfa[i-1]);
                strcpy(ordem_alfa[i-1], ordem_alfa[i]);
                strcpy(ordem_alfa[i], aux2);

                auxi = ids[i-1];
                ids[i-1] = ids[i];
                ids[i] = auxi;
                
                auxf = precos[i-1];
                precos[i-1] = precos[i];
                precos[i] = auxf;
            }    
        }
    }
        
    for (i=1; i<max; i++)
    {    
        printf("-----------------------------------------------------------------------\n");
        printf("--->\t%s. Preço: R$%.2f (id = %d)\n", ordem_alfa[i], precos[i], ids[i]);
    }
}

void adicionar_no_carrinho(float preco, float *pcarrinho) //Essa função é utilizada para adicionar jogos ao carrinho quando solicitado na funcao principal.
{
    *pcarrinho = *pcarrinho + preco;
}

void ver_carrinho(int jogos_no_carrinho[50][max], float valor_carrinho, games jogo[max], int usuario_logado)
{
    int i;
    printf("\nValor total do carrinho: %.2f\n", valor_carrinho);
    for (i = 0; i < max; i++)
    {
        if(jogos_no_carrinho[usuario_logado][i] != 0)
        {
            printf("%s == %d unidade(s)\n", jogo[i].nome, jogos_no_carrinho[usuario_logado][i]);
        }
    }
    printf("\n");    
}

void remover_carrinho(int jogos_no_carrinho[50][max], float *pcarrinho, games jogo[max], int usuario_logado)
{
	int i;
	char aux8;
	for (i = 0; i < max; i++)
	{
        if(jogos_no_carrinho[usuario_logado][i] != 0)
        {
            printf("\n%s == %d unidade(s)\n", jogo[i].nome, jogos_no_carrinho[usuario_logado][i]);
        	printf("Remover unidade? S/N: ");
        	scanf("%c", &aux8);
        	limpabufer();
	        if(aux8 == 'S' || aux8 == 's')
	        {
	        	jogos_no_carrinho[usuario_logado][i]--;
	        	*pcarrinho = *pcarrinho - jogo[i].preco;
	        	printf("Unidade removida com sucesso!\n");
	        }
        }
    }
}

void menu(char *op1, char *aux6)
{
    int aux1 = 1;
    char opax;
    printf("Menu de opções:\n");
    if(*aux6 == '1')
    {
        printf("Catálogo completo, digite 1.\nFazer logoff, digite 2.\nVer carrinho, digite 3.\n");
    }
    else
    {
        printf("Catálogo completo, digite 1.\nFazer login, digite 2.\nVer carrinho, digite 3.\n");   
    }

    printf("Digite a opção: ");

    do
    {
        scanf("%c", &opax);
        limpabufer();
        if(opax == '1' || opax == '2' || opax == '3')
        {
            aux1 = 0;
        }
        else
        {
            printf("Digite uma opção válida: ");
        	
        }
    }while(aux1 == 1);
    *op1 = opax;
}

int logar(struct cadastro *user) //Essa função armazena os dados do usuario no ato do login, ->
								//-> chama a função search para comparar com os dados que já estão registrados e inclui '*' na tela -> 
								//-> substituindo caracteres de senha que o usuário digitou.
{
    int i, lmt, aux5 = 1, y;
    char aux4;

    printf("\nLogin: ");
    //limpabufer();
    fgets(procurar.busca, 30, stdin);
    //limpabufer();
    printf("Senha: ");
    fgets(procurar.pass, 100, stdin);
    //limpabufer();
    
    lmt = strlen(procurar.pass)-1;
    system("clear");
    printf("Login: %s", procurar.busca);
    printf("Senha: ");
     
    for(i=0;i<lmt;i++)
    {
        putchar('*');
    }
    printf("\n");

    for(i = 0; i < 50; i++)
    {
    	y = search(procurar.busca, user[i].usuario, procurar.pass, user[i].senha);
	    if(y == 1)
	    {
	    	printf("\nLogin efetuado com sucesso!\n\n");
	    	break;
		}
	}

	if(y != 1)
	{
		printf("\nLogin ou senha incorreto(s). Tentar novamente? S/N: ");
		do{
			scanf("%c", &aux4);
			limpabufer();
			if(aux4 == 'S' || aux4 == 's')
			{
				logar(user);
				system("clear");
			}
			else if(aux4 == 'N' || aux4 == 'n')
			{
				system("clear");
				return -1;
			}
			else{
				printf("Digite uma opção válida: ");
			}
		}while(aux4 != 'S' && aux4 != 's' && aux4 != 'N' && aux4 != 'n');
	}
	else{
		return i;
		system("clear");
	}
}

void registro(int usuario_atual, struct cadastro *user)//Essa função armazena os dados do usuário em seus respectivos campos ->
													  //-> da estrutura. 
{
	int i = usuario_atual;

    printf("\nNome: ");
    fgets(user[i].nome,30,stdin);
    printf("Sobrenome: ");
    fgets(user[i].sobrenome,30,stdin);
    printf("Endereço de e-mail: ");
    fgets(user[i].email,50,stdin);
    printf("CPF: ");
    fgets(user[i].cpf,50,stdin);
    printf("Rua: ");
    fgets(user[i].rua,100,stdin);
    printf("Número: ");
    fgets(user[i].numero,10,stdin);
    printf("CEP: ");
    fgets(user[i].cep,15,stdin);
    printf("login: ");
    fgets(user[i].usuario,50,stdin);
    printf("Senha: ");
    fgets(user[i].senha,100,stdin);
}

int pagamento(struct cadastro *user, int usuario_logado)
{
	int i = usuario_logado;
	char op3, op4;
	printf("Numero do cartao: \n");
	fgets(user[i].cartao, 17, stdin);
	if(user[i].cartao[0]=='5' && user[i].cartao[1]<='9'){
        printf("Bandeira: Mastercard\n");
    }else if(user[i].cartao=='4' && user[i].cartao[1]<='9'){
        printf("Bandeira: Visa\n");
    }else if(user[i].cartao[0]=='3' && user[i].cartao[1]<='7'){
        printf("Bandeira: American Express\n");   
    }else{
        printf("Bandeira do cartao nao reconhecida. Fique tranquilo(a), voce podera prosseguir para compra.\n");
    }
	printf("Nome do titular: \n");
	fgets(user[i].titular, 12, stdin);
	printf("Validade: \n");
	fgets(user[i].val, 8, stdin);
	printf("Codigo de seguranca: \n");
	fgets(user[i].cvv, 4, stdin);
	limpabufer();
	
	printf("Confirmar compra? S/N: ");
	do{
		scanf("%c", &op3);
		limpabufer();
		if(op3 == 'N' || op3 == 'n'){
			return 0;
		}
		else if(op3 == 'S' || op3 == 's')
		{
			system("clear");
			printf("\nCompra realizada com sucesso! Mais informações serão enviadas ao e-mail do comprador.\n");
			return 1;
		}
		else{
			printf("Digite uma opção válida: ");
		}
	}while(op3 != 'N' && op3 != 'n' && op3 != 'S' && op3 != 's');
}

int main()
{
    //para iniciar o codigo, abaixo temos as declaracoes das variaveis:
    //todas as variaveis usadas para selecionar uma opcao serao chamadas de "op", e as auxiliares de "aux"
    int i, j, aux7, usuario_logado = -1, usuario_atual = 0, novo_usuario = 0, flag = 1, flag2 = 1, id_escolhido = 0;
    char op1, op2, aux2, aux3, aux6 = '0';
    float valor_carrinho[50];
    int jogos_no_carrinho[50][max];//vetor que armazena as unidades de cada jogo no carrinho
    
    for(i=0; i<50; i++)//zerando o valor de todos os carrinhos
    {
    	valor_carrinho[i] = 0;
        for(j=0; j<max; j++)
        {
        	jogos_no_carrinho[i][j] = 0;
    	}
    }

    preencher(jogo);

    printf("\nOlá, seja bem-vindo(a) à loja de jogos xxxx, desenvolvida por Lucas Duarte Bisoffi e Nathan Ferreira Nunes.\n");
    do
    {
        menu(&op1, &aux6); //A chamada dessa função nos permite visualizar o menu na tela.
        system("clear");
        switch(op1)
        {
            case '1': 
                do{
                    ver_jogos(jogo); //Caso seja escolhida a primeira opção, essa função irá preencher a tela com os jogos disponíveis.
                    if(aux6 == '0')
                    {
                        printf("\nFaça login para adicionar jogos ao carrinho.\n\n");
                   		printf("Digite 0 para voltar ao menu ou 1 para encerrar o programa: ");
                   		do{	
                   			scanf("%c", &aux3);
                   			limpabufer();
	                   		if(aux3 == '0')
	                   		{
	                   			flag2 = 0;
	                   			system("clear");
	                   			break;
	                   		}
	                   		else if(aux3 == '1')
	                   		{
	                   			return 0;
	                   		}
	                   		else{
	                   			printf("Digite uma opção válida!\n");
	                   		}
	                   	}while(aux3 != '0' && aux3 != '1');	
                   	}
	                else
	                {
	                    printf("\nCaso deseje adicionar algum jogo ao carrinho, digite seu respectivo id. Caso deseje sair do catálogo, digite 0: ");
	                    scanf("%d", &id_escolhido);
	                    limpabufer();
	                    if(id_escolhido == 0)
	                    {
	                        flag2 = 0;
	                        system("clear");
	                    }
	                    else
	                    {
	                        system("clear");
	                        printf("\nAdicionar %s, cujo valor é de %.2f, ao seu carrinho?\n", jogo[id_escolhido].nome, jogo[id_escolhido].preco);
	                        printf("S/N: ");
	                        scanf("%c", &aux2);
	                        limpabufer();
	                        if(aux2 == 'S' || aux2 == 's')
	                        {
	                        	adicionar_no_carrinho(jogo[id_escolhido].preco, &valor_carrinho[usuario_logado]);
	                        	jogos_no_carrinho[usuario_logado][id_escolhido]++;
	                 	  		printf("Jogo adicionado com sucesso!\n\n");
	                        }
	                        else
	                        {
	                            printf("Jogo não adicionado.\n\n");
	                        }
	                    }
	                }
                }while(flag2 == 1);
                break;
            case '2':
            	if(aux6 == '0')
            	{
		            printf("Digite 1 para fazer login\nDigite 2 se voce for um novo usuario.\n");
		            do
		            {    
			            printf("Opção: ");
			            scanf("%c", &op2);
		                limpabufer();
		                switch(op2)
		                {
		                    case '1':
		                    	aux7 = logar(user);
	                       		if(aux7 != -1)
		                    	{
			                    	usuario_logado = aux7;
			                   		aux6 = '1';
			                	}		     
			                	break;
			                case '2':
			                 	registro(novo_usuario, user);
			                    printf("\nRegistro efetuado com sucesso!\nFaça seu login abaixo:\n");
			                    novo_usuario++;
			                    aux7 = logar(user);
		                        if(aux7 != -1)
		                        {
			                    	usuario_logado = aux7;
			                       	aux6 = '1';
			                    }
			                    break;
			                default:
			                    break;
			            }
		            }while(op2 != '1' && op2 != '2');
		        }
		        else
		        {
		        	aux6 = '0';
		           	usuario_logado = -1;
		        }
	           	break;
            case '3':
            	if(aux6 == '0')
            	{
            		printf("Não há usuário logado!\n\n");
            	}
            	else
            	{
                	ver_carrinho(jogos_no_carrinho, valor_carrinho[usuario_logado], jogo, usuario_logado);
                	if(valor_carrinho[usuario_logado] != 0)
                	{
	                	printf("\nDeseja remover algum item do carrinho? S/N: ");
		                scanf("%c", &aux2);
		                limpabufer();
		                if(aux2 == 'S' || aux2 == 's')
		                {
		                	remover_carrinho(jogos_no_carrinho, &valor_carrinho[usuario_logado], jogo, usuario_logado);
	                		printf("\n");
	                	}
	                	printf("Deseja realizar a compra? S/N: ");
	                	scanf("%c", &aux2);
		                limpabufer();
		                if(aux2 == 'S' || aux2 == 's')
		                {
		                	if(pagamento(user, usuario_logado))
		                	{
		                		printf("\nDigite 0 para voltar ao menu ou 1 para encerrar o programa: ");
		                   		do{	
		                   			scanf("%c", &aux3);
		                   			limpabufer();
			                   		if(aux3 == '0')
			                   		{
			                   			flag2 = 0;
			                   			system("clear");
			                   			for(i=0; i<max; i++)
									    {
									        jogos_no_carrinho[usuario_logado][i] = 0;
									        valor_carrinho[usuario_logado] = 0;	
									    }
			                   			break;
			                   		}
			                   		else if(aux3 == '1')
			                   		{
			                   			return 0;
			                   		}
			                   		else{
			                   			printf("Digite uma opção válida!\n");
			                   		}
			                   	}while(aux3 != '0' && aux3 != '1');
		                	}
		                }
	                }	
                break;
            default: 
               	printf("sei la\n");
                break;
            }
    	}    
    }while(flag==1);

    return 0;
}