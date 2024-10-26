#include "wrapping_integers.hh"
#include <cmath>
#include <iostream>
using namespace std;

Wrap32 Wrap32::wrap( uint64_t n, Wrap32 zero_point )
{
  return Wrap32{static_cast<uint32_t>(((n % 4294967296) + (zero_point.raw_value_ % 4294967296))%4294967296)};
}

uint64_t Wrap32::unwrap( Wrap32 zero_point, uint64_t checkpoint ) const
{
    uint64_t uint32 = 4294967296;
    uint64_t sudo_abs = 0;
    if (zero_point.raw_value_ <= raw_value_)   sudo_abs = raw_value_ - zero_point.raw_value_;
    else    sudo_abs = (uint32 -zero_point.raw_value_) + raw_value_ ;

    uint64_t quotient = checkpoint / uint32;

    uint64_t op1 = sudo_abs + ((quotient-1) * uint32);
    uint64_t op2 = sudo_abs + ((quotient) * uint32);
    uint64_t op3 = sudo_abs + ((quotient+1) * uint32);

    long long diff1 = op1- checkpoint;
    long long diff2 = op2- checkpoint;
    long long diff3 = op3- checkpoint;

    if (diff1 < 0 ) diff1 = -1 * diff1; 
    if (diff2 < 0 ) diff2 = -1 * diff2;
    if (diff3 < 0 ) diff3 = -1 * diff3; 

    //cout<<"Sudo Absolute value: "<<sudo_abs <<"\nQuotient: "<<quotient<<"\nCheckPoint: "<<checkpoint<<endl;
    // std::cout <<"op1 " << op1 << std::endl;
    // std::cout <<"op2 " << op2 << std::endl;
    // std::cout <<"op3 " << op3 << std::endl;
    // std::cout <<"diff1 " << diff1 << std::endl;
    // std::cout <<"diff2 " << diff2 << std::endl;
    // std::cout <<"diff3 " << diff3 << std::endl;


    if (diff1 <= diff2 && diff1 <= diff3 && quotient > 0)   return op1;
    else if (diff3 <= diff1 && diff3 <= diff2)   return op3;
    else return op2;

}
