/*
 * Seven Kingdoms: Ancient Adversaries
 *
 * Copyright 1997,1998 Enlight Software Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

//Filename    : OSTR.CPP
//Description : Object String

#include <OMISC.h>
#include <OSTR.h>
#include <win32_compat.h>

#if(defined(SPANISH))
	#define THOUSAND_SEPARATOR '.'
	#define DECIMAL_SEPARATOR ','
#else
	#define THOUSAND_SEPARATOR ','
	#define DECIMAL_SEPARATOR '.'
#endif

//------- Define static variable --------//

static char work_buf[MAX_STR_LEN+1];

//-------- Begin of constructor/destructor functions --------//

String::String()
{
   str_buf[0] = '\0';
}

String::String( char *s )
{
   strncpy(str_buf, s, MAX_STR_LEN );
   str_buf[MAX_STR_LEN] = '\0';
}

String::String( const char *s )
{
   strncpy(str_buf, s, MAX_STR_LEN );
   str_buf[MAX_STR_LEN] = '\0';
}

String::String( String& s )
{
   memcpy(str_buf, s.str_buf, MAX_STR_LEN+1 );
}

//---------- End of constructor/destructor functions --------//


//------- Begin of function String::substr --------//
//
// <int> pos = the start position of the sub string you want
//             start from 0, 0-aligned
// [int] len = the length of the sub string
//             (default : till the end of the string
//
char* String::substr(int pos, int len)
{
  work_buf[0] = '\0';

  int strLen = strlen(str_buf);

  if(pos >= strLen)                     // check for boundary errors
     return work_buf;

  if( len <= 0 )
     len = strLen - pos;
  else
  {
     if(len > strLen - pos)
        return work_buf;
  }

  strncpy( work_buf, str_buf+pos, len );
  work_buf[len] = '\0';

  return work_buf;
}

//------- End of function String::substr ------------//


//------- Begin of function String::upper/lower -------//

char* String::upper()
{
   memcpy( work_buf, str_buf, len()+1 );
   strupr( work_buf );

   return work_buf;
}

char* String::lower(void)
{
   memcpy( work_buf, str_buf, len()+1 );
   strlwr( work_buf );

   return work_buf;
}

//--------- End of function String::upper/lower --------//


//-------- Begin of function String::at ---------------//
//
// <char*> searchStr = the string you want to search for
//
// return : >= 0 the position of the search str in the string
//          = -1 if not found
//
int String::at(char* searchStr)
{
  int pos;
  char *tmp;

  if( (tmp = strstr(str_buf, searchStr)) != NULL)
    pos = (int)(tmp-str_buf);
  else
    pos = -1;

  return pos;
}
//---------- End of function String::at ---------------//


//-------- Begin of operator= functions -----------//

String& String::operator=(String& s)
{
   memcpy(str_buf, s.str_buf, MAX_STR_LEN+1 );

   return *this;
}

String& String::operator=(char *s)
{
   strncpy(str_buf, s, MAX_STR_LEN );
   str_buf[MAX_STR_LEN] = '\0';

   return *this;
}

String& String::operator=(const char *s)
{
   strncpy(str_buf, s, MAX_STR_LEN );
   str_buf[MAX_STR_LEN] = '\0';

   return *this;
}

String& String::operator=(long value)
{
   strncpy(str_buf, format(value, 4), MAX_STR_LEN);
   str_buf[MAX_STR_LEN] = '\0';

   return *this;
}
//---------- End of operator= functions -----------//


//-------- Begin of operator+= functions -----------//

String& String::operator+=(String& s)
{
   strncat( str_buf, s.str_buf, MAX_STR_LEN );
   str_buf[MAX_STR_LEN] = '\0';
   return *this;
}

String& String::operator+=(char *s)
{
   strncat( str_buf, s, MAX_STR_LEN );
   str_buf[MAX_STR_LEN] = '\0';
   return *this;
}

String& String::operator+=(const char *s)
{
   strncat( str_buf, s, MAX_STR_LEN );
   str_buf[MAX_STR_LEN] = '\0';
   return *this;
}

String& String::operator+=(long value)
{
   strncat( str_buf, format(value, 4), MAX_STR_LEN );
   str_buf[MAX_STR_LEN] = '\0';
   return *this;
}

//---------- End of operator+= functions -----------//


//-------- Begin of operator*= functions -----------//

String& String::operator*=(int n)
{
  memcpy( work_buf, str_buf, len()+1 );

  for(int i=1; i<n; i++)
     strncat(str_buf, work_buf, MAX_STR_LEN);

  str_buf[MAX_STR_LEN] = '\0';

  return *this;
}

//---------- End of operator*= functions -----------//

char* String::format( int inNum, int formatType )
{
   static char outBuf[35];
   static char longBuf[25];
   char   *outPtr=outBuf;
   char   *longStr;
   int    i, intDigit, sign;

   if( inNum < 0 )
   {
      sign  = -1;
      inNum = -inNum;
   }
   else
      sign  = 0;

   longStr  = ltoa( inNum, longBuf, 10 );
   intDigit = strlen(longStr);  // no. of integer digits

   //--------- negetive bracket ------------//

   if( sign < 0 )
      *outPtr++ = '(';

   //--------- dollar sign ------------//

	if( formatType == 2 )
      *outPtr++ = '$';

	//-------- integer number -----------//

	for( i=intDigit ; i>0 ; i-- )
	{
		if( formatType != 4 )		// no thousand separators for format 4
		{
			if( i%3 == 0 && i < intDigit )
				*outPtr++ = THOUSAND_SEPARATOR;
		}

		*outPtr++ = *longStr++;
	}

	//--------- percent sign (%) ------------//

	if( formatType == 3 )
      *outPtr++ = '%';

   //--------- negetive bracket ----------//

   if( sign < 0 )
      *outPtr++ = ')';

   *outPtr++ = '\0';

   return outBuf;
}

