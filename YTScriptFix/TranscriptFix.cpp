/* Citation and Sources...
Workshop 09
Module: Text
Filename: Text.cpp
Version 1.0
Author	Peter Wan
Revision History
-----------------------------------------------------------
Date          Reason
Nov 23        Preliminary submission
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------
OR
-----------------------------------------------------------
Write exactly which part of the code is given to you as help and
who gave it to you, or from what source you acquired it.
-----------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "TranscriptFix.h"

using namespace sdds;
using namespace std;

namespace sdds
{
   int TranscriptFix::getFileLength(std::istream& istr) const
   {
      int len{};
            
      if (istr)
      {
         // save the current read position
         std::streampos cur = istr.tellg();
         // go to the end
         istr.seekg(0, ios::end);
         // tell what is the positions (end position = size)
         len = unsigned(istr.tellg());
         // now go back to where you were.
         istr.seekg(cur);
      }
      return len;
   }

   std::istream& TranscriptFix::read(std::istream& istr)
   {
      int i;
      int fileLength;

      // Gets the amount of readable characters from the file 
      fileLength = getFileLength(istr);

      // Allocates memory to the size of the file on the disk
      // Note, getFileLength may return extra characters on different Operating
      // Systems when encountering a newline.
      // One system may read \r\n, the other might read just \n;
      m_content = new char[fileLength + 1];

      // istr.get(char&) evaluates returns istr. When istr is used
      // as a boolean, it return true if it's in a good state or
      // if it's in a bad state. In this case, it returns true if it
      // reads a character from the stream and false when it hits EOF. 
      // It will also set the char& to equal the value it reads from the stream
      // (not including EOF). Since reading the EOF set istr to a fail state,
      // we clear it afterwards.
      for (i = 0; i < fileLength && istr.get(m_content[i]); i++);

      // Null terminates the string
      m_content[i] = '\0';

      // If any data is read (we can check this via m_content),
      // clear() the state of the istream object.
      // Otherwise, leave it as is.
      if (m_content[0])  istr.clear();

      return istr;
   }

   std::ostream& TranscriptFix::write(std::ostream& ostr) const
   {
      int len = strlen(m_content);
      int newlineCount = 0;
      bool reduceNewline = true;

      if (!m_content[0])
      {
         std::cout << "No data was read from the data file." << std::endl;
      }
      else
      {
         for (int i = 0; i < len; i++)
         {            
            if (reduceNewline && m_content[i] == '\n')
            {
               ostr << " ";
               newlineCount++;
               if (newlineCount == 2)
               {
                  reduceNewline = false;
                  newlineCount = 0;
               }
            }
            else
            {
               ostr << m_content[i];
               if (m_content[i] == '\n')
               {
                  reduceNewline = true;
               }
            }
         }
      }

      return ostr;
   }

   TranscriptFix::~TranscriptFix()
   {
      delete[] m_content;
   }

   std::ostream& operator<<(std::ostream& ostr, const TranscriptFix& text)
   {
      return text.write(ostr);
   }

   std::istream& operator>>(std::istream& istr, TranscriptFix& text)
   {
      return text.read(istr);
   }
}