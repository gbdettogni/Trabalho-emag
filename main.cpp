#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <octave/oct.h>
#include <octave/ls-oct-text.h>
#include <math.h>
#include <termios.h>
#include <unistd.h>

int main(){
    printf("Escolha a funcao\nZ para aumentar fontes (padrao)\nX para diminuir as fontes\nC para mover um objeto\nV para ativar o menu de objetos\nB para dimensionar um objeto\nH para ativar este menu\nE para sair\n");
    char mode = 'z';
    
    static struct termios oldt, newt;
    tcgetattr( STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON);
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);
    char command;
    double v1 = 40.0;
    double v2 = 0.0;
    double v3 = -90.0;
    double v4 = 0.0;
    int nx = 70;
    int ny = 70;
    double h = 0.1;
    double E = 8.85*pow(10,-12);
    double ro = 1.59*pow(10, -8);
    int f = 0;
    int p1 = nx/2;
    int p2 = ny/2;
    int size = 5;
    char obj = '1';
    while(1){
        if(f){
        scanf("%c", &command);
        if(command >='A' && command <= 'Z')
            command = command - ('A' - 'a');
        if(command == 'e') break;
        else if(command == 'h'){
            printf("Escolha a funcao\nZ para aumentar fontes (padrao)\nX para diminuir as fontes\nC para mover um objeto\nV para ativar o menu de objetos\nB para dimensionar um objeto\nH para ativar este menu\nE para sair\n");
        }
        else if(command == 'v'){
            printf("Escolha um objeto:\n1) Linha vertical\n2) Linha horizontal\n3) Quadrado\n4) Triangulo\nPressione qualquer outro botao para remover o objeto\n");
        }
        if (command == 'z' || command == 'x' || command == 'c' || command == 'v' || command == 'b'){
            printf("\nModo alterado, use sempre as teclas wasd para efetuar as operacoes\n");
            mode = command;
            continue;
        }
        else if(mode == 'z'){
            switch (command) {
                case 'a':
                    v1+=5;
                    printf("\nValores atuais de tensao\nv1:%.2lf v2:%.2lf v3:%.2lf v4:%.2lf", v1, v2, v3, v4);
                    break;
                case 'd':
                    v3+=5;
                    printf("\nValores atuais de tensao\nv1:%.2lf v2:%.2lf v3:%.2lf v4:%.2lf", v1, v2, v3, v4);
                    break;
                case 's':
                    v2+=5;
                    printf("\nValores atuais de tensao\nv1:%.2lf v2:%.2lf v3:%.2lf v4:%.2lf", v1, v2, v3, v4);
                    break;
                case 'w':
                    v4+=5;
                    printf("\nValores atuais de tensao\nv1:%.2lf v2:%.2lf v3:%.2lf v4:%.2lf", v1, v2, v3, v4);
                    break;
                default:
                    printf("comando invalido\n");
                    break;
            }
        }
        else if(mode == 'x'){
            switch (command) {
                case 'a':
                    v1-=5;
                    printf("\nValores atuais de tensao\nv1:%.2lf v2:%.2lf v3:%.2lf v4:%.2lf", v1, v2, v3, v4);
                    break;
                case 'd':
                    v3-=5;
                    printf("\nValores atuais de tensao\nv1:%.2lf v2:%.2lf v3:%.2lf v4:%.2lf", v1, v2, v3, v4);
                    break;
                case 's':
                    v2-=5;
                    printf("\nValores atuais de tensao\nv1:%.2lf v2:%.2lf v3:%.2lf v4:%.2lf", v1, v2, v3, v4);
                    break;
                case 'w':
                    v4-=5;
                    printf("\nValores atuais de tensao\nv1:%.2lf v2:%.2lf v3:%.2lf v4:%.2lf", v1, v2, v3, v4);
                    break;
                default:
                    printf("comando invalido\n");
                    break;
            }
        }
        else if(mode == 'c'){
            switch (command) {
                case 'a':
                    p2--;
                    printf("\nCoordenadas do objeto?\np1: %d p2: %d\n", p1, p2);
                    break;
                case 'd':
                    p2++;
                    printf("\nCoordenadas do objeto?\np1: %d p2: %d\n", p1, p2);
                    break;
                case 's':
                    p1--;
                    printf("\nCoordenadas do objeto?\np1: %d p2: %d\n", p1, p2);
                    break;
                case 'w':
                    p1++;
                    printf("\nCoordenadas do objeto?\np1: %d p2: %d\n", p1, p2);
                    break;
                default:
                    printf("comando invalido\n");
                    break;
            }
        }
        else if(mode == 'v'){
            obj = command;
        }
        else if(mode == 'b'){
            switch (command) {
                case 'd':
                    size++;
                    printf("\nTamanho atual: %d\n", 2*size);
                    break;
                case 'a':
                    size--;
                    printf("\nTamanho atual: %d\n", 2*size);
                    break;
                case 's':
                    size--;
                    printf("\nTamanho atual: %d\n", 2*size);
                    break;
                case 'w':
                    size++;
                    printf("\nTamanho atual: %d\n", 2*size);
                    break;
                default:
                    printf("comando invalido\n");
                    break;
            }
        }
        }
        f=1;
        // printf("%.20lf", E);
        Matrix M(nx, ny);

        double v[nx][ny];
        double p[nx][ny];
        for (int i = 0; i < nx; i++) {
            for (int j = 0; j < nx; j++) {
                v[i][j] = 0;
                p[i][j] = 0;
            }
        }
        
        switch (obj) {
            case '1':
                for (int i = -size; i < size; i++)
                    p[p1+i][p2] = ro;
                break;
            case '2':
                for (int i = -size; i < size; i++)
                    p[p1][p2+i] = ro;
                break;
            case '3':
                for (int j = -size; j < size; j++){
                    for (int i = -size; i < size; i++){
                        p[p1+j][p2+i] = ro;
                    }
                }
                break;
            case '4':
                for (int j = -size; j < size; j++){
                    for (int i = -size; i < j; i++){
                        p[p1+j][p2+i] = ro;
                    }
                }
                break;
            default:
                break;
        }
        

        for(int i = 1; i < nx-1; i++){
            v[i][0] = v1;
            v[i][ny-1] = v3;
        }

        for(int i = 1; i < ny-1; i++){
            v[0][i] = v4;
            v[nx-1][i] = v2;
        }
            

        v[0][0] = 0.5*(v1+v4);
        v[nx-1][0] = 0.5*(v1+v2);
        v[0][ny-1] = 0.5*(v3+v4);
        v[nx-1][ny-1] = 0.5*(v2+v3);

        // for (int i = 0; i < nx; i++) {
        //     for (int j = 0; j < nx; j++) {
        //         printf("%.20lf ", p[i][j]);
        //     }
        //     printf("\n");
        // }
        while(1){
            double med = 0.0;
            for(int i = 1; i < nx-1; i++){
                for(int j = 1; j < ny-1; j++){
                    double old = v[i][j];
                    v[i][j] = 0.25 * (v[i+1][j] + v[i-1][j] + v[i][j+1] + v[i][j-1] + p[i][j]*h*h/E);
                    med = med + fabs(v[i][j]-old);
                }
            }
            med = med / ((nx-2)*(ny-2));
            if (med < 0.01) break;
        }
        for (int i = 0; i < nx; i++) {
            for (int j = 0; j < nx; j++) {
                M.elem(i,j) = v[i][j];
            }
        }
        int flag;        
        while(1){
            FILE* tsl = fopen("tsl", "r");
            fscanf(tsl, "%d", &flag);
            fclose(tsl);
            if(flag) break;
        }
        std::ofstream out_file_stream("out.mat");
        save_text_data (out_file_stream,octave_value(M),std::string("M_matrix"),true,5);
        out_file_stream.close();
        
        FILE* tsl = fopen("tsl", "w");
        fprintf(tsl, "0");
        fclose(tsl);
    }
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
    return 0;
}