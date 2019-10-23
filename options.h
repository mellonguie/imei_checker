/* 
 * This header contains prototypes of functions which
 * handle the options
 */

/* Autor : Jean Prince MELLO NGUIE 
 * Creation date : 20/10/2019
 * Update date   : XX/XX/XXXX
 * Revision      : 1.0.0
 */

#ifndef OPTIONS_H
#define OPTIONS_H
#include <stdint.h>

#define AUTOR   "Jean Prince MELLO NGUIE"
#define RELEASE "1.0.0"

#define TAC_STR_LEN		8
#define SNR_STR_LEN		6

#define IMEI_STR_LEN	15
#define IMEISV_STR_LEN	16

#define DEBUG	1

/* Global variables */
extern char *optarg;
char *my_imei_imeisv;

/* Functions prototype */
void print_help(void);
void print_version(void);
void print_info(char **argv);

/*int parsing_options(int argc, char **argv);*/
void tac_extraction(char *data);
void snr_extraction(char *data);
int imei_imeisv_checking(char *data);
#endif /* OPTIONS_H */
