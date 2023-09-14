#ifndef STATE_H
#define STATE_H

namespace EdgarSam
{
    class State
    {
    public:
        virtual void InitState() = 0;
        virtual void HandleInput() = 0;
        virtual void Update(float dt) = 0;
        virtual void Draw(float dt) = 0;
        virtual void Pause(){};
        virtual void Resume(){};
    };
}
#endif