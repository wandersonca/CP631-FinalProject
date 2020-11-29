#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "dictionary/dictionary.h"
#include "bruteforce/bruteforce.h"


void help()
{
    printf("HPC Password Cracker Help:\n");
    printf("--verbose (-v): verbose output\n");
    //TODO: add the rest of the options
}

int main(int argc, char **argv)
{
    int c;
    // Flags
    int verbose_flag = 0;
    int bruteforce_flag = 0;
    int dictionary_flag = 0;
    int character_length = 4;
    char password_hash[65] = "";
    char bruteforce_characters[256] = "";
    char dictionary_path[256] = "";

    while (1)
    {
        // Used for parsing long options (--long-option)
        static struct option long_options[] =
            {
                {"verbose", no_argument, 0, 'v'},
                {"password", required_argument, 0, 'p'},
                {"dictionary", required_argument, 0, 'd'},
                {"bruteforce", no_argument, 0, 'b'},
                {"uppercase", no_argument, 0, 'u'},
                {"lowercase", no_argument, 0, 'l'},
                {"numbers", no_argument, 0, 'n'},
                {"symbols", optional_argument, 0, 's'},
                {"character-length", required_argument, 0, 'c'}
            };

        /* getopt_long stores the option index here. */
        int option_index = 0;

        c = getopt_long(argc, argv, "vp:d:bulns::c:", long_options, &option_index);

        /* Detect the end of the options. */
        if (c == -1)
            break;

        switch (c)
        {
        case 'v':
            verbose_flag=1;
            break;
        case 'p':
            strcpy(password_hash,optarg);
            break;
        case 'd':
            dictionary_flag=1;
            strcpy(dictionary_path,optarg);
            break;
        case 'b':
            bruteforce_flag=1;
            break;
        case 'u':
            strcat(bruteforce_characters, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
            break;
        case 'l':
            strcat(bruteforce_characters, "abcdefghijklmnopqrstuvwxyz");
            break;
        case 'n':
            strcat(bruteforce_characters, "0123456789");
            break;
        case 's':
            if(optarg == NULL)
            {
                // TODO?:  Does % in this string need to be escaped? E.g., %% or is it just the editor picking up on this?
                strcat(bruteforce_characters, "~!@#$%^&*()_+");
            } 
            else 
            {
                strcat(bruteforce_characters, optarg);
            }
            break;
        case 'c':
            character_length = atoi(optarg);
            break;
        case '?':
            help();
            break;

        default:
            abort();
        }
    }

    int result;

    // TODO: make these mutually exclusive... 
    if(dictionary_flag)
    {
        result = dictionary_crack(password_hash, dictionary_path, verbose_flag);
    }

    if(bruteforce_flag) 
    {
        result = bruteforce_crack(password_hash, bruteforce_characters, character_length, verbose_flag);
    }
    exit(result);
}