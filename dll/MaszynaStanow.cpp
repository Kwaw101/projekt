#include "MaszynaStanow.h"

void MaszynaStanow::addState(std::unique_ptr<state> newState, bool isReplacing) {
    this->_isAdding = true;
    this->_isReplacing = isReplacing; // Dodaj to pole do klasy w .h
    this->_newState = std::move(newState);
}

void MaszynaStanow::removeState() {
    this->_isRemoving = true;
}

void MaszynaStanow::processStateChanges() {
    if (this->_isRemoving && !this->_states.empty()) {
        this->_states.pop();
        if (!this->_states.empty()) {
            this->_states.top()->resume();
        }
        this->_isRemoving = false;
    }

    if (this->_isAdding) {
        if (!this->_states.empty()) {
            if (this->_isReplacing) {
                this->_states.pop();
            }
            else {
                this->_states.top()->pause();
            }
        }

        this->_states.push(std::move(this->_newState));
        this->_states.top()->init();
        this->_isAdding = false;
    }
}

std::unique_ptr<state>& MaszynaStanow::getActiveState() {
    return this->_states.top();
}