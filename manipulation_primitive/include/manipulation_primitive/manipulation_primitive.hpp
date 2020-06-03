#pragma once

#include "data_structures/percept.hpp"
#include "data_structures/actuator.hpp"
#include "strategy/primitive_strategy.hpp"
#include <set>

namespace mios {

class Memory;

class Attractor{
public:
    virtual bool reached(const Percept& p) = 0;
};

class MPParameters{

};

class ManipulationPrimitive{
public:
    ManipulationPrimitive(const std::string& type, const std::string& name, const Percept& p_0, Memory* memory, const std::vector<std::shared_ptr<PrimitiveStrategy> > &strategies);

    bool get_flag_error() const;
    void set_flag_error();
    std::string get_type() const;
    std::string get_name() const;

    Actuator* initialize(const Percept &p_0);
    Actuator* initialize(const Percept &p_0, const Actuator &cmd);
    Actuator* step(const Percept& p);
    void terminate(const Percept& p);
    Actuator* cmd_from_buffer();
    Actuator* stop(const Percept &p);
    bool is_settled() const;

private:
    bool compose_command(const Percept &p);

private:
    const std::string m_type;
    const std::string m_name;
    Memory* m_memory;
    std::vector<std::pair<std::shared_ptr<PrimitiveStrategy>,Actuator> > m_strategies;

    Actuator m_cmd;

    bool m_flag_error;
    bool m_flag_initialized;
    bool m_flag_terminated;


};

}
