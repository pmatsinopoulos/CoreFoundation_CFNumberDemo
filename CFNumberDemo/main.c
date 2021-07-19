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

int main(int argc, const char * argv[]) {  
  unsigned int ui = 5;
  float f = 8.2;
  unsigned long myFuncAddress = (unsigned long)myFunc;
  printf("Value of myFuncAddress %p\n", (void *)myFuncAddress);
  
  printf("\nPrint sizes of variables\n");
  printf("Size of ui            = %ld\n", sizeof(ui));
  printf("Size of f             = %ld\n", sizeof(f));
  printf("Size of myFuncAddress = %ld\n", sizeof(myFuncAddress));
  printf("---------------------------\n");
  
  CFNumberRef uiNumberRef = CFNumberCreate(kCFAllocatorDefault, kCFNumberLongType, (const void *)&ui);
  CFNumberRef fNumberRef = CFNumberCreate(kCFAllocatorDefault, kCFNumberFloatType, (const void *)&f);
  CFNumberRef myFuncAddressRef = CFNumberCreate(kCFAllocatorDefault, kCFNumberLongLongType, (const void *)&myFuncAddress);
  
  // Get Types
  printf("Get Types:...\n");
  CFNumberType numberType = CFNumberGetType(uiNumberRef);
  printf("ui number type is kCFNumberLongType = %s\n", numberType == kCFNumberLongType ? "YES" : "NO");
  printf("ui number type is kCFNumberSInt64Type = %s\n", numberType == kCFNumberSInt64Type ? "YES" : "NO");
  
  numberType = CFNumberGetType(fNumberRef);
  printf("f number type is kCFNumberFloatType = %s\n", numberType == kCFNumberFloatType ? "YES" : "NO");
  printf("f number type is kCFNumberFloat32Type = %s\n", numberType == kCFNumberFloat32Type ? "YES" : "NO");
  
  numberType = CFNumberGetType(myFuncAddressRef);
  printf("myFuncAddress number type is kCFNumberLongLongType = %s\n", numberType == kCFNumberLongLongType ? "YES" : "NO");
  printf("myFuncAddress number type is kCFNumberSInt64Type = %s\n", numberType == kCFNumberSInt64Type ? "YES" : "NO");
  printf("---------------------------\n");
  
  // Get Values
  printf("Get Values:...\n");
  unsigned int uiValue;
  CFNumberGetValue(uiNumberRef, kCFNumberLongType, (void *)&uiValue);
  printf("ui value retrieved = %i\n", uiValue); // prints "5" for the value
  
  float fValue;
  CFNumberGetValue(fNumberRef, kCFNumberFloatType, (void *)&fValue);
  printf("f value retrieved = %.2f\n", fValue); // prints "8.20" for the value
  
  unsigned long myFuncAddressValue;
  CFNumberGetValue(myFuncAddressRef, kCFNumberLongLongType, (void *)&myFuncAddressValue);
  printf("myFuncAddress value retrieved = %p\n", (void *)myFuncAddressValue);
  printf("---------------------------\n");
  
  // Call function via returned value to prove that it works
  printf("Call function via returned value to prove that it works...\n");
  int res = ((int (*)(int))myFuncAddressValue)(2);
  printf("res = %d\n", res);
  
  // Release resources
  CFRelease(uiNumberRef);
  CFRelease(fNumberRef);
  CFRelease(myFuncAddressRef);
  
  return 0;
}
