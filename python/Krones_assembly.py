from mios_examples import *
from industrial_tasks import *
import math
#was brauche ich?
#Move
#MoveToContact
#Grasp
#Screw
#Insert

poses=[
    "idlePoseKrones",
    "standardPoseObjects",
    "screwPeg1Pose",
    "screwPeg1PoseApproach",
    "screwPeg2Pose",
    "screwPeg2PoseApproach",
    "ringPose",
    "ringPoseApproach",
    "screwPose",
    "screwPoseApproach",
    "pegPose1",
    "pegPoseApproach1",
    "pegPose2",
    "pegPose2Approach2",
    "screwPeg1InsertionPose",
    "screwPeg1InsertionPoseApproach",
    "screwPeg2InsertionPose",
    "screwPeg2InsertionPoseApproach",

]




robot_ip= "10.157.174.197"
#todo ->teach


#move(robot_ip,location)






# #teach_robot_poses(robot_ip,13000)

# #start_task_and_wait(robot_ip, "MoveToCartPose",port=13000, parameters={"parameters": {"pose":poses[0]}})
# release(robot_ip,13000)
# #start_task_and_wait(robot_ip, "MoveToCartPose",port=13000, parameters={"parameters": {"pose":poses[1]}})

# #start_task_and_wait(robot_ip, "MoveToCartPose",port=13000, parameters={"parameters": {"pose":"screwPeg1Pose"}})
# start_task_and_wait(robot_ip, "MoveToJointPose",port=13000, parameters={"parameters": {"pose":"screwPeg2Pose"}})

# graspObject(robot_ip,"screwPeg2Pose",port=13000)
# start_task_and_wait(robot_ip, "MoveToCartPose",port=13000, parameters={"parameters": {"pose":"screwPeg2PoseApproach"}})

# start_task_and_wait(robot_ip, "MoveToCartPose",port=13000, parameters={"parameters": {"pose":"idlePoseKrones"}})
# start_task_and_wait(robot_ip, "MoveToJointPose",port=13000, parameters={"parameters": {"pose":"screwPeg2InsertionPoseApproach"}})
# start_task_and_wait(robot_ip, "MoveToCartPose",port=13000, parameters={"parameters": {"pose":"screwPeg2InsertionPose"}})

screw(robot_ip,'screwPeg2InsertionPoseApproach','screwPeg2InsertionPose',port=13000 )

# for i in range(3):s
#     start_task_and_wait(robot_ip, "MoveToJointPose",port=12000, parameters={"parameters": {"pose":"pose1_0"}})
#     start_task_and_wait(robot_ip, "MoveToJointPose",port=12000, parameters={"parameters": {"pose":"pose1_1"}})
#     start_task_and_wait(robot_ip, "MoveToJointPose",port=12000, parameters={"parameters": {"pose":"pose1_2"}})

#start_task_and_wait(robot_ip, "MoveToJointPose", parameters={"parameters": {"q_g": [0,0,0,0,0,0,0], "pose":"NoneObject"}})

#def move(robot, location, offset = [0,0,0], port=12000, wait = True,f_ext = [10,5], add_nullspace=False):
