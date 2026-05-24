#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "gnl/get_next_line.h"

// char **str2args(char *str, int len, int *argc)
// {
//  int i = 0, arg_start = 0, quote = 0;
//  char **out;

//  if(!str && !*str) return 0;
//  out = (char **)malloc(sizeof(char *) * (len + 1)); /* maximalni mozny pocet izolovanych slov - pokud maji jeden znak*/
//  if(!out) return 0;
//  while(i < len)
//  {
//   if(quote)
//   {
//    if(str[i] == quote) /* konec uvozovek */
//    {
//     quote = 0;
//     out[(*argc)++] = (str[i] = 0, &str[arg_start]);
//     arg_start = i + 1;
//    }
//   }
//   else
//   {
//    if(str[i] == ' ') /* mezera mimo uvozovky */
//    {
//     if(i > arg_start) out[(*argc)++] = (str[i] = 0, &str[arg_start]);
//     arg_start = i + 1;
//    }
//    else if(str[i] == '"' || str[i] == '\'') /* zacatek obou druhu uvozovek */
//    {
//     quote = str[i];
//     arg_start = i + 1;
//    }
//   }     
//   i++;
//  }
//  if(i > arg_start) out[(*argc)++] = (str[i] = 0, &str[arg_start]); /* netestovano na neuzavrene uvozovky :-) */
//  return out; 
// } 





char **str2args(char *str, int len, int *argc)
{
 int i = 0, arg_start = 0, quote = 0;
 char **out;

 if(!str && !*str) return 0;
 out = (char **)malloc(sizeof(char *) * (len + 1)); /* maximalni mozny pocet izolovanych slov - pokud maji jeden znak*/
 if(!out) return 0;
 while(i < len)
 {
  if(quote)
  {
   if(str[i] == quote) /* konec uvozovek */
   {
    quote = 0;
    out[(*argc)++] = (str[i] = 0, &str[arg_start]); /* v uvozovkach muze byt i prazdny string */
    arg_start = i + 1;
   }
  }
  else switch(str[i])
  {
   case '"':
   case '\'':
    quote = str[i];
	// break;
   case ' ':
    if(i > arg_start) out[(*argc)++] = (str[i] = 0, &str[arg_start]); /* pouze neprazdne stringy */
    arg_start = i + 1;        
  }
  i++;
 }
 if(i > arg_start) out[(*argc)++] = &str[arg_start]; /* netestovano na neuzavrene uvozovky :-) */
 return out; 
} 





int main(void) 
{ 
 int argc = 0;
 char **argv;
 char *in;


 while (1)
 {

	write(1, "minishell$ ", 11);
			in= get_next_line(0);
			if(!in)
				return (0);

	//const char *in = "prikaz parametr1  parametr2 \"parametr 3\" '  p.4 :-)' param5";
	//const char *in = get_next_line(0);
	int len = strlen(in);
	char *buf = (char *)malloc(sizeof(char) * (len + 1));
	
	strcpy(buf, in);
	argv = str2args(buf, len, &argc);
	if(argv)
	{
	while(argc-- > 0) printf("%d: %s\n", argc, argv[argc]);
	
	}

 }
free(argv);

 return 0;
}