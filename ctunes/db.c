/* ============================

	cTunes 1.8
	C Programming exercise
	
	Kailash Nadh, http://kailashnadh.name

============================ */

#include "ctunes.h"

// == variable declarations
FILE *db_fp;							// file pointer
const char *db_file = "data/tunes.dat";	// db file
Tune **db_tunes = NULL;
int db_size = 0;

// ====================================================

// read
void dbOpen() {

	int go;

	// open the data file
	db_fp = fopen(db_file,"rb");
	if(db_fp == NULL) {
		printf("Failed opening db - %s", db_file);
		exit(0);
	}

	// read the records
	db_size = 0; go = 1;

	do {

		// allocate memory for the dynamic array of structs (Tune)
		db_tunes = (Tune **)realloc(db_tunes, (db_size + 1) * sizeof(Tune *));
		db_tunes[db_size] = (Tune *) malloc(sizeof(Tune));


		// read the data structures from the file, one by one
		go = fread(db_tunes[db_size], sizeof(Tune), 1, db_fp);


		if(go != 1) {
			free(db_tunes[db_size]);
			break;
		}

		//printf("val-%d : %s\n", go, db_tunes[db_size]->title);

		// increment the db size
		db_size++;

	} while(go == 1);

	fclose(db_fp);
}

// delete a record
void dbDelete(int key) {

	db_fp = fopen(db_file, "wb");

	int i;
	for(i=0; i<dbSize(); i++) {
		if((i+1) != key) {
			fwrite(db_tunes[i], sizeof(Tune), 1, db_fp);
		}
	}

	fclose(db_fp);
}

// save the database
void dbSave() {
	db_fp = fopen(db_file, "wb");

	int i;
	for(i=0; i<dbSize(); i++) {
		fwrite(db_tunes[i], sizeof(Tune), 1, db_fp);
	}

	fclose(db_fp);
}

// add a record
void dbAdd(Tune *newtune) {
	db_fp = fopen(db_file, "ab");
	fwrite(newtune, sizeof(Tune), 1, db_fp);
	fclose(db_fp);
}


// safely close the database and free the memory
void dbClose() {
	int i;
	for(i = 0; i < dbSize(); i++) {
		free(db_tunes[i]);
		i++;
	}
	free(db_tunes);
}

// get the db filename
const char* dbFile() {
	return db_file;
}

// get the db size (number of records)
int dbSize() {
	return db_size;
}


// get the db data size in bytes
float dbDataSize() {
	return (sizeof(Tune) * dbSize());
}

