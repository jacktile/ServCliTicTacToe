/**
 *
 * Following the tutorial from https://developer.ibm.com/technologies/security/tutorials/l-openssl
 *
 *
 * *//

// headers 
#include "openssl/bio.h"
#include "openssl/ssl.h"
#include "openssl/err.h"

int main()
{
	// initializing OpenSSL
	SSL_load_error_strings();
	ERR_load_BIO_strings();
	OpenSSL_add_all_algorithms();

	BIO * bio;
	
	bio = BIO_new_connect("hostname:port"); 	// change this to respective port
	if (bio == NULL)
	{
		// handle error
	}


	if (BIO_do_connect(bio) <= 0)
	{
		// handle failed connection
	}

	// attempting to read from the connection 
	int x = BIO_read(bio, buf, len);
	if (x == 0)
	{
		// handle the closed connection
	} else if (x < 0)
	{
		if (!BIO_should_retry(bio))
		{
			// handle failed read
		}

		// for handling the retry
	}


	// attempting to write to the connection 
	if (BIO_write(bio, buf, len) <= 0)
	{
		if(!BIO_should_retry(bio))
		{
			// handle the failed write
		}

		// handle the retry
	}

	// closing the connection 
	// --- * for reuse
	BIO_reset(bio);

	// to free from memory: BIO_free_all(bio);	

	return 0;
}
