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
void substitution_decryption_of_unknown(void);

int main() {
    int menu_select = 4;
    /*printf("Please select which function you wish to perform: \n");
    printf("Enter 1 for rotation encrytion\n");
    printf("Enter 2 for rotation decryption\n");
    printf("Enter 3 for substitution encryption\n");
    printf("Enter 4 for substitution decryption\n");
    printf("Enter 5 for rotation decryption without a key\n");
    printf("Enter 6 for substitution decryption without a key\n");
    scanf("%d", &menu_select);*/
        switch (menu_select) {
            case 1: rotation_encryption(); break; //performs rotation encryption of a known message. Needs a key
            case 2: rotation_decryption(); break; //performs rotation decryption of a given encrypted message. Needs a known key
            case 3: substitution_encryption(); break; //performs substitution encryption of a known message and key
            case 4: substitution_decryption(); break; //performs substitution decryption of a given encrypted message. Needs known key
            case 5: rotation_decryption_of_unknown(); break; //Decrypts an unknown text where you do not know the rotation amount
            case 6: substitution_decryption_of_unknown(); break; //Decrypts an unknown text where you do not know the letter substitutions
            default: printf("Something went wrong\n");
        }
    return 0;
}

//Encryption of known message using rotation encryption    
void rotation_encryption(void){
    FILE *fp;
    fp = fopen("input.txt", "r+"); //Opening file to read input and the recieve output
    if(fp == NULL) { //Error checking, i.e executes if unable to open file
        printf("Can't open input file");
        return; //Exits function completely - no point continuing if you cant read the file
    }
    int count = 0; //counter for how long the input message is
    while(!feof(fp)) { //While not at the end of the file
        char c = 0;
        fscanf(fp, "%c", &c); //Assingning file character to variable c to be used in if statement below
        if(c != '\n') { //This tests for a new line, this only execute if the file has NOT reached a new line
            count++; //count is incremented to show there is another letter in the string to be inialised below
        } else { //if it is a newline
            count = count - 1; /*count is incremented an extra time so to get correct number of characters in the 
                                first line count needs to be decreased by 1*/
            break; //stop reading the file as we have counted all elements in the first row
        }
    }
    char message_text[count]; //string with length = amount of characters in first line of file
    int i = 0; //string counter
    fseek(fp, 0, SEEK_SET); //resets the file position indicator to beginning of the file - so we can read from beginning again
    while(!feof(fp)) { //While not at the end of the file
        char c = 0;
        fscanf(fp, "%c", &c); //Assingning file character to variable c to be used in if statement below
        if(c != '\n') { //This tests for a new line, this only execute if the file has NOT reached a new line
            message_text[i] = c; // gives each string element the the corresponding letter in the file's first row
            i++; //i.e moving to the next element of message_text
        } else { //when c == newline
            break; //exits once the newline has been reached
        } 
    }
    int y; // 'key' value. Amount the message is rotated by
    fscanf(fp, "%d", &y); //reads second line of file for an interger number between 0 and 25
    convert_case(message_text); //converts lowercase to uppercase    
    e(message_text, y, count); //encryption function, see below for definition and description   
    printf("%s\n", message_text); // Prints string (which  is now encrypted) to stdout
    fprintf(fp, "\n%s\n", message_text); //Prints string (which is now encrypted) to the file
    fclose(fp); //closes the file fp
}

