#include "reassembler.hh"
#include <iostream>
using namespace std;


void Reassembler::insert(uint64_t first_index, string data, bool is_last_substring) {

    //handel last substring ka last index
    if(is_last_substring)
    {
      lastIndex = true;
      last_index = first_index+data.size();
    }
    if (closed) return;

    // Ignore inserts that are less than the next_index
    if (first_index + (uint64_t)data.size()< next_index) return;  //before start of required
    if(first_index> next_index + output_.writer().available_capacity()) return;  //after end of what we want to store
    
    //this works as we are now sure we get some chars that are surely part of our required string of chars
    if (first_index <= next_index) { 
        data = data.substr(next_index-first_index); //removing unnecessary part from start
        first_index = next_index; //as indexes before next_index are already handeled

        string bytes_to_push = ""; //initiliizing string
        uint64_t avalCap = output_.writer().available_capacity(); //how much we can at max store in buffer at this moment
        for(char a :data) {  //looping on all the chars
            if(avalCap <= 0)
            {
              break; //got all chars we can handel
            }
            
            bytes_to_push += a; //storing char
            avalCap--; //handling avalible capacity
            if(vbuffer[pick].first == next_index) //if it was already buffered
            {
              vbuffer[pick] = make_pair(-1, 'W');  //make it default
              bytes_buffered--; //descrease count of buffered bytes
            }
            pick = (pick+1)%capacity_; // slide window to right
            next_index++; //increment index of next required byte
        }
        output_.writer().push(bytes_to_push); //push bytes that we stored above as they are at the begining of the window

        bytes_to_push = "";
        while(vbuffer[pick].first == next_index && output_.writer().available_capacity() > 0)
        {
            bytes_to_push += vbuffer[pick].second; //concatinate ordered chars
            vbuffer[pick] = make_pair(-1, 'W');  //make it default
            pick = (pick+1)%capacity_; // slide window to right
            next_index++; //move to next required index 
            bytes_buffered--;  //descrease count of buffered bytes
        }
        output_.writer().push(bytes_to_push); //push required string in order

    }
    else
    {
      for(uint64_t i= first_index;i<(uint64_t)data.size()+first_index && output_.reader().bytes_popped()+capacity_>i && first_index - next_index < capacity_;i++)
      {
        uint64_t temp = -1; //to match with -1
        if(vbuffer[(pick + i - next_index)%capacity_].first == temp)
        {
          vbuffer[(pick + i - next_index)%capacity_] = make_pair(i,data[i - first_index]);
          bytes_buffered++;
        }
      }
    }

    if(lastIndex &&last_index<= next_index && bytes_buffered ==0 ) // closed + no bytes left
    {
      closed = true;
      output_.writer().close();
    }
}

uint64_t Reassembler::bytes_pending() const
{
  
  return bytes_buffered;
}
















// #include "reassembler.hh"
// #include <iostream>
// using namespace std;


// void Reassembler::insert(uint64_t first_index, string data, bool is_last_substring) {


//     //handel last substring ka last index
//     if(is_last_substring)
//     {
//       lastIndex = true;
//       last_index = first_index+data.size();
//     }
//     if (closed) return;

//     // Ignore inserts that are less than the next_index
//     if (first_index + (uint64_t)data.size()< next_index) return;  //before start of required
//     if(first_index> next_index + output_.writer().available_capacity()) return;  //after end of what we want to store


//     //this works as we are now sure we get some chars that are surely part of our required string of chars
//     if (first_index <= next_index) { 
//         data = data.substr(next_index-first_index); //removing unnecessary part from start
//         first_index = next_index; //as indexes before next_index are already handeled

//         string bytes_to_push = ""; //initiliizing string
//         uint64_t avalCap = output_.writer().available_capacity(); //how much we can at max store in buffer at this moment
//         for(char a :data) {  //looping on all the chars
//             if(avalCap <= 0)
//             {
//               break; //got all chars we can handel
//             }
            
//             bytes_to_push += a; //storing char
//             avalCap--; //handling avalible capacity
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


//         while(buffer_.find(next_index) != buffer_.end()  && output_.writer().available_capacity() > 0)
//         {
//             //cout<<"------------"<<bytes_buffered<<"  data "<<buffer_[next_index]<<" next index "<<next_index<<endl;
            
//             //cout<<""<<buffer_[next_index]<<"";
//             output_.writer().push(buffer_[next_index]);
//             buffer_.erase(next_index);
//             next_index++;
//             bytes_buffered--;
//             //cout<<buffer_[next_index-1];

//             //cout<<(buffer_.find(next_index) != buffer_.end())<<"     capacity : "<< (output_.writer().available_capacity())<<endl;
//         }

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


//         }
//       }
//     }

//     if(lastIndex &&last_index<= next_index && bytes_buffered ==0 )
//     {
//       closed = true;
//       output_.writer().close();
//     }
// }

// uint64_t Reassembler::bytes_pending() const
// {
  
//   return bytes_buffered;
// }
