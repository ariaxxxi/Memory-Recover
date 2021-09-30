
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    if (argc != 2) 
    {
        return 1;
    }
    //open memory card
    FILE *file = fopen(argv[1], "r");

    if (file == NULL) 
    {
        return 1;
    }
    int countJPG = 0;
    char filename[10];
    unsigned char buffer[512];

    FILE *img;

    while (fread(buffer, sizeof(char), 512, file) != 0)
    {
 
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) 
        {
            if (countJPG > 0)
            {
                fclose(img);
            }

            //name a new file
            sprintf(filename, "%03i.jpg", countJPG);
            //open the new file
            img = fopen(filename, "w");
            //write to the file
            fwrite(buffer, sizeof(char), 512, img);
            countJPG ++;
        } 
        //if this one is not jpg but jpg already exist before
        else if (countJPG > 0) 
        {
            fwrite(buffer, sizeof(char), 512, img);
        }
    }
    fclose(file);
    fclose(img);
}


