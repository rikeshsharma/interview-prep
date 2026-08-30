# Inter-Process Communication

- A process has its own isolated virtual address space.
- but this create a problem that process cannot communicate directly
- this is overcomed by various methods of inter process communication.

                    IPC
                     │
       ┌─────────────┼─────────────┐
       │             │             │
     Pipes     Shared Memory    Message
       │             │          Passing
       │             │             │
   ┌───┴───┐         │        ┌────┴────┐
 Anonymous Named     │      Message   Socket
  Pipe     Pipe      │      Queue
                     │
                synchronization
                required

1. Pipe: A pipe provide a communication channel between processes
  - Anonymos Pipe
  - Named Pipe : Similar to anonymous pipe expect it has a name in
                filesystem

2. Shared Memory: two or more processes map the same physical memory
                   into their virtual address spaces.
  - Shared memory gives you shared data, but it doesn't automatically
    give you safe access
  - Shared memory usually needs synchronization.
                      Process A ──┐
                                  ↓
                             Shared Memory
                                  ↑
                      Process B ──┘

- Process synchronization: It is mechanism used to coordinate multiple
processes that access shared resources, so they don't interfere with each 
other and produce incorrect results.

3. Message Passing: It is an IPC mechanism where processes communicate 
by sending and receiving messages through the operating system, rather 
than directly sharing memory.

-           Process A                         Process B
               |                                  |
               | -------- send(message) --------> |
               |        Operating System          |
               | <------- receive(message) ------ |

-                         Process A
                            |
                            | message
                            ↓
                           Kernel
                            |
                            | message
                            ↓
                          Process B
- It makes synchronization and isolation easier in many designs.

    - Synchronous Message Passing: The sender/receiver may block until
                                  the corresponding operation can proceed
    - Asynchronous Message Passing: The sender can continue after putting
                                    the message into a queue/buffer.
                                    Receiver can receive it later.
    - Can be achieved by **Message Queue**
or using
--- 
- **Socket**: This can be used for same as well as different machine
Process A ─── socket ─── Process B
---
Machine A                  Machine B

Process A                  Process B
    │                          │
 Socket                      Socket
    │                          │
    └────── Network ───────────┘
---
Examples:
- HTTP
- databases
- microservices
- distributed systems

4. Signals: are a mechanism for notifying a process that an event occurred.
SIGINT    → interrupt, e.g. Ctrl+C
SIGTERM   → request termination
SIGKILL   → force termination
SIGSTOP   → stop process
SIGCHLD   → child process changed state
---

1. 
- Anonymous Pipe
```cpp
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>

int main() {
    int pipefd[2];
    // pipefd[0] = read end
    // pipefd[1] = write end
    pipe(pipefd);
    pid_t pid = fork();
    if (pid == 0) {
        // =====================
        // Child process
        // =====================
        close(pipefd[1]);  // Child only reads
        char buffer[100];
        ssize_t bytesRead = read(pipefd[0], buffer, sizeof(buffer) - 1);
        buffer[bytesRead] = '\0';
        std::cout << "Child received: " << buffer << '\n';
        close(pipefd[0]);
    }
    else {
        // =====================
        // Parent process
        // =====================
        close(pipefd[0]);  // Parent only writes
        const char* message = "Hello from parent!";
        write(pipefd[1], message, strlen(message));
        close(pipefd[1]);
        wait(nullptr);
    }
    return 0;
}
```

- Named Pipe
process 1 writer
```cpp
#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>

int main() {
    const char* pipeName = "/tmp/myfifo";
    // Create the named pipe
    mkfifo(pipeName, 0666);
    // Open for writing
    int fd = open(pipeName, O_WRONLY);
    const char* message = "Hello from writer!";
    write(fd, message, strlen(message));
    close(fd);
    return 0;
}
```
process 2 reader
```cpp
#include <iostream>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char* pipeName = "/tmp/myfifo";
    // Open for reading
    int fd = open(pipeName, O_RDONLY);
    char buffer[100];
    ssize_t bytesRead = read(fd, buffer, sizeof(buffer) - 1);
    buffer[bytesRead] = '\0';
    std::cout << "Received: " << buffer << '\n';
    close(fd);
    return 0;
}
```

2. Shared Memory
Process 1 - writer
```cpp
#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <cstring>

int main() {
    const char* name = "/my_shared_memory";
    // Create shared memory
    int fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    // Give it a size
    ftruncate(fd, 1024);
    // Map it into our process's address space
    void* ptr = mmap(
        nullptr,
        1024,
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        fd,
        0
    );
    char* sharedMemory = static_cast<char*>(ptr);
    // Write into shared memory
    const char* message = "Hello from Process 1!";
    strcpy(sharedMemory, message);
    std::cout << "Writer wrote: " << sharedMemory << '\n';
    // Cleanup mapping
    munmap(ptr, 1024);
    close(fd);
    return 0;
}
```
Process 2 - reader
```cpp
#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

int main() {
    const char* name = "/my_shared_memory";
    // Open existing shared memory
    int fd = shm_open(name, O_RDWR, 0666);
    // Map it into our process
    void* ptr = mmap(
        nullptr,
        1024,
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        fd,
        0
    );
    char* sharedMemory = static_cast<char*>(ptr);
    // Read from shared memory
    std::cout << "Reader received: "
              << sharedMemory
              << '\n';
    munmap(ptr, 1024);
    close(fd);
    // Remove shared memory object
    shm_unlink(name);
    return 0;
}
```

