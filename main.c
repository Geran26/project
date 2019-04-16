#include <stdio.h> 

void convert_case(char *str); // Converts lowercase letters to uppercase letters
void e(char *str, int y); // Performs Rotation encryption
void d(char *str, int y); // Performs Rotation decryption
void rotation_encryption(void);
void rotation_decryption(void);

int main() {
    int menu_select = 3;
    switch (menu_select) {
        case 1: rotation_encryption(); break;
        case 2: rotation_decryption(); break;
        default: printf("Something went wrong\n");
    }
    return 0;
}
    
void rotation_encryption(void){
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
}

void rotation_decryption(void){
    //Decryption of known message
    char cipher_text[] = "Ymnx Nx F Rjxxflj.";
    int i = 0; //Resetting string counter
    int y = 5;
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
}

/*Definition for function that converts the case of the message. For every element of the string
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
by 26 if the element value + roatation amount is greater than 26. This only encrypts letters as other 
symbols (numbers, punctuation, white space) are outside the range of -1 to 26*/
void e(char *str, int y){
    int i; //String counter
    for(i=0; i<18; i++){
        if(str[i]>(-1) && str[i]<26){
            str[i] = (str[i] + y) % 26;
        }
    }
    return;
}

/*Definition for the function that performs rotation decryption. y = roatation amount. For each element
of the string that is greater than or equal to the rotation amount and less than 26, this function subtracts
the rotation amount and takes modulus 26, returning a number corresponding to a letter in the decrypted 
message. If the string element is smaller than the rotation amount but greater thean -1 then 26 is added 
before performing the same expression as above to avoid a negative number in the modulus equation. This 
only encrypts letters as other symbols (numbers, punctuation, white space) are outside the range of -1 to 26 */
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
