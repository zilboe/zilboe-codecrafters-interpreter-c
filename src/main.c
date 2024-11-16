#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char *read_file_contents(const char *filename);
int scanner_process(const char *content);
int main(int argc, char *argv[])
{
    // Disable output buffering
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    if (argc < 3)
    {
        fprintf(stderr, "Usage: ./your_program tokenize <filename>\n");
        return 1;
    }

    const char *command = argv[1];
    if (strcmp(command, "tokenize") == 0)
    {
        // // You can use print statements as follows for debugging, they'll be visible when running tests.
        // fprintf(stderr, "Logs from your program will appear here!\n");

        char *file_contents = read_file_contents(argv[2]);

        // Uncomment this block to pass the first stage
        if (strlen(file_contents) > 0)
        {
            int exits = scanner_process(file_contents);
            // fprintf(stderr, "Scanner not implemented\n");
            exit(exits);
        }
        printf("EOF  null\n"); // Placeholder, remove this line when implementing the scanner

        free(file_contents);
    }
    else
    {
        fprintf(stderr, "Unknown command: %s\n", command);
        return 1;
    }

    return 0;
}
const char *skip_tab = "<|TAB|>";
const char *skip_space = "<|SPACE|>";
int scanner_process(const char *content)
{
    unsigned char lines = 1;
    unsigned char exits = 0;
    unsigned char euqal = 0;
    unsigned char skip_line = 0;
    for (int i = 0; i < strlen(content); i++)
    {
        printf("ch = %c\n", content[i]);
        if (strncmp(content + i, skip_tab, strlen(skip_tab)) == 0)
        {
            i = i + strlen(skip_tab)-1;
            continue;
        }
        if (strncmp(content + i, skip_space, strlen(skip_space)) == 0)
        {
            i = i + strlen(skip_space)-1;
            continue;
        }
        if (skip_line)
        {
            if (content[i] == '\n')
            {
                skip_line = 0;
                continue;
            }
        }
        if (i < strlen(content) - 1)
        {
            if (content[i] == '/' && content[i + 1] == '/')
            {
                skip_line = 1;
                i = i + 1;
                continue;
            }
            if (content[i] == '=' && content[i + 1] == '=')
            {
                printf("EQUAL_EQUAL == null\n");
                i = i + 1;
                continue;
            }
            if (content[i] == '!' && content[i + 1] == '=')
            {
                printf("BANG_EQUAL != null\n");
                i = i + 1;
                continue;
            }
            if (content[i] == '<' && content[i + 1] == '=')
            {
                printf("LESS_EQUAL <= null\n");
                i = i + 1;
                continue;
            }
            if (content[i] == '>' && content[i + 1] == '=')
            {
                printf("GREATER_EQUAL >= null\n");
                i = i + 1;
                continue;
            }
        }
        switch (content[i])
        {
        case '\n':
            skip_line = 0;
            lines++;
            break;
        case '/':
            printf("SLASH / null\n");
            break;
        case '<':
            printf("LESS < null\n");
            break;
        case '>':
            printf("GREATER > null\n");
            break;
        case '!':
            printf("BANG ! null\n");
            break;
        case '(':
            printf("LEFT_PAREN ( null\n");
            break;
        case ')':
            printf("RIGHT_PAREN ) null\n");
            break;
        case '{':
            printf("LEFT_BRACE { null\n");
            break;
        case '}':
            printf("RIGHT_BRACE } null\n");
            break;
        case '*':
            printf("STAR * null\n");
            break;
        case '.':
            printf("DOT . null\n");
            break;
        case ',':
            printf("COMMA , null\n");
            break;
        case '+':
            printf("PLUS + null\n");
            break;
        case '-':
            printf("MINUS - null\n");
            break;
        case ';':
            printf("SEMICOLON ; null\n");
            break;
        case '=':
            printf("EQUAL = null\n");
            break;
        default:
            fprintf(stderr, "[line %d] Error: Unexpected character: %c\n", lines, content[i]);
            exits = 65;
            break;
        }
    }
    printf("EOF  null\n");
    return exits;
}

char *read_file_contents(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error reading file: %s\n", filename);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *file_contents = malloc(file_size + 1);
    if (file_contents == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        return NULL;
    }

    size_t bytes_read = fread(file_contents, 1, file_size, file);
    if (bytes_read < file_size)
    {
        fprintf(stderr, "Error reading file contents\n");
        free(file_contents);
        fclose(file);
        return NULL;
    }

    file_contents[file_size] = '\0';
    fclose(file);

    return file_contents;
}
