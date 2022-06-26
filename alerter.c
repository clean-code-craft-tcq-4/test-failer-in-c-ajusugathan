#include <stdio.h>
#include <assert.h>

#define THRESHOLD_TEMPERATURE 200   

int alertFailureCount = 0;

int networkAlertStub(float celcius) {
    printf("ALERT: Temperature is %.1f celcius.\n", celcius);
    // Return 200 for ok
	if(celcius<=THRESHOLD_TEMPERATURE)
	{
		return 200;
	}
	else
	{
		return 500;
	}
    // Return 500 for not-ok
    // stub always succeeds and returns 200
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
        alertFailureCount += 1;
    }
}

int main() {
	
    alertInCelcius(420.5,&networkAlertStub);
    assert(500 == networkAlertStub(FarenheitToCelciusConversion(420.5)));
    assert(215 == (int)FarenheitToCelciusConversion(420.5));
    assert(alertFailureCount == 1);
	
    alertInCelcius(300,&networkAlertStub);
    assert(200 == networkAlertStub(FarenheitToCelciusConversion(300)));
    assert(148 == (int)FarenheitToCelciusConversion(300));
    assert(alertFailureCount == 1);
	
    alertInCelcius(550,&networkAlertStub);
    assert(500 == networkAlertStub(FarenheitToCelciusConversion(550)));
    assert(287 == (int)FarenheitToCelciusConversion(550));
    assert(alertFailureCount == 2);
	
    alertInCelcius(200,&networkAlertStub);
    assert(200 == networkAlertStub(FarenheitToCelciusConversion(200)));
    assert(93 == (int)FarenheitToCelciusConversion(200));
    assert(alertFailureCount == 2);
	
    alertInCelcius(250,&networkAlertStub);
    assert(200 == networkAlertStub(FarenheitToCelciusConversion(250)));
    assert(121==(int)FarenheitToCelciusConversion(250));
    assert(alertFailureCount == 2);
	
    alertInCelcius(600,&networkAlertStub);
    assert(500 == networkAlertStub(FarenheitToCelciusConversion(600)));
    assert(315 == (int)FarenheitToCelciusConversion(600));
    assert(alertFailureCount == 3);
	
    printf("%d alerts failed.\n", alertFailureCount);
    printf("All is well (maybe!)\n");
    return 0;
}
