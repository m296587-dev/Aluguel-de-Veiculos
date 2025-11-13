#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sistema.h"
#include <ctype.h>

void atualizar_cliente(char cpf_busca[12], long posicao)
{
    system("clear");
    printf("╔════════════════════════════════════════╗\n");
    printf("║           ATUALIZAR CLIENTE            ║\n");
    printf("╚════════════════════════════════════════╝\n\n");
    
    Cliente cliente;
    FILE *arquivo = fopen("clientes.bin", "rb");
    if(arquivo == NULL)
    {
        printf("❌ Erro ao abrir arquivo!\n\n");
        printf("Pressione Enter para voltar...");
        getchar(); getchar();
        return;
    }
    
    fseek(arquivo, posicao, SEEK_SET);
    fread(&cliente, sizeof(Cliente), 1, arquivo);
    fclose(arquivo);
    
    printf("Deixe em branco (Enter) para manter o valor atual.\n\n");
    
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    
    printf("Nome atual: %s\n", cliente.nome);
    printf("Novo nome: ");
    char novo_nome[100];
    fgets(novo_nome, sizeof(novo_nome), stdin);
    novo_nome[strcspn(novo_nome, "\n")] = 0;
    if(strlen(novo_nome) > 0)
    {
        strcpy(cliente.nome, novo_nome);
    }
    
    printf("\nCNH atual: %s\n", cliente.CNH);
    printf("Nova CNH: ");
    char nova_cnh[12];
    fgets(nova_cnh, sizeof(nova_cnh), stdin);
    nova_cnh[strcspn(nova_cnh, "\n")] = 0;
    if(strlen(nova_cnh) > 0) {
        strcpy(cliente.CNH, nova_cnh);
    }
    
    printf("\nCategoria CNH atual: %s\n", cliente.categoria_cnh);
    printf("Nova categoria CNH: ");
    char nova_categoria[3];
    fgets(nova_categoria, sizeof(nova_categoria), stdin);
    nova_categoria[strcspn(nova_categoria, "\n")] = 0;
    if(strlen(nova_categoria) > 0) {
        for(int i = 0; nova_categoria[i]; i++) {
            nova_categoria[i] = toupper(nova_categoria[i]);
        }
        if(validarCategoriaCNH(nova_categoria)) {
            strcpy(cliente.categoria_cnh, nova_categoria);
        }
    }
    
    printf("\nTelefone atual: %lld\n", cliente.telefone);
    printf("Novo telefone: ");
    char telefone_str[20];
    fgets(telefone_str, sizeof(telefone_str), stdin);
    telefone_str[strcspn(telefone_str, "\n")] = 0;
    if(strlen(telefone_str) > 0)
    {
        long long novo_telefone;
        if(sscanf(telefone_str, "%lld", &novo_telefone) == 1)
        {
            cliente.telefone = novo_telefone;
        }
    }
    arquivo = fopen("clientes.bin", "r+b");
    if(arquivo != NULL)
    {
        fseek(arquivo, posicao, SEEK_SET);
        fwrite(&cliente, sizeof(Cliente), 1, arquivo);
        fclose(arquivo);
        printf("\n✅ Cliente atualizado com sucesso!\n");
    } else {
        printf("\n❌ Erro ao salvar alteracoes!\n");
    }
    
    printf("Pressione Enter para continuar...");
    getchar();
}
