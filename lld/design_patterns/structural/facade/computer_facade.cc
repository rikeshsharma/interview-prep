/*
Implement a Computer Startup Facade.
You are given these subsystem classes:
*/
#include <iostream>
#include <string>
class CPU {
public:
    void Freeze() {
      std::cout << "Freeze the cpu\n";
    }
    void Jump(long position) {
      std::cout << "Jumpt to position: " <<position<<"\n";
    }
    void Execute() {
      std::cout << "Execute the instruction\n";
    }
};

class Memory {
public:
    void Load(long position, const std::string& data) {
      std::cout << "Load the position: " << position 
                <<" with data: "<< data << "\n";
    }
};

class HardDrive {
public:
    std::string Read(std::string lba, int size) {
      std::cout << "Read lba: "<<lba<<" size: "<<size<<"\n";
      return "";
    }
};
/*
Your job is to create:
*/
class ComputerFacade {
  CPU cpu_;
  Memory memory_;
  HardDrive harddrive_;
public:
  ComputerFacade() = default;
  ComputerFacade(CPU cpu, Memory memory, HardDrive harddrive)
                : cpu_(cpu), memory_(memory), harddrive_(harddrive) {}
  void Start() {
    cpu_.Freeze();
    harddrive_.Read("BOOT", 1024);
    memory_.Load(0, "data");
    cpu_.Jump(0);
    cpu_.Execute();
  }
};
/*
Start() should perform this sequence:
1. CPU.Freeze()

2. HardDrive.Read("BOOT", 1024)

3. Memory.Load(0, data)

4. CPU.Jump(0)

5. CPU.Execute()
The client should eventually be able to do only:
ComputerFacade computer;
computer.Start();
Constraints
Don't modify the existing subsystem classes.
ComputerFacade should own/use the subsystem objects.
Don't put subsystem logic into the client.
Use proper C++ encapsulation.
You don't need inheritance or virtual functions for this exercise.
Try writing the complete C++ implementation yourself.
*/

int main() {
  ComputerFacade computer;
  computer.Start();
  return 0;
}