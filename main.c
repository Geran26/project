#include <stdio.h> 

void convert_case(char *str); // Converts lowercase letters to uppercase letters
void e(char *str, int y); // Performs Rotation encryption
void d(char *str, int y); // Performs Rotation decryption

int main() {
    //Encryption of known message
    char str[] = "This is a message.";
    int i; //string counter
    int y = 5; // 'key' value. Amount the message is rotated by
    convert_case(str); //converts lowercase to uppercase
    printf("%s\n", str);
    for(i=0; i<18; i++){ //ASCII of each letter minus 65 gives a number between 0 and 25
        if(str[i]<91 && str[i]>64){
            str[i] = str[i] - 65;
        }
    }
    e(str, y);
    for(i=0; i<18; i++){ // Returns str to values between 65 and 90, so it prints letters
        if(str[i]<26 && str[i]>(-1)){
            str[i] = str[i] + 65;
        }
    }   
    printf("%s\n", str);
    //Decryption of known message
    char cipher_text[] = "Ymnx Nx F Rjxxflj.";
    i = 0; //Resetting string counter
    convert_case(cipher_text);
    for(i=0; i<18; i++){ //ASCII of each letter minus 65 gives a number between 0 and 25
        if(cipher_text[i]<91 && cipher_text[i]>64){
            cipher_text[i] = cipher_text[i] - 65;
        }
    }
    d(cipher_text, y);
    for(i=0; i<18; i++){ // Returns str to values between 65 and 90, so it prints letter
    if(cipher_text[i]<26 && cipher_text[i]>(-1)){
            cipher_text[i] = cipher_text[i] + 65;
        }
    } 
    printf("%s\n", cipher_text);
    return 0;
}

/*Definition for function that converts case of the message. For every element of the string
that has a ASCII value betweeen 96 and 123 (i.e the ASCII Values of lowercase letters) it takes
away 32, leaving values within the range of 65 to 90 (i.e the ASCII values of uppercase letters)
This only changes letters as other symbols (numbers, punctuation, white space) are outside the 
range of 96 to 123 in ASCII*/
void convert_case(char *str){
    int i;
    for(i=0; i<18; i++){
        if(str[i]>96 && str[i]<123){
            str[i] = str[i] -32;
        }
    }
    return;
} 

/*Definition for the function that performs rotation encryption. For each element of the string it 
adds the rotation amount and takes this value modulus 26. This returns the element value + rotation
amount if this is less than 26 or returns the remainder of (element value + rotation amount) divided
by 26 if the element value + roatation amount is greater than 26*/
void e(char *str, int y){
    int i; //String counter
    for(i=0; i<18; i++){
        if(str[i]>(-1) && str[i]<26){
            str[i] = (str[i] + y) % 26;
        }
    }
    return;
}

/*Definition for the function that performs rotation decryption.*/
void d(char *str, int y){
    int i;
    for(i=0; i<18; i++){
        if(str[i]>=y && str[i]<26){
            str[i] = (str[i] - y) % 26;
        } else if(str[i]>(-1) && str[i]<y){
            str[i] = str[i] + 26;
            str[i] = (str[i] - y) % 26;
        }
    }
    return;
}