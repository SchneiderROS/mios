#pragma once

#include <unordered_map>
#include <string>
#include <nlohmann/json.hpp>

#include "task/task.hpp"

namespace mios {

struct TaskData{
    nlohmann::json context;
    TaskResult result;
    std::string name;
};

}
