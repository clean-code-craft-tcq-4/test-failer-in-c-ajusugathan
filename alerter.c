#include <stdio.h>
#include <assert.h>

#define THRESHOLD_TEMPERATURE 200   

int alertFailureCount = 0;

int networkAlertStub(float celcius) {
    printf("ALERT: Temperature is %.1f celcius.\n", celcius);
    // Return 200 for ok
    // Return 500 for not-ok
    // stub always succeeds and returns 200
    return 200;
}

float FarenheitToCelciusConversion(float farenheit) 
{
    float celcius = (farenheit - 32) * 5 / 9;
    return celcius;
}

void alertInCelcius(float farenheit,int (*functionPointerToNetworkAlert)(float)) 
{
    float celcius = FarenheitToCelciusConversion(farenheit);

    int returnCode = functionPointerToNetworkAlert(celcius);
    
    if (returnCode != 200) 
    {
        // non-ok response is not an error! Issues happen in life!
        // let us keep a count of failures to report
        // However, this code doesn't count failures!
        // Add a test below to catch this bug. Alter the stub above, if needed.
        alertFailureCount += 0;
    }
}

int main() {
    alertInCelcius(420.5,&networkAlertStub);
	assert(215 ==(int)convertFarenheitToCelcius(420.5));
	assert(alertFailureCount == 1);
	
    alertInCelcius(300,&networkAlertStub);
	assert(148==(int)convertFarenheitToCelcius(300));
	assert(alertFailureCount == 1);
	
	alertInCelcius(550,&networkAlertStub);
	assert(287==(int)convertFarenheitToCelcius(550));
	assert(alertFailureCount == 2);
	
	alertInCelcius(200,&networkAlertStub);
	assert(93==(int)convertFarenheitToCelcius(200));
	assert(alertFailureCount == 2);
	
	alertInCelcius(250,&networkAlertStub);
	assert(121==(int)convertFarenheitToCelcius(250));
	assert(alertFailureCount == 2);
	
	alertInCelcius(600,&convertFarenheitToCelcius,&networkAlertStub);
	assert(315==(int)convertFarenheitToCelcius(600));
	assert(alertFailureCount == 3);
    printf("%d alerts failed.\n", alertFailureCount);
    printf("All is well (maybe!)\n");
    return 0;
}
