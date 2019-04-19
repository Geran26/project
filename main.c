#include <stdio.h> 

void convert_case(char *str); // Converts lowercase letters to uppercase letters
void e(char *str, int y); // Performs Rotation encryption
void d(char *str, int y); // Performs Rotation decryption
void rotation_encryption(void);
void rotation_decryption(void);
void substitution_encryption(void);
void substitution_decryption(void);

int main() {
    int menu_select = 3;
    switch (menu_select) {
        case 1: rotation_encryption(); break; //performs rotation encryption of a known message. Needs a key
        case 2: rotation_decryption(); break; //performs rotation decryption of a given encrypted message. Needs a known key
        case 3: substitution_encryption(); break; //performs substitution encryption of a known message and key
        case 4: substitution_decryption(); break; //performs substitution decryption of a given encrypted message. Needs known key
        default: printf("Something went wrong\n");
    }
    return 0;
}

//Encryption of known message using rotation encryption    
void rotation_encryption(void){
    char str[] = "This is a message.";
    int i; //string counter
    int y = 5; // 'key' value. Amount the message is rotated by
    convert_case(str); //converts lowercase to uppercase    
    for(i=0; i<18; i++){ //i.e executes for all elements of the string cipher_text
        if(str[i]<91 && str[i]>64){ //if the string element lies in this range it is an uppercase letter and needs to be encrypted 
            str[i] = str[i] - 65; /*To perform encryption we need a number between 0 and 25, the ASCII of each uppercase letter minus 65 
                                    gives a number between 0 and 25*/
        }    
    }
    e(str, y); //encryption function, see below for definition and description
    for(i=0; i<18; i++){ // Returns string elements to values between 65 and 90, so when printf'd it prints letters
        if(str[i]<26 && str[i]>(-1)){
            str[i] = str[i] + 65;
        }
    }   
    printf("%s\n", str); // Prints string (which is now encrypted) to stdout 
}

//Decryption of known message using rotation decryption
void rotation_decryption(void){
    char cipher_text[] = "Ymnx Nx F Rjxxflj."; 
    int i = 0; //string counter
    int y = 5; //key value, i.e amount the encrypted message has been rotated by
    convert_case(cipher_text); //converts form lowercase to uppercase
    for(i=0; i<18; i++){ //i.e executes for all elements of the string cipher_text
        if(cipher_text[i]<91 && cipher_text[i]>64){ //if the string element lies in this range it is an uppercase letter and needs to be encrypted 
            cipher_text[i] = cipher_text[i] - 65; /*To perform encryption we need a number between 0 and 25, the ASCII of each uppercase letter minus 65 
                                                    gives a number between 0 and 25*/
        }
    }
    d(cipher_text, y); //decryption function, see below for definition and description
    for(i=0; i<18; i++){ // Returns cipher_text to values between 65 and 90, so when printf'd it prints letter
        if(cipher_text[i]<26 && cipher_text[i]>(-1)){
            cipher_text[i] = cipher_text[i] + 65;
        }
    } 
    printf("%s\n", cipher_text); //Prints cipher_text (which is now decrypted) to stdout
}

//Encryption of a known message with known key using substitution encryption
void substitution_encryption(void){
    char message_text[] = "This Is A Message.";
    char cipher_key[] = "QWERTYUIOPASDFGHJKLZXCVBNM"; //key describing what letters replace each letter of the alphabet
    char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; //the standard alphabet
    int i = 0; //string counter for alphabet and cipher_key in order to always be referring to corresponding elements of the two alphabets
    int j = 0; //string counter for message_text
    convert_case(message_text); //converts letters from lowercase to uppercase
    for(i=0; j<18; i++) { //i.e executes for the entire message, all letters of the alphabet are examined for each letter of the message
        if(alphabet[i] == message_text[j]) { //if the letter of the alphabet is the same as the letter in the message
            message_text[j] = cipher_key[i]; //substitute that message letter for the corresponding letter in the cipher alphabet
            i = -1; //resets string counter to 0 once the increment is performed in the for loop
            j++;  /*increments the string counter for message_text, i.e causes the above if statement to examine the next letter in the message. 
                    Only increments when a letter of the message is encrypted*/
        } else if(message_text[j]>90 || message_text[j]<65) { //executes if the element of the message is not an uppercase letter
            j++; //increments message_text, i.e moves onto the next element because this one is not a letter
            i = -1; //resets string counter to 0 once the increment is performed in the for loop
        }
    }
    printf("%s\n", message_text); //prints encrypted message to stdout
}

//Decryption of a known cipher text with a known cipher alphabet (key) using substitution decryption
void substitution_decryption(void) {
    char cipher_text[] = "ZIOL OL Q DTLLQUT";
    char cipher_key[] = "QWERTYUIOPASDFGHJKLZXCVBNM"; //key describing what letters replace each letter of the alphabet
    char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; //the standard alphabet
    int i = 0; //string counter for alphabet and cipher_key in order to always be referring to corresponding elements of the two alphabets
    int j = 0; //string counter for cipher_text
    convert_case(cipher_text); //converts letters form lowercase to uppercase
    for(i=0;ji<18; i++) { //i.e executes for the entire cipher_text, all letters of the alphabet are examined for each letter of cipher_text
        if(cipher_key[i] == cipher_text[j]) { //if the letter of the cipher_key is the same as the letter in the cipher_text
            cipher_text[j] = alphabet[i]; //substitute the cipher_text letter for the letter in the standard alphabet that corresponds to the letter in cipher_key
            i = -1; //resets string counter to 0 once the increment is performed in the for loop
            j++;  /*increments the string counter for message_text, i.e causes the above if statement to examine the next letter in the message. 
                    Only increments when a letter of the message is encrypted*/
        } else if(cipher_text[j]>90 || cipher_text[j]<65) {  //executes if the element of the message is not an uppercase letter
            j++; //increments message_text, i.e moves onto the next element because this one is not a letter
            i = -1; //resets string counter to 0 once the increment is performed in the for loop
        }
    }
    printf("%s\n", cipher_text); //prints decrypted message to stdout
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
