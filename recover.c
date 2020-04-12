#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Ensure only one command line argument
    if(argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }


    // Open file named images
    FILE *images = fopen(argv[1], "r");
    if ( images == NULL)
    {
        return 2;
    }

        // Initialize array called buffer of type BYTE
        BYTE *buffer = malloc(512);
        if ( buffer == NULL)
        {
            printf("Cannot open file\n");
            return 3;
        }

        // Variable for image number
            int img_num = 0;

        // Declaration of a FILE pointer
        FILE* img;

        // FREE THIS LATER, character array for creating names of JPEG files
        char* image = malloc(8);


        // Create condition to prompt fread
        while (fread(buffer, 1, 512, images) != 0)
        {

            // Read information
            fread(buffer, 1, 512, images);

            // Checking for a JPEG
            if( buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] & 0xf0) == 0xe0))
            {
                // If start of first JPEG
                if (img_num == 0)
                {
                    // Create string for new filename

                    sprintf(image,"%03i.jpg", img_num);

                    //Open and write to first JPEG file
                    img = fopen(image, "w");
                    fwrite(buffer, 1, 512, img);
                    img_num ++;
                }

                // If already found a JPEG
                else
                {
                    fclose(img);

                    sprintf(image,"%03i.jpg", img_num);

                    //Open and write to new JPEG file
                    img = fopen(image, "w");
                    fwrite(buffer, 1, 512, img);
                    img_num ++;

                }
            }

            else
            {
                //If JPEG found continue writing to it
                if (img_num != 0)
                {
                    fwrite(buffer, 1, 512, img);
                }

            }
        }

    free(buffer);
    free(image);
    fclose(img);
    fclose(images);


}