#ifndef PROVIDED_INCLUDED
#define PROVIDED_INCLUDED

#include <string>

const int VACANT = -1;
const int RED = 0;
const int BLACK = 1;
const int TIE_GAME = -1;

class ScaffoldImpl;

class Scaffold
{
  public:
    Scaffold(int nColumns, int nLevels);
    ~Scaffold();
    Scaffold(const Scaffold& other);
    Scaffold& operator=(const Scaffold& rhs);
    int cols() const;
    int levels() const;
    int numberEmpty() const;
    int checkerAt(int column, int level) const;
    void display() const;
    bool makeMove(int column, int color);
    int undoMove();
  private:
    ScaffoldImpl* m_impl;
};

class Player
{
  public:
    Player(std::string nm) : m_name(nm) {}
    virtual ~Player() {}
    std::string name() const { return m_name; };
    virtual bool isInteractive() const { return false; }
    virtual int chooseMove(const Scaffold& s, int N, int color) = 0;
      // We prevent any kind of Player object from being copied or assigned by
      // making the copy constructor and assignment operator unavailable in
      // the base class (and thus in any derived class).
    Player(const Player& other) = delete;
    Player& operator=(const Player& other) = delete;
  private:
    std::string m_name;
};

class HumanPlayerImpl;

class HumanPlayer : public Player
{
  public:
    HumanPlayer(std::string nm);
    virtual ~HumanPlayer();
    virtual bool isInteractive() const { return true; }
    virtual int chooseMove(const Scaffold& s, int N, int color);
  private:
    HumanPlayerImpl* m_impl;
};

class BadPlayerImpl;

class BadPlayer : public Player
{
  public:
    BadPlayer(std::string nm);
    virtual ~BadPlayer();
    virtual int chooseMove(const Scaffold& s, int N, int color);
  private:
    BadPlayerImpl* m_impl;
};

class SmartPlayerImpl;

class SmartPlayer : public Player
{
  public:
    SmartPlayer(std::string nm);
    virtual ~SmartPlayer();
    virtual int chooseMove(const Scaffold& s, int N, int color);
  private:
    SmartPlayerImpl* m_impl;
};

class GameImpl;

class Game
{
  public:
    Game(int nColumns, int nLevels, int N, Player* red, Player* black);
    ~Game();
    bool completed(int& winner) const;
    bool takeTurn();
    void play();
    int checkerAt(int c, int r) const;
      // We prevent a Game object from being copied or assigned by
      // making the copy constructor and assignment operator unavailable.
    Game(const Game& other) = delete;
    Game& operator=(const Game& other) = delete;
  private:
    GameImpl* m_impl;
};

//==========================================================================
// AlarmClock ac(numMilliseconds);  // Set an alarm clock that will time out
//                                  // after the indicated number of ms
// if (ac.timedOut())  // Will be false until the alarm clock times out; after
//                     // that, always returns true.
//==========================================================================

#include <chrono>
#include <future>
#include <atomic>

class AlarmClock
{
  public:
    AlarmClock(int ms)
     : m_timedOut(false), m_isRunning(true)
    {
        m_alarmClockFuture = std::async([=]() {
            for (int k = 0; k < ms  &&  m_isRunning; k++)
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            if (m_isRunning)
                m_timedOut = true;
        });
    }

    ~AlarmClock()
    {
        m_isRunning = false;
        m_alarmClockFuture.get();
    }

    bool timedOut() const
    {
        return m_timedOut;
    }

    AlarmClock(const AlarmClock&) = delete;
    AlarmClock& operator=(const AlarmClock&) = delete;
  private:
    std::atomic<bool> m_timedOut;
    std::atomic<bool> m_isRunning;
    std::future<void> m_alarmClockFuture;
};

#endif // PROVIDED_INCLUDED
