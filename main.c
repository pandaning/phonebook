#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include IMPL

#define DICT_FILE "./dictionary/words.txt"

static double diff_in_second(struct timespec t1, struct timespec t2)
{
    struct timespec diff;
    if (t2.tv_nsec-t1.tv_nsec < 0) {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec - 1;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
    } else {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
    }
    return (diff.tv_sec + diff.tv_nsec / 1000000000.0);
}

int min(int a, int b, int c)
{
    return a < b ? (a < c ? a:c):(b < c ? b:c);
}
int Similarity(char *compare, char *compared)
{
    int L1 = strlen(compare), L2 = strlen(compared);
    char str1[L1+1], str2[L2+1];
    str1[0] = '*';
    str1[1] = 0;
    str2[0] = '*';
    str2[1] = 0;
    strcat(str1, compare);
    strcat(str2, compared);
    int dp[L1+1][L2+1];
    int i, j;

    for(i = 0; str1[i]; i++) {
        for(j = 0; str2[j]; j++) {
            if(i == 0) dp[i][j] = j;
            else if(j == 0) dp[i][j] = i;
            else {
                if(str1[i] == str2[j]) dp[i][j] = dp[i-1][j-1];
                else dp[i][j] =  min(dp[i][j-1], dp[i-1][j], dp[i-1][j-1]) + 1;
            }
        }
    }
    return dp[L1][L2];
}

#ifdef HASHFUNCTION
int main(int argc, char *argv[])
{
    FILE *fp, *outfile;
    int i = 0;
    char line[MAX_LAST_NAME_SIZE];
    struct timespec start, end;
    double cpu_time1, cpu_time2;

    /* check file opening */
    fp = fopen(DICT_FILE, "r");
    if (fp == NULL) {
        printf("cannot open the file\n");
        return -1;
    }
    /*Build head for Hash Table*/
    phonebook.init_Hash_Table();

    printf("size of entry : %lu bytes\n", sizeof(HashList));
    char dictionary[349909][17] = {0};
    int dicSize = 0;

    clock_gettime(CLOCK_REALTIME, &start);
    while (fgets(line, sizeof(line), fp)) {
        while (line[i] != '\0')
            i++;
        line[i - 1] = '\0';
        i = 0;
        phonebook.push_Hash_Table(line);
        strcpy(dictionary[dicSize++], line);
    }
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time1 = diff_in_second(start, end);

    /* close file as soon as possible */
    fclose(fp);

    /* the given last name to find */
    char input[MAX_LAST_NAME_SIZE] = "aacc";

    /* compute the execution time */
    clock_gettime(CLOCK_REALTIME, &start);
    int found=phonebook.IsFound(input);

    //If the word is not found in the file, print similary words
    if(found==0) {
        int i;
        int cnt = 0;
        for(i = 0; i < dicSize; i++) {
            if(Similarity(input, dictionary[i]) == 1) {
                cnt++;
                printf("You input \"%s\"   Do you mean \"%s\"\n", input, dictionary[i]);
            }
        }
        printf("There are %d similary words.\n\n",  cnt);
    }
    //After print the similary words, end the program
    assert(found==1);
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time2 = diff_in_second(start, end);
    printf("execution time of append() : %lf sec\n", cpu_time1);
    printf("execution time of findName() : %lf sec\n", cpu_time2);
    outfile = fopen("ShiftMethod.txt","a");
    fprintf(outfile, "%f\t%f\n", cpu_time1, cpu_time2);

    phonebook.Release_Hash_Table();
    return 0;
}
#endif

#ifdef ORIGINAL
int main(int argc, char *argv[])
{
    FILE *fp, *outfile;
    int i = 0;
    char line[MAX_LAST_NAME_SIZE];
    struct timespec start, end;
    double cpu_time1, cpu_time2;

    /* check file opening */
    fp = fopen(DICT_FILE, "r");
    if (fp == NULL) {
        printf("cannot open the file\n");
        return -1;
    }

    /* build the entry */
    entry *pHead, *e;
    pHead = (entry *) malloc(sizeof(entry));
    printf("size of entry : %lu bytes\n", sizeof(entry));
    e = pHead;
    e->pNext = NULL;

#if defined(__GNUC__)
    __builtin___clear_cache((char *) pHead, (char *) pHead + sizeof(entry));
#endif
    clock_gettime(CLOCK_REALTIME, &start);
    while (fgets(line, sizeof(line), fp)) {
        while (line[i] != '\0')
            i++;
        line[i - 1] = '\0';
        i = 0;
        e = append(line, e);
    }
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time1 = diff_in_second(start, end);

    /* close file as soon as possible */
    fclose(fp);

    e = pHead;

    /* the givn last name to find */
    char input[MAX_LAST_NAME_SIZE] = "zyxel";
    e = pHead;

    assert(findName(input, e) &&
           "Did you implement findName() in " IMPL "?");
    assert(0 == strcmp(findName(input, e)->lastName, "zyxel"));

#if defined(__GNUC__)
    __builtin___clear_cache((char *) pHead, (char *) pHead + sizeof(entry));
#endif
    /* compute the execution time */
    clock_gettime(CLOCK_REALTIME, &start);
    findName(input, e);
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time2 = diff_in_second(start, end);

    printf("execution time of append() : %lf sec\n", cpu_time1);
    printf("execution time of findName() : %lf sec\n", cpu_time2);
    outfile = fopen("Ori1.txt","a");
    fprintf(outfile, "%f\t%f\n", cpu_time1, cpu_time2);

    /* FIXME: release all allocated entries */
    free(pHead);

    return 0;
}
#endif