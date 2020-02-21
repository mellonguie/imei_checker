/**
  This program enables to check the
  validity of an IMEI or IMEISV string

  Autor : Jean Prince MELLO NGUIE
  Creation date : 10/20/2019
  Update date : 02/21/2020
  Revision : v1.0.1
 **/

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

	ret = imei_imeisv_checking(argv[1]);
	if (ret != 0) {
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

