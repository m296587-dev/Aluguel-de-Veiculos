#include <stdio.h>
#include <stdlib.h>
#include "sistema.h"
#include <ctype.h>
#include <string.h>

void dados_cliente()
{
    int opcao_final;
    
    do {
        FILE *clientes = fopen("clientes.bin","ab");
        
        if(clientes == NULL){
            printf("❌ Erro ao abrir arquivo de clientes!\n");
            return;
        }
        
        Cliente novo_cliente;
        memset(&novo_cliente, 0, sizeof(Cliente));
        system("clear");
        printf("=== DADOS PESSOAIS ===\n\n");
        
        
        printf("Nome completo: ");
        scanf(" %[^\n]", novo_cliente.nome);
        
        //========================================================
        printf("\nCPF (11 digitos): ");
        char cpf_temp[12];
        int cpf_duplicado, cpf_valido;
        
        do {
            cpf_duplicado = 0;
            cpf_valido = 0;
            
            scanf("%11s", cpf_temp);
            while (getchar() != '\n');
    
            if(strlen(cpf_temp) != 11)
            {
                printf("CPF deve ter exatamente 11 digitos! Digite novamente: ");
                continue;
            }
    
            int apenas_numeros = 1;
            for(int i = 0; i < 11; i++){
                if(!isdigit(cpf_temp[i]))
                {
                    apenas_numeros = 0;
                    break;
                }
            }
    
            if(!apenas_numeros)
            {
                printf("CPF deve conter apenas numeros! Digite novamente: ");
                continue;
            }
    
            if(!validarCPF(cpf_temp))
            {
                printf("CPF invalido! Digite novamente: ");
            } else {
                cpf_valido = 1;
                strcpy(novo_cliente.CPF, cpf_temp);
            }
            
            if(cpf_valido)
            {
                FILE *clientes_leitura = fopen("clientes.bin", "rb");
                if(clientes_leitura != NULL)
                {
                    Cliente cliente_existente;
                    while(fread(&cliente_existente, sizeof(Cliente), 1, clientes_leitura)){
                        if(strcmp(cliente_existente.CPF, novo_cliente.CPF) == 0)
                        {
                            cpf_duplicado = 1;
                            break;
                        }
                    }
                    fclose(clientes_leitura);
                }
                
                if(cpf_duplicado)
                {
                    printf("❌ CPF ja cadastrado! Digite um CPF diferente: ");
                }
            }
            
        } while(cpf_duplicado || !cpf_valido);

        //========================================================
        printf("\nCNH (11 digitos): ");
        char cnh_temp[12];
        do {
            scanf("%11s", cnh_temp);
            while (getchar() != '\n');
    
            if(strlen(cnh_temp) != 11)
            {
                printf("CNH deve ter exatamente 11 digitos! Digite novamente: ");
                continue;
            }
    
            int apenas_numeros = 1;
            for(int i = 0; i < 11; i++){
                if(!isdigit(cnh_temp[i])){
                    apenas_numeros = 0;
                    break;
                }
            }
    
            if(!apenas_numeros){
                printf("CNH deve conter apenas numeros! Digite novamente: ");
                continue;
            }
    
                if(!validarCNH(cnh_temp))
                {
                    printf("CNH invalida! Digite novamente: ");
                } else {
                    strcpy(novo_cliente.CNH, cnh_temp);
                }
        } while(!validarCNH(cnh_temp));

        //=========================================================
        printf("\nCategoria CNH (A, B, C, D, E, AB): ");
        do 
        {
            scanf("%2s", novo_cliente.categoria_cnh);
            for (int i = 0; novo_cliente.categoria_cnh[i]; i++){
                novo_cliente.categoria_cnh[i] = toupper(novo_cliente.categoria_cnh[i]);
            }
            if(!validarCategoriaCNH(novo_cliente.categoria_cnh)){
                printf("Categoria invalida! Digite (A, B, C, D, E, AB): ");
            }
        }while(!validarCategoriaCNH(novo_cliente.categoria_cnh));
        
        //==========================================================
        printf("\nTelefone (apenas numeros): ");
        scanf("%lld", &novo_cliente.telefone);
        while (getchar() != '\n'); 
        
        //==========================================================
        
        novo_cliente.ativo = 1;

        fwrite(&novo_cliente, sizeof(Cliente), 1, clientes);
        fclose(clientes);
        
        system("clear");
        printf("\n✅ Cliente cadastrado com sucesso!\n\n");
        
        printf("1 - Cadastrar novo cliente\n2 - Voltar\n\n");
        printf("\nSelecione a opcao: ");
        scanf("%d", &opcao_final);
        
        while (getchar() != '\n');
        
        if (opcao_final != 1) {
            return;
        }
    }while(opcao_final == 1);
}
