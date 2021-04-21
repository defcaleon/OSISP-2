#include <stdio.h>
#include <sys/dir.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>


void ReadDirect(char filePath[], DIR *inndp, FILE *F1)
{
DIR *dp;

DIR *indp;
struct dirent *d;
struct stat infoFile;
int totalFile = 0;
int totalSize = 0;
int maxFileSize = 0;
int MAXDIR = 50;
char nameDir[MAXDIR];
char maxFileName[MAXDIR];
memset(maxFileName, '\0', MAXDIR);

dp = inndp;
d = readdir(dp);


while (d != NULL)
{
memset(nameDir, '\0', MAXDIR);
strcat(nameDir, filePath);
strcat(nameDir, "/");
strcat(nameDir, d->d_name);
indp = opendir(nameDir);

if (indp == NULL && d->d_name[0] != '.')
{
stat(nameDir, &infoFile);

if (infoFile.st_size > maxFileSize)
{
memset(maxFileName, '\0', MAXDIR);
strcat(maxFileName, d->d_name);
}

totalSize += infoFile.st_size;
printf(" Name-%s | Size-%ld\n", d->d_name, infoFile.st_size);
if (F1 != NULL)
fprintf(F1," Name-%s | Size-%ld\n", d->d_name, infoFile.st_size);
totalFile++;

}
d = readdir(dp);
}
printf("-File name with max size=%s\n", maxFileName);
fprintf(F1, "-File name with max size=%s\n", maxFileName);
printf("-Total Catalog Size=%d\n", totalSize);
fprintf(F1, "-Total Catalog Size=%d\n", totalSize);
printf("-Total Catalog File=%d\n\n", totalFile);
fprintf(F1, "-Total Catalog File=%d\n\n", totalFile);


//rewinddir(dp);
//dp = opendir(filePath);
//dp = inndp;
rewinddir(dp);
d=readdir(dp);
while (d != NULL)
{
memset(nameDir, '\0', MAXDIR);
strcat(nameDir, filePath);
strcat(nameDir, "/");
strcat(nameDir, d->d_name);
indp = opendir(nameDir);


if (indp != NULL && strcmp(d->d_name, ".") != 0 && strcmp(d->d_name, "..") != 0)
//if (indp != NULL && strcmp(d->d_name, ".") != 0 && strcmp(d->d_name, "..") != 0 && strcmp(d->d_name, ".vscode") != 0)
{
memset(nameDir, '\0', MAXDIR);
strcat(nameDir, filePath);
if (filePath[sizeof(filePath)/sizeof(char)] != '/')
strcat(nameDir, "/");
strcat(nameDir, d->d_name);
printf("Catalog-%s\n",nameDir);
if (F1 != NULL)
fprintf(F1, "Catalog-%s\n",nameDir);
ReadDirect(nameDir, indp, F1);
}
d = readdir(dp);
}

closedir(dp);

}



int main(int argc, char* argv[])
{
char pathname;



DIR *dp;
DIR *indp;

int totalSize = 0;
char maxFileName[] = {'\n'};
FILE *F1;


if (argc == 3)
{
F1 = fopen(argv[2], "w");
printf("Catalog-%s\n", argv[1]);
fprintf(F1, "Catalog-%s\n", argv[1]);
ReadDirect(argv[1], opendir(argv[1]), F1);
fclose(F1);
}
else
{
printf("Incorrect input!!!\n");
return 1;
}


return 0;
}