// #include <fstream>
// #include <boost/iostreams/filtering_streambuf.hpp>
// #include <boost/iostreams/stream.hpp>
// #include <boost/iostreams/filter/bzip2.hpp>
// #include <boost/iostreams/device/array.hpp>
// #include <boost/iostreams/copy.hpp>
// namespace io = boost::iostreams;
// int main()
// {
//     const size_t N = 1000000;
//     char* volume = new char[N];
//     std::fill_n(volume, N, 'a'); // 100,000 letters 'a'

//     io::stream< io::array_source > source (volume, N);

//     {  
//       std::ofstream file("volume.bz2", std::ios::out | std::ios::binary); 
//       io::filtering_streambuf<io::output> outStream; 
//       outStream.push(io::bzip2_compressor()); 
//       outStream.push(file); 
//       io::copy(source, outStream); 
//      }
//     // Volume.bz2 is written and closed. File size 48 bytes long
// }

#include <ostream>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/stream.hpp>

namespace io = boost::iostreams;

int main()
{
    io::stream_buffer<io::file_sink> buf("log.txt");
    std::ostream                     out(&buf);
    // out writes to log.txt
}