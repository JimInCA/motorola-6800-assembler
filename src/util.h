
#ifndef _UTIL_H_
#define _UTIL_H_

void fatal(char *str);
;
void error(char *str);
void warn(char *str);
int delim(char c);
char *skip_white(char *ptr);
void eword(int wd);
int emit(int byte);
void f_record(void);
void hexout(int byte);
void print_line(void);
void any(char c, char *str);
char mapdn(char c);
void lobyte(int i);
void hibyte(int i);
void head(char *str1, char *str2);
void alpha(char c);
void alphan(char c);
void white(char c);
char *alloc(int nbytes);

#endif // _UTIL_H_

