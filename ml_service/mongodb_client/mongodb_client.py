import pymongo
from bson import objectid
from pymongo import MongoClient
import logging


logger = logging.getLogger("ml_service")

class DatabaseClient():
    """Simple Client for MongoDB interaction"""
    def __init__(self, db_name, host = 'localhost', port = 27017):
        self.client = MongoClient(host, port)
        self.db = self.client[db_name]
        logger.info("MongoDB is initialized at " + host +":"+str(port) + "with name " + db_name)

    def read(self, collection: str, search_param: dict) -> list:
        col = self.db[collection]
        findings = []
        for f in col.find(filter=search_param):
            findings.append(f)
        return findings

    def write(self, collection: str, document: dict or list) -> objectid.ObjectId  or list:
        col = self.db[collection]
        if isinstance(document, list):
            #document_id = col.insert_many(document).inserted_ids
            document_ids = []
            for doc in document:
                single_id = self._write_single(collection, doc)
                document_ids.append(single_id)
        elif isinstance(document, dict):
            document_ids = col.insert_one(document).inserted_id
        else:
            logger.error("Document type is not dict or list, but " + str(type(document)))
            logger.info("Cannot insert document into Database.")
            return False
        return document_ids
    
    def _write_single(self, collection: str, document: dict) -> objectid.ObjectId:
        col = self.db[collection]
        if isinstance(document, dict):
            return col.insert_one(document).inserted_id
        else: 
            logger.error("Document type is not dict, but " + str(type(document)))
            logger.info("Cannot insert document into Database.")
            return False
    
    def remove(self, collection: str, search_param: dict) -> bool:
        col = self.db[collection]
        result = col.delete_one(search_param, collation=None, session=None)
        if result.deleted_count > 0:
            return True
        else:
            return False
    
    def update(self, collection: str, search_param: dict, new_param: dict) -> bool:
        col = self.db[collection]
        if isinstance(search_param, dict):
            if isinstance(new_param, dict):    
                new_param_set = {"$set": new_param}
                col.update_one(search_param, new_param_set)
            else:
                logger.error("new parameter for update are not dict, but " + str(type(new_param)))
                return False
        else:
            logger.error("search parameter for update are not dict, but " + str(type(new_param)))
            return False
        return True
        

    def delete_collection(self, collection: str):
        print(self.db.list_collection_names())
        col = self.db[collection]
        col.drop()
        print(self.db.list_collection_names())

if __name__ == "__main__":
    client = DatabaseClient("testDB_name")
 
    docs = [{"name1": [1,2,3],"name2":"Udo Jürgens"},{"name1": [1,2,3],"name2":"Jens Span"},{"name1": "test","name2":"not_updated"}]
    #docs = [5,4,{"name1": [1,2,3],"name2":"Jens Span"},2]
    id = client.write("col2",docs)
 
    doc = client.read("col2",{"name1": "test"})
    print("found doc:\n", doc)

    client.update("col2",{"name1": "test"},{"name3": "new_updatated"})
    for d in client.read("col2",{}):
        print(d)
    client.delete_collection("col2")

    