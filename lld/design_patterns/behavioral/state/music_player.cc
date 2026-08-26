/*
Scenario: Music Player
We have a music player with three states:
Stopped
Playing
Paused
It supports these operations:
play()
pause()
stop()
The behavior is:
Stopped
play():
Starting playback...
→ transition to Playing
pause():
Cannot pause. Music is stopped.
stop():
Already stopped.
Playing
play():
Already playing.
pause():
Pausing music...
→ transition to Paused
stop():
Stopping music...
→ transition to Stopped
Paused
play():
Resuming music...
→ transition to Playing
pause():
Already paused.
stop():
Stopping music...
→ transition to Stopped
Your Task
Implement the State Pattern with approximately this structure:
*/

#include <iostream>
#include <string>
#include <memory>

class MusicPlayer;


class PlayerState {
public:
    virtual void play(MusicPlayer&) = 0;
    virtual void pause(MusicPlayer&) = 0;
    virtual void stop(MusicPlayer&) = 0;

    virtual ~PlayerState() = default;
};

class StoppedState : public PlayerState {
public:
  void play(MusicPlayer& player) override;
  void pause(MusicPlayer& player) override;
  void stop(MusicPlayer& player) override;
};

class PlayingState : public PlayerState {
public:
  void play(MusicPlayer& player) override;
  void pause(MusicPlayer& player) override;
  void stop(MusicPlayer& player) override;
};

class PausedState : public PlayerState {
public:
  void play(MusicPlayer& player) override;
  void pause(MusicPlayer& player) override;
  void stop(MusicPlayer& player) override;
};

// And the Context:
class MusicPlayer {
private:
  std::unique_ptr<PlayerState> player_state_;
public:
    MusicPlayer() : player_state_(std::make_unique<StoppedState>()) {}
    void play() {
      player_state_->play(*this);
    }
    void pause() {
      player_state_->pause(*this);
    }
    void stop() {
      player_state_->stop(*this);
    }

    void setState(std::unique_ptr<PlayerState> player_state) {
      player_state_ = std::move(player_state);
    }
};

// Then create:
void StoppedState::play(MusicPlayer& player) {
  std::cout<<"Starting playback...\n";
  player.setState(std::make_unique<PlayingState>());
}
void StoppedState::pause(MusicPlayer& player) {
  std::cout<<"Cannot pause. Music is stopped.\n";
}
void StoppedState::stop(MusicPlayer& player) {
  std::cout<<"Already stopped.\n";
}

void PlayingState::play(MusicPlayer& player) {
  std::cout<<"Already playing.\n";
}
void PlayingState::pause(MusicPlayer& player) {
  std::cout<<"Pausing music...\n";
  player.setState(std::make_unique<PausedState>());
}
void PlayingState::stop(MusicPlayer& player) {
  std::cout<<"Stopping music...\n";
  player.setState(std::make_unique<StoppedState>());
}

void PausedState::play(MusicPlayer& player) {
  std::cout<<"Resuming music...\n";
  player.setState(std::make_unique<PlayingState>());
}
void PausedState::pause(MusicPlayer& player) {
  std::cout<<"Already paused.\n";
}
void PausedState::stop(MusicPlayer& player) {
  std::cout<<"Stopping music...\n";
  player.setState(std::make_unique<StoppedState>());
}

/*
Important constraints
1. Do not use enum State.
2. Do not use switch.
3. MusicPlayer must delegate operations to the current state.
4. State transitions must happen through MusicPlayer.
5. Use runtime polymorphism.
6. Use proper ownership for the state objects.
7. You only need to write the State Pattern classes and MusicPlayer.
I will provide the main() myself below so you can test your implementation against it:
*/

int main() {

    MusicPlayer player;

    player.stop();

    player.play();

    player.play();

    player.pause();

    player.pause();

    player.play();

    player.stop();

    player.pause();

    return 0;
}

/*
Expected output
Already stopped.
Starting playback...
Already playing.
Pausing music...
Already paused.
Resuming music...
Stopping music...
Cannot pause. Music is stopped.
Your challenge: write the complete implementation of PlayerState, StoppedState, PlayingState, PausedState, and MusicPlayer.
*/
