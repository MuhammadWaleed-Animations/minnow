#include "socket.hh"

#include <cstdlib>
#include <iostream>
#include <span>
#include <string>

using namespace std;

#include <vector>

void get_URL( const string& host, const string& path )
{
  //cerr << "Function called: get_URL(" << host << ", " << path << ")\n";
  //cerr << "Warning: get_URL() has not been implemented yet.\n";
  //cout<<"Bri der krdi meharban atay atay.\n";
  //cout<<":)\n";


  Address adr(host,"80");

  TCPSocket tcps;
  tcps.connect(adr);
  //cout<<"connect done------------\n";
  vector<string> v;
  string s = "GET "+path+" HTTP/1.1\r\n";
  v.push_back(s);
  s= "HOST: "+host+"\r\n";
  v.push_back(s);
  s= "Connection: close\r\n";
  v.push_back(s);
  s= "\r\n";
  v.push_back(s);
  // for(auto i :v)
  // {
  //   cout<<i;
  // }
  
  tcps.write(v);
  
  string r;
  tcps.read(r);
  int n = 0;
  while(r[0] != 0 && n<4){
    cout<<r;
    tcps.read(r);
  }

  // // cout<<"--------"<<endl;
  tcps.close();
}

int main( int argc, char* argv[] )
{
  try {
    if ( argc <= 0 ) {
      abort(); // For sticklers: don't try to access argv[0] if argc <= 0.
    }

    auto args = span( argv, argc );

    // The program takes two command-line arguments: the hostname and "path" part of the URL.
    // Print the usage message unless there are these two arguments (plus the program name
    // itself, so arg count = 3 in total).
    if ( argc != 3 ) {
      cerr << "Usage: " << args.front() << " HOST PATH\n";
      cerr << "\tExample: " << args.front() << " stanford.edu /class/cs144\n";
      return EXIT_FAILURE;
    }

    // Get the command-line arguments.
    const string host { args[1] };
    const string path { args[2] };

    // Call the student-written function.
    get_URL( host, path );
  } catch ( const exception& e ) {
    cerr << e.what() << "\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}