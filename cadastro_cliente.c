#include <stdio.h>
#include <stdlib.h>
#include "sistema.h"

void cadastro_cliente()
{
    system("clear");
    printf("╔════════════════════════════════════════╗\n");
    printf("║         CADASTRO DE CLIENTE            ║\n");
    printf("╚════════════════════════════════════════╝\n\n");
    printf("Preencha os dados abaixo:\n");
    printf("• Todos os campos sao obrigatorios\n");
    printf("• Use CPF apenas numeros (11 digitos)\n");
    printf("• CNH apenas numeros\n\n");
    printf("Pressione Enter para comecar...");
    getchar(); 
    getchar();
    
    dados_cliente();
}
