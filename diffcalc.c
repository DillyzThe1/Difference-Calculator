#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

#include <windows.h>
#include <Wincrypt.h>

#ifdef WIN32
#include <io.h>
#define F_OK 0
#define access _access
#endif

bool isFolder(const char* pathhhh)
{
    struct stat path;
    stat(pathhhh, &path);
    return S_ISREG(path.st_mode) == 0;
}

bool verifyPath(char *pathh) {
	DIR* dir = opendir(pathh);
	if (dir) {
		closedir(dir);
		return true;
	}
	if (access(pathh, F_OK) == 0)
		return true;
	return false;
}

// https://learn.microsoft.com/en-us/windows/win32/seccrypto/example-c-program--creating-an-md-5-hash-from-file-content
#define BUFSIZE 1024
#define MD5LEN  16
DWORD fileHash(char *rgbDigits, char *filename) {
    DWORD dwStatus = 0;
	sprintf(rgbDigits, "0123456789abcdef");
	
	HANDLE hFile = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
    {
        dwStatus = GetLastError();
        printf("Error opening file %s\nError: %d\n", filename, dwStatus); 
        return dwStatus;
    }
	
	HCRYPTPROV hProv = 0;
    HCRYPTHASH hHash = 0;
	if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
    {
        dwStatus = GetLastError();
        printf("CryptAcquireContext failed: %d\n", dwStatus); 
        CloseHandle(hFile);
        return dwStatus;
    }
	
	if (!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash))
    {
        dwStatus = GetLastError();
        printf("CryptAcquireContext failed: %d\n", dwStatus); 
        CloseHandle(hFile);
        CryptReleaseContext(hProv, 0);
        return dwStatus;
    }
	
    BOOL bResult = FALSE;
    BYTE rgbFile[BUFSIZE];
    DWORD cbRead = 0;
	while (bResult = ReadFile(hFile, rgbFile, BUFSIZE, &cbRead, NULL))
    {
        if (cbRead == 0)
            break;

        if (!CryptHashData(hHash, rgbFile, cbRead, 0))
        {
            dwStatus = GetLastError();
            printf("CryptHashData failed: %d\n", dwStatus); 
            CryptReleaseContext(hProv, 0);
            CryptDestroyHash(hHash);
            CloseHandle(hFile);
            return dwStatus;
        }
    }
	
	if (!bResult)
    {
        dwStatus = GetLastError();
        printf("ReadFile failed: %d\n", dwStatus); 
        CryptReleaseContext(hProv, 0);
        CryptDestroyHash(hHash);
        CloseHandle(hFile);
        return dwStatus;
    }
	
    DWORD cbHash = MD5LEN;
    BYTE rgbHash[MD5LEN];
    if (CryptGetHashParam(hHash, HP_HASHVAL, rgbHash, &cbHash, 0))
    {
        //printf("MD5 hash of file %s is: ", filename);
		sprintf(rgbDigits, "");
        for (DWORD i = 0; i < cbHash; i++)
        {
            //printf("%c%c", rgbDigits[rgbHash[i] >> 4], rgbDigits[rgbHash[i] & 0xf]);
			sprintf(rgbDigits, "%s%c%c", rgbDigits, rgbDigits[rgbHash[i] >> 4], rgbDigits[rgbHash[i] & 0xf]);
        }
        //printf("\n");
    }
    else
    {
        dwStatus = GetLastError();
        printf("CryptGetHashParam failed: %d\n", dwStatus); 
    }

    CryptDestroyHash(hHash);
    CryptReleaseContext(hProv, 0);
    CloseHandle(hFile);
	
	return dwStatus;
}

void checkFolder(FILE *log, char *folderPath, char *compPath, bool noHash, char *missingName) {
	DIR *d = opendir(folderPath);
	struct dirent *dir;
	if (d) {
		while ((dir = readdir(d)) != NULL) {
			char *dname = dir->d_name;
			if (strcmp(dname, ".") == 0 || strcmp(dname, "..") == 0)
				continue;
			char newSuperDirectio[256];
			sprintf(newSuperDirectio, "%s/%s", compPath, dname);
			if (!verifyPath(newSuperDirectio)) {
				sprintf(newSuperDirectio, "%s/%s", folderPath, dname);
				printf("%s - %s\n", missingName, newSuperDirectio);
				fprintf(log, "%s - %s\n", missingName, newSuperDirectio);
				continue;
			}
			
			char diiiii1[256];
			sprintf(diiiii1, "%s/%s", folderPath, dname);
			char diiiii2[256];
			sprintf(diiiii2, "%s/%s", compPath, dname);
			if (isFolder(diiiii1)) {
				checkFolder(log, diiiii1, diiiii2, noHash, missingName);
				continue;
			}
			
			if (noHash)
				continue;
			
			char funnyHash1[512], funnyHash2[512];
			fileHash(funnyHash1, diiiii1); 
			fileHash(funnyHash2, diiiii2);
			//printf("super %s %s %d\n", funnyHash1, funnyHash2, strcmp(funnyHash1, funnyHash2));
			if (strcmp(funnyHash1, funnyHash2) == 0)
				continue;
			printf("HASH MISMATCH - %s & %s\n", diiiii1, diiiii2);
			fprintf(log, "HASH MISMATCH - %s & %s\n", diiiii1, diiiii2);
		}
		closedir(d);
	}
}

char ch;
char dir1[256], dir2[256];
void main() {
	printf("hello world what are you doing here\n");
	
	printf("First Path: \n");
    scanf("%255s", &dir1);
	if (!verifyPath(dir1)) {
		printf("%s is not an exist\n", dir1);
		scanf("%c",&ch);
		return;
	}
    printf("hello world what are %s\n\n", dir1);
        
    printf("Second Path: \n");
    scanf("%255s", &dir2);
	if (!verifyPath(dir2)) {
		printf("%s is not an exist\n", dir2);
		scanf("%c",&ch);
		return;
	}
    printf("hello wwww what are %s\n\n", dir2);
	
	FILE *wo;
	wo = fopen("diff.txt", "w");
	fputs("hello boy\nwhat are you\n\ndoing here\n\n", wo);
	
	// the big part
	checkFolder(wo, dir1, dir2, false, "ADDED");
	checkFolder(wo, dir2, dir1, true, "REMOVED");
	//
	fclose(wo);
	
	scanf("%c",&ch);
}