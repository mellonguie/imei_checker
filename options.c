/* 
 * This module contains the definition of functions
 * which handle the options.
 */

/* Autor : MELLO NGUIE Jean Prince
 * Creation date : 20/10/2019
 * Update date   : XX/XX/XXXX
 * Revision      : 1.0.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*#include <getopt.h>*/
#include <ctype.h>

#include "options.h"

void print_help(void)
{
	fprintf(stdout, "./imei_imeisv_checking <my-imei-imeisv>\n");
}

void print_version(void)
{
	fprintf(stdout, "imei_imeisv_checking %s\n\n\nWritten by %s.\n", RELEASE, AUTOR);
}

#if 0
void print_info(char **argv)
{
	fprintf(stderr, "Try '%s -h' for more information.\n", argv[0]);
}

int parsing_options(int argc, char **argv)
{
	int opt;
	int n = 0;

	while ((opt = getopt(argc, argv, "hvi:")) != -1)
	{
		n++; /* enable to know if an option has been found */
		switch (opt) {
			case 'h' :
				print_help();
				break;

			case 'v' :
				print_version();
				break;

			case 'i' :
				filename = optarg;
				break;
			default :
				print_info(argv);
				return -1;
        }
    }

    if ((opt == -1) && (n == 0))
    {
        print_info(argv);
    }
    
    return opt;
}
#endif

#if 0
int get_long_options(int argc, char **argv)
{
    int n = 0;
    int opt;
    int opt_idx;
    static struct option long_options[] = {
                   {"help",     no_argument,       0, 'h'},
                   {"version",  no_argument,       0, 'v'},
                   {"in-file",  required_argument, 0, 'i'},
               };

    while ((opt = getopt_long(argc, argv, "hvqw:i:s", long_options, &opt_idx)) != -1)
    {
        n++; /* enable to know if an option has been found */
        switch (opt) {
            case 'h' :
                print_help();
                break;

            case 'v' :
                print_version();
                break;

            case 'i' :
                filename = optarg;
                return opt;
                /*pcap_fd = pcap_open_offline(optarg, errbuf);
                if (pcap_fd == NULL)
                {
                    pcap_perror(pcap_fd, errbuf);
                    return EXIT_FAILURE;
                }

                printf("file opened with success !\n");

                pcap_close(pcap_fd);*/
                break;

            case 's' :
                return opt;
                break;

            case '?' :
                break;

            default :
                print_info(argv);
        }
    }

    if ((opt == -1) && (n == 0))
    {
        print_info(argv);
    }
    
    return opt;
}
#endif

void tac_extraction(char *data) {
	int i;
	fprintf(stdout, "TAC: ");
	for (i = 0; i < TAC_STR_LEN; i++) {
		fprintf(stdout, "%c", data[i]);
	}
    fprintf(stdout, "\n");
}

void snr_extraction(char *data) {
	int i;
	fprintf(stdout, "SNR: ");
	for (i = TAC_STR_LEN; i < TAC_STR_LEN + SNR_STR_LEN; i++) {
		fprintf(stdout, "%c", data[i]);
	}
    fprintf(stdout, "\n");
}

char luhn_check_digit(char *data, uint32_t len) {
	uint32_t i;
	/*int conv;*/
	char cd = '0';
	int *tmp1 = malloc(len * sizeof(len));
	int *tmp2 = malloc(len * sizeof(len));
	memset(tmp1, 0, len);
	memset(tmp2, 0, len);

	/* Convert each char to int */
	for (i = 0; i < len; i++) {
		tmp1[i] = data[i] - '0';
		fprintf(stdout, "[%d]", tmp1[i]);
	}
    fprintf(stdout, "\n");

	/* Double value of odd index */
	for (i = len-1; i > 0; i--) {
		if (i % 2 == 1) {
			tmp2[i] = tmp1[i] * 2;
		} else {
			tmp2[i] = tmp1[i];
		}
	}
	tmp2[i] = tmp1[i];

	/* Check values */
	for (i = 0; i < len; i++) {
		fprintf(stdout, "[%d]", tmp2[i]);
	}
    fprintf(stdout, "\n");



	free(tmp1);
	free(tmp2);
	return cd;
}

int imei_imeisv_checking(char *data) {
	size_t i;
	uint32_t nb_digits = 0;
	size_t data_len = strlen(data);
	
	/* Check the data len */
	if (data_len < IMEI_STR_LEN-1 || data_len > IMEISV_STR_LEN) {
		fprintf(stderr, "The string you have enter cannot be an IMEI or IMEISV !\n");
		return -1;
	}

	/* Check if the string is composed by digits only */
	for (i = 0; i < data_len; i++) {
		if (isdigit(data[i])) {
			nb_digits++;
		} else {
			fprintf(stderr, "'%c' at index %lu is not a digit !\n", data[i], i);
			return -1;
		}
	}

	fprintf(stdout, "IMEI/IMEISV: %.*s\n", nb_digits, data);

	/* Extract TAC (Type Allocation Code) */
	tac_extraction(data);

	/* Extract SNR (Serial Number) */
	snr_extraction(data);
	
	
	if (nb_digits == IMEI_STR_LEN-1) { /* We should complement IMEI by a Check Digit (CD) */
		luhn_check_digit(data, nb_digits);
	}

	if (nb_digits == IMEI_STR_LEN) { /* The IMEI lenght is OK but not yet check */
		fprintf(stdout, "IMEI: %.*s\n", nb_digits, data);
		fprintf(stdout, "CD: %c\n", data[nb_digits-1]);
	}

	if (nb_digits == IMEISV_STR_LEN) { /* We should extract IMEI from IMEISV
										  and complement by a Check Digit (CD) */
		fprintf(stdout, "IMEISV: %.*s\n", nb_digits, data);
		fprintf(stdout, "SVN: %.*s\n", 2, &data[nb_digits-2]);
	}

	return 0;
}
