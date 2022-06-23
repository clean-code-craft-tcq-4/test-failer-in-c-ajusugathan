#include <stdio.h>
#include <assert.h>
#include <string.h>

const char* MajorColorNames[] = {"White", "Red", "Black", "Yellow", "Violet"};

const char* MinorColorNames[] = {"Blue", "Orange", "Green", "Brown", "Slate"};

int numberOfMajorColors = sizeof(MajorColorNames) / sizeof(MajorColorNames[0]);

int numberOfMinorColors = sizeof(MinorColorNames) / sizeof(MinorColorNames[0]);
int maxCombination =(numberOfMajorColors*numberOfMinorColors);

typedef struct 
{
    int  pairNumber;
    char majorColorName[10];
    char minorColorName[10];
}colorPair;

 colorPair colorPairMap[25];
 colorPair colorCodeReferenceManual[25];

void CopycolorMap_forTest(int pairCount,int pairNumber,const char* majorColor,const char* minorColor)
{
    colorPairMap[pairCount].pairNumber = pairNumber;
    strcpy(colorPairMap[pairCount].majorColorName , majorColor);
    strcpy(colorPairMap[pairCount].minorColorName , minorColor);
}

void generateColorCodeReferenceManual(void)
{
    int MajorColorCount = 0;
    int MinorColorCount = 0;
    int PairNumber = 1;

    for(MajorColorCount = 0; MajorColorCount < numberOfMajorColors; MajorColorCount++)
    {
        for(MinorColorCount = 0; MinorColorCount < numberOfMinorColors; MinorColorCount++)
        {
            colorCodeReferenceManual[MajorColorCount*numberOfMajorColors+MinorColorCount].pairNumber = PairNumber;
            strcpy(colorCodeReferenceManual[MajorColorCount*numberOfMajorColors+MinorColorCount].majorColorName , MajorColorNames[MajorColorCount]);
            strcpy(colorCodeReferenceManual[MajorColorCount*numberOfMajorColors+MinorColorCount].minorColorName , MinorColorNames[MinorColorCount]);
            PairNumber++;
        }
    }
}

int printColorMap() {
    const char* majorColor[] = {"White", "Red", "Black", "Yellow", "Violet"};
    const char* minorColor[] = {"Blue", "Orange", "Green", "Brown", "Slate"};
    int i = 0, j = 0;
    for(i = 0; i < 5; i++) {
        for(j = 0; j < 5; j++) {
            printf("%d | %s | %s\n", i * 5 + j, majorColor[i], minorColor[i]);
            CopycolorMap_forTest((i * 5 + j),(i * 5 + j),majorColor[i],minorColor[i]);
        }
    }
    return i * j;
}

void testColorMap()
{
    generateColorCodeReferenceManual();
    for(int colorMapCount=0;colorMapCount<maxCombination;colorMapCount++)
    {
        assert(colorCodeReferenceManual[colorMapCount].pairNumber == colorPairMap[colorMapCount].pairNumber);
        assert(strcmp(colorCodeReferenceManual[colorMapCount].majorColorName,colorPairMap[colorMapCount].majorColorName) == 0);
        assert(strcmp(colorCodeReferenceManual[colorMapCount].minorColorName,colorPairMap[colorMapCount].minorColorName) == 0);
    }
}

int main() {
    
    int result = printColorMap();
    assert(result == maxCombination);
    testColorMap();
    printf("All is well (maybe!)\n");
    return 0;
}
