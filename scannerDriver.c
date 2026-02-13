// starter code for Simple_PL1 scanner
#include <stdio.h>  //for c I/o
#include <stdlib.h> // for exit()
#include <ctype.h>  // for isalpha(), isalnum(), ...
enum tokenType
{
    READ,
    WRITE,
    ID,
    NUMBER,
    LPAREN,
    RPAREN,
    SEMICOLON,
    COMMA,
    ASSIGN,
    PLUS,
    MINUS,
    TIMES,
    DIV,
    SCAN_EOF
};
char* mnemonic[] = { "READ", "WRITE", "ID", "NUMBER", "LPAREN", "RPAREN", "SEMICOLON", "COMMA",
                    "ASSIGN", "PLUS", "MINUS", "TIMES", "DIV", "SCAN_EOF" };
void lexical_error(char ch)
{
    fprintf(stderr, "Lexical Error. Unexpected character: %c.\n", ch);
}
char lexeme[256] = { '\0' };
unsigned int lexLen = 0;
FILE* src;
enum tokenType scan()
{
    static int currentCh = ' ';
    static int tempCh = ' ';
    char* reserved[2] = { "read", "write" };
    lexLen = 0; // clear lexeme buffer for each scan
    lexeme[0] = '\0';
    extern FILE* src; // pointer to FILE handle that binds to source file.
    if (feof(src))
    {
        return SCAN_EOF;
    }
    while ((currentCh = fgetc(src)) != EOF)
    {
        if (isspace(currentCh))
        {
            continue;
        }
        else if (isalpha(currentCh) || currentCh == '_')
        {
            lexeme[0] = currentCh;
            lexLen = 1;

            // build identifier lexeme
            for (tempCh = fgetc(src); isalnum(tempCh) || tempCh == '_';)
            {
                // adds character to lexeme where lexLen is the current length of the lexeme
                lexeme[lexLen++] = tempCh;
                // get next character
                tempCh = fgetc(src); 
            }
            lexeme[lexLen] = '\0'; // null terminate lexeme so that it knows its the end of the lexeme
            ungetc(tempCh, src); // put back character that is not a alpha/digit or ‘_’
            // see if lexeme is a reserved word, if not, return ID.
            if (strcmp(lexeme, reserved[0]) == 0)
            {
                return READ;
            }
            else if (strcmp(lexeme, reserved[1]) == 0)
            {
                return WRITE;
            }
            else
            {
                return ID;
            }
        }
        else if (isdigit(currentCh))
        {
            // build lexeme for number
            // finish fixing lexeme string, ungetc the last character read that is not a digit and then return NUMBER
            lexeme[0] = currentCh;
            lexLen = 1;
            // reads the numbers
            while (isdigit(tempCh = fgetc(src))) {
                lexeme[lexLen++] = tempCh;
            }

            //check if it could possibly be an ID that starts with a numer like 10x_5y
            if (isalpha(tempCh) || tempCh == '_') {
                lexeme[lexLen++] = tempCh;
                while (isalnum(tempCh = fgetc(src)) || tempCh == '_') {
                    lexeme[lexLen++] = tempCh;
                }
                lexeme[lexLen] = '\0';
                ungetc(tempCh, src);
                return ID;
            }

            // if just pure numbers, then return NUMBER
            lexeme[lexLen] = '\0';
            ungetc(tempCh, src);
            return NUMBER;
        }
        else if (currentCh == '+')
        {
            return PLUS;
        }
        else if (currentCh == '-')
        {
            return MINUS;
        }
        else if (currentCh == '*')
        {
            return TIMES;
        }
        else if (currentCh == '/')
        {
            return DIV;
        }
        else if (currentCh == ';')
        {
            return SEMICOLON;
        }
        else if (currentCh == ',')
        {
            return COMMA;
        }
        else if (currentCh == '(')
        {
            return LPAREN;
        }
        else if (currentCh == ')')
        {
            return RPAREN;
        }
        else if (currentCh == ':')
        {
            // verify if next character is '='
            tempCh = fgetc(src);
            if (tempCh == '=')
            {
                return ASSIGN;
            }
            else
            {
                lexical_error(currentCh);
            }
        }
        else
        {
            lexical_error(currentCh);
        }

    }
    return SCAN_EOF;
}

int main(int argc, char* argv[])
{
    extern FILE* src;
    enum tokenType currentToken;
    if (argc > 1)
    { // should be better testing for proper number of arguments, but not required for this project
        if (fopen_s(&src, argv[1], "r"))
        {
            fprintf(stderr, "Error opening source file: %s ", argv[1]);
            exit(1);
        }
    }
    while ((currentToken = scan()) != SCAN_EOF)
    {
        // finish body for displaying the string version of the internal token name and
        // also print lexeme if the token is a ID or NUMBER. Do not print lexeme for the other tokens.
        if (currentToken == ID)
        {
            printf("%s, %s\n", mnemonic[currentToken], lexeme);
        }
        else if (currentToken == NUMBER) {
            int number = atoi(lexeme);
            printf("%s, %i\n", mnemonic[currentToken], number);
        }
        else
        {
            printf("%s\n", mnemonic[currentToken]);
        }
    }
    fclose(src);
    return 0;
} // end driver