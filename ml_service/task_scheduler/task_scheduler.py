import logging
import sys
from threading import Thread
from queue import Queue
from problem_definition.problem_definition import ProblemDefinition
from xmlrpc.client import ServerProxy


logger = logging.getLogger("ml_service")
logger.setLevel(logging.INFO)
handler = logging.StreamHandler(sys.stdout)
handler.setLevel(logging.DEBUG)
logger.addHandler(handler)


class Task:
    def __init__(self, problem_definition: str, service_configuration: str, agents: list, service_url):
        self.problem_definition = problem_definition
        self.service_configuration = service_configuration
        self.agents = agents
        self.service_url = service_url


class TaskScheduler:

    def __init__(self):
        self.unassigned_tasks = Queue()
        self.assigned_tasks = set()
        self.services = set()
        self.keep_running = False

    def add_task(self, task: Task):
        self.unassigned_tasks.put(task)

    def solve_tasks(self):
        while self.keep_running is True and (
                self.unassigned_tasks.empty() is False or self.assigned_tasks.empty() is False):
            task = self.unassigned_tasks.get()  # get next task
            self.unassigned_tasks.task_done()

            if self.is_service_ready(task.service_url) is False:  # if task can not be started...
                self.unassigned_tasks.put(task)  # put it back
                continue
            else:  # if task can be started
                self.assigned_tasks.add(task)
                task_thread = Thread(target=self.solve_task, args=(task,))
                task_thread.start()

    def is_service_ready(self, service_url: str, agents: list) -> bool:
        s = ServerProxy(service_url, allow_none=True)
        return s.is_ready(agents)

    def solve_task(self, task: Task):
        s = ServerProxy(task.service_url, allow_none=True)
        s.start_service(task.problem_definition, task.service_configuration, task.agents, None)
        s.wait_for_service()
        # if successful all fine, else put back to unassigned tasks
