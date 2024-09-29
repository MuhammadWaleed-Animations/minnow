#include "byte_stream.hh"
#include <iostream>
#include <queue>
using namespace std;

ByteStream::ByteStream(uint64_t capacity)
    : capacity_(capacity), a_capacity_(capacity), b_pushed(0), b_popped(0), error_(false), close_(false)
{}

bool Writer::is_closed() const
{
  // Your code here.
  return close_;
}
void Writer::push(std::string data)
{
    if (close_ || error_) return;

    for (char c : data)
    {
        if (a_capacity_ == 0) return;

        sudoQ.push_back(c);
        --a_capacity_;
        ++b_pushed;
    }
}


uint64_t Writer::available_capacity() const
{
    return a_capacity_;
}


void Writer::close()
{
  // Your code here.
  close_ = true;
}


uint64_t Writer::bytes_pushed() const
{
  // Your code here.
  return b_pushed;
}

bool Reader::is_finished() const
{
  // Your code here.
  return close_ && sudoQ.empty();//qbuffer.empty();
}

uint64_t Reader::bytes_popped() const
{
  // Your code here.
  return b_popped;
}
std::string_view Reader::peek() const
{
    if (sudoQ.empty())
        return std::string_view(); // Default-constructed string_view (empty)

    // Create and return a string_view from the buffer
    return std::string_view(sudoQ.data(), sudoQ.size());
}

void Reader::pop(uint64_t len)
{
    if(sudoQ.empty()) return;
    len = std::min(len, sudoQ.size());

    sudoQ.erase(sudoQ.begin(), sudoQ.begin() + len);
    a_capacity_ += len;
    b_popped += len;
}
uint64_t Reader::bytes_buffered() const
{
  // Your code here.
  return (b_pushed - b_popped);
}




// #include "byte_stream.hh"
// #include <iostream>
// #include <queue>
// using namespace std;

// string b="";
// ByteStream::ByteStream( uint64_t capacity ) : capacity_( capacity ),a_capacity_(capacity){ close_ = false;}

// bool Writer::is_closed() const
// {
//   // Your code here.
//   return close_;
// }

// void Writer::push( string data )
// {
//   // Your code here.
//   //(void)data;
//   //uint64_t temp = a_capacity_;
//   if(close_ || error_) return;

//   for(uint64_t i= 0 ;data[i] != '\0';i++)
//   {
//     if(a_capacity_ == 0) return;
//     sudoQ.push_back(data[i]);
//     //qbuffer.push(data[i]);
//     //buffer =  buffer+data[i];
//     a_capacity_ -= 1;
//     b_pushed += 1;
//   }  
//   return;
// }

// void Writer::close()
// {
//   // Your code here.
//   close_ = true;
// }

// uint64_t Writer::available_capacity() const
// {
//   // Your code here.
//   return a_capacity_;
// }

// uint64_t Writer::bytes_pushed() const
// {
//   // Your code here.
//   return b_pushed;
// }

// bool Reader::is_finished() const
// {
//   // Your code here.
//   return close_ && sudoQ.empty();//qbuffer.empty();
// }

// uint64_t Reader::bytes_popped() const
// {
//   // Your code here.
//   return b_popped;
// }

// string_view Reader::peek() const
// {
//   // queue<char> temp =qbuffer;
//   // buffer = "";
//   // while(!temp.empty())
//   // {
//   //     buffer = buffer +temp.front();
//   //     temp.pop();
//   // }
//   // //cout<<b<<std::endl;
  

//   // return buffer;
//   if(sudoQ.empty())
//     buffer = "";
//   else 
//   buffer = string(sudoQ.data(),sudoQ.size());

//   return buffer;
// }

// void Reader::pop( uint64_t len )
// {
//   // for(uint64_t i=0;i<len && a_capacity_<capacity_;i++)
//   // {
//   //     //buffer =  buffer.substr(1);
//   //     qbuffer.pop();
      
//   //     a_capacity_ += 1;
//   //     b_popped += 1;
//   // }
//   if(sudoQ.empty()) return;
//   len = min(len,sudoQ.size());
//   sudoQ.erase(sudoQ.begin(),sudoQ.begin()+len);
//   a_capacity_ += len;
//   b_popped += len;

// }

// uint64_t Reader::bytes_buffered() const
// {
//   // Your code here.
//   return (b_pushed - b_popped);
// }

///////////////////////////////////////////////////////////////////////////////////////////
// #include "byte_stream.hh"
// #include <queue>
// using namespace std;

// ByteStream::ByteStream( uint64_t capacity ) : capacity_( capacity ),a_capacity_(capacity){ close_ = false;}

// bool Writer::is_closed() const
// {
//   // Your code here.
//   return close_;
// }

// void Writer::push( string data )
// {
//   // Your code here.
//   //(void)data;
//   uint64_t temp = a_capacity_;
//   for(uint64_t i= 0 ;i<temp && data[i] != '\0';i++)
//   {
//     buffer =  buffer+data[i];
//     a_capacity_ -= 1;
//     b_pushed += 1;
//   }  
//   return;
// }

// void Writer::close()
// {
//   // Your code here.
//   close_ = true;
// }

// uint64_t Writer::available_capacity() const
// {
//   // Your code here.
//   return a_capacity_;
// }

// uint64_t Writer::bytes_pushed() const
// {
//   // Your code here.
//   return b_pushed;
// }

// bool Reader::is_finished() const
// {
//   // Your code here.
//   return close_ && buffer.size() == 0;
// }

// uint64_t Reader::bytes_popped() const
// {
//   // Your code here.
//   return b_popped;
// }

// string_view Reader::peek() const
// {
//   // Your code here.
//   return buffer;
// }

// void Reader::pop( uint64_t len )
// {
//   for(uint64_t i=0;i<len && a_capacity_<capacity_ ;i++)
//   {
//       buffer =  buffer.substr(1);
//       a_capacity_ += 1;
//       b_popped += 1;
//   }

// }

// uint64_t Reader::bytes_buffered() const
// {
//   // Your code here.
//   return (b_pushed - b_popped);
// }
