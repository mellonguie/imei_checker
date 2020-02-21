/**
 * Autor : Jean Prince MELLO NGUIE 
 * Creation date : 10/20/2019
 * Update date   : 02/21/2020
 * Revision      : 1.0.1
 */

#ifndef OPTIONS_H
#define OPTIONS_H

#include <stdint.h>

#define TAC_STR_LEN		8
#define SNR_STR_LEN		6

#define IMEI_STR_LEN	15
#define IMEISV_STR_LEN	16


/* Global variable */
char *my_imei_imeisv;

/* Functions prototype */
void print_help(void);
void tac_extraction(char *data);
void snr_extraction(char *data);
int imei_imeisv_checking(char *data);

#endif /* OPTIONS_H */
