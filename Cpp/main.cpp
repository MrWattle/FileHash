#include <fstream>
#include <iostream>
#include <openssl/sha.h>

#define BUF_SIZE 4096

int main(int argc, char** argv)
{
    std::ifstream input_stream;
    SHA_CTX context;
    unsigned char out_hash[SHA_DIGEST_LENGTH];
    char buf[BUF_SIZE];

    if (argc != 2)
    {
        std::cerr<<"Use format: ./hash <file>"<<std::endl;
        return 1;
    }

    input_stream.open(argv[1], std::ios_base::in | std::ios_base::binary);
    if (!input_stream.is_open())
    {
        std::cerr<<"Can't read file: "<<argv[1]<<std::endl;
        return 1;
    }

    SHA1_Init(&context);
    do {
        input_stream.read(buf, BUF_SIZE);
        SHA1_Update(&context, buf, input_stream.gcount());
    } while (input_stream.gcount() > 0);

    input_stream.close();
    SHA1_Final(out_hash, &context);

    std::cout<<"SHA1("<<argv[1]<<")= ";
    for (int i = 0; i<SHA_DIGEST_LENGTH; i++)
        std::cout<<std::hex<<(short)out_hash[i];
    std::cout<<std::endl;

    return 0;
}