//Decryption of known message using rotation decryption
void rotation_decryption(void){
    FILE *fp;
    fp = fopen("DecryptionInput.txt", "r+"); //Opening file to read input and the recieve output
    if(fp == NULL) { //Error checking, i.e executes if unable to open file
        printf("Can't open input file");
        return; //Exits function completely - no point continuing if you cant read the file
    }
    int count = 0; //counter for how long the input message is
    while(!feof(fp)) { //While not at the end of the file
        char c = 0;
        fscanf(fp, "%c", &c); //Assingning file character to variable c to be used in if statement below
        if(c != '\n') { //This tests for a new line, this only execute if the file has NOT reached a new line
            count++; //count is incremented to show there is another letter in the string to be inialised below
        } else { //if it is a newline
            count = count - 1; /*count is incremented an extra time so to get correct number of characters in the 
                                first line count needs to be decreased by 1*/
            break; //stop reading the file as we have counted all elements in the first row
        }
    }
    char cipher_text[count]; //string with length = amount of characters in first line of file
    int i = 0; //string counter
    fseek(fp, 0, SEEK_SET); //resets the file position indicator to beginning of the file - so we can read from beginning again
    while(!feof(fp)) { //While not at the end of the file
        char c = 0;
        fscanf(fp, "%c", &c); //Assingning file character to variable c to be used in if statement below
        if(c != '\n') { //This tests for a new line, this only execute if the file has NOT reached a new line
            cipher_text[i] = c; // gives each string element the the corresponding letter in the file's first row
            i++; //i.e moving to the next element of cipher_text
        } else { //when c == newline
            break; //exits once the newline has been reached
        } 
    }
    int y; // 'key' value. Amount the message is rotated by
    fscanf(fp, "%d", &y); //reads second line of file for an interger number between 0 and 25
    convert_case(cipher_text); //converts form lowercase to uppercase
    d(cipher_text, y, count); //decryption function, see below for definition and description
    printf("%s\n", cipher_text); //Prints cipher_text (which is now decrypted) to stdout
    fprintf(fp, "\n%s\n", cipher_text); //Prints cipher_text (which is now decrypted) to the file
    fclose(fp); //closes the file
}

