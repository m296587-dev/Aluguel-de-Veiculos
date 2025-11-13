#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "sistema.h"

void excluir_veiculo(char placa[8], long posicao) {
    system("clear");
    printf("╔════════════════════════════════════════╗\n");
    printf("║           EXCLUIR VEICULO              ║\n");
    printf("╚════════════════════════════════════════╝\n\n");
    
    FILE *arquivo_veiculos = fopen("veiculos.bin", "r+b");
    if(arquivo_veiculos == NULL)
    {
        printf("❌ Erro ao abrir arquivo de veiculos!\n");
        printf("Pressione Enter para voltar...");
        getchar(); 
        getchar();
        return;
    }
    
    Veiculo veiculo;
    fseek(arquivo_veiculos, posicao, SEEK_SET);
    fread(&veiculo, sizeof(Veiculo), 1, arquivo_veiculos);
    
    printf("Veiculo: %s %s\n", veiculo.marca, veiculo.modelo);
    printf("Placa: %s\n\n", veiculo.placa);
    
    if(veiculo.alugado)
    {
        printf("❌ Nao e possivel excluir este veiculo!\n");
        printf("Motivo: Veiculo esta atualmente alugado.\n\n");
        printf("Pressione Enter para voltar...");
        getchar(); 
        getchar();
        fclose(arquivo_veiculos);
        return;
    }
    
    char confirmacao;
    printf("⚠️  TEM CERTEZA QUE DESEJA EXCLUIR ESTE VEICULO?\n");
    printf("Esta acao nao pode ser desfeita! (s/N): ");
    scanf(" %c", &confirmacao);
    
    if(confirmacao == 's' || confirmacao == 'S')
    {
        veiculo.ativo = 0;
        
        fseek(arquivo_veiculos, posicao, SEEK_SET);
        fwrite(&veiculo, sizeof(Veiculo), 1, arquivo_veiculos);
        fclose(arquivo_veiculos);
        
        printf("\n✅ Veiculo excluido com sucesso!\n");
    }
    else
    {
        fclose(arquivo_veiculos);
        printf("\nOperacao cancelada.\n");
    }
    
    printf("Pressione Enter para continuar...");
    getchar(); 
    getchar();
}
