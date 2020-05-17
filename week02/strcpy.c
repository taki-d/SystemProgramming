#include <stdio.h>
#include <string.h>

char *my_strcpy(char *s1, const char *s2){
    int i = 0;
    while(s2[i] != '\0'){
        s1[i] = s2[i];
        i++;
    }
    s1[i+1];
};

char *my_strdup(){

};

int main(void){
    //
    char str1[100] = "University of Tsukuba";
    char str2[100] = "College of Information Science";
    char str3[100] = "Tsukuba City";

    char my_str1[100] = "University of Tsukuba";
    char my_str2[100] = "College of Information Science";
    char my_str3[100] = "Tsukuba City";

    printf("strcpy   : %s\n", str1);
    printf("mystrcpy : %s\n", str1);

    strcpy(str1, str2);
    my_strcpy(my_str1, my_str2);

    printf("strcpy   : %s\n", str1);
    printf("mystrcpy : %s\n", str1);

    strcpy(str1, str3);
    my_strcpy(my_str1, my_str3);

    printf("strcpy   : %s\n", str1);
    printf("mystrcpy : %s\n", str1);

    return 0;
}
