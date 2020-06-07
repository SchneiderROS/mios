#!/usr/bin/python3 -u
import requests
from http.client import HTTPSConnection
import base64
import hashlib
import json
import ssl
import sys
import socket
import time


class FrankaAPI:

    def __init__(self, hostname, user, password):
        self._hostname = hostname
        self._user = user
        self._password = password

    def __enter__(self):
        self._client = HTTPSConnection(self._hostname, context=ssl._create_unverified_context())
        self._client.connect()
        self._client.request('POST', '/admin/api/login',
                             body=json.dumps({'login': self._user,
                                              'password': self.encode_password(self._user, self._password)}),
                             headers={'content-type': 'application/json'})
        self._token = self._client.getresponse().read().decode('utf8')
        return self

    def __exit__(self, type, value, traceback):
        self._client.close()

    def start_task(self, task):
        self._client.request('POST', '/desk/api/execution',
                             body='id=%s' % task,
                             headers={'content-type': 'application/x-www-form-urlencoded',
                                      'Cookie': 'authorization=%s' % self._token})
        return self._client.getresponse().read()

    def stop_task(self):
        self._client.request('DELETE', '/desk/api/execution',
                             headers={'content-type': 'application/x-www-form-urlencoded',
                                      'Cookie': 'authorization=%s' % self._token})
        return self._client.getresponse().read()

    def unlock_brakes(self):
        print('Unlock brakes')
        print(self._hostname)
        print(self._user)
        print(self._password)
        self._client.request('POST', '/desk/api/robot/open-brakes',
                             headers={'content-type': 'application/x-www-form-urlencoded',
                                      'Cookie': 'authorization=%s' % self._token})
        return self._client.getresponse().read()

    def lock_brakes(self):
        self._client.request('POST', '/desk/api/robot/close-brakes',
                             headers={'content-type': 'application/x-www-form-urlencoded',
                                      'Cookie': 'authorization=%s' % self._token})
        return self._client.getresponse().read()

    def shutdown(self):
        self._client.request('POST', '/admin/api/shutdown',
                             headers={'content-type': 'application/json'})

    def pack_pose(self):
        self._client.request('POST', '/desk/api/robot/fold',
                             headers={'content-type': 'application/x-www-form-urlencoded',
                                      'Cookie': 'authorization=%s' % self._token})
        return self._client.getresponse().read()

    def check_timeline(self):
        self._client.request('GET','/desk/api/execution',
                             headers={'content-type': 'application/x-www-form-urlencoded',
                                      'Cookie': 'authorization=%s' % self._token})
        str=self._client.getresponse().read().decode('utf-8')
        info=json.loads(str)
        result = dict()
        if info['lastActivePath'] is None:
            result["finished"]=False
        else:
            result["finished"] = True

    def encode_password(self,user, password):
        bs = ','.join(
            [str(b) for b in hashlib.sha256((password + '#' + user + '@franka').encode('utf-8')).digest()])
        return base64.encodestring(bs.encode('utf-8')).decode('utf-8')


def shutdown(ip, user, pwd):
    try:
        with FrankaAPI(ip, user, pwd) as api:
            api.shutdown()
            return True
    except (socket.error):
        print('Socket error, possibly no host with IP: ', ip,', name: ', name,' and password: ', pwd)
        return False


def unlock_brakes(ip, user, pwd):
    try:
        with FrankaAPI(ip, user, pwd) as api:
            api.unlock_brakes()
            return True
    except (socket.error):
        print('Socket error, possibly no host with IP: ', ip,', name: ', name,' and password: ', pwd)
        return False


def lock_brakes(ip, user, pwd):
    try:
        with FrankaAPI(ip, user, pwd) as api:
            api.lock_brakes()
            return True
    except (socket.error):
        print('Socket error, possibly no host with IP: ', ip,', name: ', name,' and password: ', pwd)
        return False


def pack_pose(ip, user, pwd):
    try:
        with FrankaAPI(ip, name, pwd) as api:
            api.pack_pose()
            return True
    except (socket.error):
        print('Socket error, possibly no host with IP: ', ip,', name: ', name,' and password: ', pwd)
        return False


@dispatcher.add_method
def stop_task(ip, name, pwd):
    try:
        with FrankaAPI(ip, name, pwd) as api:
            api.stop_task()
    except (socket.error):
        print('Socket error, possibly no host with IP: ', ip,', name: ', name,' and password: ', pwd)


@dispatcher.add_method
def check_task(ip, name, pwd):
    try:
        with FrankaAPI(ip, name, pwd) as api:
            return api.check_timeline()
    except (socket.error):
        print('Socket error, possibly no host with IP: ', ip,', name: ', name,' and password: ', pwd)


@dispatcher.add_method
def start_task(ip, name, pwd, task):
    try:
        with FrankaAPI(ip, name, pwd) as api:
            api.start_task(task)
    except (socket.error):
        print('Socket error, possibly no host with IP: ', ip,', name: ', name,' and password: ', pwd)


if __name__ == '__main__':
    if len(sys.argv) <= 4:
        sys.exit("Not enough args")
    fun = sys.argv[1]
    p_hostname = sys.argv[2]
    p_user = sys.argv[3]
    p_password = sys.argv[4]
    if fun == "lock_brakes":
        lock_brakes(p_hostname, p_user, p_password)
    if fun == "unlock_brakes":
        unlock_brakes(p_hostname, p_user, p_password)
    if fun == "shutdown":
        shutdown(p_hostname, p_user, p_password)
    if fun == "pack_pose":
        pack_pose(p_hostname, p_user, p_password)
