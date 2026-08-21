/*
Problem: Lazy File Reader Proxy
You are given a file-reading system.
Reading a large file is expensive, so the application should not actually load the file until the client requests its contents.
You must implement a Virtual Proxy.
Requirements
Create the following classes.
1. File
Create an abstract interface:
class File {
public:
    virtual std::string Read() = 0;
    virtual ~File() = default;
};
2. RealFile
Implement File.
It should contain:
std::string filename_;
Constructor:
RealFile(const std::string& filename);
When Read() is called, it should print:
Loading file: <filename>
and return:
Contents of <filename>
3. FileProxy
Implement File.
The proxy should contain a pointer/unique_ptr to RealFile.
Important requirement:
The RealFile must not be created inside the FileProxy constructor.
Instead, it must be created the first time Read() is called.
Therefore:
FileProxy proxy("movie.txt");
must not print:
Loading file: movie.txt
But:
proxy.Read();
should create the RealFile and then delegate the call to it.
Subsequent calls to:
proxy.Read();
must reuse the same RealFile.
So the real file should be created exactly once.
You only implement these
You need to write:
class File
class RealFile
class FileProxy
Do not write main().
I will provide the main() for you so that you only have to concentrate on the Proxy pattern.
The test program is:
int main() {
    std::unique_ptr<File> file =
        std::make_unique<FileProxy>("movie.txt");

    std::cout << "Proxy created\n";

    std::cout << file->Read() << '\n';

    std::cout << "Reading again\n";

    std::cout << file->Read() << '\n';

    return 0;
}
Expected output
Proxy created
Loading file: movie.txt
Contents of movie.txt
Reading again
Contents of movie.txt
Notice something important:
Proxy created
appears before:
Loading file: movie.txt
That proves lazy initialization is happening.
And because Loading file appears only once, the proxy must reuse the same RealFile.
Your task
Implement only:
class File
class RealFile
class FileProxy
using appropriate C++ ownership (std::unique_ptr is recommended).
*/
#include <iostream>
#include <string>
#include <memory>

class File {
protected:
  std::string filename_;
public:
  File(std::string filename) : filename_(filename) {}
  virtual std::string Read() = 0;
  virtual ~File() = default;
};

class RealFile : public File {

public:
  RealFile(std::string filename) : File(filename) {}
  std::string Read() override {
    std::cout << "Loading file: " << filename_ <<"\n";
    return "Contents of " + filename_;
  }
};

class FileProxy : public File {
  std::unique_ptr<RealFile> file_;
public:
  FileProxy(std::string filename) : File(filename) {}
  std::string Read() override {
    if(file_ == nullptr) {
      file_ = std::make_unique<RealFile>(filename_);
    }
    return file_->Read();
  }

};

int main() {
    std::unique_ptr<File> file =
        std::make_unique<FileProxy>("movie.txt");

    std::cout << "Proxy created\n";

    std::cout << file->Read() << '\n';

    std::cout << "Reading again\n";

    std::cout << file->Read() << '\n';

    return 0;
}