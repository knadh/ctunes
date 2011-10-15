/* ============================

	cTunes 1.8
	C Programming exercise
	
	Kailash Nadh, http://kailashnadh.name

============================ */

#include "ctunes.h"

extern char *menu_opts[];

// ============== declarations

void statistics();
void showAll();
void doSort(int opt);
int doSearch(int opt);
void diagnostics();
void delete();
void addRecord();

// ============== main function
int main() {

	int opt = 100;


	dbOpen();		// initialize the db

	menuInit();		// initialize the menu



	while(opt != 99) {
		opt = menuRun(opt);	// show the menu

		switch(opt) {

			// display all records
			case 1:
				showAll();
			break;

			// delete records
			case 2:
				delete();
			break;

			// add records
			case 3:
				addRecord();
			break;

			// show the sorting options
			case 4:
				opt = menuSort();
				if(opt != 0) {
					doSort(opt);
				}
				opt = 0;
			break;

			// show the searching options
			case 5:
				doSearch(menuSearch());
			break;

			// export data
			case 6:
				exportData(menuExport());
			break;

			// diagnostics
			case 7:
				diagnostics();
			break;

			// statistics
			case 8:
				statistics();
			break;

			
			// exit
			case 9:
				dbClose();	// safely close the db
				exit(0);
			break;
		}
	}
	return 0;
}

// print some useful statistics
void statistics() {
	PrintBr(); PrintLine();
	printf("cTunes version\t\t: %.2f\n", VERSION);
	printf("Db file\t\t\t: %s\n", dbFile());
	printf("Number of records\t: %d\n", dbSize() );
	printf("Size on disk\t\t: %.2f KB", (dbDataSize() / 1024) );
	PrintBr();
}


// show all records (formatted)
void showAll() {

	char x[3];

	PrintLine();
	printf("Displaying %d records", dbSize());
	PrintBr();

	// print the formatted column headers
	TunesHeaders();

	PrintLine();

	int i;
	for(i=0; i < dbSize(); i++) {

		printf("%d", (i+1));
		PrintTabs(4, numDigits(i+1));		// fixed with column

		printf("%s", db_tunes[i]->artist);
		PrintTabs(18, strlen(db_tunes[i]->artist));		// fixed with column

		printf("%s", strConcat(db_tunes[i]->title));
		PrintTabs(19, strlen(db_tunes[i]->title));		// fixed with column

		printf("%s", strConcat(db_tunes[i]->album));
		PrintTabs(19, strlen(db_tunes[i]->album));		// fixed with column

		printf("%s", db_tunes[i]->genre);
		PrintTabs(14, strlen(db_tunes[i]->genre));		// fixed with column

		printf("%d", db_tunes[i]->year);

		printf("\n");
	}
}

// sort
void doSort(int opt) {

	PrintLine();
	printf("Sorted.\n");

	TunesSort(opt, 1);	// selection sort
	dbOpen();
	TunesSort(opt, 2);	// bubble sort

	showAll();

	printf("\nTo view the metrics of this operation, please goto 'Diagnostics'");

	if(menuSortSave()) {				// write the changes to the file
		dbSave();
		printf("The sorted playlist has been saved.\n");
	} else {
		// reload the db, lose the changes
		dbOpen();
	}
}


