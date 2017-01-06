#ifndef BETTER_STATE
#define BETTER_STATE

class betterState {
public:
    betterState();
    betterState(int, int);
    bool operator<(const betterState&) const;
    int getDirection();
    int getManhattan();
private:
    int direction;
    int manhattan;
};

#endif
