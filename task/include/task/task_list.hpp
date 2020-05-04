#pragma once

#include <map>
#include <memory>


namespace mios{
class Task;
struct TaskList{
TaskList();
std::map<std::string,std::shared_ptr<Task> > tasks;
};
}
