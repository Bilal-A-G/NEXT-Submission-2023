#pragma once
#include "vector"

namespace TESLA
{
    class RenderQueue
    {
    public:
        RenderQueue() = delete;
        
        static void AddToQueue(void* toAdd)
        {
            m_queue.push_back(toAdd);
        }

        static void RemoveFromQueue(void* toRemove)
        {
            for(int i = 0; i < m_queue.size(); i++)
            {
                if(m_queue[i] == toRemove)
                {
                    m_queue.erase(m_queue.begin() + i);
                }
            }
        }

        static std::vector<void*>& GetQueue(){return m_queue;}
    private:
        static std::vector<void*> m_queue;
    };
}

