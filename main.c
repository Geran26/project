#include <stdio.h> 

void convert_case(char *str);

int main() {
    char str[] = "This is a message.";
    printf("%s\n", str);
    int i; //string counter
    convert_case(str);
    printf("%s\n", str);
    //Encryption of known message
    for(i=0; i<18; i++) {
        if(str[i]>64 && str[i]<91){
            str[i] = str[i] + 11;
            if(str[i]>90){
                str[i] = str[i] - 25;
            }
        }
    }
    printf("%s\n", str);
    //Decryption of known message
    for(i=0; i<18; i++) {
        if(str[i]>64 && str[i]<91){
            str[i] = str[i] - 11;
            if(str[i]<65){
                str[i] = str[i] + 25;
            }
        }
    }
    printf("%s\n", str);
    return 0;
}

void convert_case(char *str){
    int i;
    for(i=0; i<18; i++){
        if(str[i]>96 && str[i]<123){
            str[i] = str[i] -32;
        }
    }
    return;
}