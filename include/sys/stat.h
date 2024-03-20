#ifndef _STAT_H
#define _STAT_H

#include <sys/types.h>

/*!  \struct struct stat
     \brief Struttura dati che contine le informazioni su di un file
 */
struct stat {
	dev_t     st_dev; /**< device id del file*/
	
	uid_t     st_uid; /**< user id del file*/	
	gid_t     st_gid; /**< group id del file*/
	
	off_t	  st_size; /**< Dimensione del file */
};


int stat(const char *, struct stat *);

#endif