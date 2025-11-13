#include <stdio.h>
#include <stdlib.h>
#include "sistema.h"
#include <ctype.h>
#include <string.h>

void dados_veiculo()
{
    int opcao_final;
    
    do {
        FILE *veiculos = fopen("veiculos.bin","ab");
        
        if(veiculos == NULL){
            printf("❌ Erro ao abrir arquivo de veiculos!\n");
            return;
        }
        
        Veiculo novo_veiculo;
        memset(&novo_veiculo, 0, sizeof(Veiculo));
        system("clear");
        printf("=== DADOS DO VEICULO ===\n\n");
        
        //========================================================
        printf("Placa (7 caracteres, ex: ABC1D23): ");
        
        int placa_duplicada, placa_valida;
        do 
        {
            placa_duplicada = 0;
            placa_valida = 0;
            
            scanf("%7s", novo_veiculo.placa);
            while (getchar() != '\n');
            
            for(int i = 0; novo_veiculo.placa[i]; i++){
                novo_veiculo.placa[i] = toupper(novo_veiculo.placa[i]);
            }
            
            if(!validarPlaca(novo_veiculo.placa)){
                printf("Placa invalida! Use 7 caracteres (ex: ABC1D23): ");
            }
            
            placa_valida = 1;
            
            FILE *veiculos_leitura = fopen("veiculos.bin", "rb");
            if(veiculos_leitura != NULL)
            {
                Veiculo veiculo_existente;
                while(fread(&veiculo_existente, sizeof(Veiculo), 1, veiculos_leitura)){
                    if(strcmp(veiculo_existente.placa, novo_veiculo.placa) == 0){
                        placa_duplicada = 1;
                        break;
                    }
                }
                fclose(veiculos_leitura);
            }
            
            if(placa_duplicada)
            {
                printf("❌ Placa ja cadastrada! Digite uma placa diferente: ");
            }
        }while(placa_duplicada || !placa_valida);
        
        //========================================================
        printf("\nMarca (ate 30 caracteres): ");
        scanf(" %[^\n]", novo_veiculo.marca);
        for(int i = 0; novo_veiculo.marca[i]; i++){
            novo_veiculo.marca[i] = toupper(novo_veiculo.marca[i]);
        }
        
        //========================================================
        printf("\nModelo (ate 50 caracteres): ");
        scanf(" %[^\n]", novo_veiculo.modelo);
        
        //========================================================
        printf("\nCategoria CNH (A, B, C, D, E, AB): ");
        do 
        {
            scanf("%2s", novo_veiculo.categoria_cnh);
            for (int i = 0; novo_veiculo.categoria_cnh[i]; i++){
                novo_veiculo.categoria_cnh[i] = toupper(novo_veiculo.categoria_cnh[i]);
            }
            if(!validarCategoriaCNH(novo_veiculo.categoria_cnh)){
                printf("Categoria inválida! Digite (A, B, C, D, E, AB): ");
            }
        }while(!validarCategoriaCNH(novo_veiculo.categoria_cnh));
        
        //========================================================
        printf("\nValor da diaria (ex: 150.00): ");
        do 
        {
            if(scanf("%f", &novo_veiculo.valor_diaria) != 1){
                printf("Erro na leitura. Digite um valor valido (ex: 150.00): ");
                while (getchar() != '\n');
                continue;
            }
            if(novo_veiculo.valor_diaria <= 0){
                printf("Valor deve ser maior que zero! Digite novamente: ");
            }
        }while(novo_veiculo.valor_diaria <= 0);
        
        //========================================================
        
        novo_veiculo.ativo = 1;
        
        fwrite(&novo_veiculo, sizeof(Veiculo), 1, veiculos);
        fclose(veiculos);
        
        system("clear");
        printf("\n✅ Veiculo cadastrado com sucesso!\n\n");
        
        printf("1 - Cadastrar novo veiculo\n2 - Voltar\n\n");
        printf("Selecione a opcao: ");
        scanf("%d", &opcao_final);
        
        while (getchar() != '\n');
        
        if (opcao_final != 1) {
            return;
        }
    }while(opcao_final == 1);
}
