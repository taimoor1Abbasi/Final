#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include "cosewic.h"

//MAIN FUNCTIONS
void mainLogic(const struct Filedata data[], int records) {
    int selection;
    do
    {
        ("=======================================================\n");
        printf("         Canada Species at Risk Analysis\n");
        printf("            (Data Years: 2010 - 2019)\n");
        printf("=======================================================\n");
        printf("1. View by year (sorted ASCENDING by year)\n");
        printf("2. View by province (sorted DESCENDING by totals)\n");
        printf("3. View by taxon (sorted ASCENDING by totals)\n");
        printf("4. View by province and taxon\n");
        printf("-------------------------------------------------------\n");
        printf("0. Exit\n");
        printf("-------------------------------------------------------\n");
        printf("Selection: \n");
        selection = inputInt(0, 4);
        switch (selection)
        {
        case 0:
            printf("Application Terminated!\n");
            break;
        case 1:
            ViewbyYear(data,records);
            break;
        case 2:
            ViewbyProvince(data,records);
            break;
        case 3:
            ViewbyTaxon(data,records);
            break;
        case 4:
            //Viewbypt();
            break;
        }
    } while (selection); 


}



//Display FUNCTIONS
void displayHeader(int type) {
    
    if (type==1)
    {
        printf("\nYEAR EXTINCT EXTIRPATED ENDANGERED THREATENED CONCERN     TOTAL\n");
        printf("---- ------- ---------- ---------- ---------- ------- ---------\n");
    }
    if (type == 2)
    {
        printf("\nPROVINCE             EXTINCT EXTIRPATED ENDANGERED THREATENED CONCERN     TOTAL\n");
        printf("-------------------- ------- ---------- ---------- ---------- ------- ---------\n");
    }
    if (type == 3)
    {
        printf("\nTAXON           EXTINCT EXTIRPATED ENDANGERED THREATENED CONCERN     TOTAL\n");
        printf("--------------- ------- ---------- ---------- ---------- ------- ---------\n");
    }
}


//Appilcation Funtions
void ViewbyYear(const struct FileData data[],int max) {
    displayHeader(1);
    int total = 0;
    int year=2010;
    int ex=0, et=0, en=0, th=0, con=0, sum = 0,se=0,sx=0,sn=0,st=0,sc=0;
    for (; year < 2020; year++)
    {
        ex = countex(data, max, year,"","", 1);
        et = countext(data, max, year, "", "", 1);
        en = counted(data, max, year, "", "", 1);
        th = countth(data, max, year, "", "", 1);
        con = countcon(data, max, year, "", "", 1);
        total = ex + et + en + th + con;
        printf("%d    %d       %d       %d       %d    %d     %d\n",year,ex,et,en,th,con,total);
        sum = total + sum;
        se += ex, sx += et, sn += en, st += th, sc += con;
        ex = 0, et = 0, en = 0, th = 0, con = 0,total;
    }
    printf("     ------- ---------- ---------- ---------- ------- ---------\n");
    printf("       %d      %d      %d      %d   %d    %d\n\n", se, sx, sn, st, sc,sum);
}

ViewbyProvince(const struct FileData data[], int max) {
    displayHeader(2);
    int total = 0;
    int i=0;
    char* province[13] = {"Ontario","Nunavut","Manitoba","Yukon Territory","New Brunswick","Quebec","Saskatchewan","Nova Scotia","Newfoundland","Alberta" ,"Prince Edward Island" ,"British Columbia" ,"Northwest Territory"};
    char* p[13] = { "ON","NU","MB","YT","NB","QC","SK","NS","NL","AB" ,"PE" ,"BC" ,"NT" };
    int ex = 0, et = 0, en = 0, th = 0, con = 0, sum = 0, se = 0, sx = 0, sn = 0, st = 0, sc = 0;
    for (; i < 13; i++)
    {
        ex = countex(data, max, 0, p[i], "", 2);
        et = countext(data, max, 0, p[i], "", 2);
        en = counted(data, max, 0, p[i], "", 2);
        th = countth(data, max, 0, p[i], "", 2);
        con = countcon(data, max, 0, p[i], "", 2);
        total = ex + et + en + th + con;
        printf("%-22s  %d       %d       %d       %d    %d     %d\n", province[i], ex, et, en, th, con, total);
        sum = total + sum;
        se += ex, sx += et, sn += en, st += th, sc += con;
        ex = 0, et = 0, en = 0, th = 0, con = 0, total;
    }
    printf("-------------------- ------- ---------- ---------- ---------- ------- ---------\n");
    printf("                       %d      %d      %d      %d   %d    %d\n\n", se, sx, sn, st, sc, sum);

}

