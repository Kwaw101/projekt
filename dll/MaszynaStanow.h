#pragma once
#include <memory>
#include <stack>
#include "state.h"
using namespace std;

class __declspec(dllexport) MaszynaStanow
{
private:
    stack<std::unique_ptr<state>> _states;
    unique_ptr<state> _newState;

    bool _isRemoving = false;
    bool _isAdding = false;
    bool _isReplacing = false;

public:
    MaszynaStanow() = default;
    ~MaszynaStanow() = default;

    void addState(std::unique_ptr<state> newState, bool isReplacing = true);
    void removeState();
    void processStateChanges();

    unique_ptr<state>& getActiveState();
};

