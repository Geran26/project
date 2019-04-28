/*Geran Dunlop's (3324608) code for the ENGG1003 Assignment 1.  */

#include <stdio.h> 
#include <string.h>

void rotation_encryption(void); //Performs the entire rotation encryption
void rotation_decryption(void); //Performs the entire rotation decryption
void substitution_encryption(void); //Performs the entire substitution encryption
void substitution_decryption(void); //Performs the entire substitution decryption
void rotation_decryption_of_unknown(void); // rotation decryption -- no key required
void substitution_decryption_of_unknown(void); // substitution decryption -- no cipher alphabet required
void convert_case(char *str); // Converts lowercase letters to uppercase letters
void e(char *str, int y, int x); //Implements the rotation encryption algorithm
void d(char *str, int y, int x); //Implements the Rotation decryption algorithm
int maximum_element_location(char *str); //Returns the number of the element of the array with the largest number
int counting_phrases(char *str, int x, char *word); //Counts how many times a substring is found in a string

int main() 
{
    int menu_select; //user-friendly menu selection
    printf("Please select which function you wish to perform: \n");
    printf("Enter 1 for rotation encrytion\n");
    printf("Enter 2 for rotation decryption\n");
    printf("Enter 3 for substitution encryption\n");
    printf("Enter 4 for substitution decryption\n");
    printf("Enter 5 for rotation decryption without a key\n");
    printf("Enter 6 for substitution decryption without a key\n");
    scanf("%d", &menu_select);
    switch (menu_select) {
        case 1: rotation_encryption(); break; //performs rotation encryption of a known message. Needs a key
        case 2: rotation_decryption(); break; //performs rotation decryption of a given encrypted message. Needs a known key
        case 3: substitution_encryption(); break; //performs substitution encryption of a known message and key
        case 4: substitution_decryption(); break; //performs substitution decryption of a given encrypted message. Needs known key
        case 5: rotation_decryption_of_unknown(); break; //Decrypts an unknown text where you do not know the rotation amount
        case 6: substitution_decryption_of_unknown(); break; //Decrypts an unknown text where you do not know the letter substitutions
        default: printf("Something went wrong\n"); //executes when a number 1 - 6 is not entered
    }
    return 0;
}

