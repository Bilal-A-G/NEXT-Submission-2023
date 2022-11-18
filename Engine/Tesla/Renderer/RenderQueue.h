#pragma once
#include "vector"
#include "Mesh/Mesh.h"

namespace TESLA
{
    class RenderQueue
    {
    public:
        RenderQueue() = delete;
        
        static void AddToQueue(Mesh* toAdd)
        {
            m_queue.push_back(toAdd);
        }

        static void RemoveFromQueue(Mesh* toRemove)
        {
            for(int i = 0; i < m_queue.size(); i++)
            {
                if(m_queue[i] == toRemove)
                {
                    m_queue.erase(m_queue.begin() + i);
                }
            }
        }
        
        static std::vector<Mesh*>& GetQueue(){return m_queue;}
    private:
        static std::vector<Mesh*> m_queue;
    };
}

