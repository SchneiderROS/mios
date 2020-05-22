#pragma once

#include "skill/skill.hpp"
#include <memory>
#include <atomic>

namespace mios {
class Core;
class Memory;

class SkillEngine{
public:
    SkillEngine(Core* core);

    bool load_skill(std::shared_ptr<Skill> skill);
    void unload_skill();
    bool execute_skill();
    void stop_skill(bool success);
    Actuator* get_next_command(const Percept& percept);

private:

    Core* m_core;
    Memory* m_memory;

    std::shared_ptr<Skill> m_active_skill;
};

}
