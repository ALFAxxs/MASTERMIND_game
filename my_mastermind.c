#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
int size_word(char* str){

    int d = 0;
     for (int i = 0; str[i] != '\0'; i++){
       d++;
    }
    return d;
}
char* all_giv(){
    char *satr = (char*)malloc(500 * sizeof(char));
    int i = 0;
    char k;
    while (read(0, &k, 1) > 0){
        if (k != '\n'){
            satr[i] = k;
            i++;
        }
        else {
            return satr;
         }
    }
    return 0;
}
int input(char* str, char m){

    for (int i = 0; i < size_word(str); i++){
        if (str[i] == m){
            return 1;
        }
    }
    return 0;
}
int wrong_answer(char* str){

    int tr = 1;
    if (size_word(str) != 4){
        return 0;
    }
    for (int i = 0; i < size_word(str); i++){
        if (str[i] > '9' || str[i] < '0'){
            tr = 0; 
        }
        for (int h = 0; h < i; h++){
            if (str[h] == str[i]){
                tr = 0;
            }
        }
    }
    if (!tr ){
        return 0;
    }else{
        return 1;
        }
}
int check_str(char* str, char* str2){

    for (int i = 0; i < size_word(str); i++){
        if (str[i] != str2[i]){
            return 0;
        }
    }
    return 1;
}
void get_rand_code(char* str){

    srand(time(NULL));
    for (int i = 0; i < 4; i++){
        char randamm = rand() % 8 + '0';
        if (input(str, randamm) == 0){
            str[i] = randamm;
        }
    }
}
char* copy(char* str, char* str2){

    int i = 0;
    while (i < size_word(str2)){
        str[i] = str2[i];
        i++;
    }
    return str;
}
int main(int argc, char* argv[]){

 int welp = 0,misp = 0, absol = 0, bsol = 0,raunnumb = 10;char memor[500];
     for (int j = 1; j < argc; j++){
         if (check_str(argv[j], "-c")){
             absol = j+1;
         }
         if (check_str(argv[j], "-t")){
             bsol = j+1;
             raunnumb = atoi(argv[bsol]);
         }
     }
    if (absol != 0){
        copy(memor, argv[absol]);
    }else{
        get_rand_code(memor);
        }
    printf("Will you find the secret code?\n");
    for (int k = 0; k < raunnumb; k++){
        welp =0; misp = 0;
        printf("---\nRound %d\nPlease enter a valid guess\n",k);
        int trueinput; char* memo = malloc(500);
        do{ 
            trueinput = 1;
            write(0, ">",1);
            memo=all_giv();
             if (wrong_answer(memo) == 0){
                trueinput = 0;
            }
            if (trueinput == 0){
                printf("Wrong input!\n");
            }
            } while (trueinput != 1);
            for (int h = 0; h < 4; h++){
            if (memor[h] == memo[h]){
                welp++;
            }else if (input(memor, memo[h]) != 0 && memor[h] != memo[h]){
                misp++;
            }
             }
            if (welp == 4){
            printf("Congratz! You did it!\n");
            return 0;
            }else {
            printf("Well placed pieces: %d\nMisplaced pieces: %d\n",welp, misp);
        }
    }
}