#ifndef SDDS_TRANSCRIPT_FIX_H_
#define SDDS_TRANSCRIPT_FIX_H_
#include <iostream>
namespace sdds
{
   class TranscriptFix
   {
      char* m_content{};
      int getFileLength(std::istream& istr = std::cin)const;
   public:
      TranscriptFix() = default;
      TranscriptFix& operator=(const TranscriptFix& text) = delete;
      std::istream& read(std::istream& istr = std::cin);
      std::ostream& write(std::ostream& ostr = std::cout)const;
      virtual ~TranscriptFix();
   };

   // Helper functions
   std::ostream& operator<<(std::ostream& ostr, const TranscriptFix& text);
   std::istream& operator>>(std::istream& istr, TranscriptFix& text);
}
#endif
