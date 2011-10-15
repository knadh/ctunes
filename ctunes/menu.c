/* ============================

	cTunes 1.8
	C Programming exercise
	
	Kailash Nadh, http://kailashnadh.name

============================ */


#include "ctunes.h"


// variable declarations
char *menu_opts[9];
int menu_size;

// method declarations
int menuRun(int ops_s);
void menuMain();
void menuPrompt();
int menuSort();
int menuSortSave();
int menuExport();
int menuSearch();

// ==========================================================

// initialise the menu item
void menuInit() {
	menu_opts[0] = "View all tunes";
	menu_opts[1] = "Delete tunes";
	menu_opts[2] = "Add new tunes";
	menu_opts[3] = "Sort tunes";
	menu_opts[4] = "Search tunes";
	menu_opts[5] = "Export tunes";
	menu_opts[6] = "Diagnostics";
	menu_opts[7] = "Statistics";
	menu_opts[8] = "Quit";

	menu_size = sizeof(menu_opts)/4;
}

// Display the cli menu
int menuRun(int opt_s) {

	char str_opt, x;
	int opt = -1;

	if(opt_s >= 0 && opt_s < menu_size) {
		printf("\n> Press Enter to continue..");
		getAchar();
	}

	menuMain();
	menuPrompt();

	// read the user input

	str_opt = getAchar();	// read a character
	opt = atoi(&str_opt);	// conver to integer

	if(opt < 1 || opt > menu_size) {
		menuMain();
		PrintMsg("! Invalid option");
		return 0;
	}

	return opt;
}

void menuMain() {
	clearScr();

	// the welcome 'ascii art'
	printf("\t\t   _______\n");
	printf("\t\t  |__   __|\n");
	printf("\t\t  ___| |_   _ _ __   ___  ___ \n");
	printf("\t\t / __| | | | | '_ \\ / _ \\/ __|\n");
	printf("\t\t| (__| | |_| | | | |  __/\\__ \\\n");
	printf("\t\t \\___|_|\\__,_|_| |_|\\___||___/\n\n");
	printf("\t\t\tWelcome to cTunes v%.2f\n", VERSION);

	PrintLine();

	// print out the menu elements
	int i;
	for(i=0; i<menu_size; i++) {
		printf("%d. %s\n", (i+1), menu_opts[i]);
	}
	PrintLine();
}

void menuPrompt() {
	printf("Please enter an option: ");
}

// sort menu
int menuSort() {

	char str_opt;
	int opt = 0;

	PrintBr(); PrintLine();
	printf("\t\t\tSort Records\n");
	PrintLine();

	printf("0. Back to menu\n1. Sort by Artist\n2. Sort by Title\n3. Sort by Album\n4. Sort by Genre\n5. Sort by Year\n\n");
	menuPrompt();
	str_opt = getAchar();

	opt = atoi(&str_opt);	// conver to integer

	if(opt < 0 || opt > 5) {
		PrintMsg("! Invalid option");
		return 0;
	} else {
		return opt;
	}

	return 0;
}

// save the sort menu
int menuSortSave() {

	char str_opt;
	int opt = 0;

	PrintBr(); PrintLine();
	printf("Do you wish to write the changes (sorted playlist) to the file?\n");
	PrintLine();

	printf("1) Save changes\n0) Do not save changes\n\n");
	menuPrompt();
	str_opt = getAchar();

	opt = atoi(&str_opt);	// conver to integer

	if(opt < 0 || opt > 5) {
		PrintMsg("! Invalid option");
		return 0;
	} else {
		return opt;
	}

	return 0;
}

// export menu
int menuExport() {

	char str_opt;
	int opt = 0;

	PrintBr(); PrintLine();
	printf("\t\t\tExport Tunes\n");
	PrintLine();

	printf("0. Back to menu\n1. Export as csv\n2. Export as xml\n3. Export as html\n\n");
	menuPrompt();
	str_opt = getAchar();

	opt = atoi(&str_opt);	// convert to integer

	if(opt < 0 || opt > 3) {
		PrintMsg("! Invalid option");
		return 0;
	} else {
		return opt;
	}

	return 0;
}

// search menu
int menuSearch() {

	char str_opt;
	int opt = 0;

	PrintBr(); PrintLine();
	printf("\t\t\tExport Tunes\n");
	PrintLine();

	printf("0. Back to menu\n1. Search by Artist\n2. Search by Title\n3. Search by Album\n4. Search by Genre\n5. Search by Year\n\n");
	menuPrompt();
	str_opt = getAchar();

	opt = atoi(&str_opt);	// conver to integer

	if(opt < 0 || opt > 5) {
		PrintMsg("! Invalid option");
		return 0;
	} else {
		return opt;
	}

	return 0;
}

// diagnostics menu
int menuDiagnostics() {

	char str_opt;
	int opt = 0;

	PrintBr(); PrintLine();
	printf("\t\t\tExport Metrics\n");
	PrintLine();

	printf("0. Back to menu\n1. Export metrics as csv\n2. Export metrics as xml\n3. Export metrics as html\n4. View metrics on screen\n\n");
	menuPrompt();
	str_opt = getAchar();

	opt = atoi(&str_opt);	// convert to integer

	if(opt < 0 || opt > 4) {
		PrintMsg("! Invalid option");
		return 0;
	} else {
		return opt;
	}

	return 0;
}

// add a new tune
void menuAdd(Tune *newtune) {

	char yr[5];
	char input[50];

	PrintBr(); PrintLine();
	printf("\t\t\tAdd a new Tune\n");
	PrintLine();


	printf("Artist name\t: ");
	getAstring(input, 50);

	if(strcmp(input, "") == 0) {
		strcpy(newtune->artist, "Unknown");
	} else {
		strcpy(newtune->artist, input);
	}


	printf("Song Title\t: ");
	getAstring(input, 50);
	strcpy(newtune->title, input);

	printf("Album name\t: ");
	getAstring(input, 50);
	strcpy(newtune->album, input);

	printf("Song Genre\t: ");
	getAstring(input, 50);
	strcpy(newtune->genre, input);

	if(strcmp(input, "") == 0) {
		strcpy(newtune->genre, "Unknown");
	} else {
		strcpy(newtune->genre, input);
	}

	printf("Year\t\t: ");
	getAstring(yr, 5);

	newtune->year = atoi(yr);
}

