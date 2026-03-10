#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isKeyword(char *word) {
    char keywords[15][10] = {"int","float","char","double","if","else","for","while","return","void","main","do","switch","case","break"};
    for (int i = 0; i < 15; i++) {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int main() {
    FILE *fp;
    char ch, str[20];
    int i = 0;

    fp = fopen("input.c", "r");
    if (fp == NULL) {
        printf("Error: Cannot open file.\n");
        return 0;
    }

    printf("Lexeme\t\tToken\n");
    printf("-----------------------------\n");

    while ((ch = fgetc(fp)) != EOF) {

        if (isspace(ch))
            continue;

        // Identifier or keyword
        if (isalpha(ch) || ch == '_') {
            i = 0;
            str[i++] = ch;
            while (isalnum(ch = fgetc(fp)) || ch == '_') {
                str[i++] = ch;
            }
            str[i] = '\0';
            ungetc(ch, fp);

            if (isKeyword(str))
                printf("%-15s -> Keyword\n", str);
            else
                printf("%-15s -> Identifier\n", str);
        }

        // Number constant
        else if (isdigit(ch)) {
            i = 0;
            str[i++] = ch;
            while (isdigit(ch = fgetc(fp))) {
                str[i++] = ch;
            }
            str[i] = '\0';
            ungetc(ch, fp);
            printf("%-15s -> Integer Constant\n", str);
        }

        // Operators
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' ||
                 ch == '=' || ch == '<' || ch == '>' || ch == '%') {
            printf("%-15c -> Operator\n", ch);
        }

        // Special symbols (punctuators)
        else if (ch == ';')
            printf("%-15c -> End of Statement\n", ch);
        else if (ch == '(')
            printf("%-15c -> Open Parenthesis\n", ch);
        else if (ch == ')')
            printf("%-15c -> Close Parenthesis\n", ch);
        else if (ch == '{')
            printf("%-15c -> Open Brace\n", ch);
        else if (ch == '}')
            printf("%-15c -> Close Brace\n", ch);
        else if (ch == '#')
            printf("%-15c -> Preprocessor Directive\n", ch);

        // Unknown / invalid characters
        else {
            // ignore valid punctuation like comma, space, quotes etc. if needed
            if (ch != ',' && ch != '"' && ch != '\'' && ch != '[' && ch != ']' && ch != '\\')
                printf("Error: Invalid symbol '%c' found.\n", ch);
        }
    }

    fclose(fp);
    return 0;
}
