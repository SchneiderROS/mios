#!/usr/bin/python3 -u
import time
import numpy as np

from ws_client import *


def start_skill(address: str, skill: str, parameters: dict, control: dict):
    response = start_task(address, "GenericTask", parameters={"parameters": {
        "skill_names": ["skill"],
        "skill_types": [skill]
    },
        "skills": {
            "skill": {
                "skill": parameters,
                "control": control
            }
        }})
    return response


def test_tax_grab(robot="collective-panda-008.local"):
    start_skill(robot, "TaxGrab", {"objects": {"Retract": "tax_grab_retract", "Approach": "tax_grab_approach",
                                               "Grabbable": "cylinder_60"}, "speed": [0.1, 0.5], "acc": [0.5, 1.0],
                                   "grasp_width": 0.03, "grasp_speed": 2, "grasp_force": 30,
                                   "ROI_x": [-0.2, 0.2, -0.2, 0.2, -0.2, 0.2],
                                   "ROI_phi": [0, 0, 0, 0, 0, 0]}, {"control_mode": 2})


def test_tax_place(robot="collective-panda-008.local"):
    call_method(robot, 12000, "set_grasped_object", {"object": "cylinder_60"})
    start_skill(robot, "TaxPlace", {"objects": {"Retract": "tax_place_retract", "Approach": "tax_place_approach",
                                                "Placeable": "cylinder_60", "Surface": "cylinder_60"},
                                    "speed": [0.05, 0.5], "acc": [0.5, 1.0],
                                    "release_width": 0.06, "release_speed": 2,
                                    "ROI_x": [-0.2, 0.2, -0.2, 0.2, -0.2, 0.2],
                                    "ROI_phi": [0, 0, 0, 0, 0, 0]}, {"control_mode": 0})


def test_tax_turn(robot="collective-panda-008.local"):
    call_method(robot, 12000, "set_grasped_object", {"object": "tax_turn_turnable"})
    start_skill(robot, "TaxTurn", {"objects": {"Turnable": "tax_turn_turnable", "GoalOrientation": "tax_turn_goal"},
                                   "turn_speed": [0.05, 0.5], "turn_acc": [0.5, 1.0]},
                {"control_mode": 0})


def test_tax_press_button(robot="collective-panda-008.local"):
    start_skill(robot, "TaxPressButton",
                {"objects": {"Button": "tax_press_button_button", "Approach": "tax_press_button_approach"},
                 "approach_speed": [0.05, 0.5], "approach_acc": [0.5, 1.0],
                 "press_speed": [0.05, 0.5], "press_acc": [0.5, 1.0], "duration": 5,
                 "ROI_x": [-0.2, 0.2, -0.2, 0.2, -0.2, 0.2],
                 "ROI_phi": [0, 0, 0, 0, 0, 0]},
                {"control_mode": 0})
