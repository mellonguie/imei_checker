/* This program enables to check the validity of an IMEI or IMEISV string */
 
/* Autor : MELLO NGUIE Jean Prince
 * Creation date : 20/10/2019
 * Update date : X/XX/XXXX
 * Revision : v1.0.0 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>

#include "imei.h"

int main(int argc, char *argv[])
{
	int ret;

	/* Check the number of arguments */
	if (argc < 2) {
		print_help();
		return EXIT_FAILURE;
	}

	/* Parse options */
	/*opt = get_long_options(argc, argv);*/
	/*opt = parsing_options(argc, argv);
	if (opt >= 0) {
		return EXIT_FAILURE;
	}*/

	ret = imei_imeisv_checking(argv[argc-1]);
	if (ret != 0) {
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

