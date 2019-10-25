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

#include "imei.h"

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

/* Convert each char to int */
void convert_str_to_int(char *data, int *res, uint32_t len) {
	uint32_t i;
	for (i = 0; i < len; i++) {
		res[i] = data[i] - '0';
	}
}


void double_odd_index(int *in, int *out, uint32_t len) {
	uint32_t i;
	for (i = len-1; i > 0; i--) {
		if (i % 2 == 1) {
			out[i] = in[i] * 2;
		} else {
			out[i] = in[i];
		}
	}
	out[i] = in[i];
}

#if DEBUG
void dump_int_array(int *tab, uint32_t len) {
	uint32_t i;
	for (i = 0; i < len; i++) {
		fprintf(stdout, "[%d]", tab[i]);
	}
    fprintf(stdout, "\n");
}
#endif

int get_nb_char_in_int(int *input, uint32_t len) {
	uint32_t i;
	char tab[3] = {0};
	size_t size_elem = 0;
	int nb_elem = 0;

	for (i = 0; i < len; i++) {
		sprintf(tab, "%d", input[i]);
        size_elem = strlen(tab);
#if DEBUG
		fprintf(stdout, "%d => sz=%lu\n", input[i], size_elem);
#endif
		nb_elem += size_elem;
	}

	return nb_elem;
}

void convert_int_to_str(int *input, char *output, uint32_t in_len, uint32_t out_len) {
	uint32_t i, j, k, o;
	char tab[3] = {0};
	size_t size_elem = 0;

	for (i = 0, o = 0; i < in_len || o < out_len; i++, o++) {
		sprintf(tab, "%d", input[i]);
        size_elem = strlen(tab);
#if DEBUG
		fprintf(stdout, "%d => sz=%lu\n", input[i], size_elem);
#endif
		if (size_elem == 1) {
			output[o] = tab[size_elem-1];
		} else {
			for (j = 0, k = o; j < (uint32_t)size_elem; j++, k++) {
				output[k] = tab[j];
				o = k;
			}
		}
	}
}

int sum_digits(char *input, int len) {
	int i;
	int sum = 0;

	for (i = 0; i < len; i++) {
		sum += input[i] - '0';
	}

	return sum;
}

char luhn_check_digit(char *data, uint32_t len) {
	uint32_t n_chr;
	/*int conv;*/
	char cd = '0';
	int sum;
	int next_high_val;
	int *tmp1 = malloc(len * sizeof(len));
	int *tmp2 = malloc(len * sizeof(len));
	char *tmp3;
	memset(tmp1, 0, len);
	memset(tmp2, 0, len);

	/* Convert a string to int */
	convert_str_to_int(data, tmp1, len);
#if DEBUG
	dump_int_array(tmp1, len);
#endif

	/* Double value of odd index */
	double_odd_index(tmp1, tmp2, len);
#if DEBUG
	dump_int_array(tmp2, len);
#endif

	n_chr = get_nb_char_in_int(tmp2, len);
	tmp3 = malloc(n_chr);
	memset(tmp3, 0, n_chr);

	/* Convert int to str */
    convert_int_to_str(tmp2, tmp3, len, n_chr);

	/* Sum all digits */
	sum = sum_digits(tmp3, n_chr);
	if (sum % 10 == 0) {
		cd = '0';
	} else {
		next_high_val = sum;
		do {
			next_high_val++;
		} while (next_high_val % 10 != 0);
		cd = (char)(next_high_val - sum);
	}

	free(tmp1);
	free(tmp2);
	free(tmp3);

	return cd;
}


char *imei_build(char *data, uint32_t len, char cd) {
	char *imei = NULL;
	char cd_arr[2] = {0};
	sprintf(cd_arr, "%c", (cd + '0'));

	imei = malloc(len + 3);
	if (imei == NULL) {
		return NULL;
	}

	strcat(imei, data);
	strcat(imei, cd_arr);

	return imei;
}

int imei_imeisv_checking(char *data) {
	size_t i;
	char cd;
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
		char *imei;
		size_t imei_len;
		cd = luhn_check_digit(data, nb_digits);
		fprintf(stdout, "CD: %d\n", cd);
		imei = imei_build(data, nb_digits, cd);
		imei_len = strlen(imei);
		fprintf(stdout, "IMEI: %.*s (%lu)\n", (int)imei_len, imei, imei_len);
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
