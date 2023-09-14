#include "StateManager.h"
#include <iostream>

namespace EdgarSam
{
    void StateManager::PushState(std::unique_ptr<State> newState, bool isReplacing, bool isRemoving)
    {
        this->currentState_ = std::move(newState);
        this->isReplacing_ = isReplacing;
        this->isAdding_ = true;
        this->isRemoving_ = isRemoving;
    }
    void StateManager::AddState()
    {
        if (!states_.empty())
        {
            if (this->isReplacing_)
            {
                this->states_.pop_back();
            }
            else
            {
                this->states_[this->currentIndex_]->Pause();
            }
        }
        states_.push_back(std::move(this->currentState_));
        currentIndex_ = states_.size() - 1;
        states_[currentIndex_]->InitState();
    }

    void StateManager::RemoveState()
    {
        if (this->isRemoving_)
        {
            states_.pop_back();

            if (!states_.empty())
            {
                currentIndex_ = states_.size() - 1;
                states_[currentIndex_]->Resume();
            }
            else
            {
                currentIndex_ = -1;
            }
            this->isRemoving_ = false;
        }
    }

    void StateManager::UpdateState()
    {
        if (!states_.empty())
        {
            this->RemoveState();
        }
        if (this->isAdding_)
        {
            this->AddState();
            this->isAdding_ = false;
        }
    }

    std::unique_ptr<State> &StateManager::getActiveState()
    {
        if (currentIndex_ >= 0 && currentIndex_ < states_.size())
        {
            return states_[currentIndex_];
        }
        else
        {
            static std::unique_ptr<State> nullState(nullptr);
            return nullState;
        }
    }
}
