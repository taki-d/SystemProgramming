#include <stdio.h>
#include <string.h>

char *my_strcpy(char *s1, const char *s2){
    int i = 0;
    while(s2[i] != '\0'){
        s1[i] = s2[i];
        i++;
    }

    return s1;
};

char *my_strdup(const char *s){
    char *rt_s = malloc(sizeof(s));
    printf("%d\n",sizeof(*s));

    int i = 0;
    while(s[i] != '\0'){
        rt_s[i] = s[i];
        i++;
    }

    return rt_s;
};

int main(void){
    char str1[100] = "University of Tsukuba";
    char str2[100] = "College of Information Science";

    char *s1, *s2, *my_s1, *my_s2;

    s1 = strdup(str1);
    my_s1 = my_strdup(str1);

    printf("strdup   : %s\n", s1);
    printf("mystrdup : %s\n", my_s1);

    s2 = strdup(str2);
    my_s2 = my_strdup(str2);

    printf("strdup   : %s\n", s2);
    printf("mystrdup : %s\n", my_s2);

    free(s1);
    free(s2);
    free(my_s1);
    free(my_s2);

    return 0;
}