// search
int doSearch(int opt) {

	char key[20], x[3], key_lower[10], target[50], target_lower[50];	// we only need a 10 chars long keyword
	int n = 0, year = 0;
	bool found = false;

	if(opt == 0) return 0;

	PrintLine();
	printf("Please enter a search key: ");
	getAstring(key, 20);
	PrintLine();

	strLower(key, key_lower);

	// simple, linear search algorithm
	int i;
	for(i=0; i < dbSize(); i++) {

		// it is not a good idea to put this switch here in the for loop, but for a simple program of this scale, it doesn't really matter
		// search options
		found = false;
		switch(opt) {
			case 1:	// artist
				strLower(db_tunes[i]->artist, target_lower);
			break;

			case 2:	// title
				strLower(db_tunes[i]->title, target_lower);
			break;

			case 3:	// album
				strLower(db_tunes[i]->album, target_lower);
			break;

			case 4:	// genre
				strLower(db_tunes[i]->genre, target_lower);
			break;

			case 5:	// year
				year = atoi(key);	// convert to integer
				if(year == db_tunes[i]->year) {
					found = true;
				}
			break;

		}
		if(opt != 5) {
			strcpy(target, target_lower);
			if(strstr(target, key_lower)) {
				found = true;					// check whether key_lower is present in the target string
			}
		}

		if(found == true) {
			printf("%d", (n+1));
			PrintTabs(4, numDigits(n+1));		// fixed with column

			printf("%s", db_tunes[i]->artist);
			PrintTabs(18, strlen(db_tunes[i]->artist));		// fixed with column

			printf("%s", strConcat(db_tunes[i]->title));
			PrintTabs(19, strlen(db_tunes[i]->title));		// fixed with column

			printf("%s", strConcat(db_tunes[i]->album));
			PrintTabs(19, strlen(db_tunes[i]->album));		// fixed with column

			printf("%s", db_tunes[i]->genre);
			PrintTabs(14, strlen(db_tunes[i]->genre));		// fixed with column

			printf("%d", db_tunes[i]->year);

			printf("\n");

			n++;
		}
	}
	if(n == 0) {
		printf("Sorry, no matches found\n");
	}
}

// diagnostics
void diagnostics() {

	int diag = 0;

	// metrics available?
	if(metrics.bubble_size == 0) {
		PrintMsg("> Please run a sort opertaion first to collect metrics");
	} else {
		diag = menuDiagnostics();

		if(diag == 4) {
			// view metrics on the screen

			PrintLine();
			printf("\t\t\tMetrics - sorting algorithms\n");
			PrintLine();
			PrintBr();

			printf("\tAlgorithm\t:\tSelection sort\n");
			printf("\tSorted by\t:\t%s\n", fieldByIndex(metrics.select_field));
			printf("\tData size\t:\t%d\n", metrics.select_size);
			printf("\tIterations\t:\t%d\n", metrics.select_count);
			printf("\tSwaps\t\t:\t%d\n", metrics.select_swaps);
			printf("\tExecution time\t:\t%.3f seconds\n", metrics.select_time);

			printf("\n\n");

			printf("\tAlgorithm\t:\tBubble sort\n");
			printf("\tSorted by\t:\t%s\n", fieldByIndex(metrics.bubble_field));
			printf("\tData size\t:\t%d\n", metrics.bubble_size);
			printf("\tIterations\t:\t%d\n", metrics.bubble_count);
			printf("\tSwaps\t\t:\t%d\n", metrics.bubble_swaps);
			printf("\tExecution time\t:\t%.3f seconds\n", metrics.bubble_time);
			
		} else {
			exportMetrics(diag);
		}
	}
}

// delete tunes
void delete() {

	int key = -1;
	char c[5];

	PrintLine();
	printf("\t\t\tDelete songs\n");
	PrintLine();
	PrintBr();

	showAll();
	printf("\n\nPlease enter the index of the song (1 - %d) delete or 0 to return: ", dbSize());
	getAstring(c, 5);

	key = atoi(c);

	if(key != 0)
	if(key < 1 || key > dbSize()) {
		PrintMsg("Sorry, you entered an incorrect index");
	} else {
		dbDelete(key);
		printf("\n%d. \"%s\" - has been deleted", key, db_tunes[key-1]->title);
		dbOpen();
	}
}

// add a record
void addRecord() {

	Tune *newtune = (Tune *)malloc(sizeof(Tune));
	menuAdd(newtune);

	dbAdd(newtune);
	dbOpen();

	printf("\n\n> The tune \"%s\" has been added", newtune->title);
	free(newtune);
}

