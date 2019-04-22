#include <stdio.h> 
#include <string.h>

void convert_case(char *str); // Converts lowercase letters to uppercase letters
void e(char *str, int y, int x); // Performs Rotation encryption
void d(char *str, int y, int x); // Performs Rotation decryption
void rotation_encryption(void);
void rotation_decryption(void);
void substitution_encryption(void);
void substitution_decryption(void);
void rotation_decryption_of_unknown(void);
int maximum_element_location(char *str);
int counting_phrases(char *str, int x, char *word);

int main() {
    int menu_select = 5;
    switch (menu_select) {
        case 1: rotation_encryption(); break; //performs rotation encryption of a known message. Needs a key
        case 2: rotation_decryption(); break; //performs rotation decryption of a given encrypted message. Needs a known key
        case 3: substitution_encryption(); break; //performs substitution encryption of a known message and key
        case 4: substitution_decryption(); break; //performs substitution decryption of a given encrypted message. Needs known key
        case 5: rotation_decryption_of_unknown(); break;
        default: printf("Something went wrong\n");
    }
    return 0;
}

//Encryption of known message using rotation encryption    
void rotation_encryption(void){
    char str[] = "This is a message";
    int x = (int) strlen(str);
    int y = 5; // 'key' value. Amount the message is rotated by
    convert_case(str); //converts lowercase to uppercase    
    e(str, y, x); //encryption function, see below for definition and description   
    printf("%s\n", str); // Prints string (which is now encrypted) to stdout 
}

//Decryption of known message using rotation decryption
void rotation_decryption(void){
    char cipher_text[] = "SJSFMPCRM WG O USBWIG. PIH WT MCI XIRUS O TWGV PM WHG OPWZWHM HC QZWAP O HFSS, WH KWZZ ZWJS WHG KVCZS ZWTS PSZWSJWBU HVOH WH WG GHIDWR. - OZPSFH SWBGHSWB";
    int y = 14; //key value, i.e amount the encrypted message has been rotated by
    int x = (int) strlen(cipher_text);
    convert_case(cipher_text); //converts form lowercase to uppercase
    d(cipher_text, y, x); //decryption function, see below for definition and description
    printf("%s\n", cipher_text); //Prints cipher_text (which is now decrypted) to stdout
}