//Encryption of a known message with known key using substitution encryption
void substitution_encryption(void){
    FILE *fp;
    fp = fopen("SubEncryptInput.txt", "r+"); //Opening file to read input and the recieve output
    if(fp == NULL) { //Error checking, i.e executes if unable to open file
        printf("Can't open input file");
        return; //Exits function completely - no point continuing if you cant read the file
    }
    int count = 0; //counter for how long the input message is
    while(!feof(fp)) { //While not at the end of the file
        char c = 0;
        fscanf(fp, "%c", &c); //Assingning file character to variable c to be used in if statement below
        if(c != '\n') { //This tests for a new line, this only execute if the file has NOT reached a new line
            count++; //count is incremented to show there is another letter in the string to be inialised below
        } else { //if it is a newline
            count = count - 1; /*count is incremented an extra time so to get correct number of characters in the 
                                first line count needs to be decreased by 1*/
            break; //stop reading the file as we have counted all elements in the first row
        }
    }
    char message_text[count]; //string with length = amount of characters in first line of file
    int i = 0; //string counter
    fseek(fp, 0, SEEK_SET); //resets the file position indicator to beginning of the file - so we can read from beginning again
    while(!feof(fp)) { //While not at the end of the file
        char c = 0;
        fscanf(fp, "%c", &c); //Assingning file character to variable c to be used in if statement below
        if(c != '\n') { //This tests for a new line, this only execute if the file has NOT reached a new line
            message_text[i] = c; // gives each string element the the corresponding letter in the file's first row
            i++; //i.e moving to the next element of message_text
        } else { //when c == newline
            break; //exits once the newline has been reached
        } 
    }
    char cipher_key[26]; //key describing what letters replace each letter of the alphabet
    i = 0; //resetting the string counter
    while(!feof(fp)) { //while not at the end of the file
        char c = 0; // char used to do check below
        fscanf(fp, "%c", &c); //assigns each character of the file to variable c
        if(c != '\n' && i != 26) { // This executes if the character is not a newline and if the string is not full
            cipher_key[i] = c; //each element of string becomes corresponding character in file
            i++; //i.e moves to the next element of string
        } else {
            break; //exits once all 26 character have been read or a newline is found
        }
    }
    char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; //the standard english alphabet
    i = 0; /*string counter reset for use as counter for alphabet and cipher_key in order to always be referring to 
            corresponding elements of the two alphabets*/
    int j = 0; //string counter for message_text
    convert_case(message_text); //converts letters from lowercase to uppercase (if required)
    for(i = 0; j < count; i++) { //i.e executes for the entire message, all letters of the alphabet are examined for each letter of the message
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
    fprintf(fp, "\n%s\n", message_text); //prints encrypted message to file
    fclose(fp); //closes the file
}

//Decryption of a known cipher text with a known cipher alphabet (key) using substitution decryption
void substitution_decryption(void) {
    FILE *fp;
    fp = fopen("SubDecryptInput.txt", "r+"); //Opening file to read input and the recieve output
    if(fp == NULL) { //Error checking, i.e executes if unable to open file
        printf("Can't open input file");
        return; //Exits function completely - no point continuing if you cant read the file
    }
    int count = 0; //counter for how long the input message is
    while(!feof(fp)) { //While not at the end of the file
        char c = 0;
        fscanf(fp, "%c", &c); //Assingning file character to variable c to be used in if statement below
        if(c != '\n') { //This tests for a new line, this only execute if the file has NOT reached a new line
            count++; //count is incremented to show there is another letter in the string to be inialised below
        } else { //if it is a newline
            count = count - 1; /*count is incremented an extra time so to get correct number of characters in the 
                                first line count needs to be decreased by 1*/
            break; //stop reading the file as we have counted all elements in the first row
        }
    }
    char cipher_text[count]; //string with length = amount of characters in first line of file
    int i = 0; //string counter
    fseek(fp, 0, SEEK_SET); //resets the file position indicator to beginning of the file - so we can read from beginning again
    while(!feof(fp)) { //While not at the end of the file
        char c = 0;
        fscanf(fp, "%c", &c); //Assingning file character to variable c to be used in if statement below
        if(c != '\n') { //This tests for a new line, this only execute if the file has NOT reached a new line
            cipher_text[i] = c; // gives each string element the the corresponding letter in the file's first row
            i++; //i.e moving to the next element of message_text
        } else { //when c == newline
            break; //exits once the newline has been reached
        } 
    }
    char cipher_key[26]; //key describing what letters replace each letter of the alphabet (26 = number of letters in the alphabet)
    i = 0; //resetting the string counter
    while(!feof(fp)) { //while not at the end of the file
        char c = 0; // char used to do check below in if statement
        fscanf(fp, "%c", &c); //assigns each character of the file to variable c
        if(c != '\n' && i != 26) { // This executes if the character is not a newline and if the string is not full
            cipher_key[i] = c; //each element of string becomes corresponding character in file
            i++; //i.e moves to the next element of string
        } else {
            break; //exits once all 26 character have been read or a newline is found
        }
    }
    char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; //the standard alphabet
    i = 0; //reset string counter for use as counter for alphabet and cipher_key in order to always be referring to corresponding elements of the two alphabets
    int j = 0; //string counter for cipher_text
    convert_case(cipher_text); //converts letters form lowercase to uppercase
    for(i = 0; j < count; i++) { //i.e executes for the entire cipher_text, all letters of the alphabet are examined for each letter of cipher_texcount
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
    fprintf(fp, "\n%s\n", cipher_text); //prints decrypted message to file
    fclose(fp); //closes the file
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
        d(cipher_text, y, x); //decryption function see function definition below
        printf("%s\n", cipher_text); //Prints cipher_text (which is now decrypted) to stdout
    } else { // Executes if none of these words are found in the text
        printf("None of these words appear in this text.");
    }
}

void substitution_decryption_of_unknown(void) {
    char cipher_text[] = "RCR VYE BGBX HBNX FHB FXNQBRV YM RNXFH IZNQEBCJ FHB PCJB? C FHYEQHF KYF. CF'J KYF N JFYXV FHB DBRC PYEZR FBZZ VYE. CF'J N JCFH ZBQBKR. RNXFH IZNQEBCJ PNJ N RNXA ZYXR YM FHB JCFH, JY IYPBXMEZ NKR JY PCJB HB LYEZR EJB FHB MYXLB FY CKMZEBKLB FHB OCRCLHZYXCNKJ FY LXBNFB ZCMB… HB HNR JELH N AKYPZBRQB YM FHB RNXA JCRB FHNF HB LYEZR BGBK ABBI FHB YKBJ HB LNXBR NWYEF MXYO RVCKQ. FHB RNXA JCRB YM FHB MYXLB CJ N INFHPNV FY ONKV NWCZCFCBJ JYOB LYKJCRBX FY WB EKKNFEXNZ. HB WBLNOB JY IYPBXMEZ… FHB YKZV FHCKQ HB PNJ NMXNCR YM PNJ ZYJCKQ HCJ IYPBX, PHCLH BGBKFENZZV, YM LYEXJB, HB RCR. EKMYXFEKNFBZV, HB FNEQHF HCJ NIIXBKFCLB BGBXVFHCKQ HB AKBP, FHBK HCJ NIIXBKFCLB ACZZBR HCO CK HCJ JZBBI. CXYKCL. HB LYEZR JNGB YFHBXJ MXYO RBNFH, WEF KYF HCOJBZM.";
    char letter_count[26]; //Used to record the frequency of each letter in the cipher_text
    char ordered_letter_count[26]; //Used to order the above string from largest to smallest without changing it
    char cipher_frequency[26]; //String stores the alphabet that statistically is most likely to be the one used to encrypt
    char letter_frequency[] = "ETAOINSHRDLUCMWFGYPBVKJXQZ"; //ordered frequency that letters appear throughout the english language
    int i = 0, j = 0; //String countesr throughout bell=ow code
    for(i = 0; i < 26; i++) { //array initialisation
        letter_count[i] = 0;
        ordered_letter_count[i] = 0;
    }
    convert_case(cipher_text); //converts letters from lower to upper case (if required)
    for(i = 0; i < strlen(cipher_text); i++) {
        if(cipher_text[i] < 91 && cipher_text[i] > 64) { //If element of cipher_text is an uppercase letter
            int letter_value = cipher_text[i] - 65; //gives letter_value a value between 0 and 25 (corresponding A - Z)
            letter_count[letter_value]++; /*letter_value is a number between 0 and 25 so the element of letter_count (0 - 25) corresponding to the 
                                            letters (A - Z) is incremented to record the letter that appeared in cipher text*/
            ordered_letter_count[letter_value]++; //Same as above
        } 
    }
    for(i = 0; i < 25; i++) { // A 'bubble sort'
        for(j = 0; j < (25 - i); j++) {
            if(ordered_letter_count[j] < ordered_letter_count[(j+1)]){
                int temp = ordered_letter_count[j];
                ordered_letter_count[j] = ordered_letter_count[(j+1)];
                ordered_letter_count[(j+1)] = temp;
            }
        }
    }
   j = 0;
    for(i = 0; j < 26; i++) {
        if(letter_count[i] == ordered_letter_count[j]) {
            cipher_frequency[j] = i + 65;
            if(cipher_frequency[j] == cipher_frequency[(j-1)] && j != 0) {
                continue;
            } else if(cipher_frequency[j] == cipher_frequency[(j-2)] && j>=2) {
                continue;
            }
            j++;
            i = -1;
        }
    }
    j = 0;
    for(i = 0; j < strlen(cipher_text); i++) { //i.e executes for the entire cipher_text, all letters of the alphabet are examined for each letter of cipher_text
        if(cipher_frequency[i] == cipher_text[j]) { //if the letter of the cipher_frequency is the same as the letter in the cipher_text
            cipher_text[j] = letter_frequency[i]; //substitute the cipher_text letter for the letter in the standard alphabet that corresponds to the letter in cipher_key
            i = -1; //resets string counter to 0 once the increment is performed in the for loop
            j++;  /*increments the string counter for message_text, i.e causes the above if statement to examine the next letter in the message. 
                    Only increments when a letter of the message is encrypted*/
        } else if(cipher_text[j]>90 || cipher_text[j]<65) {  //executes if the element of the message is not an uppercase letter
            j++; //increments message_text, i.e moves onto the next element because this one is not a letter
            i = -1; //resets string counter to 0 once the increment is performed in the for loop
        }
    }
    printf("%s\n", cipher_text); //prints decrypted message to stdout
    for(j = 0; j < strlen(cipher_text); j++) { //i.e executes for the entire cipher_text, all letters of the alphabet are examined for each letter of cipher_text
        if(cipher_text[j] == 'H') { //if the letter of the cipher_frequency is the same as the letter in the cipher_text
            cipher_text[j] = 'R'; //substitute the cipher_text letter for the letter in the standard alphabet that corresponds to the letter in cipher_key
        } else if(cipher_text[j] == 'A'){
            cipher_text[j] = 'H';
        } else if(cipher_text[j] == 'N') {
            cipher_text[j] = 'A';
        } else if(cipher_text[j] == 'M') {
            cipher_text[j] = 'F';
        } else if(cipher_text[j] == 'F') {
            cipher_text[j] = 'P';
        } else if(cipher_text[j] == 'P') {
            cipher_text[j] = 'M';
        } else if(cipher_text[j] == 'R') {
            cipher_text[j] = 'N';
        } else if(cipher_text[j] == 'B') {
            cipher_text[j] = 'K';
        } else if(cipher_text[j] == 'K') {
            cipher_text[j] = 'B';
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
    int x = (int) strlen(str);
    for(i=0; i<x; i++){
        if(str[i]>96 && str[i]<123) {
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