#include "task/taskobserver.hpp"

namespace mios {

TaskObserver::TaskObserver(){
    m_finished.lock();
}

void TaskObserver::wait_for_finish(){
    std::scoped_lock<std::mutex> finish_lock(m_finished);
}

void TaskObserver::finish(){
    m_finished.unlock();
}

}
