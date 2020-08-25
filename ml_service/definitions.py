from problem_definition.domain import Domain
from problem_definition.problem_definition import ProblemDefinition


def insert_cylinder_30():
    limits = {
        "speed_t": (0, 0.2),
        "speed_r": (0, 0.5),
        "acc_t": (0, 0.5),
        "acc_r": (0, 1),
        "wiggle_a_x": (0, 5),
        "wiggle_a_y": (0, 5),
        "wiggle_a_z": (0, 5),
        "wiggle_a_phi": (0, 2),
        "wiggle_a_chi": (0, 2),
        "wiggle_a_psi": (0, 2),
        "wiggle_f_x": (0, 2),
        "wiggle_f_y": (0, 2),
        "wiggle_f_z": (0, 2),
        "wiggle_f_phi": (0, 1),
        "wiggle_f_chi": (0, 1),
        "wiggle_f_psi": (0, 1),
        "stuck_t_thr": (0, 1),
        "stuck_dx_thr": (0, 0.1),
        "offset_x": (-0.01, 0.01),
        "offset_y": (-0.01, 0.01),
        "offset_phi": (-10, 10),
        "offset_chi": (-10, 10)
    }
    context_mapping = {
        "speed_t": ["skills.insertion.skill.traj_speed-1"],
        "speed_r": ["skills.insertion.skill.traj_speed-2"],
        "acc_t": ["skills.insertion.skill.traj_acc-1"],
        "acc_r": ["skills.insertion.skill.traj_acc-2"],
        "wiggle_a_x": ["skills.insertion.skill.search_a-1"],
        "wiggle_a_y": ["skills.insertion.skill.search_a-2"],
        "wiggle_a_z": ["skills.insertion.skill.search_a-3"],
        "wiggle_a_phi": ["skills.insertion.skill.search_a-4"],
        "wiggle_a_chi": ["skills.insertion.skill.search_a-5"],
        "wiggle_a_psi": ["skills.insertion.skill.search_a-6"],
        "wiggle_f_x": ["skills.insertion.skill.search_f-1"],
        "wiggle_f_y": ["skills.insertion.skill.search_f-2"],
        "wiggle_f_z": ["skills.insertion.skill.search_f-3"],
        "wiggle_f_phi": ["skills.insertion.skill.search_f-4"],
        "wiggle_f_chi": ["skills.insertion.skill.search_f-5"],
        "wiggle_f_psi": ["skills.insertion.skill.search_f-6"],
        "stuck_t_thr": ["skills.insertion.skill.stuck_t_thr"],
        "stuck_dx_thr": ["skills.insertion.skill.stuck_dx_thr"],
        "offset_x": ["parameters.offset-1"],
        "offset_y": ["parameters.offset-2"],
        "offset_phi": ["parameters.offset-4"],
        "offset_chi": ["parameters.offset-5"],
    }

    domain = Domain(limits, context_mapping)
    default_context = {
        "name": "InsertObject",
        "parameters": {
            "Insertable": "cylinder_30",
            "InsertInto": "hole_30"
        }
    }
    reset_instructions = []
    reset_instructions.append({
        "name": "ExtractObject",
        "skills": {
            "extraction": {
                "skill": {
                    "traj_speed": [0.05, 0.5],
                    "traj_acc": [0.5, 1],
                    "search_a": [3, 3, 0, 2, 2, 1],
                    "search_f": [1, 0.75, 0, 1, 0.75, 0.5],
                    "stuck_dx_thr": 0.1
                }
            }
        },
        "parameters": {
            "Extractable": "cylinder_30",
            "ExtractFrom": "hole_30"
        }
    })
    pd = ProblemDefinition("insert_object", domain, default_context, [], [], reset_instructions, ["insertion", "cylinder_30"])
    return pd
