#pragma once

#include "manipulation_primitive/manipulation_primitive.hpp"


namespace mios {

struct ConfigMP_NullPrimitive : public ConfigMP{

};

struct EvalMP_NullPrimitive : public EvalMP{

};

struct NullAttractor : public Attractor{
    void reset(){
    }
};

class NullPrimitive : public ManipulationPrimitive{
public:
    NullPrimitive();

    void initialize(const Percept &p_0,const std::shared_ptr<ConfigUser> config);
    CmdMP& step(const Percept& p);
    void terminate();

    bool in_attractor(const Percept &p);
    bool init_attractor(const Percept &p, const std::shared_ptr<ConfigUser> config);
    bool check_attractor();

    void setup_logs(unsigned long long length);
    void write_logs();
};

}
