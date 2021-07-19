//
//  main.c
//  CFNumberDemo
//
//  Created by Panayotis Matsinopoulos on 19/7/21.
//

#include <stdio.h>
#include <CoreFoundation/CoreFoundation.h>

int myFunc(int a) {
  return a + 1;
}

typedef struct _Temperature {
  int maximum;
  int minimum;
} Temperature;

void PrintTemperature(Temperature *temperature) {
  printf("Temperature maximum %d, minimum %d\n", temperature->maximum, temperature->minimum);
}

int main(int argc, const char * argv[]) {
  unsigned int ui = 5;
  float f = 8.2;
    
  Temperature temperature = { .maximum = 40, .minimum = 32 };
  unsigned long temperatureAddress = (unsigned long)&temperature;
  printf("Address of temperature %p\n", (void *)temperatureAddress);
  
  Temperature *pTemperature = malloc(sizeof(Temperature));
  pTemperature->maximum = 42;
  pTemperature->minimum = 31;
  printf("Value of pTemperature %p\n", pTemperature);
  
  unsigned long myFuncAddress = (unsigned long)myFunc;
  printf("Value of myFuncAddress %p\n", (void *)myFuncAddress);

  CFNumberRef uiNumberRef = CFNumberCreate(kCFAllocatorDefault, kCFNumberLongType, (const void *)&ui);
  CFNumberRef fNumberRef = CFNumberCreate(kCFAllocatorDefault, kCFNumberFloatType, (const void *)&f);
  CFNumberRef temperatureAddressNumberRef = CFNumberCreate(kCFAllocatorDefault, kCFNumberLongLongType, (const void *)&temperatureAddress);
  CFNumberRef pTemperatureNumberRef = CFNumberCreate(kCFAllocatorDefault, kCFNumberLongLongType, (const void *)&pTemperature);
  CFNumberRef myFuncAddressNumberRef = CFNumberCreate(kCFAllocatorDefault, kCFNumberLongLongType, (const void *)&myFuncAddress);

  // Get Types
  printf("---------------------------\n");
  printf("Get Types:...\n");
  CFNumberType numberType = CFNumberGetType(uiNumberRef);
  printf("ui number type is kCFNumberLongType = %s\n", numberType == kCFNumberLongType ? "YES" : "NO");
  printf("ui number type is kCFNumberSInt64Type = %s\n", numberType == kCFNumberSInt64Type ? "YES" : "NO");
  
  numberType = CFNumberGetType(fNumberRef);
  printf("f number type is kCFNumberFloatType = %s\n", numberType == kCFNumberFloatType ? "YES" : "NO");
  printf("f number type is kCFNumberFloat32Type = %s\n", numberType == kCFNumberFloat32Type ? "YES" : "NO");
  
  numberType = CFNumberGetType(temperatureAddressNumberRef);
  printf("temperatureAddress number type is kCFNumberLongLongType = %s\n", numberType == kCFNumberLongLongType ? "YES" : "NO");
  printf("temperatureAddress number type is kCFNumberSInt64Type = %s\n", numberType == kCFNumberSInt64Type ? "YES" : "NO");

  numberType = CFNumberGetType(pTemperatureNumberRef);
  printf("pTemperature number type is kCFNumberLongLongType = %s\n", numberType == kCFNumberLongLongType ? "YES" : "NO");
  printf("pTemperature number type is kCFNumberSInt64Type = %s\n", numberType == kCFNumberSInt64Type ? "YES" : "NO");
  
  numberType = CFNumberGetType(myFuncAddressNumberRef);
  printf("myFuncAddress number type is kCFNumberLongLongType = %s\n", numberType == kCFNumberLongLongType ? "YES" : "NO");
  printf("myFuncAddress number type is kCFNumberSInt64Type = %s\n", numberType == kCFNumberSInt64Type ? "YES" : "NO");

  printf("---------------------------\n");
  
  // Change the original value and Get Values of the CFNumber objects
  printf("Get Values:...\n");
  
  ui = 8;
  unsigned int uiValue;
  CFNumberGetValue(uiNumberRef, kCFNumberLongType, (void *)&uiValue);
  printf("ui value retrieved = %i\n", uiValue); // prints "5" for the value
  
  f = 15.3;
  float fValue;
  CFNumberGetValue(fNumberRef, kCFNumberFloatType, (void *)&fValue);
  printf("f value retrieved = %.2f\n", fValue); // prints "8.20" for the value
  
  unsigned long temperatureAddressValue;
  CFNumberGetValue(temperatureAddressNumberRef, kCFNumberLongLongType, (void *)&temperatureAddressValue);
  printf("temperatureAddress value retrieved = %p\n", (void *)temperatureAddressValue);
  PrintTemperature((Temperature *)temperatureAddressValue);
  
  Temperature *pTemperatureValue;
  CFNumberGetValue(pTemperatureNumberRef, kCFNumberLongLongType, (void *)&pTemperatureValue);
  printf("pTemperature value retrieved = %p\n", (void *)pTemperatureValue);
  PrintTemperature(pTemperatureValue);
  
  unsigned long myFuncAddressValue;
  CFNumberGetValue(myFuncAddressNumberRef, kCFNumberLongLongType, (void *)&myFuncAddressValue);
  printf("myFuncAddress value retrieved = %p\n", (void *)myFuncAddressValue);
  // Call function via returned value to prove that it works
  printf("Call function via returned value to prove that it works...\n");
  int res = ((int (*)(int))myFuncAddressValue)(2);
  printf("res = %d\n", res);
  printf("---------------------------\n");
  
  // Release resources
  CFRelease(myFuncAddressNumberRef);
  CFRelease(pTemperatureNumberRef);
  CFRelease(temperatureAddressNumberRef);
  CFRelease(fNumberRef);
  CFRelease(uiNumberRef);

  free(pTemperature);
  pTemperature = NULL;
  
  return 0;
}
