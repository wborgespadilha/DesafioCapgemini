#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <locale.h>

int i,opcao,funcao;
char senha[128] = " ";
char palavra[128];
char matriz[2048][256];

int main(int argc, char *argv[]) 
{
	setlocale(LC_ALL, "Portuguese");//habilita a acentuação para o português
	do
	{
		printf("Insira 1 para teste manual, 2 para teste unitário ou 3 para sair.\n");
		scanf("%d",&opcao);
		
		if(opcao == 1)//TESTE MANUAL
		{
			printf("Insira um número inteiro\n");
			scanf("%d",&i);
			
			DesenharEscada(i);
			
			printf("Insira a sua senha\n");
			scanf("%s",&senha);
			
			printf("\n");
			
			funcao = VerificarSenha(senha);
			if(funcao == 0)
			{
				printf("Não é necessário adicionar mais caracteres na senha\n");
			}
			else if(funcao == 1)
			{
				printf("É necessário adicionar mais 1 caractere na senha\n");
			}
			else
			{
				printf("É necessário adicionar mais %d caracteres na senha\n",funcao);
			}
	
			printf("\n");
			printf("Insira uma palavra\n");
			scanf("%s",palavra);
			printf("\n");
			
			funcao = VerificarAnagramasPares(palavra);
			if (funcao == 0)
			{
				printf("A palavra não possui pares de substrings que são anagramas\n");
			}
			else if(funcao == 1)
			{
				printf("A palavra possui 1 par de substrings que são anagramas\n");
			}
			else
			{
				printf("A palavra possui %d pares de substrings que são anagramas\n",funcao);
			}
	
			printf("\n\n");
		}
		else if(opcao == 2)//TESTE UNITARIO
		{
			printf(" ");
			
			srand ( time(NULL) );//seta a seed
			i = rand() % 60;//sorteia o número
			
			printf("Número sorteado: %i\n",i);
			
			DesenharEscada(i);
			
			char caracteres[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%&*()^-+";//bug conhecido: as vezes a senha é gerada com um caractere especial que não está aqui. faz sentido? não.
			
			srand( time(NULL) );//seta a seed
			int tamanho = rand() % 10;//sorteia o numero
			int q;
			
			for(q = 0;q<= tamanho;q++)
			{
				srand( rand() );//seta a seed
				int p = rand() % 73;//sorteia o numero
				
				char aux[128];
				strncpy(aux, caracteres + p, 1);//copia o caractere correspondente ao numero sorteado
				strcat(senha,aux);//coloca o caractere na senha
				memset(aux, 0, strlen(aux));//limpa o auxiliar
			}
			
			printf("Senha gerada: %s\n",senha);
			
	
			funcao = VerificarSenha(senha);
			if(funcao == 0)
			{
				printf("Não é necessário adicionar mais caracteres na senha\n\n");
			}
			else if(funcao == 1)
			{
				printf("É necessário adicionar mais 1 caractere na senha\n\n");
			}
			else
			{
				printf("É necessário adicionar mais %d caracteres na senha\n\n",funcao);
			}
			
			memset(senha, 0, strlen(senha));//limpa a senha para caso a próxima execução também seja teste unitário
			
			
			char caracteres2[26] = "abcdefghijklmnopqrstuvwxyz";
			
			srand (time(NULL));//sorteia a seed
			tamanho = rand() % 10;//sorteia o numero
			
			for(q = 0;q< tamanho;q++)
			{
				srand ( rand() );//seta a seed
				int p = rand() % 25;//sorteia o numero
				char aux[128];
				strncpy(aux, caracteres2 + p, 1);//copia o caractere correspondente ao numero sorteado
				strcat(palavra,aux);//coloca o caractere na senha
				memset(aux, 0, strlen(aux));//limpa o auxiliar
			}
			
			printf("Palavra gerada: %s\n\n",palavra);
			
			funcao = VerificarAnagramasPares(palavra);
			if (funcao == 0)
			{
				printf("A palavra não possui pares de substrings que são anagramas\n");
			}
			else if(funcao == 1)
			{
				printf("A palavra possui 1 par de substrings que são anagramas\n");
			}
			else
			{
				printf("A palavra possui %d pares de substrings que são anagramas\n",funcao);
			}
			
			memset(palavra, 0, strlen(palavra));//limpa a palavra para caso a próxima execução também seja teste unitário
			
			
			printf("\n\n");
		}
			
	}	
	while(opcao != 3);
	
	return 0;
}

int DesenharEscada(int i)
{
	int x,y,z;
	
	printf("\n");
	
	for(x = 1; x <= i; x++)//percorre as linhas até que o número da linha seja igual ao número digitado
	{
		for(y = 0; y < (i-x); y++)//printa os espaços igual ao numero digitado menos o número da linha atual
		{
			printf(" ");
		}
		for(z = 1; z <= x; z++)//printa a quantidade de  * igual ao número da linha
		{
			printf("*");
		}
		printf("\n");
	}
	
	printf("\n");
	return 0;
}

int VerificarSenha(char senha[])
{
	int f = 0;
	int g;
	
	g = VerificarMaisculas(senha);
	
	printf("Maiúsculos: %i\n",g);
	
	if (g == 0)//primeira verificação, se há letras maiúsculas
	{
		f ++;
	}
	
	g = VerificarMinusculas(senha);

	printf("Minúsculos: %i\n",g);

	if (g == 0)//verifica se há letras minúsculas
	{
		f ++;
	}
	
	g = VerificarCaracteres(senha);
	
	printf("CaracteresEspeciais: %i\n",g);
	
	if (g == 0)//verifica se há caracteres especiais
	{
		f ++;
	}
	
	g = VerificarDigitos(senha);
	
	printf("Dígitos: %i\n",g);
	
	if (g == 0)//verifica se há digitos
	{
		f ++;
	}
	
	g = strlen(senha);
	
	printf("Tamanho da senha: %i\n\n",g);
	
	while( (g + f) < 6)//se o número de caracteres mais o numero de caracteres a ser adicionados não bater 6, adicionar 1 no a ser adicionado
	{
		f++;
	}
	
	
	return f;
}

int VerificarMaisculas(char senha[])
{
	int k = 0;
	int j;
	
	for(j = 0; j < strlen(senha); j++)// percorre toda a extensão do array
	{
		if (senha[j] == 'A')//verificação termo a termo
		{
			k ++;
		}
		if (senha[j] == 'B')
		{
			k ++;
		}
		if (senha[j] == 'C')
		{
			k ++;
		}
		if (senha[j] == 'D')
		{
			k ++;
		}
		if (senha[j] == 'E')
		{
			k ++;
		}
		if (senha[j] == 'F')
		{
			k ++;
		}
		if (senha[j] == 'G')
		{
			k ++;
		}
		if (senha[j] == 'H')
		{
			k ++;
		}
		if (senha[j] == 'I')
		{
			k ++;
		}
		if (senha[j] == 'J')
		{
			k ++;
		}
		if (senha[j] == 'K')
		{
			k ++;
		}
		if (senha[j] == 'L')
		{
			k ++;
		}
		if (senha[j] == 'M')
		{
			k ++;
		}
		if (senha[j] == 'N')
		{
			k ++;
		}
		if (senha[j] == 'O')
		{
			k ++;
		}
		if (senha[j] == 'P')
		{
			k ++;
		}
		if (senha[j] == 'Q')
		{
			k ++;
		}
		if (senha[j] == 'R')
		{
			k ++;
		}
		if (senha[j] == 'S')
		{
			k ++;
		}
		if (senha[j] == 'T')
		{
			k ++;
		}
		if (senha[j] == 'Y')
		{
			k ++;
		}
		if (senha[j] == 'V')
		{
			k ++;
		}
		if (senha[j] == 'W')
		{
			k ++;
		}
		if (senha[j] == 'X')
		{
			k ++;
		}
		if (senha[j] == 'Y')
		{
			k ++;
		}
		if (senha[j] == 'Z')
		{
			k ++;
		}
	}
	return k;//retorna o número de letras maiúsculas
}

int VerificarMinusculas(char senha[])
{
	int k = 0;
	int j;
	
	for(j = 0; j < sizeof(senha); j++)// percorre toda a extensão do array
	{
		if (senha[j] == 'a')//verificação termo a termo
		{
			k ++;
		}
		if (senha[j] == 'b')
		{
			k ++;
		}
		if (senha[j] == 'c')
		{
			k ++;
		}
		if (senha[j] == 'd')
		{
			k ++;
		}
		if (senha[j] == 'e')
		{
			k ++;
		}
		if (senha[j] == 'f')
		{
			k ++;
		}
		if (senha[j] == 'g')
		{
			k ++;
		}
		if (senha[j] == 'h')
		{
			k ++;
		}
		if (senha[j] == 'i')
		{
			k ++;
		}
		if (senha[j] == 'j')
		{
			k ++;
		}
		if (senha[j] == 'k')
		{
			k ++;
		}
		if (senha[j] == 'l')
		{
			k ++;
		}
		if (senha[j] == 'm')
		{
			k ++;
		}
		if (senha[j] == 'n')
		{
			k ++;
		}
		if (senha[j] == 'o')
		{
			k ++;
		}
		if (senha[j] == 'p')
		{
			k ++;
		}
		if (senha[j] == 'q')
		{
			k ++;
		}
		if (senha[j] == 'r')
		{
			k ++;
		}
		if (senha[j] == 's')
		{
			k ++;
		}
		if (senha[j] == 't')
		{
			k ++;
		}
		if (senha[j] == 'u')
		{
			k ++;
		}
		if (senha[j] == 'v')
		{
			k ++;
		}
		if (senha[j] == 'w')
		{
			k ++;
		}
		if (senha[j] == 'x')
		{
			k ++;
		}
		if (senha[j] == 'y')
		{
			k ++;
		}
		if (senha[j] == 'z')
		{
			k ++;
		}
	}
	return k;//retorna o número de letras minúsculas
}

int VerificarDigitos(char senha[])
{
	int k = 0;
	int j;
	
	for(j = 0; j < sizeof(senha); j++)// percorre toda a extensão do array
	{
		if (senha[j] == '0')//verificação termo a termo
		{
			k ++;
		}
		if (senha[j] == '1')
		{
			k ++;
		}
		if (senha[j] == '2')
		{
			k ++;
		}
		if (senha[j] == '3')
		{
			k ++;
		}
		if (senha[j] == '4')
		{
			k ++;
		}
		if (senha[j] == '5')
		{
			k ++;
		}
		if (senha[j] == '6')
		{
			k ++;
		}
		if (senha[j] == '7')
		{
			k ++;
		}
		if (senha[j] == '8')
		{
			k ++;
		}
		if (senha[j] == '9')
		{
			k ++;
		}
	}
	return k;//retorna o número de dígitos
}

int VerificarCaracteres(char senha[])
{
	int k = 0;
	int j;
	
	for(j = 0; j < sizeof(senha); j++)// percorre toda a extensão do array
	{
		if (senha[j] == '!')//verificação termo a termo
		{
			k ++;
		}
		if (senha[j] == '@')
		{
			k ++;
		}
		if (senha[j] == '#')
		{
			k ++;
		}
		if (senha[j] == '$')
		{
			k ++;
		}
		if (senha[j] == '%')
		{
			k ++;
		}
		if (senha[j] == '^')
		{
			k ++;
		}
		if (senha[j] == '&')
		{
			k ++;
		}
		if (senha[j] == '*')
		{
			k ++;
		}
		if (senha[j] == '(')
		{
			k ++;
		}
		if (senha[j] == ')')
		{
			k ++;
		}
		if (senha[j] == '+')
		{
			k ++;
		}
		if (senha[j] == '-')
		{
			k ++;
		}
	}
	return k;//retorna o número de caracteres especiais
}

int VerificarAnagramasPares(char palavra[])
{
	int i,j,x,z,total;
	char str[256] = " ",str2[256] = " ";
	int len = strlen(palavra)/2;
	int p = 0;
	
	//printf("len: %i\n",len); //debug

	//PRIMEIRA METADE
	for(x = 0; x <= len; x++)//pegará substrings cada vez maiores, até o limite de tamaho = metade da palavra arredendado pra baixo
	{
		//printf("-----x: %d------\n",x); //debug
		for(i = 0; i < strlen(palavra); i++)//verificará o conteudo de cada string
		{
			memcpy(str,&palavra[i],x + 1);//pega a substring
			//printf("i(%d): %s\n",x+1,str); //debug
				
			for(j = 0; j < strlen(palavra); j++)//com o conteúdo das outras strings
			{
					
				memcpy(str2,&palavra[j],x + 1);//x + i seleciona o tamanho da substring
				//printf(" j: %s\n",str2); //debug
					
				if(i != j)//exceto na mesma posição
				{
					if(VerificarAnagrama(str,str2) == 1)
					{
						strcpy(matriz[p],str);
						//printf("passado: %s,%s\n",str,str2); //debug
						p++;
					}
				}
			}
		}
	}

	return ProcessarPares();
}

int VerificarAnagrama(char str[], char str2[])
{
	int i,j;
	char aux;

	//bubble sort no conteúdo das strings 
	
	for(i = 0; i < strlen(str); i ++)
	{
		for(j = 0; j < strlen(str);j++)
		{
			if(str[j] > str[i])
			{
				aux = str[i];
				
				str[i] = str[j];
				str[j] = aux;
			}
		}
	}
	for(i = 0; i < strlen(str2); i ++)
	{
		for(j = 0; j < strlen(str2);j++)
		{
			if(str2[j] > str2[i])
			{
				aux = str2[i];
				
				str2[i] = str2[j];
				str2[j] = aux;
			}
		}
	}
	//como estão perfeitamente ordenadas, basta comparar diretamente
	if(strcmp(str,str2) == 0)
	{
		return 1;
	}
	
	return 0;
}

int ProcessarPares()
{
	int x,i,j;
	char vetor[256];
	char vetor2[256];
	char aux;
	int total = 0;
	
	for(x = 0; x < 2048;x++)//pega cada string da matriz
	{
		strcpy(vetor, matriz[x]);
		if(strlen(vetor)!=0)
		{
			//vetor[x] = BubbleSort(vetor[256]);
			//bubble sort no conteúdo da matriz
			
			for(i = 0; i < 256; i ++)
			{
				for(j = 0; j < 256;j++)
				{
					if(vetor[j] > vetor[i])
					{
						aux = vetor[i];
						
						vetor[i] = vetor[j];
						vetor[j] = aux;
					}
				}
			}
			strcpy(matriz[x],vetor);
		}
	}
	
	
	for(x = 0; x < 2048;x++)//pega cada string da matriz
	{
		strcpy(vetor,matriz[x]);
		for(i = 0; i < 2048; i ++)//e compara com todas as outras
		{
			strcpy(vetor2,matriz[i]);
			if((strlen(vetor)!=0) && (strlen(vetor2)!=0))//se não forem string vazias
			{
				if(x != i)//e não forem iguais continua
				{
					if(strcmp(vetor,vetor2) == 1)
					{
						total++;
						memset(matriz[x],0,256);//remove o par para não ler eles novamente
						memset(matriz[i],0,256);
					}
				}
			}
		}
	}
	return total;
}
