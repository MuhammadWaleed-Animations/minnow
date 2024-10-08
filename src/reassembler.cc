#include "reassembler.hh"
#include <iostream>
using namespace std;


// void Reassembler::insert(uint64_t first_index, string data, bool is_last_substring) {
//     if(is_last_substring)
//     {
//       lastIndex = true;
//       last_index = first_index+data.size();
//     }
//     if (closed) return;
//
//     // Ignore inserts that are less than the next_index
//     if (first_index + (uint64_t)data.size()< next_index) return;
//     if(first_index> next_index + output_.writer().available_capacity()) return;
//     //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//     //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     if (first_index <= next_index) {
//         data = data.substr(next_index-first_index);
//         first_index = next_index;
//         // for(int i = 0;output_.writer().available_capacity() > 0 && data[i] != '\0';i++) {
//         //     char byte = data[i];
//         //     output_.writer().push(string(1, byte));
//         //     if(buffer_.find(next_index) != buffer_.end())
//         //     {
//         //       buffer_.erase(next_index);
//         //       bytes_buffered--;
//         //     }
//         //     //cout<<"Next index: "<<next_index<<" byte "<<byte<<"  bytes_buffered- "<<bytes_buffered<<endl;
//         //     next_index++;
//         // }
//
//         //-------------------------------------------------------
//         string bytes_to_push = "";
//         uint64_t avalCap = output_.writer().available_capacity();
//         for(char a :data) {
//             if(avalCap <= 0)
//             {
//               break;
//             }
//             //output_.writer().push(string(1,a));
//             bytes_to_push += a;
//             avalCap--;
//             if(buffer_.find(next_index) != buffer_.end())
//             {
//               buffer_.erase(next_index);
//               bytes_buffered--;
//             }
//             //cout<<"Next index: "<<next_index<<" byte "<<byte<<"  bytes_buffered- "<<bytes_buffered<<endl;
//             next_index++;
//         }
//         output_.writer().push(bytes_to_push);
//         //-------------------------------------------------------
//
//
//         while(buffer_.find(next_index) != buffer_.end()  && output_.writer().available_capacity() > 0)
//         {
//             //cout<<"------------"<<bytes_buffered<<"  data "<<buffer_[next_index]<<" next index "<<next_index<<endl;
//            
//             //cout<<""<<buffer_[next_index]<<"";
//             output_.writer().push(buffer_[next_index]);
//             buffer_.erase(next_index);
//             next_index++;
//             bytes_buffered--;
//             //cout<<buffer_[next_index-1];
//
//             //cout<<(buffer_.find(next_index) != buffer_.end())<<"     capacity : "<< (output_.writer().available_capacity())<<endl;
//         }
//
//     }
//     else
//     {
//       for(uint64_t i= first_index;i<(uint64_t)data.size()+first_index && output_.reader().bytes_popped()+capacity_>i ;i++)
//       {
//         if(!(buffer_.find(i) != buffer_.end()))
//         {
//           buffer_[i] = string(1,data[i-first_index]);
//           //cout<<"bytes_buffered: "<<bytes_buffered<<"  - "<<data[i-first_index]<<" f"<<i<<endl;
//           bytes_buffered = bytes_buffered +1;
//
//
//         }
//       }
//     }
//
//     if(lastIndex &&last_index<= next_index && bytes_buffered ==0 )
//     {
//       closed = true;
//       output_.writer().close();
//     }
// }

void Reassembler::insert(uint64_t first_index, string data, bool is_last_substring) {
    if(is_last_substring)
    {
      lastIndex = true;
      last_index = first_index+data.size();
    }
    if (closed) return;

    // Ignore inserts that are less than the next_index
    if (first_index + (uint64_t)data.size()< next_index) return;
    if(first_index> next_index + output_.writer().available_capacity()) return;

    if (first_index <= next_index) {
        data = data.substr(next_index-first_index);
        first_index = next_index;
        string bytes_to_push = "";
        uint64_t avalCap = output_.writer().available_capacity();
        for(char a :data) {
            if(avalCap <= 0)
            {
              break;
            }
            //output_.writer().push(string(1,a));
            bytes_to_push += a;
            avalCap--;
            if(buffer_.find(next_index) != buffer_.end())
            {
              buffer_.erase(next_index);
              bytes_buffered--;
            }
            //cout<<"Next index: "<<next_index<<" byte "<<byte<<"  bytes_buffered- "<<bytes_buffered<<endl;
            next_index++;
        }
        output_.writer().push(bytes_to_push);


        while(buffer_.find(next_index) != buffer_.end()  && output_.writer().available_capacity() > 0)
        {
            //cout<<"------------"<<bytes_buffered<<"  data "<<buffer_[next_index]<<" next index "<<next_index<<endl;
            
            //cout<<""<<buffer_[next_index]<<"";
            output_.writer().push(buffer_[next_index]);
            buffer_.erase(next_index);
            next_index++;
            bytes_buffered--;
            //cout<<buffer_[next_index-1];

            //cout<<(buffer_.find(next_index) != buffer_.end())<<"     capacity : "<< (output_.writer().available_capacity())<<endl;
        }

    }
    else
    {
      for(uint64_t i= first_index;i<(uint64_t)data.size()+first_index && output_.reader().bytes_popped()+capacity_>i ;i++)
      {
        if(!(buffer_.find(i) != buffer_.end()))
        {
          buffer_[i] = string(1,data[i-first_index]);
          //cout<<"bytes_buffered: "<<bytes_buffered<<"  - "<<data[i-first_index]<<" f"<<i<<endl;
          bytes_buffered = bytes_buffered +1;


        }
      }
    }

    if(lastIndex &&last_index<= next_index && bytes_buffered ==0 )
    {
      closed = true;
      output_.writer().close();
    }
}


uint64_t Reassembler::bytes_pending() const
{
  
  return bytes_buffered;
}
