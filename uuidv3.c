/** @file uuidv3.c
 *  @brief Generate UUID version 3. 
 *  
 *  $gcc uuidv3.c -o uuid -lssl -lcrypto
 *  @author Salil Dinesh Apte
 *  @bug    No known bugs
 */

/*
 *#####################################################################
 *  Initialization block
 *  ---------------------
 *  This block contains initialization code for this particular file.
 *  It typically contains Includes, constants or global variables used
 *  throughout the file.
 *#####################################################################
 */

/* ---Standard includes--- */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <openssl/sha.h>

/*
 *#####################################################################
 *  Process block
 *  -------------
 *  Solve all your problems here 
 *#####################################################################
 */

/**
 * @brief      Function for SHA-256 hashing of a string
 *
 * @param[in]  hash          The input string is combination of MAC address and timestamp 
 * @param      outputBuffer  The buffer used for hashing
 *
 * @return     NA
 */
void sha256_hash_string (unsigned char hash[SHA256_DIGEST_LENGTH], char outputBuffer[32])
{
	/* This will store the UUID */
	char *uuid=malloc(36);

	/* For loop for SHA-256 hashing of string */
	for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
	{
		sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
	}/* Ending for loop */

	/* Terminating the hashed string */
	outputBuffer[32] = 0;
	    
	/* Add four hyphen '-' characters 
	* to finally generate the UUID
	*/ 
	memset(uuid, '\0', 37);
	/* copy str till 8 places */
	strncpy(uuid, outputBuffer, 8);

	/* then insert hyphen by concatenation*/
	strcat(uuid, "-");
  
        /* similarly others follow */
	strncat(uuid, &outputBuffer[8], 4);

	strcat(uuid, "-");

	strncat(uuid, &outputBuffer[12], 4);

	strcat(uuid, "-");

	strncat(uuid, &outputBuffer[16], 4);

	strcat(uuid, "-");

	strncat(uuid, &outputBuffer[20], 12);

	/* Printing generated UUID */
	printf("UUID:%s\n",uuid);

	/* Free memory for uuid since its no longer needed */
	free(uuid);
}

/**
 * @brief      Generate UUIDv3
 *
 * @return     -1 if error in opening mac.txt file, else 0 for success
 */

int gen_uuidv3c()
{
	/* Saving system MAC address to an output file
	enp0s3 is the device name
	This may be different for every device or docker container */
	system("cat /sys/class/net/enp0s3/address > mac.txt");

	/* File pointer to work with file */
	FILE *fp;

	/* Declarations for components of UUIDv3
	MAC address is namespace
	UNIX timestamp as the name
	intBuffer for storing timestamp as a string
	combine for concatenating MAC address and timestamp
 	buffer for SHA-256 hash */
   	char mac[18],intBuffer[11];
	char *combine=malloc(28);
	int timeStamp=(int)time(NULL);
	static unsigned char buffer[32];
	

   	/* opening file which contains mac address for reading */
   	fp = fopen("mac.txt" , "r");
   	if(fp == NULL) {
      		perror("Error opening file");
      		return(-1);
   	}

   	if( fgets (mac, 18, fp)!=NULL ) {
      		/* writing content to stdout */
		/* Printing MAC address */
		puts("MAC address:");
      		puts(mac);
   	}

	/* Closing the file mac.txt */
   	fclose(fp);

	/* Printing current timestamp */
	printf("Timestamp:%d\n",timeStamp);

	/* Combining MAC address and UNIX timestamp */
	strcat(combine,mac);

	/* Converting int timeStamp to char* using snprintf */
	snprintf(intBuffer, 11, "%d", timeStamp);

	strcat(combine,intBuffer);

	/* Checking if MAC address and Timestamp were combined correctly */
	printf("Concatenated string - %s\n",combine);
	
	/* Call to sha_hash_string function */
	sha256_hash_string(combine, buffer);
	
	return 0;
}

/**
 * @brief      main 
 * Driver program for calling gen_uuidv3() function
 *
 * @return     0
 */

int main(){
	/* call to gen_uuidv3c function */
	gen_uuidv3c();
	
	/* To check if program executed successfully */
  	return 0;
}