ViewbyTaxon(const struct FileData data[], int max) {
    displayHeader(3);
    int total = 0;
    int i = 0;
    char* taxon[10] = {"Mammals","Birds","Reptiles","Amphibians","Fishes","Arthropods","Molluscs","Vascular Plants","Mosses","Lichens"};
    int ex = 0, et = 0, en = 0, th = 0, con = 0, sum = 0, se = 0, sx = 0, sn = 0, st = 0, sc = 0;
    for (; i < 10; i++)
    {
        ex = countex(data, max, 0, "", taxon[i], 3);
        et = countext(data, max, 0, "", taxon[i], 3);
        en = counted(data, max, 0, "", taxon[i], 3);
        th = countth(data, max, 0, "", taxon[i], 3);
        con = countcon(data, max, 0, "", taxon[i],3);
        total = ex + et + en + th + con;
        printf("%-17s  %d       %d       %d       %d    %d     %d\n", taxon[i], ex, et, en, th, con, total);
        sum = total + sum;
        se += ex, sx += et, sn += en, st += th, sc += con;
        ex = 0, et = 0, en = 0, th = 0, con = 0, total;
    }
    printf("                ------- ---------- ---------- ---------- ------- ---------\n");
    printf("                  %d      %d      %d      %d   %d    %d\n\n", se, sx, sn, st, sc, sum);
}

//Viewbypt();

//UTILITY FUNCTIONS
int getyear(const struct FileData data[]) {
    int y=0;
    return y;
}

int countex(const struct FileData data[], int max, int year,char provice[], char taxon[],int choice) {
    int i = 0;
    int total = 0;
    for (; i < max; i++)
    {
        if (data[i].year == year && !strcmp(data[i].status, "EXTINCT") && choice==1) {
            total+=data[i].count;
        }
        if (!strcmp(data[i].province, provice) && !strcmp(data[i].status, "EXTINCT") && choice == 2) {
            total += data[i].count;
        }
        if (!strcmp(data[i].taxon, taxon) && !strcmp(data[i].status, "EXTINCT") && choice == 3) {
            total += data[i].count;
        }
    }
    return total;
}
int countext(const struct FileData data[], int max, int year, char provice[], char taxon[], int choice) {
    int i = 0;
    int total = 0;
    for (; i < max; i++)
    {
        if (data[i].year == year && !strcmp(data[i].status, "EXTIRPATED") && choice == 1) {
            total += data[i].count;
        }
        if (!strcmp(data[i].province, provice) && !strcmp(data[i].status, "EXTIRPATED") && choice == 2) {
            total += data[i].count;
        }
        if (!strcmp(data[i].taxon, taxon) && !strcmp(data[i].status, "EXTIRPATED") && choice == 3) {
            total += data[i].count;
        }
    }
    return total;
}
int counted(const struct FileData data[], int max, int year, char provice[], char taxon[], int choice) {
    int i = 0;
    int total = 0;
    for (; i < max; i++)
    {
        if (data[i].year == year && !strcmp(data[i].status, "ENDANGERED") && choice == 1) {
            total += data[i].count;
        }
        if (!strcmp(data[i].province, provice) && !strcmp(data[i].status, "ENDANGERED") && choice == 2) {
            total += data[i].count;
        }
        if (!strcmp(data[i].taxon, taxon) && !strcmp(data[i].status, "ENDANGERED") && choice == 3) {
            total += data[i].count;
        }
    }
    return total;
}
int countth(const struct FileData data[], int max, int year, char provice[], char taxon[], int choice) {
    int i = 0;
    int total = 0;
    for (; i < max; i++)
    {

        if (data[i].year == year && !strcmp(data[i].status, "THREATENED") && choice == 1) {
            total += data[i].count;
        }
        if (!strcmp(data[i].province, provice) && !strcmp(data[i].status, "THREATENED") && choice == 2) {
            total += data[i].count;
        }
        if (!strcmp(data[i].taxon, taxon) && !strcmp(data[i].status, "THREATENED") && choice == 3) {
            total += data[i].count;
        }
    }
    return total;
}
int countcon(const struct FileData data[], int max, int year, char provice[], char taxon[], int choice) {
    int i = 0;
    int total = 0;
    for (; i < max; i++)
    {
        if (data[i].year == year && !strcmp(data[i].status, "SPECIAL CONCERN") && choice == 1) {
            total += data[i].count;
        }
        if (!strcmp(data[i].province, provice) && !strcmp(data[i].status, "SPECIAL CONCERN") && choice == 2) {
            total += data[i].count;
        }
        if (!strcmp(data[i].taxon, taxon) && !strcmp(data[i].status, "SPECIAL CONCERN") && choice == 3) {
            total += data[i].count;
        }
    }
    return total;
}

int inputInt() {
    int i = 0, a = 0;
    char c;
    do
    {
        scanf(" %d%c", &i, &c);
        if (i % 1 == 0 && c != '\n') { //checks the if  value is a number as  //
            printf("Error! Input a whole number: ");
            clearInputBuffer();
        }// i did not use size of but just read until the \n is detected.//
        else {
            a = i;
        }
    } while (i == 0);
    return a;
}

int loadData(const char* datafile, struct FileData data[], int max) {
    int i = 0;
    struct FileData t;
    FILE* fp = fopen(datafile, "r");
    if (fp != NULL)
    {
        fscanf(fp, "%*[^\n]\n");
        while (i < max) {
           fscanf(fp, "%d,%[^,],%[^,],%d,%s\n", &data[i].year, data[i].taxon, data[i].status, &data[i].count, data[i].province);
            i++;
        }
        fclose(fp);
        fp = NULL;
    }
    return i;
}

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}
