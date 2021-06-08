#pragma once

#include "mios/data_structures/results.hpp"
#include "nlohmann/json.hpp"

#include <unordered_map>
#include <string>


namespace mios {

struct TaskData{
    TaskData():name("NullData"),context(nlohmann::json()){

    }
    TaskData(const std::string& name, const nlohmann::json& context, const TaskResult& result):name(name),context(context),result(result){

    }
    std::string name;
    nlohmann::json context;
    TaskResult result;
};

}
