import pymongo
from pymongo import MongoClient
import json
import os
from os import listdir
from os.path import isfile, join
import subprocess


def ping_host(hostname):
    return subprocess.call('ping -c 2 ' + hostname, shell=True, stdout=subprocess.DEVNULL, stderr=subprocess.STDOUT)


def download_skill(db_url, skill, check_url=True):
    if check_url:
        if ping_host(db_url) != 0:
            print('Could not reach host at ' + db_url)
            return False
    try:
        client = MongoClient('mongodb://' + db_url + ':27017')
        skills = client.mios.skills

        path_descr = os.getcwd() + '/../../libraries/contexts/skills/'
        if not os.path.isdir(path_descr):
            os.makedirs(path_descr)

        doc = skills.find_one({'name': skill})
        if doc is None:
            print('Skill with name ' + skill + ' does not exist in database.')
            return False
        del doc["_id"]
        with open(path_descr + skill + '.json', 'w') as file:
            json.dump(doc, file)
        return True
    except pymongo.errors.ServerSelectionTimeoutError as e:
        print(e)
        print('Could not reach database on url ' + db_url)
        return False


def upload_skill(db_url, skill, overwrite=False, check_url=True):
    if check_url:
        if ping_host(db_url) != 0:
            print('Could not reach host at ' + db_url)
            return False
    try:
        client = MongoClient('mongodb://' + db_url + ':27017')
        skills = client.mios.skills

        path_context = os.getcwd() + '/../../libraries/contexts/skills/'
        if not os.path.isdir(path_context):
            print('No folder named mios/libraries/contexts/skills/ exists.')
            return False

        if not os.path.isfile(path_context + skill + '.json'):
            print('Can not find skill file ' + skill + '.json. Context files must be stored '
                                                       'in mios/libraries/contexts/skills/ .')
            return False

        with open(path_context + skill + '.json', 'r') as file:
            data = json.load(file)

        doc = skills.find_one({"name": data['name']})
        if doc is not None:
            if overwrite is False:
                print('Skill with id ' + data['name'] + ' already exists in database. To overwrite set the overwrite '
                                                        'flag of this function to True.')
                return False
            else:
                skills.delete_many({'name': data['name']})

        skills.insert_one(data)
        return True
    except pymongo.errors.ServerSelectionTimeoutError as e:
        print(e)
        print('Could not reach url ' + db_url)
        return False


def download_all_skills(db_url):
    if ping_host(db_url) != 0:
        print('Could not reach host at ' + db_url)
        return False
    try:
        client = MongoClient('mongodb://' + db_url + ':27017')
        skills = client.mios.skills
        cursor = skills.find({})
        for doc in cursor:
            download_skill(db_url, doc['name'], False)
        return True
    except pymongo.errors.ServerSelectionTimeoutError as e:
        print(e)
        print('Could not reach url ' + db_url)
        return False


def upload_all_skills(db_url, overwrite=False):
    if ping_host(db_url) != 0:
        print('Could not reach host at ' + db_url)
        return False
    path_context = os.getcwd() + '/../../libraries/contexts/skills/'
    if not os.path.isdir(path_context):
        print('Did not find folder mios/libraries/contexts/skills/ .')
        return False

    skills = [f for f in listdir(path_context) if isfile(join(path_context, f))]
    for s in skills:
        filename = s.split('.')
        if filename[1] != 'json':
            print(s + ' is not a valid description file.')
            return True
        if upload_skill(db_url, filename[0], overwrite, False) is False:
            return False
    return True


def download_task(db_url, task, check_url=True):
    if check_url:
        if ping_host(db_url) != 0:
            print('Could not reach host at ' + db_url)
            return False
    try:
        client = MongoClient('mongodb://' + db_url + ':27017')
        tasks = client.mios.tasks

        path_context = os.getcwd() + '/../../libraries/contexts/tasks/'
        if not os.path.isdir(path_context):
            os.makedirs(path_context)

        doc = tasks.find_one({'name': task})
        if doc is None:
            print('Task with name ' + task + ' does not exist in database.')
            return False
        del doc["_id"]
        with open(path_context + task + '.json', 'w') as file:
            json.dump(doc, file)
        return True
    except pymongo.errors.ServerSelectionTimeoutError as e:
        print(e)
        print('Could not reach url ' + db_url)
        return False


def upload_task(db_url, task, overwrite=False, check_url=True):
    if check_url:
        if ping_host(db_url) != 0:
            print('Could not reach host at ' + db_url)
            return False
    try:
        client = MongoClient('mongodb://' + db_url + ':27017')
        tasks = client.mios.tasks

        path_context = os.getcwd() + '/../../libraries/contexts/tasks/'
        if not os.path.isdir(path_context):
            print('Did not find folder mios/libraries/contexts/tasks/ .')
            return False

        if not os.path.isfile(path_context + task + '.json'):
            print('Can not find task file ' + task + '.json. Descriptions files must be '
                                                     'stored in mios/libraries/contexts/tasks/ .')
            return False

        with open(path_context + task + '.json', 'r') as file:
            data = json.load(file)

        doc = tasks.find_one({"name": data['name']})
        if doc is not None:
            if overwrite is False:
                print('Task with name ' + data['name'] + ' already exists in knowledge base. '
                                                       'To overwrite set the overwrite flag of this function to True.')
                return False
            else:
                tasks.delete_one({'name': data['name']})

        tasks.insert_one(data)
        return True
    except pymongo.errors.ServerSelectionTimeoutError as e:
        print(e)
        print('Could not reach url ' + db_url)
        return False


def download_all_tasks(db_url):
    if ping_host(db_url) != 0:
        print('Could not reach host at ' + db_url)
        return False
    try:
        client = MongoClient('mongodb://' + db_url + ':27017')
        tasks = client.mios.tasks
        cursor = tasks.find({})
        for doc in cursor:
            download_task(db_url, doc['name'], False)
        return True
    except pymongo.errors.ServerSelectionTimeoutError as e:
        print(e)
        print('Could not reach url ' + db_url)
        return False


def upload_all_tasks(db_url, overwrite=False):
    if ping_host(db_url) != 0:
        print('Could not reach host at ' + db_url)
        return False
    path_context = os.getcwd() + '/../../libraries/contexts/tasks/'
    if not os.path.isdir(path_context):
        print('Did not find folder mios/libraries/contexts/tasks/ .')
        return False

    tasks = [f for f in listdir(path_context) if isfile(join(path_context, f))]
    for t in tasks:
        filename = t.split('.')
        if filename[1] != 'json':
            print(t + ' is not a valid description file.')
            return False
        if upload_task(db_url, filename[0], overwrite, False) is False:
            return False
    return True
