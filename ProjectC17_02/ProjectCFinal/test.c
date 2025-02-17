#include <stdio.h>
#include <time.h>

int main() {
    time_t curtime;
    struct tm *localTime;

    // Get the current time
    time(&curtime);
    // Convert it to local time representation
    localTime = localtime(&curtime);

    // Print the date in dd/mm/yyyy format
    printf("Ngày tháng năm hiện tại (UTC+7): %02d/%02d/%04d\n", 
           localTime->tm_mday, localTime->tm_mon + 1, localTime->tm_year + 1900);

    return 0;
}
