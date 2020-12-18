#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <vector>
#include <boost/align/aligned_allocator.hpp>
#include <hayai/hayai.hpp>
#include "test.hpp"

// TEST FUNCTION //
// params: * filepath - path to file,
//         * mode (true - direct reading using O_DIRECT, false - standart reading)
//         * blocks_count - count of block need to be read
void MyTest::MakeTest(const char filepath[], bool mode, int blocks_count)
{
    int fd;
    if (mode == true)
    {
        fd = open(filepath, O_DIRECT | O_RDONLY);
    }
    else
    {
        fd = open(filepath, O_RDONLY);
    }

    if (fd == -1)
    {
        std::cerr << "File open ERROR: " << strerror(errno) << '\n';
    }

    struct stat file_stat;
    const long block_size = 4096;

    std::random_device rd;
    std::mt19937 gen(rd());

    fstat(fd, &file_stat);
    std::uniform_int_distribution<> distrib(0, file_stat.st_size / block_size);
    std::vector<char, boost::alignment::aligned_allocator<char, block_size>> buffer(block_size);

    int i;
    for (i = 0; i < blocks_count; i++)
    {
        int rr = pread(fd, &(buffer[0]), block_size, distrib(gen) * block_size);
        if (rr == -1)
        {
            std::cerr << "File read ERROR: " << strerror(errno) << '\n';
        }
    }
    close(fd);
}



// BENCHMARKS //
// params: group name, test name, number of runs, number of iterations
int runs = 1;
int iterations = 10;
const char path[] = "/home/user/Projects/stpoi/big_data2.txt";

BENCHMARK(MyTest, StdReadingTest, runs, iterations)
{
    MyTest().MakeTest(path, false, 100);
}

BENCHMARK(MyTest, DirectReadingTest, runs, iterations)
{
    MyTest().MakeTest(path, true, 100);
}





