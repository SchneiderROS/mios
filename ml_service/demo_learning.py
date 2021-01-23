from definitions.insertion_definitions import insert_key_demo
from utils.experiment_wizard import start_experiment
from services.cmaes import CMAESConfiguration
from utils.udp_client import call_method
from utils.udp_client import start_task


def learn():
    pd = insert_key_demo("abus_e30", 1)
    config = CMAESConfiguration()
    config.n_ind = 5
    robot = "collective-panda-005.local"
    call_method(robot, 12002, "set_grasped_object", {"object": "key_abus_e30"})
    start_experiment(robot, [robot], pd, config, keep_record=False)


def learn_2():
    robot = "collective-panda-005.local"
    call_method(robot, 12002, "set_grasped_object", {"object": "key_abus_e30"})
    start_task(robot, "InsertObject", {
        "parameters":{
            "Insertable": "key_abus_e30",
            "InsertInto": "lock_abus_e30",
            "approach": "lock_abus_e30_above"
        },
        "skills": {
            "insertion": {
                "control": {
                    "K": [200, 200, 10, 10, 10, 10]
                }
            }
        }
    })

    start_task(robot, "ExtractObject", {
        "parameters":
            {
                "Extractable": "key_abus_e30",
                "extract_from": "lock_abus_e30",
                "extract_to": "lock_abus_e30_above"
            }
    })

    start_task(robot, "InsertObject", {
        "parameters":{
            "Insertable": "key_abus_e30",
            "InsertInto": "lock_abus_e30",
            "approach": "lock_abus_e30_above"
        },
        "skills": {
            "insertion": {
                "control": {
                    "K": [200, 200, 10, 10, 10, 10]
                },
                "skill": {
                    "offset": [0.003, -0.002, 0, -5, -5, 0]
                }
            }
        }
    })

    start_task(robot, "ExtractObject", {
        "parameters":
            {
                "Extractable": "key_abus_e30",
                "extract_from": "lock_abus_e30",
                "extract_to": "lock_abus_e30_above"
            }
    })

    start_task(robot, "InsertObject", {
        "parameters":{
            "Insertable": "key_abus_e30",
            "InsertInto": "lock_abus_e30",
            "approach": "lock_abus_e30_above"
        },
        "skills": {
            "insertion": {
                "control": {
                    "K": [200, 200, 10, 10, 10, 10]
                }
            }
        }
    })

    start_task(robot, "ExtractObject", {
        "parameters":
            {
                "Extractable": "key_abus_e30",
                "extract_from": "lock_abus_e30",
                "extract_to": "lock_abus_e30_above"
            }
    })

    start_task(robot, "InsertObject", {
        "parameters":{
            "Insertable": "key_abus_e30",
            "InsertInto": "lock_abus_e30",
            "approach": "lock_abus_e30_above"
        },
        "skills": {
            "insertion": {
                "control": {
                    "K": [200, 200, 10, 10, 10, 10]
                }
            }
        }
    })

    start_task(robot, "ExtractObject", {
        "parameters":
            {
                "Extractable": "key_abus_e30",
                "extract_from": "lock_abus_e30",
                "extract_to": "lock_abus_e30_above"
            }
    })
    trial_successful()


def trial_successful():
    robot = "collective-panda-005.local"
    call_method(robot, 12002, "set_grasped_object", {"object": "key_abus_e30"})
    start_task(robot, "InsertObject", {
        "parameters":{
            "Insertable": "key_abus_e30",
            "InsertInto": "lock_abus_e30",
            "approach": "lock_abus_e30_above"
        },
        "skills": {
            "insertion": {
                "control": {
                    "K": [1000, 1000, 1000, 100, 100, 100]
                },
                "skill": {
                    "offset": [0, 0, 0, 0, 5, 0]
                }
            }
        }
    })

    start_task(robot, "ExtractObject", {
        "parameters":
            {
                "Extractable": "key_abus_e30",
                "extract_from": "lock_abus_e30",
                "extract_to": "lock_abus_e30_above"
            }
    })