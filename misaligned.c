#include <stdio.h>
#include <assert.h>
#include <string.h>

#include <stdio.h>
#include <assert.h>
#include <string.h>

#define MAX_COLOR_PAIR 25

const char* MajorColorNames[] = {"White", "Red", "Black", "Yellow", "Violet"};

const char* MinorColorNames[] = {"Blue", "Orange", "Green", "Brown", "Slate"};

int numberOfMajorColors = sizeof(MajorColorNames) / sizeof(MajorColorNames[0]);

int numberOfMinorColors = sizeof(MinorColorNames) / sizeof(MinorColorNames[0]);
    
char ColorCodeReferenceManual[25][100];
char colorMapInfo[25][100];

int getPairNumber(int majorColorCount,int minorColorCount)
{
    return((majorColorCount * numberOfMajorColors + minorColorCount) + 1);
}

int getColorMap()
{
    int majorColorIndex;
    int minorColorIndex;
	char ColorMapRow[100];
	int pair=0;
    for(majorColorIndex=0; majorColorIndex < numberOfMajorColors; majorColorIndex++)
    {
        for(minorColorIndex=0; minorColorIndex < numberOfMinorColors; minorColorIndex++)
        {
            sprintf(ColorMapRow, "%d\t|%s\t\t|%s\n",(getPairNumber(majorColorIndex,minorColorIndex)),(MajorColorNames[majorColorIndex]),(MinorColorNames[minorColorIndex]));
            strcpy(&colorMapInfo[(majorColorIndex * numberOfMajorColors + minorColorIndex)][0],ColorMapRow);
			printf("%s",&colorMapInfo[(majorColorIndex * numberOfMajorColors + minorColorIndex)][0]);
			pair++;
        }
    }
    return(majorColorIndex*minorColorIndex);
}

int printColorMap() 
{
    int totalPairNumber;
    printf("Color Map Generated\n\n");
    totalPairNumber=getColorMap();
    return (totalPairNumber);
}

void generateColorCodeReferenceManual()
{
    int pairNumber = 1;
	char ColorMapRow[100];
	printf("\n Actual Color Code Refernece Manual\n\n");
    for(int majorColorIndex=0; majorColorIndex < numberOfMajorColors; majorColorIndex++)
    {
        for(int minorColorIndex=0; minorColorIndex < numberOfMinorColors; minorColorIndex++)
        {
            sprintf(ColorMapRow, "%d\t|%s\t\t|%s\n",pairNumber++,(MajorColorNames[majorColorIndex]),(MinorColorNames[minorColorIndex]));
			strcpy(&ColorCodeReferenceManual[(majorColorIndex * numberOfMajorColors + minorColorIndex)][0],ColorMapRow);
            printf("%s",&ColorCodeReferenceManual[(majorColorIndex * numberOfMajorColors + minorColorIndex)][0]);
        }
    }
    
}


int main() 
{
    int result = printColorMap();
    generateColorCodeReferenceManual();
    for(int combination_count=0;combination_count<MAX_COLOR_PAIR;combination_count++)
    {
       assert(strcmp(&ColorCodeReferenceManual[combination_count][0],colorMapInfo[combination_count][0])==0);
       
    }
    printf("All is well (maybe!)\n");
    return 0;
}
