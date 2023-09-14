#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <vector>
#include <memory>
#include "State.h"

namespace EdgarSam
{
    class StateManager
    {
    public:
        StateManager() {}
        ~StateManager() {}
        void PushState(std::unique_ptr<State> newState, bool isReplacing = true, bool isRemoving = false);
        void AddState();
        void RemoveState();
        void UpdateState();
        std::unique_ptr<State> &getActiveState();

    private:
        std::vector<std::unique_ptr<State>> states_;
        int currentIndex_;
        bool isReplacing_;
        bool isAdding_;
        bool isRemoving_;
        std::unique_ptr<State> currentState_;
    };
}
#endif