3. Message Passing

- message queue
sender
```cpp
#include <iostream>
#include <cstring>

#include <fcntl.h>      // O_CREAT, O_WRONLY
#include <sys/stat.h>   // mode constants
#include <mqueue.h>     // POSIX message queues
#include <unistd.h>     // sleep()

int main() {
    // ---------------------------------------------------------
    // Name of the message queue.
    //
    // Unlike an anonymous pipe, a message queue has a name.
    // Therefore, two unrelated processes can open the same queue.
    // ---------------------------------------------------------
    const char* queueName = "/my_message_queue";
    // ---------------------------------------------------------
    // Create the message queue.
    //
    // O_CREAT -> create it if it doesn't already exist
    // O_WRONLY -> this process only wants to send messages
    //
    // 0666 -> permissions
    // ---------------------------------------------------------
    mqd_t queue = mq_open(
        queueName,
        O_CREAT | O_WRONLY,
        0666,
        nullptr
    );
    if (queue == (mqd_t)-1) {
        perror("mq_open");
        return 1;
    }
    // ---------------------------------------------------------
    // Message we want to send.
    // ---------------------------------------------------------
    const char* message = "Hello from sender!";
    // ---------------------------------------------------------
    // Put the message into the message queue.
    //
    // mq_send() does NOT send directly to the receiver.
    //
    // Conceptually:
    //
    // Sender
    //   |
    //   | mq_send()
    //   ↓
    // Message Queue
    //   |
    //   | mq_receive()
    //   ↓
    // Receiver
    //
    // The message waits in the queue until the receiver
    // retrieves it.
    // ---------------------------------------------------------
    if (mq_send(
            queue,
            message,
            strlen(message) + 1,
            0
        ) == -1) {

        perror("mq_send");

        mq_close(queue);
        return 1;
    }
    std::cout << "Message sent!\n";
    // ---------------------------------------------------------
    // Close our connection to the queue.
    // ---------------------------------------------------------
    mq_close(queue);
    return 0;
}
```

receiver
```cpp
#include <iostream>

#include <fcntl.h>      // O_RDONLY
#include <mqueue.h>     // POSIX message queues
#include <unistd.h>     // sleep()

int main() {
    // ---------------------------------------------------------
    // The receiver uses the SAME queue name as the sender.
    //
    // This is how the two unrelated processes find the same
    // message queue.
    // ---------------------------------------------------------
    const char* queueName = "/my_message_queue";
    // ---------------------------------------------------------
    // Open the existing message queue for reading.
    // ---------------------------------------------------------
    mqd_t queue = mq_open(
        queueName,
        O_RDONLY
    );
    if (queue == (mqd_t)-1) {
        perror("mq_open");
        return 1;
    }
    // ---------------------------------------------------------
    // Buffer where the received message will be stored.
    //
    // For this simple example, we know that our message is
    // small enough to fit in this buffer.
    // ---------------------------------------------------------
    char buffer[1024];
    // ---------------------------------------------------------
    // Receive a message from the queue.
    //
    // IMPORTANT:
    //
    // By default, mq_receive() is BLOCKING.
    //
    // If the queue is empty, the receiver sleeps/waits here
    // until a message becomes available.
    //
    // Once the sender puts a message into the queue:
    //
    // Message Queue
    //      |
    //      | mq_receive()
    //      ↓
    //   Receiver
    // ---------------------------------------------------------
    ssize_t bytesReceived = mq_receive(
        queue,
        buffer,
        sizeof(buffer),
        nullptr
    );
    if (bytesReceived == -1) {
        perror("mq_receive");

        mq_close(queue);
        return 1;
    }
    // ---------------------------------------------------------
    // mq_receive() gives us the number of bytes received.
    //
    // We make sure the buffer is null-terminated so that
    // we can print it as a C string.
    // ---------------------------------------------------------
    buffer[bytesReceived] = '\0';
    std::cout << "Received: "
              << buffer
              << '\n';
    // ---------------------------------------------------------
    // Close the queue from this process.
    // ---------------------------------------------------------
    mq_close(queue);
    // ---------------------------------------------------------
    // Remove the message queue from the system.
    //
    // This is similar to deleting the named IPC object.
    //
    // Usually, you want one process to be responsible for
    // calling mq_unlink() when the queue is no longer needed.
    // ---------------------------------------------------------
    mq_unlink(queueName);
    return 0;
}
```