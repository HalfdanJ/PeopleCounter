#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *make_words(char *s, int ncomma);
char *insert_comma(long n, int *ncomma);
char *int2words(int n);


char *make_words(char *s, int ncomma)
{
  int i, len, rest = 0;
  char *p = NULL;
  static char zzz[256];

  static char *ones[] = {"one ","two ","three ","four ",
			 "five ","six ","seven ","eight ","nine "};
  // the odd balls
  static char *tens[] = {"ten ","eleven ","twelve ","thirteen ",
			 "fourteen ","fifteen ","sixteen ","seventeen ","eighteen ","nineteen "};
  // from here on a more logic order sets in
  static char *twenties[] = {"","twenty ","thirty ","forty ",
			     "fifty ","sixty ","seventy ","eighty ","ninety "};
  static char *hundreds[] = {
    "hundred ","thousand ","million "};

  memset(zzz, '\0', 256); // fill with nulls
  len = strlen(s);
  for(i = 0; i < len; i++)
    {

      // for testing
      //printf("i = %d rest = %d ncomma = %d s[%d] = %c len = %d zzz = %s\n", i, rest, ncomma, i, s[i], len, zzz);

      // skip the comma
      if ((p = strchr((s[i] == ',') ? &s[++i] : &s[i], ',')) == NULL)
	{
	  p = &s[strlen(s)];
	}
      if (s[i] == '0')
	{
	  continue; // skip one iteration
	}
      if ((rest = (p - &s[i])) != 0)
	{
	  if (rest == 3)
	    {
	      strcat(zzz, ones[s[i] - '0' - 1]);
	      strcat(zzz, hundreds[0]);
	      // special cases
	      if (len == 7 && s[2] == '0') strcat(zzz, hundreds[1]);
	      if (len == 11 && s[2] == '0') strcat(zzz, hundreds[2]);
	    }
	  else if (rest == 2) 
	    {
	      if (s[i] == '1')
		{
		  strcat(zzz, tens[s[++i] - '0']);
		  rest--;
		}
	      else
		{
		  strcat(zzz, twenties[s[i] - '0' - 1]);
		}
	    }
	  else
	    strcat(zzz, ones[s[i] - '0' - 1]);
	}
      if (rest == 1 && ncomma != 0)
	{
	  strcat(zzz, hundreds[ncomma--]);
	}
    }
  return zzz;
}

// insert a comma every third place from right to help in make_words
// returns the modified numeric string and the number of commas
char *insert_comma(long n, int *ncomma)
{
  static char zzz[30];
  int i = 0;
  char *p = &zzz[sizeof(zzz)-1];

  *p = '\0';
  *ncomma = 0;
  do 
    {
      if (i % 3 == 0 && i != 0) 
	{
	  *--p = ',';
	  ++*ncomma;
	}
      *--p = (char)('0' + n % 10);
      n /= 10;
      i++;
    } while(n != 0);
  return p;
}

char *int2words(int n)
{
  int nc;
  char *ps, *zzz, *minus;
  char *buffer;
  buffer = (char *) malloc(256);

  // save any - sign
  if (n < 0)
    {
      minus = "minus";
      n = abs(n);
    }
  else
    {
      minus = "";
    }

  ps = insert_comma(n, &nc);
  // ps is the comma modified numeric string, nc is the number of commas
  zzz = make_words(ps, nc);

  // if there was a - sign add it back
  sprintf(buffer,"%s %s", minus, zzz);

  return buffer;
}
