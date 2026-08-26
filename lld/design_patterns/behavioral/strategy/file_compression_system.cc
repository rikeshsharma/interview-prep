/*
Problem: File Compression System
You are designing a file compression system.
The application can compress files using different algorithms:
- ZIP
- GZIP
- BZIP2
Each compression algorithm has:
compress(...)
and should return the compressed size.
The application should also be able to change the compression algorithm at runtime.
Requirements
You need to design:
1. CompressionStrategy
An abstract Strategy interface.
It should provide:
virtual int compress(const std::string& filename,
                     int originalSize) = 0;
2. Three concrete strategies
Implement:
ZipCompression
GzipCompression
Bzip2Compression
Each should implement compress().
For the purpose of this exercise, use these compression rules:
ZIP   → 70% of original size
GZIP  → 60% of original size
BZIP2 → 50% of original size
Since the return type is int, make sure your implementation handles the conversion correctly.
For example, if:
originalSize = 101
then:
ZIP = 70% → 70
GZIP = 60% → 60
BZIP2 = 50% → 50
You may use integer arithmetic.
3. FileCompressor
This is your Context.
It must:
- store a CompressionStrategy
- allow the strategy to be changed at runtime
- provide:
int compressFile(const std::string& filename,
                 int originalSize);
compressFile() should delegate the actual compression to the current strategy.
You should not put ZIP/GZIP/BZIP2 logic inside FileCompressor.
Important constraints
Do not:
- use if/else based on compression type inside FileCompressor
- use switch
- use an enum to select the algorithm
- implement compression directly inside FileCompressor
- create separate compressFile() implementations for every algorithm
The point is to demonstrate Strategy + polymorphism + composition.
Your task
Implement everything marked TODO below.
*/

#include <iostream>
#include <memory>
#include <string>

class CompressionStrategy {
public:
    virtual int compress(const std::string& filename, 
                              int originalSize) = 0;
    virtual ~CompressionStrategy() = default;
};


class ZipCompression : public CompressionStrategy {
public:
    int compress(const std::string& filename,
                  int originalSize) override {
      return static_cast<int>(0.7*originalSize);
    }
};


class GzipCompression : public CompressionStrategy {
public:
    int compress(const std::string& filename,
                  int originalSize) override {
      return static_cast<int>(0.6*originalSize);
    }
};


class Bzip2Compression : public CompressionStrategy {
public:
    int compress(const std::string& filename,
                  int originalSize) override {
      return static_cast<int>(0.5*originalSize);
    }
};


class FileCompressor {
private:
    std::unique_ptr<CompressionStrategy> compression_strategy_;
public:
    FileCompressor(std::unique_ptr<CompressionStrategy> strategy)
                  : compression_strategy_(std::move(strategy)) {}

    void setStrategy(std::unique_ptr<CompressionStrategy> strategy) {
      compression_strategy_ = std::move(strategy);
    }

    int compressFile(const std::string& filename, int originalSize) {
        return compression_strategy_->compress(filename, originalSize);
    }
};


int main() {

    FileCompressor compressor(
        std::make_unique<ZipCompression>()
    );

    std::cout << compressor.compressFile(
        "movie.mkv", 1000
    ) << '\n';


    compressor.setStrategy(
        std::make_unique<GzipCompression>()
    );

    std::cout << compressor.compressFile(
        "movie.mkv", 1000
    ) << '\n';


    compressor.setStrategy(
        std::make_unique<Bzip2Compression>()
    );

    std::cout << compressor.compressFile(
        "movie.mkv", 1000
    ) << '\n';


    return 0;
}

/*
Expected output
700
600
500
Your challenge: fill in only the TODOs.
The important part isn't just making it compile. While implementing it, ask yourself:
"Why does FileCompressor know about CompressionStrategy, but not ZipCompression, GzipCompression, or Bzip2Compression?"
*/