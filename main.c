#include <stdio.h>

int main () {

    int coluna = 0, linha = 0, calcula_minas = 0, boom = 0;
    char matricula[20];
    int campo[6][6] = {0};


    printf("\n\nseja bem vindo ao campo minado: \n\npra comecar, insira sua matricula: ");
    scanf("%s", matricula);


    // calcula as minas baseando-se na matricula do aluno

    for(int i = 0; i<10; i+= 2) {

        if(matricula[i] == '\0' || matricula[i+1] == '\0') {

            break;

        }

        linha = matricula[i] - '0', coluna = matricula[i+1] - '0';
        
        linha = linha%6, coluna = coluna%6; 

        if(campo[linha][coluna] == -1) {

            continue;

        }

        campo[linha][coluna] = -1;

           
        linha = 0, coluna = 0;
        
    }

    for(int i= 0; i<6; i++) {

        for(int j=0; j<6; j++) {

            if(campo[i][j] == -1) {

                boom++;
  
            }


            // detecta as minas ao redor


            else {


                if(i!=0 && campo[i-1][j] == -1) {

                    calcula_minas++;

                }

                if(i!=5 && campo[i+1][j] == -1) {

                    calcula_minas++;

                }

                if(j!= 0 && campo[i][j-1] == -1) {

                    calcula_minas++;

                }

                if(j!= 5 && campo[i][j+1] == -1) {

                    calcula_minas++;

                }

                if(j!= 0 && i!= 0 && campo[i-1][j-1] == -1) {

                    calcula_minas++;

                }

                if(j!= 5 && i!= 5 && campo[i+1][j+1] == -1) {

                    calcula_minas++;

                }

                if(i!= 5 && j!=0 && campo[i+1][j-1] == -1) {

                    calcula_minas++;
                    
                }

                if(i!=0 && j!= 5 && campo[i-1][j+1] == -1) {

                    calcula_minas++;
                    
                }


                // diz quantas minas estao ao redor
       

                campo [i][j] = calcula_minas;               


            }

            calcula_minas = 0;
                
        }

    }


    // imprime o primeiro esboço do tabuleiro


    int interface[6][6] = {0}, colunax, linhax;

    printf("\ntotal de minas no campo: %d", boom);

    printf("\n\n");

    for(int i = 0; i<6; i++) {

        printf("L%d", i+1);


        for(int j = 0; j<6; j++) {

          
            printf("|");

            printf(" #");           

            printf(" |");

            

        }

        printf("\n");

        if(i==5 ) {

            printf("   C1   C2   C3   C4   C5   C6 ");

        }
      

    }

    int gameover = 0, jogada = 0, casa=0;
 
    // aqui começa a parte logica, nao so a visual


    while(gameover==0 && casa < (36 - boom)) {


        printf("\n\nescolha a linha(Lx): ");
        scanf("%d" , &linhax);

        linhax = linhax - 1;

        while(linhax>5 || linhax<0) {

            printf("\npor favor insira uma opcao valida: ");
            scanf("%d", &linhax);
            linhax = linhax-1;

        }
        

        printf("\n\nescolha a coluna(Cx): ");
        scanf("%d" , &colunax);

        colunax = colunax - 1;

        while(colunax>5 || colunax<0) {

            printf("\npor favor insira uma opcao valida: ");
            scanf("%d", &colunax);
            printf("\n");

            colunax = colunax-1;

        }

        if(campo[linhax][colunax] == -1) {

            gameover++;

        }
        
        // essa parte faz o "efeito cascata", passei um tempinho pensando em como elaborar isso
        
        else {

            if (interface[linhax][colunax] == 0) {

                interface[linhax][colunax] = 1;

                jogada++;

                casa++;
  
                if (campo[linhax][colunax] == 0) { 
                    
                    for(int l = linhax - 1; l <= linhax + 1; l++) {

                        for(int m = colunax - 1; m <= colunax + 1; m++) {
                                              
                            if (l >= 0 && l < 6 && m >= 0 && m < 6) {      
                                
                                if (interface[l][m] == 0 && campo[l][m] != -1) {
                                    
                                    interface[l][m] = 1;

                                    casa++;
                                   
                                }
                            }
                        }
                    }
                }
            }

            else {

                printf("\n\nvoce ja escolheu essa casa, por favor escolha outra!\n\n");
            }

        }
    

        // imprime as jogadas do usuario, como:  casas abertas/fechadas e minas ao redor

        for(int i = 0; i<6; i++) {

            printf("L%d", i+1);

            for(int j = 0; j<6; j++) {

          
                printf("|");

                if(interface[i][j] == 1) {
                
                    printf(" %d", campo[i][j]);

                
                }

                else if(gameover>0 && campo[i][j] == -1) {

                    printf(" *");

                }
                
                else {

                    printf(" #");

                }

                printf(" |");

            

            }


            printf("\n");

            if(i==5 ) {

                printf("\n   C1   C2   C3   C4   C5   C6 ");

            }

            

        }

    

    }

    // aqui eu personalizei a mensagem de vitoria, pra caso seja a primeira jogada, nao imprimir no
    // plural, o que tiraria um pouco a graça da interaçao


    if(gameover>0 && casa>0) {

        printf("\n\n a coordenada que voce marcou (L%d, C%d) tinha uma mina\n\n game over!\n\n estatisticas: ao todo voce abriu um total de %d casas e fez %d jogadas", linhax+1, colunax+1, casa, jogada);

    }

    else if(gameover>0 && casa==0) {

        printf("\n\n a coordenada que voce marcou (L%d, C%d) tinha uma mina\n\n game over!\n\n estatisticas: voce abriu uma casa e fez uma jogada, boa sorte da proxima vez!", linhax+1, colunax+1);

    }

    else if(casa >= 36 - boom) {

        printf("\n\n parabens voce conseguiu sair dessa ileso, ao todo voce fez um total de %d jogadas e abriu %d casas", jogada, casa);
    }
    
    // imprime o campo minado inteiro, mostrando a localizaçao das minas 


    printf("\n\n aqui esta seu campo minado completo: \n\n");

    for(int i = 0; i<6; i++) {

        printf("L%d", i+1);

        for(int j = 0; j<6; j++) {
    
            printf("|");

            if(campo[i][j] == -1) {
                
                printf(" *");

            }

            else {
                
                

                printf(" %d", campo[i][j]);

            }

            printf(" |");

        }


        printf("\n");

        if(i==5 ) {

            printf("\n   C1   C2   C3   C4   C5   C6 ");

        }

            

    }


    return 0;

}
