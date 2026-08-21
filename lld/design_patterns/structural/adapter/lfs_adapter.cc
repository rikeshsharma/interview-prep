#include <iostream>
#include <string>

/*
Problem: File Storage Adapter
Imagine you're building a browser download manager.
Your application expects every storage system to provide:
*/

class Storage {
public:
    virtual void Save(const std::string& filename,
                      const std::string& data) = 0;

    virtual ~Storage() = default;
};

/*
Your existing application already has code that works with Storage.
However, you need to integrate this old third-party class:
*/

class LegacyFileSystem {
public:
    void WriteFile(const char* path,
                   const char* contents,
                   int size) {
        // Imagine this writes the data to disk.
        std::cout << "Writing " << size
                  << " bytes to " << path << '\n';
    }
};

/*
You must not modify LegacyFileSystem.
Your job is to implement:
*/
class LegacyFileSystemAdapter : public Storage {
    // Your implementation
    LegacyFileSystem lfs_object;
    public:
    LegacyFileSystemAdapter(LegacyFileSystem legacy) : lfs_object(legacy) {}
    void Save(const std::string& filename,
              const std::string& data) override {
                lfs_object.WriteFile(filename.c_str(),
                                     data.c_str(), 
                                     static_cast<int>(data.size()));
              }
};
/*
So that this works:
*/
int main() {
    LegacyFileSystem legacy;

    LegacyFileSystemAdapter storage(legacy);

    storage.Save("download.txt", "Hello Chromium!");

    return 0;
}

/*
The output should effectively be:
Writing 16 bytes to download.txt
Constraints
LegacyFileSystem cannot be modified.

Storage cannot be modified.

LegacyFileSystemAdapter must implement Storage.

The adapter should contain/use a LegacyFileSystem.

Save() must translate:
std::string
       ↓
const char*
and calculate the correct size.

Don't add unnecessary classes.

Your task
Implement only these three things:
class Storage
class LegacyFileSystem
and
class LegacyFileSystemAdapter
The first two are already given above, so your real task is the adapter.
Try writing it yourself before looking for a solution.
The key question you should ask yourself is:
"What interface does the client expect, and what interface does 
the old class provide? Where exactly do I translate between the two?"
That question is essentially the Adapter Pattern. */