//Encryption of a known message with known key using substitution encryption
void substitution_encryption(void){
    char message_text[] = "This Is A Message.";
    char cipher_key[] = "QWERTYUIOPASDFGHJKLZXCVBNM"; //key describing what letters replace each letter of the alphabet
    char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; //the standard alphabet
    int i = 0; //string counter for alphabet and cipher_key in order to always be referring to corresponding elements of the two alphabets
    int j = 0; //string counter for message_text
    int x = (int) strlen(message_text);
    convert_case(message_text); //converts letters from lowercase to uppercase
    for(i = 0; j < x; i++) { //i.e executes for the entire message, all letters of the alphabet are examined for each letter of the message
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
    int x = (int) strlen(cipher_text);
    convert_case(cipher_text); //converts letters form lowercase to uppercase
    for(i = 0; j < x; i++) { //i.e executes for the entire cipher_text, all letters of the alphabet are examined for each letter of cipher_text
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

void rotation_decryption_of_unknown(void) {
    char cipher_text[] = "YMNX NX F RJXXFLJ"; //Unknown encrypted text
    int x = (int) strlen(cipher_text); //Return the length of a string (excluding the '\0') and assigns to x
    int y = 0; // Rotation amount, changed further down code
    char word_count[26]; //Array will be used to record the word count of the words below
    convert_case(cipher_text); //converts form lowercase to uppercase (If needed)
    for(y = 0; y <= 25; y++) { // i.e for all rotation amounts (as there is only 25 possible rotations)
        d(cipher_text, y, x); //decryption function, see below for definition and description
        char the[] = " THE "; //6 Chars are the 6 words we are looking for in our decrypted text. Spaces are important as they help the compiler...
        char it[] = " IT "; //...recognise when the word 'THE' is by itself (i.e not apart of another word)
        char and[] = " AND ";
        char of[] = " OF "; //These words are all some of the most common words in the English Language 
        char is[] = " IS ";
        char to[] = " TO ";
        word_count[y] = counting_phrases(cipher_text, x, the) + counting_phrases(cipher_text, x, it) + counting_phrases(cipher_text, x, and) + counting_phrases(cipher_text, x, of) + counting_phrases(cipher_text, x, is) + counting_phrases(cipher_text, x, to);
        /* Above line: counting_phrases (see function definition below) counts the occurence of each word in the 'decrypted' string. The sum of the occurence
        of each word is taken and assigned to the element of array word_count corresponding to the rotation amount where each occurence was recorded */
        e(cipher_text, y, x); //Encryption function, see function definition and description below
    }
    y = maximum_element_location(word_count); /*The maximum element of word_count tells us which rotation returns a decryption with the most of these 6 words, 
                                                and it can be inferred that this rotation (i.e y) will give the full decryption of the text*/
    if(y >= 1){ //i.e if the rotation is anything but a rotation by 0 )staying the same
        d(cipher_text, y, x);
        printf("%s\n", cipher_text); //Prints cipher_text (which is now decrypted) to stdout
    } else { // Executes if none of these words are found in the text
        printf("None of these words appear in this text.");
    }
}

/*Definition for function that converts the case of the message. For every element of the string
that has a ASCII value betweeen 96 and 123 (i.e the ASCII Values of lowercase letters) it takes
away 32, leaving values within the range of 65 to 90 (i.e the ASCII values of uppercase letters)
This only changes letters as other symbols (numbers, punctuation, white space) are outside the 
range of 96 to 123 in ASCII*/
void convert_case(char *str){
    int i;
    int x = (int) strlen(str);
    for(i=0; i<x; i++){
        if(str[i]>96 && str[i]<123){
            str[i] = str[i] -32;
        }
    }
    return;
} 

/*Definition for the function that performs rotation encryption. The function arguments are a pointer to the string containing the message to be encrypted,
int y which is the rotation amount and int x which is the length of the string containing the message. For each element of the string, 65 is taken away
from the element (which has an ASCII value from 65 to 90) to give a value between 0 and 25 which is required to perform the actual encryption. Then, the 
rotation amoount (y) is added to each element and the modulus 26 is taken. This returns the element value + rotation amount if this is less than 26 or 
returns the remainder of (element value + rotation amount) divided by 26 if the element value + roatation amount is greater than 26. This only encrypts 
letters as other symbols (numbers, punctuation, white space) are outside the range of -1 to 26. Finally 65 is added back to each of the strings elements
to return their values to ones between 65 and 90 so that each element of the string corresponds to the ASCII values of the uppercase letters. This 
function returns void, but alters the string, given as a pointer in the argument of the function, effectively returning the encrypted string*/
void e(char *str, int y, int x){
    int i=0; //String counter
    for(i = 0; i < x; i++){ //i.e executes for all elements of the string
        if(str[i]<91 && str[i]>64){ //if the string element lies in this range it is an uppercase letter and needs to be encrypted 
            str[i] = str[i] - 65;
        }    
    }
    for(i = 0; i < x; i++){ // Encryption mathematics 
        if(str[i]>(-1) && str[i]<26){
            str[i] = (str[i] + y) % 26;
        }
    }
    for(i = 0; i < x; i++){ // Returns string elements to values between 65 and 90, so when printf'd it prints letters
        if(str[i]<26 && str[i]>(-1)){
            str[i] = str[i] + 65;
        }
    }
    return;
}

/*Definition for the function that performs rotation decryption. The function arguments are a pointer to the string containing the message to be encrypted,
int y which is the rotation amount and int x which is the length of the string containing the message. For each element of the string, 65 is taken away
from the element (which has an ASCII value from 65 to 90) to give a value between 0 and 25 which is required to perform the actual encryption. Then for 
each element of the string that is greater than or equal to the rotation amount and less than 26, this function subtractsthe rotation amount and takes
modulus 26. If the string element is smaller than the rotation amount but greater than -1 then 26 is added before performing the same expression as above
to avoid a negative number in the modulus equation. This only encrypts letters as other symbols (numbers, punctuation, white space) are outside the range 
of -1 to 26. Finally 65 is added back to each of the strings elements to return their values to ones between 65 and 90 so that each element of the string 
corresponds to the ASCII values of the uppercase letters. This function returns void, but alters the string, given as a pointer in the argument of the 
function, effectively returning the decrypted string */
void d(char *str, int y, int x){
    int i; //string counter
    for(i = 0; i < x; i++){ //i.e executes for all elements of the string cipher_text
        if(str[i]<91 && str[i]>64){ //if the string element lies in this range it is an uppercase letter and needs to be encrypted 
            str[i] = str[i] - 65;
        }
    }
    for(i = 0; i < x; i++){ // Decryption
        if(str[i]>=y && str[i]<26){
            str[i] = (str[i] - y) % 26;
        } else if(str[i]>(-1) && str[i]<y){ //Modulus of a negative number is undefined
            str[i] = str[i] + 26;
            str[i] = (str[i] - y) % 26; 
        }
    }
    for(i = 0; i < x; i++){ // Returns cipher_text to values between 65 and 90, so when printf'd it prints letter
        if(str[i]<26 && str[i]>(-1)){
            str[i] = str[i] + 65;
        }
    }
    return;
}

/*Definition of a function that returns the location of the largest number of a string. The function argument is a pointer to the string of which you wish to
find the location of the largest element. This function compares each element of the string to the previous largest element of the string to determine if it
larger or not. if it is it replaces the 'maximum' variable. This replaced value is then used to compare against the remaining elements of the string. This
continues until all elements of the stirng are tested. Whenever the maximum value is replaced the location is recorded as i (i.e the number of the element of
the string). This value is returned once the final maximum value is determined.  */
int maximum_element_location(char *str) {
    int maximum = str[0]; //records the ongoing maximum number
    int location = 0; //records the location (i.e which element of the string) of the maximum number
    int i = 0; //String counter
    for(i = 1; i < 26; i++){ //For all elements of the string (This function only needs i to be less than 26 as there is only 26 possible rotations)
        if(str[i] > maximum) {
            maximum = str[i];
            location = i;
        }
    }
    return location;
}

/*Definition of a function that counts the amount of times a substring (i.e a word) is present in a string. This function takes 3 arguments, the pointer
to a string which is to be examined (i.e the 'decrypted' message), int x which is the size of this string and another pointer to a string which is a word
(i.e " THE ", " AND ", etc... ). Explanation of flow control; if the element of the message string is the same as the word then the second if statement is
tested. Else j is reset to 0 and the continue statement causes the for statement to execute from the top. The second if statement tests if the full word has
been found. J is only incremented when the first if statement is true but the second is not, this means every time the letters in the word are found in the 
string, j is incremented until either the word is found, j is reset and count incremented or the letters in the word and string are no longer the same. This
continues until the entire 'decrypted' message is tested for this word. The value of the count is returned (i.e the number of times the word appears in the 
'decrypted' message) */ 
int counting_phrases(char *str, int x, char *word) {
    int i = 0; // string counter
    int j = 0; //2nd string counter
    int count = 0; // used to record the sumber of each word
    for(i = 0; i < x; i++){ // for all elements of the string (1st argument)
        if(str[i] == word[j]){
            if(j == (strlen(word) - 1)){ // minus one because the string length is measured from one, but elements are numbered from 0
                count++;
                j = 0;
                continue; // executes from the top of for statement (j is not incremented)
            }
        } else { // conncected to the first if statement
            j = 0;
            continue; // executes from the top of for statement (j is not incremented)
        }
        j++;
    }
    return count;
}