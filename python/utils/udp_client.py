import socket
import json


def call_method(hostname: str, port: int, method: str, payload=None, timeout: float = -1) -> dict:
    request = {
        "method": method,
        "request": payload
    }
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.sendto(json.dumps(request).encode('utf-8'), (hostname, port))
    if timeout >= 0:
        s.settimeout(timeout)
    response = {"result": {"result": False, "error": "No response"}}
    try:
        data, address = s.recvfrom(4096)
        if address[1] != port:
            response = {"result": {"result": False, "error": "Sender has different address then receiver!"}}
        else:
            response = json.loads(data.decode("utf-8"))
    except socket.timeout:
        response = {"result": {"result": False, "error": "Connection timed out"}}
    return response


def start_task(hostname: str, task: str, parameters={}, queue=False, timeout=-1) -> dict:
    payload = {
        "task": task,
        "parameters": parameters,
        "queue": queue
    }
    return call_method(hostname, 12002, "start_task", payload, timeout)


def stop_task(hostname: str, nominal=False, success=False, recover=False, empty_queue=False, cost_suc=0.0, cost_err=0.0) -> dict:
    payload = {
        "nominal": nominal,
        "success": success,
        "recover": recover,
        "empty_queue": empty_queue,
        "cost_suc": cost_suc,
        "cost_err": cost_err
    }
    return call_method(hostname, 12002, "stop_task", payload)


def wait_for_task(hostname: str, task_uuid: str) -> dict:
    payload = {
        "task_uuid": task_uuid
    }
    return call_method(hostname, 12002, "wait_for_task", payload)

