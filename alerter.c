#include <stdio.h>
#include <assert.h>

#define TEST_CODE_ENABLED  STD_ON   //switch to enable production code
#define TEST_THRESHOLD_TEMPERATURE 200   

int alertFailureCount = 0;

#if (TEST_CODE_ENABLED == STD_ON)

int networkAlertStub(float celcius) {
    printf("ALERT: Temperature is %.1f celcius.\n", celcius);
    // Return 200 for ok
    // Return 500 for not-ok
    // stub always succeeds and returns 200
    return 200;
}

void testAlertFailure(int Failed_countInital,float TemperatureInCelcious,int networkReturnCode)
{
    if(TemperatureInCelcious>TEST_THRESHOLD_TEMPERATURE)
    {
        assert(networkReturnCode==500);
        assert(Failed_countInital!=alertFailureCount);
    }
    else
    {
        assert(networkReturnCode==200);
        assert(Failed_countInital==alertFailureCount);
    }
}

#endif

void alertInCelcius(float farenheit) 
{
    float celcius = (farenheit - 32) * 5 / 9;
    
#if (TEST_CODE_ENABLED == STD_ON)
    int InitialFailureCount = alertFailureCount;
    int returnCode = networkAlertStub(celcius);
#endif
    
    if (returnCode != 200) 
    {
        // non-ok response is not an error! Issues happen in life!
        // let us keep a count of failures to report
        // However, this code doesn't count failures!
        // Add a test below to catch this bug. Alter the stub above, if needed.
        alertFailureCount += 0;
    }
    
#if (TEST_CODE_ENABLED == STD_ON)
testAlertFailure(InitialFailureCount,celcius,returnCode);
#endif
    
}

int main() {
    alertInCelcius(400.5);
    alertInCelcius(303.6);
    printf("%d alerts failed.\n", alertFailureCount);
    printf("All is well (maybe!)\n");
    return 0;
}