/*Encryption of known message using rotation encryption. This fucntion takes no arguments and returns no values, it simlpy makes 
the switch statement above neater. Reads text from a file and stores it character by character in an array. It then reads a key 
value from the same file. A case conversion is then performed using a function defined and described further down my code. The 
encryption algorithm is then implemented using the e() function (defined and described further below). The encrypted message is
then printed to both stdout and the file. This function requires the the message all be written on the first line of the file,
else it wont be wholly encrypted*/
void rotation_encryption(void)
{
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

/*Decryption of known message using rotation decryption. This fucntion takes no arguments and returns no values, it simlpy makes 
the switch statement above neater. First it reads text from a file and stores it character by character in an array. It then reads 
a key value from the same file. A case conversion is then performed using a function defined and described further down my code. 
The decryption algorithm is implemented using the d() function which is defined and described further down my code. The decrypted
string is then printed to stdout and the file. This function requires the the message all be written on the first line of the file,
else it wont be wholly decrypted*/
void rotation_decryption(void)
{
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

/*Encryption of a known message with known key using substitution encryption. This fucntion takes no arguments and returns no values, it simlpy makes 
the switch statement above neater. First it reads text from a file and stores it character by character in an array. It then reads
the next 26 chars which form the cipher key used to make the substitutions. The function the compares the message text to the
alphabet and then makes the corresponding substitutions using the cipher key. The encrypted message is then printed to stdout and
the file. Similar to the other functions this one requires that the message to be encrypted is on the first line of the file and
that there is 26 letters on the second line to use as the cipher key. */
void substitution_encryption(void)
{
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

/*Decryption of a known cipher text with a known cipher alphabet (key) using substitution decryption. This fucntion takes no 
arguments and returns no values, it simlpy makes the switch statement above neater. First it reads text from a file and stores it 
character by character in an array. It then reads the next 26 chars which form the cipher key used to make the substitutions. The 
function the compares the message text to the cipher key and then makes the corresponding substitutions using the standard
alphabet, which is hard coded. The decrypted message is then printed to stdout and the file. Again this function requires the 
input text to all be written on the first line of the file. The cipher key is then on the second line of the file. */
void substitution_decryption(void)
{
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

/*Decryption of a text using rotation decryption without a key. This fucntion takes no arguments and returns no values, it 
simlpy makes the switch statement above neater. First it reads text from a file and stores it character by character in an array.
It the converts the case to uppercase if required. This decryption code uses the 'brute force' technique. Each rotation amount is 
used to 'decrypt' the message, this 'decrypted' message is then tested for 6 words which are extremely common in the english 
language. The total frequency of all the words across all the rotations is recorded in the word_count array. The largest number
is then determined and that element (i.e rotation amount) is used to decode the entire text. This decryption is then printed
to stdout and the file. If none of these words are found a simple error message is printed. This function requires that the 
message text is on the first line of the file. */
void rotation_decryption_of_unknown(void)
{
    FILE *fp;
    fp = fopen("RotDecryptUnknown.txt", "r+"); //Opening file to read input and the recieve output
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
    int y = 0; // Rotation amount, changed further down code
    char word_count[26]; //Array will be used to record the word count of the words below
    convert_case(cipher_text); //converts form lowercase to uppercase (If needed)
    for(y = 0; y <= 25; y++) { // i.e for all rotation amounts (as there is only 25 possible rotations)
        d(cipher_text, y, count); //decryption function, see below for definition and description
        char the[] = " THE "; //6 strings are the 6 words we are looking for in our decrypted text. Spaces are important as they help the compiler...
        char it[] = " IT "; //...recognise when the word is by itself (i.e not apart of another word)
        char and[] = " AND ";
        char of[] = " OF "; //These words are all some of the most common words in the English Language 
        char is[] = " IS ";
        char to[] = " TO ";
        word_count[y] = counting_phrases(cipher_text, count, the) + counting_phrases(cipher_text, count, it) + counting_phrases(cipher_text, count, and) + counting_phrases(cipher_text, count, of) + counting_phrases(cipher_text, count, is) + counting_phrases(cipher_text, count, to);
        /* Above line: counting_phrases (see function definition below) counts the occurence of each word in the 'decrypted' string. The sum of the occurence
        of each word is taken and assigned to the element of array word_count corresponding to the rotation amount where each occurence was recorded */
        e(cipher_text, y, count); /*Encryption function, see function definition and description below, cipher_text needs to be re-encrypted to be decrypted 
                                on the next loop*/
    }
    y = maximum_element_location(word_count); /*The maximum element of word_count tells us which rotation returns a decryption with the most of these 6 words, 
                                                and it can be inferred that this rotation (i.e y) will give the full decryption of the text*/
    if(y >= 1){ /*i.e if the rotation is anything but a rotation by 0 (staying the same), above function maximum_element_location will return 0 if none of these 
                words are found in any of the rotation decryptions.*/
        d(cipher_text, y, count); //decryption function see function definition below
        printf("%s\n", cipher_text); //Prints cipher_text (which is now decrypted) to stdout
        fprintf(fp, "\n%s\n", cipher_text); //Prints decrypted cipher_text to the file
    } else { // Executes if none of these words are found in the text
        printf("None of these words appear in this text.");
    }
    fclose(fp); //closes the file
}

/*Decryption of a text using substitution decryption without a cipher key. This fucntion takes no arguments and returns no values, 
it simlpy makes the switch statement above neater. First it reads text from a file and stores it character by character in an array.
It then converts the case to uppercase if required. This decryption uses a statistical analysis attack to determine the most common
letters in the encrypted message. The amount of each letter in the cipher text is recorded in two arrays, one of which is then 
ordered from largest to smallest Another array then gets filled with the letters in order of their frequency in the cipher text. 
This is then used as the cipher key. The cipher text is compared with this key and the appropriate letters of a hard coded regular
letter frequency are substituted. The decrypted message is then printed to stdout and the file for a visual analysis and from there
further substitutions counld be made manually. This function requires that the cipher text be on the first line of the file. This 
method of statistical analysis will be fairly accurate for large sections of text, accurate enough to determine further 
substitutions for medium length text but fairly inaccurate for small sections of text as the frequency of the letters is unlikely
to correspond with the standard statistical frequency of each letter.*/
void substitution_decryption_of_unknown(void)
{
    FILE *fp;
    fp = fopen("SubDecryptUnknown.txt", "r+"); //Opening file to read input and the recieve output
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
    char letter_count[26]; //Used to record the frequency of each letter in the cipher_text
    char ordered_letter_count[26]; //Used to order the above string from largest to smallest without changing it
    char cipher_frequency[26]; //String stores the alphabet that statistically is most likely to be the one used to encrypt
    char letter_frequency[] = "ETAOINSHRDLUCMWFGYPBVKJXQZ"; //ordered frequency that letters appear throughout the english language
    i = 0; //resetting string counter for use below
    int j = 0; //String counters throughout bellow code
    for(i = 0; i < 26; i++) { //array initialisation, needed as these arrays will be incremented
        letter_count[i] = 0;
        ordered_letter_count[i] = 0;
    }
    convert_case(cipher_text); //converts letters from lower to upper case (if required)
    for(i = 0; i < count; i++) {
        if(cipher_text[i] < 91 && cipher_text[i] > 64) { //If element of cipher_text is an uppercase letter
            int letter_value = cipher_text[i] - 65; //gives letter_value a value between 0 and 25 (corresponding A - Z)
            letter_count[letter_value]++; /*letter_value is a number between 0 and 25 so the element of letter_count (0 - 25) corresponding to the 
                                            letters (A - Z) is incremented to record the letter that appeared in cipher text*/
            ordered_letter_count[letter_value]++; //Same as above
        } 
    }
    for(i = 0; i < 25; i++) { // A 'bubble sort'
        for(j = 0; j < (25 - i); j++) { /*This loop executes one less time, each time i is incremented. Each iteration moves the 
                                          smallest number in the array to the right until the numbers are ordered in descending 
                                          order from left to right*/
            if(ordered_letter_count[j] < ordered_letter_count[(j+1)]){
                int temp = ordered_letter_count[j]; /*These 3 lines swap j and j+1 to get the largest number 
                                                    towards the 'left' of the array*/
                ordered_letter_count[j] = ordered_letter_count[(j+1)];
                ordered_letter_count[(j+1)] = temp;
            }
        }
    }
   j = 0; //resetting the string counter
   /*The below loops until the element of letter_count is equal to the element of ordered_letter_count (i.e referring to the 
   same letter). The two string counters are needed because element i of letter_count (0 - 25) corresponds to a letter (A = 0 - 
   Z = 25), element j of ordered_letter_count gives the order of the frequency of the letters, element 0 is the most frequent and
   element 25 is the least frequent. When this occurs the element j of cipher_frequency is given the ascii value of the 
   corresponding capital letter. This means that cipher_frequency gives the order of the letters (element j = 0 to j = 25) AND 
   gives the letters themselves (i+65 gives the ascii character of the letter corresponding to the element i of letter_count). The
   if statement then tests for if the frequency is the same. If the frequency is the same as the frequency of the element before
   then the if statement causes the loop to continue without incrementing j so as to search for the next letter with that frequency
   (if there is 2 equal frequencies then there must be two letters with that frequency). This will give us a string that 
   details the characters of the text in frequency order to use as our cipher key*/
   for(i = 0; j < 26; i++) {
        if(letter_count[i] == ordered_letter_count[j]) {
            cipher_frequency[j] = i + 65;
            if(cipher_frequency[j] == cipher_frequency[(j-1)] && j != 0) {
                continue;
            } else if(cipher_frequency[j] == cipher_frequency[(j-2)] && j>=2) {
                continue;
            }
            j++;
            i = -1; //set to minus 1 to allow for the increment that happens in the for loop
        }
    }
    j = 0; //resetting a string counter for use in the loop below
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
    fprintf(fp, "\n%s\n", cipher_text); //prints decrypted message to file
    fclose(fp); //closes file
}

/*Definition for function that converts the case of the message. For every element of the string
that has a ASCII value betweeen 96 and 123 (i.e the ASCII Values of lowercase letters) it takes
away 32, leaving values within the range of 65 to 90 (i.e the ASCII values of uppercase letters)
This only changes letters as other symbols (numbers, punctuation, white space) are outside the 
range of 96 to 123 in ASCII*/
void convert_case(char *str)
{
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
void e(char *str, int y, int x)
{
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
void d(char *str, int y, int x)
{
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

/*Definition of a function that returns the location of the largest number of a string (returns the first element, i.e 0 if the array is full of 0's). The
function argument is a pointer to the string of which you wish to find the location of the largest element. This function compares each element of the string 
to the previous largest element of the string to determine if it larger or not. if it is it replaces the 'maximum' variable. This replaced value is then used 
to compare against the remaining elements of the string. This continues until all elements of the stirng are tested. Whenever the maximum value is replaced 
the location is recorded as i (i.e the number of the element of the string). This value is returned once the final maximum value is determined.  */
int maximum_element_location(char *str)
{
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
int counting_phrases(char *str, int x, char *word)
{
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